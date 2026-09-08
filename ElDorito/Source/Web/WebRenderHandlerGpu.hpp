#ifndef __WEB_WEBRENDERHANDLERGPU_HPP__
#define __WEB_WEBRENDERHANDLERGPU_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Download/HttpFileDownload.hpp"
#include "Forge/Magnets.hpp"
#include "Player/PlayerEmblemGenerator.hpp"
#include "Utils/Rectangle.hpp"
#include "Web/Ui/ScreenLayer.hpp"
#include "Web/WebRenderHandlerOsr.hpp"

#include <atomic>
#include <memory>
#include <vector>
#include <Windows.h>

/* ---------- forward declarations */

namespace Utils
{
	struct Rectangle;
}
namespace Web
{
	namespace Browser
	{
		class RenderHandlerGpu;
		class RenderHandlerOsr;
	}
}

/* ---------- constants */

/* ---------- definitions */

namespace Web
{
	namespace Browser
	{
		class RenderHandlerGpu :
			public Web::Browser::RenderHandlerOsr,
			public virtual CefBaseRefCounted
		{
		public:
			public:
			class GpuAcceleratedSurface
			{
			public:
				_inline void OnAcceleratedPaint(void *sharedHandle);
				_inline IDirect3DTexture9 *GetTexture(IDirect3DDevice9 *device);
				_inline void Reset();
				_inline void Resize(unsigned __int32 width, unsigned __int32 height);
			private:
				bool m_didResize; // 0x0
				unsigned char __pad0[3]; // 0x1
				void *m_handle; // 0x4
				std::atomic<void *> m_nextHandle; // 0x8
				CefSize m_size; // 0xC
				Microsoft::WRL::ComPtr<IDirect3DTexture9> m_texture; // 0x1C
			public:
				_inline GpuAcceleratedSurface(); /* compiler_generated() */
				_inline ~GpuAcceleratedSurface(); /* compiler_generated() */
			};
			static_assert(sizeof(GpuAcceleratedSurface) == 32, "Invalid GpuAcceleratedSurface size");
			public:
			RenderHandlerGpu(Web::Browser::RenderHandlerGpu &);
			RenderHandlerGpu(IDirect3DDevice9 *device9, HWND__ *window);
			Web::Browser::RenderHandlerGpu &operator=(Web::Browser::RenderHandlerGpu const &);
			virtual _inline ~RenderHandlerGpu();
			virtual bool InitRenderer();
			virtual bool Resize(unsigned __int32 width, unsigned __int32 height);
			virtual void OnPreResetDevice();
			virtual void OnPostResetDevice();
			virtual bool Render();
			virtual void Shutdown();
		private:
			virtual void OnPopupShow(scoped_refptr<CefBrowser> browser, bool show);
			virtual void OnPopupSize(scoped_refptr<CefBrowser> browser, CefRect const &rect);
			virtual void OnAcceleratedPaint(scoped_refptr<CefBrowser> browser, cef_paint_element_type_t type, std::vector<CefRect> const &dirtyRects, void *sharedHandle);
			_inline bool PopupIsVisible() const;
			HWND__ *m_Window; // 0x8
			CefSize m_ViewSize; // 0xC
			Microsoft::WRL::ComPtr<IDirect3DDevice9> m_Device; // 0x1C
			Microsoft::WRL::ComPtr<IDirect3DVertexDeclaration9> m_VertexDeclaration; // 0x20
			Microsoft::WRL::ComPtr<IDirect3DVertexShader9> m_VertexShader; // 0x24
			Microsoft::WRL::ComPtr<IDirect3DPixelShader9> m_PixelShader; // 0x28
			bool m_PopupVisible; // 0x2C
			bool m_PopupValid; // 0x2D
			Utils::Rectangle m_PopupRect; // 0x30
			__int32 m_GpuBufferCount; // 0x40
			bool m_GpuVsyncEnable; // 0x44
			void *m_GpuWaitEvent; // 0x48
			std::unique_ptr<GpuAcceleratedSurface> m_ViewSurface; // 0x4C
			std::unique_ptr<GpuAcceleratedSurface> m_PopupSurface; // 0x50
			CefRefCount ref_count_; // 0x54
		public:
			virtual _inline void AddRef() const;
			virtual _inline bool Release() const;
			virtual _inline bool HasOneRef() const;
			virtual _inline bool HasAtLeastOneRef() const;
		};
		static_assert(sizeof(Web::Browser::RenderHandlerGpu) == 96, "Invalid Web::Browser::RenderHandlerGpu size");
	}
}

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

namespace Web
{
	namespace Browser
	{
		_extern void _sub_10CEB0B0(Web::Browser::RenderHandlerGpu * const);
		_inline RenderHandlerGpu::~RenderHandlerGpu() // 0x10CEB0B0
		{
			mangled_x86(MANGLED_TODO, "??1RenderHandlerGpu@Browser@Web@@UAE@XZ");
			// __shifted(Web::Browser::RenderHandlerGpu, 92);
			// Web::Browser::RenderHandlerGpu *const this;
			todo("implement");
			_sub_10CEB0B0(this);
		}

		_inline bool RenderHandlerGpu::PopupIsVisible() const // 0x10CEC6B0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?PopupIsVisible@RenderHandlerGpu@Browser@Web@@ABE_NXZ");
			// Web::Browser::RenderHandlerGpu const *const this;

			return m_PopupVisible;
		}

		_extern void _sub_10CEB620(CefBaseRefCounted * const);
		_inline void RenderHandlerGpu::AddRef() const // 0x10CEB620
		{
			mangled_x86(MANGLED_TODO, "?AddRef@RenderHandlerGpu@Browser@Web@@UBEXXZ");
			// __shifted(Web::Browser::RenderHandlerGpu, 92);
			// Web::Browser::RenderHandlerGpu const *const this;
			todo("implement");
			_sub_10CEB620((CefBaseRefCounted *)this);
		}

		_extern bool _sub_10CEB8B0(CefBaseRefCounted * const);
		_inline bool RenderHandlerGpu::HasAtLeastOneRef() const // 0x10CEB8B0
		{
			mangled_x86(MANGLED_TODO, "?HasAtLeastOneRef@RenderHandlerGpu@Browser@Web@@UBE_NXZ");
			// __shifted(Web::Browser::RenderHandlerGpu, 92);
			// Web::Browser::RenderHandlerGpu const *const this;
			todo("implement");
			bool __result = _sub_10CEB8B0((CefBaseRefCounted *)this);
			return __result;
		}

		_extern bool _sub_10CEB910(CefBaseRefCounted * const);
		_inline bool RenderHandlerGpu::HasOneRef() const // 0x10CEB910
		{
			mangled_x86(MANGLED_TODO, "?HasOneRef@RenderHandlerGpu@Browser@Web@@UBE_NXZ");
			// __shifted(Web::Browser::RenderHandlerGpu, 92);
			// Web::Browser::RenderHandlerGpu const *const this;
			todo("implement");
			bool __result = _sub_10CEB910((CefBaseRefCounted *)this);
			return __result;
		}

		_extern bool _sub_10CEC6E0(CefBaseRefCounted * const);
		_inline bool RenderHandlerGpu::Release() const // 0x10CEC6E0
		{
			mangled_x86(MANGLED_TODO, "?Release@RenderHandlerGpu@Browser@Web@@UBE_NXZ");
			// __shifted(Web::Browser::RenderHandlerGpu, 92);
			// Web::Browser::RenderHandlerGpu const *const this;
			// function call : void *(unsigned __int32)
			todo("implement");
			bool __result = _sub_10CEC6E0((CefBaseRefCounted *)this);
			return __result;
		}
	}
}

/* ---------- private code */

#endif // __WEB_WEBRENDERHANDLERGPU_HPP__
