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
#include "Objects/ObjectMessaging.hpp"

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

#include <format>  // hades: added for 0x107965A0
long tag_find_by_name(unsigned long group_tag, char const *name);  // hades: added for 0x107965A0  // hades: added for 0x107965A0
extern s_object_data *object_get(unsigned long object_index); extern s_object_data *(*const object_try_and_get_and_verify_type)(unsigned long, c_enum<e_object_type, long>);  // hades: added for 0x107965A0; the second for CheatDeleteWeapons' lambda

extern void (*const object_get_world_position)(unsigned long, real_point3d *);  // hades: added for 0x107977F0
extern void (*const object_placement_data_new)(s_object_placement_data *, long, unsigned long, s_damage_owner *);  // hades: added for 0x107977F0
s_player_datum *player_get(unsigned long player_index);  // hades: added for 0x107977F0
bool tag_loaded(long tag_index);  // hades: added for 0x107977F0

void cheat_objects(long const *objects, __int32 count);
bool cheat_all_objects(long group_tag, bool everything);
bool CheatAllWeapons(std::vector<std::string> const &args, std::string &returnValue);
bool CheatAllVehicles(std::vector<std::string> const &args, std::string &returnValue);
bool CheatAllEquipment(std::vector<std::string> const &args, std::string &returnValue);
bool CheatDeleteWeapons(std::vector<std::string> const &args, std::string &returnValue);
bool CheatSpawn(std::vector<std::string> const &args, std::string &returnValue);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Modules
{
	ModuleCheat::ModuleCheat() : ModuleBase("Cheat") /* hades-mem-init: : ModuleBase(todo_result<std::string>()) */ // 0x107955E0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0ModuleCheat@Modules@@QAE@XZ");

		AddCommand("AllWeapons", "cheat_all_weapons", "Gives the player all weapons", eCommandFlagsHostOnly, CheatAllWeapons);
		AddCommand("AllVehicles", "cheat_all_vehicles", "Gives the player all vehicles", eCommandFlagsHostOnly, CheatAllVehicles);
		AddCommand("AllEquipment", "cheat_all_equipment", "Gives the player all equipment", eCommandFlagsHostOnly, CheatAllEquipment);
		AddCommand("DeleteWeapons", "cheat_delete_weapons", "Deletes the current weapons", eCommandFlagsHostOnly, CheatDeleteWeapons);
		AddCommand("Spawn", "drop", "Spawn an object", eCommandFlagsHostOnly, CheatSpawn, { "tag name" });
	}
}

/* ---------- private code */

void cheat_objects(long const *objects, __int32 count) // 0x107977F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?cheat_objects@@YAXPBJH@Z");

	void (*const c_map_variant__register_object)(long, long, bool) = reinterpret_cast<void (*)(long, long, bool)>(0x584790);
	long player_index = ((unsigned long (*)(long))0x589C30)(0);
	if (player_index == -1)
		return;
	s_player_datum *player = player_get(player_index);
	if (player->unit_index == -1)
		return;
	real_point3d player_position;
	object_get_world_position(player->unit_index, &player_position);
	real_vector3d player_forward;
	real_vector3d player_up;
	((void (*)(long, real_vector3d *, real_vector3d *))0xB2E490)(player->unit_index, &player_forward, &player_up);
	float max_radius = 0.0f;
	for (__int32 i = 0; i < count; i++)
	{
		if (!tag_loaded(objects[i]))
			continue;
		s_object_definition *definition = (s_object_definition *)tag_get('obje', objects[i]);
		max_radius = fmaxf(max_radius, definition->bounding_radius * 1.2f + 2.0f);
	}
	for (__int32 i = 0; i < count; i++)
	{
		if (objects[i] == -1)
			continue;
		if (!tag_loaded(objects[i]))
			continue;
		float theta = atan2(player_forward.i, player_forward.j) + i * 6.2831855f / count;
		s_object_placement_data placement;
		object_placement_data_new(&placement, objects[i], -1, nullptr);
		placement.forward = player_forward;
		placement.up = player_up;
		placement.relative_position.x = cos(theta) * max_radius + player_position.x;
		placement.relative_position.y = sin(theta) * max_radius + player_position.y;
		placement.relative_position.z = fmaxf(0.8f, max_radius / 2.0f) + player_position.z;
		long object_index = ((long (*)(s_object_placement_data *))0xB30440)(&placement);
		if (object_index != -1)
		{
			((void (*)(long))0x4B2CD0)(object_index);
			((void (*)(long))0x58FFB0)(object_index);
		}
	}
}

#line 252
bool cheat_all_objects(long group_tag, bool everything) // 0x107971D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?cheat_all_objects@@YA_NJ_N@Z");
#line 272

	long objects[256];
	__int32 count = 0;
	s_game_globals *globals = game_globals_get();
	if (everything || globals->MultiplayerGlobals.index == -1)
	{
		s_tag_iterator iter;
		((void(__cdecl *)(s_tag_iterator *, long))0x5033E0)(&iter, group_tag);
		long index = 0;
		while (index = ((long(__cdecl *)(s_tag_iterator *))0x503400)(&iter), index != -1 && count < sizeof(objects) / sizeof(objects[0]))
			objects[count++] = index;
	}
	else
	{
		s_multiplayer_globals_definition *mulg = (s_multiplayer_globals_definition *)tag_get('mulg', globals->MultiplayerGlobals.index);
		if (group_tag == 'weap')
		{
			for (__int32 i = 0; i < mulg->universal->weapons.count && count < sizeof(objects) / sizeof(objects[0]); i++)
			{
				if (mulg->universal->weapons[i].object.index != -1)
					objects[count++] = mulg->universal->weapons[i].object.index;
			}
		}
		else if (group_tag == 'vehi')
		{
			for (__int32 i = 0; i < mulg->universal->vehicles.count && count < sizeof(objects) / sizeof(objects[0]); i++)
			{
				if (mulg->universal->vehicles[i].object.index != -1)
					objects[count++] = mulg->universal->vehicles[i].object.index;
			}
		}
		else if (group_tag == 'eqip')
		{
			for (__int32 i = 0; i < mulg->universal->consumables.count && count < sizeof(objects) / sizeof(objects[0]); i++)
			{
				if (mulg->universal->consumables[i].object.index != -1)
					objects[count++] = mulg->universal->consumables[i].object.index;
			}
		}
		else
		{
			#line 296 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Modules\\ModuleCheat.cpp"
				assert(!"not supported");
				#line 316 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Modules\\ModuleCheat.cpp"
			return false;
		}
	}
	Objects::CObjectMessaging::EnqueueAction([objects, count]() { cheat_objects(objects, count); });
	return true;
}

bool CheatAllWeapons(std::vector<std::string> const &args, std::string &returnValue) // 0x10796430
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CheatAllWeapons@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	return cheat_all_objects(0x77656170, args.size() > 0 && args[0] == "1");
}

bool CheatAllVehicles(std::vector<std::string> const &args, std::string &returnValue) // 0x10796390
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CheatAllVehicles@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	return cheat_all_objects(0x76656869, args.size() > 0 && args[0] == "1");
}

bool CheatAllEquipment(std::vector<std::string> const &args, std::string &returnValue) // 0x107962F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CheatAllEquipment@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	return cheat_all_objects(0x65716970, args.size() > 0 && args[0] == "1");
}

bool CheatDeleteWeapons(std::vector<std::string> const &args, std::string &returnValue) // 0x107964D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CheatDeleteWeapons@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	Objects::CObjectMessaging::EnqueueAction([]()
	{
		void (*const object_delete)(long) = reinterpret_cast<void (*)(long)>(0xB2CF40);
		long unitIndex = ((long (*)(long))0x589CC0)(0);
		if (unitIndex == -1)
			return;
		auto unit = (s_unit_data *)object_try_and_get_and_verify_type(unitIndex, 0x2003);
		if (!unit)
			return;
		for (int i = 0; i < unit->weapon_object_indices.get_count(); i++)
		{
			if (unit->weapon_object_indices[i] != -1)
			{
				object_delete(unit->weapon_object_indices[i]);
				unit->weapon_object_indices[i] = -1;
			}
		}
	});
	return true;
}

bool CheatSpawn(std::vector<std::string> const &args, std::string &returnValue) // 0x107965A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CheatSpawn@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	if (args.empty())
	{
		returnValue = "Invalid arguments";
		return false;
	}
	struct s_group
	{
		char const *tag;
		char const *name;
	};
	static s_group groups[] =
	{
		{ "obje", "object" },
		{ "bipd", "biped" },
		{ "vehi", "vehicle" },
		{ "weap", "weapon" },
		{ "eqip", "equipment" },
		{ "argd", "alternate_reality_device" },
		{ "term", "terminal" },
		{ "proj", "projectile" },
		{ "proj", "projectile" },
		{ "scen", "scenery" },
		{ "mach", "machine" },
		{ "ctrl", "control" },
		{ "ssce", "sound_scenery" },
		{ "bloc", "crate" },
		{ "crea", "creature" },
		{ "gint", "giant" },
		{ "efsc", "effect_scenery" },
		{ "effe", "effect" },
	};
	std::string const &specifier = args[0];
	unsigned __int32 pos = specifier.find_last_of('.');
	if (pos == std::string::npos)
	{
		returnValue = "Invalid tag specified";
		return false;
	}
	std::string group_name = specifier.substr(pos + 1);
	std::string name = specifier.substr(0, pos);
	__int32 index = -1;
	for (__int32 i = 0; i < (__int32)std::size(groups); i++)
	{
		if (group_name == groups[i].tag || group_name == groups[i].name)
			index = i;
	}
	if (index == -1)
	{
		returnValue = "Invalid group";
		return false;
	}
	unsigned long group_tag;
	memcpy(&group_tag, groups[index].tag, 4);
	group_tag = _byteswap_ulong(group_tag);
	long tag_index = tag_find_by_name(group_tag, name.c_str());
	if (tag_index == -1)
	{
		returnValue = std::format("Could not find any tags named '{}' to drop", args[0]);
		return false;
	}
	Objects::CObjectMessaging::EnqueueAction([group_tag, tag_index]()
	{
		long player_index = ((unsigned long (*)(long))0x589C30)(0);
		if (player_index == -1)
			return;
		s_player_datum *player = player_get(player_index);
		if (player->unit_index == -1)
			return;
		s_unit_data *unit = (s_unit_data *)object_get(player->unit_index);
		real_point3d camera_position;
		((void (*)(long, real_point3d *))0xB439D0)(player->unit_index, &camera_position);
		if (group_tag == 'effe')
		{
			float const distance = 2.25f;
			real_point3d position;
			position.x = 2.25f * unit->aiming_vector.i + camera_position.x;
			position.y = 2.25f * unit->aiming_vector.j + camera_position.y;
			position.z = 2.25f * unit->aiming_vector.k + camera_position.z;
			((void (*)(long, real_point3d const *, real_vector3d const *, real_vector3d const *, long, long, long, long))0x5B87F0)(tag_index, &position, &unit->aiming_vector, &global_up3d, 1, 1, 0, 0);
		}
		else
		{
			s_object_placement_data placement;
			object_placement_data_new(&placement, tag_index, -1, nullptr);
			placement.forward = unit->aiming_vector;
			placement.up = global_up3d;
			placement.relative_position.x = 0.5f * unit->aiming_vector.i + camera_position.x;
			placement.relative_position.y = 0.5f * unit->aiming_vector.j + camera_position.y;
			placement.relative_position.z = 0.5f * unit->aiming_vector.k + camera_position.z;
			long object_index = ((long (*)(s_object_placement_data *))0xB30440)(&placement);
			if (object_index != -1)
			{
				((void (*)(long))0x4B2CD0)(object_index);
				((void (*)(long))0x58FFB0)(object_index);
			}
		}
	});
	return true;
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
