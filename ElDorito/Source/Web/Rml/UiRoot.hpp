#ifndef __WEB_RML_UIROOT_HPP__
#define __WEB_RML_UIROOT_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Web/Rml/LuaHttp.hpp"
#include "Web/Rml/LuaTimers.hpp"

#include <RmlUi/Lua/IncludeLua.h>

#include <deque>
#include <filesystem>
#include <functional>
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <vector>

/* ---------- forward declarations */

namespace Rml
{
	class Context;
	class ElementDocument;
}

/* ---------- definitions */

namespace Web
{
	namespace RmlUi
	{
		class AsyncTextures;
		class FileInterface;
		class LuaState;
		class ScreenDocument;

		// C++ port of ui/ui/ui.js: owns the screen list from screens/screens.json, one document
		// per screen, their Hidden/Waiting/Visible state, event routing between C++ and the
		// screens' Lua, input capture aggregation and the `dew_core` Lua API.
		class UiRoot
		{
		public:
			enum class ScreenState
			{
				Hidden = 0,
				Waiting = 1,
				Visible = 2,
			};

			UiRoot(LuaState &lua, ::Rml::Context *context, FileInterface &files, AsyncTextures &textures);
			~UiRoot();

			static UiRoot *Get() { return s_instance; }

			bool Init(const std::filesystem::path &uiDirectory, bool debugging);
			void Shutdown();
			// Processes queued commands, input, timers, HTTP and texture completions, then
			// updates the context.  UI thread (the EndScene thread) only: RmlUi and Lua are
			// not thread-safe and must never be touched from another thread.
			void Update(double now);
			// Game thread (ElDorito::Tick): runs the bridge calls and ScreenLayer callbacks
			// the UI queued, the way the CEF query handler did; results go back to the UI
			// thread for the next Update.
			void PumpGameThread();
			void OnResize(int width, int height);
			void ReloadAll();
			void ToggleDebugger();
			bool IsDebuggerVisible() const;
			::Rml::Context *GetContext() const { return m_context; }

			// C++ -> UI, thread-safe (queued until the next Update).
			void RequestScreen(const std::string &screenId, const std::string &dataJson);
			void HideScreen(const std::string &screenId);
			void Notify(const std::string &event, const std::string &dataJson, bool broadcast);
			void NotifyScreen(const std::string &screenId, const std::string &event, const std::string &dataJson);
			void SendControllerInput(const std::string &inputJson);

			// Debug/tooling: runs Lua in a screen's environment and returns tostring() of the
			// first result (or the error).
			std::string EvalInScreen(const std::string &screenId, const std::string &code);

		private:
			struct Screen
			{
				std::string id;
				std::string url;
				std::string fallbackUrl;
				std::string variable;      // cvar that holds the url, if any
				bool captureInput = false;
				bool capturePointer = false;
				int zIndex = 0;
				bool overlayOnly = false;  // the toast layer: always shown, never counts as "visible UI"
				ScreenState state = ScreenState::Hidden;
				bool loaded = false;
				double loadStartTime = 0.0;
				std::string pendingData;   // JSON handed to the next "show"
				ScreenDocument *document = nullptr;
				int envRef = 0;
				// event name -> Lua handler refs (dew.on)
				std::map<std::string, std::vector<int>> handlers;
			};

			struct Command
			{
				enum class Type { Request, Hide, Notify, NotifyScreen, ControllerInput } type;
				std::string screenId;
				std::string event;
				std::string json;
				bool broadcast = false;
			};

			void ProcessCommands();
			void CreateScreen(const std::string &id, const std::string &url, const std::string &variable, const std::string &fallbackUrl, bool captureInput, int zIndex, bool overlayOnly);
			void LoadScreen(Screen &screen);
			void UnloadScreen(Screen &screen);
			void ShowScreen(Screen &screen, bool show);
			void SetState(Screen &screen, ScreenState state);
			void UpdateOverlay();
			void DeliverEvent(Screen &screen, const std::string &event, const std::string &dataJson);
			void DeliverEventToSubscribed(const std::string &event, const std::string &dataJson, bool broadcast);
			void DeliverEventTable(Screen &screen, const std::string &event, int dataRef);
			Screen *FindScreen(const std::string &id);
			Screen *FindScreenByEnv(int envRef);
			Screen *FindScreenByDocument(ScreenDocument *document);
			std::string ResolveScreenUrl(const Screen &screen) const;
			void OnEnvCreated(ScreenDocument &document, int envRef);
			void OnEnvReleased(ScreenDocument &document, int envRef);
			bool LoadDewLibrary();
			void RegisterDewCore();
			void LoadStorage();
			void SaveStorage();

			// dew_core (Lua C functions)
			static int L_callMethod(lua_State *L);
			static int L_callMethodSync(lua_State *L);
			static int L_on(lua_State *L);
			static int L_off(lua_State *L);
			static int L_show(lua_State *L);
			static int L_hide(lua_State *L);
			static int L_notify(lua_State *L);
			static int L_notifyScreen(lua_State *L);
			static int L_captureInput(lua_State *L);
			static int L_capturePointer(lua_State *L);
			static int L_toast(lua_State *L);
			static int L_setTimer(lua_State *L);
			static int L_clearTimer(lua_State *L);
			static int L_onFrame(lua_State *L);
			static int L_http(lua_State *L);
			static int L_httpCancel(lua_State *L);
			static int L_fetchImage(lua_State *L);
			static int L_openUrl(lua_State *L);
			static int L_log(lua_State *L);
			static int L_readFile(lua_State *L);
			static int L_fileExists(lua_State *L);
			static int L_storageGet(lua_State *L);
			static int L_storageSet(lua_State *L);
			static int L_getMemoryStats(lua_State *L);
			static int L_enumerateAudioInputs(lua_State *L);
			static int L_isDebugging(lua_State *L);
			static int L_getScreenState(lua_State *L);
			static int L_setToastActive(lua_State *L);
			static int L_getTime(lua_State *L);

			LuaState &m_lua;
			::Rml::Context *m_context;
			FileInterface &m_files;
			AsyncTextures &m_textures;
			LuaTimers m_timers;
			LuaHttp m_http;
			std::filesystem::path m_uiDirectory;
			std::vector<std::unique_ptr<Screen>> m_screens; // sorted by zIndex ascending
			std::mutex m_commandMutex;
			std::deque<Command> m_commands;
			// UI thread -> game thread work, and game thread -> UI thread completions.
			std::mutex m_gameTaskMutex;
			std::deque<std::function<void()>> m_gameTasks;
			std::mutex m_uiTaskMutex;
			std::deque<std::function<void()>> m_uiTasks;
			void PostToGameThread(std::function<void()> task);
			void PostToUiThread(std::function<void()> task);
			void RunUiTasks();
			void DeliverMethodResult(int error, const std::string &result, int onSuccess, int onFailure, const std::string &method);
			int m_dewFactoryRef = 0;
			bool m_ready = false;
			bool m_debugging = false;
			bool m_debuggerInitialised = false;
			bool m_reloadPending = false;
			bool m_toastActive = false;
			bool m_lastOverlayVisible = false;
			double m_now = 0.0;
			std::map<std::string, std::string> m_storage;
			bool m_storageLoaded = false;
			static UiRoot *s_instance;
		};
	}
}

#endif // __WEB_RML_UIROOT_HPP__
