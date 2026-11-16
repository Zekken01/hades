/* ---------- headers */

#include "hades/hades.h"

#include "Web/Rml/LuaState.hpp"

#include "Console/Console.hpp"
#include "Utils/Logger.hpp"
#include "Utils/Singleton.hpp"
#include "Web/Rml/LuaJson.hpp"

/* ---------- private code */

namespace
{
	void LogLuaError(const std::string &message)
	{
		Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Graphics, Utils::LogLevel::Error, "[Lua] " + message);
		Console::WriteLine("[Lua] " + message);
	}
}

namespace Web
{
	namespace RmlUi
	{
		LuaState *LuaState::s_current = nullptr;

		LuaState::LuaState()
		{
		}

		LuaState::~LuaState()
		{
			Shutdown();
		}

		bool LuaState::Init()
		{
			if (m_L)
				return true;
			m_L = luaL_newstate();
			if (!m_L)
				return false;
			luaL_openlibs(m_L);

			// The UI never needs to spawn processes or exit the game from Lua.
			lua_getglobal(m_L, "os");
			if (lua_istable(m_L, -1))
			{
				lua_pushnil(m_L);
				lua_setfield(m_L, -2, "execute");
				lua_pushnil(m_L);
				lua_setfield(m_L, -2, "exit");
			}
			lua_pop(m_L, 1);
			lua_getglobal(m_L, "io");
			if (lua_istable(m_L, -1))
			{
				lua_pushnil(m_L);
				lua_setfield(m_L, -2, "popen");
			}
			lua_pop(m_L, 1);

			LuaJson::Register(m_L);
			s_current = this;
			return true;
		}

		void LuaState::Shutdown()
		{
			if (!m_L)
				return;
			m_deferred.clear();
			lua_close(m_L);
			m_L = nullptr;
			if (s_current == this)
				s_current = nullptr;
		}

		int LuaState::Traceback(lua_State *L)
		{
			const char *message = lua_tostring(L, 1);
			if (!message)
			{
				if (luaL_callmeta(L, 1, "__tostring") && lua_type(L, -1) == LUA_TSTRING)
					return 1;
				message = lua_pushfstring(L, "(error object is a %s value)", luaL_typename(L, 1));
			}
			luaL_traceback(L, L, message, 1);
			return 1;
		}

		bool LuaState::PCall(int nargs, int nresults)
		{
			const int handlerIndex = lua_gettop(m_L) - nargs;
			lua_pushcfunction(m_L, Traceback);
			lua_insert(m_L, handlerIndex);
			const int status = lua_pcall(m_L, nargs, nresults, handlerIndex);
			if (status != LUA_OK)
			{
				const char *error = lua_tostring(m_L, -1);
				LogLuaError(error ? error : "unknown error");
				lua_pop(m_L, 2); // error, handler
				return false;
			}
			lua_remove(m_L, handlerIndex);
			return true;
		}

		int LuaState::CreateEnv()
		{
			lua_newtable(m_L);
			lua_newtable(m_L);
			lua_getglobal(m_L, "_G");
			lua_setfield(m_L, -2, "__index");
			lua_setmetatable(m_L, -2);
			return luaL_ref(m_L, LUA_REGISTRYINDEX);
		}

		void LuaState::PushEnv(int envRef)
		{
			if (envRef > 0)
				lua_rawgeti(m_L, LUA_REGISTRYINDEX, envRef);
			else
				lua_pushglobaltable(m_L);
		}

		void LuaState::ReleaseEnv(int &envRef)
		{
			Unref(envRef);
		}

		bool LuaState::LoadChunk(const char *code, size_t length, const std::string &chunkName, int envRef)
		{
			if (luaL_loadbufferx(m_L, code, length, chunkName.c_str(), "t") != LUA_OK)
			{
				const char *error = lua_tostring(m_L, -1);
				LogLuaError(error ? error : "load failed");
				lua_pop(m_L, 1);
				return false;
			}
			if (envRef > 0)
			{
				// A main chunk's first upvalue is _ENV.
				PushEnv(envRef);
				lua_setupvalue(m_L, -2, 1);
			}
			return true;
		}

		bool LuaState::RunChunk(const char *code, size_t length, const std::string &chunkName, int envRef)
		{
			if (!LoadChunk(code, length, chunkName, envRef))
				return false;
			return PCall(0, 0);
		}

		int LuaState::Ref(int index)
		{
			lua_pushvalue(m_L, index);
			return luaL_ref(m_L, LUA_REGISTRYINDEX);
		}

		void LuaState::Unref(int &ref)
		{
			if (ref > 0 && m_L)
				luaL_unref(m_L, LUA_REGISTRYINDEX, ref);
			ref = LUA_NOREF;
		}

		void LuaState::PushRef(int ref)
		{
			if (ref > 0)
				lua_rawgeti(m_L, LUA_REGISTRYINDEX, ref);
			else
				lua_pushnil(m_L);
		}

		void LuaState::Defer(std::function<void(lua_State *)> work)
		{
			m_deferred.push_back(std::move(work));
		}

		void LuaState::RunDeferred()
		{
			// Work queued while running is picked up next frame, mirroring JS task ordering.
			std::deque<std::function<void(lua_State *)>> work;
			work.swap(m_deferred);
			for (auto &item : work)
			{
				const int top = lua_gettop(m_L);
				item(m_L);
				lua_settop(m_L, top);
			}
		}

		void LuaState::ClearDeferred()
		{
			m_deferred.clear();
		}

		void LuaState::CollectGarbageStep()
		{
			if (m_L)
				lua_gc(m_L, LUA_GCSTEP, 0);
		}
	}
}
