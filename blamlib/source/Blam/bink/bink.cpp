/* ---------- headers */

#include "Blam/bink/bink.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/math/integer_math_definitions.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/tls.hpp"
#include "Blam/rasterizer/rasterizer.hpp"
#include "Blam/rasterizer/rasterizer_samplers.hpp"
#include "Blam/rasterizer/rasterizer_shaders.hpp"
#include "Blam/rasterizer/rasterizer_states.hpp"
#include "Blam/rasterizer/rasterizer_vertex_types.hpp"
#include "Blam/rasterizer/rasterizers_textures_cache.hpp"
#include "Blam/shaders/render_method_submit.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"

#include <Windows.h>

/* ---------- forward declarations */

struct s_bink_globals;
struct s_screen_vertex;
struct short_rectangle2d;
struct tls_data;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace eldorado
{
	// Functions in eldorado.exe, named from the game's own symbols where it has them.
	static auto const bink_copy_frame_planes = reinterpret_cast<void (*)(s_bink_globals::s_bink_runtime::s_bink_video_frame *, __int32)>(0x615EE0);  // no symbol; named from what it does
}

namespace eldorado
{
	// Functions in eldorado.exe, named from the game's own symbols.
	static auto const bink_setup_rasterizer = reinterpret_cast<void (*)(__int32)>(0x6179B0);
	static auto const c_rasterizer_normalize_screenspace_vertices = reinterpret_cast<void (*)(float, float, float, float, s_screen_vertex *, long)>(0xA46910);
	static auto const c_rasterizer_set_srgbwrite = reinterpret_cast<void (*)(bool)>(0xA48EB0);
	static auto const release_unused_textures = reinterpret_cast<__int32 (*)(__int32)>(0x618870);
}

namespace eldorado
{
	// Functions in eldorado.exe, named as in ManagedDonkey.
	static auto const bink_playback_active = reinterpret_cast<bool (*)()>(0x616910);
	static auto const c_rasterizer_clear_sampler_textures = reinterpret_cast<void (*)()>(0xA22AB0);
	static auto const rasterizer_draw_textured_screen_quad1 = reinterpret_cast<void (*)(void *, char)>(0xA465F0);
}

extern void bink_display_frame(short_rectangle2d *rect);
extern bool bink_prediction_queued_and_not_active();

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern __int32 *g_bink_frame_width; // 0x11359FE0
	extern __int32 *g_bink_frame_height; // 0x11359FE4
}
using namespace hades_file_local;
/* ---------- public code */

void bink_display_frame(short_rectangle2d *rect) // 0x10F18130
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?bink_display_frame@@YAXPAUshort_rectangle2d@@@Z");

	bool (*const sub_42E2C0)() = (bool (*)())0x42E2C0;
	void (*const sub_52C5A0)(__int32) = (void (*)(__int32))0x52C5A0;
	void (*const sub_52C580)(__int32) = (void (*)(__int32))0x52C580;
	void (*const interface_get_current_display_or_window_settings)(short_rectangle2d *, short_rectangle2d *, short_rectangle2d *, short_rectangle2d *) = (void (*)(short_rectangle2d *, short_rectangle2d *, short_rectangle2d *, short_rectangle2d *))0xA9FA40;
	if (sub_42E2C0())
		sub_52C5A0(10);
	tls_data *tls = (tls_data *)tls_get(0);
	s_bink_globals *bink_globals = s_bink_globals::get();
	__int32 texture_index;
	if (bink_globals->flags & 0x100)
		texture_index = bink_globals->bink_runtime.frame.framebuffers.FrameNum;
	else
		texture_index = tls->bink_gamestate->runtime_frame_texture_index;
	if (eldorado::bink_playback_active() && texture_index != -1)
	{
		eldorado::release_unused_textures(texture_index);
		eldorado::bink_copy_frame_planes(&bink_globals->bink_runtime.frame, texture_index);
		__int32 buffer_width = bink_globals->bink_runtime.frame.framebuffers.YABufferWidth;
		__int32 buffer_height = bink_globals->bink_runtime.frame.framebuffers.YABufferHeight;
		__int32 width = rect->x1 - rect->x0;
		__int32 height = rect->y1 - rect->y0;
		s_screen_vertex vertices[4];
		memset(vertices, 0, sizeof(vertices));
		for (__int32 i = 0; i < 4; i++)
		{
			float u;
			float v;
			float x;
			float y;
			if ((i + 1) & 2)
				u = (float)buffer_width / *g_bink_frame_width;
			else
				u = 0.0f;
			if (i <= 1)
				v = 0.0f;
			else
				v = (float)buffer_height / *g_bink_frame_height;
			if ((i + 1) & 2)
				x = rect->x1;
			else
				x = rect->x0;
			if (i <= 1)
				y = rect->y0;
			else
				y = rect->y1;
			vertices[i].position = { x, y };
			vertices[i].texcoord = { u, v };
		}
		vertices[0].color = 0xFFFFFFFF;
		vertices[1].color = 0xFFFFFFFF;
		vertices[2].color = 0xFFFFFFFF;
		vertices[3].color = 0xFFFFFFFF;
		eldorado::bink_setup_rasterizer(texture_index);
		short_rectangle2d fullscreen_pixel_bounds;
		interface_get_current_display_or_window_settings(&fullscreen_pixel_bounds, nullptr, nullptr, nullptr);
		eldorado::c_rasterizer_normalize_screenspace_vertices(1.0f / (fullscreen_pixel_bounds.x1 - fullscreen_pixel_bounds.x0), 1.0f / (fullscreen_pixel_bounds.y1 - fullscreen_pixel_bounds.y0), fullscreen_pixel_bounds.x0, fullscreen_pixel_bounds.y0, vertices, 4);
		eldorado::c_rasterizer_set_srgbwrite(false);
		eldorado::rasterizer_draw_textured_screen_quad1(vertices, 0);
		eldorado::c_rasterizer_set_srgbwrite(true);
		eldorado::c_rasterizer_clear_sampler_textures();
		bink_globals->bink_runtime.frame.textures[texture_index].displayed = true;
	}
	if (sub_42E2C0())
		sub_52C580(10);
}

bool bink_prediction_queued_and_not_active() // 0x10F18760
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?bink_prediction_queued_and_not_active@@YA_NXZ");

	s_bink_globals *bink_globals = s_bink_globals::get();
	return bink_globals->pending_prediction_message.queued_state == 1;
}

s_bink_globals *s_bink_globals::get() // 0x10F187F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get@s_bink_globals@@SAPAU1@XZ");

	return (s_bink_globals *)0x244E298;
}

/* ---------- private code */

/* ---------- data definitions */
namespace hades_file_local { __int32 *g_bink_frame_width = reinterpret_cast<__int32 *>(0x18BB398); }
namespace hades_file_local { __int32 *g_bink_frame_height = reinterpret_cast<__int32 *>(0x18BB39C); }
