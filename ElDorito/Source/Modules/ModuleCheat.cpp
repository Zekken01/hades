/* ---------- headers */

#include "Modules/ModuleCheat.hpp"
#include "hades/hades.h"

#include "Blam/cache/tag_iterator.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_globals.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/multiplayer_definitions.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/static_array.inl"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/multiplayer_game_objects.hpp"
#include "Blam/objects/object_definitions.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/scenario/scenario_definitions.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_block_index.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
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
struct real_point3d;
struct real_vector3d;
struct s_damage_owner;
struct s_game_globals;
struct s_multiplayer_globals_definition;
struct s_object_definition;
struct s_object_placement_data;
struct s_player_datum;
struct s_tag_iterator;
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

void cheat_objects(long const *objects, __int32 count);
bool cheat_all_objects(long group_tag, bool everything);
bool CheatAllWeapons(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &args, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnValue);
bool CheatAllVehicles(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &args, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnValue);
bool CheatAllEquipment(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &args, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnValue);
bool CheatDeleteWeapons(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &args, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnValue);
bool CheatSpawn(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &args, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnValue);

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

_extern void _sub_107977F0(long const *, __int32);
void cheat_objects(long const *objects, __int32 count) // 0x107977F0
{
	// `anonymous-namespace'::cheat_objects
	// static ...; // 0x10797C08
	// static ...; // 0x10797BFE
	// static ...; // 0x10797BF4
	// static ...; // 0x10797BC4
	// static ...; // 0x10797BBC
	// long const *objects;
	// __int32 count;
	// s_player_datum *player;
	// long player_index;
	// real_point3d player_position;
	// real_vector3d player_forward;
	// float max_radius;
	// real_vector3d player_up;
	// void (*const c_map_variant__register_object)(long, long, bool);
	{
		// __int32 i;
		{
			// s_object_definition *definition;
		}
	}
	{
		{
			// s_object_placement_data placement;
			// long object_index;
			// float theta;
		}
	}
	// function call : unsigned long (*const)(long)
	// function call : void (*const)(unsigned long, real_point3d *)
	// function call : void (*const)(long, real_vector3d *, real_vector3d *)
	// function call : void *(*const)(unsigned long, long)
	// function call : void (*const)(s_object_placement_data *, long, unsigned long, s_damage_owner *)
	// function call : long (*const)(s_object_placement_data *)
	// function call : void (*const)(long)
	// function call : void (*const)(long)
	todo("implement");
	_sub_107977F0(objects, count);
}

_extern bool _sub_107971D0(long, bool);
bool cheat_all_objects(long group_tag, bool everything) // 0x107971D0
{
	// `anonymous-namespace'::cheat_all_objects
	// static ...; // 0x107976A5
	// static ...; // 0x107976A0
	// static ...; // 0x1079767C
	// static ...; // 0x10797674
	// long group_tag;
	// bool everything;
	// __int32 count;
	// long objects[256];
	// s_game_globals *globals;
	{
		// s_tag_iterator iter;
		{
			// long index;
		}
	}
	{
		// s_multiplayer_globals_definition *mulg;
		{
			// __int32 i;
		}
		{
		}
		{
		}
	}
	// function call : void (*const)(s_tag_iterator *, long)
	// function call : long (*const)(s_tag_iterator *)
	// function call : void *(*const)(unsigned long, long)
	todo("implement");
	bool __result = _sub_107971D0(group_tag, everything);
	return __result;
}

_extern bool _sub_10796430(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CheatAllWeapons(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &args, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnValue) // 0x10796430
{
	// `anonymous-namespace'::CheatAllWeapons
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnValue;
	todo("implement");
	bool __result = _sub_10796430(args, returnValue);
	return __result;
}

_extern bool _sub_10796390(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CheatAllVehicles(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &args, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnValue) // 0x10796390
{
	// `anonymous-namespace'::CheatAllVehicles
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnValue;
	todo("implement");
	bool __result = _sub_10796390(args, returnValue);
	return __result;
}

_extern bool _sub_107962F0(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CheatAllEquipment(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &args, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnValue) // 0x107962F0
{
	// `anonymous-namespace'::CheatAllEquipment
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnValue;
	todo("implement");
	bool __result = _sub_107962F0(args, returnValue);
	return __result;
}

_extern bool _sub_107964D0(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CheatDeleteWeapons(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &args, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnValue) // 0x107964D0
{
	// `anonymous-namespace'::CheatDeleteWeapons
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnValue;
	todo("implement");
	bool __result = _sub_107964D0(args, returnValue);
	return __result;
}

_extern bool _sub_107965A0(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CheatSpawn(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &args, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnValue) // 0x107965A0
{
	// `anonymous-namespace'::CheatSpawn
	// static ...; // 0x10796950
	// static ...; // 0x10796946
	// static ...; // 0x1079693C
	// static ...; // 0x1079690C
	// static ...; // 0x10796904
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &args;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnValue;
	// long tag_index;
	// unsigned long group_tag;
	// static CheatSpawn::__l2::s_group `CheatSpawn'::`2'::groups[18]; // 0x1134DC20
	// __int32 index;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > group_name;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &specifier;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > name;
	// unsigned __int32 pos;
	{
		// __int32 i;
	}
	todo("implement");
	bool __result = _sub_107965A0(args, returnValue);
	return __result;
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_tag_block<s_multiplayer_consumable>::try_get_element(__int32, s_multiplayer_consumable **) const;
template bool c_tag_block<s_multiplayer_vehicle>::try_get_element(__int32, s_multiplayer_vehicle **) const;
template bool c_tag_block<s_multiplayer_weapon>::try_get_element(__int32, s_multiplayer_weapon **) const;
template long s_static_array<long,4>::get_count();
template s_multiplayer_consumable & c_tag_block<s_multiplayer_consumable>::operator[](__int32);
template s_multiplayer_consumable * c_tag_block<s_multiplayer_consumable>::get_element(__int32) const;
template s_multiplayer_vehicle & c_tag_block<s_multiplayer_vehicle>::operator[](__int32);
template s_multiplayer_vehicle * c_tag_block<s_multiplayer_vehicle>::get_element(__int32) const;
template s_multiplayer_weapon & c_tag_block<s_multiplayer_weapon>::operator[](__int32);
template s_multiplayer_weapon * c_tag_block<s_multiplayer_weapon>::get_element(__int32) const;
