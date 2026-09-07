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

namespace DirectXHook
{
	extern void ApplyAll();
}

bool HookDirectX(IDirect3DDevice9 *device);
HRESULT EndSceneHook(IDirect3DDevice9 *device);
bool InitializeDeviceHook(bool useDesktopDC, bool nullRefDevice);
HRESULT ResetHook(IDirect3DDevice9 *device, _D3DPRESENT_PARAMETERS_ *params);
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
	extern HRESULT (*origResetPtr)(IDirect3DDevice9 *, _D3DPRESENT_PARAMETERS_ *); // 0x1240F674
	extern HRESULT (*origEndScenePtr)(IDirect3DDevice9 *); // 0x1240F678
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

extern HRESULT _sub_109610E0(IDirect3DDevice9 *);
HRESULT EndSceneHook(IDirect3DDevice9 *device) // 0x109610E0
{
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
	todo("implement");
	HRESULT __result = _sub_109610E0(device);
	return __result;
}

_extern bool _sub_10961A10(bool, bool);
bool InitializeDeviceHook(bool useDesktopDC, bool nullRefDevice) // 0x10961A10
{
	// `anonymous-namespace'::InitializeDeviceHook
	// bool nullRefDevice;
	// bool (*const InitializeDevice)(bool, bool);
	// function call : bool (*const)(bool, bool)
	todo("implement");
	bool __result = _sub_10961A10(useDesktopDC, nullRefDevice);
	return __result;
}

extern HRESULT _sub_10961B00(IDirect3DDevice9 *, _D3DPRESENT_PARAMETERS_ *);
HRESULT ResetHook(IDirect3DDevice9 *device, _D3DPRESENT_PARAMETERS_ *params) // 0x10961B00
{
	// `anonymous-namespace'::ResetHook
	// static ...; // 0x10961BE8
	// static ...; // 0x10961BE0
	// IDirect3DDevice9 *device;
	// _D3DPRESENT_PARAMETERS_ *params;
	// std::shared_ptr<Web::Browser::WebRenderer> webRenderer;
	// HRESULT result;
	// function call : HRESULT (*)(IDirect3DDevice9 *, _D3DPRESENT_PARAMETERS_ *)
	todo("implement");
	HRESULT __result = _sub_10961B00(device, params);
	return __result;
}

_extern void _sub_109613D0();
void HandleTakeScreenshotHook() // 0x109613D0
{
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
	todo("implement");
	_sub_109613D0();
}

extern HRESULT _sub_109621A0(short_rectangle2d *, float, float);
HRESULT set_viewport_window(short_rectangle2d *rect, float min_z, float max_z) // 0x109621A0
{
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
	todo("implement");
	HRESULT __result = _sub_109621A0(rect, min_z, max_z);
	return __result;
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

extern HRESULT _sub_10961D50(unsigned __int32, unsigned __int32, unsigned __int32, unsigned __int32, _D3DFORMAT, _D3DPOOL, IDirect3DTexture9 **, __int32, __int32, void *, char const *);
HRESULT c_d3d_resource_allocator__create_texture_hook(unsigned __int32 width, unsigned __int32 height, unsigned __int32 levels, unsigned __int32 usage, _D3DFORMAT format, _D3DPOOL pool, IDirect3DTexture9 **out_texture, __int32 a8, __int32 a9, void *data_address, char const *name) // 0x10961D50
{
	// `anonymous-namespace'::c_d3d_resource_allocator__create_texture_hook
	// char const *name;
	// HRESULT hr;
	// function call : HRESULT (*)(unsigned __int32, unsigned __int32, unsigned __int32, unsigned __int32, _D3DFORMAT, _D3DPOOL, IDirect3DTexture9 **, __int32, __int32, void *, char const *)
	todo("implement");
	HRESULT __result = _sub_10961D50(width, height, levels, usage, format, pool, out_texture, a8, a9, data_address, name);
	return __result;
}

extern HRESULT _sub_10961CA0(unsigned __int32, unsigned __int32, unsigned __int32, _D3DFORMAT, _D3DPOOL, IDirect3DCubeTexture9 **, __int32, void *, __int32, char const *);
HRESULT c_d3d_resource_allocator__create_cube_texture_hook(unsigned __int32 edge_length, unsigned __int32 levels, unsigned __int32 usage, _D3DFORMAT format, _D3DPOOL pool, IDirect3DCubeTexture9 **out_texture, __int32 a7, void *a8, __int32 a9, char const *name) // 0x10961CA0
{
	// `anonymous-namespace'::c_d3d_resource_allocator__create_cube_texture_hook
	// char const *name;
	// HRESULT hr;
	// function call : HRESULT (*)(unsigned __int32, unsigned __int32, unsigned __int32, _D3DFORMAT, _D3DPOOL, IDirect3DCubeTexture9 **, __int32, void *, __int32, char const *)
	todo("implement");
	HRESULT __result = _sub_10961CA0(edge_length, levels, usage, format, pool, out_texture, a7, a8, a9, name);
	return __result;
}

extern HRESULT _sub_10961E10(unsigned __int32, unsigned __int32, unsigned __int32, unsigned __int32, unsigned __int32, _D3DFORMAT, _D3DPOOL, IDirect3DVolumeTexture9 **, void *, void *, __int32, char const *);
HRESULT c_d3d_resource_allocator__create_volume_texture_hook(unsigned __int32 width, unsigned __int32 height, unsigned __int32 depth, unsigned __int32 levels, unsigned __int32 usage, _D3DFORMAT format, _D3DPOOL pool, IDirect3DVolumeTexture9 **out_texture, void *unk, void *data, __int32 a11, char const *name) // 0x10961E10
{
	// `anonymous-namespace'::c_d3d_resource_allocator__create_volume_texture_hook
	// char const *name;
	// HRESULT hr;
	// function call : HRESULT (*)(unsigned __int32, unsigned __int32, unsigned __int32, unsigned __int32, unsigned __int32, _D3DFORMAT, _D3DPOOL, IDirect3DVolumeTexture9 **, void *, void *, __int32, char const *)
	todo("implement");
	HRESULT __result = _sub_10961E10(width, height, depth, levels, usage, format, pool, out_texture, unk, data, a11, name);
	return __result;
}

extern c_rasterizer_texture_ref *_sub_10961ED0(c_rasterizer_texture_ref *, s_bitmap_image *, char const *, bool);
c_rasterizer_texture_ref *c_rasterizer_texture_ref__allocate_hook(c_rasterizer_texture_ref *data, s_bitmap_image *bitmap_data, char const *name, bool a4) // 0x10961ED0
{
	// `anonymous-namespace'::c_rasterizer_texture_ref__allocate_hook
	// bool a4;
	// c_rasterizer_texture_ref *(*const c_rasterizer_texture_ref__allocate)(c_rasterizer_texture_ref *, s_bitmap_image *, char const *, bool);
	// function call : c_rasterizer_texture_ref *(*const)(c_rasterizer_texture_ref *, s_bitmap_image *, char const *, bool)
	todo("implement");
	c_rasterizer_texture_ref * __result = _sub_10961ED0(data, bitmap_data, name, a4);
	return __result;
}

_extern void _sub_109622F0(_D3DPRESENT_PARAMETERS_ *);
void update_present_parameters(_D3DPRESENT_PARAMETERS_ *present_params) // 0x109622F0
{
	// `anonymous-namespace'::update_present_parameters
	// _D3DPRESENT_PARAMETERS_ *present_params;
	// Modules::ModuleSettings *const moduleSettings;
	todo("implement");
	_sub_109622F0(present_params);
}

extern _D3DPRESENT_PARAMETERS_ *_sub_10962140();
_D3DPRESENT_PARAMETERS_ *get_presentation_parameters_hook() // 0x10962140
{
	// `anonymous-namespace'::get_presentation_parameters_hook
	// procedure flags: nofpo
	// _D3DPRESENT_PARAMETERS_ *present_params;
	todo("implement");
	_D3DPRESENT_PARAMETERS_ * __result = _sub_10962140();
	return __result;
}

extern _D3DPRESENT_PARAMETERS_ *_sub_109620E0();
_D3DPRESENT_PARAMETERS_ *get_last_presentation_parameters_hook() // 0x109620E0
{
	// `anonymous-namespace'::get_last_presentation_parameters_hook
	// procedure flags: nofpo
	// _D3DPRESENT_PARAMETERS_ *last_present_params;
	todo("implement");
	_D3DPRESENT_PARAMETERS_ * __result = _sub_109620E0();
	return __result;
}
