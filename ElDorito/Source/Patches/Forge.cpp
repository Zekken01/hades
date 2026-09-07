/* ---------- headers */

#include "hades/hades.h"

#include "Blam/BlamInput.hpp"
#include "Blam/BlamNetwork.hpp"
#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/effects/screen_effect.hpp"
#include "Blam/fmod/fmod_functions.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/engine/game_engine_sandbox.hpp"
#include "Blam/game/game_engine_candy_monitor.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/function_definitions.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/math/sound_math.hpp"
#include "Blam/memory/bitstream.hpp"
#include "Blam/memory/data_array.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/physics/havok_component.hpp"
#include "Blam/physics/havok_types.hpp"
#include "Blam/physics/havok_utilities.hpp"
#include "Blam/rasterizer/rasterizer_game_states.hpp"
#include "Blam/rasterizer/rasterizer_geometry.hpp"
#include "Blam/saved_games/scenario_map_variant.hpp"
#include "Blam/scenario/scenario.hpp"
#include "Blam/sounds/sound_memory.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "CommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Console/Console.hpp"
#include "ElDorito.hpp"
#include "Forge/ForgeDevice.hpp"
#include "Forge/ForgeUndo.hpp"
#include "Forge/ForgeUndoMapVariant.hpp"
#include "Forge/Geoemetry.hpp"
#include "Forge/ObjectSet.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Patches/GamePatches.hpp"
#include "Patches/Ui.hpp"
#include "Pointer.hpp"
#include "ThirdParty/rapidjson/allocators.h"
#include "ThirdParty/rapidjson/encodedstream.h"
#include "ThirdParty/rapidjson/error/error.h"
#include "ThirdParty/rapidjson/internal/biginteger.h"
#include "ThirdParty/rapidjson/internal/diyfp.h"
#include "ThirdParty/rapidjson/internal/ieee754.h"
#include "ThirdParty/rapidjson/internal/pow10.h"
#include "ThirdParty/rapidjson/internal/strtod.h"
#include "ThirdParty/rapidjson/memorystream.h"
#include "ThirdParty/rapidjson/reader.h"
#include "Utils/EventSink.hpp"
#include "Utils/Macros.hpp"
#include "Utils/NameValueTable.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/StlUtil.hpp"
#include "Utils/String.hpp"
#include "Web/Bridge/WebRendererQueryHandler.hpp"
#include "Web/Ui/Screen.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <atomic>
#include <bitset>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <deque>
#include <exception>
#include <functional>
#include <initializer_list>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <memory>
#include <ostream>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <system_error>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <unordered_map>
#include <utility>
#include <vector>

/* ---------- forward declarations */

class CForgeDeviceManager;
class c_function_definition;
struct c_periodic_function_compact;
struct real_vector3d;
struct s_function_definition_internal;
struct s_monitorState;
struct s_selectionState;
struct s_tag_data;

namespace Utils {}
using namespace ::Utils;
namespace Utils
{
	namespace AntiCheat {}
	using namespace Utils::AntiCheat;
}

namespace Modules {}
using namespace ::Modules;
namespace Patches
{
	namespace Forge {}
	using namespace Patches::Forge;
}

namespace Forge
{
	namespace Magnets {}
	using namespace Forge::Magnets;
	namespace Selection {}
	using namespace Forge::Selection;
	namespace Prefabs {}
	using namespace Forge::Prefabs;
	namespace Volumes {}
	using namespace Forge::Volumes;
	namespace SelectionRenderer {}
	using namespace Forge::SelectionRenderer;
	namespace Reforge {}
	using namespace Forge::Reforge;
}

namespace base
{
	namespace internal {}
	using namespace base::internal;
}

namespace Web {}
using namespace ::Web;
namespace Web
{
	namespace Ui {}
	using namespace Web::Ui;
}

namespace Web
{
	namespace Ui
	{
		namespace ScreenLayer {}
		using namespace Web::Ui::ScreenLayer;
		namespace WebForge {}
		using namespace Web::Ui::WebForge;
		namespace WebConsole {}
		using namespace Web::Ui::WebConsole;
	}
}

namespace Web
{
	namespace Browser {}
	using namespace Web::Browser;
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge {}
		using namespace Web::Browser::Bridge;
	}
}

namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Camera {}
	using namespace Patches::Camera;
	namespace Game {}
	using namespace Patches::Game;
}

namespace Console {}
using namespace ::Console;
namespace Blam {}
using namespace ::Blam;

/* ---------- constants */

/* ---------- definitions */

struct s_monitorState
{
	bool IsValid; // 0x0
	bool MonitorLastTick; // 0x1
	bool NoclipLastTick; // 0x2
	long HeldObjectIndex; // 0x4
	long HeldObjectRootNode; // 0x8
	real_vector3d GrabOffset; // 0xC
	s_monitorState(); /* compiler_generated() */
};
// static_assert(sizeof(s_monitorState) == 24, "Invalid s_monitorState size");
// Withheld: the type inventory does not describe this type, so its
// padding could not be reconstructed.

struct s_selectionState
{
	public:
	struct ChildInfo
	{
		real_vector3d displacement; // 0x0
		float scale; // 0xC
		ChildInfo(); /* compiler_generated() */
	};
	// static_assert(sizeof(ChildInfo) == 16, "Invalid ChildInfo size");
	// Withheld: the type inventory does not describe this type, so its
	// padding could not be reconstructed.
	public:
	real_point3d initialPosition; // 0x0
	float initialScale; // 0xC
	std::unordered_map<int,ChildInfo,std::hash<int>,std::equal_to<int>,std::allocator<std::pair<int const ,ChildInfo> > > children; // 0x10
	s_selectionState(s_selectionState &); /* compiler_generated() */
	s_selectionState(s_selectionState const &); /* compiler_generated() */
	s_selectionState(); /* compiler_generated() */
	~s_selectionState(); /* compiler_generated() */
	s_selectionState &operator=(s_selectionState &); /* compiler_generated() */
	s_selectionState &operator=(s_selectionState const &); /* compiler_generated() */
};
// static_assert(sizeof(s_selectionState) == 56, "Invalid s_selectionState size");
// Withheld: the type inventory does not describe this type, so its
// padding could not be reconstructed.

namespace
{

}
//struct light_intensity_function_evaluate::__l2::s_functionData
//{
//	s_function_definition_internal header; // 0x0
//	c_periodic_function_compact periodic; // 0x20
//};
//static_assert(sizeof(light_intensity_function_evaluate::__l2::s_functionData) == 52, "Invalid light_intensity_function_evaluate::__l2::s_functionData size");

namespace Patches
{
	namespace Forge
	{
		typedef void (*ItemSpawnedCallback)(unsigned __int32);
	}
}

/* ---------- prototypes */

namespace Patches
{
	namespace Forge
	{
		extern void ApplyAll();
		extern void ApplyAfterTagsLoaded();
		extern void Tick();
		extern void OnItemSpawned(void (*callback)(unsigned __int32));
	}
}

/* ---------- globals */

/* ---------- private variables */

namespace
{
	extern float const HELDOBJECT_DISTANCE_MIN; // 0x111AFB88
	extern float const HELDOBJECT_DISTANCE_CHANGE_MULTIPLIER; // 0x111AFB8C
	extern float const MONITOR_MOVEMENT_SPEEDS[7]; // 0x111AFB90
	extern wchar_t const *MONITOR_MOVEMENT_SPEED_NAMES[7]; // 0x11354370
	extern std::vector<void (__cdecl*)(unsigned int),std::allocator<void (__cdecl*)(unsigned int)> > s_ItemSpawnedCallbacks; // 0x124584C0
	extern real_vector3d global_zero3d; // 0x111AFB58
}
/* ---------- public code */

extern c_function_definition* _sub_10A5EEF0(c_function_definition *const);
_inline c_function_definition::c_function_definition() // 0x10A5EEF0
{
	mangled_x86(MANGLED_TODO, "??0c_function_definition@@QAE@XZ");
	// c_function_definition *const this;
	compiler_generated();
	todo("implement");
	_sub_10A5EEF0(this);
}

extern s_tag_data* _sub_10A5EF40(s_tag_data *const);
_inline s_tag_data::s_tag_data() // 0x10A5EF40
{
	mangled_x86(MANGLED_TODO, "??0s_tag_data@@QAE@XZ");
	// s_tag_data *const this;
	compiler_generated();
	todo("implement");
	_sub_10A5EF40(this);
}

namespace Patches
{
	namespace Forge
	{
		_extern void _sub_10A60560();
		void ApplyAll() // 0x10A60560
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@Forge@Patches@@YAXXZ");
			// procedure flags: nofpo
			// CForgeDeviceManager *forgeDeviceManager;
			todo("implement");
			_sub_10A60560();
		}

		_extern void _sub_10A603E0();
		void ApplyAfterTagsLoaded() // 0x10A603E0
		{
			mangled_x86(MANGLED_TODO, "?ApplyAfterTagsLoaded@Forge@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10A603E0();
		}

		_extern void _sub_10A674B0();
		void Tick() // 0x10A674B0
		{
			mangled_x86(MANGLED_TODO, "?Tick@Forge@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10A674B0();
		}

		_extern void _sub_10A66A20(void (*)(unsigned __int32));
		void OnItemSpawned(void (*callback)(unsigned __int32)) // 0x10A66A20
		{
			mangled_x86(MANGLED_TODO, "?OnItemSpawned@Forge@Patches@@YAXP6AXI@Z@Z");
			// void (*callback)(unsigned __int32);
			todo("implement");
			_sub_10A66A20(callback);
		}
	}
}

/* ---------- private code */
