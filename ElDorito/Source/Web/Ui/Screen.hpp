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

#include <boost/lockfree/queue.hpp>
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

/* ---------- forward declarations */

struct CefStringTraitsUTF16;
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
			class WebRendererQueryHandler :
				public CefMessageRouterBrowserSide::Handler
			{
			public:
			private:
				public:
				struct PendingQuery
				{
					rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> m_Json; // 0x0
					std::function<enum Web::Browser::Bridge::QueryError __cdecl(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &,std::string *)> m_Method; // 0x38
					const rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > * m_Args; // 0x60
					scoped_refptr<CefMessageRouterBrowserSide::Callback> m_Callback; // 0x64
					~PendingQuery();
					PendingQuery();
				};
				public:
				boost::lockfree::queue<PendingQuery *> m_Queries; // 0x8
				std::unordered_map<std::string,std::function<enum Web::Browser::Bridge::QueryError __cdecl(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &,std::string *)>,std::hash<std::string>,std::equal_to<std::string>,std::allocator<std::pair<std::string const ,std::function<enum Web::Browser::Bridge::QueryError __cdecl(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &,std::string *)> > > > m_Methods; // 0x90
			public:
				WebRendererQueryHandler();
				virtual bool OnQuery(scoped_refptr<CefBrowser> browser, scoped_refptr<CefFrame> frame, long long queryId, CefStringBase<CefStringTraitsUTF16> const &request, bool persistent, scoped_refptr<CefMessageRouterBrowserSide::Callback> callback);
				virtual void OnQueryCanceled(scoped_refptr<CefBrowser> browser, scoped_refptr<CefFrame> frame, long long queryId);
				void AddMethod(std::string const &name, std::function<enum Web::Browser::Bridge::QueryError __cdecl(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &,std::string *)> const &method);
				void Update();
				virtual _inline ~WebRendererQueryHandler(); /* compiler_generated() */
			};
			static_assert(sizeof(Web::Browser::Bridge::WebRendererQueryHandler) == 184, "Invalid Web::Browser::Bridge::WebRendererQueryHandler size");
		}
	}
}

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
			_inline WebScreen(); /* compiler_generated() */
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
		_inline void WebScreen::OnCreate(Web::Browser::Bridge::WebRendererQueryHandler &queryHandler) // 0x10C7D930
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OnCreate@WebScreen@Ui@Web@@UAEXAAVWebRendererQueryHandler@Bridge@Browser@3@@Z");
			// Web::Browser::Bridge::WebRendererQueryHandler &queryHandler;
		}

		_inline void WebScreen::OnDestroy() // 0x10C7D970
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OnDestroy@WebScreen@Ui@Web@@UAEXXZ");
			// Web::Ui::WebScreen *const this;
		}

		_inline void WebScreen::OnShow() // 0x10C7DFF0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OnShow@WebScreen@Ui@Web@@UAEXXZ");
			// Web::Ui::WebScreen *const this;
		}

		_inline void WebScreen::OnHide() // 0x10C7DFB0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OnHide@WebScreen@Ui@Web@@UAEXXZ");
			// Web::Ui::WebScreen *const this;
		}

		_inline void WebScreen::OnUpdate() // 0x10C7E030
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OnUpdate@WebScreen@Ui@Web@@UAEXXZ");
			// Web::Ui::WebScreen *const this;
		}
	}
}

/* ---------- private code */

#endif // __WEB_UI_SCREEN_HPP__
