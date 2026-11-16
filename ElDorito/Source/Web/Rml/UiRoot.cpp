/* ---------- headers */

#include "hades/hades.h"

#include "Web/Rml/UiRoot.hpp"

#include "CommandMap.hpp"
#include "Console/Console.hpp"
#include "ElDorito.hpp"
#include "ThirdParty/rapidjson/document.h"
#include "ThirdParty/rapidjson/stringbuffer.h"
#include "ThirdParty/rapidjson/writer.h"
#include "Utils/Logger.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"
#include "Web/Rml/AsyncTextures.hpp"
#include "Web/Rml/FileInterface.hpp"
#include "Web/Rml/Input.hpp"
#include "Web/Rml/LuaJson.hpp"
#include "Web/Rml/LuaState.hpp"
#include "Web/Rml/ScreenDocument.hpp"
#include "Web/Ui/Screen.hpp"
#include "Web/Ui/ScreenLayer.hpp"
#include "Web/WebRenderer.hpp"

#include <RmlUi/Core/Context.h>
#include <RmlUi/Core/Core.h>
#include <RmlUi/Core/ElementDocument.h>
#include <RmlUi/Core/Elements/ElementFormControlInput.h>
#include <RmlUi/Lua/LuaType.h>
#include <RmlUi/Core/Factory.h>
#include <RmlUi/Debugger/Debugger.h>

#include <Windows.h>
#include <psapi.h>
#include <shellapi.h>
#include <mmdeviceapi.h>
#include <functiondiscoverykeys_devpkey.h>

#include <algorithm>
#include <fstream>

/* ---------- private code */

namespace
{
	const char kToastScreenId[] = "toast";

	void LogUi(Utils::LogLevel level, const std::string &message)
	{
		Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Graphics, level, "[ui] " + message);
		if (level >= Utils::LogLevel::Warning)
			Console::WriteLine("[ui] " + message);
	}

	// Lua helpers for the dew_core functions
	std::string CheckString(lua_State *L, int index, const char *fallback = "")
	{
		size_t length = 0;
		const char *text = lua_tolstring(L, index, &length);
		return text ? std::string(text, length) : std::string(fallback);
	}

	// JSON text for the table/value at `index` ({} when nil).
	std::string ArgJson(lua_State *L, int index)
	{
		if (lua_isnoneornil(L, index))
			return "{}";
		return Web::RmlUi::LuaJson::Stringify(L, index);
	}

	Web::Browser::Bridge::WebRendererQueryHandler *QueryHandler()
	{
		auto renderer = Web::Browser::WebRenderer::GetInstance();
		return renderer ? renderer->GetQueryHandler() : nullptr;
	}
}

namespace Web
{
	namespace RmlUi
	{
		UiRoot *UiRoot::s_instance = nullptr;

		UiRoot::UiRoot(LuaState &lua, ::Rml::Context *context, FileInterface &files, AsyncTextures &textures)
			: m_lua(lua), m_context(context), m_files(files), m_textures(textures), m_timers(lua), m_http(lua)
		{
			s_instance = this;
			ScreenDocument::SetEnvCreatedHook([this](ScreenDocument &document, int envRef) { OnEnvCreated(document, envRef); });
			ScreenDocument::SetEnvReleasedHook([this](ScreenDocument &document, int envRef) { OnEnvReleased(document, envRef); });
		}

		UiRoot::~UiRoot()
		{
			Shutdown();
			ScreenDocument::SetEnvCreatedHook(nullptr);
			ScreenDocument::SetEnvReleasedHook(nullptr);
			if (s_instance == this)
				s_instance = nullptr;
		}

		/* lifecycle */

		bool UiRoot::Init(const std::filesystem::path &uiDirectory, bool debugging)
		{
			m_uiDirectory = uiDirectory;
			m_debugging = debugging;
			RegisterDewCore();
			LoadStorage();
			if (!LoadDewLibrary())
				LogUi(Utils::LogLevel::Warning, "ui/lib/dew.lua is missing; screens will have no `dew` table");

			// screens/screens.json: the same file the web UI read
			std::string json;
			if (!m_files.ReadAll("dew://screens/screens.json", json))
			{
				LogUi(Utils::LogLevel::Error, "cannot read dew://screens/screens.json");
				return false;
			}
			rapidjson::Document document;
			document.Parse(json.c_str(), json.size());
			if (document.HasParseError() || !document.IsObject() || !document.HasMember("screens") || !document["screens"].IsArray())
			{
				LogUi(Utils::LogLevel::Error, "screens.json is not valid");
				return false;
			}
			for (auto &entry : document["screens"].GetArray())
			{
				if (!entry.IsObject() || !entry.HasMember("id") || !entry["id"].IsString())
					continue;
				auto str = [&](const char *key) { return entry.HasMember(key) && entry[key].IsString() ? std::string(entry[key].GetString()) : std::string(); };
				const bool capture = entry.HasMember("captureInput") && entry["captureInput"].IsBool() && entry["captureInput"].GetBool();
				const int zIndex = entry.HasMember("zIndex") && entry["zIndex"].IsNumber() ? entry["zIndex"].GetInt() : 0;
				CreateScreen(str("id"), str("url"), str("var"), str("fallbackUrl"), capture, zIndex, false);
			}
			// The toast layer replaces the #toast_container of the old root page.
			CreateScreen(kToastScreenId, "dew://ui/toast.rml", "", "", false, 1000, true);
			std::stable_sort(m_screens.begin(), m_screens.end(), [](const std::unique_ptr<Screen> &a, const std::unique_ptr<Screen> &b) { return a->zIndex < b->zIndex; });

			for (auto &screen : m_screens)
				LoadScreen(*screen);
			if (Screen *toast = FindScreen(kToastScreenId))
				ShowScreen(*toast, true);

			// The debugger (F7) is created on first use: once initialised it shows a warning
			// beacon over the game whenever anything logs a warning.
			m_ready = true;
			return true;
		}

		void UiRoot::Shutdown()
		{
			if (!m_context && m_screens.empty())
				return;
			m_ready = false;
			m_timers.ClearAll();
			m_http.CancelAll();
			{
				std::lock_guard<std::mutex> lock(m_gameTaskMutex);
				m_gameTasks.clear();
			}
			{
				std::lock_guard<std::mutex> lock(m_uiTaskMutex);
				m_uiTasks.clear();
			}
			m_lua.ClearDeferred();
			for (auto &screen : m_screens)
				UnloadScreen(*screen);
			if (m_context)
				m_context->Update(); // documents are destroyed on the next update
			m_screens.clear();
			if (m_debuggerInitialised)
			{
				::Rml::Debugger::Shutdown();
				m_debuggerInitialised = false;
			}
			m_lua.Unref(m_dewFactoryRef);
			SaveStorage();
			m_context = nullptr;
		}

		void UiRoot::Update(double now)
		{
			if (!m_context)
				return;
			m_now = now;
			ProcessCommands();
			RunUiTasks();
			Input::Drain(m_context);
			m_textures.Pump();
			m_http.Pump(now);
			m_timers.Tick(now);
			m_lua.RunDeferred();
			if (m_reloadPending)
			{
				m_reloadPending = false;
				::Rml::Factory::ClearStyleSheetCache();
				::Rml::Factory::ClearTemplateCache();
				::Rml::ReleaseTextures();
				for (auto &screen : m_screens)
					LoadScreen(*screen);
				if (Screen *toast = FindScreen(kToastScreenId))
					ShowScreen(*toast, true);
			}
			// Screens asked for before they finished loading (ui.js's 5 s watchdog).
			for (auto &screen : m_screens)
			{
				if (screen->state == ScreenState::Waiting && !screen->loaded && now - screen->loadStartTime > 5.0)
				{
					LogUi(Utils::LogLevel::Warning, "screen \"" + screen->id + "\" took longer than 5 seconds to load; reloading");
					LoadScreen(*screen);
				}
			}
			m_context->Update();
			m_lua.CollectGarbageStep();
		}

		void UiRoot::OnResize(int width, int height)
		{
			if (!m_context)
				return;
			m_context->SetDimensions({ std::max(width, 1), std::max(height, 1) });
			// The web UI scaled every page by min(w/1280, h/720); dp units do the same here.
			const float ratio = std::min(width / 1280.f, height / 720.f);
			m_context->SetDensityIndependentPixelRatio(ratio > 0.f ? ratio : 1.f);
		}

		void UiRoot::ReloadAll()
		{
			for (auto &screen : m_screens)
			{
				const bool wasVisible = screen->state == ScreenState::Visible || screen->state == ScreenState::Waiting;
				UnloadScreen(*screen);
				if (wasVisible && !screen->overlayOnly)
					SetState(*screen, ScreenState::Waiting);
			}
			m_timers.ClearAll();
			m_http.CancelAll();
			m_lua.ClearDeferred();
			m_reloadPending = true; // documents are destroyed on the next Context::Update
			UpdateOverlay();
		}

		void UiRoot::ToggleDebugger()
		{
			if (!m_debuggerInitialised && m_context)
				m_debuggerInitialised = ::Rml::Debugger::Initialise(m_context);
			if (m_debuggerInitialised)
				::Rml::Debugger::SetVisible(!::Rml::Debugger::IsVisible());
			UpdateOverlay();
		}

		bool UiRoot::IsDebuggerVisible() const
		{
			return m_debuggerInitialised && ::Rml::Debugger::IsVisible();
		}

		/* C++ -> UI (queued) */

		void UiRoot::RequestScreen(const std::string &screenId, const std::string &dataJson)
		{
			std::lock_guard<std::mutex> lock(m_commandMutex);
			m_commands.push_back({ Command::Type::Request, screenId, "", dataJson.empty() ? "{}" : dataJson, false });
		}

		void UiRoot::HideScreen(const std::string &screenId)
		{
			std::lock_guard<std::mutex> lock(m_commandMutex);
			m_commands.push_back({ Command::Type::Hide, screenId, "", "", false });
		}

		void UiRoot::Notify(const std::string &event, const std::string &dataJson, bool broadcast)
		{
			std::lock_guard<std::mutex> lock(m_commandMutex);
			m_commands.push_back({ Command::Type::Notify, "", event, dataJson.empty() ? "{}" : dataJson, broadcast });
		}

		void UiRoot::NotifyScreen(const std::string &screenId, const std::string &event, const std::string &dataJson)
		{
			std::lock_guard<std::mutex> lock(m_commandMutex);
			m_commands.push_back({ Command::Type::NotifyScreen, screenId, event, dataJson.empty() ? "{}" : dataJson, false });
		}

		void UiRoot::SendControllerInput(const std::string &inputJson)
		{
			std::lock_guard<std::mutex> lock(m_commandMutex);
			// Controller ticks arrive every UI tick; keep only the newest one pending.
			for (auto it = m_commands.begin(); it != m_commands.end();)
			{
				if (it->type == Command::Type::ControllerInput)
					it = m_commands.erase(it);
				else
					++it;
			}
			m_commands.push_back({ Command::Type::ControllerInput, "", "controllerinput", inputJson, false });
		}

		void UiRoot::ProcessCommands()
		{
			std::deque<Command> commands;
			{
				std::lock_guard<std::mutex> lock(m_commandMutex);
				commands.swap(m_commands);
			}
			for (auto &command : commands)
			{
				switch (command.type)
				{
				case Command::Type::Request:
				{
					Screen *screen = FindScreen(command.screenId);
					if (!screen)
					{
						LogUi(Utils::LogLevel::Error, "requested to show screen \"" + command.screenId + "\", but it isn't defined");
						break;
					}
					screen->pendingData = command.json;
					if (screen->loaded)
						ShowScreen(*screen, true);
					else
					{
						SetState(*screen, ScreenState::Waiting);
						if (!screen->document)
							LoadScreen(*screen);
					}
					break;
				}
				case Command::Type::Hide:
				{
					Screen *screen = FindScreen(command.screenId);
					if (!screen)
					{
						LogUi(Utils::LogLevel::Error, "requested to hide screen \"" + command.screenId + "\", but it isn't defined");
						break;
					}
					ShowScreen(*screen, false);
					break;
				}
				case Command::Type::Notify:
					DeliverEventToSubscribed(command.event, command.json, command.broadcast);
					break;
				case Command::Type::NotifyScreen:
					if (Screen *screen = FindScreen(command.screenId))
						DeliverEvent(*screen, command.event, command.json);
					break;
				case Command::Type::ControllerInput:
				{
					Screen *topmost = nullptr;
					for (auto &screen : m_screens)
						if (screen->state == ScreenState::Visible && screen->captureInput && (!topmost || screen->zIndex > topmost->zIndex))
							topmost = screen.get();
					if (topmost)
						DeliverEvent(*topmost, "controllerinput", command.json);
					break;
				}
				}
			}
		}

		std::string UiRoot::EvalInScreen(const std::string &screenId, const std::string &code)
		{
			Screen *screen = FindScreen(screenId);
			if (!screen || screen->envRef <= 0)
				return "<no such screen>";
			lua_State *L = m_lua.L();
			const int top = lua_gettop(L);
			std::string chunk = "return " + code;
			if (luaL_loadbufferx(L, chunk.c_str(), chunk.size(), "=eval", "t") != LUA_OK)
			{
				lua_pop(L, 1);
				chunk = code;
				if (luaL_loadbufferx(L, chunk.c_str(), chunk.size(), "=eval", "t") != LUA_OK)
				{
					std::string error = lua_tostring(L, -1);
					lua_settop(L, top);
					return "<compile error> " + error;
				}
			}
			m_lua.PushEnv(screen->envRef);
			lua_setupvalue(L, -2, 1);
			std::string result;
			if (lua_pcall(L, 0, 1, 0) != LUA_OK)
				result = std::string("<error> ") + lua_tostring(L, -1);
			else
				result = luaL_tolstring(L, -1, nullptr);
			lua_settop(L, top);
			return result;
		}

		/* screens */

		void UiRoot::CreateScreen(const std::string &id, const std::string &url, const std::string &variable, const std::string &fallbackUrl, bool captureInput, int zIndex, bool overlayOnly)
		{
			if (FindScreen(id))
				return;
			auto screen = std::make_unique<Screen>();
			screen->id = id;
			screen->url = url;
			screen->variable = variable;
			screen->fallbackUrl = fallbackUrl;
			screen->captureInput = captureInput;
			screen->zIndex = zIndex;
			screen->overlayOnly = overlayOnly;
			m_screens.push_back(std::move(screen));
		}

		std::string UiRoot::ResolveScreenUrl(const Screen &screen) const
		{
			std::string url = screen.url;
			if (!screen.variable.empty())
			{
				std::string value;
				if (Modules::CommandMap::Instance().GetVariableString(screen.variable, value) && !value.empty())
					url = value;
			}
			auto fixup = [](std::string candidate) {
				// Configs may still point at the web pages.
				if (candidate.size() > 5 && candidate.compare(candidate.size() - 5, 5, ".html") == 0)
					candidate.replace(candidate.size() - 5, 5, ".rml");
				return candidate;
			};
			FileInterface::Resolved resolved;
			if (!url.empty() && m_files.Resolve(fixup(url), resolved))
				return fixup(url);
			if (!screen.fallbackUrl.empty())
			{
				if (!url.empty())
					LogUi(Utils::LogLevel::Warning, "failed to access " + url + " - trying fallback");
				return fixup(screen.fallbackUrl);
			}
			return fixup(url);
		}

		void UiRoot::LoadScreen(Screen &screen)
		{
			if (!m_context)
				return;
			UnloadScreen(screen);
			screen.loadStartTime = m_now;
			const std::string url = ResolveScreenUrl(screen);
			if (url.empty())
				return; // no url yet (cvar empty): stays hidden until requested again
			ScreenDocument::SetNextScreenId(screen.id);
			::Rml::ElementDocument *document = m_context->LoadDocument(url);
			ScreenDocument::SetNextScreenId("");
			if (!document)
			{
				LogUi(Utils::LogLevel::Error, "failed to load screen \"" + screen.id + "\" from " + url);
				return;
			}
			screen.document = rmlui_dynamic_cast<ScreenDocument *>(document);
			if (!screen.document)
			{
				LogUi(Utils::LogLevel::Error, "screen \"" + screen.id + "\" did not produce a ScreenDocument (is the Lua plugin registered?)");
				m_context->UnloadDocument(document);
				return;
			}
			// (no SetId: screens use their own ids, e.g. the dialog screen has an element "dialog")
			// Documents with a numeric z-index stack by value under the context root.
			document->SetProperty("z-index", std::to_string(screen.zIndex));
			screen.envRef = screen.document->GetEnvRef();
			screen.loaded = true;
			if (screen.state == ScreenState::Waiting)
				ShowScreen(screen, true);
		}

		void UiRoot::UnloadScreen(Screen &screen)
		{
			screen.loaded = false;
			if (screen.document && m_context)
			{
				if (screen.state != ScreenState::Hidden)
					screen.document->Hide();
				m_context->UnloadDocument(screen.document);
			}
			// The environment hook clears handlers/timers when the document is destroyed, but
			// the document lives until the next Context::Update; detach now.
			if (screen.envRef > 0)
			{
				m_timers.ClearOwner(screen.envRef);
				m_http.CancelOwner(screen.envRef);
			}
			for (auto &handlers : screen.handlers)
				for (int &ref : handlers.second)
					m_lua.Unref(ref);
			screen.handlers.clear();
			screen.document = nullptr;
			screen.envRef = 0;
		}

		void UiRoot::SetState(Screen &screen, ScreenState state)
		{
			screen.state = state;
			if (!screen.overlayOnly)
			{
				// OnShow/OnHide are game code: run them on the game thread.
				PostToGameThread([id = screen.id, state]() {
					Web::Ui::ScreenLayer::NotifyScreenStateChanged(id, (Web::Ui::ScreenLayer::EScreenState)state);
				});
			}
		}

		void UiRoot::ShowScreen(Screen &screen, bool show)
		{
			if (!screen.document)
			{
				if (show)
					SetState(screen, ScreenState::Waiting);
				return;
			}
			if (show)
			{
				SetState(screen, ScreenState::Visible);
				screen.document->Show(::Rml::ModalFlag::None, (screen.captureInput || screen.capturePointer) ? ::Rml::FocusFlag::Document : ::Rml::FocusFlag::None);
				std::string data = screen.pendingData.empty() ? "{}" : screen.pendingData;
				screen.pendingData.clear();
				DeliverEvent(screen, "show", data);
			}
			else if (screen.state == ScreenState::Waiting || screen.state == ScreenState::Visible)
			{
				SetState(screen, ScreenState::Hidden);
				screen.document->Hide();
				DeliverEvent(screen, "hide", "{}");
			}
			UpdateOverlay();
		}

		void UiRoot::UpdateOverlay()
		{
			int visible = 0;
			bool capture = false;
			bool capturePointer = false;
			Screen *topmost = nullptr;
			for (auto &screen : m_screens)
			{
				if (screen->state != ScreenState::Visible || screen->overlayOnly)
					continue;
				visible++;
				if (screen->capturePointer)
					capturePointer = true;
				if (screen->captureInput)
					capture = true;
				if ((screen->captureInput || screen->capturePointer) && (!topmost || screen->zIndex > topmost->zIndex))
					topmost = screen.get();
			}
			if (IsDebuggerVisible())
			{
				visible++;
				capture = true;
				capturePointer = true;
			}
			const bool overlayVisible = visible > 0 || m_toastActive;
			const bool showChanged = overlayVisible != m_lastOverlayVisible;
			m_lastOverlayVisible = overlayVisible;
			// CaptureInput pushes game input contexts: game thread only.
			PostToGameThread([showChanged, overlayVisible, capture, capturePointer]() {
				if (showChanged)
					Web::Ui::ScreenLayer::Show(overlayVisible);
				Web::Ui::ScreenLayer::CaptureInput(capture, capturePointer);
			});
			// ui.js focused the topmost capturing iframe, which keeps the element focused inside
			// it; only move focus when it is not already in that document.
			if (topmost && topmost->document && !IsDebuggerVisible())
			{
				::Rml::Element *focused = m_context->GetFocusElement();
				if (!focused || focused->GetOwnerDocument() != topmost->document)
					topmost->document->Focus();
			}
		}

		UiRoot::Screen *UiRoot::FindScreen(const std::string &id)
		{
			for (auto &screen : m_screens)
				if (screen->id == id)
					return screen.get();
			return nullptr;
		}

		UiRoot::Screen *UiRoot::FindScreenByEnv(int envRef)
		{
			if (envRef <= 0)
				return nullptr;
			for (auto &screen : m_screens)
				if (screen->envRef == envRef)
					return screen.get();
			return nullptr;
		}

		UiRoot::Screen *UiRoot::FindScreenByDocument(ScreenDocument *document)
		{
			for (auto &screen : m_screens)
				if (screen->document == document)
					return screen.get();
			return nullptr;
		}

		/* events */

		void UiRoot::DeliverEvent(Screen &screen, const std::string &event, const std::string &dataJson)
		{
			if (!screen.loaded)
				return;
			auto it = screen.handlers.find(event);
			if (it == screen.handlers.end() || it->second.empty())
				return;
			lua_State *L = m_lua.L();
			const int top = lua_gettop(L);
			LuaJson::PushParsed(L, dataJson);
			const int dataRef = m_lua.Ref(-1);
			lua_settop(L, top);
			DeliverEventTable(screen, event, dataRef);
			int ref = dataRef;
			m_lua.Unref(ref);
		}

		void UiRoot::DeliverEventTable(Screen &screen, const std::string &event, int dataRef)
		{
			auto it = screen.handlers.find(event);
			if (it == screen.handlers.end())
				return;
			// Handlers may subscribe/unsubscribe while running.
			std::vector<int> handlers = it->second;
			lua_State *L = m_lua.L();
			for (int handlerRef : handlers)
			{
				const int top = lua_gettop(L);
				m_lua.PushRef(handlerRef);
				if (lua_isfunction(L, -1))
				{
					// The web handlers received the whole message: {event, screen, data}.
					lua_createtable(L, 0, 3);
					lua_pushstring(L, event.c_str());
					lua_setfield(L, -2, "event");
					lua_pushstring(L, screen.id.c_str());
					lua_setfield(L, -2, "screen");
					m_lua.PushRef(dataRef);
					lua_setfield(L, -2, "data");
					m_lua.PCall(1, 0);
				}
				lua_settop(L, top);
			}
		}

		void UiRoot::DeliverEventToSubscribed(const std::string &event, const std::string &dataJson, bool broadcast)
		{
			lua_State *L = m_lua.L();
			int dataRef = 0;
			for (auto &screen : m_screens)
			{
				if (!broadcast && screen->state != ScreenState::Visible)
					continue;
				if (!screen->loaded)
					continue;
				auto it = screen->handlers.find(event);
				if (it == screen->handlers.end() || it->second.empty())
					continue;
				if (dataRef == 0)
				{
					const int top = lua_gettop(L);
					LuaJson::PushParsed(L, dataJson);
					dataRef = m_lua.Ref(-1);
					lua_settop(L, top);
				}
				DeliverEventTable(*screen, event, dataRef);
			}
			if (dataRef)
				m_lua.Unref(dataRef);
		}

		/* Lua environments */

		bool UiRoot::LoadDewLibrary()
		{
			std::string code;
			if (!m_files.ReadAll("dew://lib/dew.lua", code))
				return false;
			lua_State *L = m_lua.L();
			const int top = lua_gettop(L);
			bool ok = m_lua.LoadChunk(code.c_str(), code.size(), "@dew://lib/dew.lua", 0) && m_lua.PCall(0, 1) && lua_isfunction(L, -1);
			if (ok)
				m_dewFactoryRef = m_lua.Ref(-1);
			else
				LogUi(Utils::LogLevel::Error, "dew://lib/dew.lua must return a function(screenId, document)");
			lua_settop(L, top);
			return ok;
		}

		void UiRoot::OnEnvCreated(ScreenDocument &document, int envRef)
		{
			lua_State *L = m_lua.L();
			if (Screen *screen = FindScreenByDocument(&document))
				screen->envRef = envRef;
			else if (Screen *byId = FindScreen(document.GetScreenId()))
				byId->envRef = envRef; // called from inside LoadDocument, before screen.document is set
			if (m_dewFactoryRef <= 0)
				return;
			const int top = lua_gettop(L);
			m_lua.PushRef(m_dewFactoryRef);
			lua_pushstring(L, document.GetScreenId().c_str());
			::Rml::Lua::LuaType<::Rml::ElementDocument>::push(L, &document, false);
			if (m_lua.PCall(2, 1) && lua_istable(L, -1))
			{
				m_lua.PushEnv(envRef);
				lua_pushvalue(L, -2);
				lua_setfield(L, -2, "dew");
			}
			lua_settop(L, top);
		}

		void UiRoot::OnEnvReleased(ScreenDocument &, int envRef)
		{
			m_timers.ClearOwner(envRef);
			m_http.CancelOwner(envRef);
			if (Screen *screen = FindScreenByEnv(envRef))
			{
				for (auto &handlers : screen->handlers)
					for (int &ref : handlers.second)
						m_lua.Unref(ref);
				screen->handlers.clear();
				screen->envRef = 0;
			}
		}

		/* storage (localStorage replacement, data/ui/storage.json) */

		void UiRoot::LoadStorage()
		{
			m_storageLoaded = true;
			std::ifstream in("data/ui/storage.json", std::ios::binary);
			if (!in.is_open())
				return;
			std::string json((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
			rapidjson::Document document;
			document.Parse(json.c_str(), json.size());
			if (document.HasParseError() || !document.IsObject())
				return;
			for (auto it = document.MemberBegin(); it != document.MemberEnd(); ++it)
				if (it->value.IsString())
					m_storage[it->name.GetString()] = it->value.GetString();
		}

		void UiRoot::SaveStorage()
		{
			if (!m_storageLoaded)
				return;
			std::error_code ec;
			std::filesystem::create_directories("data/ui", ec);
			rapidjson::StringBuffer buffer;
			rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
			writer.StartObject();
			for (auto &entry : m_storage)
			{
				writer.Key(entry.first.c_str());
				writer.String(entry.second.c_str());
			}
			writer.EndObject();
			std::ofstream out("data/ui/storage.json", std::ios::binary | std::ios::trunc);
			out << buffer.GetString();
		}

		/* dew_core */

		void UiRoot::RegisterDewCore()
		{
			lua_State *L = m_lua.L();
			const luaL_Reg functions[] = {
				{ "callMethod", L_callMethod },
				{ "callMethodSync", L_callMethodSync },
				{ "on", L_on },
				{ "off", L_off },
				{ "show", L_show },
				{ "hide", L_hide },
				{ "notify", L_notify },
				{ "notifyScreen", L_notifyScreen },
				{ "captureInput", L_captureInput },
				{ "capturePointer", L_capturePointer },
				{ "toast", L_toast },
				{ "setTimer", L_setTimer },
				{ "clearTimer", L_clearTimer },
				{ "onFrame", L_onFrame },
				{ "http", L_http },
				{ "httpCancel", L_httpCancel },
				{ "fetchImage", L_fetchImage },
				{ "openUrl", L_openUrl },
				{ "log", L_log },
				{ "readFile", L_readFile },
				{ "fileExists", L_fileExists },
				{ "storageGet", L_storageGet },
				{ "storageSet", L_storageSet },
				{ "getMemoryStats", L_getMemoryStats },
				{ "enumerateAudioInputs", L_enumerateAudioInputs },
				{ "isDebugging", L_isDebugging },
				{ "getScreenState", L_getScreenState },
				{ "setToastActive", L_setToastActive },
				{ "getTime", L_getTime },
				{ "setSelectionRange", L_setSelectionRange },
				{ nullptr, nullptr },
			};
			luaL_newlib(L, functions);
			lua_setglobal(L, "dew_core");
		}

		// dew_core.callMethod(screenId, method, args, onSuccess, onFailure)
		// The method runs now; the callbacks run on the next Update, like the old promise.
		int UiRoot::L_callMethod(lua_State *L)
		{
			UiRoot *self = Get();
			const std::string method = CheckString(L, 2);
			const std::string argsJson = ArgJson(L, 3);
			const int onSuccess = lua_isfunction(L, 4) ? self->m_lua.Ref(4) : 0;
			const int onFailure = lua_isfunction(L, 5) ? self->m_lua.Ref(5) : 0;
			// The handlers are game code (the CEF bridge ran them from ScreenLayer::Tick):
			// invoke on the game thread, deliver the callbacks back on the UI thread.
			self->PostToGameThread([method, argsJson, onSuccess, onFailure]() {
				std::string result;
				Web::Browser::Bridge::QueryError error = Web::Browser::Bridge::QueryError_NotAvailable;
				if (auto *handler = QueryHandler())
				{
					rapidjson::Document args;
					args.Parse(argsJson.c_str(), argsJson.size());
					if (args.HasParseError() || !args.IsObject())
					{
						error = Web::Browser::Bridge::QueryError_BadQuery;
						result = "Bad query: \"args\" must be an object";
					}
					else
						error = handler->Invoke(method, args, &result);
				}
				else
					result = "Unsupported method: the bridge is not available";
				if (auto *root = Get())
					root->PostToUiThread([error, result, onSuccess, onFailure, method]() {
						if (auto *self = Get())
							self->DeliverMethodResult(error, result, onSuccess, onFailure, method);
					});
			});
			return 0;
		}

		void UiRoot::DeliverMethodResult(int error_, const std::string &result, int onSuccess, int onFailure, const std::string &method)
		{
			const auto error = (Web::Browser::Bridge::QueryError)error_;
			m_lua.Defer([error, result, onSuccess, onFailure, method](lua_State *L) {
				auto *self = Get();
				if (!self)
					return;
				int ok = onSuccess, fail = onFailure;
				if (error == Web::Browser::Bridge::QueryError_Ok)
				{
					self->m_lua.PushRef(ok);
					if (lua_isfunction(L, -1))
					{
						lua_pushlstring(L, result.data(), result.size());
						self->m_lua.PCall(1, 0);
					}
				}
				else
				{
					self->m_lua.PushRef(fail);
					if (lua_isfunction(L, -1))
					{
						lua_pushlstring(L, result.data(), result.size());
						lua_pushinteger(L, (lua_Integer)error);
						lua_pushstring(L, method.c_str());
						self->m_lua.PCall(3, 0);
					}
					else
						LogUi(Utils::LogLevel::Warning, "unhandled bridge error in \"" + method + "\": " + result);
				}
				self->m_lua.Unref(ok);
				self->m_lua.Unref(fail);
			});
		}

		void UiRoot::PostToGameThread(std::function<void()> task)
		{
			std::lock_guard<std::mutex> lock(m_gameTaskMutex);
			m_gameTasks.push_back(std::move(task));
		}

		void UiRoot::PostToUiThread(std::function<void()> task)
		{
			std::lock_guard<std::mutex> lock(m_uiTaskMutex);
			m_uiTasks.push_back(std::move(task));
		}

		void UiRoot::PumpGameThread()
		{
			std::deque<std::function<void()>> tasks;
			{
				std::lock_guard<std::mutex> lock(m_gameTaskMutex);
				tasks.swap(m_gameTasks);
			}
			for (auto &task : tasks)
				task();
		}

		void UiRoot::RunUiTasks()
		{
			std::deque<std::function<void()>> tasks;
			{
				std::lock_guard<std::mutex> lock(m_uiTaskMutex);
				tasks.swap(m_uiTasks);
			}
			for (auto &task : tasks)
				task();
		}

		// ok, resultOrError, code = dew_core.callMethodSync(screenId, method, args)
		// Runs the handler on the calling (UI) thread; only for handlers that do not touch
		// game state.  Screens use the asynchronous callMethod.
		int UiRoot::L_callMethodSync(lua_State *L)
		{
			const std::string method = CheckString(L, 2);
			const std::string argsJson = ArgJson(L, 3);
			std::string result;
			Web::Browser::Bridge::QueryError error = Web::Browser::Bridge::QueryError_NotAvailable;
			if (auto *handler = QueryHandler())
			{
				rapidjson::Document args;
				args.Parse(argsJson.c_str(), argsJson.size());
				if (args.HasParseError() || !args.IsObject())
				{
					error = Web::Browser::Bridge::QueryError_BadQuery;
					result = "Bad query: \"args\" must be an object";
				}
				else
					error = handler->Invoke(method, args, &result);
			}
			lua_pushboolean(L, error == Web::Browser::Bridge::QueryError_Ok);
			lua_pushlstring(L, result.data(), result.size());
			lua_pushinteger(L, (lua_Integer)error);
			return 3;
		}

		// token = dew_core.on(screenId, event, fn)
		int UiRoot::L_on(lua_State *L)
		{
			UiRoot *self = Get();
			Screen *screen = self->FindScreen(CheckString(L, 1));
			const std::string event = CheckString(L, 2);
			if (!screen || event.empty() || !lua_isfunction(L, 3))
			{
				lua_pushnil(L);
				return 1;
			}
			const int ref = self->m_lua.Ref(3);
			screen->handlers[event].push_back(ref);
			lua_pushinteger(L, ref);
			return 1;
		}

		// dew_core.off(screenId, token)
		int UiRoot::L_off(lua_State *L)
		{
			UiRoot *self = Get();
			Screen *screen = self->FindScreen(CheckString(L, 1));
			int token = (int)luaL_optinteger(L, 2, 0);
			if (!screen || token <= 0)
				return 0;
			for (auto &handlers : screen->handlers)
			{
				auto it = std::find(handlers.second.begin(), handlers.second.end(), token);
				if (it != handlers.second.end())
				{
					handlers.second.erase(it);
					self->m_lua.Unref(token);
					break;
				}
			}
			return 0;
		}

		// dew_core.show(screenId, targetId|nil, data)
		int UiRoot::L_show(lua_State *L)
		{
			UiRoot *self = Get();
			std::string target = lua_isstring(L, 2) ? CheckString(L, 2) : CheckString(L, 1);
			self->RequestScreen(target, ArgJson(L, 3));
			return 0;
		}

		// dew_core.hide(screenId, targetId|nil)
		int UiRoot::L_hide(lua_State *L)
		{
			UiRoot *self = Get();
			std::string target = lua_isstring(L, 2) ? CheckString(L, 2) : CheckString(L, 1);
			self->HideScreen(target);
			return 0;
		}

		// dew_core.notify(screenId, event, data) -- a screen-originated event, broadcast to subscribers
		int UiRoot::L_notify(lua_State *L)
		{
			Get()->Notify(CheckString(L, 2), ArgJson(L, 3), true);
			return 0;
		}

		// dew_core.notifyScreen(targetId, event, data)
		int UiRoot::L_notifyScreen(lua_State *L)
		{
			Get()->NotifyScreen(CheckString(L, 1), CheckString(L, 2), ArgJson(L, 3));
			return 0;
		}

		// dew_core.captureInput(screenId, capture)
		int UiRoot::L_captureInput(lua_State *L)
		{
			UiRoot *self = Get();
			if (Screen *screen = self->FindScreen(CheckString(L, 1)))
			{
				screen->captureInput = lua_toboolean(L, 2) != 0;
				screen->capturePointer = false; // as ui.js: pointer capture is dropped either way
				self->UpdateOverlay();
				rapidjson::StringBuffer buffer;
				rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
				writer.StartObject();
				writer.Key("capture");
				writer.Bool(screen->captureInput);
				writer.Key("screen");
				writer.String(screen->id.c_str());
				writer.EndObject();
				self->Notify("captureInput", buffer.GetString(), true);
			}
			return 0;
		}

		// dew_core.capturePointer(screenId, capture)
		int UiRoot::L_capturePointer(lua_State *L)
		{
			UiRoot *self = Get();
			if (Screen *screen = self->FindScreen(CheckString(L, 1)))
			{
				screen->capturePointer = lua_toboolean(L, 2) != 0;
				self->UpdateOverlay();
			}
			return 0;
		}

		// dew_core.toast(table) -> the toast layer's "toast" handler draws it
		int UiRoot::L_toast(lua_State *L)
		{
			Get()->NotifyScreen(kToastScreenId, "toast", ArgJson(L, 1));
			return 0;
		}

		// id = dew_core.setTimer(screenId, fn, milliseconds, repeat)
		int UiRoot::L_setTimer(lua_State *L)
		{
			UiRoot *self = Get();
			if (!lua_isfunction(L, 2))
				return 0;
			Screen *screen = self->FindScreen(CheckString(L, 1));
			const int owner = screen ? screen->envRef : 0;
			const double delay = luaL_optnumber(L, 3, 0.0) / 1000.0;
			const bool repeat = lua_toboolean(L, 4) != 0;
			lua_pushinteger(L, self->m_timers.SetTimer(self->m_lua.Ref(2), delay, repeat, owner));
			return 1;
		}

		// dew_core.clearTimer(id)
		int UiRoot::L_clearTimer(lua_State *L)
		{
			Get()->m_timers.Clear((int)luaL_optinteger(L, 1, 0));
			return 0;
		}

		// id = dew_core.onFrame(screenId, fn)
		int UiRoot::L_onFrame(lua_State *L)
		{
			UiRoot *self = Get();
			if (!lua_isfunction(L, 2))
				return 0;
			Screen *screen = self->FindScreen(CheckString(L, 1));
			lua_pushinteger(L, self->m_timers.AddFrameCallback(self->m_lua.Ref(2), screen ? screen->envRef : 0));
			return 1;
		}

		// id = dew_core.http(screenId, {url, method, body, headers, timeout}, callback)
		int UiRoot::L_http(lua_State *L)
		{
			UiRoot *self = Get();
			luaL_checktype(L, 2, LUA_TTABLE);
			Screen *screen = self->FindScreen(CheckString(L, 1));
			auto field = [&](const char *name, const char *fallback) {
				lua_getfield(L, 2, name);
				std::string value = lua_isstring(L, -1) ? CheckString(L, -1) : std::string(fallback);
				lua_pop(L, 1);
				return value;
			};
			const std::string url = field("url", "");
			const std::string method = field("method", "GET");
			const std::string body = field("body", "");
			lua_getfield(L, 2, "timeout");
			const double timeout = lua_isnumber(L, -1) ? lua_tonumber(L, -1) / 1000.0 : 30.0;
			lua_pop(L, 1);
			std::vector<std::pair<std::string, std::string>> headers;
			lua_getfield(L, 2, "headers");
			if (lua_istable(L, -1))
			{
				lua_pushnil(L);
				while (lua_next(L, -2) != 0)
				{
					if (lua_isstring(L, -2) && lua_isstring(L, -1))
						headers.emplace_back(CheckString(L, -2), CheckString(L, -1));
					lua_pop(L, 1);
				}
			}
			lua_pop(L, 1);
			const int callback = lua_isfunction(L, 3) ? self->m_lua.Ref(3) : 0;
			lua_pushinteger(L, self->m_http.Request(method, url, body, headers, timeout, callback, screen ? screen->envRef : 0));
			return 1;
		}

		int UiRoot::L_httpCancel(lua_State *L)
		{
			Get()->m_http.Cancel((int)luaL_optinteger(L, 1, 0));
			return 0;
		}

		// dew_core.fetchImage(screenId, url, function(ok, cacheUrl) end)
		int UiRoot::L_fetchImage(lua_State *L)
		{
			UiRoot *self = Get();
			const std::string url = CheckString(L, 2);
			const int callback = lua_isfunction(L, 3) ? self->m_lua.Ref(3) : 0;
			self->m_textures.FetchImage(url, [callback](bool ok, const std::string &cacheUrl) {
				auto *self = Get();
				if (!self)
					return;
				int ref = callback;
				lua_State *L = self->m_lua.L();
				const int top = lua_gettop(L);
				self->m_lua.PushRef(ref);
				if (lua_isfunction(L, -1))
				{
					lua_pushboolean(L, ok);
					lua_pushstring(L, cacheUrl.c_str());
					self->m_lua.PCall(2, 0);
				}
				lua_settop(L, top);
				self->m_lua.Unref(ref);
			});
			return 0;
		}

		// dew_core.openUrl(url) -- window.open replacement: hands the link to the system browser
		int UiRoot::L_openUrl(lua_State *L)
		{
			std::string url = CheckString(L, 1);
			if (url.empty())
				return 0;
			if (_strnicmp(url.c_str(), "http://", 7) != 0 && _strnicmp(url.c_str(), "https://", 8) != 0)
				url = "http://" + url;
			const std::wstring wide = Utils::String::WidenString(url);
			ShellExecuteW(nullptr, L"open", wide.c_str(), L"", nullptr, SW_SHOWNORMAL);
			return 0;
		}

		// dew_core.log(level, message)  level: "error" | "warn" | "info" | "debug"
		int UiRoot::L_log(lua_State *L)
		{
			const std::string level = CheckString(L, 1, "info");
			const std::string message = CheckString(L, 2);
			Utils::LogLevel logLevel = Utils::LogLevel::Info;
			if (level == "error")
				logLevel = Utils::LogLevel::Error;
			else if (level == "warn" || level == "warning")
				logLevel = Utils::LogLevel::Warning;
			else if (level == "debug")
				logLevel = Utils::LogLevel::Trace;
			Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Graphics, logLevel, "[Lua] " + message);
			if (logLevel >= Utils::LogLevel::Warning || Get()->m_debugging)
				Console::WriteLine("[ui] " + message);
			return 0;
		}

		// text|nil = dew_core.readFile(url)
		int UiRoot::L_readFile(lua_State *L)
		{
			std::string data;
			if (Get()->m_files.ReadAll(CheckString(L, 1), data))
				lua_pushlstring(L, data.data(), data.size());
			else
				lua_pushnil(L);
			return 1;
		}

		// bool = dew_core.fileExists(url)   (dew://, pak://, plain paths)
		int UiRoot::L_fileExists(lua_State *L)
		{
			FileInterface::Resolved resolved;
			lua_pushboolean(L, Get()->m_files.Resolve(CheckString(L, 1), resolved));
			return 1;
		}

		int UiRoot::L_storageGet(lua_State *L)
		{
			UiRoot *self = Get();
			auto it = self->m_storage.find(CheckString(L, 1));
			if (it == self->m_storage.end())
				lua_pushnil(L);
			else
				lua_pushlstring(L, it->second.data(), it->second.size());
			return 1;
		}

		int UiRoot::L_storageSet(lua_State *L)
		{
			UiRoot *self = Get();
			const std::string key = CheckString(L, 1);
			if (lua_isnoneornil(L, 2))
				self->m_storage.erase(key);
			else
				self->m_storage[key] = CheckString(L, 2);
			self->SaveStorage();
			return 0;
		}

		// {workingSet, privateBytes, luaBytes} = dew_core.getMemoryStats()
		int UiRoot::L_getMemoryStats(lua_State *L)
		{
			PROCESS_MEMORY_COUNTERS_EX counters = {};
			counters.cb = sizeof(counters);
			GetProcessMemoryInfo(GetCurrentProcess(), reinterpret_cast<PROCESS_MEMORY_COUNTERS *>(&counters), sizeof(counters));
			lua_createtable(L, 0, 3);
			lua_pushinteger(L, (lua_Integer)counters.WorkingSetSize);
			lua_setfield(L, -2, "workingSet");
			lua_pushinteger(L, (lua_Integer)counters.PrivateUsage);
			lua_setfield(L, -2, "privateBytes");
			lua_pushinteger(L, (lua_Integer)lua_gc(L, LUA_GCCOUNT, 0) * 1024 + lua_gc(L, LUA_GCCOUNTB, 0));
			lua_setfield(L, -2, "luaBytes");
			return 1;
		}

		// {{id=, name=}, ...} = dew_core.enumerateAudioInputs()
		// names = dew_core.enumerateAudioInputs() -- active capture endpoints' friendly names, the
		// labels navigator.mediaDevices.enumerateDevices() gave the settings page.
		int UiRoot::L_enumerateAudioInputs(lua_State *L)
		{
			std::vector<std::string> names;
			const HRESULT init = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
			IMMDeviceEnumerator *enumerator = nullptr;
			if (SUCCEEDED(CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (void **)&enumerator)))
			{
				IMMDeviceCollection *devices = nullptr;
				if (SUCCEEDED(enumerator->EnumAudioEndpoints(eCapture, DEVICE_STATE_ACTIVE, &devices)))
				{
					UINT count = 0;
					devices->GetCount(&count);
					for (UINT i = 0; i < count; i++)
					{
						IMMDevice *device = nullptr;
						if (FAILED(devices->Item(i, &device)))
							continue;
						IPropertyStore *store = nullptr;
						if (SUCCEEDED(device->OpenPropertyStore(STGM_READ, &store)))
						{
							PROPVARIANT name;
							PropVariantInit(&name);
							if (SUCCEEDED(store->GetValue(PKEY_Device_FriendlyName, &name)) && name.vt == VT_LPWSTR && name.pwszVal)
								names.push_back(Utils::String::ThinString(name.pwszVal));
							PropVariantClear(&name);
							store->Release();
						}
						device->Release();
					}
					devices->Release();
				}
				enumerator->Release();
			}
			if (SUCCEEDED(init))
				CoUninitialize();
			lua_createtable(L, (int)names.size(), 0);
			for (size_t i = 0; i < names.size(); i++)
			{
				lua_pushlstring(L, names[i].data(), names[i].size());
				lua_rawseti(L, -2, (lua_Integer)i + 1);
			}
			LuaJson::MarkArray(L, -1);
			return 1;
		}

		int UiRoot::L_isDebugging(lua_State *L)
		{
			lua_pushboolean(L, Get()->m_debugging);
			return 1;
		}

		// state = dew_core.getScreenState(screenId)  (0 hidden, 1 waiting, 2 visible)
		int UiRoot::L_getScreenState(lua_State *L)
		{
			Screen *screen = Get()->FindScreen(CheckString(L, 1));
			lua_pushinteger(L, screen ? (lua_Integer)screen->state : 0);
			return 1;
		}

		// dew_core.setToastActive(bool) -- keeps the overlay rendering while toasts are on screen
		int UiRoot::L_setToastActive(lua_State *L)
		{
			UiRoot *self = Get();
			self->m_toastActive = lua_toboolean(L, 1) != 0;
			self->UpdateOverlay();
			return 0;
		}

		// seconds = dew_core.getTime()
		int UiRoot::L_getTime(lua_State *L)
		{
			lua_pushnumber(L, Get()->m_now);
			return 1;
		}

		// dew_core.setSelectionRange(inputElement, start, end) -- caret/selection of a text input
		// (the Lua bindings do not expose ElementFormControlInput::SetSelectionRange)
		int UiRoot::L_setSelectionRange(lua_State *L)
		{
			auto *element = ::Rml::Lua::LuaType<::Rml::Element>::check(L, 1);
			auto *input = dynamic_cast<::Rml::ElementFormControlInput *>(element);
			if (input)
				input->SetSelectionRange((int)luaL_checkinteger(L, 2), (int)luaL_optinteger(L, 3, luaL_checkinteger(L, 2)));
			lua_pushboolean(L, input != nullptr);
			return 1;
		}
	}
}
