// ui-harness: runs the real UI host (Web::Browser::WebRenderer + RmlUi + Lua screens) on a
// D3D9Ex device in a hidden window, driven by a small script, and saves screenshots.
//
//   ui-harness.exe <ui root dir> <script file> [--verbose] [--size WxH]
//
// The ui root is the directory that contains `ui\` (e.g. ElDorito).  Script lines:
//   var <name> <value>                 cvar value (CommandMap::GetVariableString, `command <name>`)
//   result <method|command:cmd> <json> canned bridge result
//   show <screen> [json]               ScreenLayer::Show(screen, json)
//   hide <screen>
//   notify <event> [json] [nobroadcast]
//   notifyscreen <screen> <event> [json]
//   controller <json>                  one controller tick (ui.sendControllerInput)
//   mouse <x> <y> | click <x> <y> | rclick <x> <y> | wheel <delta>
//   key <vk> | char <text>
//   wait <seconds>                     run frames for this long
//   shot <file.png>
//   expect-call <substring>            fail unless a bridge call contains this text
//   expect-clean                       fail if any error was logged so far
//   # comment

#include "hades/hades.h"

#include "Web/Rml/Input.hpp"
#include "Web/Rml/UiRoot.hpp"
#include "Web/WebRenderer.hpp"

#include <RmlUi/Core/Context.h>
#include <RmlUi/Core/ElementDocument.h>

#include "harness.hpp"

#include <d3d9.h>
#include <d3dx9.h>
#include <Windows.h>

#include <chrono>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <thread>

namespace
{
	IDirect3D9Ex *g_d3d = nullptr;
	IDirect3DDevice9Ex *g_device = nullptr;
	HWND g_window = nullptr;
	int g_width = 1280;
	int g_height = 720;
	int g_failures = 0;

	bool CreateDevice()
	{
		WNDCLASSA wc = {};
		wc.lpfnWndProc = DefWindowProcA;
		wc.hInstance = GetModuleHandleA(nullptr);
		wc.lpszClassName = "ui-harness";
		RegisterClassA(&wc);
		g_window = CreateWindowA("ui-harness", "ui-harness", WS_OVERLAPPEDWINDOW, 0, 0, g_width, g_height, nullptr, nullptr, wc.hInstance, nullptr);
		if (!g_window || FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &g_d3d)))
			return false;
		D3DPRESENT_PARAMETERS pp = {};
		pp.Windowed = TRUE;
		pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		pp.BackBufferFormat = D3DFMT_A8R8G8B8;
		pp.BackBufferWidth = g_width;
		pp.BackBufferHeight = g_height;
		pp.EnableAutoDepthStencil = TRUE;
		pp.AutoDepthStencilFormat = D3DFMT_D24S8;
		pp.hDeviceWindow = g_window;
		pp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
		HRESULT hr = g_d3d->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_window,
			D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_FPU_PRESERVE | D3DCREATE_MULTITHREADED, &pp, nullptr, &g_device);
		if (FAILED(hr))
		{
			printf("[harness] CreateDeviceEx failed 0x%08lx\n", hr);
			return false;
		}
		return true;
	}

	void Frame()
	{
		MSG msg;
		while (PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE))
			DispatchMessageA(&msg);
		auto renderer = Web::Browser::WebRenderer::GetInstance();
		// A stand-in for the game frame: a dark blue gradient-ish clear.
		g_device->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_XRGB(30, 38, 52), 1.f, 0);
		g_device->BeginScene();
		if (renderer->Initialized())
		{
			if (renderer->IsRendering())
				renderer->Render(g_device);
			else
				renderer->Update();
		}
		g_device->EndScene();
		g_device->PresentEx(nullptr, nullptr, nullptr, nullptr, 0);
	}

	void RunFor(double seconds)
	{
		auto end = std::chrono::steady_clock::now() + std::chrono::microseconds((long long)(seconds * 1e6));
		do
		{
			Frame();
			std::this_thread::sleep_for(std::chrono::milliseconds(16));
		} while (std::chrono::steady_clock::now() < end);
	}

	bool Screenshot(const std::string &path)
	{
		IDirect3DSurface9 *backBuffer = nullptr, *copy = nullptr;
		if (FAILED(g_device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer)))
			return false;
		D3DSURFACE_DESC desc;
		backBuffer->GetDesc(&desc);
		bool ok = SUCCEEDED(g_device->CreateOffscreenPlainSurface(desc.Width, desc.Height, desc.Format, D3DPOOL_SYSTEMMEM, &copy, nullptr)) &&
			SUCCEEDED(g_device->GetRenderTargetData(backBuffer, copy)) &&
			SUCCEEDED(D3DXSaveSurfaceToFileA(path.c_str(), D3DXIFF_PNG, copy, nullptr, nullptr));
		if (copy) copy->Release();
		backBuffer->Release();
		printf("[harness] shot %s %s\n", path.c_str(), ok ? "ok" : "FAILED");
		return ok;
	}

	void PostInput(UINT message, WPARAM wParam, LPARAM lParam)
	{
		MSG msg = {};
		msg.hwnd = g_window;
		msg.message = message;
		msg.wParam = wParam;
		msg.lParam = lParam;
		Web::RmlUi::Input::Enqueue(msg);
	}

	std::string Rest(std::istringstream &in)
	{
		std::string rest;
		std::getline(in, rest);
		size_t start = rest.find_first_not_of(" \t");
		return start == std::string::npos ? std::string() : rest.substr(start);
	}

	void RunScript(const std::string &path)
	{
		std::ifstream file(path);
		if (!file.is_open())
		{
			printf("[harness] cannot open script %s\n", path.c_str());
			g_failures++;
			return;
		}
		std::string line;
		int lineNumber = 0;
		while (std::getline(file, line))
		{
			lineNumber++;
			if (!line.empty() && line.back() == '\r')
				line.pop_back();
			std::istringstream in(line);
			std::string op;
			in >> op;
			if (op.empty() || op[0] == '#')
				continue;
			auto *root = Web::RmlUi::UiRoot::Get();
			if (op == "var")
			{
				std::string name;
				in >> name;
				Harness::g_variables[name] = Rest(in);
			}
			else if (op == "result")
			{
				std::string key;
				in >> key;
				Harness::g_methodResults[key] = Rest(in);
			}
			else if (op == "show")
			{
				std::string screen;
				in >> screen;
				std::string json = Rest(in);
				if (root) root->RequestScreen(screen, json.empty() ? "{}" : json);
			}
			else if (op == "hide")
			{
				std::string screen;
				in >> screen;
				if (root) root->HideScreen(screen);
			}
			else if (op == "notify")
			{
				std::string event;
				in >> event;
				std::string json = Rest(in);
				bool broadcast = true;
				const std::string suffix = " nobroadcast";
				if (json.size() >= suffix.size() && json.compare(json.size() - suffix.size(), suffix.size(), suffix) == 0)
				{
					broadcast = false;
					json.resize(json.size() - suffix.size());
				}
				if (root) root->Notify(event, json.empty() ? "{}" : json, broadcast);
			}
			else if (op == "notifyscreen")
			{
				std::string screen, event;
				in >> screen >> event;
				std::string json = Rest(in);
				if (root) root->NotifyScreen(screen, event, json.empty() ? "{}" : json);
			}
			else if (op == "controller")
			{
				if (root) root->SendControllerInput(Rest(in));
			}
			else if (op == "mouse" || op == "click" || op == "rclick")
			{
				int x = 0, y = 0;
				in >> x >> y;
				LPARAM lp = MAKELPARAM(x, y);
				PostInput(WM_MOUSEMOVE, 0, lp);
				if (op == "click")
				{
					PostInput(WM_LBUTTONDOWN, MK_LBUTTON, lp);
					PostInput(WM_LBUTTONUP, 0, lp);
				}
				else if (op == "rclick")
				{
					PostInput(WM_RBUTTONDOWN, MK_RBUTTON, lp);
					PostInput(WM_RBUTTONUP, 0, lp);
				}
			}
			else if (op == "wheel")
			{
				int delta = 0;
				in >> delta;
				PostInput(WM_MOUSEWHEEL, MAKEWPARAM(0, (short)delta), 0);
			}
			else if (op == "key")
			{
				int vk = 0;
				in >> vk;
				PostInput(WM_KEYDOWN, vk, 0);
				PostInput(WM_KEYUP, vk, 0);
			}
			else if (op == "char")
			{
				for (char c : Rest(in))
					PostInput(WM_CHAR, (unsigned char)c, 0);
			}
			else if (op == "wait")
			{
				double seconds = 0;
				in >> seconds;
				RunFor(seconds);
			}
			else if (op == "shot")
			{
				Frame();
				if (!Screenshot(Rest(in)))
					g_failures++;
			}
			else if (op == "lua")
			{
				std::string screen;
				in >> screen;
				if (root)
					printf("[lua %s] %s\n", screen.c_str(), root->EvalInScreen(screen, Rest(in)).c_str());
			}
			else if (op == "doc")
			{
				// load and show an arbitrary document (outside screens.json)
				auto *renderer = Web::Browser::WebRenderer::GetInstance().get();
				if (auto *context = renderer->GetContext())
				{
					if (auto *document = context->LoadDocument(Rest(in)))
						document->Show();
					else
						g_failures++;
				}
				renderer->ShowRenderer(true, true);
			}
			else if (op == "expect-call")
			{
				std::string needle = Rest(in);
				bool found = false;
				for (auto &call : Harness::g_calls)
					if (call.find(needle) != std::string::npos)
						found = true;
				if (!found)
				{
					printf("[harness] FAIL line %d: no bridge call contains \"%s\"\n", lineNumber, needle.c_str());
					g_failures++;
				}
			}
			else if (op == "expect-clean")
			{
				if (Harness::g_errors > 0)
				{
					printf("[harness] FAIL line %d: %d error(s) logged\n", lineNumber, Harness::g_errors);
					g_failures++;
				}
			}
			else
			{
				printf("[harness] unknown op \"%s\" on line %d\n", op.c_str(), lineNumber);
				g_failures++;
			}
		}
	}
}

int main(int argc, char **argv)
{
	if (argc < 3)
	{
		printf("usage: ui-harness <ui root dir> <script> [--verbose] [--size WxH]\n");
		return 2;
	}
	for (int i = 3; i < argc; i++)
	{
		std::string arg = argv[i];
		if (arg == "--verbose")
			Harness::g_verbose = true;
		else if (arg == "--size" && i + 1 < argc)
			sscanf_s(argv[++i], "%dx%d", &g_width, &g_height);
	}
	const std::string script = std::filesystem::absolute(argv[2]).string();
	std::filesystem::current_path(argv[1]);

	if (!CreateDevice())
		return 3;
	auto renderer = Web::Browser::WebRenderer::GetInstance();
	Web::Browser::WebRenderer::OverrideWindowResolution(g_width, g_height);
	if (!renderer->InitRenderer(g_device) || !renderer->Init("dew://ui/", true))
	{
		printf("[harness] UI host failed to start\n");
		return 4;
	}
	RunFor(0.2);
	// Screens not ported yet fail to load at startup; only count what the script causes.
	printf("[harness] startup: %d error(s), %d warning(s)\n", Harness::g_errors, Harness::g_warnings);
	Harness::g_errors = 0;
	Harness::g_warnings = 0;
	RunScript(script);
	RunFor(0.1);
	renderer->Shutdown();
	printf("[harness] done: %d error(s), %d warning(s), %d failure(s)\n", Harness::g_errors, Harness::g_warnings, g_failures);
	return g_failures > 0 ? 1 : 0;
}
