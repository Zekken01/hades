/* ---------- headers */

#include "hades/hades.h"

#include "Blam/bitmaps/bitmap_definition.hpp"
#include "Blam/BlamNetwork.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/integer_math_definitions.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/bitstream.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/rasterizer/rasterizer_d3d_allocations.hpp"
#include "Blam/rasterizer/rasterizers_textures_cache.hpp"
#include "Blam/render/views/render_lights_view.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "ElDorito.hpp"
#include "Modules/ModuleSettings.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Patches/CustomPackets.hpp"
#include "Player/PlayerEmblemDownload.hpp"
#include "Player/PlayerEmblemGenerator.hpp"
#include "Pointer.hpp"
#include "Utils/Macros.hpp"
#include "Utils/Rectangle.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"
#include "Web/WebRenderer.hpp"
#include "Web/WebRendererApp.hpp"
#include "Web/WebRendererRenderHandler.hpp"
#include "Web/WebRenderHandlerOsr.hpp"

#include <base/cef_atomic_ref_count.h>
#include <base/cef_lock.h>
#include <base/cef_logging.h>
#include <base/cef_platform_thread.h>
#include <base/cef_ref_counted.h>
#include <base/cef_scoped_refptr.h>
#include <base/cef_thread_checker.h>
#include <base/internal/cef_lock_impl.h>
#include <cef_app.h>
#include <cef_audio_handler.h>
#include <cef_base.h>
#include <cef_browser_process_handler.h>
#include <cef_client.h>
#include <cef_command_handler.h>
#include <cef_context_menu_handler.h>
#include <cef_devtools_message_observer.h>
#include <cef_dialog_handler.h>
#include <cef_display_handler.h>
#include <cef_download_handler.h>
#include <cef_drag_handler.h>
#include <cef_extension_handler.h>
#include <cef_find_handler.h>
#include <cef_focus_handler.h>
#include <cef_frame_handler.h>
#include <cef_jsdialog_handler.h>
#include <cef_keyboard_handler.h>
#include <cef_life_span_handler.h>
#include <cef_load_handler.h>
#include <cef_menu_model_delegate.h>
#include <cef_print_handler.h>
#include <cef_render_handler.h>
#include <cef_render_process_handler.h>
#include <cef_request_handler.h>
#include <cef_resource_handler.h>
#include <cef_resource_request_handler.h>
#include <d3dx9core.h>
#include <d3dx9math.h>
#include <d3dx9math.inl>
#include <internal/cef_string_wrappers.h>
#include <internal/cef_types_wrappers.h>
#include <internal/cef_win.h>

#include <Windows.h>
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
#include <charconv>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <filesystem>
#include <forward_list>
#include <functional>
#include <initializer_list>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <optional>
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

struct _D3DLOCKED_RECT;
struct _D3DPRESENT_PARAMETERS_;
struct _D3DSURFACE_DESC;
struct _D3DVIEWPORT9;
struct c_rasterizer_texture_ref;
struct s_bitmap_image;
struct short_rectangle2d;
namespace Modules
{
	class ModuleSettings;
}
namespace Web
{
	namespace Browser
	{
		class WebRenderer;
	}
}

namespace Utils {}
using namespace ::Utils;
namespace Utils
{
	namespace AntiCheat {}
	using namespace Utils::AntiCheat;
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

namespace Modules {}
using namespace ::Modules;
namespace Player {}
using namespace ::Player;
namespace Player
{
	namespace Emblems {}
	using namespace Player::Emblems;
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

namespace Http {}
using namespace ::Http;
namespace Blam {}
using namespace ::Blam;

/* ---------- constants */

/* ---------- definitions */

typedef void (*Video_CallsD3DEndScene_ptr)();

/* ---------- prototypes */

char const *tag_get_name(long tag_index);  // hades: added for 0X10961ED0

namespace DirectXHook
{
	extern void ApplyAll();
}

bool HookDirectX(IDirect3DDevice9 *device);
HRESULT __stdcall EndSceneHook(IDirect3DDevice9 *device);
bool InitializeDeviceHook(bool useDesktopDC, bool nullRefDevice);
HRESULT __stdcall ResetHook(IDirect3DDevice9 *device, _D3DPRESENT_PARAMETERS_ *params);
void HandleTakeScreenshotHook();
HRESULT set_viewport_window(short_rectangle2d *rect, float min_z, float max_z);
char const *GetD3DPoolName(_D3DPOOL pool);
HRESULT check_create_texture(__int32 type, _D3DPOOL pool, char const *tag_name, HRESULT hr);
HRESULT c_d3d_resource_allocator__create_texture_hook(unsigned __int32 width, unsigned __int32 height, unsigned __int32 levels, unsigned __int32 usage, _D3DFORMAT format, _D3DPOOL pool, IDirect3DTexture9 **out_texture, __int32 a8, __int32 a9, void *data_address, char const *name);
HRESULT c_d3d_resource_allocator__create_cube_texture_hook(unsigned __int32 edge_length, unsigned __int32 levels, unsigned __int32 usage, _D3DFORMAT format, _D3DPOOL pool, IDirect3DCubeTexture9 **out_texture, __int32 a7, void *a8, __int32 a9, char const *name);
HRESULT c_d3d_resource_allocator__create_volume_texture_hook(unsigned __int32 width, unsigned __int32 height, unsigned __int32 depth, unsigned __int32 levels, unsigned __int32 usage, _D3DFORMAT format, _D3DPOOL pool, IDirect3DVolumeTexture9 **out_texture, void *unk, void *data, __int32 a11, char const *name);
c_rasterizer_texture_ref *c_rasterizer_texture_ref__allocate_hook(c_rasterizer_texture_ref *data, s_bitmap_image *bitmap_data, char const *name, bool a4);
void update_present_parameters(_D3DPRESENT_PARAMETERS_ *present_params);
_D3DPRESENT_PARAMETERS_ *get_presentation_parameters_hook();
_D3DPRESENT_PARAMETERS_ *get_last_presentation_parameters_hook();

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern HRESULT (*c_d3d_resource_allocator__create_volume_texture)(unsigned __int32, unsigned __int32, unsigned __int32, unsigned __int32, unsigned __int32, _D3DFORMAT, _D3DPOOL, IDirect3DVolumeTexture9 **, void *, void *, __int32, char const *); // 0x1240F684
	extern void (*Video_CallsD3DEndSceneOrginal)(); // 0x1240F670
	extern HRESULT (__stdcall *origResetPtr)(IDirect3DDevice9 *, _D3DPRESENT_PARAMETERS_ *); // 0x1240F674
	extern HRESULT (__stdcall *origEndScenePtr)(IDirect3DDevice9 *);  // 0x1240F678
	extern HRESULT (*c_d3d_resource_allocator__create_texture)(unsigned __int32, unsigned __int32, unsigned __int32, unsigned __int32, _D3DFORMAT, _D3DPOOL, IDirect3DTexture9 **, __int32, __int32, void *, char const *); // 0x1240F67C
	extern HRESULT (*c_d3d_resource_allocator__create_cube_texture)(unsigned __int32, unsigned __int32, unsigned __int32, _D3DFORMAT, _D3DPOOL, IDirect3DCubeTexture9 **, __int32, void *, __int32, char const *); // 0x1240F680
}
using namespace hades_file_local;
/* ---------- public code */

namespace DirectXHook
{
	_extern void _sub_10960980();
	void ApplyAll() // 0x10960980
	{
		mangled_x86(MANGLED_TODO, "?ApplyAll@DirectXHook@@YAXXZ");
		// procedure flags: nofpo
		todo("implement");
		_sub_10960980();
	}
}

/* ---------- private code */

_extern bool _sub_109616C0(IDirect3DDevice9 *);
bool HookDirectX(IDirect3DDevice9 *device) // 0x109616C0
{
	// `anonymous-namespace'::HookDirectX
	// static ...; // 0x10961958
	// static ...; // 0x1096194C
	// static ...; // 0x10961944
	// IDirect3DDevice9 *device;
	// std::shared_ptr<Web::Browser::WebRenderer> webRenderer;
	// unsigned __int32 *directXVTable;
	// bool webDebugging;
	// function call : void *()
	// function call : void (char const *)
	todo("implement");
	bool __result = _sub_109616C0(device);
	return __result;
}

HRESULT __stdcall EndSceneHook(IDirect3DDevice9 *device) // 0x109610E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?EndSceneHook@@YGJPAUIDirect3DDevice9@@@Z");
	// `anonymous-namespace'::EndSceneHook
	// static ...; // 0x109612C0
	// static ...; // 0x109612B4
	// static ...; // 0x1096129C
	// static ...; // 0x10961294
	// IDirect3DDevice9 *device;
	// std::shared_ptr<Web::Browser::WebRenderer> webRenderer;
	// _D3DVIEWPORT9 viewport;
	// __int32 *windowResolution;
	// function call : HRESULT (_D3DVIEWPORT9 *)
	// function call : HRESULT (_D3DVIEWPORT9 const *)
	// function call : HRESULT (*)(IDirect3DDevice9 *)

	//Fixes the viewport if the game is in fullscreen with an incorrect aspect ratio.
	auto *windowResolution = reinterpret_cast<int *>(0x19106E4);
	D3DVIEWPORT9 viewport;
	device->GetViewport(&viewport);
	viewport.X = 0;
	viewport.Y = 0;
	viewport.Width = windowResolution[0];
	viewport.Height = windowResolution[1];
	device->SetViewport(&viewport);

	// Update the web renderer
	auto webRenderer = WebRenderer::GetInstance();
	if (webRenderer->Initialized() && webRenderer->IsRendering())
		webRenderer->Render(device);
	return (*origEndScenePtr)(device);
}

bool InitializeDeviceHook(bool useDesktopDC, bool nullRefDevice) // 0x10961A10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?InitializeDeviceHook@@YA_N_N0@Z");
	// `anonymous-namespace'::InitializeDeviceHook
	// bool nullRefDevice;
	// bool (*const InitializeDevice)(bool, bool);
	// function call : bool (*const)(bool, bool)

	bool (__cdecl *const InitializeDevice)(bool, bool) = (bool (__cdecl *const)(bool, bool))0xA21B40;

	if (Utils::Singleton<ElDorito>::Instance().IsHeadless())
		nullRefDevice = true;

	if (!InitializeDevice(useDesktopDC, nullRefDevice))
		return false;

	if (nullRefDevice)
		return true;

	return HookDirectX(*(IDirect3DDevice9 **)0x50DADDC);
}

HRESULT __stdcall ResetHook(IDirect3DDevice9 *device, _D3DPRESENT_PARAMETERS_ *params) // 0x10961B00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ResetHook@@YGJPAUIDirect3DDevice9@@PAU_D3DPRESENT_PARAMETERS_@@@Z");
	// `anonymous-namespace'::ResetHook
	// static ...; // 0x10961BE8
	// static ...; // 0x10961BE0
	// IDirect3DDevice9 *device;
	// _D3DPRESENT_PARAMETERS_ *params;
	// std::shared_ptr<Web::Browser::WebRenderer> webRenderer;
	// HRESULT result;
	// function call : HRESULT (*)(IDirect3DDevice9 *, _D3DPRESENT_PARAMETERS_ *)

	auto webRenderer = WebRenderer::GetInstance();
	webRenderer->PreReset();
	auto result = origResetPtr(device, params);
	webRenderer->PostReset();
	return result;
}

void HandleTakeScreenshotHook() // 0x109613D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?HandleTakeScreenshotHook@@YAXXZ");
	// `anonymous-namespace'::HandleTakeScreenshotHook
	// procedure flags: nofpo
	// static ...; // 0x1096161A
	// static ...; // 0x10961610
	// static ...; // 0x1096160B
	// static ...; // 0x10961600
	// static ...; // 0x109615D0
	// static ...; // 0x109615C8
	// _D3DSURFACE_DESC desc;
	// IDirect3DDevice9 *device;
	// bool (*const write_jpeg)(unsigned char *, __int32, __int32, wchar_t *);
	// unsigned char &takeScreenshot;
	// IDirect3DSurface9 *backBuffer;
	// IDirect3DSurface9 *tmpBuffer;
	// _D3DLOCKED_RECT lockedRect;
	// function call : HRESULT (unsigned __int32, unsigned __int32, _D3DBACKBUFFER_TYPE, IDirect3DSurface9 **)
	// function call : HRESULT (_D3DSURFACE_DESC *)
	// function call : HRESULT (unsigned __int32, unsigned __int32, _D3DFORMAT, _D3DPOOL, IDirect3DSurface9 **, void **)
	// function call : HRESULT (IDirect3DSurface9 *, IDirect3DSurface9 *)
	// function call : HRESULT (_D3DLOCKED_RECT *, tagRECT const *, unsigned long)
	// function call : bool (*const)(unsigned char *, __int32, __int32, wchar_t *)
	// function call : HRESULT ()
	// function call : unsigned long ()
	// function call : unsigned long ()

	const auto write_jpeg = (bool(*)(BYTE *pBits, int width, int height, wchar_t *path))(0x0060F5D0);

	auto &takeScreenshot = *(uint8_t*)0x0244DEE8;
	if (!takeScreenshot)
		return;
	takeScreenshot = 0;

	IDirect3DSurface9 *backBuffer, *tmpBuffer;
	D3DSURFACE_DESC desc;
	D3DLOCKED_RECT lockedRect;

	auto device = *(IDirect3DDevice9**)0x050DADDC;

	if (SUCCEEDED(device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer)))
	{
		if (SUCCEEDED(backBuffer->GetDesc(&desc)) && (desc.Format == D3DFMT_A8R8G8B8 || desc.Format == D3DFMT_X8R8G8B8) &&
			SUCCEEDED(device->CreateOffscreenPlainSurface(desc.Width, desc.Height, desc.Format, D3DPOOL_SYSTEMMEM, &tmpBuffer, nullptr)))
		{
			if (SUCCEEDED(device->GetRenderTargetData(backBuffer, tmpBuffer)) &&
				SUCCEEDED(tmpBuffer->LockRect(&lockedRect, nullptr, D3DLOCK_READONLY)))
			{
				write_jpeg((BYTE*)lockedRect.pBits, desc.Width, desc.Height, (wchar_t*)0x0244DFC0);
				tmpBuffer->UnlockRect();
			}
			tmpBuffer->Release();
		}

		backBuffer->Release();
	}
}

HRESULT set_viewport_window(short_rectangle2d *rect, float min_z, float max_z) // 0x109621A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_viewport_window@@YAJPAUshort_rectangle2d@@MM@Z");
	// `anonymous-namespace'::set_viewport_window
	// static ...; // 0x10962284
	// short_rectangle2d *rect;
	// float min_z;
	// float max_z;
	// short_rectangle2d new_rect;
	// unsigned long *g_game_resolution;
	// constexpr HRESULT (*const `set_viewport_window'::`2'::set_viewport)(short_rectangle2d *, float, float); // constant == 10784784
	// unsigned long *g_client_resolution;
	// function call : HRESULT (*const)(short_rectangle2d *, float, float)

	unsigned long *g_client_resolution = (unsigned long *)0x19106E4;
	unsigned long *g_game_resolution = (unsigned long *)0x19106C0;
	short_rectangle2d new_rect;

	new_rect.x0 = 0;
	new_rect.y0 = 0;

	if (Utils::Singleton<Modules::ModuleSettings>::Instance().VarFullscreen->ValueInt == 2)
	{
		new_rect.x1 = (short)g_game_resolution[0];
		new_rect.y1 = (short)g_game_resolution[1];
	}
	else
	{
		new_rect.x1 = (short)g_client_resolution[0];
		new_rect.y1 = (short)g_client_resolution[1];
	}

	return ((HRESULT (*)(short_rectangle2d *, float, float))0xA49010)(&new_rect, min_z, max_z);
}

extern char const *_sub_10961350(_D3DPOOL);
char const *GetD3DPoolName(_D3DPOOL pool) // 0x10961350
{
	// `anonymous-namespace'::GetD3DPoolName
	// static ...; // 0x109613A4
// $LN7:
// $LN6:
// $LN5:
// $LN4:
	// _D3DPOOL pool;
	todo("implement");
	char const * __result = _sub_10961350(pool);
	return __result;
}

extern HRESULT _sub_10961F60(__int32, _D3DPOOL, char const *, HRESULT);
HRESULT check_create_texture(__int32 type, _D3DPOOL pool, char const *tag_name, HRESULT hr) // 0x10961F60
{
	// `anonymous-namespace'::check_create_texture
	// __int32 type;
	// _D3DPOOL pool;
	// char const *tag_name;
	// HRESULT hr;
	{
		// char buff[4096];
	}
	// function call : __int32 (HWND__ *, char const *, char const *, unsigned __int32)
	todo("implement");
	HRESULT __result = _sub_10961F60(type, pool, tag_name, hr);
	return __result;
}

HRESULT c_d3d_resource_allocator__create_texture_hook(unsigned __int32 width, unsigned __int32 height, unsigned __int32 levels, unsigned __int32 usage, _D3DFORMAT format, _D3DPOOL pool, IDirect3DTexture9 **out_texture, __int32 a8, __int32 a9, void *data_address, char const *name) // 0x10961D50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_d3d_resource_allocator__create_texture_hook@@YAJIIIIW4_D3DFORMAT@@W4_D3DPOOL@@PAPAUIDirect3DTexture9@@HHPAXPBD@Z");
	// `anonymous-namespace'::c_d3d_resource_allocator__create_texture_hook
	// char const *name;
	// HRESULT hr;
	// function call : HRESULT (*)(unsigned __int32, unsigned __int32, unsigned __int32, unsigned __int32, _D3DFORMAT, _D3DPOOL, IDirect3DTexture9 **, __int32, __int32, void *, char const *)

	HRESULT hr = c_d3d_resource_allocator__create_texture(width, height, levels, usage, format, pool, out_texture, a8, a9, data_address, name);
	return check_create_texture(0, pool, name, hr);
}

HRESULT c_d3d_resource_allocator__create_cube_texture_hook(unsigned __int32 edge_length, unsigned __int32 levels, unsigned __int32 usage, _D3DFORMAT format, _D3DPOOL pool, IDirect3DCubeTexture9 **out_texture, __int32 a7, void *a8, __int32 a9, char const *name) // 0x10961CA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_d3d_resource_allocator__create_cube_texture_hook@@YAJIIIW4_D3DFORMAT@@W4_D3DPOOL@@PAPAUIDirect3DCubeTexture9@@HPAXHPBD@Z");
	// `anonymous-namespace'::c_d3d_resource_allocator__create_cube_texture_hook
	// char const *name;
	// HRESULT hr;
	// function call : HRESULT (*)(unsigned __int32, unsigned __int32, unsigned __int32, _D3DFORMAT, _D3DPOOL, IDirect3DCubeTexture9 **, __int32, void *, __int32, char const *)

	HRESULT hr = c_d3d_resource_allocator__create_cube_texture(edge_length, levels, usage, format, pool, out_texture, a7, a8, a9, name);
	return check_create_texture(1, pool, name, hr);
}

HRESULT c_d3d_resource_allocator__create_volume_texture_hook(unsigned __int32 width, unsigned __int32 height, unsigned __int32 depth, unsigned __int32 levels, unsigned __int32 usage, _D3DFORMAT format, _D3DPOOL pool, IDirect3DVolumeTexture9 **out_texture, void *unk, void *data, __int32 a11, char const *name) // 0x10961E10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_d3d_resource_allocator__create_volume_texture_hook@@YAJIIIIIW4_D3DFORMAT@@W4_D3DPOOL@@PAPAUIDirect3DVolumeTexture9@@PAX3HPBD@Z");
	// `anonymous-namespace'::c_d3d_resource_allocator__create_volume_texture_hook
	// char const *name;
	// HRESULT hr;
	// function call : HRESULT (*)(unsigned __int32, unsigned __int32, unsigned __int32, unsigned __int32, unsigned __int32, _D3DFORMAT, _D3DPOOL, IDirect3DVolumeTexture9 **, void *, void *, __int32, char const *)

	HRESULT hr = c_d3d_resource_allocator__create_volume_texture(width, height, depth, levels, usage, format, pool, out_texture, unk, data, a11, name);
	return check_create_texture(2, pool, name, hr);
}

c_rasterizer_texture_ref *c_rasterizer_texture_ref__allocate_hook(c_rasterizer_texture_ref *data, s_bitmap_image *bitmap_data, char const *name, bool a4) // 0x10961ED0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_rasterizer_texture_ref__allocate_hook@@YAPAUc_rasterizer_texture_ref@@PAU1@PAUs_bitmap_image@@PBD_N@Z");
	// `anonymous-namespace'::c_rasterizer_texture_ref__allocate_hook
	// bool a4;
	// c_rasterizer_texture_ref *(*const c_rasterizer_texture_ref__allocate)(c_rasterizer_texture_ref *, s_bitmap_image *, char const *, bool);
	// function call : c_rasterizer_texture_ref *(*const)(c_rasterizer_texture_ref *, s_bitmap_image *, char const *, bool)

	c_rasterizer_texture_ref *(__cdecl *const allocate)(c_rasterizer_texture_ref *, s_bitmap_image *, char const *, bool) = (c_rasterizer_texture_ref *(__cdecl *const)(c_rasterizer_texture_ref *, s_bitmap_image *, char const *, bool))0xa6dff0;

	name = tag_get_name(*(long *)0x190e460);
	return allocate(data, bitmap_data, name, a4);
}

void update_present_parameters(_D3DPRESENT_PARAMETERS_ *present_params) // 0x109622F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?update_present_parameters@@YAXPAU_D3DPRESENT_PARAMETERS_@@@Z");
	// `anonymous-namespace'::update_present_parameters
	// _D3DPRESENT_PARAMETERS_ *present_params;
	// Modules::ModuleSettings *const moduleSettings;

	Modules::ModuleSettings &module_settings = Utils::Singleton<Modules::ModuleSettings>::Instance();
	present_params->PresentationInterval = module_settings.VarVSync->ValueInt ? 1 : 0x80000000;
}

_D3DPRESENT_PARAMETERS_ *get_presentation_parameters_hook() // 0x10962140
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_presentation_parameters_hook@@YAPAU_D3DPRESENT_PARAMETERS_@@XZ");
	// `anonymous-namespace'::get_presentation_parameters_hook
	// procedure flags: nofpo
	// _D3DPRESENT_PARAMETERS_ *present_params;

	_D3DPRESENT_PARAMETERS_ *present_params = (_D3DPRESENT_PARAMETERS_ *)0x50dd928;

	update_present_parameters(present_params);
	return present_params;
}

_D3DPRESENT_PARAMETERS_ *get_last_presentation_parameters_hook() // 0x109620E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_last_presentation_parameters_hook@@YAPAU_D3DPRESENT_PARAMETERS_@@XZ");
	// `anonymous-namespace'::get_last_presentation_parameters_hook
	// procedure flags: nofpo
	// _D3DPRESENT_PARAMETERS_ *last_present_params;

	_D3DPRESENT_PARAMETERS_ *last_present_params = (_D3DPRESENT_PARAMETERS_ *)0x50dd960;

	update_present_parameters(last_present_params);
	return last_present_params;
}
