/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/geometry/geometry_definitions.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/static_array.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/physics/collision_bsp.hpp"
#include "Blam/physics/havok_types.hpp"
#include "Blam/rasterizer/rasterizer.hpp"
#include "Blam/rasterizer/rasterizer_geometry.hpp"
#include "Blam/rasterizer/rasterizer_samplers.hpp"
#include "Blam/rasterizer/rasterizer_states.hpp"
#include "Blam/rasterizer/rasterizers_textures_cache.hpp"
#include "Blam/scenario/scenario.hpp"
#include "Blam/shaders/render_method_submit.hpp"
#include "Blam/shaders/render_methods_definitions.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/structures/structure_bsp_definitions.hpp"
#include "Blam/structures/structure_seams.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "Blam/visibility/visibility.hpp"
#include "Blam/visibility/visibility_items.hpp"
#include "Modules/ModuleGraphics.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Patches/PlayerPropertiesExtension.hpp"
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

struct c_collision_bsp_reference;
struct c_render_method_data;
struct real_matrix4x3;
struct s_cluster_reference;
struct s_instance_part;
struct s_mesh;
struct s_scenario_structure_bsp;
struct s_structure_bsp_path_finding;
struct s_structure_bsp_resources;
struct s_structure_cluster;
struct s_structure_instanced_geometry_instance;
namespace Modules
{
	class ModuleGraphics;
}
namespace
{
	struct s_decal_cylinder;
	struct c_instanced_geometry_iterator;
	struct s_instance_collision_test_arguements;
}

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Reach {}
	using namespace Patches::Reach;
}

/* ---------- constants */

/* ---------- definitions */

namespace
{
	#pragma pack(push, 4)
	struct s_decal_cylinder
	{
		real_matrix4x3 matrix; // 0x0
		float radius; // 0x34
		float height; // 0x38
	};
	#pragma pack(pop)
	static_assert(sizeof(s_decal_cylinder) == 60, "Invalid s_decal_cylinder size");

	struct c_instanced_geometry_iterator
	{
		static long const k_max_instances;
		c_instanced_geometry_iterator(s_cluster_reference *, s_decal_cylinder *, long);
		bool next_instance();
		bool next_cluster();
		bool next_instance_bucket();
		void next();
	private:
		s_decal_cylinder *m_cylinder; // 0x0
		s_cluster_reference *m_cluster_references; // 0x4
		long m_structure_bsp_index; // 0x8
		long m_cluster_reference_index; // 0xC
		s_scenario_structure_bsp *m_structure_bsp; // 0x10
		s_structure_cluster *m_cluster; // 0x14
		s_mesh *m_mesh; // 0x18
		long m_instance_bucket_count; // 0x1C
		long m_instance_bucket_index; // 0x20
		s_instance_part *m_instance_buckets; // 0x24
		unsigned long *m_visited_instance_bit_vector; // 0x28
		long _pad[127]; // 0x2C
		long m_instance_bucket_instance_count; // 0x228
		long m_instance_bucket_instance_index; // 0x22C
		long m_instance_index; // 0x230
		s_structure_instanced_geometry_instance *m_instance; // 0x234
	};
	static_assert(sizeof(c_instanced_geometry_iterator) == 568, "Invalid c_instanced_geometry_iterator size");

	struct s_instance_collision_test_arguements
	{
		__int32 bsp_index; // 0x0
		s_scenario_structure_bsp *structure_bsp; // 0x4
		s_structure_bsp_resources *collision_bsp_resource; // 0x8
		c_collision_bsp_reference collision_bsp_reference; // 0xC
		s_structure_bsp_path_finding *path_finding; // 0x14
	};
	static_assert(sizeof(s_instance_collision_test_arguements) == 24, "Invalid s_instance_collision_test_arguements size");
}
/* ---------- prototypes */

namespace Patches
{
	namespace Reach
	{
		extern void ApplyAfterInit();
	}
}

/* ---------- globals */

float (*c_render_method_data::m_context_interface)(long, long, long); // 0x1138DEE0
namespace Utils
{
	Modules::ModuleGraphics *Utils::Singleton<Modules::ModuleGraphics>::m_instance; // 0x1138DEDC
}

/* ---------- private variables */

/* ---------- public code */

namespace Patches
{
	namespace Reach
	{
		_extern void _sub_107BEB80();
		void ApplyAfterInit() // 0x107BEB80
		{
			mangled_x86(MANGLED_TODO, "?ApplyAfterInit@Reach@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_107BEB80();
		}
	}
}

/* ---------- private code */
