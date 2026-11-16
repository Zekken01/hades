#ifndef __WEB_RML_LUASTATE_HPP__
#define __WEB_RML_LUASTATE_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include <RmlUi/Lua/IncludeLua.h>

#include <deque>
#include <functional>
#include <string>

/* ---------- definitions */

namespace Web
{
	namespace RmlUi
	{
		// Owns the one lua_State the UI runs on.  Screens get their own environment table
		// (iframe-style global isolation) that falls back to _G; the shared `dew_core`,
		// `dew_json` and `rmlui` globals live in _G.
		class LuaState
		{
		public:
			LuaState();
			~LuaState();

			bool Init();
			void Shutdown();
			lua_State *L() const { return m_L; }
			static LuaState *Current() { return s_current; }

			// Environments (registry references).
			int CreateEnv();
			void PushEnv(int envRef);
			void ReleaseEnv(int &envRef);

			// Compiles `code` and runs it with _ENV = env (0 = globals).  Errors are logged.
			bool RunChunk(const char *code, size_t length, const std::string &chunkName, int envRef);
			// Loads a chunk without running it; leaves the function on the stack on success.
			bool LoadChunk(const char *code, size_t length, const std::string &chunkName, int envRef);
			// Calls the function (with its arguments) on top of the stack with a traceback handler.
			bool PCall(int nargs, int nresults);

			int Ref(int index);
			void Unref(int &ref);
			void PushRef(int ref);

			// Work queued for the next Update() on the game thread (bridge callbacks and the like).
			void Defer(std::function<void(lua_State *)> work);
			void RunDeferred();
			void ClearDeferred();

			void CollectGarbageStep();

		private:
			static int Traceback(lua_State *L);

			lua_State *m_L = nullptr;
			std::deque<std::function<void(lua_State *)>> m_deferred;
			static LuaState *s_current;
		};
	}
}

#endif // __WEB_RML_LUASTATE_HPP__
