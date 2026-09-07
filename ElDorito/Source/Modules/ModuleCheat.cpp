/* ---------- headers */

#include "Modules/ModuleCheat.hpp"
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
#include "Blam/memory/static_array.inl"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/multiplayer_game_objects.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/scenario/scenario_definitions.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_block_index.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "Modules/ModuleBase.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <atomic>
#include <charconv>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <functional>
#include <initializer_list>
#include <iterator>
#include <limits>
#include <memory>
#include <mutex>
#include <ratio>
#include <stdexcept>
#include <stop_token>
#include <string>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

struct lambda_1;
namespace Modules
{
	class ModuleBase;
	class ModuleCheat;
}

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;
namespace Objects {}
using namespace ::Objects;

/* ---------- constants */

/* ---------- definitions */

//class cheat_all_objects::__l2::<lambda_1>
//{
//public:
//	void operator()() const;
//	<lambda_1>(cheat_all_objects::__l2::<lambda_1> &);
//	<lambda_1>(long const (&)[256], __int32 const &);
//private:
//	long objects[256]; // 0x0
//	__int32 count; // 0x400
//public:
//	cheat_all_objects::__l2::<lambda_1> &operator=(cheat_all_objects::__l2::<lambda_1> const &);
//};
//static_assert(sizeof(cheat_all_objects::__l2::<lambda_1>) == 1028, "Invalid cheat_all_objects::__l2::<lambda_1> size");

//class CheatDeleteWeapons::__l2::<lambda_1>
//{
//public:
//	void operator()() const;
//};
//static_assert(sizeof(CheatDeleteWeapons::__l2::<lambda_1>) == 1, "Invalid CheatDeleteWeapons::__l2::<lambda_1> size");

//struct CheatSpawn::__l2::s_group
//{
//	char const *tag; // 0x0
//	char const *name; // 0x4
//};
//static_assert(sizeof(CheatSpawn::__l2::s_group) == 8, "Invalid CheatSpawn::__l2::s_group size");

//class CheatSpawn::__l2::<lambda_1>
//{
//public:
//	void operator()() const;
//	<lambda_1>(CheatSpawn::__l2::<lambda_1> &);
//	<lambda_1>(unsigned long const &, long const &);
//private:
//	unsigned long group_tag; // 0x0
//	long tag_index; // 0x4
//public:
//	CheatSpawn::__l2::<lambda_1> &operator=(CheatSpawn::__l2::<lambda_1> const &);
//};
//static_assert(sizeof(CheatSpawn::__l2::<lambda_1>) == 8, "Invalid CheatSpawn::__l2::<lambda_1> size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Modules
{
	extern ModuleCheat* _sub_107955E0(Modules::ModuleCheat *const);
	ModuleCheat::ModuleCheat() : ModuleBase(todo_result<std::basic_string<char,std::char_traits<char>,std::allocator<char> >>()) // 0x107955E0
	{
		mangled_x86(MANGLED_TODO, "??0ModuleCheat@Modules@@QAE@XZ");
		// Modules::ModuleCheat *const this;
		todo("implement");
		_sub_107955E0(this);
	}
}

/* ---------- private code */
