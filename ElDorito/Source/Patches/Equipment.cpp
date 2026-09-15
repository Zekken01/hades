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

template<typename t_arg0> t_arg0 *object_get(unsigned long object_index);  // hades: added for 0x10A553F0

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
		_extern void _sub_10A53110();
		void ApplyAll() // 0x10A53110
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@Equipment@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10A53110();
		}

		_extern void _sub_10A54CF0(long, long, s_player_action_context *);
		void PlayerConsiderEquipmentInteraction(long playerIndex, long equipmentIndex, s_player_action_context *outActionContext) // 0x10A54CF0
		{
			mangled_x86(MANGLED_TODO, "?PlayerConsiderEquipmentInteraction@Equipment@Patches@@YAXJJPAUs_player_action_context@@@Z");
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
			todo("implement");
			_sub_10A54CF0(playerIndex, equipmentIndex, outActionContext);
		}
	}
}

/* ---------- private code */

_extern void _sub_10A55750(long, long);
void player_examine_nearby_item_hook(long player_index, long item_index) // 0x10A55750
{
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
	{
		// void *equipment_def;
	}
	{
		// long loop_weapon_index;
		// player_examine_nearby_item_hook::__l2::s_unit_weapon_pickup_result pickup_result;
		{
			// __int32 i;
			{
				// long weapon_index;
				// long inventory_index;
				{
					// short rounds_picked_up;
					{
						// c_player_output_user_iterator iterator;
						{
							// s_object_data *weapon;
						}
					}
					{
						// s_object_data *weapon;
					}
				}
			}
		}
		{
			// s_item_data *equipment;
			{
				// long current_equipment_index;
				// long equipment_type;
				{
					// long output_index_index;
				}
				{
					// player_examine_nearby_item_hook::__l2::s_unit_weapon_pickup_action_request action_request;
					// c_player_output_user_iterator iterator;
				}
			}
			{
				// c_player_output_user_iterator iterator;
			}
		}
		{
			// player_examine_nearby_item_hook::__l2::s_unit_weapon_pickup_action_request action_request;
		}
	}
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
	todo("implement");
	_sub_10A55750(player_index, item_index);
}

_extern void _sub_10A56920(long);
void unit_add_initial_loadout_hook(long unit_index) // 0x10A56920
{
	// `anonymous-namespace'::unit_add_initial_loadout_hook
	// long unit_index;
	// void (*const unit_add_initial_loadout)(long);
	{
		// s_unit_data *unit;
		// s_player_datum *player;
		// s_scenario *scnr;
		// Blam::Network::Session *session;
		{
			// bool useRespawn;
			// __int32 character_profile;
		}
	}
	// function call : bool (*)()
	// function call : bool (*const)()
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : bool (*const)()
	// function call : bool (*const)()
	// function call : void (*const)(long)
	todo("implement");
	_sub_10A56920(unit_index);
}

_extern void _sub_10A56BB0(long, short, bool, bool);
void unit_add_starting_profile_equipment_hook(long unit_index, short profile_index, bool reset, bool mark_as_garbage) // 0x10A56BB0
{
	// `anonymous-namespace'::unit_add_starting_profile_equipment_hook
	// bool mark_as_garbage;
	// s_unit_data *unit;
	// bool (*const unit_add_weapon_to_inventory)(long, long, long);
	// long (*const unit_create_starting_weapon)(long, s_starting_weapon_info *, bool);
	// void (*const unit_delete_all_weapons)(long);
	// s_scenario_profile &profile;
	{
		// long i;
	}
	{
		{
			// long weapon_index;
		}
	}
	{
	}
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void (*const)(long)
	// function call : long (*const)(long, s_starting_weapon_info *, bool)
	// function call : bool (*const)(long, long, long)
	// function call : void (*const)(long)
	todo("implement");
	_sub_10A56BB0(unit_index, profile_index, reset, mark_as_garbage);
}

_extern bool _sub_10A579B0(long);
bool unit_update_weapons_hook(long unit_index) // 0x10A579B0
{
	// `anonymous-namespace'::unit_update_weapons_hook
	// long unit_index;
	// bool ret;
	// bool (*const unit_update_weapons)(unsigned __int32);
	{
		// s_unit_data *unit;
		{
			// __int32 i;
			{
				// s_player_datum *player;
				// bool equipment_Empty;
				// e_equipment_type equipment_type;
				// s_unit_data *eqipObject;
				// long equipment_index;
			}
		}
	}
	// function call : bool (*const)(unsigned __int32)
	// function call : bool (*const)()
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : e_equipment_type (*const)(long, long)
	// function call : long (*const)(long)
	// function call : float (*const)(long)
	// function call : void (*const)(long, long)
	todo("implement");
	bool __result = _sub_10A579B0(unit_index);
	return __result;
}

_extern void _sub_10A54A70(__int32, __int32, unsigned __int32);
void EquipmentUseHook(__int32 unitObjectIndex, __int32 slotIndex, unsigned __int32 isClient) // 0x10A54A70
{
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
	todo("implement");
	_sub_10A54A70(unitObjectIndex, slotIndex, isClient);
}

_extern __int32 _sub_10A54C00(unsigned __int32);
__int32 GetMPGlobalsEquipmentBlockIndex(unsigned __int32 tagIndex) // 0x10A54C00
{
	// `anonymous-namespace'::GetMPGlobalsEquipmentBlockIndex
	// unsigned __int32 tagIndex;
	// s_game_globals *game_globals;
	// s_multiplayer_globals_definition *multiplayer_globals;
	{
		// __int32 i;
	}
	// function call : void *(*const)(unsigned long, long)
	todo("implement");
	__int32 __result = _sub_10A54C00(tagIndex);
	return __result;
}

_extern void *_sub_10A54FB0(s_player_datum *);
void *Player_GetArmorAbilitiesCHUDHook(s_player_datum *playerDatum) // 0x10A54FB0
{
	// `anonymous-namespace'::Player_GetArmorAbilitiesCHUDHook
	// s_player_datum *playerDatum;
	// s_unit_data *unitObject;
	// static unsigned char `Player_GetArmorAbilitiesCHUDHook'::`2'::data[8]; // 0x124584A0
	// s_object_data *itemObject;
	// long primaryEquipmentObjectIndex;
	todo("implement");
	void * __result = _sub_10A54FB0(playerDatum);
	return __result;
}

void unit_drop_on_death_hook(long unit_index) // 0x10A57680
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?unit_drop_on_death_hook@@YAXJ@Z");
	// `anonymous-namespace'::unit_drop_on_death_hook
	// long unit_index;

	unit_drop_grenades(unit_index);
}

_extern void _sub_10A574F0(long, long);
void unit_drop_equipment_hook(long unit_index, long slot_index) // 0x10A574F0
{
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
	todo("implement");
	_sub_10A574F0(unit_index, slot_index);
}

_extern void _sub_10A57C80(long, long);
void update_equipment_vision(long equipment_index, long unit_index) // 0x10A57C80
{
	// `anonymous-namespace'::update_equipment_vision
	// static ...; // 0x10A57DDC
	// static ...; // 0x10A57DD4
	// long equipment_index;
	// long unit_index;
	// s_equipment_vision_block *(*const equipment_get_vision_definition)(long);
	// s_equipment_data *equipment;
	// long time_since_used;
	{
		// c_data_array<s_screen_effect_datum> *screen_effects;
		// s_equipment_vision_block *vision;
		{
			// c_data_iterator<s_screen_effect_datum> it;
		}
	}
	// function call : long (*const)()
	// function call : float (*const)(long)
	// function call : long (*const)(float)
	// function call : s_equipment_vision_block *(*const)(long)
	todo("implement");
	_sub_10A57C80(equipment_index, unit_index);
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

	s_equipment_data *equipment;
	const auto equipment_update = (void(*)(long, long))0xB891F0;

	equipment_update(equipment_index, unit_index);
	equipment = object_get<s_equipment_data>(equipment_index);
	if (((bool(*)(long, e_equipment_type))0xBA0360)(equipment->definition_index, (e_equipment_type)23))
	{
		update_equipment_vision(equipment_index, unit_index);
	}
}

_extern void _sub_10A576D0(long);
void unit_toss_item_object_detach_hook(long item_index) // 0x10A576D0
{
	// `anonymous-namespace'::unit_toss_item_object_detach_hook
	// long item_index;
	// void (*const object_detach)(long);
	// function call : bool (*const)()
	// function call : void (*const)(long)
	todo("implement");
	_sub_10A576D0(item_index);
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

_extern bool _sub_10A55110(void *, void *, long, long *, long, s_simulation_unit_pickup_event_data *);
bool __fastcall c_simulation_unit_pickup_event_definition__apply_game_event_hook(void *thisptr, void *__formal, long reference_gamestate_count, long *game_state_indices, long payload_size, s_simulation_unit_pickup_event_data *payload) // 0x10A55110
{
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
	{
		// long damage_reporting_type;
		// long output_index_index;
		// s_equipment_definition *definition;
	}
	// function call : long (*const)(long, long)
	// function call : void *(*const)(unsigned long, long)
	// function call : void (*const)(long, long)
	// function call : long (*const)(long, s_damage_owner *, long *, long, float, float, real_rgb_color *, void *, long)
	// function call : long (*const)(long)
	// function call : void (*const)(long, long)
	// function call : long (*const)(long, long)
	// function call : bool (*const)(void *, long, long *, long, s_simulation_unit_pickup_event_data *)
	todo("implement");
	bool __result = _sub_10A55110(thisptr, __formal, reference_gamestate_count, game_state_indices, payload_size, payload);
	return __result;
}

_extern void _sub_10A56750(long, long);
void simulation_action_pickup_healthpack(long unit_index, long definition_index) // 0x10A56750
{
	// `anonymous-namespace'::simulation_action_pickup_healthpack
	// static ...; // 0x10A56810
	// static ...; // 0x10A56808
	// long unit_index;
	// long definition_index;
	{
		// long player_index;
		{
			// s_simulation_unit_pickup_event_data data;
		}
	}
	// function call : void (*const)(long, long, long *, long, long, void const *)
	todo("implement");
	_sub_10A56750(unit_index, definition_index);
}

_extern bool _sub_10A57210(long, long);
bool unit_can_pickup_healthpack(long unit_index, long equipment_index) // 0x10A57210
{
	// `anonymous-namespace'::unit_can_pickup_healthpack
	// long equipment_index;
	// s_unit_data *unit;
	// s_unit_definition *unit_definition;
	// s_equipment_data *equipment;
	// s_equipment_definition *equipment_definition;
	{
		// long i;
		{
			// float body;
			// s_equipment_health_pack_block *healthpack_type;
			// float shield;
		}
	}
	// function call : void *(*const)(unsigned long, long)
	// function call : void *(*const)(unsigned long, long)
	// function call : long (*const)()
	// function call : long (*const)()
	// function call : long (*const)()
	todo("implement");
	bool __result = _sub_10A57210(unit_index, equipment_index);
	return __result;
}

_extern bool _sub_10A56F20(long, long);
bool unit_can_pickup_equipment_hook(long unit_index, long equipment_index) // 0x10A56F20
{
	// `anonymous-namespace'::unit_can_pickup_equipment_hook
	// long equipment_index;
	// long player_index;
	// bool (*const c_player_trait_weapons__get_weapon_pickup_allowed)(void *);
	// long current_equipment_index;
	// s_equipment_data *equipment;
	// long equipment_type;
	// bool (*const game_engine_running)();
	{
		// float active_fraction;
		{
			// long remaining_chages;
		}
	}
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
	todo("implement");
	bool __result = _sub_10A56F20(unit_index, equipment_index);
	return __result;
}

_extern void _sub_10A57780(long);
void unit_update_health_pack_hook(long unit_index) // 0x10A57780
{
	// `anonymous-namespace'::unit_update_health_pack_hook
	// static ...; // 0x10A5792C
	// static ...; // 0x10A57920
	// static ...; // 0x10A57918
	// long unit_index;
	// s_unit_data *unit;
	{
		// float tick_length;
		// unsigned long long update_flags;
	}
	// function call : long (*const)()
	// function call : float (*const)()
	// function call : void (*const)(long, unsigned long long *)
	todo("implement");
	_sub_10A57780(unit_index);
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
