/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/geometry/geometry_definitions.hpp"
#include "Blam/geometry/geometry_sampler.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/data_array.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/physics/havok_types.hpp"
#include "Blam/rasterizer/rasterizer_geometry.hpp"
#include "Blam/rasterizer/rasterizer_globals.hpp"
#include "Blam/rasterizer/rasterizer_samplers.hpp"
#include "Blam/rasterizer/rasterizer_states.hpp"
#include "Blam/rasterizer/rasterizers_textures_cache.hpp"
#include "Blam/render/render_globals.hpp"
#include "Blam/scenario/scenario.hpp"
#include "Blam/shaders/render_method_submit.hpp"
#include "Blam/shaders/render_methods_definitions.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "Blam/visibility/visibility_items.hpp"
#include "Forge/Geoemetry.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
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

struct s_compression_info;

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;
namespace Forge {}
using namespace ::Forge;
namespace Forge
{
	namespace Reforge {}
	using namespace Forge::Reforge;
}

namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace RenderObject {}
	using namespace Patches::RenderObject;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Patches
{
	namespace RenderObject
	{
		extern void ApplyAll();
		extern bool GetPRTDisabled();
	}
}

/* ---------- globals */

/* ---------- private variables */

namespace
{
	extern bool g_prt_disabled; // 0x124083AC
}
/* ---------- public code */

namespace Patches
{
	namespace RenderObject
	{
		_extern void _sub_108DE300();
		void ApplyAll() // 0x108DE300
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@RenderObject@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_108DE300();
		}
	}
}

extern s_compression_info* _sub_108DDBA0(s_compression_info *const, s_compression_info const &);
_inline s_compression_info::s_compression_info(s_compression_info const &__that) // 0x108DDBA0
{
	mangled_x86(MANGLED_TODO, "??0s_compression_info@@QAE@ABU0@@Z");
	// s_compression_info const &__that;
	compiler_generated();
	todo("implement");
	_sub_108DDBA0(this, __that);
}

namespace Patches
{
	namespace RenderObject
	{
		_extern bool _sub_108DEC70();
		bool GetPRTDisabled() // 0x108DEC70
		{
			mangled_x86(MANGLED_TODO, "?GetPRTDisabled@RenderObject@Patches@@YA_NXZ");
			// procedure flags: nofpo
			todo("implement");
			bool __result = _sub_108DEC70();
			return __result;
		}
	}
}

/* ---------- private code */
