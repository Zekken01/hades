/* ---------- headers */

#include "hades/hades.h"

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
#include "Blam/interface/gui/gui_widget_render_info.hpp"
#include "Blam/interface/user_interface_definitions.hpp"
#include "Blam/math/integer_math_definitions.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/bitstream.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/rasterizer/rasterizer.hpp"
#include "Blam/rasterizer/rasterizer_geometry.hpp"
#include "Blam/rasterizer/rasterizer_globals.hpp"
#include "Blam/rasterizer/rasterizer_render_targets.hpp"
#include "Blam/rasterizer/rasterizer_samplers.hpp"
#include "Blam/rasterizer/rasterizer_screen_geometry.hpp"
#include "Blam/rasterizer/rasterizer_states.hpp"
#include "Blam/rasterizer/rasterizer_vertex_types.hpp"
#include "Blam/rasterizer/rasterizers_textures_cache.hpp"
#include "Blam/render/screen_postprocess.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Forge/Magnets.hpp"
#include "Interface/CustomBitmapManager.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Player/PlayerEmblemGenerator.hpp"
#include "Pointer.hpp"
#include "Utils/Singleton.hpp"

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
#include <condition_variable>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <forward_list>
#include <functional>
#include <initializer_list>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <mutex>
#include <optional>
#include <ostream>
#include <ratio>
#include <shared_mutex>
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

struct real_point2d;
struct s_gui_bitmap_widget_render_info;
struct s_rasterizer_globals;
struct s_rasterizer_screen_geometry_parameters;
struct s_screen_vertex;
struct s_user_interface_shared_globals;
struct short_rectangle2d;
namespace Blam
{
	namespace Network
	{
		struct Session;
	}
}
namespace hades_file_local
{
	class CRenderFullScreenBlur;
}
using namespace hades_file_local;

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;
namespace Player {}
using namespace ::Player;
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
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace MenuBlur {}
	using namespace Patches::MenuBlur;
}

namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Network {}
	using namespace Blam::Network;
}

/* ---------- constants */

/* ---------- definitions */

namespace hades_file_local
{
	class CRenderFullScreenBlur
	{
	public:
		void Update();
		void Render();
	private:
		float m_alpha; // 0x0
	public:
		CRenderFullScreenBlur(); /* compiler_generated() */
	};
	static_assert(sizeof(CRenderFullScreenBlur) == 4, "Invalid CRenderFullScreenBlur size");
}
using namespace hades_file_local;
/* ---------- prototypes */

namespace Patches
{
	namespace MenuBlur
	{
		extern void ApplyAll();
		extern void Tick();
		extern void RenderUIPostProcess();
	}
}

void get_blur_factors(float *blur_x, float *blur_y);
e_surface blur_display();
void scale_ui_screen_vertices(real_point2d *vertices);
void draw_widget_blur(s_gui_bitmap_widget_render_info *info, short_rectangle2d *display_bounds);
void draw_custom_bitmap(s_gui_bitmap_widget_render_info *info, short_rectangle2d *display_bounds, long explicit_shader_index);
void draw_custom_emblem(s_gui_bitmap_widget_render_info *info, short_rectangle2d *display_bounds, __int32 player_index);
void draw_custom_bitmap(s_gui_bitmap_widget_render_info *info, IDirect3DTexture9 *texture, short_rectangle2d *display_bounds);
void ui_draw_bitmap_widget_hook(s_gui_bitmap_widget_render_info *data, short_rectangle2d *display_bounds);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Patches
{
	namespace MenuBlur
	{
		_extern void _sub_108D17D0();
		void ApplyAll() // 0x108D17D0
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@MenuBlur@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_108D17D0();
		}

		_extern void _sub_108D1FE0();
		void Tick() // 0x108D1FE0
		{
			mangled_x86(MANGLED_TODO, "?Tick@MenuBlur@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_108D1FE0();
		}

		_extern void _sub_108D1F80();
		void RenderUIPostProcess() // 0x108D1F80
		{
			mangled_x86(MANGLED_TODO, "?RenderUIPostProcess@MenuBlur@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_108D1F80();
		}
	}
}

/* ---------- private code */

_extern void _sub_108D3330(float *, float *);
void get_blur_factors(float *blur_x, float *blur_y) // 0x108D3330
{
	// `anonymous-namespace'::get_blur_factors
	// float *blur_y;
	// s_user_interface_shared_globals *ui_shared_globals;
	// function call : s_user_interface_shared_globals *(*const)()
	todo("implement");
	_sub_108D3330(blur_x, blur_y);
}

extern e_surface _sub_108D2190();
e_surface blur_display() // 0x108D2190
{
	// `anonymous-namespace'::blur_display
	// procedure flags: nofpo
	// static ...; // 0x108D22A3
	// static ...; // 0x108D229C
	// static ...; // 0x108D2284
	// static ...; // 0x108D227C
	// float blur_x;
	// e_surface surface;
	// float blur_y;
	// function call : void (*const)(bool)
	// function call : e_surface (*const)(e_surface)
	// function call : e_surface (*const)(long, e_surface, long)
	// function call : e_surface (*const)(e_surface)
	// function call : void (*const)()
	// function call : void (*const)()
	todo("implement");
	e_surface __result = _sub_108D2190();
	return __result;
}

_extern void _sub_108D3490(real_point2d *);
void scale_ui_screen_vertices(real_point2d *vertices) // 0x108D3490
{
	// `anonymous-namespace'::scale_ui_screen_vertices
	// real_point2d *vertices;
	// unsigned long *g_game_resolution;
	// float width_scale;
	// float height_scale;
	todo("implement");
	_sub_108D3490(vertices);
}

_extern void _sub_108D2C70(s_gui_bitmap_widget_render_info *, short_rectangle2d *);
void draw_widget_blur(s_gui_bitmap_widget_render_info *info, short_rectangle2d *display_bounds) // 0x108D2C70
{
	// `anonymous-namespace'::draw_widget_blur
	// static ...; // 0x108D3160
	// static ...; // 0x108D3148
	// static ...; // 0x108D3140
	// s_gui_bitmap_widget_render_info *info;
	// short_rectangle2d *display_bounds;
	// e_surface blur_surface;
	// s_rasterizer_screen_geometry_parameters params;
	// float max_v;
	// s_screen_vertex vertices[4];
	// float min_u;
	// float max_u;
	// float min_v;
	// float display_width;
	// float display_height;
	// function call : void (*const)(s_rasterizer_screen_geometry_parameters *, s_screen_vertex *)
	todo("implement");
	_sub_108D2C70(info, display_bounds);
}

_extern void _sub_108D2400(s_gui_bitmap_widget_render_info *, short_rectangle2d *, long);
void draw_custom_bitmap(s_gui_bitmap_widget_render_info *info, short_rectangle2d *display_bounds, long explicit_shader_index) // 0x108D2400
{
	// `anonymous-namespace'::draw_custom_bitmap
	// static ...; // 0x108D2A2C
	// static ...; // 0x108D2A20
	// static ...; // 0x108D2A08
	// static ...; // 0x108D29CC
	// static ...; // 0x108D29C4
	// s_gui_bitmap_widget_render_info *info;
	// short_rectangle2d *display_bounds;
	// long explicit_shader_index;
	// long (*const DrawPrimitiveUP)(long, long, void *, long);
	// s_rasterizer_screen_geometry_parameters params;
	// s_screen_vertex vertices[4];
	// void (*const interface_get_current_display_or_window_settings)(short_rectangle2d *, short_rectangle2d *, short_rectangle2d *, short_rectangle2d *);
	// s_rasterizer_globals *const rasg;
	// void *const vtsh;
	// long address_mode;
	// void *const pixl;
	// long filter_mode;
	// void (*const c_vertex_declaration_table__vertex_shader_declaration_set)(long, long, long);
	// s_explicit_shader_ref *const explicit_shader;
	// short_rectangle2d fullscreen_pixel_bounds;
	// function call : void *(*const)(unsigned long, long)
	// function call : void *(*const)(unsigned long, long)
	// function call : bool (*const)(void *, long, long, long)
	// function call : bool (*const)(void *, long)
	// function call : void (*const)(long, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>)
	// function call : void (*const)(long, c_enum<enum e_sampler_filter_mode,long>)
	// function call : void (*const)(long)
	// function call : void (*const)(short_rectangle2d *, short_rectangle2d *, short_rectangle2d *, short_rectangle2d *)
	// function call : void (*const)(float, float, float, float, s_screen_vertex *, long)
	// function call : void (*const)(long)
	// function call : long (*const)(long)
	// function call : void (*const)(long, long, long)
	// function call : bool (*const)(IDirect3DIndexBuffer9 *)
	// function call : long (*const)(long, long, void *, long)
	// function call : long (*const)(long)
	// function call : void (*const)(long)
	// function call : void (*const)()
	todo("implement");
	_sub_108D2400(info, display_bounds, explicit_shader_index);
}

_extern void _sub_108D2BE0(s_gui_bitmap_widget_render_info *, short_rectangle2d *, __int32);
void draw_custom_emblem(s_gui_bitmap_widget_render_info *info, short_rectangle2d *display_bounds, __int32 player_index) // 0x108D2BE0
{
	// `anonymous-namespace'::draw_custom_emblem
	// __int32 player_index;
	// long *g_sampler_texture_refs;
	todo("implement");
	_sub_108D2BE0(info, display_bounds, player_index);
}

_extern void _sub_108D22F0(s_gui_bitmap_widget_render_info *, IDirect3DTexture9 *, short_rectangle2d *);
void draw_custom_bitmap(s_gui_bitmap_widget_render_info *info, IDirect3DTexture9 *texture, short_rectangle2d *display_bounds) // 0x108D22F0
{
	// `anonymous-namespace'::draw_custom_bitmap
	// short_rectangle2d *display_bounds;
	// long (*const DrawPrimitiveUP)(long, long, void *, long);
	// IDirect3DDevice9 *device;
	// void (*const interface_get_current_display_or_window_settings)(short_rectangle2d *, short_rectangle2d *, short_rectangle2d *, short_rectangle2d *);
	// long *g_sampler_texture_refs;
	// bool *g_sampler_gamma_correction_array;
	// void (*const c_vertex_declaration_table__vertex_shader_declaration_set)(long, long, long);
	// function call : HRESULT (unsigned long, IDirect3DBaseTexture9 *)
	// function call : HRESULT (unsigned long, _D3DSAMPLERSTATETYPE, unsigned long)
	todo("implement");
	_sub_108D22F0(info, texture, display_bounds);
}

_extern void _sub_108D37E0(s_gui_bitmap_widget_render_info *, short_rectangle2d *);
void ui_draw_bitmap_widget_hook(s_gui_bitmap_widget_render_info *data, short_rectangle2d *display_bounds) // 0x108D37E0
{
	// `anonymous-namespace'::ui_draw_bitmap_widget_hook
	// short_rectangle2d *display_bounds;
	// void (*const ui_draw_bitmap_widget)(s_gui_bitmap_widget_render_info *, short_rectangle2d *);
	{
		// e_surface old_surface;
	}
	{
		// IDirect3DTexture9 *texture;
	}
	{
		// __int32 player_index;
	}
	{
		// __int32 localPlayerIndex;
		// Blam::Network::Session *session;
	}
	// function call : e_surface (*const)(long)
	// function call : e_surface (*const)(long, e_surface, long)
	// function call : void (*const)(s_gui_bitmap_widget_render_info *, short_rectangle2d *)
	// function call : void (*const)(s_gui_bitmap_widget_render_info *, short_rectangle2d *)
	todo("implement");
	_sub_108D37E0(data, display_bounds);
}

_extern void _sub_108D1A10(CRenderFullScreenBlur *const);
void CRenderFullScreenBlur::Render() // 0x108D1A10
{
	// `anonymous-namespace'::CRenderFullScreenBlur::Render
	// static ...; // 0x108D1E61
	// static ...; // 0x108D1E58
	// static ...; // 0x108D1E40
	// static ...; // 0x108D1E38
	// CRenderFullScreenBlur *const this;
	// unsigned long color;
	// e_surface blur_surface;
	// s_rasterizer_screen_geometry_parameters params;
	// s_screen_vertex vertices[4];
	// unsigned long *g_game_resolution;
	// float display_width;
	// unsigned char alpha;
	// float display_height;
	// function call : void (*const)(s_rasterizer_screen_geometry_parameters *, s_screen_vertex *)
	todo("implement");
	_sub_108D1A10(this);
}

_extern void _sub_108D2030(CRenderFullScreenBlur *const);
void CRenderFullScreenBlur::Update() // 0x108D2030
{
	// `anonymous-namespace'::CRenderFullScreenBlur::Update
	// CRenderFullScreenBlur *const this;
	// bool enabled;
	// float m_transitionRateSeconds;
	// function call : float (*const)()
	todo("implement");
	_sub_108D2030(this);
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_tag_block<s_explicit_shader_ref>::try_get_element(__int32, s_explicit_shader_ref **) const;
template s_explicit_shader_ref & c_tag_block<s_explicit_shader_ref>::operator[](__int32);
template s_explicit_shader_ref * c_tag_block<s_explicit_shader_ref>::get_element(__int32) const;
