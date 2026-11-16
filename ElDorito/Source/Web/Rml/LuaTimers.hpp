#ifndef __WEB_RML_LUATIMERS_HPP__
#define __WEB_RML_LUATIMERS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include <vector>

/* ---------- definitions */

namespace Web
{
	namespace RmlUi
	{
		class LuaState;

		// setTimeout / setInterval / requestAnimationFrame for the Lua screens, ticked from the
		// game thread.  `owner` is the screen's environment reference so a screen's timers die
		// with it on unload/reload.
		class LuaTimers
		{
		public:
			explicit LuaTimers(LuaState &lua);
			~LuaTimers();

			int SetTimer(int functionRef, double delaySeconds, bool repeat, int owner);
			int AddFrameCallback(int functionRef, int owner);
			void Clear(int id);
			void ClearOwner(int owner);
			void ClearAll();
			void Tick(double now);

		private:
			struct Timer
			{
				int id;
				int functionRef;
				double due;
				double interval;
				bool repeat;
				bool everyFrame;
				int owner;
				bool dead;
			};

			LuaState &m_lua;
			std::vector<Timer> m_timers;
			int m_nextId = 1;
			bool m_ticking = false;
		};
	}
}

#endif // __WEB_RML_LUATIMERS_HPP__
