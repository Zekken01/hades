/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/effects/screen_effect.hpp"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/tls.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/rasterizer/rasterizer.hpp"
#include "Blam/rasterizer/rasterizer_geometry.hpp"
#include "Blam/rasterizer/rasterizer_globals.hpp"
#include "Blam/rasterizer/rasterizer_render_targets.hpp"
#include "Blam/rasterizer/rasterizer_samplers.hpp"
#include "Blam/rasterizer/rasterizer_shaders.hpp"
#include "Blam/rasterizer/rasterizer_states.hpp"
#include "Blam/rasterizer/rasterizers_textures_cache.hpp"
#include "Blam/render/camera_fx_settings.hpp"
#include "Blam/render/depth_of_field.hpp"
#include "Blam/render/render_blurs.hpp"
#include "Blam/render/render_globals.hpp"
#include "Blam/render/screen_postprocess.hpp"
#include "Blam/render/views/render_lights_view.hpp"
#include "Blam/render/views/render_player_view.hpp"
#include "Blam/shaders/render_method_submit.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Patch.hpp"
#include "Player/PlayerEmblemGenerator.hpp"
#include "Pointer.hpp"
#include "Utils/Singleton.hpp"

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
#include <initializer_list>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <streambuf>
#include <system_error>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

class c_rasterizer_globals;
struct s_depth_of_field;
struct s_motion_blur_parameters;
struct s_surface_group_description;

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;

/* ---------- constants */

/* ---------- definitions */

typedef IDirect3DQuery9 *LPDIRECT3DQUERY9;
typedef IDirect3DSurface9 *LPDIRECT3DSURFACE9;

/* ---------- prototypes */

extern void render_postprocess_patches_tick();
extern long detect_driver_forced_msaa();
extern void render_postprocess_patches_apply_after_init();
extern void render_postprocess_patches_apply();

/* ---------- globals */

s_motion_blur_parameters *c_rasterizer_globals::g_motion_blur_parameters; // 0x11354A3C
bool (*s_depth_of_field::get_enabled)(); // 0x11354A50
float (*s_depth_of_field::get_depth_of_field_blur_sigma)(s_depth_of_field *); // 0x11354A54

/* ---------- private variables */

namespace
{
	extern long driver_forced_msaa_value; // 0x11354A2C
	extern long g_exposure_occlusion_pixels_passed; // 0x1246736C
	extern IDirect3DSurface9 *g_exposure_dup_surface; // 0x12467370
	extern bool reflections_enabled; // 0x12467374
}
/* ---------- public code */

_extern void _sub_10AC2F20();
void render_postprocess_patches_tick() // 0x10AC2F20
{
	mangled_x86(MANGLED_TODO, "?render_postprocess_patches_tick@@YAXXZ");
	// procedure flags: nofpo
	todo("implement");
	_sub_10AC2F20();
}

_extern long _sub_10AC1880();
long detect_driver_forced_msaa() // 0x10AC1880
{
	mangled_x86(MANGLED_TODO, "?detect_driver_forced_msaa@@YAJXZ");
	// procedure flags: nofpo
	// static ...; // 0x10AC1E5A
	// static ...; // 0x10AC1E4E
	// static ...; // 0x10AC1E40
	// static ...; // 0x10AC1E33
	// static ...; // 0x10AC1E28
	// static ...; // 0x10AC1E14
	// static ...; // 0x10AC1DCC
	// static ...; // 0x10AC1DC4
	// long msaa_level;
	// IDirect3DDevice9Ex *const device;
	// IDirect3DVertexBuffer9 *test_buffer;
	// detect_driver_forced_msaa::__l2::s_test_vertex test_verts[4];
	{
		// void *test_vertices;
		{
			// IDirect3DSurface9 *test_surface;
			// long test_rt_res;
			// _D3DFORMAT test_format;
			{
				// IDirect3DQuery9 *test_query;
				{
					// __int32 non_occluded_pixels;
					// unsigned long start_time;
					// long cycles;
				}
			}
		}
	}
	// function call : HRESULT ()
	// function call : HRESULT (unsigned __int32, unsigned long, unsigned long, _D3DPOOL, IDirect3DVertexBuffer9 **, void **)
	// function call : HRESULT (unsigned __int32, unsigned __int32, void **, unsigned long)
	// function call : HRESULT ()
	// function call : HRESULT (unsigned __int32, unsigned __int32, _D3DFORMAT, _D3DMULTISAMPLE_TYPE, unsigned long, __int32, IDirect3DSurface9 **, void **)
	// function call : HRESULT (_D3DQUERYTYPE, IDirect3DQuery9 **)
	// function call : HRESULT (unsigned long, IDirect3DSurface9 *)
	// function call : HRESULT (unsigned __int32, IDirect3DVertexBuffer9 *, unsigned __int32, unsigned __int32)
	// function call : HRESULT (unsigned long)
	// function call : HRESULT (_D3DRENDERSTATETYPE, unsigned long)
	// function call : HRESULT (_D3DRENDERSTATETYPE, unsigned long)
	// function call : HRESULT (unsigned long)
	// function call : HRESULT (_D3DPRIMITIVETYPE, unsigned __int32, unsigned __int32)
	// function call : HRESULT (unsigned long)
	// function call : HRESULT (void *, unsigned long, unsigned long)
	// function call : HRESULT (void *, unsigned long, unsigned long)
	// function call : HRESULT (unsigned long, IDirect3DSurface9 *)
	// function call : unsigned long ()
	// function call : unsigned long ()
	// function call : unsigned long ()
	// function call : HRESULT ()
	todo("implement");
	long __result = _sub_10AC1880();
	return __result;
}

_extern void _sub_10AC2E10();
void render_postprocess_patches_apply_after_init() // 0x10AC2E10
{
	mangled_x86(MANGLED_TODO, "?render_postprocess_patches_apply_after_init@@YAXXZ");
	// procedure flags: nofpo
	// static ...; // 0x10AC2ED4
	// static ...; // 0x10AC2EC8
	// static ...; // 0x10AC2EC0
	// IDirect3DDevice9Ex *const device;
	// IDirect3DTexture9 *dup_exposure_tex;
	// function call : HRESULT (unsigned __int32, unsigned __int32, unsigned __int32, unsigned long, _D3DFORMAT, _D3DPOOL, IDirect3DTexture9 **, void **)
	// function call : HRESULT (unsigned __int32, IDirect3DSurface9 **)
	todo("implement");
	_sub_10AC2E10();
}

_extern void _sub_10AC21B0();
void render_postprocess_patches_apply() // 0x10AC21B0
{
	mangled_x86(MANGLED_TODO, "?render_postprocess_patches_apply@@YAXXZ");
	// procedure flags: nofpo
	// long const shadow_texture_resolution;
	// s_surface_group_description *shadow_surface;
	// s_surface_group_description *shadow_color_surface;
	// s_surface_group_description *cortana_effect_surface;
	todo("implement");
	_sub_10AC21B0();
}

/* ---------- private code */
