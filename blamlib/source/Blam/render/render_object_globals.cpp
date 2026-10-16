/* ---------- headers */

#include "Blam/render/render_object_globals.hpp"
#include "hades/hades.h"

#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/tls.hpp"
#include "Blam/physics/havok_types.hpp"
#include "Blam/rasterizer/rasterizer_geometry.hpp"
#include "Blam/rasterizer/rasterizer_states.hpp"
#include "Blam/rasterizer/rasterizers_textures_cache.hpp"
#include "Blam/scenario/scenario.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_groups.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <wchar.h>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <limits>
#include <type_traits>

/* ---------- forward declarations */

struct s_render_object_globals;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern s_render_object_globals *render_object_globals_get();

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

s_render_object_globals *render_object_globals_get() // 0x10F13A40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_object_globals_get@@YAPAUs_render_object_globals@@XZ");

	return tls_getd().render_object_globals;
}

/* ---------- private code */
