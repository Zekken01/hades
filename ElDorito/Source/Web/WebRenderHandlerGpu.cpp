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

#include "Utils/Logger.hpp"  // hades: added for 0x10CEB700

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
#include <d3dcompiler.h>  // hades: added for 0x10CEB960
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

char *c_rasterizer_samplers::sampler_srgb_states = reinterpret_cast<decltype(c_rasterizer_samplers::sampler_srgb_states)>(0x50DB200); // 0x113555D4

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
		_inline void RenderHandlerGpu::GpuAcceleratedSurface::OnAcceleratedPaint(void *sharedHandle) // 0x10CEC270
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OnAcceleratedPaint@GpuAcceleratedSurface@RenderHandlerGpu@Browser@Web@@QAEXPAX@Z");

			if (void **wrappedHandle = (void **)MapViewOfFile(sharedHandle, FILE_MAP_READ, 0, 0, sizeof(void *)))
			{
				m_nextHandle.store(*wrappedHandle);
				UnmapViewOfFile(wrappedHandle);
			}
		}
	}
}


namespace Web
{
	namespace Browser
	{
		_inline IDirect3DTexture9 *RenderHandlerGpu::GpuAcceleratedSurface::GetTexture(IDirect3DDevice9 *device) // 0x10CEB700
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetTexture@GpuAcceleratedSurface@RenderHandlerGpu@Browser@Web@@QAEPAUIDirect3DTexture9@@PAUIDirect3DDevice9@@@Z");

			void *nextHandle = m_nextHandle.load();
			if (m_didResize)
			{
				m_didResize = false;
				Reset();
			}
			if (nextHandle != m_handle)
			{
				m_handle = nextHandle;
				HRESULT hr = device->CreateTexture(m_size.width, m_size.height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_texture, &m_handle);
				if (FAILED(hr))
					Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Graphics, Utils::LogLevel::Info, "Web::Browser::RenderHandlerGpu::GpuAcceleratedSurface::GetTexture:44 - Failed to create surface texture. Error: %x", hr);
			}
			return m_texture.Get();
		}

		_inline void RenderHandlerGpu::GpuAcceleratedSurface::Reset() // 0x10CED360
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Reset@GpuAcceleratedSurface@RenderHandlerGpu@Browser@Web@@QAEXXZ");

			m_texture = nullptr;
			m_handle = nullptr;
		}

		_inline void RenderHandlerGpu::GpuAcceleratedSurface::Resize(unsigned __int32 width, unsigned __int32 height) // 0x10CED3C0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Resize@GpuAcceleratedSurface@RenderHandlerGpu@Browser@Web@@QAEXII@Z");

			m_size = CefSize(width, height);
			m_didResize = true;
		}

#line 269
		RenderHandlerGpu::RenderHandlerGpu(IDirect3DDevice9 *device9, HWND__ *window) : m_Window(window), m_Device(device9), m_VertexDeclaration(nullptr), m_VertexShader(nullptr), m_PixelShader(nullptr), m_PopupVisible(false), m_PopupValid(false), m_GpuBufferCount(0), m_GpuVsyncEnable(false), m_GpuWaitEvent(nullptr) /* hades-mem-init:  */ // 0x10CEAAB0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??0RenderHandlerGpu@Browser@Web@@QAE@PAUIDirect3DDevice9@@PAUHWND__@@@Z");
#line 273

			#line 281 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Web\\WebRenderHandlerGpu.cpp"
			LOG_ASSERT(device9);
			LOG_ASSERT(window);
			#line 278 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Web\\WebRenderHandlerGpu.cpp"
		}

		// mangled_x86(MANGLED_DEFAULT, "??1GpuAcceleratedSurface@RenderHandlerGpu@Browser@Web@@QAE@XZ"); no body to assert in
		_inline RenderHandlerGpu::GpuAcceleratedSurface::~GpuAcceleratedSurface() = default; // 0x10CEB050

		void RenderHandlerGpu::OnPopupShow(scoped_refptr<CefBrowser> browser, bool show) // 0x10CEC410
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OnPopupShow@RenderHandlerGpu@Browser@Web@@EAEXV?$scoped_refptr@VCefBrowser@@@@_N@Z");

			m_PopupVisible = show;
		}

		void RenderHandlerGpu::OnPopupSize(scoped_refptr<CefBrowser> browser, CefRect const &rect) // 0x10CEC470
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OnPopupSize@RenderHandlerGpu@Browser@Web@@EAEXV?$scoped_refptr@VCefBrowser@@@@ABVCefRect@@@Z");

			Utils::Rectangle newRect(rect.x, m_ViewSize.height - rect.y - rect.height, rect.width, rect.height);
			if (newRect == m_PopupRect)
			{
				m_PopupValid = true;
			}
			else
			{
				m_PopupRect = newRect;
				m_PopupSurface->Resize(m_PopupRect.Width, m_PopupRect.Height);
			}
		}

		void RenderHandlerGpu::OnAcceleratedPaint(scoped_refptr<CefBrowser> browser, cef_paint_element_type_t type, std::vector<CefRect> const &dirtyRects, void *sharedHandle) // 0x10CEC320
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OnAcceleratedPaint@RenderHandlerGpu@Browser@Web@@EAEXV?$scoped_refptr@VCefBrowser@@@@W4cef_paint_element_type_t@@ABV?$vector@VCefRect@@V?$allocator@VCefRect@@@std@@@std@@PAX@Z");

			if (type == PET_POPUP)
				m_PopupSurface->OnAcceleratedPaint(sharedHandle);
			else
				m_ViewSurface->OnAcceleratedPaint(sharedHandle);
		}

		bool RenderHandlerGpu::Resize(unsigned __int32 width, unsigned __int32 height) // 0x10CED4B0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Resize@RenderHandlerGpu@Browser@Web@@UAE_NII@Z");

			m_ViewSize = CefSize(width, height);
			m_ViewSurface->Resize(width, height);

			return true;
		}

		void RenderHandlerGpu::OnPreResetDevice() // 0x10CEC640
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OnPreResetDevice@RenderHandlerGpu@Browser@Web@@UAEXXZ");

			m_ViewSurface->Reset();
			m_PopupSurface->Reset();
		}

		void RenderHandlerGpu::OnPostResetDevice() // 0x10CEC620
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OnPostResetDevice@RenderHandlerGpu@Browser@Web@@UAEXXZ");
		}

		bool RenderHandlerGpu::InitRenderer() // 0x10CEB960
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?InitRenderer@RenderHandlerGpu@Browser@Web@@UAE_NXZ");

			bool const &g_d3d9ex = *reinterpret_cast<bool const *>(0x1910700);
			if (!g_d3d9ex)
			{
				Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Graphics, Utils::LogLevel::Info, "Web::Browser::RenderHandlerGpu::InitRenderer:140 - D3D9x was not found. CEF GPU Accelleration disabled!");
				return false;
			}
			HMODULE lib = LoadLibraryA("bin\\cef\\d3dcompiler_47.dll");
			if (!lib)
			{
				Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Graphics, Utils::LogLevel::Info, "Web::Browser::RenderHandlerGpu::InitRenderer:149 - D3DCOMPILER_47.dll was not found. CEF GPU Accelleration disabled!");
				return false;
			}
			pD3DCompile D3DCompile_ = (pD3DCompile)GetProcAddress(lib, "D3DCompile");
			D3DVERTEXELEMENT9 elements[] =
			{
				{ 0, 0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
				{ 0, 8, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
				D3DDECL_END()
			};
			HRESULT vd_result = m_Device.Get()->CreateVertexDeclaration(elements, &m_VertexDeclaration);
			ID3DBlob *vs_source;
			HRESULT vs_result = D3DCompile_(WebRendererHlsl, strlen(WebRendererHlsl), nullptr, nullptr, nullptr, "main_vs", "vs_3_0", D3DCOMPILE_OPTIMIZATION_LEVEL3, 0, &vs_source, nullptr);
			ID3DBlob *ps_source;
			HRESULT ps_result = D3DCompile_(WebRendererHlsl, strlen(WebRendererHlsl), nullptr, nullptr, nullptr, "main_ps", "ps_3_0", D3DCOMPILE_OPTIMIZATION_LEVEL3, 0, &ps_source, nullptr);
			if (FAILED(vd_result) || FAILED(vs_result) || FAILED(ps_result))
			{
				Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Graphics, Utils::LogLevel::Info, "Web::Browser::RenderHandlerGpu::InitRenderer:176 - Vertex declaration or shader compilation failed (%x) (%x) (%x).", vd_result, vs_result, ps_result);
				return false;
			}
			vs_result = m_Device.Get()->CreateVertexShader((DWORD const *)vs_source->GetBufferPointer(), &m_VertexShader);
			ps_result = m_Device.Get()->CreatePixelShader((DWORD const *)ps_source->GetBufferPointer(), &m_PixelShader);
			if (FAILED(vs_result) || FAILED(ps_result))
			{
				Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Graphics, Utils::LogLevel::Info, "Web::Browser::RenderHandlerGpu::InitRenderer:186 - Shader creation failed (%x) (%x).", vs_result, ps_result);
				return false;
			}
			m_ViewSurface = std::make_unique<GpuAcceleratedSurface>();
			m_PopupSurface = std::make_unique<GpuAcceleratedSurface>();
			return true;
		}

		// mangled_x86(MANGLED_DEFAULT, "??0GpuAcceleratedSurface@RenderHandlerGpu@Browser@Web@@QAE@XZ"); no body to assert in

		bool RenderHandlerGpu::Render() // 0x10CEC8C0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Render@RenderHandlerGpu@Browser@Web@@UAE_NXZ");

			Modules::ModuleGraphics const &moduleGraphicxs = Modules::ModuleGraphics::Instance();
			IDirect3DTexture9 *const viewTexture = m_ViewSurface->GetTexture(m_Device.Get());
			if (!viewTexture)
				return false;
			((void (*)(long))0xA22D10)(3);
			((bool (*)(IDirect3DVertexDeclaration9 *))0xA24650)(m_VertexDeclaration.Get());
			((bool (*)(IDirect3DVertexShader9 *))0xA247B0)(m_VertexShader.Get());
			((bool (*)(IDirect3DPixelShader9 *))0xA23500)(m_PixelShader.Get());
			c_rasterizer_samplers::sampler_srgb_states[5] = 1;
			((void (*)(long, c_enum<e_sampler_filter_mode, long>))0xA23660)(5, _filter_bilinear);
			((void (*)(long, c_enum<e_sampler_address_mode, long>, c_enum<e_sampler_address_mode, long>, c_enum<e_sampler_address_mode, long>))0xA23570)(5, _address_mode_clamp, _address_mode_clamp, _address_mode_clamp);
			((void (*)(long))0xA232D0)(2);
			((bool (*)(IDirect3DIndexBuffer9 *))0xA233C0)(nullptr);
			float gamma = moduleGraphicxs.VarGammaPower->ValueFloatMax - moduleGraphicxs.VarGammaPower->ValueFloat + 0.6f;
			real_vector4d gamma_power = { gamma, 0.0f, 0.0f, 0.0f };
			m_Device->SetPixelShaderConstantF(1, &gamma_power.i, 1);
			real_vector4d pixel_size = { 1.0f / m_ViewSize.width, 1.0f / m_ViewSize.height };
			pixel_size.k = pixel_size.i / 2.0f;
			pixel_size.w = pixel_size.j / 2.0f;
			SCefScreenVertex const vertices[4] =
			{
				{ { -1.0f, -1.0f }, { 0.0f + pixel_size.k, 0.0f + pixel_size.w } },
				{ { 1.0f, -1.0f }, { 1.0f + pixel_size.k, 0.0f + pixel_size.w } },
				{ { -1.0f, 1.0f }, { 0.0f + pixel_size.k, 1.0f + pixel_size.w } },
				{ { 1.0f, 1.0f }, { 1.0f + pixel_size.k, 1.0f + pixel_size.w } },
			};
			m_Device->SetTexture(5, viewTexture);
			m_Device->SetSamplerState(5, D3DSAMP_SRGBTEXTURE, 1);
			m_Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertices, sizeof(SCefScreenVertex));
			if (PopupIsVisible())
			{
				IDirect3DTexture9 *const popupTexture = m_PopupSurface->GetTexture(m_Device.Get());
				if (popupTexture)
				{
					float const x0 = (m_PopupRect.X - 0.5f) / m_ViewSize.width * 2.0f - 1.0f;
					float const y0 = (m_PopupRect.Y - 0.5f) / m_ViewSize.height * 2.0f - 1.0f;
					float const x1 = (m_PopupRect.X + m_PopupRect.Width - 0.5f) / m_ViewSize.width * 2.0f - 1.0f;
					float const y1 = (m_PopupRect.Y + m_PopupRect.Height - 0.5f) / m_ViewSize.height * 2.0f - 1.0f;
					SCefScreenVertex const vertices[4] =
					{
					{ { x0, y0 }, { 0.0f, 0.0f } },
					{ { x1, y0 }, { 1.0f, 0.0f } },
					{ { x0, y1 }, { 0.0f, 1.0f } },
					{ { x1, y1 }, { 1.0f, 1.0f } },
					};
					m_Device->SetTexture(5, popupTexture);
					m_Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertices, sizeof(SCefScreenVertex));
				}
			}
			((void (*)(long, c_rasterizer_texture_ref))0xA23810)(5, c_rasterizer_texture_ref(-1));
			m_Device->SetTexture(5, nullptr);
			return true;
		}

		void RenderHandlerGpu::Shutdown() // 0x10CED5C0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Shutdown@RenderHandlerGpu@Browser@Web@@UAEXXZ");
		}
	}
}

/* ---------- private code */

/* ---------- explicit instantiations */

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace Web { namespace Browser { namespace hades_file_local_Web_Browser { char const *WebRendererHlsl = "\n\nuniform sampler2D gpu_view : register(s5);\nuniform float gamma_power : register(c1);\nuniform float4 scale : register(c2); // from end_frame(), contrast/brightness control\n\n//#define COMPONENT_SWAP\n\nfloat4 main_ps(in float4 position : POSITION, in float2 texcoord : TEXCOORD0) : COLOR\n{\n    float4 color = tex2D(gpu_view, texcoord);\n\n#ifdef COMPONENT_SWAP\n    color.rgb = float3(color.b, color.g, color.r);\n#endif\n\n    // gamma, contrast and brightness\n    color.rgb = pow(sqrt(color.rgb), gamma_power);\n    color.rgb = color.rgb * scale.x + scale.y;\n    \n    return color;\n}\n\nstruct s_cef_screen_vertex_hlsl\n{\n    float2 position : POSITION;\n    float2 texcoord : TEXCOORD0;\n};\n\nvoid main_vs(const in s_cef_screen_vertex_hlsl input, out float4 position : POSITION, out float2 texcoord : TEXCOORD0)\n{\n    position.xy = input.position;\n    position.zw = 1.0f;\n    texcoord.xy = input.texcoord.xy;\n}\n\n"; } } }
