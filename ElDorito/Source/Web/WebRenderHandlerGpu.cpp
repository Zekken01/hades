/* ---------- headers */

#include "Web/WebRenderHandlerGpu.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/rasterizer/rasterizer.hpp"
#include "Blam/rasterizer/rasterizer_geometry.hpp"
#include "Blam/rasterizer/rasterizer_samplers.hpp"
#include "Blam/rasterizer/rasterizer_shaders.hpp"
#include "Blam/rasterizer/rasterizer_states.hpp"
#include "Blam/rasterizer/rasterizers_textures_cache.hpp"
#include "Blam/shaders/render_method_submit.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Forge/Magnets.hpp"
#include "Modules/ModuleGraphics.hpp"
#include "Player/PlayerEmblemGenerator.hpp"
#include "Utils/Rectangle.hpp"
#include "Utils/Singleton.hpp"
#include "Web/Ui/ScreenLayer.hpp"
#include "Web/WebRendererShader.hpp"
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
#include <Windows.h>

/* ---------- forward declarations */

struct ID3D10Blob;
struct ID3DInclude;
struct _D3DVERTEXELEMENT9;
struct _D3D_SHADER_MACRO;
struct c_rasterizer_samplers;
struct c_rasterizer_texture_ref;
struct real_vector4d;
namespace Modules
{
	class ModuleGraphics;
}
namespace Utils
{
	struct Rectangle;
}
namespace Web
{
	namespace Browser
	{
		class RenderHandlerGpu;
		struct SCefScreenVertex;
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

namespace Modules {}
using namespace ::Modules;
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

typedef real_vector4d vector_4d;

/* ---------- prototypes */

/* ---------- globals */

char *c_rasterizer_samplers::sampler_srgb_states; // 0x113555D4

/* ---------- private variables */

namespace Web
{
	namespace Browser
	{
		namespace hades_file_local_Web_Browser
		{
			extern char const *WebRendererHlsl; // 0x11355590
		}
		using namespace hades_file_local_Web_Browser;
	}
}
/* ---------- public code */

namespace Web
{
	namespace Browser
	{
		_extern void _sub_10CEC270(Web::Browser::RenderHandlerGpu::GpuAcceleratedSurface *const, void *);
		_inline void RenderHandlerGpu::GpuAcceleratedSurface::OnAcceleratedPaint(void *sharedHandle) // 0x10CEC270
		{
			mangled_x86(MANGLED_TODO, "?OnAcceleratedPaint@GpuAcceleratedSurface@RenderHandlerGpu@Browser@Web@@QAEXPAX@Z");
			// void *sharedHandle;
			{
				// void **wrappedHandle;
			}
			// function call : void *(void *, unsigned long, unsigned long, unsigned long, unsigned long)
			// function call : __int32 (void const *)
			todo("implement");
			_sub_10CEC270(this, sharedHandle);
		}
	}
}

extern IDirect3DTexture9 *_sub_10CEB700(Web::Browser::RenderHandlerGpu::GpuAcceleratedSurface *const, IDirect3DDevice9 *);
namespace Web
{
	namespace Browser
	{
		_inline IDirect3DTexture9 *RenderHandlerGpu::GpuAcceleratedSurface::GetTexture(IDirect3DDevice9 *device) // 0x10CEB700
		{
			mangled_x86(MANGLED_TODO, "?GetTexture@GpuAcceleratedSurface@RenderHandlerGpu@Browser@Web@@QAEPAUIDirect3DTexture9@@PAUIDirect3DDevice9@@@Z");
			// IDirect3DDevice9 *device;
			// void *nextHandle;
			{
				// HRESULT hr;
			}
			// function call : HRESULT (unsigned __int32, unsigned __int32, unsigned __int32, unsigned long, _D3DFORMAT, _D3DPOOL, IDirect3DTexture9 **, void **)
			todo("implement");
			IDirect3DTexture9 * __result = _sub_10CEB700(this, device);
			return __result;
		}

		_extern void _sub_10CED360(Web::Browser::RenderHandlerGpu::GpuAcceleratedSurface *const);
		_inline void RenderHandlerGpu::GpuAcceleratedSurface::Reset() // 0x10CED360
		{
			mangled_x86(MANGLED_TODO, "?Reset@GpuAcceleratedSurface@RenderHandlerGpu@Browser@Web@@QAEXXZ");
			// Web::Browser::RenderHandlerGpu::GpuAcceleratedSurface *const this;
			todo("implement");
			_sub_10CED360(this);
		}

		_extern void _sub_10CED3C0(Web::Browser::RenderHandlerGpu::GpuAcceleratedSurface *const, unsigned __int32, unsigned __int32);
		_inline void RenderHandlerGpu::GpuAcceleratedSurface::Resize(unsigned __int32 width, unsigned __int32 height) // 0x10CED3C0
		{
			mangled_x86(MANGLED_TODO, "?Resize@GpuAcceleratedSurface@RenderHandlerGpu@Browser@Web@@QAEXII@Z");
			// unsigned __int32 height;
			todo("implement");
			_sub_10CED3C0(this, width, height);
		}

		extern RenderHandlerGpu* _sub_10CEAAB0(Web::Browser::RenderHandlerGpu *const, IDirect3DDevice9 *, HWND__ *);
		RenderHandlerGpu::RenderHandlerGpu(IDirect3DDevice9 *device9, HWND__ *window) // 0x10CEAAB0
		{
			mangled_x86(MANGLED_TODO, "??0RenderHandlerGpu@Browser@Web@@QAE@PAUIDirect3DDevice9@@PAUHWND__@@@Z");
			// HWND__ *window;
			todo("implement");
			_sub_10CEAAB0(this, device9, window);
		}

		// mangled_x86(MANGLED_DEFAULT, "??1GpuAcceleratedSurface@RenderHandlerGpu@Browser@Web@@QAE@XZ"); no body to assert in
		_inline RenderHandlerGpu::GpuAcceleratedSurface::~GpuAcceleratedSurface() = default; // 0x10CEB050

		_extern void _sub_10CEC410(Web::Browser::RenderHandlerGpu *const, scoped_refptr<CefBrowser>, bool);
		void RenderHandlerGpu::OnPopupShow(scoped_refptr<CefBrowser> browser, bool show) // 0x10CEC410
		{
			mangled_x86(MANGLED_TODO, "?OnPopupShow@RenderHandlerGpu@Browser@Web@@EAEXV?$scoped_refptr@VCefBrowser@@@@_N@Z");
			// bool show;
			todo("implement");
			_sub_10CEC410(this, browser, show);
		}

		_extern void _sub_10CEC470(Web::Browser::RenderHandlerGpu *const, scoped_refptr<CefBrowser>, CefRect const &);
		void RenderHandlerGpu::OnPopupSize(scoped_refptr<CefBrowser> browser, CefRect const &rect) // 0x10CEC470
		{
			mangled_x86(MANGLED_TODO, "?OnPopupSize@RenderHandlerGpu@Browser@Web@@EAEXV?$scoped_refptr@VCefBrowser@@@@ABVCefRect@@@Z");
			// static ...; // 0x10CEC5A8
			// Web::Browser::RenderHandlerGpu *const this;
			// scoped_refptr<CefBrowser> browser;
			// CefRect const &rect;
			// Utils::Rectangle newRect;
			todo("implement");
			_sub_10CEC470(this, browser, rect);
		}

		_extern void _sub_10CEC320(Web::Browser::RenderHandlerGpu *const, scoped_refptr<CefBrowser>, cef_paint_element_type_t, std::vector<CefRect> const &, void *);
		void RenderHandlerGpu::OnAcceleratedPaint(scoped_refptr<CefBrowser> browser, cef_paint_element_type_t type, std::vector<CefRect> const &dirtyRects, void *sharedHandle) // 0x10CEC320
		{
			mangled_x86(MANGLED_TODO, "?OnAcceleratedPaint@RenderHandlerGpu@Browser@Web@@EAEXV?$scoped_refptr@VCefBrowser@@@@W4cef_paint_element_type_t@@ABV?$vector@VCefRect@@V?$allocator@VCefRect@@@std@@@std@@PAX@Z");
			// void *sharedHandle;
			todo("implement");
			_sub_10CEC320(this, browser, type, dirtyRects, sharedHandle);
		}

		_extern bool _sub_10CED4B0(Web::Browser::RenderHandlerGpu *const, unsigned __int32, unsigned __int32);
		bool RenderHandlerGpu::Resize(unsigned __int32 width, unsigned __int32 height) // 0x10CED4B0
		{
			mangled_x86(MANGLED_TODO, "?Resize@RenderHandlerGpu@Browser@Web@@UAE_NII@Z");
			// unsigned __int32 height;
			todo("implement");
			bool __result = _sub_10CED4B0(this, width, height);
			return __result;
		}

		_extern void _sub_10CEC640(Web::Browser::RenderHandlerGpu *const);
		void RenderHandlerGpu::OnPreResetDevice() // 0x10CEC640
		{
			mangled_x86(MANGLED_TODO, "?OnPreResetDevice@RenderHandlerGpu@Browser@Web@@UAEXXZ");
			// Web::Browser::RenderHandlerGpu *const this;
			todo("implement");
			_sub_10CEC640(this);
		}

		void RenderHandlerGpu::OnPostResetDevice() // 0x10CEC620
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OnPostResetDevice@RenderHandlerGpu@Browser@Web@@UAEXXZ");
			// Web::Browser::RenderHandlerGpu *const this;
		}

		_extern bool _sub_10CEB960(Web::Browser::RenderHandlerGpu *const);
		bool RenderHandlerGpu::InitRenderer() // 0x10CEB960
		{
			mangled_x86(MANGLED_TODO, "?InitRenderer@RenderHandlerGpu@Browser@Web@@UAE_NXZ");
			// static ...; // 0x10CEBE98
			// static ...; // 0x10CEBE8E
			// static ...; // 0x10CEBE84
			// static ...; // 0x10CEBE60
			// static ...; // 0x10CEBE58
			// Web::Browser::RenderHandlerGpu *const this;
			// ID3D10Blob *vs_source;
			// ID3D10Blob *ps_source;
			// HRESULT ps_result;
			// bool const &g_d3d9ex;
			// HRESULT vd_result;
			// HRESULT vs_result;
			// HINSTANCE__ *lib;
			// _D3DVERTEXELEMENT9 elements[3];
			// HRESULT (*D3DCompile_)(void const *, unsigned long, char const *, _D3D_SHADER_MACRO const *, ID3DInclude *, char const *, char const *, unsigned __int32, unsigned __int32, ID3D10Blob **, ID3D10Blob **);
			// function call : HINSTANCE__ *(char const *)
			// function call : __int32 (*(HINSTANCE__ *, char const *))()
			// function call : HRESULT (_D3DVERTEXELEMENT9 const *, IDirect3DVertexDeclaration9 **)
			// function call : HRESULT (*)(void const *, unsigned long, char const *, _D3D_SHADER_MACRO const *, ID3DInclude *, char const *, char const *, unsigned __int32, unsigned __int32, ID3D10Blob **, ID3D10Blob **)
			// function call : HRESULT (*)(void const *, unsigned long, char const *, _D3D_SHADER_MACRO const *, ID3DInclude *, char const *, char const *, unsigned __int32, unsigned __int32, ID3D10Blob **, ID3D10Blob **)
			// function call : void *()
			// function call : HRESULT (unsigned long const *, IDirect3DVertexShader9 **)
			// function call : void *()
			// function call : HRESULT (unsigned long const *, IDirect3DPixelShader9 **)
			todo("implement");
			bool __result = _sub_10CEB960(this);
			return __result;
		}

		// mangled_x86(MANGLED_DEFAULT, "??0GpuAcceleratedSurface@RenderHandlerGpu@Browser@Web@@QAE@XZ"); no body to assert in
		_inline RenderHandlerGpu::GpuAcceleratedSurface::GpuAcceleratedSurface() = default; // 0x10CEAA10

		_extern bool _sub_10CEC8C0(Web::Browser::RenderHandlerGpu *const);
		bool RenderHandlerGpu::Render() // 0x10CEC8C0
		{
			mangled_x86(MANGLED_TODO, "?Render@RenderHandlerGpu@Browser@Web@@UAE_NXZ");
			// static ...; // 0x10CED131
			// static ...; // 0x10CED126
			// static ...; // 0x10CED11D
			// static ...; // 0x10CED114
			// static ...; // 0x10CED0E4
			// static ...; // 0x10CED0DC
			// Web::Browser::RenderHandlerGpu *const this;
			// float gamma;
			// Modules::ModuleGraphics const &moduleGraphicxs;
			// Web::Browser::SCefScreenVertex const vertices[4];
			// real_vector4d gamma_power;
			// IDirect3DTexture9 *const viewTexture;
			// real_vector4d pixel_size;
			{
				// IDirect3DTexture9 *const popupTexture;
				{
					// Web::Browser::SCefScreenVertex const vertices[4];
					// float const x0;
					// float const y0;
					// float const x1;
					// float const y1;
				}
			}
			// function call : void (*const)(long)
			// function call : bool (*const)(IDirect3DVertexDeclaration9 *)
			// function call : bool (*const)(IDirect3DVertexShader9 *)
			// function call : bool (*const)(IDirect3DPixelShader9 *)
			// function call : void (*const)(long, c_enum<enum e_sampler_filter_mode,long>)
			// function call : void (*const)(long, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>)
			// function call : void (*const)(long)
			// function call : bool (*const)(IDirect3DIndexBuffer9 *)
			// function call : HRESULT (unsigned __int32, float const *, unsigned __int32)
			// function call : HRESULT (unsigned long, IDirect3DBaseTexture9 *)
			// function call : HRESULT (unsigned long, _D3DSAMPLERSTATETYPE, unsigned long)
			// function call : HRESULT (_D3DPRIMITIVETYPE, unsigned __int32, void const *, unsigned __int32)
			// function call : HRESULT (unsigned long, IDirect3DBaseTexture9 *)
			// function call : HRESULT (_D3DPRIMITIVETYPE, unsigned __int32, void const *, unsigned __int32)
			// function call : void (*const)(long, c_rasterizer_texture_ref)
			// function call : HRESULT (unsigned long, IDirect3DBaseTexture9 *)
			todo("implement");
			bool __result = _sub_10CEC8C0(this);
			return __result;
		}

		void RenderHandlerGpu::Shutdown() // 0x10CED5C0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Shutdown@RenderHandlerGpu@Browser@Web@@UAEXXZ");
			// Web::Browser::RenderHandlerGpu *const this;
		}
	}
}

/* ---------- private code */
