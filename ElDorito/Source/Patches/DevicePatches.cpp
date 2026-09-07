/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/data_array.inl"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Forge/ForgeDevice.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Patches/GamePatches.hpp"
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

class CForgeDeviceManager;
struct IGameSystem;
struct s_player_action_context;

namespace Utils {}
using namespace ::Utils;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Devices {}
	using namespace Patches::Devices;
	namespace Game {}
	using namespace Patches::Game;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Patches
{
	namespace Devices
	{
		extern void ApplyAll();
		extern bool PlayerConsiderDeviceInteraction(long player_index, long device_index, s_player_action_context *out_action_context);
	}
}

/* ---------- globals */

namespace Utils
{
	CForgeDeviceManager *Utils::Singleton<CForgeDeviceManager>::m_instance; // 0x1240833C
}

/* ---------- private variables */

/* ---------- public code */

namespace Patches
{
	namespace Devices
	{
		_extern void _sub_108CE320();
		void ApplyAll() // 0x108CE320
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@Devices@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_108CE320();
		}

		_extern bool _sub_108CED20(long, long, s_player_action_context *);
		bool PlayerConsiderDeviceInteraction(long player_index, long device_index, s_player_action_context *out_action_context) // 0x108CED20
		{
			mangled_x86(MANGLED_TODO, "?PlayerConsiderDeviceInteraction@Devices@Patches@@YA_NJJPAUs_player_action_context@@@Z");
			// s_player_action_context *out_action_context;
			// bool (*const player_consider_device_interaction)(long, long, s_player_action_context *);
			// function call : bool (*const)(long, long, s_player_action_context *)
			todo("implement");
			bool __result = _sub_108CED20(player_index, device_index, out_action_context);
			return __result;
		}
	}
}

extern CForgeDeviceManager* _sub_108CE160(CForgeDeviceManager *const);
_inline CForgeDeviceManager::CForgeDeviceManager() // 0x108CE160
{
	mangled_x86(MANGLED_TODO, "??0CForgeDeviceManager@@QAE@XZ");
	// CForgeDeviceManager *const this;
	compiler_generated();
	todo("implement");
	_sub_108CE160(this);
}

extern IGameSystem* _sub_108CE1C0(IGameSystem *const);
_inline IGameSystem::IGameSystem() // 0x108CE1C0
{
	mangled_x86(MANGLED_TODO, "??0IGameSystem@@QAE@XZ");
	// IGameSystem *const this;
	compiler_generated();
	todo("implement");
	_sub_108CE1C0(this);
}

_extern void _sub_108CE1F0(CForgeDeviceManager *const);
_inline CForgeDeviceManager::~CForgeDeviceManager() // 0x108CE1F0
{
	mangled_x86(MANGLED_TODO, "??1CForgeDeviceManager@@UAE@XZ");
	// CForgeDeviceManager *const this;
	compiler_generated();
	todo("implement");
	_sub_108CE1F0(this);
}

/* ---------- private code */
