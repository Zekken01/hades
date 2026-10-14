#ifndef __WEB_WEBRENDERHANDLERCPU_HPP__
#define __WEB_WEBRENDERHANDLERCPU_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Forge/Magnets.hpp"
#include "Player/PlayerEmblemGenerator.hpp"
#include "Utils/Rectangle.hpp"
#include "Web/Ui/ScreenLayer.hpp"
#include "Web/WebRenderHandlerGpu.hpp"
#include "Web/WebRenderHandlerOsr.hpp"

#include <memory>
#include <mutex>
#include <vector>
#include <Windows.h>

/* ---------- forward declarations */

struct ID3DXSprite;
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

/* ---------- constants */

/* ---------- definitions */

namespace Web
{
	namespace Browser
	{
		class RenderHandlerCpu :
			public Web::Browser::RenderHandlerOsr,
			public virtual CefBaseRefCounted
		{
		public:
			RenderHandlerCpu(Web::Browser::RenderHandlerCpu &);
			RenderHandlerCpu(IDirect3DDevice9 *device9, HWND__ *window);
			Web::Browser::RenderHandlerCpu &operator=(Web::Browser::RenderHandlerCpu const &);
			virtual _inline ~RenderHandlerCpu() = default;
			virtual bool InitRenderer();
			virtual bool Resize(unsigned __int32 width, unsigned __int32 height);
			virtual void OnPreResetDevice();
			virtual void OnPostResetDevice();
			virtual bool Render();
			virtual _inline void Shutdown();
		private:
			virtual void OnPopupSize(scoped_refptr<CefBrowser> browser, CefRect const &rect);
			virtual void OnPopupShow(scoped_refptr<CefBrowser> browser, bool show);
			virtual void OnPaint(scoped_refptr<CefBrowser> browser, cef_paint_element_type_t type, std::vector<CefRect> const &dirtyRects, void const *buffer, __int32 width, __int32 height);
			void ResetTextureDirtyRect();
			Utils::Rectangle GetTextureDirtyRect() const;
			HWND__ *m_Window; // 0x8
			CefSize m_ViewSize; // 0xC
			Microsoft::WRL::ComPtr<IDirect3DDevice9> m_Device; // 0x1C
			Microsoft::WRL::ComPtr<IDirect3DTexture9> m_Texture; // 0x20
			Microsoft::WRL::ComPtr<ID3DXSprite> m_Sprite; // 0x24
			std::mutex m_TextureLock; // 0x28
			std::vector<unsigned char> m_TextureData; // 0x58
			unsigned __int32 m_TextureStride; // 0x68
			Utils::Rectangle m_DirtyRect; // 0x6C
			std::vector<unsigned char> m_PopupData; // 0x7C
			Utils::Rectangle m_PopupRect; // 0x8C
			bool m_PopupVisible; // 0x9C
			bool m_PopupValid; // 0x9D
			CefRefCount ref_count_; // 0xA0
		public:
			virtual _inline void AddRef() const;
			virtual _inline bool Release() const;
			virtual _inline bool HasOneRef() const;
			virtual _inline bool HasAtLeastOneRef() const;
		};
		static_assert(sizeof(Web::Browser::RenderHandlerCpu) == 172, "Invalid Web::Browser::RenderHandlerCpu size");
	}
}

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

namespace Web
{
	namespace Browser
	{


		_inline void RenderHandlerCpu::Shutdown() // 0x10CEA280
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Shutdown@RenderHandlerCpu@Browser@Web@@UAEXXZ");
			// Web::Browser::RenderHandlerCpu *const this;
		}

		_inline void RenderHandlerCpu::AddRef() const // 0x10CE8880
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?AddRef@RenderHandlerCpu@Browser@Web@@UBEXXZ");
			// __shifted(Web::Browser::RenderHandlerCpu, 168);
			// Web::Browser::RenderHandlerCpu const *const this;

			ref_count_.AddRef();
		}

		_inline bool RenderHandlerCpu::HasAtLeastOneRef() const // 0x10CE89B0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?HasAtLeastOneRef@RenderHandlerCpu@Browser@Web@@UBE_NXZ");
			// __shifted(Web::Browser::RenderHandlerCpu, 168);
			// Web::Browser::RenderHandlerCpu const *const this;

			return ref_count_.HasAtLeastOneRef();
		}

		_inline bool RenderHandlerCpu::HasOneRef() const // 0x10CE8A10
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?HasOneRef@RenderHandlerCpu@Browser@Web@@UBE_NXZ");
			// __shifted(Web::Browser::RenderHandlerCpu, 168);
			// Web::Browser::RenderHandlerCpu const *const this;

			return ref_count_.HasOneRef();
		}

		_inline bool RenderHandlerCpu::Release() const // 0x10CE9890
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Release@RenderHandlerCpu@Browser@Web@@UBE_NXZ");
			// __shifted(Web::Browser::RenderHandlerCpu, 168);
			// Web::Browser::RenderHandlerCpu const *const this;
			// function call : void *(unsigned __int32)

			if (ref_count_.Release())
			{
				delete static_cast<RenderHandlerCpu const *>(this);
				return true;
			}

			return false;
		}
	}
}

/* ---------- private code */

#endif // __WEB_WEBRENDERHANDLERCPU_HPP__
