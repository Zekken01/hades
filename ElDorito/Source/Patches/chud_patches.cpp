/* ---------- headers */

#include "hades/hades.h"

#include "Blam/camera/director.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/interface/chud/chud.hpp"
#include "Blam/interface/chud/chud_globals.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/tls.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/physics/havok_types.hpp"
#include "Blam/rasterizer/rasterizer.hpp"
#include "Blam/rasterizer/rasterizer_geometry.hpp"
#include "Blam/rasterizer/rasterizer_samplers.hpp"
#include "Blam/rasterizer/rasterizer_shaders.hpp"
#include "Blam/rasterizer/rasterizer_states.hpp"
#include "Blam/rasterizer/rasterizers_textures_cache.hpp"
#include "Blam/render/camera_fx_settings.hpp"
#include "Blam/render/views/render_player_view.hpp"
#include "Blam/shaders/render_method_submit.hpp"
#include "Blam/shaders/render_methods_definitions.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "Debug/DebugDraw.hpp"
#include "Modules/ModuleTweaks.hpp"
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

struct s_widget_geometry_properties;
namespace Modules
{
	class ModuleTweaks;
}

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Chud {}
	using namespace Patches::Chud;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Patches
{
	namespace Chud
	{
		extern void ApplyAll();
	}
}

/* ---------- globals */

namespace Utils
{
	Modules::ModuleTweaks *Utils::Singleton<Modules::ModuleTweaks>::m_instance; // 0x1195B5CC
}

/* ---------- private variables */

/* ---------- public code */

namespace Patches
{
	namespace Chud
	{
		_extern void _sub_10858520();
		void ApplyAll() // 0x10858520
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@Chud@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10858520();
		}
	}
}

extern s_widget_geometry_properties* _sub_10858300(s_widget_geometry_properties *const);
_inline s_widget_geometry_properties::s_widget_geometry_properties() // 0x10858300
{
	mangled_x86(MANGLED_TODO, "??0s_widget_geometry_properties@@QAE@XZ");
	// s_widget_geometry_properties *const this;
	compiler_generated();
	todo("implement");
	_sub_10858300(this);
}

/* ---------- private code */
