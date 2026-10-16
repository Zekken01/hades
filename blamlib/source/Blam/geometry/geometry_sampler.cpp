/* ---------- headers */

#include "Blam/geometry/geometry_sampler.hpp"
#include "hades/hades.h"

#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/physics/havok_types.hpp"
#include "Blam/rasterizer/rasterizer_geometry.hpp"
#include "Blam/rasterizer/rasterizers_textures_cache.hpp"
#include "Blam/scenario/scenario.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_groups.hpp"

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
#include <limits>
#include <mutex>
#include <ratio>
#include <stdexcept>
#include <stop_token>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>

/* ---------- forward declarations */

struct c_geometry_sampler;
struct real_point3d;
struct real_vector3d;
struct s_geometry_sample;
struct s_geometry_test_result;

/* ---------- constants */

/* ---------- definitions */

struct c_geometry_sampler
{
	static e_geometry_sampler_outcome (*const sample)(real_point3d *, real_vector3d *, long, long, bool, char, s_geometry_sample *);
	static e_geometry_collision_type (*const geometry_test_vector)(real_point3d *, real_vector3d *, char, __int32, char, __int32, char, s_geometry_test_result *);
	static long (*interpolate_geometry_samples)(s_geometry_sample *, s_geometry_sample *, float, char);
};

/* ---------- prototypes */

/* ---------- globals */

extern s_geometry_sample *g_default_geometry_sample; // 0x1135A0B4
long (*c_geometry_sampler::interpolate_geometry_samples)(s_geometry_sample *, s_geometry_sample *, float, char) = reinterpret_cast<decltype(c_geometry_sampler::interpolate_geometry_samples)>(0xA425E0); // 0x1135A0B8

/* ---------- private variables */

/* ---------- public code */

/* ---------- private code */
