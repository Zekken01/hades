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

#include "Utils/Logger.hpp"  // hades: added for 0x10CE8B30

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
		RenderHandlerCpu::RenderHandlerCpu(IDirect3DDevice9 *device9, HWND__ *window) : m_Window(window), m_Device(device9), m_Texture(nullptr), m_Sprite(nullptr), m_TextureStride(0), m_PopupVisible(false), m_PopupValid(false) /* hades-mem-init:  */ // 0x10CE7C90
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??0RenderHandlerCpu@Browser@Web@@QAE@PAUIDirect3DDevice9@@PAUHWND__@@@Z");

			#line 175 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Web\\WebRenderHandlerCpu.cpp"
			LOG_ASSERT(device9);
			LOG_ASSERT(window);
			#line 175 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Web\\WebRenderHandlerCpu.cpp"
		}

		// mangled_x86(MANGLED_DEFAULT, "??0RenderHandlerOsr@Browser@Web@@QAE@XZ"); no body to assert in

		void RenderHandlerCpu::OnPopupSize(scoped_refptr<CefBrowser> browser, CefRect const &rect) // 0x10CE95A0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OnPopupSize@RenderHandlerCpu@Browser@Web@@EAEXV?$scoped_refptr@VCefBrowser@@@@ABVCefRect@@@Z");

			m_PopupRect = Utils::Rectangle(rect.x, rect.y, rect.width, rect.height);
			m_PopupData.resize(rect.width * rect.height * 4);
			m_PopupValid = false;
		}

		void RenderHandlerCpu::OnPopupShow(scoped_refptr<CefBrowser> browser, bool show) // 0x10CE93E0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OnPopupShow@RenderHandlerCpu@Browser@Web@@EAEXV?$scoped_refptr@VCefBrowser@@@@_N@Z");

			m_PopupVisible = show;
			if (!show)
				browser->GetHost()->Invalidate(::PET_VIEW);
		}

		void RenderHandlerCpu::OnPaint(scoped_refptr<CefBrowser> browser, cef_paint_element_type_t type, std::vector<CefRect> const &dirtyRects, void const *buffer, __int32 width, __int32 height) // 0x10CE8D70
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OnPaint@RenderHandlerCpu@Browser@Web@@EAEXV?$scoped_refptr@VCefBrowser@@@@W4cef_paint_element_type_t@@ABV?$vector@VCefRect@@V?$allocator@VCefRect@@@std@@@std@@PBXHH@Z");

			if (m_TextureData.size() == 0)
				return;
			std::lock_guard<std::mutex> lock(m_TextureLock);
			__int32 stride = width * 4;
			Utils::Rectangle popupDirtyRect;
			for (CefRect const &dirtyRect : dirtyRects)
			{
				Utils::Rectangle srcRect(dirtyRect.x, dirtyRect.y, dirtyRect.width, dirtyRect.height);
				if (type == ::PET_VIEW)
				{
					Utils::Rectangle::Copy(m_TextureData.data(), dirtyRect.x, dirtyRect.y, m_TextureStride, buffer, srcRect, stride, 4);
					m_DirtyRect = m_DirtyRect.Add(srcRect);
					if (m_PopupVisible && m_PopupValid && srcRect.Intersects(m_PopupRect))
						popupDirtyRect = popupDirtyRect.Add(srcRect.Intersect(m_PopupRect));
				}
				else if (type == ::PET_POPUP)
				{
					Utils::Rectangle::Copy(m_PopupData.data(), dirtyRect.x, dirtyRect.y, stride, buffer, srcRect, stride, 4);
					m_PopupValid = true;
					if (m_PopupVisible)
					{
						Utils::Rectangle popupScreenRect = srcRect.Translate(m_PopupRect.X, m_PopupRect.Y);
						Utils::Rectangle::Copy(m_TextureData.data(), popupScreenRect.X, popupScreenRect.Y, m_TextureStride, buffer, srcRect, stride, 4);
						m_DirtyRect = m_DirtyRect.Add(popupScreenRect);
					}
				}
			}
			if (!popupDirtyRect.IsEmpty())
			{
				__int32 popupStride = m_PopupRect.Width * 4;
				Utils::Rectangle popupSrcRect = popupDirtyRect.Translate(-m_PopupRect.X, -m_PopupRect.Y);
				Utils::Rectangle::Copy(m_TextureData.data(), popupDirtyRect.X, popupDirtyRect.Y, m_TextureStride, m_PopupData.data(), popupSrcRect, popupStride, 4);
			}
		}

		bool RenderHandlerCpu::Resize(unsigned __int32 width, unsigned __int32 height) // 0x10CE9E50
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Resize@RenderHandlerCpu@Browser@Web@@UAE_NII@Z");

			m_ViewSize = CefSize(width, height);
			unsigned __int32 textureDataSize = width * height * 4;
			if (!textureDataSize)
				return false;

			Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Graphics, Utils::LogLevel::Info, "Web::Browser::RenderHandlerCpu::Resize:90 - Tried to allocate 0x%x bytes.", textureDataSize);
			std::scoped_lock<std::mutex> lock(m_TextureLock);
			m_TextureData.resize(textureDataSize);
			m_TextureStride = width * 4;
			std::fill(m_TextureData.begin(), m_TextureData.end(), 0);
			if (FAILED(m_Device->CreateTexture(width, height, 1, D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_Texture, NULL)))
				return false;
			return true;
		}
	}
}

namespace Utils
{

}

namespace Web
{
	namespace Browser
	{
		Utils::Rectangle RenderHandlerCpu::GetTextureDirtyRect() const // 0x10CE8950
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetTextureDirtyRect@RenderHandlerCpu@Browser@Web@@ABE?AURectangle@Utils@@XZ");

			return m_DirtyRect;
		}

		void RenderHandlerCpu::ResetTextureDirtyRect() // 0x10CE9DD0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ResetTextureDirtyRect@RenderHandlerCpu@Browser@Web@@AAEXXZ");

			m_DirtyRect = Utils::Rectangle();
		}

		void RenderHandlerCpu::OnPreResetDevice() // 0x10CE97D0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OnPreResetDevice@RenderHandlerCpu@Browser@Web@@UAEXXZ");

			if (m_Sprite)
			{
				m_Sprite->OnLostDevice();
			}
		}

		void RenderHandlerCpu::OnPostResetDevice() // 0x10CE9720
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OnPostResetDevice@RenderHandlerCpu@Browser@Web@@UAEXXZ");

			if (m_Sprite)
			{
				m_Sprite->OnResetDevice();
			}
		}

		bool RenderHandlerCpu::Render() // 0x10CE99D0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Render@RenderHandlerCpu@Browser@Web@@UAE_NXZ");

			std::unique_lock<std::mutex> lock(m_TextureLock);
			if (!m_Texture)
				return false;
			if (!GetTextureDirtyRect().IsEmpty())
			{
				_D3DLOCKED_RECT rect;
				HRESULT hr = m_Texture->LockRect(0, &rect, nullptr, D3DLOCK_DISCARD);
				if (SUCCEEDED(hr))
				{
					unsigned __int32 width = m_ViewSize.width;
					unsigned __int32 height = m_ViewSize.height;
					Utils::Rectangle copyRect(0, 0, width, height);
					Utils::Rectangle::Copy(rect.pBits, 0, 0, rect.Pitch, m_TextureData.data(), copyRect, width * 4, 4);
					m_Texture->UnlockRect(0);
					ResetTextureDirtyRect();
				}
			}
			lock.unlock();
			m_Sprite->Begin(D3DXSPRITE_ALPHABLEND);
			m_Sprite->Draw(m_Texture.Get(), nullptr, nullptr, nullptr, 0xFFFFFFFF);
			m_Sprite->Flush();
			m_Sprite->End();
			return true;
		}

		bool RenderHandlerCpu::InitRenderer() // 0x10CE8B30
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?InitRenderer@RenderHandlerCpu@Browser@Web@@UAE_NXZ");

			HRESULT hr = D3DXCreateSprite(m_Device.Get(), &m_Sprite);
			if (FAILED(hr))
			{
				Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Graphics, Utils::LogLevel::Info, "Web::Browser::RenderHandlerCpu::InitRenderer:170 - Could not create sprite (%x).", hr);
				return false;
			}
			return true;
		}
	}
}

/* ---------- private code */
