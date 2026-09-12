/* ---------- headers */

#include "Web/WebRenderHandlerCpu.hpp"
#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Forge/Magnets.hpp"
#include "Player/PlayerEmblemGenerator.hpp"
#include "Utils/Rectangle.hpp"
#include "Utils/Singleton.hpp"
#include "Web/Ui/ScreenLayer.hpp"
#include "Web/WebRenderHandlerOsr.hpp"

#include <base/cef_atomic_ref_count.h>
#include <base/cef_lock.h>
#include <base/cef_logging.h>
#include <base/cef_platform_thread.h>
#include <base/cef_ref_counted.h>
#include <base/cef_scoped_refptr.h>
#include <base/cef_thread_checker.h>
#include <base/internal/cef_lock_impl.h>
#include <boost/asio.hpp>
#include <boost/assert.hpp>
#include <boost/exception/all.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/parameter/aux_/use_default_tag.hpp>
#include <boost/throw_exception.hpp>
#include <cef_base.h>
#include <cef_devtools_message_observer.h>
#include <cef_extension_handler.h>
#include <cef_render_handler.h>
#include <d3dx9core.h>
#include <d3dx9math.h>
#include <d3dx9math.inl>
#include <internal/cef_string_wrappers.h>
#include <internal/cef_types_wrappers.h>
#include <internal/cef_win.h>

#include <Windows.h>
#include <boost/align/detail/align_up.hpp>
#include <boost/align/detail/is_alignment.hpp>
#include <boost/current_function.hpp>
#include <boost/mp11/algorithm.hpp>
#include <boost/mp11/detail/mp_count.hpp>
#include <boost/parameter/aux_/void.hpp>
#include <intsafe.h>
#include <roapi.h>
#include <roerrorapi.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <weakreference.h>
#include <wrl/client.h>
#include <wrl/event.h>
#include <wrl/implements.h>
#include <wrl/internal.h>
#include <wrl/module.h>
#include <wrl/wrappers/corewrappers.h>
#include <algorithm>
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
#include <memory>
#include <mutex>
#include <ostream>
#include <ratio>
#include <sstream>
#include <stdexcept>
#include <stop_token>
#include <streambuf>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

struct D3DXVECTOR3;
struct _D3DLOCKED_RECT;
struct begin;
struct end;
namespace Utils
{
	struct Rectangle;
}
namespace Web
{
	namespace Browser
	{
		class RenderHandlerCpu;
		class RenderHandlerOsr;
	}
}

namespace Utils {}
using namespace ::Utils;
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

namespace Windows {}
using namespace ::Windows;
namespace Windows
{
	namespace Foundation {}
	using namespace Windows::Foundation;
}

namespace Windows
{
	namespace Foundation
	{
		namespace Diagnostics {}
		using namespace Windows::Foundation::Diagnostics;
	}
}

namespace ABI {}
using namespace ::ABI;
namespace Web {}
using namespace ::Web;
namespace Web
{
	namespace Browser {}
	using namespace Web::Browser;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Web
{
	namespace Browser
	{
		extern RenderHandlerCpu* _sub_10CE7C90(Web::Browser::RenderHandlerCpu *const, IDirect3DDevice9 *, HWND__ *);
		RenderHandlerCpu::RenderHandlerCpu(IDirect3DDevice9 *device9, HWND__ *window) // 0x10CE7C90
		{
			mangled_x86(MANGLED_TODO, "??0RenderHandlerCpu@Browser@Web@@QAE@PAUIDirect3DDevice9@@PAUHWND__@@@Z");
			// HWND__ *window;
			todo("implement");
			_sub_10CE7C90(this, device9, window);
		}

		// mangled_x86(MANGLED_DEFAULT, "??0RenderHandlerOsr@Browser@Web@@QAE@XZ"); no body to assert in
		_inline RenderHandlerOsr::RenderHandlerOsr() = default; // 0x10CE80C0

		_extern void _sub_10CE95A0(Web::Browser::RenderHandlerCpu *const, scoped_refptr<CefBrowser>, CefRect const &);
		void RenderHandlerCpu::OnPopupSize(scoped_refptr<CefBrowser> browser, CefRect const &rect) // 0x10CE95A0
		{
			mangled_x86(MANGLED_TODO, "?OnPopupSize@RenderHandlerCpu@Browser@Web@@EAEXV?$scoped_refptr@VCefBrowser@@@@ABVCefRect@@@Z");
			// CefRect const &rect;
			todo("implement");
			_sub_10CE95A0(this, browser, rect);
		}

		_extern void _sub_10CE93E0(Web::Browser::RenderHandlerCpu *const, scoped_refptr<CefBrowser>, bool);
		void RenderHandlerCpu::OnPopupShow(scoped_refptr<CefBrowser> browser, bool show) // 0x10CE93E0
		{
			mangled_x86(MANGLED_TODO, "?OnPopupShow@RenderHandlerCpu@Browser@Web@@EAEXV?$scoped_refptr@VCefBrowser@@@@_N@Z");
			// bool show;
			// function call : scoped_refptr<CefBrowserHost> ()
			// function call : void (cef_paint_element_type_t)
			todo("implement");
			_sub_10CE93E0(this, browser, show);
		}

		_extern void _sub_10CE8D70(Web::Browser::RenderHandlerCpu *const, scoped_refptr<CefBrowser>, cef_paint_element_type_t, std::vector<CefRect> const &, void const *, __int32, __int32);
		void RenderHandlerCpu::OnPaint(scoped_refptr<CefBrowser> browser, cef_paint_element_type_t type, std::vector<CefRect> const &dirtyRects, void const *buffer, __int32 width, __int32 height) // 0x10CE8D70
		{
			mangled_x86(MANGLED_TODO, "?OnPaint@RenderHandlerCpu@Browser@Web@@EAEXV?$scoped_refptr@VCefBrowser@@@@W4cef_paint_element_type_t@@ABV?$vector@VCefRect@@V?$allocator@VCefRect@@@std@@@std@@PBXHH@Z");
			// static ...; // 0x10CE91D0
			// Web::Browser::RenderHandlerCpu *const this;
			// scoped_refptr<CefBrowser> browser;
			// cef_paint_element_type_t type;
			// std::vector<CefRect> const &dirtyRects;
			// void const *buffer;
			// __int32 width;
			// __int32 height;
			// std::lock_guard<std::mutex> lock;
			// __int32 stride;
			// Utils::Rectangle popupDirtyRect;
			{
				// std::vector<CefRect> const &<range>$L0;
				// CefRect const *<begin>$L0;
				// CefRect const *<end>$L0;
				{
					// CefRect const &dirtyRect;
					{
						// Utils::Rectangle srcRect;
						{
							// Utils::Rectangle popupScreenRect;
						}
					}
				}
			}
			{
				// __int32 popupStride;
				// Utils::Rectangle popupSrcRect;
			}
			todo("implement");
			_sub_10CE8D70(this, browser, type, dirtyRects, buffer, width, height);
		}

		_extern bool _sub_10CE9E50(Web::Browser::RenderHandlerCpu *const, unsigned __int32, unsigned __int32);
		bool RenderHandlerCpu::Resize(unsigned __int32 width, unsigned __int32 height) // 0x10CE9E50
		{
			mangled_x86(MANGLED_TODO, "?Resize@RenderHandlerCpu@Browser@Web@@UAE_NII@Z");
			// static ...; // 0x10CEA0C0
			// Web::Browser::RenderHandlerCpu *const this;
			// unsigned __int32 width;
			// unsigned __int32 height;
			// std::scoped_lock<std::mutex> lock;
			// unsigned __int32 textureDataSize;
			// function call : HRESULT (unsigned __int32, unsigned __int32, unsigned __int32, unsigned long, _D3DFORMAT, _D3DPOOL, IDirect3DTexture9 **, void **)
			todo("implement");
			bool __result = _sub_10CE9E50(this, width, height);
			return __result;
		}
	}
}

namespace Utils
{
	extern Rectangle _sub_10CE8950(Web::Browser::RenderHandlerCpu const *const);
}

namespace Web
{
	namespace Browser
	{
		Utils::Rectangle RenderHandlerCpu::GetTextureDirtyRect() const // 0x10CE8950
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetTextureDirtyRect@RenderHandlerCpu@Browser@Web@@ABE?AURectangle@Utils@@XZ");
			// Web::Browser::RenderHandlerCpu const *const this;

			return m_DirtyRect;
		}

		void RenderHandlerCpu::ResetTextureDirtyRect() // 0x10CE9DD0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ResetTextureDirtyRect@RenderHandlerCpu@Browser@Web@@AAEXXZ");
			// Web::Browser::RenderHandlerCpu *const this;

			m_DirtyRect = Utils::Rectangle();
		}

		void RenderHandlerCpu::OnPreResetDevice() // 0x10CE97D0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OnPreResetDevice@RenderHandlerCpu@Browser@Web@@UAEXXZ");
			// Web::Browser::RenderHandlerCpu *const this;
			// function call : HRESULT ()

			if (m_Sprite)
			{
				m_Sprite->OnLostDevice();
			}
		}

		void RenderHandlerCpu::OnPostResetDevice() // 0x10CE9720
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OnPostResetDevice@RenderHandlerCpu@Browser@Web@@UAEXXZ");
			// Web::Browser::RenderHandlerCpu *const this;
			// function call : HRESULT ()

			if (m_Sprite)
			{
				m_Sprite->OnResetDevice();
			}
		}

		_extern bool _sub_10CE99D0(Web::Browser::RenderHandlerCpu *const);
		bool RenderHandlerCpu::Render() // 0x10CE99D0
		{
			mangled_x86(MANGLED_TODO, "?Render@RenderHandlerCpu@Browser@Web@@UAE_NXZ");
			// static ...; // 0x10CE9CDE
			// static ...; // 0x10CE9CD9
			// static ...; // 0x10CE9CD0
			// static ...; // 0x10CE9CAC
			// static ...; // 0x10CE9CA4
			// Web::Browser::RenderHandlerCpu *const this;
			// std::unique_lock<std::mutex> lock;
			{
				// _D3DLOCKED_RECT rect;
				// HRESULT hr;
				{
					// Utils::Rectangle copyRect;
					// unsigned __int32 width;
					// unsigned __int32 height;
				}
			}
			// function call : HRESULT (unsigned __int32, _D3DLOCKED_RECT *, tagRECT const *, unsigned long)
			// function call : HRESULT (unsigned __int32)
			// function call : HRESULT (unsigned long)
			// function call : HRESULT (IDirect3DTexture9 *, tagRECT const *, D3DXVECTOR3 const *, D3DXVECTOR3 const *, unsigned long)
			// function call : HRESULT ()
			// function call : HRESULT ()
			todo("implement");
			bool __result = _sub_10CE99D0(this);
			return __result;
		}

		_extern bool _sub_10CE8B30(Web::Browser::RenderHandlerCpu *const);
		bool RenderHandlerCpu::InitRenderer() // 0x10CE8B30
		{
			mangled_x86(MANGLED_TODO, "?InitRenderer@RenderHandlerCpu@Browser@Web@@UAE_NXZ");
			// Web::Browser::RenderHandlerCpu *const this;
			// HRESULT hr;
			todo("implement");
			bool __result = _sub_10CE8B30(this);
			return __result;
		}
	}
}

/* ---------- private code */
