/* ---------- headers */

#include "hades/hades.h"

#include "Web/Rml/LuaHttp.hpp"

#include "Common/Http/HttpHeaders.hpp"
#include "Common/Http/HttpRequest.hpp"
#include "Web/Rml/LuaState.hpp"

#include <atomic>

/* ---------- prototypes */

namespace Http { extern std::shared_ptr<Http::IHttpRequest> CreateRequest(); }

/* ---------- private code */

namespace Web
{
	namespace RmlUi
	{
		enum class HttpState : int
		{
			Loading = 0,
			Done,
			Failed,
		};

		struct LuaHttp::Entry
		{
			int id = 0;
			int owner = 0;
			int callbackRef = 0;
			double started = 0.0;
			double timeout = 0.0;
			bool cancelled = false;
			std::shared_ptr<Http::IHttpRequest> request;
			std::atomic<int> state = (int)HttpState::Loading;
			std::atomic<int> statusCode = 0;
			std::mutex bytesMutex;
			std::string body;
			std::vector<std::pair<std::string, std::string>> responseHeaders;
		};

		LuaHttp::LuaHttp(LuaState &lua) : m_lua(lua)
		{
		}

		LuaHttp::~LuaHttp()
		{
			CancelAll();
		}

		int LuaHttp::Request(const std::string &method, const std::string &url, std::string body,
			const std::vector<std::pair<std::string, std::string>> &headers, double timeoutSeconds, int callbackRef, int owner)
		{
			auto entry = std::make_shared<Entry>();
			entry->id = m_nextId++;
			entry->owner = owner;
			entry->callbackRef = callbackRef;
			entry->timeout = timeoutSeconds;
			entry->started = -1.0; // stamped on the first Pump

			auto request = Http::CreateRequest();
			if (!request)
			{
				entry->state = (int)HttpState::Failed;
				std::lock_guard<std::mutex> lock(m_mutex);
				m_entries.push_back(entry);
				return entry->id;
			}
			request->SetMethod(method.empty() ? "GET" : method);
			request->SetUrl(url);
			request->SetMaxRedirects(5);
			if (!body.empty())
				request->SetBody(std::move(body));
			if (!headers.empty())
			{
				Http::CHttpHeaders httpHeaders;
				for (auto &header : headers)
					httpHeaders.Add(header.first, header.second, Http::CHttpHeaders::Replace);
				request->SetHeaders(httpHeaders);
			}

			std::weak_ptr<Entry> weak = entry;
			request->SetReceiver([weak](const char *data, unsigned int length) -> bool {
				auto e = weak.lock();
				if (!e)
					return false;
				std::lock_guard<std::mutex> lock(e->bytesMutex);
				e->body.append(data, length);
				return true;
			});
			request->SetOnCompleted([weak](std::shared_ptr<Http::IHttpRequest> req, bool success) {
				auto e = weak.lock();
				if (!e)
					return;
				if (auto response = req->GetResponse())
				{
					e->statusCode = response->GetResponseCode();
					std::lock_guard<std::mutex> lock(e->bytesMutex);
					for (auto &header : response->GetHeaders())
						e->responseHeaders.emplace_back(header.first, header.second);
				}
				e->state = (int)(success ? HttpState::Done : HttpState::Failed);
			});
			entry->request = request;
			{
				std::lock_guard<std::mutex> lock(m_mutex);
				m_entries.push_back(entry);
			}
			if (!request->Send())
				entry->state = (int)HttpState::Failed;
			return entry->id;
		}

		void LuaHttp::Cancel(int id)
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			for (auto &entry : m_entries)
			{
				if (entry->id == id)
				{
					entry->cancelled = true;
					if (entry->request)
						entry->request->Cancel();
				}
			}
		}

		void LuaHttp::CancelOwner(int owner)
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			for (auto &entry : m_entries)
			{
				if (entry->owner == owner)
				{
					entry->cancelled = true;
					if (entry->request)
						entry->request->Cancel();
				}
			}
		}

		void LuaHttp::CancelAll()
		{
			std::vector<std::shared_ptr<Entry>> entries;
			{
				std::lock_guard<std::mutex> lock(m_mutex);
				entries.swap(m_entries);
			}
			for (auto &entry : entries)
			{
				if (entry->request)
					entry->request->Cancel();
				m_lua.Unref(entry->callbackRef);
			}
		}

		void LuaHttp::Pump(double now)
		{
			std::vector<std::shared_ptr<Entry>> finished;
			{
				std::lock_guard<std::mutex> lock(m_mutex);
				for (auto it = m_entries.begin(); it != m_entries.end();)
				{
					auto &entry = *it;
					if (entry->started < 0.0)
						entry->started = now;
					int state = entry->state.load();
					if (state == (int)HttpState::Loading && entry->timeout > 0.0 && now - entry->started > entry->timeout)
					{
						if (entry->request)
							entry->request->Cancel();
						entry->state = (int)HttpState::Failed;
						state = (int)HttpState::Failed;
					}
					if (entry->cancelled || state != (int)HttpState::Loading)
					{
						finished.push_back(entry);
						it = m_entries.erase(it);
					}
					else
						++it;
				}
			}

			lua_State *L = m_lua.L();
			for (auto &entry : finished)
			{
				entry->request.reset();
				if (entry->cancelled)
				{
					m_lua.Unref(entry->callbackRef);
					continue;
				}
				const bool ok = entry->state.load() == (int)HttpState::Done;
				const int top = lua_gettop(L);
				m_lua.PushRef(entry->callbackRef);
				if (lua_isfunction(L, -1))
				{
					lua_pushboolean(L, ok);
					lua_createtable(L, 0, 3);
					lua_pushinteger(L, entry->statusCode.load());
					lua_setfield(L, -2, "status");
					{
						std::lock_guard<std::mutex> lock(entry->bytesMutex);
						lua_pushlstring(L, entry->body.data(), entry->body.size());
						lua_setfield(L, -2, "body");
						lua_createtable(L, 0, (int)entry->responseHeaders.size());
						for (auto &header : entry->responseHeaders)
						{
							lua_pushlstring(L, header.second.data(), header.second.size());
							lua_setfield(L, -2, header.first.c_str());
						}
						lua_setfield(L, -2, "headers");
					}
					m_lua.PCall(2, 0);
				}
				lua_settop(L, top);
				m_lua.Unref(entry->callbackRef);
			}
		}
	}
}
