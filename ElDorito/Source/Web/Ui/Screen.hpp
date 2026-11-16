#ifndef __WEB_UI_SCREEN_HPP__
#define __WEB_UI_SCREEN_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Forge/Magnets.hpp"
#include "mods/mod_package_updater.hpp"
#include "ThirdParty/rapidjson/allocators.h"
#include "ThirdParty/rapidjson/document.h"
#include "ThirdParty/rapidjson/stream.h"
#include "Utils/NameValueTable.hpp"
#include "Utils/StlUtil.hpp"
#include "Web/Bridge/WebRendererQueryHandler.hpp"
#include "Web/Ui/ScreenLayer.hpp"

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

/* ---------- forward declarations */

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{
			class WebRendererQueryHandler;
		}
	}
}
namespace Web
{
	namespace Ui
	{
		class WebScreen;
	}
}

/* ---------- constants */

/* ---------- definitions */

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{
			// Registry of the methods the UI can call ("command", "show", "sessionInfo", ...).
			// Formerly the CEF message-router handler; Lua now invokes methods synchronously on
			// the game thread, so there is no query queue.
			class WebRendererQueryHandler
			{
			public:
				using Method = std::function<enum Web::Browser::Bridge::QueryError __cdecl(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &,std::string *)>;

				WebRendererQueryHandler();
				void AddMethod(std::string const &name, Method const &method);
				bool HasMethod(std::string const &name) const;
				// Runs a method; `result` receives the JSON result or the error message.
				Web::Browser::Bridge::QueryError Invoke(std::string const &name, rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &args, std::string *result);
				// Parses a {"method":..., "args":{...}} request string the way the CEF bridge did.
				Web::Browser::Bridge::QueryError InvokeRequest(std::string const &request, std::string *result);
				void Update();
				virtual ~WebRendererQueryHandler() = default;

			private:
				std::unordered_map<std::string, Method> m_Methods;
			};
		}
	}
}

namespace Web
{
	namespace Ui
	{
		class WebScreen;
	}
}

/* ---------- constants */

/* ---------- definitions */


namespace Web
{
	namespace Ui
	{
		class WebScreen
		{
		public:
			virtual _inline void OnCreate(Web::Browser::Bridge::WebRendererQueryHandler &queryHandler);
			virtual _inline void OnDestroy();
			virtual _inline void OnShow();
			virtual _inline void OnHide();
			virtual _inline void OnUpdate();
		protected:
			void Notify(std::string const &event, std::string const &data);
		public:
			WebScreen(Web::Ui::WebScreen &); /* compiler_generated() */
			WebScreen(Web::Ui::WebScreen const &); /* compiler_generated() */
			_inline WebScreen() = default; /* compiler_generated() */
			Web::Ui::WebScreen &operator=(Web::Ui::WebScreen &); /* compiler_generated() */
			Web::Ui::WebScreen &operator=(Web::Ui::WebScreen const &); /* compiler_generated() */
		};
		static_assert(sizeof(Web::Ui::WebScreen) == 4, "Invalid Web::Ui::WebScreen size");
	}
}

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

namespace Web
{
	namespace Ui
	{
		inline void WebScreen::OnCreate(Web::Browser::Bridge::WebRendererQueryHandler &queryHandler) // 0x10C7D930
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OnCreate@WebScreen@Ui@Web@@UAEXAAVWebRendererQueryHandler@Bridge@Browser@3@@Z");
		}

		inline void WebScreen::OnDestroy() // 0x10C7D970
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OnDestroy@WebScreen@Ui@Web@@UAEXXZ");
		}

		inline void WebScreen::OnShow() // 0x10C7DFF0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OnShow@WebScreen@Ui@Web@@UAEXXZ");
		}

		inline void WebScreen::OnHide() // 0x10C7DFB0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OnHide@WebScreen@Ui@Web@@UAEXXZ");
		}

		inline void WebScreen::OnUpdate() // 0x10C7E030
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OnUpdate@WebScreen@Ui@Web@@UAEXXZ");
		}
	}
}

/* ---------- private code */

#endif // __WEB_UI_SCREEN_HPP__
