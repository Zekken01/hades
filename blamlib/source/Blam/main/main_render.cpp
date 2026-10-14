/* ---------- headers */

#include "Blam/main/main_render.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"

#include <stdio.h>

/* ---------- forward declarations */

struct c_player_render_camera_iterator;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

c_player_render_camera_iterator::c_player_render_camera_iterator() // 0x10F1D9D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0c_player_render_camera_iterator@@QAE@XZ");
	// c_player_render_camera_iterator *const this;
	// bool (*const terminal_is_being_read_internal)();
	// bool (*const rasterizer_get_is_widescreen)();
	// long (*const main_render_get_player_window_count)();
		// __int32 render_window_count;
		// __int32 window_count;
	// function call : bool (*const)()
	// function call : bool (*const)()
	// function call : long (*const)()
	// function call : bool (*const)()

	bool (*const terminal_is_being_read_internal)() = reinterpret_cast<bool (*)()>(0x53B570);
	long (*const main_render_get_player_window_count)() = reinterpret_cast<long (*)()>(0x589F00);
	bool (*const rasterizer_get_is_widescreen)() = reinterpret_cast<bool (*)()>(0xA1FC90);
	m_current_iteration = 0;
	m_output_user_index = -1;
	m_observer_result = nullptr;
	m_window_arrangement = 0;
	if (reinterpret_cast<bool (*)()>(0x67D270)() || terminal_is_being_read_internal())
	{
		m_window_count = 1;
	}
	else
	{
		__int32 window_count = 1;
		__int32 render_window_count = main_render_get_player_window_count();
		if (render_window_count > 1)
			window_count = render_window_count;
		if (window_count >= 4)
			window_count = 4;
		m_window_count = window_count;
		if (window_count > 1)
			m_window_arrangement = rasterizer_get_is_widescreen() + 1;
	}
}

/* ---------- private code */
