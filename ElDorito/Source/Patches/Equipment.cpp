/* ---------- headers */

#include "hades/hades.h"

#include "Blam/ai/actor.hpp"
#include "Blam/BlamNetwork.hpp"
#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/effects/screen_effect.hpp"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_globals.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/multiplayer_definitions.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/items/equipment.hpp"
#include "Blam/items/equipment_definitions.hpp"
#include "Blam/items/items.hpp"
#include "Blam/math/color_definitions.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/bitstream.hpp"
#include "Blam/memory/data_array.inl"
#include "Blam/memory/data_iterator.inl"
#include "Blam/memory/static_array.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/motor/action_system.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/objects/object_types.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/physics/havok_types.hpp"
#include "Blam/rasterizer/rasterizer_geometry.hpp"
#include "Blam/scenario/scenario.hpp"
#include "Blam/scenario/scenario_definitions.hpp"
#include "Blam/simulation/game_interface/simulation_game_units.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "Blam/units/unit_definitions.hpp"
#include "Blam/units/units.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "ElDorito.hpp"
#include "Forge/Geoemetry.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Pointer.hpp"
#include "ThirdParty/rapidjson/document.h"
#include "Utils/Macros.hpp"
#include "Utils/String.hpp"

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

class c_player_output_user_iterator;
struct real_rgb_color;
struct s_action_request;
struct s_damage_owner;
struct s_equipment_data;
struct s_equipment_definition;
struct s_equipment_health_pack_block;
struct s_equipment_vision_block;
struct s_game_globals;
struct s_item_data;
struct s_multiplayer_globals_definition;
struct s_object_data;
struct s_player_action_context;
struct s_player_datum;
struct s_player_interaction;
struct s_scenario;
struct s_scenario_profile;
struct s_screen_effect_datum;
struct s_simulation_unit_pickup_event_data;
struct s_starting_weapon_info;
struct s_unit_data;
struct s_unit_definition;
namespace Blam
{
	namespace Network
	{
		struct Session;
	}
}

namespace Utils {}
using namespace ::Utils;
namespace Utils
{
	namespace AntiCheat {}
	using namespace Utils::AntiCheat;
}

namespace Forge {}
using namespace ::Forge;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Sprint {}
	using namespace Patches::Sprint;
	namespace Equipment {}
	using namespace Patches::Equipment;
}

namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Network {}
	using namespace Blam::Network;
}

/* ---------- constants */

/* ---------- definitions */

//struct player_examine_nearby_item_hook::__l2::s_unit_weapon_pickup_result
//{
//	char indices1[2]; // 0x0
//	char indices2[2]; // 0x2
//};
//static_assert(sizeof(player_examine_nearby_item_hook::__l2::s_unit_weapon_pickup_result) == 4, "Invalid player_examine_nearby_item_hook::__l2::s_unit_weapon_pickup_result size");

//struct player_examine_nearby_item_hook::__l2::s_unit_weapon_pickup_action_request :
//	public s_action_request
//{
//	long item_index; // 0x4
//	long pickup_type; // 0x8
//};
//static_assert(sizeof(player_examine_nearby_item_hook::__l2::s_unit_weapon_pickup_action_request) == 12, "Invalid player_examine_nearby_item_hook::__l2::s_unit_weapon_pickup_action_request size");

/* ---------- prototypes */

namespace eldorado
{
	// Functions in eldorado.exe, named as in ManagedDonkey.
	static auto const action_submit0 = reinterpret_cast<bool (*)(long, s_action_request *)>(0xB69C50);
	static auto const equipment_activate = reinterpret_cast<bool (*)(long, long, bool)>(0xB86C20);
	static auto const equipment_definition_get_type = reinterpret_cast<e_equipment_type (*)(long, long)>(0xBA0260);
	static auto const game_is_authoritative = reinterpret_cast<bool (*)()>(0x5319C0);
	static auto const game_is_survival = reinterpret_cast<bool (*)()>(0x531E20);
	static auto const object_wake = reinterpret_cast<void (*)(long)>(0xB34D00);
	static auto const player_mapping_get_first_output_user = reinterpret_cast<long (*)(long)>(0x589A70);
	static auto const player_mapping_get_next_output_user = reinterpret_cast<long (*)(long, long)>(0x589B90);
	static auto const simulation_action_object_update_internal = reinterpret_cast<void (*)(long, unsigned long long *)>(0x4B3010);
	static auto const unit_can_pickup_equipment = reinterpret_cast<bool (*)(long, long)>(0xB3AAA0);
	static auto const unit_get_active_primary_weapon = reinterpret_cast<long (*)(long, long *)>(0xB42EF0);
	static auto const weapon_is_support_weapon = reinterpret_cast<bool (*)(long)>(0xB641D0);
}

extern float distance_squared3d(real_point3d const *p1, real_point3d const *p2);  // hades: added for 0x10A54CF0

namespace Patches { namespace Sprint { int GetState(); bool PlayerHasSprintTrait(long playerIndex); } }  // hades: added for 0x10A579B0

extern long (*const game_seconds_to_ticks_round)(float);  // hades: added for 0x10A57C80

extern bool (*game_is_campaign)();  // hades: added for 0x10A56920
s_scenario *global_scenario_get();  // hades: added for 0x10A56920
namespace Blam::Network { Session *GetActiveSession(); }  // hades: added for 0x10A56920

extern long (*const game_time_get)();  // hades: added for 0x10A57780
extern float (*const game_tick_length)();  // hades: added for 0x10A57780

extern s_object_data *(*const object_try_and_get_and_verify_type)(unsigned long, c_enum<e_object_type, long>);  // hades: added for 0x10A574F0

extern bool (*const game_is_multiplayer)();  // hades: added for 0x10A576D0
#include "Forge/ForgeUtil.hpp"  // hades: added for 0x10A576D0

template<typename t_arg0> static t_arg0 *object_get(unsigned long object_index) { return (t_arg0 *)object_get(object_index); }  // hades: a file-local template in the original (undecorated `object_get<T>`), defined so it is emitted;  // hades: added for 0x10A553F0

namespace Patches
{
	namespace Equipment
	{
		extern void ApplyAll();
		extern void PlayerConsiderEquipmentInteraction(long playerIndex, long equipmentIndex, s_player_action_context *outActionContext);
	}
}

void player_examine_nearby_item_hook(long player_index, long item_index);
void unit_add_initial_loadout_hook(long unit_index);
void unit_add_starting_profile_equipment_hook(long unit_index, short profile_index, bool reset, bool mark_as_garbage);
bool unit_update_weapons_hook(long unit_index);
void EquipmentUseHook(__int32 unitObjectIndex, __int32 slotIndex, unsigned __int32 isClient);
__int32 GetMPGlobalsEquipmentBlockIndex(unsigned __int32 tagIndex);
void *Player_GetArmorAbilitiesCHUDHook(s_player_datum *playerDatum);
void unit_drop_on_death_hook(long unit_index);
void unit_drop_equipment_hook(long unit_index, long slot_index);
void update_equipment_vision(long equipment_index, long unit_index);
void equipment_update_hook(long equipment_index, long unit_index);
void unit_toss_item_object_detach_hook(long item_index);
void TankModeCrashFixHook();
bool __fastcall c_simulation_unit_pickup_event_definition__apply_game_event_hook(void *thisptr, void *__formal, long reference_gamestate_count, long *game_state_indices, long payload_size, s_simulation_unit_pickup_event_data *payload);
void simulation_action_pickup_healthpack(long unit_index, long definition_index);
bool unit_can_pickup_healthpack(long unit_index, long equipment_index);
bool unit_can_pickup_equipment_hook(long unit_index, long equipment_index);
void unit_update_health_pack_hook(long unit_index);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Patches
{
	namespace Equipment
	{
		void ApplyAll() // 0x10A53110
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAll@Equipment@Patches@@YAXXZ");
			// procedure flags: nofpo

			Hook(0x1394A0, player_examine_nearby_item_hook).Apply();
			Hook(0x739110, unit_add_starting_profile_equipment_hook).Apply();
			Hook(0x13D20D, unit_add_initial_loadout_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x6858FE, Player_GetArmorAbilitiesCHUDHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x749F23, unit_update_weapons_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x13DC4B, EquipmentUseHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0xBA06A, EquipmentUseHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x1069A2D, EquipmentUseHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x1083588, EquipmentUseHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x10C9559, EquipmentUseHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Patch::NopFill(Pointer::Base(0x786CFF), 6);
			Patch::NopFill(Pointer::Base(0x74CFF4), 6);
			Patch::NopFill(Pointer::Base(0x137F4D), 2);
			Patch::NopFill(Pointer::Base(0x13DC0A), 2);
			Patch(0x137F20, { 0xB0, 0x01, 0xC3 }).Apply();
			Patch(0x78A179, { 0xEB }).Apply();
			Patch(0x78950D, { 0xEB }).Apply();
			Hook(0x7406D5, unit_drop_on_death_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Patch(0x7406CF, { 0x90, 0x90 }).Apply();
			Hook(0x7409E0, unit_drop_equipment_hook).Apply();
			Patch(0x74A0FB, { 0xEB }).Apply();
			Patch::NopFill(0xB88703, 5);
			Patch::NopFill(0xB89462, 5);
			Hook(0x749600, unit_toss_item_object_detach_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x73D099, TankModeCrashFixHook).Apply();
			Pointer(0x1641368).Write(c_simulation_unit_pickup_event_definition__apply_game_event_hook);
			Hook(0x73AAA0, unit_can_pickup_equipment_hook).Apply();
			Hook(0x74BA80, unit_update_health_pack_hook).Apply();
			Hook(0x749F69, equipment_update_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Patch::NopFill(0x58C989, 6);
		}

		void PlayerConsiderEquipmentInteraction(long playerIndex, long equipmentIndex, s_player_action_context *outActionContext) // 0x10A54CF0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?PlayerConsiderEquipmentInteraction@Equipment@Patches@@YAXJJPAUs_player_action_context@@@Z");
			// static ...; // 0x10A54F00
			// long playerIndex;
			// long equipmentIndex;
			// s_player_action_context *outActionContext;
			// s_player_datum const *player;
			// s_unit_data const *unit;
			// long active_primary_weapon_index;
			// s_equipment_data const *equipment;
			// bool (*const player_evaluate_interaction)(long, s_player_interaction *, s_player_interaction *);
			// s_player_interaction interaction;
			// float const radius;
			// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
			// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
			// function call : long (*const)(long, long *)
			// function call : bool (*const)(long)
			// function call : bool (*const)(long, long)
			// function call : bool (*const)(long, s_player_interaction *, s_player_interaction *)

			bool (*const player_evaluate_interaction)(long, s_player_interaction *, s_player_interaction *) = reinterpret_cast<bool (*)(long, s_player_interaction *, s_player_interaction *)>(0x539240);
			s_player_datum const *player = player_get(playerIndex);
			s_unit_data const *unit = (s_unit_data const *)object_try_and_get_and_verify_type(player->unit_index, 0x2003);
			s_equipment_data const *equipment = (s_equipment_data const *)object_try_and_get_and_verify_type(equipmentIndex, 0x8);
			if (equipment->inventory_state)
				return;
			if (equipment->owner_unit_index == player->unit_index)
				return;
			if (unit->equipment_object_indices[0] == -1)
				return;
			long active_primary_weapon_index = eldorado::unit_get_active_primary_weapon(player->unit_index, nullptr);
			if (active_primary_weapon_index != -1 && eldorado::weapon_is_support_weapon(active_primary_weapon_index))
				return;
			float const radius = unit->bounding_sphere_radius + 0.4f;
			if (distance_squared3d(&unit->bounding_sphere_center, &equipment->bounding_sphere_center) >= radius * radius)
				return;
			if (!eldorado::unit_can_pickup_equipment(player->unit_index, equipmentIndex))
				return;
			s_player_interaction interaction = {};
			interaction.type = 2;
			interaction.object_index = equipmentIndex;
			player_evaluate_interaction(playerIndex, &interaction, &outActionContext->interaction);
		}
	}
}

/* ---------- private code */

void player_examine_nearby_item_hook(long player_index, long item_index) // 0x10A55750
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?player_examine_nearby_item_hook@@YAXJJ@Z");
	// `anonymous-namespace'::player_examine_nearby_item_hook
	// static ...; // 0x10A56402
	// static ...; // 0x10A563F3
	// static ...; // 0x10A563EA
	// static ...; // 0x10A563E1
	// static ...; // 0x10A563D3
	// static ...; // 0x10A563C4
	// static ...; // 0x10A56370
	// static ...; // 0x10A56368
	// long player_index;
	// long item_index;
	// bool (*const player_should_auto_pickup_weapon)(long, long);
	// s_player_datum *player;
	// s_unit_data *unit;
	// void (*const simulation_request_pickup_grenade)(long, long);
	// float pickup_radius_squared;
	// bool (*const unit_can_access_object)(long, long);
	// __int32 (*const equipment_play_pickup_sound)(long, long);
	// void (*const simulation_request_pickup_powerup)(long, long);
	// void (*const simulation_request_pickup_weapon)(long, long, long);
	// void (*const player_use_multiplayer_powerup)(long, long);
	// s_item_data *item;
	// bool (*const unit_can_pickup_equipment)(long, long);
	// bool (*const weapon_handle_potential_inventory_item)(long, long, long, long, short *);
	// long (*const game_get_grenade_type_index_from_item_defintion)(long);
	// bool (*const unit_add_grenade_to_inventory)(long, long);
	// bool v8;
	// bool (*const object_is_multiplayer_cinematic_object)(long);
	// long const k_parent_mask;
	// float distance_squared;
	// __int32 (*const chud_picked_up_powerup)(long, long);
	// bool (*const unit_can_pickup_weapon)(long, long, long, player_examine_nearby_item_hook::__l2::s_unit_weapon_pickup_result *);
	// void (*const game_engine_player_nearby_item)(long, long);
	// void (*const chud_picked_up_grenade)(long, long);
	// void (*const simulation_action_pickup_powerup)(long, long);
	// void (*const chud_picked_up_ammunition)(long, long, short);
	// void (*const object_destroy)(long);
		// void *equipment_def;
		// long loop_weapon_index;
		// player_examine_nearby_item_hook::__l2::s_unit_weapon_pickup_result pickup_result;
			// __int32 i;
				// long weapon_index;
				// long inventory_index;
					// short rounds_picked_up;
						// c_player_output_user_iterator iterator;
							// s_object_data *weapon;
						// s_object_data *weapon;
			// s_item_data *equipment;
				// long current_equipment_index;
				// long equipment_type;
					// long output_index_index;
					// player_examine_nearby_item_hook::__l2::s_unit_weapon_pickup_action_request action_request;
					// c_player_output_user_iterator iterator;
				// c_player_output_user_iterator iterator;
			// player_examine_nearby_item_hook::__l2::s_unit_weapon_pickup_action_request action_request;
	// function call : bool (*const)(long)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : bool (*const)()
	// function call : bool (*const)(long, long)
	// function call : void *(*const)(unsigned long, long)
	// function call : bool (*const)(long, long, long, long, short *)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void (*const)(long, long, short)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void (*const)(long)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : long (*const)(long)
	// function call : bool (*const)(long, long)
	// function call : e_equipment_type (*const)(long, long)
	// function call : bool (*const)()
	// function call : void (*const)(long, long)
	// function call : void (*const)(long, long)
	// function call : bool (*const)()
	// function call : bool (*const)(long, long, bool)
	// function call : void (*const)(long, long)
	// function call : long (*const)(long)
	// function call : void (*const)(long, long)
	// function call : long (*const)(long, long)
	// function call : void (*const)(long)
	// function call : void (*const)(long, long)
	// function call : bool (*const)()
	// function call : bool (*const)(long, s_action_request *)
	// function call : __int32 (*const)(long, long)
	// function call : __int32 (*const)(long, long)
	// function call : void (*const)(long, long)
	// function call : void (*const)(long, long)
	// function call : bool (*const)()
	// function call : bool (*const)()
	// function call : bool (*const)(long, long)
	// function call : void (*const)(long, long)
	// function call : void (*const)(long, long)
	// function call : bool (*const)(long, long, long, player_examine_nearby_item_hook::__l2::s_unit_weapon_pickup_result *)
	// function call : bool (*const)(long, long)
	// function call : bool (*const)()
	// function call : bool (*const)(long, s_action_request *)
	// function call : void (*const)(long, long, long)
	// function call : void (*const)(long, long)

	struct s_unit_weapon_pickup_result
	{
		char data[4];
	};
	struct s_unit_weapon_pickup_action_request
	{
		long type;
		long object_index;
		long pickup_type;
	};
	void (*const player_use_multiplayer_powerup)(long, long) = reinterpret_cast<void (*)(long, long)>(0xB887B0);
	bool (*const object_is_multiplayer_cinematic_object)(long) = reinterpret_cast<bool (*)(long)>(0xB2F300);
	bool (*const weapon_handle_potential_inventory_item)(long, long, long, long, short *) = reinterpret_cast<bool (*)(long, long, long, long, short *)>(0xB63840);
	long (*const game_get_grenade_type_index_from_item_defintion)(long) = reinterpret_cast<long (*)(long)>(0x52D1A0);
	void (*const game_engine_player_nearby_item)(long, long) = reinterpret_cast<void (*)(long, long)>(0x5A2440);
	bool (*const unit_can_access_object)(long, long) = reinterpret_cast<bool (*)(long, long)>(0xB3A170);
	bool (*const unit_can_pickup_equipment)(long, long) = reinterpret_cast<bool (*)(long, long)>(0xB3AAA0);
	bool (*const unit_add_grenade_to_inventory)(long, long) = reinterpret_cast<bool (*)(long, long)>(0xB38BA0);
	bool (*const unit_can_pickup_weapon)(long, long, long, s_unit_weapon_pickup_result *) = reinterpret_cast<bool (*)(long, long, long, s_unit_weapon_pickup_result *)>(0xB3AC10);
	void (*const chud_picked_up_ammunition)(long, long, short) = reinterpret_cast<void (*)(long, long, short)>(0xA89980);
	void (*const chud_picked_up_grenade)(long, long) = reinterpret_cast<void (*)(long, long)>(0xA899D0);
	__int32 (*const chud_picked_up_powerup)(long, long) = reinterpret_cast<__int32 (*)(long, long)>(0xA95850);
	void (*const simulation_request_pickup_grenade)(long, long) = reinterpret_cast<void (*)(long, long)>(0x4B4A10);
	void (*const simulation_request_pickup_powerup)(long, long) = reinterpret_cast<void (*)(long, long)>(0x4B4A20);
	void (*const simulation_request_pickup_weapon)(long, long, long) = reinterpret_cast<void (*)(long, long, long)>(0x4B4D00);
	void (*const simulation_action_pickup_powerup)(long, long) = reinterpret_cast<void (*)(long, long)>(0x4B31C0);
	__int32 (*const equipment_play_pickup_sound)(long, long) = reinterpret_cast<__int32 (*)(long, long)>(0x5408E0);
	bool (*const player_should_auto_pickup_weapon)(long, long) = reinterpret_cast<bool (*)(long, long)>(0x53CDC0);
	void (*const object_destroy)(long) = reinterpret_cast<void (*)(long)>(0xB57090);
	long const k_parent_mask = 0x2982;
	s_player_datum *player = player_get(player_index);
	if (player->unit_index == -1 || object_is_multiplayer_cinematic_object(item_index))
		return;
	s_unit_data *unit = (s_unit_data *)object_try_and_get_and_verify_type(player->unit_index, 0x2003);
	s_item_data *item = (s_item_data *)object_try_and_get_and_verify_type(item_index, 0xC);
	bool v8 = false;
	if (item->parent_object_index != -1 && ((item->physics_flags >> 4) & 1 || (1 << object_get_type(item->parent_object_index)) & k_parent_mask))
		v8 = true;
	if (item->parent_object_index != -1 && !v8 || item->ignore_object_index == player->unit_index)
		return;
	if (game_is_multiplayer() && !unit_can_access_object(player->unit_index, item_index))
		return;
	if (unit->parent_object_index != -1)
	{
		void *equipment_def = tag_get('eqip', item->definition_index);
		if (!(*(unsigned short *)offset_pointer(equipment_def, 0x120) & 0x10))
			return;
	}
	float distance_squared = distance_squared3d(&unit->bounding_sphere_center, &item->bounding_sphere_center);
	float pickup_radius_squared = (unit->bounding_sphere_radius + 0.4f) * (unit->bounding_sphere_radius + 0.4f);
	if (pickup_radius_squared > distance_squared)
	{
		long loop_weapon_index = -1;
		for (__int32 i = 0; i < 4; i++)
		{
			long inventory_index = 0;
			if (unit->current_weapon_set.indices[0] >= 0)
				inventory_index = unit->current_weapon_set.indices[0];
			long weapon_index = unit->weapon_object_indices[(inventory_index + i) % 4];
			if (weapon_index != -1)
			{
				short rounds_picked_up;
				if (weapon_handle_potential_inventory_item(weapon_index, item_index, player->unit_index, player_index, &rounds_picked_up) && rounds_picked_up > 0)
				{
					loop_weapon_index = weapon_index;
					c_player_output_user_iterator iterator;
					iterator.begin(player_index);
					while (iterator.next())
					{
						s_object_data *weapon = object_try_and_get_and_verify_type(weapon_index, 4);
						chud_picked_up_ammunition(iterator.get_output_user_index(), weapon->definition_index, rounds_picked_up);
					}
				}
				if (weapon_index == -1 && loop_weapon_index != weapon_index)
				{
					s_object_data *weapon = object_try_and_get_and_verify_type(weapon_index, 4);
					if (weapon != object_try_and_get_and_verify_type(loop_weapon_index, 4))
						eldorado::object_wake(weapon_index);
				}
			}
		}
		s_item_data *equipment = (s_item_data *)object_try_and_get_and_verify_type(item_index, 8);
		if (equipment)
		{
			if (game_get_grenade_type_index_from_item_defintion(equipment->definition_index) == -1)
			{
				if (unit_can_pickup_equipment(player->unit_index, item_index))
				{
					long equipment_type = eldorado::equipment_definition_get_type(equipment->definition_index, 0);
					long current_equipment_index = unit->equipment_object_indices[0];
					if (equipment_type == 1)
					{
						if (eldorado::game_is_authoritative())
							equipment_play_pickup_sound(player_index, item_index);
						else
							simulation_request_pickup_powerup(player_index, item_index);
					}
					else if (equipment_type == 0 || equipment_type == 9)
					{
						if (1.0f > unit->body_vitality || 1.0f > unit->shield_vitality)
						{
							if (eldorado::game_is_authoritative())
							{
								eldorado::equipment_activate(item_index, player->unit_index, false);
								player_use_multiplayer_powerup(unit->player_index, equipment->definition_index);
								long output_index_index = eldorado::player_mapping_get_first_output_user(unit->player_index);
								while (output_index_index != -1)
								{
									((void (*const)(long, long))0xA95890)(output_index_index, equipment->definition_index);
									output_index_index = eldorado::player_mapping_get_next_output_user(unit->player_index, output_index_index);
								}
								object_destroy(item_index);
								simulation_action_pickup_healthpack(player->unit_index, equipment->definition_index);
							}
							else
							{
								simulation_request_pickup_powerup(player_index, item_index);
							}
						}
					}
					else if (current_equipment_index == -1)
					{
						if (eldorado::game_is_authoritative())
						{
							s_unit_weapon_pickup_action_request action_request = {};
							action_request.type = 61;
							action_request.object_index = item_index;
							action_request.pickup_type = 2;
							eldorado::action_submit0(player->unit_index, (s_action_request *)&action_request);
							player_use_multiplayer_powerup(player_index, equipment->definition_index);
							c_player_output_user_iterator iterator;
							iterator.begin(player_index);
							while (iterator.next())
								chud_picked_up_powerup(iterator.get_output_user_index(), equipment->definition_index);
							simulation_action_pickup_powerup(player->unit_index, equipment->definition_index);
						}
						else
						{
							simulation_request_pickup_powerup(player_index, item_index);
						}
					}
				}
			}
			else if (!game_is_multiplayer() || player->traits.weapons.weapon_pickup != 2)
			{
				if (eldorado::game_is_authoritative())
				{
					if (unit_add_grenade_to_inventory(player->unit_index, item_index))
					{
						c_player_output_user_iterator iterator;
						iterator.begin(player_index);
						while (iterator.next())
							chud_picked_up_grenade(iterator.get_output_user_index(), equipment->definition_index);
					}
				}
				else
				{
					simulation_request_pickup_grenade(player_index, item_index);
				}
			}
		}
		if (object_get_type(item_index) == 2)
		{
			s_unit_weapon_pickup_result pickup_result;
			if (unit_can_pickup_weapon(player->unit_index, item_index, -1, &pickup_result) && pickup_result.data[0] && player_should_auto_pickup_weapon(player_index, item_index))
			{
				if (eldorado::game_is_authoritative())
				{
					s_unit_weapon_pickup_action_request action_request = {};
					action_request.type = 46;
					action_request.object_index = item_index;
					action_request.pickup_type = 3;
					eldorado::action_submit0(player->unit_index, (s_action_request *)&action_request);
				}
				else
				{
					simulation_request_pickup_weapon(player->unit_index, item_index, 3);
				}
			}
		}
		game_engine_player_nearby_item(player_index, item_index);
	}
}

void unit_add_initial_loadout_hook(long unit_index) // 0x10A56920
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?unit_add_initial_loadout_hook@@YAXJ@Z");
	// `anonymous-namespace'::unit_add_initial_loadout_hook
	// long unit_index;
	// void (*const unit_add_initial_loadout)(long);
		// s_unit_data *unit;
		// s_player_datum *player;
		// s_scenario *scnr;
		// Blam::Network::Session *session;
			// bool useRespawn;
			// __int32 character_profile;
	// function call : bool (*)()
	// function call : bool (*const)()
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : bool (*const)()
	// function call : bool (*const)()
	// function call : void (*const)(long)

	void (*const unit_add_initial_loadout)(long) = reinterpret_cast<void (*)(long)>(0x5A30F0);
	if (game_is_campaign() || eldorado::game_is_survival())
	{
		s_unit_data *unit = (s_unit_data *)object_try_and_get_and_verify_type(unit_index, 0x2003);
		s_player_datum *player = player_get(unit->player_index);
		s_scenario *scnr = global_scenario_get();
		Blam::Network::Session *session = Blam::Network::GetActiveSession();
		if (session && player && scnr)
		{
			bool useRespawn = player->respawn_duration_seconds > 0 || player->first_spawn;
			__int32 character_profile = session->MembershipInfo.GetPeerPlayer(player->machine_index);
			character_profile += useRespawn ? (eldorado::game_is_survival() ? 12 : 8) : (eldorado::game_is_survival() ? 4 : 0);
			if (character_profile < scnr->player_starting_profile.count)
			{
				unit_add_starting_profile_equipment_hook(player->unit_index, (short)character_profile, true, false);
				return;
			}
		}
	}
	unit_add_initial_loadout(unit_index);
}

void unit_add_starting_profile_equipment_hook(long unit_index, short profile_index, bool reset, bool mark_as_garbage) // 0x10A56BB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?unit_add_starting_profile_equipment_hook@@YAXJF_N0@Z");
	// `anonymous-namespace'::unit_add_starting_profile_equipment_hook
	// bool mark_as_garbage;
	// s_unit_data *unit;
	// bool (*const unit_add_weapon_to_inventory)(long, long, long);
	// long (*const unit_create_starting_weapon)(long, s_starting_weapon_info *, bool);
	// void (*const unit_delete_all_weapons)(long);
	// s_scenario_profile &profile;
		// long i;
			// long weapon_index;
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void (*const)(long)
	// function call : long (*const)(long, s_starting_weapon_info *, bool)
	// function call : bool (*const)(long, long, long)
	// function call : void (*const)(long)

	long (*const unit_create_starting_weapon)(long, s_starting_weapon_info *, bool) = reinterpret_cast<long (*)(long, s_starting_weapon_info *, bool)>(0xB3E9F0);
	void (*const unit_delete_all_weapons)(long) = reinterpret_cast<void (*)(long)>(0xB3FAD0);
	bool (*const unit_add_weapon_to_inventory)(long, long, long) = reinterpret_cast<bool (*)(long, long, long)>(0xB393D0);
	if (unit_index == -1 || profile_index == -1)
		return;
	s_scenario_profile &profile = global_scenario_get()->player_starting_profile[profile_index];
	s_unit_data *unit = (s_unit_data *)object_try_and_get_and_verify_type(unit_index, 0x2003);
	if (reset)
	{
		unit_delete_all_weapons(unit_index);
		unit->body_vitality = 1.0f;
		unit->shield_vitality = 1.0f;
		for (long i = 0; i < 4; i++)
			unit->grenade_counts[i] = 0;
	}
	for (long i = 0; i < 2; i++)
	{
		long weapon_index = unit_create_starting_weapon(unit_index, &profile.starting_weapons[i], mark_as_garbage);
		if (weapon_index != -1 && !unit_add_weapon_to_inventory(unit_index, weapon_index, 1))
			((void (*)(long))0xB2CD10)(weapon_index);
	}
	unit->body_vitality -= profile.starting_health_damage;
	unit->shield_vitality -= profile.starting_shield_damage;
	for (long i = 0; i < 4; i++)
	{
		unit->grenade_counts[i] += profile.starting_grenades[i];
		if (unit->current_grenade_index == -1 && unit->grenade_counts[i] > 0)
		{
			unit->current_grenade_index = (char)i;
			unit->desired_grenade_index = (char)i;
		}
	}
}

bool unit_update_weapons_hook(long unit_index) // 0x10A579B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?unit_update_weapons_hook@@YA_NJ@Z");
	// `anonymous-namespace'::unit_update_weapons_hook
	// long unit_index;
	// bool ret;
	// bool (*const unit_update_weapons)(unsigned __int32);
		// s_unit_data *unit;
			// __int32 i;
				// s_player_datum *player;
				// bool equipment_Empty;
				// e_equipment_type equipment_type;
				// s_unit_data *eqipObject;
				// long equipment_index;
	// function call : bool (*const)(unsigned __int32)
	// function call : bool (*const)()
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : e_equipment_type (*const)(long, long)
	// function call : long (*const)(long)
	// function call : float (*const)(long)
	// function call : void (*const)(long, long)

	bool (*const unit_update_weapons)(unsigned __int32) = reinterpret_cast<bool (*)(unsigned __int32)>(0xB4C6D0);
	bool ret = unit_update_weapons(unit_index);
	if (((bool (*)())0x5319C0)())
	{
		s_unit_data *unit = (s_unit_data *)object_try_and_get_and_verify_type(unit_index, 0x2003);
		for (__int32 i = 0; i < 4; i++)
		{
			long equipment_index = unit->equipment_object_indices[0];
			if (equipment_index == -1)
				continue;
			s_unit_data *eqipObject = (s_unit_data *)object_try_and_get_and_verify_type(equipment_index, -1);
			if (!eqipObject)
				continue;
			e_equipment_type equipment_type = ((e_equipment_type (*)(long, long))0xBA0260)(eqipObject->definition_index, 0);
			bool equipment_Empty = ((long (*)(long))0xB89190)(equipment_index) <= 0 && ((float (*)(long))0xB87DA0)(equipment_index) == 0.0f;
			s_player_datum *player = player_get(unit->player_index);
			if (player && equipment_type == (e_equipment_type)18 && Patches::Sprint::GetState() == 2 && !Patches::Sprint::PlayerHasSprintTrait(unit->player_index) && equipment_Empty && player->sprint_depleted_timer < 270)
				continue;
			if (equipment_Empty)
				((void (*)(long, long))0xB3FC50)(unit_index, 0);
		}
	}
	return ret;
}

void EquipmentUseHook(__int32 unitObjectIndex, __int32 slotIndex, unsigned __int32 isClient) // 0x10A54A70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?EquipmentUseHook@@YAXHHI@Z");
	// `anonymous-namespace'::EquipmentUseHook
	// unsigned __int32 isClient;
	// s_unit_data *unit;
	// void (*const EquipmentUse)(__int32, __int32, unsigned __int32);
	// long equipment_index;
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : long (*const)(long)
	// function call : float (*const)(long)
	// function call : void (*const)(__int32, __int32, unsigned __int32)

	void (*const EquipmentUse)(__int32, __int32, unsigned __int32) = reinterpret_cast<void (*)(__int32, __int32, unsigned __int32)>(0xB4CE90);
	s_unit_data *unit = (s_unit_data *)object_try_and_get_and_verify_type(unitObjectIndex, 0x2003);
	if (!unit)
		return;

	long equipment_index = unit->equipment_object_indices[slotIndex];
	if (!object_try_and_get_and_verify_type(equipment_index, 8))
		return;
	if (((long (__cdecl *)(long))0xB89190)(equipment_index) <= 0)
		return;
	if (((float (__cdecl *)(long))0xB87DA0)(equipment_index) != 0.0)
		return;

	EquipmentUse(unitObjectIndex, slotIndex, isClient);
}

__int32 GetMPGlobalsEquipmentBlockIndex(unsigned __int32 tagIndex) // 0x10A54C00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetMPGlobalsEquipmentBlockIndex@@YAHI@Z");
	// `anonymous-namespace'::GetMPGlobalsEquipmentBlockIndex
	// unsigned __int32 tagIndex;
	// s_game_globals *game_globals;
	// s_multiplayer_globals_definition *multiplayer_globals;
		// __int32 i;
	// function call : void *(*const)(unsigned long, long)

	s_game_globals *game_globals = game_globals_get();
	s_multiplayer_globals_definition *multiplayer_globals = (s_multiplayer_globals_definition *)tag_get('mulg', game_globals->MultiplayerGlobals.index);
	for (__int32 i = 1; i < multiplayer_globals->universal->consumables.count; i++)
	{
		if (multiplayer_globals->universal->consumables[i].object.index == tagIndex)
		{
			return i;
		}
	}

	return 1;
}

void *Player_GetArmorAbilitiesCHUDHook(s_player_datum *playerDatum) // 0x10A54FB0
{
	// `anonymous-namespace'::Player_GetArmorAbilitiesCHUDHook
	// s_player_datum *playerDatum;
	// s_unit_data *unitObject;
	// static unsigned char `Player_GetArmorAbilitiesCHUDHook'::`2'::data[8]; // 0x124584A0
	// s_object_data *itemObject;
	// long primaryEquipmentObjectIndex;

	static unsigned char data[8];
	memset(data, 0, sizeof(data));

	s_unit_data *unit = object_get<s_unit_data>(playerDatum->unit_index);
	if (!unit)
		return data;

	long equipment_index = unit->equipment_object_indices[0];
	if (equipment_index == -1)
		return data;

	s_object_data *object = object_get(equipment_index);
	if (!object)
		return data;

	data[3] = GetMPGlobalsEquipmentBlockIndex(object->definition_index);
	return data;
}

void unit_drop_on_death_hook(long unit_index) // 0x10A57680
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?unit_drop_on_death_hook@@YAXJ@Z");
	// `anonymous-namespace'::unit_drop_on_death_hook
	// long unit_index;

	unit_drop_grenades(unit_index);
}

void unit_drop_equipment_hook(long unit_index, long slot_index) // 0x10A574F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?unit_drop_equipment_hook@@YAXJJ@Z");
	// `anonymous-namespace'::unit_drop_equipment_hook
	// long slot_index;
	// s_unit_data *unit;
	// void *equipment_def;
	// s_unit_data *equipment;
	// void (*const equipment_update_function)(long, long);
	// long equipment_index;
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void *(*const)(unsigned long, long)
	// function call : void (*const)(long, long)

	void (*const equipment_update_function)(long, long) = reinterpret_cast<void (*)(long, long)>(0xB88470);
	s_unit_data *unit = (s_unit_data *)object_try_and_get_and_verify_type(unit_index, 0x2003);
	long equipment_index = unit->equipment_object_indices[slot_index];
	s_unit_data *equipment = (s_unit_data *)object_try_and_get_and_verify_type(equipment_index, 8);
	if (!equipment)
		return;

	void *equipment_def = tag_get(0x65716970, equipment->definition_index);
	if (*(unsigned short *)offset_pointer(equipment_def, 0x1DE) & 0x200)
		equipment_update_function(equipment_index, unit_index);
	else
		unit_drop_equipment(unit_index, slot_index);
}

void update_equipment_vision(long equipment_index, long unit_index) // 0x10A57C80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?update_equipment_vision@@YAXJJ@Z");
	// `anonymous-namespace'::update_equipment_vision
	// static ...; // 0x10A57DDC
	// static ...; // 0x10A57DD4
	// long equipment_index;
	// long unit_index;
	// s_equipment_vision_block *(*const equipment_get_vision_definition)(long);
	// s_equipment_data *equipment;
	// long time_since_used;
		// c_data_array<s_screen_effect_datum> *screen_effects;
		// s_equipment_vision_block *vision;
			// c_data_iterator<s_screen_effect_datum> it;
	// function call : long (*const)()
	// function call : float (*const)(long)
	// function call : long (*const)(float)
	// function call : s_equipment_vision_block *(*const)(long)

	s_equipment_vision_block *(*const equipment_get_vision_definition)(long) = reinterpret_cast<s_equipment_vision_block *(*)(long)>(0xBA0650);
	s_equipment_data *equipment = object_get<s_equipment_data>(equipment_index);
	long time_since_used = game_time_get() - equipment->last_use_time;
	if (time_since_used + 1 == game_seconds_to_ticks_round(((float (*)(long))0xB889F0)(equipment_index)))
	{
		s_equipment_vision_block *vision = equipment_get_vision_definition(equipment->definition_index);
		if (vision->screen_effect.index == -1)
			return;
		c_data_array<s_screen_effect_datum> *screen_effects = tls_getd().screen_effects;
		for (c_data_iterator<s_screen_effect_datum> it = screen_effects->begin(); it != screen_effects->end(); ++it)
		{
			if (it->attach_object_index == unit_index && it->definition_index == vision->screen_effect.index)
				screen_effects->delete_datum(it.current_datum_index);
		}
	}
}

void equipment_update_hook(long equipment_index, long unit_index) // 0x10A553F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?equipment_update_hook@@YAXJJ@Z");
	// `anonymous-namespace'::equipment_update_hook
	// long unit_index;
	// s_equipment_data *equipment;
	// void (*const equipment_update)(long, long);
	// function call : void (*const)(long, long)
	// function call : bool (*const)(long, e_equipment_type)

	const auto equipment_update = (void(*)(long, long))0xB891F0;
	s_equipment_data *equipment;
	equipment_update(equipment_index, unit_index);
	equipment = object_get<s_equipment_data>(equipment_index);
	if (((bool(*)(long, e_equipment_type))0xBA0360)(equipment->definition_index, (e_equipment_type)23))
	{
		update_equipment_vision(equipment_index, unit_index);
	}
}

void unit_toss_item_object_detach_hook(long item_index) // 0x10A576D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?unit_toss_item_object_detach_hook@@YAXJ@Z");
	// `anonymous-namespace'::unit_toss_item_object_detach_hook
	// long item_index;
	// void (*const object_detach)(long);
	// function call : bool (*const)()
	// function call : void (*const)(long)

	void (*const object_detach)(long) = reinterpret_cast<void (*)(long)>(0xB2D180);
	if (game_is_multiplayer() && Forge::GetObjectPhysicsMode(item_index) == static_cast<Forge::EForgeObjectPhysics>(1))
	{
		Forge::SetObjectPhysicsMode(item_index, static_cast<Forge::EForgeObjectPhysics>(0), false);
	}

	object_detach(item_index);
}

__declspec(naked) void TankModeCrashFixHook() // 0x10A550B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?TankModeCrashFixHook@@YAXXZ");
	// `anonymous-namespace'::TankModeCrashFixHook
	// procedure flags: nofpo
	// invalid_player:

	__asm
	{
		cmp ecx, 10h
		jge Loutside
		imul ecx, 2F08h
		push 0B3D09Fh
		ret
		Loutside:
		push 0B3D0BFh
		ret
	}
}

bool __fastcall c_simulation_unit_pickup_event_definition__apply_game_event_hook(void *thisptr, void *__formal, long reference_gamestate_count, long *game_state_indices, long payload_size, s_simulation_unit_pickup_event_data *payload) // 0x10A55110
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_simulation_unit_pickup_event_definition__apply_game_event_hook@@YI_NPAX0JPAJJPAUs_simulation_unit_pickup_event_data@@@Z");
	// `anonymous-namespace'::c_simulation_unit_pickup_event_definition__apply_game_event_hook
	// long reference_gamestate_count;
	// long *game_state_indices;
	// long payload_size;
	// s_simulation_unit_pickup_event_data *payload;
	// s_unit_data *unit;
	// bool (*const c_simulation_unit_pickup_event_definition__apply_game_event)(void *, long, long *, long, s_simulation_unit_pickup_event_data *);
	// long (*const simulation_gamestate_entity_get_and_verify_type)(long, long);
	// long unit_index;
	// long (*const tag_try_and_get_unsafe)(long, unsigned short);
	// long (*const unspatialized_impulse_sound_new)(long, float);
	// long (*const effect_new_from_object)(long, s_damage_owner *, long *, long, float, float, real_rgb_color *, void *, long);
		// long damage_reporting_type;
		// long output_index_index;
		// s_equipment_definition *definition;
	// function call : long (*const)(long, long)
	// function call : void *(*const)(unsigned long, long)
	// function call : void (*const)(long, long)
	// function call : long (*const)(long, s_damage_owner *, long *, long, float, float, real_rgb_color *, void *, long)
	// function call : long (*const)(long)
	// function call : void (*const)(long, long)
	// function call : long (*const)(long, long)
	// function call : bool (*const)(void *, long, long *, long, s_simulation_unit_pickup_event_data *)

	long (*const tag_try_and_get_unsafe)(long, unsigned short) = reinterpret_cast<long (*)(long, unsigned short)>(0x503510);
	long (*const simulation_gamestate_entity_get_and_verify_type)(long, long) = reinterpret_cast<long (*)(long, long)>(0x471F50);
	long (*const unspatialized_impulse_sound_new)(long, float) = reinterpret_cast<long (*)(long, float)>(0x5DE300);
	long (*const effect_new_from_object)(long, s_damage_owner *, long *, long, float, float, real_rgb_color *, void *, long) = reinterpret_cast<long (*)(long, s_damage_owner *, long *, long, float, float, real_rgb_color *, void *, long)>(0x5B8550);
	long unit_index = simulation_gamestate_entity_get_and_verify_type(game_state_indices[0], 0x2003);
	if (unit_index == -1)
		return false;
	s_unit_data *unit = (s_unit_data *)object_get(unit_index);
	if (unit->player_index == -1)
		return false;
	if (payload->type == 5)
	{
		s_equipment_definition *definition = (s_equipment_definition *)tag_get('eqip', payload->definition_index);
		((void (*)(long, long))0xB887B0)(unit->player_index, payload->definition_index);
		long damage_reporting_type = 0;
		if (definition->activation_effect.index)
			effect_new_from_object(definition->activation_effect.index, nullptr, &damage_reporting_type, unit_index, 1.0f, 1.0f, nullptr, nullptr, 1);
		long output_index_index = ((long (*)(long))0x589A70)(unit->player_index);
		while (output_index_index != -1)
		{
			((void (*)(long, long))0xA95890)(output_index_index, payload->definition_index);
			output_index_index = ((long (*)(long, long))0x589B90)(unit->player_index, output_index_index);
		}
		return true;
	}
	bool (__thiscall *const c_simulation_unit_pickup_event_definition__apply_game_event)(void *, long, long *, long, s_simulation_unit_pickup_event_data *) = reinterpret_cast<bool (__thiscall *)(void *, long, long *, long, s_simulation_unit_pickup_event_data *)>(0x4BCEC0);
	return c_simulation_unit_pickup_event_definition__apply_game_event(thisptr, reference_gamestate_count, game_state_indices, payload_size, payload);
}

void simulation_action_pickup_healthpack(long unit_index, long definition_index) // 0x10A56750
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?simulation_action_pickup_healthpack@@YAXJJ@Z");
	// `anonymous-namespace'::simulation_action_pickup_healthpack
	// static ...; // 0x10A56810
	// static ...; // 0x10A56808
	// long unit_index;
	// long definition_index;
		// long player_index;
			// s_simulation_unit_pickup_event_data data;
	// function call : void (*const)(long, long, long *, long, long, void const *)

	static void (*const simulation_action_unit_event)(long, long, long *, long, long, void const *) = reinterpret_cast<void (*)(long, long, long *, long, long, void const *)>(0x4E5810);
	if (unit_index != -1 && definition_index != -1)
	{
		long player_index = object_get<s_unit_data>(unit_index)->player_index;
		if (player_index != -1)
		{
			s_simulation_unit_pickup_event_data data;
			data.type = 5;
			data.unknown = 0;
			data.definition_index = definition_index;
			simulation_action_unit_event(10, 1, &unit_index, player_index, sizeof(data), &data);
		}
	}
}

bool unit_can_pickup_healthpack(long unit_index, long equipment_index) // 0x10A57210
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?unit_can_pickup_healthpack@@YA_NJJ@Z");
	// `anonymous-namespace'::unit_can_pickup_healthpack
	// long equipment_index;
	// s_unit_data *unit;
	// s_unit_definition *unit_definition;
	// s_equipment_data *equipment;
	// s_equipment_definition *equipment_definition;
		// long i;
			// float body;
			// s_equipment_health_pack_block *healthpack_type;
			// float shield;
	// function call : void *(*const)(unsigned long, long)
	// function call : void *(*const)(unsigned long, long)
	// function call : long (*const)()
	// function call : long (*const)()
	// function call : long (*const)()

	s_unit_data *unit = object_get<s_unit_data>(unit_index);
	s_equipment_data *equipment = object_get<s_equipment_data>(equipment_index);
	if (!unit || !equipment)
		return false;
	s_unit_definition *unit_definition = (s_unit_definition *)tag_get('unit', unit->definition_index);
	s_equipment_definition *equipment_definition = (s_equipment_definition *)tag_get('eqip', equipment->definition_index);
	for (long i = 0; i < unit_definition->reviving_equipment.count; i++)
	{
		if (unit_definition->reviving_equipment[i].equipment.index == equipment->definition_index && equipment_definition->health_pack.count > 0)
		{
			s_equipment_health_pack_block *healthpack_type = &equipment_definition->health_pack[0];
			float body = unit->body_vitality;
			float shield = unit->shield_vitality;
			if (unit->health_pack_end_time > game_time_get())
			{
				body = (unit->health_pack_end_time - game_time_get()) * unit->health_pack_body_vitality_maximum + unit->body_vitality;
				shield = (unit->health_pack_end_time - game_time_get()) * unit->health_pack_shield_vitality_maximum + unit->shield_vitality;
			}
			if (body < 1.0 && healthpack_type->health_amount > 0.0 || shield < 1.0 && healthpack_type->shield_amount > 0.0)
				return true;
		}
	}
	return false;
}

bool unit_can_pickup_equipment_hook(long unit_index, long equipment_index) // 0x10A56F20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?unit_can_pickup_equipment_hook@@YA_NJJ@Z");
	// `anonymous-namespace'::unit_can_pickup_equipment_hook
	// long equipment_index;
	// long player_index;
	// bool (*const c_player_trait_weapons__get_weapon_pickup_allowed)(void *);
	// long current_equipment_index;
	// s_equipment_data *equipment;
	// long equipment_type;
	// bool (*const game_engine_running)();
		// float active_fraction;
			// long remaining_chages;
	// function call : e_equipment_type (*const)(long, long)
	// function call : bool (*const)(long, e_action)
	// function call : long (*const)(unsigned short)
	// function call : bool (*const)()
	// function call : bool (*const)()
	// function call : bool (*const)(long, e_equipment_type)
	// function call : long (*const)(unsigned short)
	// function call : long (*const)(unsigned short)
	// function call : float (*const)(long)
	// function call : bool (*const)(void *)

	bool (*const game_engine_running)() = reinterpret_cast<bool (*)()>(0x552410);
	bool (__thiscall *const c_player_trait_weapons__get_weapon_pickup_allowed)(void *) = reinterpret_cast<bool (__thiscall *)(void *)>(0x5CC5C0);
	s_equipment_data *equipment = object_get<s_equipment_data>(equipment_index);
	long equipment_type = ((long (*)(long, long))0xBA0260)(equipment->definition_index, 0);
	long current_equipment_index = object_get<s_unit_data>(unit_index)->equipment_object_indices[0];
	if (equipment->inventory_state)
		return false;
	if (((bool (*)(long, long))0xB69BA0)(unit_index, 0x3B))
		return false;
	if (equipment_type != 1 && equipment_type < 24 && !((long (*)(unsigned short))0xB89190)(equipment_index))
		return false;
	long player_index = object_get<s_unit_data>(unit_index)->player_index;
	if (equipment_type == 1)
		return game_is_multiplayer() && game_engine_running();
	if (((bool (*)(long, long))0xBA0360)(equipment->definition_index, 9))
		return unit_can_pickup_healthpack(unit_index, equipment_index);
	if (current_equipment_index != -1)
	{
		if (equipment->definition_index == object_get(current_equipment_index)->definition_index)
		{
			long remaining_chages = ((long (*)(unsigned short))0xB89190)(current_equipment_index);
			if (((long (*)(unsigned short))0xB89190)(equipment_index) <= remaining_chages)
				return false;
		}
		float active_fraction = ((float (*)(long))0xB87DA0)(current_equipment_index);
		if (active_fraction != 0.0)
			return false;
	}
	if (player_index == -1)
		return true;
	return c_player_trait_weapons__get_weapon_pickup_allowed(&player_get(player_index)->traits.weapons);
}

void unit_update_health_pack_hook(long unit_index) // 0x10A57780
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?unit_update_health_pack_hook@@YAXJ@Z");
	// `anonymous-namespace'::unit_update_health_pack_hook
	// static ...; // 0x10A5792C
	// static ...; // 0x10A57920
	// static ...; // 0x10A57918
	// long unit_index;
	// s_unit_data *unit;
		// float tick_length;
		// unsigned long long update_flags;
	// function call : long (*const)()
	// function call : float (*const)()
	// function call : void (*const)(long, unsigned long long *)

	s_unit_data *unit = object_get<s_unit_data>(unit_index);
	if (!(unit->damage_flags & 4) && unit->health_pack_end_time > game_time_get())
	{
		float tick_length = game_tick_length();
		unit->body_vitality += tick_length * unit->health_pack_body_vitality_maximum;
		if (unit->body_vitality > 1.0f)
			unit->body_vitality = 1.0f;
		if (unit->body_vitality < 0.0f)
			unit->body_vitality = 0.0f;
		unit->shield_vitality += tick_length * unit->health_pack_shield_vitality_maximum;
		if (unit->shield_vitality > 1.0f)
			unit->shield_vitality = 1.0f;
		if (unit->shield_vitality < 0.0f)
			unit->shield_vitality = 0.0f;
		unsigned long long update_flags = 0xC0;
		eldorado::simulation_action_object_update_internal(unit_index, &update_flags);
	}
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_tag_block<s_equipment_health_pack_block>::try_get_element(__int32, s_equipment_health_pack_block **) const;
template bool c_tag_block<s_object_reviving_equipment_definition>::try_get_element(__int32, s_object_reviving_equipment_definition **) const;
template long const & s_static_array<long,4>::operator[](long) const;
template s_equipment_health_pack_block & c_tag_block<s_equipment_health_pack_block>::operator[](__int32);
template s_equipment_health_pack_block * c_tag_block<s_equipment_health_pack_block>::get_element(__int32) const;
template s_object_reviving_equipment_definition & c_tag_block<s_object_reviving_equipment_definition>::operator[](__int32);
template s_object_reviving_equipment_definition * c_tag_block<s_object_reviving_equipment_definition>::get_element(__int32) const;
template s_scenario_profile & c_tag_block<s_scenario_profile>::operator[](__int32);

/* ---------- explicit instantiations */
template s_equipment_data * object_get<s_equipment_data>(unsigned long);
