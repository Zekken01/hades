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
	// static ...; // 0x10F18618
	// static ...; // 0x10F18600
	// static ...; // 0x10F185E8
	// static ...; // 0x10F185E0
	// short_rectangle2d *rect;
	// s_bink_globals *bink_globals;
	// tls_data *tls;
	// void (*const interface_get_current_display_or_window_settings)(short_rectangle2d *, short_rectangle2d *, short_rectangle2d *, short_rectangle2d *);
	// bool (*const sub_42E2C0)();
	// void (*const sub_52C580)(__int32);
	// __int32 texture_index;
	// void (*const sub_52C5A0)(__int32);
		// __int32 buffer_width;
		// s_screen_vertex vertices[4];
		// __int32 buffer_height;
		// __int32 width;
		// __int32 height;
		// short_rectangle2d fullscreen_pixel_bounds;
			// __int32 i;
				// float u;
				// float x;
				// float y;
				// float v;
	// function call : bool (*const)()
	// function call : void (*const)(__int32)
	// function call : bool (*const)()
	// function call : __int32 (*const)(__int32)
	// function call : void (*const)(s_bink_globals::s_bink_runtime::s_bink_video_frame *, __int32)
	// function call : void (*const)(__int32)
	// function call : void (*const)(short_rectangle2d *, short_rectangle2d *, short_rectangle2d *, short_rectangle2d *)
	// function call : void (*const)(float, float, float, float, s_screen_vertex *, long)
	// function call : void (*const)(bool)
	// function call : void (*const)(void *, char)
	// function call : void (*const)(bool)
	// function call : void (*const)()
	// function call : bool (*const)()
	// function call : void (*const)(__int32)

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
	if (((bool (*const)())0x616910)() && texture_index != -1)
	{
		((__int32 (*const)(__int32))0x618870)(texture_index);
		((void (*const)(s_bink_globals::s_bink_runtime::s_bink_video_frame *, __int32))0x615EE0)(&bink_globals->bink_runtime.frame, texture_index);
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
		((void (*const)(__int32))0x6179B0)(texture_index);
		short_rectangle2d fullscreen_pixel_bounds;
		interface_get_current_display_or_window_settings(&fullscreen_pixel_bounds, nullptr, nullptr, nullptr);
		((void (*const)(float, float, float, float, s_screen_vertex *, long))0xA46910)(1.0f / (fullscreen_pixel_bounds.x1 - fullscreen_pixel_bounds.x0), 1.0f / (fullscreen_pixel_bounds.y1 - fullscreen_pixel_bounds.y0), fullscreen_pixel_bounds.x0, fullscreen_pixel_bounds.y0, vertices, 4);
		((void (*const)(bool))0xA48EB0)(false);
		((void (*const)(void *, char))0xA465F0)(vertices, 0);
		((void (*const)(bool))0xA48EB0)(true);
		((void (*const)())0xA22AB0)();
		bink_globals->bink_runtime.frame.textures[texture_index].displayed = true;
	}
	if (sub_42E2C0())
		sub_52C580(10);
}

bool bink_prediction_queued_and_not_active() // 0x10F18760
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?bink_prediction_queued_and_not_active@@YA_NXZ");
	// procedure flags: nofpo
	// s_bink_globals *bink_globals;

	s_bink_globals *bink_globals = s_bink_globals::get();
	return bink_globals->pending_prediction_message.queued_state == 1;
}

s_bink_globals *s_bink_globals::get() // 0x10F187F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get@s_bink_globals@@SAPAU1@XZ");
	// procedure flags: nofpo

	return (s_bink_globals *)0x244E298;
}

/* ---------- private code */
