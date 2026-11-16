/* ---------- headers */

#include "hades/hades.h"

#include "Web/Rml/LuaTimers.hpp"

#include "Web/Rml/LuaState.hpp"

#include <algorithm>

/* ---------- public code */

namespace Web
{
	namespace RmlUi
	{
		LuaTimers::LuaTimers(LuaState &lua) : m_lua(lua)
		{
		}

		LuaTimers::~LuaTimers()
		{
			ClearAll();
		}

		int LuaTimers::SetTimer(int functionRef, double delaySeconds, bool repeat, int owner)
		{
			Timer timer = {};
			timer.id = m_nextId++;
			timer.functionRef = functionRef;
			timer.interval = std::max(delaySeconds, 0.0);
			timer.due = -1.0; // set on the first tick so timers created before Init do not fire early
			timer.repeat = repeat;
			timer.owner = owner;
			m_timers.push_back(timer);
			return timer.id;
		}

		int LuaTimers::AddFrameCallback(int functionRef, int owner)
		{
			Timer timer = {};
			timer.id = m_nextId++;
			timer.functionRef = functionRef;
			timer.everyFrame = true;
			timer.repeat = true;
			timer.owner = owner;
			m_timers.push_back(timer);
			return timer.id;
		}

		void LuaTimers::Clear(int id)
		{
			for (auto &timer : m_timers)
				if (timer.id == id)
					timer.dead = true;
		}

		void LuaTimers::ClearOwner(int owner)
		{
			for (auto &timer : m_timers)
				if (timer.owner == owner)
					timer.dead = true;
		}

		void LuaTimers::ClearAll()
		{
			for (auto &timer : m_timers)
				timer.dead = true;
			if (!m_ticking)
			{
				for (auto &timer : m_timers)
					m_lua.Unref(timer.functionRef);
				m_timers.clear();
			}
		}

		void LuaTimers::Tick(double now)
		{
			m_ticking = true;
			// Index-based: callbacks may add timers while we iterate.
			for (size_t i = 0; i < m_timers.size(); i++)
			{
				Timer &timer = m_timers[i];
				if (timer.dead)
					continue;
				if (!timer.everyFrame)
				{
					if (timer.due < 0.0)
					{
						timer.due = now + timer.interval;
						continue;
					}
					if (now < timer.due)
						continue;
					if (timer.repeat)
						timer.due = now + std::max(timer.interval, 0.001);
					else
						timer.dead = true;
				}
				lua_State *L = m_lua.L();
				const int top = lua_gettop(L);
				m_lua.PushRef(m_timers[i].functionRef);
				if (lua_isfunction(L, -1))
				{
					lua_pushnumber(L, now);
					m_lua.PCall(1, 0);
				}
				lua_settop(L, top);
			}
			m_ticking = false;
			// Drop dead timers and release their functions.
			for (auto it = m_timers.begin(); it != m_timers.end();)
			{
				if (it->dead)
				{
					m_lua.Unref(it->functionRef);
					it = m_timers.erase(it);
				}
				else
					++it;
			}
		}
	}
}
