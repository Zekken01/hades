/* ---------- headers */

#include "mods/map_load_crash_recovery_helper.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "CommandMap.hpp"
#include "ElDorito.hpp"
#include "mods/font_package.hpp"
#include "Pointer.hpp"
#include "Utils/Macros.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <algorithm>
#include <atomic>
#include <charconv>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <deque>
#include <exception>
#include <filesystem>
#include <forward_list>
#include <fstream>
#include <functional>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <mutex>
#include <optional>
#include <ostream>
#include <ratio>
#include <sstream>
#include <stdexcept>
#include <stop_token>
#include <streambuf>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

class c_map_load_crash_recovery_helper;
struct s_game_options;

namespace Utils {}
using namespace ::Utils;
namespace Utils
{
	namespace AntiCheat {}
	using namespace Utils::AntiCheat;
}

namespace Modules {}
using namespace ::Modules;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern std::atomic_flag g_gameIsCrashed;  // hades: added for 0X10787BF0

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern char const *const kMapLoadTempFile; // 0x11181B88
}
using namespace hades_file_local;
/* ---------- public code */

void c_map_load_crash_recovery_helper::map_load_start() // 0x107876B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?map_load_start@c_map_load_crash_recovery_helper@@QAEXXZ");
	// c_map_load_crash_recovery_helper *const this;
	// s_game_options *const intermediate_game_options;
	// function call : __int32 ()

	m_dirty_disked = false;
	m_map_load_end_time = -1;
	kMapLoadTempFileName = Utils::Singleton<ElDorito>::Instance().GetInstanceName().length() > 0 ? Utils::Singleton<ElDorito>::Instance().GetInstanceName() + "-" + kMapLoadTempFile : kMapLoadTempFile;
	s_game_options *const intermediate_game_options = (s_game_options *)0x2391800;
	if (intermediate_game_options->game_mode == _game_mode_mainmenu && (0 || !IsDebuggerPresent()))
	{
		if (std::filesystem::exists(kMapLoadTempFileName.c_str()))
		{
			Utils::Singleton<Modules::CommandMap>::Instance().ExecuteCommand("Game.MainMenuMod \"\"", true);
			Utils::Singleton<Modules::CommandMap>::Instance().ExecuteCommand("writeconfig", false);
			remove(kMapLoadTempFileName.c_str());
		}
		else
		{
			std::ofstream(kMapLoadTempFileName.c_str());
		}
	}
}

void c_map_load_crash_recovery_helper::map_load_end() // 0x10787660
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?map_load_end@c_map_load_crash_recovery_helper@@QAEXXZ");
	// c_map_load_crash_recovery_helper *const this;

	m_map_load_end_time = system_milliseconds();
}

void c_map_load_crash_recovery_helper::tick() // 0x10787D00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?tick@c_map_load_crash_recovery_helper@@QAEXXZ");
	// c_map_load_crash_recovery_helper *const this;

	if (m_map_load_end_time != -1 && system_milliseconds() - m_map_load_end_time > 3000)
	{
		m_map_load_end_time = -1;
		remove(kMapLoadTempFileName.c_str());
	}
}

void c_map_load_crash_recovery_helper::shutdown() // 0x10787BF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?shutdown@c_map_load_crash_recovery_helper@@QAEXXZ");
	// c_map_load_crash_recovery_helper *const this;

	if (!g_gameIsCrashed.test() && !m_dirty_disked)
	{
		remove(kMapLoadTempFileName.c_str());
	}
}

void c_map_load_crash_recovery_helper::dirty_disk() // 0x107875B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?dirty_disk@c_map_load_crash_recovery_helper@@QAEXXZ");
	// c_map_load_crash_recovery_helper *const this;

	m_dirty_disked = true;
}

/* ---------- private code */
