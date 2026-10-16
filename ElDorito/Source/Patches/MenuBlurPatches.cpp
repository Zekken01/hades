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
#include "Modules/ModuleGame.hpp"  // hades: added for 0x108D2030

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
		// CRenderFullScreenBlur(); /* compiler_generated(): left implicit, as the original's was */
	};
	static_assert(sizeof(CRenderFullScreenBlur) == 4, "Invalid CRenderFullScreenBlur size");
}
using namespace hades_file_local;
/* ---------- prototypes */

namespace eldorado
{
	// Functions in eldorado.exe, named as in ManagedDonkey.
	static auto const c_rasterizer_clear_sampler_textures = reinterpret_cast<void (*)()>(0xA22AB0);
	static auto const c_rasterizer_get_render_target = reinterpret_cast<e_surface (*)(long)>(0xA48720);
	static auto const c_rasterizer_set_alpha_blend_mode = reinterpret_cast<void (*)(long)>(0xA22D10);
	static auto const c_rasterizer_set_cull_mode = reinterpret_cast<void (*)(long)>(0xA232D0);
	static auto const c_rasterizer_set_indices = reinterpret_cast<bool (*)(IDirect3DIndexBuffer9 *)>(0xA233C0);
	static auto const c_rasterizer_set_pixel_shader = reinterpret_cast<bool (*)(void *, long)>(0xA23460);
	static auto const c_rasterizer_set_render_target = reinterpret_cast<e_surface (*)(long, e_surface, long)>(0xA48E40);
	static auto const c_rasterizer_set_sampler_address_mode = reinterpret_cast<void (*)(long, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>, c_enum<enum e_sampler_address_mode,long>)>(0xA23570);
	static auto const c_rasterizer_set_sampler_filter_mode = reinterpret_cast<void (*)(long, c_enum<enum e_sampler_filter_mode,long>)>(0xA23660);
	static auto const c_rasterizer_set_vertex_shader = reinterpret_cast<bool (*)(void *, long, long, long)>(0xA246E0);
	static auto const c_rasterizer_set_z_buffer_mode = reinterpret_cast<long (*)(long)>(0xA247E0);
}

namespace Player { namespace PlayerEmblem { extern void set_emblem_texture(long sampler, long player_index, bool use_generic, bool screen_emblem); } }  // hades: added for 0x108D2BE0

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

extern float (*const game_tick_length)();  // hades: added for 0x108D2030

/* ---------- private variables */

namespace hades_file_local
{
	extern CRenderFullScreenBlur g_fullscreenMenuBlur; // 0x12408354
}
using namespace hades_file_local;
/* ---------- public code */

namespace Patches
{
	namespace MenuBlur
	{
		void ApplyAll() // 0x108D17D0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAll@MenuBlur@Patches@@YAXXZ");
			// procedure flags: nofpo

			Hook(0x6B9F75, ui_draw_bitmap_widget_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x71C050, ui_draw_bitmap_widget_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
		}

		void Tick() // 0x108D1FE0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Tick@MenuBlur@Patches@@YAXXZ");
			// procedure flags: nofpo

			g_fullscreenMenuBlur.Update();
		}

		void RenderUIPostProcess() // 0x108D1F80
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?RenderUIPostProcess@MenuBlur@Patches@@YAXXZ");
			// procedure flags: nofpo

			g_fullscreenMenuBlur.Render();
			CustomBitmapManager::Get()->UpdateRender();
		}
	}
}

/* ---------- private code */

void get_blur_factors(float *blur_x, float *blur_y) // 0x108D3330
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_blur_factors@@YAXPAM0@Z");
	// `anonymous-namespace'::get_blur_factors
	// float *blur_y;
	// s_user_interface_shared_globals *ui_shared_globals;
	// function call : s_user_interface_shared_globals *(*const)()

	s_user_interface_shared_globals *ui_shared_globals = ((s_user_interface_shared_globals *(*)())0xA84D20)();

	if (ui_shared_globals)
	{
		*blur_x = ui_shared_globals->menu_blur_x;
		*blur_y = ui_shared_globals->menu_blur_y;
	}
	else
	{
		*blur_x = 1.5f;
		*blur_y = 1.5f;
	}
}

e_surface blur_display() // 0x108D2190
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?blur_display@@YA?AW4e_surface@@XZ");
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

	float blur_x, blur_y;
	get_blur_factors(&blur_x, &blur_y);

	((void (*)(bool))0xA63510)(false);
	((e_surface (*)(e_surface))0xA48CB0)(_surface_disable);

	e_surface surface = c_screen_postprocess::blur_display(blur_x, blur_y);

	((e_surface (*)(long, e_surface, long))0xA48E40)(0, _surface_screenshot_display, -1);
	((e_surface (*)(e_surface))0xA48CB0)(_surface_depth_stencil);
	((void (*)())0xA202F0)();
	((void (*)())0xA202E0)();

	return surface;
}

void scale_ui_screen_vertices(real_point2d *vertices) // 0x108D3490
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?scale_ui_screen_vertices@@YAXPAUreal_point2d@@@Z");
	// `anonymous-namespace'::scale_ui_screen_vertices
	// real_point2d *vertices;
	// unsigned long *g_game_resolution;
	// float width_scale;
	// float height_scale;

	unsigned long *g_game_resolution = (unsigned long *)0x19106C0;

	float width_scale = (float)g_game_resolution[0] / (float)g_game_resolution[2];
	float height_scale = (float)g_game_resolution[1] / (float)g_game_resolution[3];

	vertices[0].x = vertices[0].x * width_scale;
	vertices[1].x = vertices[1].x * width_scale;
	vertices[2].x = vertices[2].x * width_scale;
	vertices[3].x = vertices[3].x * width_scale;
	vertices[0].y = vertices[0].y * height_scale;
	vertices[1].y = vertices[1].y * height_scale;
	vertices[2].y = vertices[2].y * height_scale;
	vertices[3].y = vertices[3].y * height_scale;
}

void draw_widget_blur(s_gui_bitmap_widget_render_info *info, short_rectangle2d *display_bounds) // 0x108D2C70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?draw_widget_blur@@YAXPAUs_gui_bitmap_widget_render_info@@PAUshort_rectangle2d@@@Z");
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

	e_surface blur_surface = blur_display();
	s_rasterizer_screen_geometry_parameters params;
	memset(&params.texture_datum_index, 0, 0x94);
	params.surface_index = blur_surface;
	params.texture_datum_index = -1;
	params.alpha_blend_mode = (short)info->blend_mode;
	params.explicit_shader_index = info->explicit_shader_index;
	params.field_40 = 1.0f;
	params.field_44 = 1.0f;
	params.field_48 = 1.0f;
	params.field_4C = 1.0f;
	float display_width = (float)(display_bounds->x1 - display_bounds->x0);
	float display_height = (float)(display_bounds->y1 - display_bounds->y0);
	float min_u = (float)(info->vertices[0].x + 0.5) / display_width;
	float max_u = (float)(info->vertices[3].x + 0.5) / display_width;
	float min_v = (float)(info->vertices[2].y + 0.5) / display_height;
	float max_v = (float)(info->vertices[3].y + 0.5) / display_height;
	scale_ui_screen_vertices(info->vertices);
	s_screen_vertex vertices[4];
	vertices[0].position = { info->vertices[0].x, info->vertices[0].y };
	vertices[0].texcoord = { min_u + info->offset_u, min_v + info->offset_v };
	vertices[0].color = info->color;
	vertices[1].position = { info->vertices[2].x, info->vertices[2].y };
	vertices[1].texcoord = { max_u + info->offset_u, min_v + info->offset_v };
	vertices[1].color = info->color;
	vertices[2].position = { info->vertices[3].x, info->vertices[3].y };
	vertices[2].texcoord = { max_u + info->offset_u, max_v + info->offset_v };
	vertices[2].color = info->color;
	vertices[3].position = { info->vertices[1].x, info->vertices[1].y };
	vertices[3].texcoord = { min_u + info->offset_u, max_v + info->offset_v };
	vertices[3].color = info->color;
	((void (*)(s_rasterizer_screen_geometry_parameters *, s_screen_vertex *))0xA46AD0)(&params, vertices);
}

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

	void (*const interface_get_current_display_or_window_settings)(short_rectangle2d *, short_rectangle2d *, short_rectangle2d *, short_rectangle2d *) = (void (*const)(short_rectangle2d *, short_rectangle2d *, short_rectangle2d *, short_rectangle2d *))0xA9FA40;
	void (*const c_vertex_declaration_table__vertex_shader_declaration_set)(long, long, long) = (void (*const)(long, long, long))0xA729B0;
	long (*const DrawPrimitiveUP)(long, long, void *, long) = (long (*const)(long, long, void *, long))0xA28330;
	s_rasterizer_screen_geometry_parameters params;
	memset(&params.texture_datum_index, 0, 0x94);
	params.alpha_blend_mode = (short)info->blend_mode;
	params.explicit_shader_index = explicit_shader_index;
	params.texture_datum_index = -1;
	params.texture_datum_index_2 = -1;
	scale_ui_screen_vertices(info->vertices);
	s_screen_vertex vertices[4];
	vertices[0].position = info->vertices[0];
	vertices[0].texcoord = { 0.0f, 0.0f };
	vertices[0].color = info->color;
	vertices[1].position = info->vertices[2];
	vertices[1].texcoord = { 1.0f, 0.0f };
	vertices[1].color = info->color;
	vertices[2].position = info->vertices[3];
	vertices[2].texcoord = { 1.0f, 1.0f };
	vertices[2].color = info->color;
	vertices[3].position = info->vertices[1];
	vertices[3].texcoord = { 0.0f, 1.0f };
	vertices[3].color = info->color;
	s_rasterizer_globals *const rasg = c_rasterizer_globals::get();
	s_explicit_shader_ref *const explicit_shader = &rasg->explicit_shaders[params.explicit_shader_index];
	if (((s_tag_reference *)explicit_shader->pixel_shader)->index == -1 || ((s_tag_reference *)explicit_shader->vertex_shader)->index == -1)
		return;
	void *const vtsh = tag_get('vtsh', ((s_tag_reference *)explicit_shader->vertex_shader)->index);
	void *const pixl = tag_get('pixl', ((s_tag_reference *)explicit_shader->pixel_shader)->index);
	if (!vtsh || !pixl)
		return;
	eldorado::c_rasterizer_set_vertex_shader(vtsh, 7, 0, 0);
	eldorado::c_rasterizer_set_pixel_shader(pixl, 0);
	long address_mode = params.texture_address_mode1 == 0;
	eldorado::c_rasterizer_set_sampler_address_mode(0, address_mode, address_mode, address_mode);
	long filter_mode = (params.texture_filter_mode == 0) + 1;
	eldorado::c_rasterizer_set_sampler_filter_mode(0, filter_mode);
	eldorado::c_rasterizer_set_alpha_blend_mode(params.alpha_blend_mode);
	short_rectangle2d fullscreen_pixel_bounds;
	interface_get_current_display_or_window_settings(&fullscreen_pixel_bounds, nullptr, nullptr, nullptr);
	((void (*const)(float, float, float, float, s_screen_vertex *, long))0xA46910)(1.0f / (fullscreen_pixel_bounds.x1 - fullscreen_pixel_bounds.x0), 1.0f / (fullscreen_pixel_bounds.y1 - fullscreen_pixel_bounds.y0), fullscreen_pixel_bounds.x0, fullscreen_pixel_bounds.y0, vertices, 4);
	eldorado::c_rasterizer_set_cull_mode(1);
	eldorado::c_rasterizer_set_z_buffer_mode(2);
	c_vertex_declaration_table__vertex_shader_declaration_set(7, 0, 0);
	eldorado::c_rasterizer_set_indices(nullptr);
	DrawPrimitiveUP(4, 2, vertices, sizeof(s_screen_vertex));
	eldorado::c_rasterizer_set_z_buffer_mode(1);
	eldorado::c_rasterizer_set_cull_mode(2);
	eldorado::c_rasterizer_clear_sampler_textures();
}

void draw_custom_emblem(s_gui_bitmap_widget_render_info *info, short_rectangle2d *display_bounds, __int32 player_index) // 0x108D2BE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?draw_custom_emblem@@YAXPAUs_gui_bitmap_widget_render_info@@PAUshort_rectangle2d@@H@Z");
	// `anonymous-namespace'::draw_custom_emblem
	// __int32 player_index;
	// long *g_sampler_texture_refs;

	long *g_sampler_texture_refs = (long *)0x1910560;

	::Player::PlayerEmblem::set_emblem_texture(0, player_index, 0, 1);
	g_sampler_texture_refs[0] = -1;
	draw_custom_bitmap(info, display_bounds, 63);
}

void draw_custom_bitmap(s_gui_bitmap_widget_render_info *info, IDirect3DTexture9 *texture, short_rectangle2d *display_bounds) // 0x108D22F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?draw_custom_bitmap@@YAXPAUs_gui_bitmap_widget_render_info@@PAUIDirect3DTexture9@@PAUshort_rectangle2d@@@Z");
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

	void (*const interface_get_current_display_or_window_settings)(short_rectangle2d *, short_rectangle2d *, short_rectangle2d *, short_rectangle2d *) = (void (*const)(short_rectangle2d *, short_rectangle2d *, short_rectangle2d *, short_rectangle2d *))0xA9FA40;
	void (*const c_vertex_declaration_table__vertex_shader_declaration_set)(long, long, long) = (void (*const)(long, long, long))0xA729B0;
	long (*const DrawPrimitiveUP)(long, long, void *, long) = (long (*const)(long, long, void *, long))0xA28330;
	long *g_sampler_texture_refs = (long *)0x1910560;
	IDirect3DDevice9 *device = *(IDirect3DDevice9 **)0x50DADDC;
	bool *g_sampler_gamma_correction_array = (bool *)0x50DB200;

	device->SetTexture(0, texture);
	device->SetSamplerState(0, D3DSAMP_SRGBTEXTURE, 1);
	g_sampler_texture_refs[0] = -1;
	draw_custom_bitmap(info, display_bounds, 88);
}

void ui_draw_bitmap_widget_hook(s_gui_bitmap_widget_render_info *data, short_rectangle2d *display_bounds) // 0x108D37E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ui_draw_bitmap_widget_hook@@YAXPAUs_gui_bitmap_widget_render_info@@PAUshort_rectangle2d@@@Z");
	// `anonymous-namespace'::ui_draw_bitmap_widget_hook
	// short_rectangle2d *display_bounds;
	// void (*const ui_draw_bitmap_widget)(s_gui_bitmap_widget_render_info *, short_rectangle2d *);
		// e_surface old_surface;
		// IDirect3DTexture9 *texture;
		// __int32 player_index;
		// __int32 localPlayerIndex;
		// Blam::Network::Session *session;
	// function call : e_surface (*const)(long)
	// function call : e_surface (*const)(long, e_surface, long)
	// function call : void (*const)(s_gui_bitmap_widget_render_info *, short_rectangle2d *)
	// function call : void (*const)(s_gui_bitmap_widget_render_info *, short_rectangle2d *)

	void (*const ui_draw_bitmap_widget)(s_gui_bitmap_widget_render_info *, short_rectangle2d *) = (void (*)(s_gui_bitmap_widget_render_info *, short_rectangle2d *))0xB170F0;
	if ((data->flags >> 2) & 1)
	{
		e_surface old_surface = eldorado::c_rasterizer_get_render_target(0);
		draw_widget_blur(data, display_bounds);
		eldorado::c_rasterizer_set_render_target(0, old_surface, -1);
	}
	else if ((data->flags & (1 << 0)) & 1)
	{
		IDirect3DTexture9 *texture = CustomBitmapManager::Get()->BitmapGetTexture(data->storage_item_index);
		if (texture)
			draw_custom_bitmap(data, texture, display_bounds);
	}
	else if (data->bitmap_index != -1 && (data->bitmap_index & 0x8000))
	{
		__int32 player_index = data->bitmap_index & 0x7FFF;
		if (player_index > -1 && player_index < 16)
			draw_custom_emblem(data, display_bounds, data->bitmap_index & 0x7FFF);
		else
			ui_draw_bitmap_widget(data, display_bounds);
	}
	else if (data->bitmap_index != -1 && ((data->flags >> 3) & 1))
	{
		Blam::Network::Session *session = Blam::Network::GetActiveSession();
		__int32 localPlayerIndex = 16;
		if (session && session->IsEstablished())
			localPlayerIndex = session->MembershipInfo.GetPeerPlayer(session->MembershipInfo.LocalPeerIndex);
		draw_custom_emblem(data, display_bounds, localPlayerIndex);
	}
	else
	{
		ui_draw_bitmap_widget(data, display_bounds);
	}
}

void CRenderFullScreenBlur::Render() // 0x108D1A10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Render@CRenderFullScreenBlur@hades_file_local@@QAEXXZ");
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

	if (m_alpha == 0.0f)
		return;
	e_surface blur_surface = blur_display();
	s_rasterizer_screen_geometry_parameters params;
	memset(&params.texture_datum_index, 0, 0x94);
	params.surface_index = blur_surface;
	params.texture_datum_index = -1;
	params.alpha_blend_mode = 5;
	params.explicit_shader_index = -1;
	params.field_40 = 1.0f;
	params.field_44 = 1.0f;
	params.field_48 = 1.0f;
	params.field_4C = 1.0f;
	unsigned long *g_game_resolution = reinterpret_cast<unsigned long *>(0x19106C0);
	float display_width = (float)g_game_resolution[0];
	float display_height = (float)g_game_resolution[1];
	unsigned char alpha = (unsigned char)(m_alpha * 255.0f);
	unsigned long color = alpha << 24 | alpha << 16 | alpha << 8 | alpha;
	s_screen_vertex vertices[4];
	vertices[0].position = { 0.0f, 0.0f };
	vertices[0].texcoord = { 0.0f, 0.0f };
	vertices[0].color = color;
	vertices[1].position = { display_width, 0.0f };
	vertices[1].texcoord = { 1.0f, 0.0f };
	vertices[1].color = color;
	vertices[2].position = { display_width, display_height };
	vertices[2].texcoord = { 1.0f, 1.0f };
	vertices[2].color = color;
	vertices[3].position = { 0.0f, display_height };
	vertices[3].texcoord = { 0.0f, 1.0f };
	vertices[3].color = color;
	((void (*)(s_rasterizer_screen_geometry_parameters *, s_screen_vertex *))0xA46AD0)(&params, vertices);
}

void CRenderFullScreenBlur::Update() // 0x108D2030
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Update@CRenderFullScreenBlur@hades_file_local@@QAEXXZ");
	// `anonymous-namespace'::CRenderFullScreenBlur::Update
	// CRenderFullScreenBlur *const this;
	// bool enabled;
	// float m_transitionRateSeconds;
	// function call : float (*const)()

	bool enabled = Utils::Singleton<Modules::ModuleGame>::Instance().VarFullscreenBlur->ValueInt != 0;
	float m_transitionRateSeconds = Utils::Singleton<Modules::ModuleGame>::Instance().VarFullscreenBlurTime->ValueFloat;

	m_alpha += game_tick_length() * m_transitionRateSeconds * (2 * enabled - 1.0f);

	if (m_alpha > 1.0f)
		m_alpha = 1.0f;
	else if (m_alpha < 0.0f)
		m_alpha = 0.0f;
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_tag_block<s_explicit_shader_ref>::try_get_element(__int32, s_explicit_shader_ref **) const;
template s_explicit_shader_ref & c_tag_block<s_explicit_shader_ref>::operator[](__int32);
template s_explicit_shader_ref * c_tag_block<s_explicit_shader_ref>::get_element(__int32) const;

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { CRenderFullScreenBlur g_fullscreenMenuBlur; }
