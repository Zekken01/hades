/* ---------- headers */

#include "Web/WebRenderer.hpp"
#include "hades/hades.h"

#include "Console/Console.hpp"
#include "ElDorito.hpp"
#include "Utils/Logger.hpp"
#include "Utils/Singleton.hpp"
#include "Web/Bridge/WebRendererQueryHandler.hpp"
#include "Web/Rml/AsyncTextures.hpp"
#include "Web/Rml/FileInterface.hpp"
#include "Web/Rml/Input.hpp"
#include "Web/Rml/LuaState.hpp"
#include "Web/Rml/RenderInterfaceD3D9.hpp"
#include "Web/Rml/ScreenDocument.hpp"
#include "Web/Rml/SystemInterface.hpp"
#include "Web/Rml/UiRoot.hpp"
#include "Web/Ui/Screen.hpp"

#include <RmlUi/Core.h>
#include <RmlUi/Debugger.h>
#include <RmlUi/Lua.h>

#include <Windows.h>

#include <algorithm>
#include <cctype>
#include <filesystem>

/* ---------- private code */

namespace
{
	void LogRenderer(Utils::LogLevel level, const std::string &message)
	{
		Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Graphics, level, "WebRenderer: " + message);
		if (level >= Utils::LogLevel::Warning)
			Console::WriteLine("WebRenderer: " + message);
	}

	int g_resolutionOverride[2] = { 0, 0 };

	void ReadWindowResolution(unsigned __int32 &width, unsigned __int32 &height)
	{
		// The game's window resolution global; tools outside the game (the UI harness) override it.
		auto *windowResolution = g_resolutionOverride[0] > 0 ? g_resolutionOverride : reinterpret_cast<int *>(0x19106E4);
		width = (unsigned __int32)std::max(windowResolution[0], 1);
		height = (unsigned __int32)std::max(windowResolution[1], 1);
	}
}

/* ---------- public code */

namespace Web
{
	namespace Browser
	{
		WebRenderer::WebRenderer()
		{
		}

		WebRenderer::~WebRenderer()
		{
			Shutdown();
		}

		std::shared_ptr<WebRenderer> WebRenderer::GetInstance()
		{
			static std::shared_ptr<WebRenderer> instance = std::make_shared<WebRenderer>();
			return instance;
		}

		void WebRenderer::OverrideWindowResolution(int width, int height)
		{
			g_resolutionOverride[0] = width;
			g_resolutionOverride[1] = height;
		}

		std::string WebRenderer::GetUIDirectory()
		{
			return (std::filesystem::current_path() / "ui").string();
		}

		double WebRenderer::Now() const
		{
			return m_SystemInterface ? m_SystemInterface->GetElapsedTime() : 0.0;
		}

		bool WebRenderer::InitRenderer(IDirect3DDevice9 *device)
		{
			if (!device || m_RmlInitialised)
				return m_RmlInitialised;
			m_RenderThread = GetCurrentThreadId();
			SetState(RendererState_Startup);

			m_RenderInterface = std::make_unique<Web::RmlUi::RenderInterfaceD3D9>(device);
			if (!m_RenderInterface->Initialize())
			{
				LogRenderer(Utils::LogLevel::Error, "D3D9 render interface failed to initialise");
				m_RenderInterface.reset();
				SetState(RendererState_Disabled);
				return false;
			}
			ReadWindowResolution(m_Width, m_Height);
			m_RenderInterface->SetViewport((int)m_Width, (int)m_Height);

			m_SystemInterface = std::make_unique<Web::RmlUi::SystemInterface>();
			const std::filesystem::path uiDirectory = GetUIDirectory();
			m_FileInterface = std::make_unique<Web::RmlUi::FileInterface>(uiDirectory, std::filesystem::current_path() / "data" / "cache" / "ui");
			m_AsyncTextures = std::make_unique<Web::RmlUi::AsyncTextures>(*m_RenderInterface, *m_FileInterface);
			m_RenderInterface->SetSourceHook([this](const std::string &source) { return m_AsyncTextures->Request(source); });
			m_RenderInterface->SetSlotReleasedHook([this](Web::RmlUi::TextureSlot *slot) { m_AsyncTextures->OnSlotReleased(slot); });

			::Rml::SetRenderInterface(m_RenderInterface.get());
			::Rml::SetSystemInterface(m_SystemInterface.get());
			::Rml::SetFileInterface(m_FileInterface.get());
			if (!::Rml::Initialise())
			{
				LogRenderer(Utils::LogLevel::Error, "Rml::Initialise failed");
				SetState(RendererState_Disabled);
				return false;
			}
			m_RmlInitialised = true;

			m_Lua = std::make_unique<Web::RmlUi::LuaState>();
			if (!m_Lua->Init())
			{
				LogRenderer(Utils::LogLevel::Error, "Lua state failed to initialise");
				SetState(RendererState_Disabled);
				return false;
			}
			::Rml::Lua::Initialise(m_Lua->L());
			// Our document class and attribute-handler instancer replace the Lua plugin's, so
			// every screen gets its own environment.
			auto *documentInstancer = new Web::RmlUi::ScreenDocumentInstancer();
			m_DocumentInstancer = documentInstancer;
			::Rml::Factory::RegisterElementInstancer("body", documentInstancer);
			m_ListenerInstancer = std::make_unique<Web::RmlUi::EnvEventListenerInstancer>();
			::Rml::Factory::RegisterEventListenerInstancer(m_ListenerInstancer.get());

			m_Context = ::Rml::CreateContext("ui", { (int)m_Width, (int)m_Height });
			if (!m_Context)
			{
				LogRenderer(Utils::LogLevel::Error, "Rml::CreateContext failed");
				SetState(RendererState_Disabled);
				return false;
			}
			LoadFonts();

			m_QueryHandler = std::make_unique<Bridge::WebRendererQueryHandler>();
			Bridge::RegisterClientFunctions(*m_QueryHandler);

			m_UiRoot = std::make_unique<Web::RmlUi::UiRoot>(*m_Lua, m_Context, *m_FileInterface, *m_AsyncTextures);
			m_UiRoot->OnResize((int)m_Width, (int)m_Height);
			return true;
		}

		void WebRenderer::LoadFonts()
		{
			// Every font under ui/lib and ui/fonts; the first one found is also the fallback face.
			bool first = true;
			std::error_code ec;
			for (const char *folder : { "lib", "fonts" })
			{
				const std::filesystem::path directory = std::filesystem::path(GetUIDirectory()) / folder;
				if (!std::filesystem::is_directory(directory, ec))
					continue;
				for (auto &entry : std::filesystem::directory_iterator(directory, ec))
				{
					std::string extension = entry.path().extension().string();
					for (auto &c : extension)
						c = (char)std::tolower((unsigned char)c);
					if (extension != ".ttf" && extension != ".otf" && extension != ".woff")
						continue;
					if (::Rml::LoadFontFace(entry.path().string(), first))
						first = false;
					else
						LogRenderer(Utils::LogLevel::Warning, "failed to load font " + entry.path().string());
				}
			}
			if (first)
				LogRenderer(Utils::LogLevel::Warning, "no fonts found under ui/lib or ui/fonts");
		}

		bool WebRenderer::Init(std::string const &, bool debugEnable)
		{
			if (!m_UiRoot)
				return false;
			m_Debugging = debugEnable;
			if (!m_UiRoot->Init(GetUIDirectory(), debugEnable))
			{
				LogRenderer(Utils::LogLevel::Error, "UI failed to initialise; see the log for the missing files");
				SetState(RendererState_Hidden);
				return false;
			}
			SetState(RendererState_Overlay);
			return true;
		}

		bool WebRenderer::Render(IDirect3DDevice9 *)
		{
			if (!Initialized() || !m_RenderInterface)
				return false;
			m_UiRoot->Update(Now());
			m_RenderInterface->BeginFrame();
			m_Context->Render();
			m_RenderInterface->EndFrame();
			return true;
		}

		bool WebRenderer::Update()
		{
			// The render path drives the UI while it is drawing; keep it alive when hidden so
			// screens finish loading and queued events are delivered.
			if (!Initialized())
				return false;
			if (!IsRendering() && GetCurrentThreadId() == m_RenderThread)
				m_UiRoot->Update(Now());
			return true;
		}

		bool WebRenderer::Initialized()
		{
			return m_RmlInitialised && m_Context && m_UiRoot;
		}

		bool WebRenderer::IsRendering()
		{
			const RendererState state = GetState();
			return state == RendererState_Overlay || state == RendererState_Shown;
		}

		bool WebRenderer::ShowRenderer(bool show, bool overlay)
		{
			if (!Initialized())
				return false;
			if (!show)
			{
				SetState(RendererState_Hidden);
				Web::RmlUi::Input::Clear();
			}
			else
				SetState(overlay ? RendererState_Overlay : RendererState_Shown);
			return true;
		}

		bool WebRenderer::Resize(unsigned __int32 width, unsigned __int32 height)
		{
			if (!m_RenderInterface)
				return false;
			m_Width = std::max<unsigned __int32>(width, 1);
			m_Height = std::max<unsigned __int32>(height, 1);
			m_RenderInterface->SetViewport((int)m_Width, (int)m_Height);
			if (m_UiRoot)
				m_UiRoot->OnResize((int)m_Width, (int)m_Height);
			return true;
		}

		bool WebRenderer::Reload()
		{
			if (!m_UiRoot)
				return false;
			m_UiRoot->ReloadAll();
			return true;
		}

		void WebRenderer::ToggleDebugger()
		{
			if (m_UiRoot)
				m_UiRoot->ToggleDebugger();
		}

		bool WebRenderer::PreReset()
		{
			if (!m_RmlInitialised || !m_RenderInterface)
				return false;
			// RmlUi recreates geometry and textures lazily through the render interface.
			::Rml::ReleaseCompiledGeometry();
			::Rml::ReleaseTextures();
			m_RenderInterface->OnPreReset();
			return true;
		}

		bool WebRenderer::PostReset()
		{
			if (!m_RmlInitialised || !m_RenderInterface)
				return false;
			m_RenderInterface->OnPostReset();
			unsigned __int32 width, height;
			ReadWindowResolution(width, height);
			Resize(width, height);
			return true;
		}

		bool WebRenderer::Shutdown()
		{
			if (!m_RmlInitialised && !m_RenderInterface)
				return false;
			SetState(RendererState_Shutdown);
			if (m_UiRoot)
				m_UiRoot->Shutdown();
			m_UiRoot.reset();
			if (m_AsyncTextures)
				m_AsyncTextures->CancelAll();
			if (m_RmlInitialised)
			{
				::Rml::Debugger::Shutdown();
				::Rml::Shutdown();
				m_RmlInitialised = false;
			}
			m_Context = nullptr;
			if (m_Lua)
				m_Lua->Shutdown(); // after Rml::Shutdown, as the Lua plugin requires
			m_Lua.reset();
			delete static_cast<Web::RmlUi::ScreenDocumentInstancer *>(m_DocumentInstancer);
			m_DocumentInstancer = nullptr;
			m_ListenerInstancer.reset();
			m_QueryHandler.reset();
			m_AsyncTextures.reset();
			m_RenderInterface.reset();
			m_FileInterface.reset();
			m_SystemInterface.reset();
			return true;
		}

		RendererState WebRenderer::GetState()
		{
			return m_State;
		}

		bool WebRenderer::SetState(RendererState p_State)
		{
			if (p_State >= RendererState_Count)
				return false;
			m_State = p_State;
			return true;
		}
	}
}
