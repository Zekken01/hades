/* ---------- headers */

#include "Player/PlayerEmotes.hpp"
#include "hades/hades.h"

#include "Blam/animations/mixing_board/channels/animation_channel.hpp"
#include "Blam/BitStream.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_globals.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/bitstream.hpp"
#include "Blam/memory/data_array.inl"
#include "Blam/memory/data_iterator.inl"
#include "Blam/memory/static_array.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/mods/mod_globals.hpp"
#include "Blam/mods/player_action_set.hpp"
#include "Blam/motor/action_system.hpp"
#include "Blam/motor/motor_system.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/objects/object_types.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/simulation/simulation_type_collection.hpp"
#include "Blam/simulation/simulation_types.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "Blam/units/units.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "mods/ModGlobals.hpp"
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
#include <limits>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include "Objects/ObjectMessaging.hpp"

#include "Modules/ModuleServer.hpp"  // hades: added for 0x107EA0D0

/* ---------- forward declarations */

class c_bitstream;
class c_motor_task;
class c_simulation_event_definition;
class c_simulation_type_collection;
struct c_animation_channel;
struct c_motor_request;
struct c_replication_outgoing_event;
struct lambda_1;
struct s_action_definition;
struct s_action_request;
struct s_game_globals;
struct s_mod_globals_definition;
struct s_mod_globals_player_character_customization;
struct s_mod_player_action;
struct s_mod_player_actions_set_definition;
struct s_object_data;
struct s_object_header;
struct s_player_datum;
struct s_unit_camera_definition;
struct s_unit_data;
struct simulation_event_definition_return_value;
namespace Blam
{
	class BitStream;
}
namespace Player
{
	class CPlayerEmotes;
}
namespace hades_file_local
{
	struct s_simulation_player_emote_event_data;
	class CPlayerEmoteAction;
	class c_simulation_player_emote_event_definition;
}
using namespace hades_file_local;

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;
namespace Player {}
using namespace ::Player;
namespace Objects {}
using namespace ::Objects;
namespace Blam {}
using namespace ::Blam;

/* ---------- constants */

/* ---------- definitions */

namespace hades_file_local
{
	struct s_simulation_player_emote_event_data
	{
		public:
		enum e_actions
		{
			_action_start = 0,
			_action_stop,
		};
		public:
		long action_type; // 0x0
		long emote_definition_index; // 0x4
		short emote_index; // 0x8
		short player_index; // 0xA
	};
	static_assert(sizeof(s_simulation_player_emote_event_data) == 12, "Invalid s_simulation_player_emote_event_data size");

	class CPlayerEmoteAction
	{
	public:
		public:
		struct SActionRequest :
			public s_action_request
		{
			__int32 definitionIndex; // 0x4
			short emoteIndex; // 0x8
			SActionRequest(__int32, __int32);
			void Submit(long);
			void submit_unit_holograms(__int32);
			unsigned char __pad0[2]; // 0xA
		};
		static_assert(sizeof(SActionRequest) == 12, "Invalid SActionRequest size");
		public:
		static void unit_put_away_weapons(long);
		static bool ActionSubmit(long, s_action_request const *);
		static bool ActionUpdate(long, e_action);
		static void ActionFinished(long, e_action);
		static void ActionInterrupt(long, e_action);
		static void ActionAnimationEvent(long, e_action, unsigned long);
		static bool StartAnimation(long, unsigned long, unsigned long);
		static s_action_definition m_definition;
	};
	static_assert(sizeof(CPlayerEmoteAction) == 1, "Invalid CPlayerEmoteAction size");

	class c_simulation_player_emote_event_definition :
		public c_simulation_event_definition
	{
	private:
		virtual e_simulation_event_type event_type() const;
		virtual char const *event_name() const;
		virtual long payload_size() const;
		virtual long number_of_entity_references() const;
		virtual bool reference_delays_entity_deletion() const;
		virtual bool event_can_be_transmitted(c_replication_outgoing_event const *, s_simulation_view_telemetry_data const *) const;
		virtual long minimum_required_bits(c_replication_outgoing_event const *, s_simulation_view_telemetry_data const *, long *) const;
		virtual float calculate_relevance(c_replication_outgoing_event const *, s_simulation_view_telemetry_data const *, float) const;
		virtual void write_description_to_string(c_replication_outgoing_event const *, s_simulation_view_telemetry_data const *, float, long, char *) const;
		virtual simulation_event_definition_return_value *gather_requirements_data(simulation_event_definition_return_value *, c_replication_outgoing_event const *, s_simulation_view_telemetry_data const *) const;
		virtual void event_payload_encode(long, void const *, c_bitstream *, bool) const;
		virtual bool event_payload_decode(long, void *, c_bitstream *, bool) const;
		virtual void prepare_event_data_for_gameworld(long, void *);
		virtual bool apply_game_event(long, long const *, long, void const *);
	public:
		// c_simulation_player_emote_event_definition(c_simulation_player_emote_event_definition &); /* compiler_generated(): left implicit, as the original's was */
		// c_simulation_player_emote_event_definition(c_simulation_player_emote_event_definition const &); /* compiler_generated(): left implicit, as the original's was */
		// c_simulation_player_emote_event_definition(); /* compiler_generated(): left implicit, as the original's was */
		// c_simulation_player_emote_event_definition &operator=(c_simulation_player_emote_event_definition &); /* compiler_generated(): left implicit, as the original's was */
		// c_simulation_player_emote_event_definition &operator=(c_simulation_player_emote_event_definition const &); /* compiler_generated(): left implicit, as the original's was */
	};
	static_assert(sizeof(c_simulation_player_emote_event_definition) == 4, "Invalid c_simulation_player_emote_event_definition size");
}
using namespace hades_file_local;
//class Player::CPlayerEmotes::RequestStartEmote::__l2::<lambda_1>
//{
//public:
//	void operator()() const;
//	<lambda_1>(Player::CPlayerEmotes::RequestStartEmote::__l2::<lambda_1> &);
//	<lambda_1>(long const &, __int32 const &, short const &);
//private:
//	long playerIndex; // 0x0
//	__int32 definitionIndex; // 0x4
//	short emoteIndex; // 0x8
//public:
//	Player::CPlayerEmotes::RequestStartEmote::__l2::<lambda_1> &operator=(Player::CPlayerEmotes::RequestStartEmote::__l2::<lambda_1> const &);
//};
//static_assert(sizeof(Player::CPlayerEmotes::RequestStartEmote::__l2::<lambda_1>) == 12, "Invalid Player::CPlayerEmotes::RequestStartEmote::__l2::<lambda_1> size");

//class Player::CPlayerEmotes::RequestStopEmote::__l2::<lambda_1>
//{
//public:
//	void operator()() const;
//	<lambda_1>(Player::CPlayerEmotes::RequestStopEmote::__l2::<lambda_1> &);
//	<lambda_1>(long const &);
//private:
//	long playerIndex; // 0x0
//public:
//	Player::CPlayerEmotes::RequestStopEmote::__l2::<lambda_1> &operator=(Player::CPlayerEmotes::RequestStopEmote::__l2::<lambda_1> const &);
//};
//static_assert(sizeof(Player::CPlayerEmotes::RequestStopEmote::__l2::<lambda_1>) == 4, "Invalid Player::CPlayerEmotes::RequestStopEmote::__l2::<lambda_1> size");

/* ---------- prototypes */

namespace eldorado
{
	// Functions in eldorado.exe, named as in ManagedDonkey.
	static auto const action_executing = reinterpret_cast<bool (*)(long, e_action)>(0xB69BA0);
	static auto const action_submit0 = reinterpret_cast<bool(__cdecl *)(long, s_action_request *)>(0xB69C50);
	static auto const game_is_authoritative = reinterpret_cast<bool (*)()>(0x5319C0);
	static auto const motor_system_submit = reinterpret_cast<e_motor_result(__cdecl *)(long, c_motor_request *)>(0xB749C0);
	static auto const player_index_from_absolute_player_index = reinterpret_cast<long(__cdecl *)(long)>(0x53B1A0);
	static auto const player_is_local = reinterpret_cast<bool (*)(long)>(0x53B4E0);
	static auto const player_mapping_get_player_by_input_user = reinterpret_cast<unsigned long(__cdecl *)(long)>(0x589C30);
}

extern void *(*const tag_get)(unsigned long, long);  // hades: added for 0x107EBE20
extern s_game_globals *game_globals_get();  // hades: added for 0x107EBE20

template<typename t_arg0> static t_arg0 *object_get(unsigned long object_index) { return (t_arg0 *)object_get(object_index); }  // hades: a file-local template in the original (undecorated `object_get<T>`), defined so it is emitted;  // hades: added for 0x107ED270

namespace hades_file_local { extern c_simulation_player_emote_event_definition emote_definition; }  // hades: added for 0x107EBDD0

s_player_datum *player_get(unsigned long player_index);  // hades: added for 0X107EB8D0

bool PlayerCanEmote(__int32 playerIndex, __int32 definitionIndex, short emoteIndex);
void PlayerStartEmote(__int32 playerIndex, long definitionIndex, long emoteIndex);
void PlayerStopEmote(__int32 playerIndex);

/* ---------- globals */

extern s_object_data *(*const object_try_and_get_and_verify_type)(unsigned long, c_enum<enum e_object_type,long>); // 0x11248848

namespace Player
{
	s_action_definition *CPlayerEmotes::m_emote_action_definition = &CPlayerEmoteAction::m_definition; // 0x11352534
}

/* ---------- private variables */

s_action_definition CPlayerEmoteAction::m_definition = { CPlayerEmoteAction::ActionSubmit, CPlayerEmoteAction::ActionUpdate, CPlayerEmoteAction::ActionAnimationEvent, CPlayerEmoteAction::ActionFinished, CPlayerEmoteAction::ActionInterrupt }; // 0x11352538

/* ---------- public code */

namespace Player
{
	bool CPlayerEmotes::RequestStartEmote(short emoteIndex) // 0x107EBE20
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?RequestStartEmote@CPlayerEmotes@Player@@SA_NF@Z");

		long playerIndex = eldorado::player_mapping_get_player_by_input_user(0);
		if (playerIndex == -1)
			return false;
		short characterTypeIndex = -1;
		s_player_datum *player = player_get(playerIndex);
		if (player->unit_index != -1)
			characterTypeIndex = player->character_type_index;
		else
			return false;
		s_game_globals const *matg = game_globals_get();
		s_mod_globals_definition const *modg = mod_globals_get_definition();
		__int32 player_character_customization_index = -1;
		for (__int32 i = 0; i < modg->player_character_customizations.count; i++)
		{
			s_mod_globals_player_character_customization *character = nullptr;
			if (!modg->player_character_customizations.try_get_element(i, &character))
				continue;
			if (!character || character->global_player_character_type_index >= matg->player_character_types.count)
				continue;
			if (!matg->player_character_types[character->global_player_character_type_index].name)
				continue;
			if (characterTypeIndex == character->global_player_character_type_index)
			{
				player_character_customization_index = i;
				break;
			}
		}
		if (player_character_customization_index == -1)
			return false;
		if (modg->player_character_customizations[player_character_customization_index].action_set.index == -1)
			return false;
		__int32 definitionIndex = modg->player_character_customizations[player_character_customization_index].action_set.index;
		s_mod_player_actions_set_definition *const emoteTag = (s_mod_player_actions_set_definition *)tag_get('pact', definitionIndex);
		if (!emoteTag)
			return false;
		Objects::CObjectMessaging::EnqueueAction([playerIndex, definitionIndex, emoteIndex]()
		{
			PlayerStartEmote(playerIndex, definitionIndex, emoteIndex);
		});
		return true;
	}

	void CPlayerEmotes::RequestStopEmote() // 0x107EC1B0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?RequestStopEmote@CPlayerEmotes@Player@@SAXXZ");

		long playerIndex = eldorado::player_mapping_get_player_by_input_user(0);
		if (playerIndex == -1)
		{
			return;
		}

		Objects::CObjectMessaging::EnqueueAction([playerIndex]()
		{
			PlayerStopEmote(playerIndex);
		});
	}

	bool CPlayerEmotes::PlayerIsEmoting(__int32 playerIndex) // 0x107EB8D0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?PlayerIsEmoting@CPlayerEmotes@Player@@SA_NH@Z");

		s_player_datum *player = player_get(playerIndex);
		return player && player->unit_index != -1 && ((bool(__cdecl *)(long, int))0xb69ba0)(player->unit_index, 87);
	}

	bool CPlayerEmotes::UnitRequiresThirdPersonCamera(__int32 unitIndex) // 0x107EC7E0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?UnitRequiresThirdPersonCamera@CPlayerEmotes@Player@@SA_NH@Z");

		if (!((bool(__cdecl *)(int, int))0xb69ba0)(unitIndex, 87))
			return false;
		SActionStateData *stateData = Player::CPlayerEmotes::GetUnitActionState(unitIndex);
		if (!stateData || stateData->definitionIndex == -1)
			return false;
		s_mod_player_actions_set_definition *definition = s_mod_player_actions_set_definition::get(stateData->definitionIndex);
		s_mod_player_action &action = definition->actions[stateData->emoteIndex];
		return (action.flags & 2) != 0;
	}

	bool CPlayerEmotes::UnitCameraMovementInhibited(__int32 unitIndex) // 0x107EC4B0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?UnitCameraMovementInhibited@CPlayerEmotes@Player@@SA_NH@Z");

		if (!((bool(__cdecl *)(long, long))0xb69ba0)(unitIndex, 87))
		{
			return false;
		}
		SActionStateData *stateData = Player::CPlayerEmotes::GetUnitActionState(unitIndex);
		if (!stateData || stateData->definitionIndex == -1)
		{
			return false;
		}
		s_mod_player_actions_set_definition *actionSet = s_mod_player_actions_set_definition::get(stateData->definitionIndex);
		s_mod_player_action *actionDef = &actionSet->actions[stateData->emoteIndex];
		return (actionDef->flags & 8) != 0;
	}

	bool CPlayerEmotes::UnitMovementInhibited(__int32 unitIndex) // 0x107EC6D0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?UnitMovementInhibited@CPlayerEmotes@Player@@SA_NH@Z");

		if (!((bool (__cdecl *)(int, int))0xb69ba0)(unitIndex, 87))
			return false;
		SActionStateData *stateData = Player::CPlayerEmotes::GetUnitActionState(unitIndex);
		if (!stateData || stateData->definitionIndex == -1)
			return false;
		s_mod_player_actions_set_definition *definition = s_mod_player_actions_set_definition::get(stateData->definitionIndex);
		s_mod_player_action *action = &definition->actions[stateData->emoteIndex];
		return (action->flags & 4) != 0;
	}

	bool CPlayerEmotes::UnitCancelInhibited(__int32 unitIndex) // 0x107EC5C0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?UnitCancelInhibited@CPlayerEmotes@Player@@SA_NH@Z");

		if (!((bool(__cdecl *)(long, long))0xb69ba0)(unitIndex, 87))
		{
			return false;
		}
		SActionStateData *stateData = Player::CPlayerEmotes::GetUnitActionState(unitIndex);
		if (!stateData || stateData->definitionIndex == -1)
		{
			return false;
		}
		s_mod_player_actions_set_definition *actionSet = s_mod_player_actions_set_definition::get(stateData->definitionIndex);
		s_mod_player_action *actionDef = &actionSet->actions[stateData->emoteIndex];
		return (actionDef->flags & 0x10) != 0;
	}

	bool CPlayerEmotes::GetUnitCamera(__int32 unitIndex, s_unit_camera_definition **camera) // 0x107EB640
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetUnitCamera@CPlayerEmotes@Player@@SA_NHPAPAUs_unit_camera_definition@@@Z");

		if (!((bool(__cdecl *)(long, long))0xb69ba0)(unitIndex, 87))
		{
			return false;
		}
		SActionStateData *stateData = Player::CPlayerEmotes::GetUnitActionState(unitIndex);
		if (!stateData || stateData->definitionIndex == -1)
		{
			return false;
		}
		s_mod_player_actions_set_definition *definition = s_mod_player_actions_set_definition::get(stateData->definitionIndex);
		s_mod_player_action *actionDef = &definition->actions[stateData->emoteIndex];
		if (actionDef->override_camera.address)
		{
			*camera = &actionDef->override_camera[0];
			return true;
		}
		return false;
	}

	Player::CPlayerEmotes::SActionStateData *CPlayerEmotes::GetUnitActionState(__int32 unitIndex) // 0x107EB590
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetUnitActionState@CPlayerEmotes@Player@@SAPAUSActionStateData@12@H@Z");

		s_unit_data *unit = (s_unit_data *)object_try_and_get_and_verify_type(unitIndex, 0x2003);

		if (!unit)
		{
			return nullptr;
		}

		return (SActionStateData *)offset_pointer(unit, unit->action_state_storage.offset + 0x94);
	}

	void CPlayerEmotes::RegisterSimulationTypes(c_simulation_type_collection *type_collection, __int32 *enitty_type_count, __int32 *event_type_count) // 0x107EBDD0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?RegisterSimulationTypes@CPlayerEmotes@Player@@SAXPAVc_simulation_type_collection@@PAH1@Z");

		type_collection->register_event_definition(_simulation_event_type_player_taunt_request, &emote_definition);
	}
}

/* ---------- private code */

_inline CPlayerEmoteAction::SActionRequest::SActionRequest(__int32 definitionIndex, __int32 emoteIndex) // 0x107EB2F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0SActionRequest@CPlayerEmoteAction@hades_file_local@@QAE@HH@Z");

	this->definitionIndex = definitionIndex;
	this->emoteIndex = emoteIndex;
	action_type = _action_player_emote;
}

_inline void CPlayerEmoteAction::SActionRequest::Submit(long unit_index) // 0x107EC430
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Submit@SActionRequest@CPlayerEmoteAction@hades_file_local@@QAEXJ@Z");

	eldorado::action_submit0(unit_index, this);
	submit_unit_holograms(unit_index);
}

_inline void CPlayerEmoteAction::SActionRequest::submit_unit_holograms(__int32 unit_index) // 0x107ECF90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?submit_unit_holograms@SActionRequest@CPlayerEmoteAction@hades_file_local@@QAEXH@Z");

	c_data_array<s_object_header> *object_headers = object_headers_get();
	for (c_data_iterator<s_object_header> it = object_headers->begin(); it != object_headers->end(); ++it)
	{
		s_unit_data *unit = (s_unit_data *)object_try_and_get_and_verify_type(it.current_datum_index, 0x2003);
		if (!unit)
			continue;
		if (unit->unit_flags & 0x40000000 && unit->hologram_creator_weak_unit_index == unit_index && it.current_datum_index != -1)
			((void (*)(long, s_action_request *))0xB69C50)(it.current_datum_index, this);
	}
}

_inline void CPlayerEmoteAction::unit_put_away_weapons(long unit_index) // 0x107ED270
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?unit_put_away_weapons@CPlayerEmoteAction@hades_file_local@@SAXJ@Z");

	bool (*const weapon_put_away)(long, bool, bool) = reinterpret_cast<bool (*)(long, bool, bool)>(0xB65530);
	void (*const unit_send_message_to_first_person)(long, e_unit_messages) = reinterpret_cast<void (*)(long, e_unit_messages)>(0xBA5750);
	void (*const unit_action_weapon_put_away_end)(long, bool, char) = reinterpret_cast<void (*)(long, bool, char)>(0xBA5940);
	void (*const unit_unzoom)(long, bool) = reinterpret_cast<void (*)(long, bool)>(0xB49D80);
	s_unit_data *unit = object_get<s_unit_data>(unit_index);
	for (long i = 0; i < 2; i++)
	{
		long inventory_index = unit->current_weapon_set.indices[i];
		if (inventory_index != -1)
		{
			long weapon_index = unit->weapon_object_indices[inventory_index];
			if (object_try_and_get_and_verify_type(weapon_index, 4))
			{
				if (weapon_put_away(weapon_index, false, true))
				{
					unit_unzoom(unit_index, false);
					unit_send_message_to_first_person(unit_index, (e_unit_messages)(i + 18));
				}
				unit_action_weapon_put_away_end(unit_index, i == 0, 0);
			}
		}
	}
	((void (*)(long, long, long, bool))0xB8C930)(unit_index, 0x89, 0, true);
}

_inline bool CPlayerEmoteAction::ActionSubmit(long unit_index, s_action_request const *action_request) // 0x107EA0D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ActionSubmit@CPlayerEmoteAction@hades_file_local@@SA_NJPBUs_action_request@@@Z");

	SActionRequest *request = (SActionRequest *)action_request;
	s_mod_player_actions_set_definition *actionSet = s_mod_player_actions_set_definition::get(request->definitionIndex);
	s_mod_player_action *actionDef = actionSet->actions.get_element(request->emoteIndex);
	if (!actionDef)
		return false;
	if (!actionDef->animation_enter)
		return false;
	if (!((bool (*)(long, long, long))0xB90C80)(unit_index, 0x57, 15) && (!((bool (*)())0x531B20)() || !Utils::Singleton<Modules::ModuleServer>::Instance().VarServerEmotesDuringPodiumEnabledClient->ValueInt))
		return false;
	long active_primary_weapon_index = ((long (*)(long, long))0xB42EF0)(unit_index, 0);
	if (active_primary_weapon_index != -1 && ((bool (*)(long))0xB641D0)(active_primary_weapon_index))
		return false;
	((void (*)(long, long, long))0xB91630)(unit_index, 15, 0);
	((void (*)(long, long))0xB69CF0)(unit_index, 2);
	if (!StartAnimation(unit_index, 0, actionDef->animation_enter))
		return false;
	if (actionDef->flags & 1)
		unit_put_away_weapons(unit_index);
	Player::CPlayerEmotes::SActionStateData *emoteStateData = Player::CPlayerEmotes::GetUnitActionState(unit_index);
	emoteStateData->definitionIndex = request->definitionIndex;
	emoteStateData->emoteIndex = request->emoteIndex;
	emoteStateData->cancelled = false;
	emoteStateData->playedExit = false;
	return true;
}

_inline bool CPlayerEmoteAction::ActionUpdate(long unit_index, e_action action_type) // 0x107EA320
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ActionUpdate@CPlayerEmoteAction@hades_file_local@@SA_NJW4e_action@@@Z");

	Player::CPlayerEmotes::SActionStateData *emoteStateData = Player::CPlayerEmotes::GetUnitActionState(unit_index);
	s_mod_player_actions_set_definition *actionSet = s_mod_player_actions_set_definition::get(emoteStateData->definitionIndex);
	s_mod_player_action *actionDef = actionSet->actions.get_element(emoteStateData->emoteIndex);
	if (!(actionDef->flags & 0x40))
	{
		c_motor_task *task = ((c_motor_task *(*)(long, long))0xB91490)(unit_index, 0x57);
		if (task)
		{
			c_animation_channel *channel = ((c_animation_channel *(*)(long, c_motor_task *))0xB90260)(unit_index, task);
			if (channel->state_flags & 2)
			{
				channel->state_flags &= ~7;
				channel->settings.playback_flags |= 1;
				((void (__thiscall *)(c_animation_channel *, float))0x983B30)(channel, 0.0f);
			}
		}
	}
	if (emoteStateData->cancelled && !emoteStateData->playedExit)
	{
		emoteStateData->playedExit = true;
		((void (*)(long, long, long))0xB91630)(unit_index, 15, 0);
		StartAnimation(unit_index, 0, actionDef->animation_exit);
	}
	return true;
}

_inline void CPlayerEmoteAction::ActionFinished(long unit_index, e_action action_type) // 0x107EA4F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ActionFinished@CPlayerEmoteAction@hades_file_local@@SAXJW4e_action@@@Z");

	Player::CPlayerEmotes::SActionStateData *emoteStateData = Player::CPlayerEmotes::GetUnitActionState(unit_index);
	s_mod_player_actions_set_definition *actionSet = s_mod_player_actions_set_definition::get(emoteStateData->definitionIndex);
	s_mod_player_action *actionDef = actionSet->actions.get_element(emoteStateData->emoteIndex);

	if (!emoteStateData->cancelled && actionDef->animation_idle != -1 && actionDef->animation_idle != 0)
	{
		StartAnimation(unit_index, 0, actionDef->animation_idle);
	}
}

_inline void CPlayerEmoteAction::ActionInterrupt(long unit_index, e_action action_type) // 0x107EA5D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ActionInterrupt@CPlayerEmoteAction@hades_file_local@@SAXJW4e_action@@@Z");
}

_inline void CPlayerEmoteAction::ActionAnimationEvent(long unit_index, e_action action_type, unsigned long flags) // 0x107EA5F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ActionAnimationEvent@CPlayerEmoteAction@hades_file_local@@SAXJW4e_action@@K@Z");
}

_inline bool CPlayerEmoteAction::StartAnimation(long unit_index, unsigned long mode, unsigned long state) // 0x107EC2F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?StartAnimation@CPlayerEmoteAction@hades_file_local@@SA_NJKK@Z");

	c_motor_request motor_request{};

	motor_request.unknown0 = 1;
	motor_request.animation_name1 = mode;
	motor_request.animation_name2 = state;
	motor_request.task_id = _motor_task_animation;
	motor_request.action_type = _action_player_emote;
	motor_request.interpolation_time = 0.1f;

	e_motor_result result = eldorado::motor_system_submit(unit_index, &motor_request);
	return result != 0;
}

_inline e_simulation_event_type c_simulation_player_emote_event_definition::event_type() const // 0x107EA610
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?event_type@c_simulation_player_emote_event_definition@hades_file_local@@EBE?AW4e_simulation_event_type@@XZ");

	return _simulation_event_type_player_taunt_request;
}

_inline char const *c_simulation_player_emote_event_definition::event_name() const // 0x107EA640
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?event_name@c_simulation_player_emote_event_definition@hades_file_local@@EBEPBDXZ");

	return "emote";
}

_inline long c_simulation_player_emote_event_definition::payload_size() const // 0x107EA670
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?payload_size@c_simulation_player_emote_event_definition@hades_file_local@@EBEJXZ");

	return 0xC;
}

_inline long c_simulation_player_emote_event_definition::number_of_entity_references() const // 0x107EA6A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?number_of_entity_references@c_simulation_player_emote_event_definition@hades_file_local@@EBEJXZ");

	return 0;
}

_inline bool c_simulation_player_emote_event_definition::reference_delays_entity_deletion() const // 0x107EA6C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?reference_delays_entity_deletion@c_simulation_player_emote_event_definition@hades_file_local@@EBE_NXZ");

	return false;
}

_inline bool c_simulation_player_emote_event_definition::event_can_be_transmitted(c_replication_outgoing_event const *__formal, s_simulation_view_telemetry_data const *__formal1) const // 0x107EA6E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?event_can_be_transmitted@c_simulation_player_emote_event_definition@hades_file_local@@EBE_NPBUc_replication_outgoing_event@@PBUs_simulation_view_telemetry_data@@@Z");

	return true;
}

_inline long c_simulation_player_emote_event_definition::minimum_required_bits(c_replication_outgoing_event const *__formal, s_simulation_view_telemetry_data const *__formal1, long *__formal2) const // 0x107EA700
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?minimum_required_bits@c_simulation_player_emote_event_definition@hades_file_local@@EBEJPBUc_replication_outgoing_event@@PBUs_simulation_view_telemetry_data@@PAJ@Z");

	return 0x38;
}

_inline float c_simulation_player_emote_event_definition::calculate_relevance(c_replication_outgoing_event const *__formal, s_simulation_view_telemetry_data const *__formal1, float __formal2) const // 0x107EA730
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?calculate_relevance@c_simulation_player_emote_event_definition@hades_file_local@@EBEMPBUc_replication_outgoing_event@@PBUs_simulation_view_telemetry_data@@M@Z");

	return 0.0f;
}

_inline void c_simulation_player_emote_event_definition::write_description_to_string(c_replication_outgoing_event const *__formal, s_simulation_view_telemetry_data const *__formal1, float __formal2, long __formal3, char *description) const // 0x107EA750
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?write_description_to_string@c_simulation_player_emote_event_definition@hades_file_local@@EBEXPBUc_replication_outgoing_event@@PBUs_simulation_view_telemetry_data@@MJPAD@Z");

	sprintf(description, "blam");
}

_inline simulation_event_definition_return_value *c_simulation_player_emote_event_definition::gather_requirements_data(simulation_event_definition_return_value *data, c_replication_outgoing_event const *e, s_simulation_view_telemetry_data const *telemetry) const // 0x107EA7B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?gather_requirements_data@c_simulation_player_emote_event_definition@hades_file_local@@EBEPAUsimulation_event_definition_return_value@@PAU3@PBUc_replication_outgoing_event@@PBUs_simulation_view_telemetry_data@@@Z");

	data->value = data->value & 0xFFFFFF01 | 0x101;
	data->value = data->value & 0x1FF | 0xA800;
	return data;
}

_inline void c_simulation_player_emote_event_definition::event_payload_encode(long payload_size, void const *payload, c_bitstream *packet, bool predicted) const // 0x107EA810
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?event_payload_encode@c_simulation_player_emote_event_definition@hades_file_local@@EBEXJPBXPAVc_bitstream@@_N@Z");

	Blam::BitStream *packet_impl = (Blam::BitStream *)packet;
	s_simulation_player_emote_event_data *const data = (s_simulation_player_emote_event_data *)payload;

	packet_impl->Write<long>(data->action_type, 2);
	packet_impl->Write<short>(data->player_index, 6);

	if (data->action_type == s_simulation_player_emote_event_data::_action_start)
	{
		packet_impl->Write<long>(data->emote_definition_index, 32);
		packet_impl->Write<short>(data->emote_index, 16);
	}
}

_inline bool c_simulation_player_emote_event_definition::event_payload_decode(long payload_size, void *payload, c_bitstream *packet, bool predicted) const // 0x107EA8D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?event_payload_decode@c_simulation_player_emote_event_definition@hades_file_local@@EBE_NJPAXPAVc_bitstream@@_N@Z");

	Blam::BitStream *packet_impl = (Blam::BitStream *)packet;
	s_simulation_player_emote_event_data *data = (s_simulation_player_emote_event_data *)payload;

	data->action_type = packet_impl->Read<long>(2);
	data->player_index = packet_impl->Read<short>(6);

	if (data->action_type == s_simulation_player_emote_event_data::_action_start)
	{
		data->emote_definition_index = packet_impl->Read<long>(32);
		data->emote_index = packet_impl->Read<long>(16);
	}

	return true;
}

_inline void c_simulation_player_emote_event_definition::prepare_event_data_for_gameworld(long payload_size, void *payload) // 0x107EA980
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?prepare_event_data_for_gameworld@c_simulation_player_emote_event_definition@hades_file_local@@EAEXJPAX@Z");
}

_inline bool c_simulation_player_emote_event_definition::apply_game_event(long reference_gamestate_count, long const *gamestate_indices, long payload_size, void const *payload) // 0x107EA9A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?apply_game_event@c_simulation_player_emote_event_definition@hades_file_local@@EAE_NJPBJJPBX@Z");

	s_simulation_player_emote_event_data *data = (s_simulation_player_emote_event_data *)payload;
	s_player_datum *player = players_get()->try_and_get_absolute(data->player_index);

	long player_index = eldorado::player_index_from_absolute_player_index(data->player_index);
	if (player_index == -1)
	{
		return false;
	}

	switch (data->action_type)
	{
	case s_simulation_player_emote_event_data::_action_start:
		PlayerStartEmote(player_index, data->emote_definition_index, data->emote_index);
		break;
	case s_simulation_player_emote_event_data::_action_stop:
		PlayerStopEmote(player_index);
		break;
	}

	return true;
}

bool PlayerCanEmote(__int32 playerIndex, __int32 definitionIndex, short emoteIndex) // 0x107EB750
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?PlayerCanEmote@@YA_NHHF@Z");

	s_player_datum *player = player_get(playerIndex);
	if (!player)
		return false;
	if (player->unit_index == -1)
		return false;
	if (!object_get(player->unit_index))
		return false;
	s_mod_globals_definition *const modg = mod_globals_get_definition();
	if (modg)
	{
		for (__int32 i = 0; i < modg->player_character_customizations.count; i++)
		{
			if (modg->player_character_customizations[i].global_player_character_type_index == player->character_type_index)
			{
				s_mod_globals_player_character_customization *const character = modg->player_character_customizations.get_element(i);
				if (!character)
					return false;
				if (character->action_set.index != definitionIndex)
					return false;
			}
		}
	}
	s_mod_player_actions_set_definition *const actionSet = s_mod_player_actions_set_definition::get(definitionIndex);
	if (emoteIndex < 0 || emoteIndex >= actionSet->actions.count)
		return false;
	return true;
}

void PlayerStartEmote(__int32 playerIndex, long definitionIndex, long emoteIndex) // 0x107EB980
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?PlayerStartEmote@@YAXHJJ@Z");

	if (!PlayerCanEmote(playerIndex, definitionIndex, emoteIndex))
		return;
	s_player_datum *player = player_get(playerIndex);
	CPlayerEmoteAction::SActionRequest actionRequest(definitionIndex, emoteIndex);
	actionRequest.Submit(player->unit_index);
	if (eldorado::player_is_local(playerIndex) || eldorado::game_is_authoritative())
	{
		s_simulation_player_emote_event_data data;
		data.action_type = 0;
		data.player_index = playerIndex != -1 ? (unsigned short)playerIndex : -1;
		data.emote_definition_index = definitionIndex;
		data.emote_index = emoteIndex;
		((void (*const)(e_simulation_event_type, long, long *, long, long, void const *))0x4E5A40)((e_simulation_event_type)16, 0, nullptr, playerIndex, sizeof(data), &data);
	}
}

void PlayerStopEmote(__int32 playerIndex) // 0x107EBB50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?PlayerStopEmote@@YAXH@Z");

	s_player_datum *player = player_get(playerIndex);
	if (!player)
		return;
	if (player->unit_index == -1 || !object_get(player->unit_index))
		return;
	if (!eldorado::action_executing(player->unit_index, (e_action)0x57))
		return;
	if (Player::CPlayerEmotes::UnitCancelInhibited(player->unit_index))
		return;
	Player::CPlayerEmotes::SActionStateData *emoteStateData = Player::CPlayerEmotes::GetUnitActionState(player->unit_index);
	s_mod_player_actions_set_definition *actionSet = s_mod_player_actions_set_definition::get(emoteStateData->definitionIndex);
	s_mod_player_action *actionDef = actionSet->actions.get_element(emoteStateData->emoteIndex);
	if (actionDef->flags & 0x20)
		((void (*const)(long, e_action))0xB69C20)(player->unit_index, (e_action)0x57);
	else
		emoteStateData->cancelled = true;
	if (eldorado::player_is_local(playerIndex) || eldorado::game_is_authoritative())
	{
		s_simulation_player_emote_event_data data = {};
		data.action_type = 1;
		data.player_index = playerIndex != -1 ? (unsigned short)playerIndex : -1;
		((void (*const)(e_simulation_event_type, long, long *, long, long, void const *))0x4E5A40)((e_simulation_event_type)16, 0, nullptr, playerIndex, sizeof(data), &data);
	}
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_tag_block<s_mod_player_action>::try_get_element(__int32, s_mod_player_action **) const;
template bool c_tag_block<s_unit_camera_definition>::try_get_element(__int32, s_unit_camera_definition **) const;
template s_game_globals_player_character_type const & c_tag_block<s_game_globals_player_character_type>::operator[](__int32) const;
template s_mod_globals_player_character_customization const & c_tag_block<s_mod_globals_player_character_customization>::operator[](__int32) const;
template s_mod_player_action & c_tag_block<s_mod_player_action>::operator[](__int32);
template s_mod_player_action * c_tag_block<s_mod_player_action>::get_element(__int32) const;
template s_player_datum * c_data_array<s_player_datum>::try_and_get_absolute(long);
template s_unit_camera_definition & c_tag_block<s_unit_camera_definition>::operator[](__int32);
template s_unit_camera_definition * c_tag_block<s_unit_camera_definition>::get_element(__int32) const;

/* ---------- explicit instantiations */
template class std::_Invoker_ret<void,1>;

/* ---------- data definitions */
namespace hades_file_local { c_simulation_player_emote_event_definition emote_definition; }
