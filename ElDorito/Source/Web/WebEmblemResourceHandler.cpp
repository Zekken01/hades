/* ---------- headers */

#include "Web/WebEmblemResourceHandler.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/game/player_appearance.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Player/PlayerEmblemRenderer.hpp"
#include "Utils/NameValueTable.hpp"

#include <base/cef_atomic_ref_count.h>
#include <base/cef_lock.h>
#include <base/cef_logging.h>
#include <base/cef_platform_thread.h>
#include <base/cef_ref_counted.h>
#include <base/cef_scoped_refptr.h>
#include <base/cef_thread_checker.h>
#include <base/internal/cef_lock_impl.h>
#include <cef_base.h>
#include <cef_devtools_message_observer.h>
#include <cef_extension_handler.h>
#include <cef_resource_handler.h>
#include <internal/cef_string_wrappers.h>
#include <internal/cef_types_wrappers.h>
#include <internal/cef_win.h>
#include <wrapper/cef_stream_resource_handler.h>

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <atomic>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <functional>
#include <ios>
#include <iosfwd>
#include <iterator>
#include <limits>
#include <map>
#include <memory>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <system_error>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>

/* ---------- forward declarations */

class CefCallback;
struct CefStringTraitsUTF16;
struct s_player_emblem_configuration;
namespace Player
{
	namespace Emblems
	{
		class IPlayerEmblemRenderCallbacks;
		class IPlayerEmblemStream;
		struct PlayerEmblemRenderMetadata;
	}
}
namespace Web
{
	namespace Browser
	{
		class WebEmblemRenderHandler;
		class WebEmblemResourceHandler;
	}
}

namespace base {}
using namespace ::base;
namespace base
{
	namespace cef_subtle {}
	using namespace base::cef_subtle;
	namespace cef_internal {}
	using namespace base::cef_internal;
	namespace internal {}
	using namespace base::internal;
}

namespace Player {}
using namespace ::Player;
namespace Player
{
	namespace Emblems {}
	using namespace Player::Emblems;
}

namespace Web {}
using namespace ::Web;
namespace Web
{
	namespace Browser {}
	using namespace Web::Browser;
}

/* ---------- constants */

/* ---------- definitions */

namespace Web
{
	namespace Browser
	{
		// hades: moved from hades/recovered_types.h onto its real base (was hades::polymorphic_bytes)
		struct WebEmblemRenderHandler :
			public Player::Emblems::IPlayerEmblemRenderCallbacks
		{
			// mangled_x86(MANGLED_KNOWN_GOOD, "??1WebEmblemRenderHandler@Browser@Web@@UAE@XZ"); defaulted on its declaration
			virtual ~WebEmblemRenderHandler() = default; // 0x10c83020
			virtual void OnRenderStart(Player::Emblems::PlayerEmblemRenderMetadata const &, std::shared_ptr<Player::Emblems::IPlayerEmblemStream>);
			virtual void OnRenderComplete();
			virtual void OnRenderDataAvailable();
			std::shared_ptr<Player::Emblems::IPlayerEmblemStream> m_stream; // 0x4
			Player::Emblems::PlayerEmblemRenderMetadata m_metadata; // 0xC
			scoped_refptr<CefCallback> m_cefContinuation; // 0x28
		public:
			__int64 GetLength() const;
			Player::Emblems::IPlayerEmblemStream *GetStream();
			WebEmblemRenderHandler(scoped_refptr<CefCallback>);
			void SetCefContinuation(scoped_refptr<CefCallback>);
			std::string const GetMimeType() const;
		public:
			WebEmblemRenderHandler();
		};
		static_assert32(sizeof(WebEmblemRenderHandler) == 44, "Invalid WebEmblemRenderHandler size");
	}
}

// Web::Browser::WebEmblemRenderHandler is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

/* ---------- prototypes */

namespace Player { namespace Emblems { extern bool ParseURL(std::string const &url, s_player_emblem_configuration &config); } }  // hades: added for 0x10C84460  // hades: added for 0x10C84460

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Web
{
	namespace Browser
	{
		_inline WebEmblemRenderHandler::WebEmblemRenderHandler(scoped_refptr<CefCallback> callback) : m_cefContinuation(callback) /* hades-mem-init:  */ // 0x10C826F0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??0WebEmblemRenderHandler@Browser@Web@@QAE@V?$scoped_refptr@VCefCallback@@@@@Z");
			// scoped_refptr<CefCallback> callback;
		}

	}
}

namespace Player
{
	namespace Emblems
	{
		// mangled_x86(MANGLED_DEFAULT, "??4PlayerEmblemRenderMetadata@Emblems@Player@@QAEAAU012@ABU012@@Z"); no body to assert in
		_inline Player::Emblems::PlayerEmblemRenderMetadata &PlayerEmblemRenderMetadata::operator=(Player::Emblems::PlayerEmblemRenderMetadata const &__that) = default; // 0x10C832C0
	}
}

namespace Web
{
	namespace Browser
	{
		_inline void WebEmblemRenderHandler::OnRenderComplete() // 0x10C842D0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OnRenderComplete@WebEmblemRenderHandler@Browser@Web@@UAEXXZ");
			// Web::Browser::WebEmblemRenderHandler *const this;
		}

		_inline void WebEmblemRenderHandler::OnRenderDataAvailable() // 0x10C842F0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OnRenderDataAvailable@WebEmblemRenderHandler@Browser@Web@@UAEXXZ");
			// Web::Browser::WebEmblemRenderHandler *const this;
			// function call : void ()

			m_cefContinuation->Continue();
		}

		_inline void WebEmblemRenderHandler::SetCefContinuation(scoped_refptr<CefCallback> callback) // 0x10C84DD0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?SetCefContinuation@WebEmblemRenderHandler@Browser@Web@@QAEXV?$scoped_refptr@VCefCallback@@@@@Z");
			// scoped_refptr<CefCallback> callback;

			m_cefContinuation = callback;
		}
	}
}


namespace Web
{
	namespace Browser
	{
		_inline std::string const WebEmblemRenderHandler::GetMimeType() const // 0x10C83F20
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetMimeType@WebEmblemRenderHandler@Browser@Web@@QBE?BV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
			// Web::Browser::WebEmblemRenderHandler const *const this;

			return m_metadata.mimeType;
		}

		_inline long long WebEmblemRenderHandler::GetLength() const // 0x10C83EF0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetLength@WebEmblemRenderHandler@Browser@Web@@QBE_JXZ");
			// Web::Browser::WebEmblemRenderHandler const *const this;

			return -1;
		}
	}
}

namespace Player
{
	namespace Emblems
	{
		// mangled_x86(MANGLED_DEFAULT, "??0IPlayerEmblemRenderCallbacks@Emblems@Player@@QAE@XZ"); no body to assert in
	}
}

namespace Web
{
	namespace Browser
	{
		bool WebEmblemResourceHandler::ProcessRequest(scoped_refptr<CefRequest> request, scoped_refptr<CefCallback> callback) // 0x10C84460
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ProcessRequest@WebEmblemResourceHandler@Browser@Web@@UAE_NV?$scoped_refptr@VCefRequest@@@@V?$scoped_refptr@VCefCallback@@@@@Z");
			// static ...; // 0x10C84933
			// static ...; // 0x10C8492F
			// static ...; // 0x10C84928
			// static ...; // 0x10C848EC
			// static ...; // 0x10C848E4
			// Web::Browser::WebEmblemResourceHandler *const this;
			// scoped_refptr<CefRequest> request;
			// scoped_refptr<CefCallback> callback;
			// std::_Tree_iterator<std::_Tree_val<std::_Tree_simple_types<std::pair<CefStringBase<CefStringTraitsUTF16> const ,CefStringBase<CefStringTraitsUTF16> > > > > it;
			// s_player_emblem_configuration config;
			// std::multimap<CefStringBase<CefStringTraitsUTF16>,CefStringBase<CefStringTraitsUTF16> > requestHeaders;
			// std::string url;
			// CefStringBase<CefStringTraitsUTF16> origin;
			// function call : void (std::multimap<CefStringBase<CefStringTraitsUTF16>,CefStringBase<CefStringTraitsUTF16> > &)
			// function call : CefStringBase<CefStringTraitsUTF16> ()
			// function call : void ()

			std::multimap<CefString,CefString> requestHeaders;
			request->GetHeaderMap(requestHeaders);
			CefString origin = "";
			auto it = requestHeaders.find("Origin");
			if (it != requestHeaders.end())
				origin = it->second;
			m_responseHeaders.insert(std::make_pair("Access-Control-Allow-Origin", origin));
			m_responseHeaders.insert(std::make_pair("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept"));
			std::string url = request->GetURL();
			s_player_emblem_configuration config;
			if (!Player::Emblems::ParseURL(url, config))
				config = {};
			m_emblemRender = std::make_shared<WebEmblemRenderHandler>(callback);
			if (!Player::Emblems::PlayerEmblemRenderer::StartRender(config, m_emblemRender))
			{
				m_emblemRender = nullptr;
				callback->Continue();
			}
			return true;
		}

		void WebEmblemResourceHandler::GetResponseHeaders(scoped_refptr<CefResponse> response, long long &response_length, CefStringBase<CefStringTraitsUTF16> &redirectUrl) // 0x10C83FA0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetResponseHeaders@WebEmblemResourceHandler@Browser@Web@@UAEXV?$scoped_refptr@VCefResponse@@@@AA_JAAV?$CefStringBase@UCefStringTraitsUTF16@@@@@Z");
			// CefStringBase<CefStringTraitsUTF16> &redirectUrl;
			// function call : void (std::multimap<CefStringBase<CefStringTraitsUTF16>,CefStringBase<CefStringTraitsUTF16> > const &)
			// function call : void (__int32)
			// function call : void (CefStringBase<CefStringTraitsUTF16> const &)
			// function call : void (__int32)

			response->SetHeaderMap(m_responseHeaders);
			if (m_emblemRender != nullptr)
			{
				response->SetStatus(200);
				response->SetMimeType(m_emblemRender->GetMimeType());
				response_length = m_emblemRender->GetLength();
			}
			else
			{
				response->SetStatus(500);
				response_length = 0;
			}
		}

		bool WebEmblemResourceHandler::ReadResponse(void *data_out, __int32 bytes_to_read, __int32 &bytes_read, scoped_refptr<CefCallback> callback) // 0x10C84A90
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ReadResponse@WebEmblemResourceHandler@Browser@Web@@UAE_NPAXHAAHV?$scoped_refptr@VCefCallback@@@@@Z");
			// scoped_refptr<CefCallback> callback;
			// Player::Emblems::IPlayerEmblemStream *stream;
			// function call : bool (void *, __int32, __int32 *)
			// function call : void ()

			Player::Emblems::IPlayerEmblemStream *stream = m_emblemRender->GetStream();
			if (stream)
			{
				if (!stream->Read(data_out, bytes_to_read, &bytes_read))
				{
					bytes_read = 0;
					callback->Cancel();
					return true;
				}
				if (!bytes_read)
					return false;
			}
			else
				bytes_read = 0;
			m_emblemRender->SetCefContinuation(callback);
			return true;
		}

		void WebEmblemResourceHandler::Cancel() // 0x10C83E20
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Cancel@WebEmblemResourceHandler@Browser@Web@@UAEXXZ");
			// Web::Browser::WebEmblemResourceHandler *const this;
		}
	}
}

/* ---------- private code */

namespace Web
{
	namespace Browser
	{
		Player::Emblems::IPlayerEmblemStream *WebEmblemRenderHandler::GetStream() // 0x10C84250
		{

					return m_stream.get();
		}
	}
}

// hades: OnRenderStart was dropped from the tree (an orphaned member); it sits at the
// end of the file so the functions above keep their line numbers.
namespace Web
{
	namespace Browser
	{
		void WebEmblemRenderHandler::OnRenderStart(Player::Emblems::PlayerEmblemRenderMetadata const &metadata, std::shared_ptr<Player::Emblems::IPlayerEmblemStream> stream) // 0x10C84370
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OnRenderStart@WebEmblemRenderHandler@Browser@Web@@UAEXABUPlayerEmblemRenderMetadata@Emblems@Player@@V?$shared_ptr@VIPlayerEmblemStream@Emblems@Player@@@std@@@Z");

			m_metadata = metadata;
			m_stream = stream;
			m_cefContinuation->Continue();
		}
	}
}
