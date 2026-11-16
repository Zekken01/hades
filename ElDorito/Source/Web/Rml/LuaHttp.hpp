#ifndef __WEB_RML_LUAHTTP_HPP__
#define __WEB_RML_LUAHTTP_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include <memory>
#include <mutex>
#include <string>
#include <utility>
#include <vector>

/* ---------- forward declarations */

namespace Http
{
	class IHttpRequest;
}

/* ---------- definitions */

namespace Web
{
	namespace RmlUi
	{
		class LuaState;

		// fetch()/XMLHttpRequest for the Lua screens over the game's WinHTTP client.  Requests
		// complete on WinHTTP threads; Pump() delivers the results to Lua on the game thread.
		class LuaHttp
		{
		public:
			explicit LuaHttp(LuaState &lua);
			~LuaHttp();

			// Returns the request id; `callbackRef` is called as callback(ok, {status, body, headers}).
			int Request(const std::string &method, const std::string &url, std::string body,
				const std::vector<std::pair<std::string, std::string>> &headers, double timeoutSeconds, int callbackRef, int owner);
			void Cancel(int id);
			void CancelOwner(int owner);
			void CancelAll();
			void Pump(double now);

		private:
			struct Entry;

			LuaState &m_lua;
			std::mutex m_mutex;
			std::vector<std::shared_ptr<Entry>> m_entries;
			int m_nextId = 1;
		};
	}
}

#endif // __WEB_RML_LUAHTTP_HPP__
