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
		c_simulation_player_emote_event_definition(c_simulation_player_emote_event_definition &); /* compiler_generated() */
		c_simulation_player_emote_event_definition(c_simulation_player_emote_event_definition const &); /* compiler_generated() */
		c_simulation_player_emote_event_definition(); /* compiler_generated() */
		c_simulation_player_emote_event_definition &operator=(c_simulation_player_emote_event_definition &); /* compiler_generated() */
		c_simulation_player_emote_event_definition &operator=(c_simulation_player_emote_event_definition const &); /* compiler_generated() */
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

s_player_datum *player_get(unsigned long player_index);  // hades: added for 0X107EB8D0

bool PlayerCanEmote(__int32 playerIndex, __int32 definitionIndex, short emoteIndex);
void PlayerStartEmote(__int32 playerIndex, long definitionIndex, long emoteIndex);
void PlayerStopEmote(__int32 playerIndex);

/* ---------- globals */

namespace Player
{
	s_action_definition *CPlayerEmotes::m_emote_action_definition; // 0x11352534
}

/* ---------- private variables */

s_action_definition CPlayerEmoteAction::m_definition; // 0x11352538

/* ---------- public code */

namespace Player
{
	_extern bool _sub_107EBE20(short);
	bool CPlayerEmotes::RequestStartEmote(short emoteIndex) // 0x107EBE20
	{
		mangled_x86(MANGLED_TODO, "?RequestStartEmote@CPlayerEmotes@Player@@SA_NF@Z");
		// static ...; // 0x107EC0EA
		// static ...; // 0x107EC0E0
		// static ...; // 0x107EC0D0
		// static ...; // 0x107EC0AC
		// static ...; // 0x107EC0A4
		// short emoteIndex;
		// s_player_datum *player;
		// s_game_globals const *matg;
		// long playerIndex;
		// s_mod_globals_definition const *modg;
		// s_mod_player_actions_set_definition *const emoteTag;
		// short characterTypeIndex;
		// __int32 definitionIndex;
		// __int32 player_character_customization_index;
		{
			// __int32 i;
			{
				// s_mod_globals_player_character_customization *character;
			}
		}
		// function call : unsigned long (*const)(long)
		// function call : void *(*const)(unsigned long, long)
		todo("implement");
		bool __result = _sub_107EBE20(emoteIndex);
		return __result;
	}

	_extern void _sub_107EC1B0();
	void CPlayerEmotes::RequestStopEmote() // 0x107EC1B0
	{
		mangled_x86(MANGLED_TODO, "?RequestStopEmote@CPlayerEmotes@Player@@SAXXZ");
		// procedure flags: nofpo
		// static ...; // 0x107EC2A0
		// static ...; // 0x107EC294
		// static ...; // 0x107EC28C
		// long playerIndex;
		// function call : unsigned long (*const)(long)
		todo("implement");
		_sub_107EC1B0();
	}

	bool CPlayerEmotes::PlayerIsEmoting(__int32 playerIndex) // 0x107EB8D0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?PlayerIsEmoting@CPlayerEmotes@Player@@SA_NH@Z");
		// __int32 playerIndex;
		// s_player_datum *player;
		// function call : bool (*const)(long, e_action)

		s_player_datum *player = player_get(playerIndex);
		return player && player->unit_index != -1 && ((bool(__cdecl *)(long, int))0xb69ba0)(player->unit_index, 87);
	}

	bool CPlayerEmotes::UnitRequiresThirdPersonCamera(__int32 unitIndex) // 0x107EC7E0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?UnitRequiresThirdPersonCamera@CPlayerEmotes@Player@@SA_NH@Z");
		// __int32 unitIndex;
		// s_mod_player_action *actionDef;
		// s_mod_player_actions_set_definition *actionSet;
		// Player::CPlayerEmotes::SActionStateData *stateData;
		// function call : bool (*const)(long, e_action)

		if (!((bool(__cdecl *)(int, int))0xb69ba0)(unitIndex, 87))
			return false;
		SActionStateData *stateData = Player::CPlayerEmotes::GetUnitActionState(unitIndex);
		if (!stateData || stateData->definitionIndex == -1)
			return false;
		s_mod_player_actions_set_definition *definition = s_mod_player_actions_set_definition::get(stateData->definitionIndex);
		s_mod_player_action &action = definition->actions[stateData->emoteIndex];
		return (action.flags & 2) != 0;
	}

	_extern bool _sub_107EC4B0(__int32);
	bool CPlayerEmotes::UnitCameraMovementInhibited(__int32 unitIndex) // 0x107EC4B0
	{
		mangled_x86(MANGLED_TODO, "?UnitCameraMovementInhibited@CPlayerEmotes@Player@@SA_NH@Z");
		// __int32 unitIndex;
		// s_mod_player_action *actionDef;
		// s_mod_player_actions_set_definition *actionSet;
		// Player::CPlayerEmotes::SActionStateData *stateData;
		// function call : bool (*const)(long, e_action)
		todo("implement");
		bool __result = _sub_107EC4B0(unitIndex);
		return __result;
	}

	bool CPlayerEmotes::UnitMovementInhibited(__int32 unitIndex) // 0x107EC6D0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?UnitMovementInhibited@CPlayerEmotes@Player@@SA_NH@Z");
		// __int32 unitIndex;
		// s_mod_player_action *actionDef;
		// s_mod_player_actions_set_definition *actionSet;
		// Player::CPlayerEmotes::SActionStateData *stateData;
		// function call : bool (*const)(long, e_action)

		if (!((bool (__cdecl *)(int, int))0xb69ba0)(unitIndex, 87))
			return false;
		SActionStateData *stateData = Player::CPlayerEmotes::GetUnitActionState(unitIndex);
		if (!stateData || stateData->definitionIndex == -1)
			return false;
		s_mod_player_actions_set_definition *definition = s_mod_player_actions_set_definition::get(stateData->definitionIndex);
		s_mod_player_action *action = &definition->actions[stateData->emoteIndex];
		return (action->flags & 4) != 0;
	}

	_extern bool _sub_107EC5C0(__int32);
	bool CPlayerEmotes::UnitCancelInhibited(__int32 unitIndex) // 0x107EC5C0
	{
		mangled_x86(MANGLED_TODO, "?UnitCancelInhibited@CPlayerEmotes@Player@@SA_NH@Z");
		// __int32 unitIndex;
		// s_mod_player_action *actionDef;
		// s_mod_player_actions_set_definition *actionSet;
		// Player::CPlayerEmotes::SActionStateData *stateData;
		// function call : bool (*const)(long, e_action)
		todo("implement");
		bool __result = _sub_107EC5C0(unitIndex);
		return __result;
	}

	bool CPlayerEmotes::GetUnitCamera(__int32 unitIndex, s_unit_camera_definition **camera) // 0x107EB640
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetUnitCamera@CPlayerEmotes@Player@@SA_NHPAPAUs_unit_camera_definition@@@Z");
		// s_unit_camera_definition **camera;
		// s_mod_player_action *actionDef;
		// s_mod_player_actions_set_definition *actionSet;
		// Player::CPlayerEmotes::SActionStateData *stateData;
		// function call : bool (*const)(long, e_action)

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

	extern CPlayerEmotes::SActionStateData *_sub_107EB590(__int32);
	Player::CPlayerEmotes::SActionStateData *CPlayerEmotes::GetUnitActionState(__int32 unitIndex) // 0x107EB590
	{
		mangled_x86(MANGLED_TODO, "?GetUnitActionState@CPlayerEmotes@Player@@SAPAUSActionStateData@12@H@Z");
		// __int32 unitIndex;
		// s_unit_data *unit;
		// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
		todo("implement");
		Player::CPlayerEmotes::SActionStateData * __result = _sub_107EB590(unitIndex);
		return __result;
	}

	_extern void _sub_107EBDD0(c_simulation_type_collection *, __int32 *, __int32 *);
	void CPlayerEmotes::RegisterSimulationTypes(c_simulation_type_collection *type_collection, __int32 *enitty_type_count, __int32 *event_type_count) // 0x107EBDD0
	{
		mangled_x86(MANGLED_TODO, "?RegisterSimulationTypes@CPlayerEmotes@Player@@SAXPAVc_simulation_type_collection@@PAH1@Z");
		// __int32 *event_type_count;
		// static c_simulation_player_emote_event_definition emote_definition; // 0x11352580
		todo("implement");
		_sub_107EBDD0(type_collection, enitty_type_count, event_type_count);
	}
}

/* ---------- private code */

_inline CPlayerEmoteAction::SActionRequest::SActionRequest(__int32 definitionIndex, __int32 emoteIndex) // 0x107EB2F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0SActionRequest@CPlayerEmoteAction@hades_file_local@@QAE@HH@Z");
	// `anonymous-namespace'::CPlayerEmoteAction::SActionRequest::SActionRequest
	// __int32 emoteIndex;

	this->definitionIndex = definitionIndex;
	this->emoteIndex = emoteIndex;
	action_type = _action_player_emote;
}

_inline void CPlayerEmoteAction::SActionRequest::Submit(long unit_index) // 0x107EC430
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Submit@SActionRequest@CPlayerEmoteAction@hades_file_local@@QAEXJ@Z");
	// `anonymous-namespace'::CPlayerEmoteAction::SActionRequest::Submit
	// long unit_index;
	// function call : bool (*const)(long, s_action_request *)

	((bool(__cdecl *const)(long, s_action_request *))0xb69c50)(unit_index, this);
	submit_unit_holograms(unit_index);
}

_extern void _sub_107ECF90(CPlayerEmoteAction::SActionRequest *const, __int32);
_inline void CPlayerEmoteAction::SActionRequest::submit_unit_holograms(__int32 unit_index) // 0x107ECF90
{
	// `anonymous-namespace'::CPlayerEmoteAction::SActionRequest::submit_unit_holograms
	// static ...; // 0x107ED0C4
	// static ...; // 0x107ED0BC
	// CPlayerEmoteAction::SActionRequest *const this;
	// __int32 unit_index;
	// c_data_array<s_object_header> *object_headers;
	{
		// c_data_iterator<s_object_header> it;
		{
			// s_unit_data *unit;
		}
	}
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : bool (*const)(long, s_action_request *)
	todo("implement");
	_sub_107ECF90(this, unit_index);
}

_extern void _sub_107ED270(long);
_inline void CPlayerEmoteAction::unit_put_away_weapons(long unit_index) // 0x107ED270
{
	// `anonymous-namespace'::CPlayerEmoteAction::unit_put_away_weapons
	// long unit_index;
	// s_unit_data *unit;
	// void (*const unit_action_weapon_put_away_end)(long, bool, char);
	// void (*const unit_send_message_to_first_person)(long, e_unit_messages);
	// bool (*const weapon_put_away)(long, bool, bool);
	// void (*const unit_unzoom)(long, bool);
	{
		// long i;
		{
			// long inventory_index;
			{
				// long weapon_index;
			}
		}
	}
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : bool (*const)(long, bool, bool)
	// function call : void (*const)(long, bool)
	// function call : void (*const)(long, e_unit_messages)
	// function call : void (*const)(long, bool, char)
	// function call : char (*const)(long, unsigned long, unsigned long, bool)
	todo("implement");
	_sub_107ED270(unit_index);
}

_extern bool _sub_107EA0D0(long, s_action_request const *);
_inline bool CPlayerEmoteAction::ActionSubmit(long unit_index, s_action_request const *action_request) // 0x107EA0D0
{
	// `anonymous-namespace'::CPlayerEmoteAction::ActionSubmit
	// s_action_request const *action_request;
	// Player::CPlayerEmotes::SActionStateData *emoteStateData;
	// long active_primary_weapon_index;
	// s_mod_player_action *actionDef;
	// s_mod_player_actions_set_definition *actionSet;
	// CPlayerEmoteAction::SActionRequest *request;
	// function call : bool (*const)(long, e_action, unsigned short)
	// function call : bool (*const)()
	// function call : long (*const)(long, long *)
	// function call : bool (*const)(long)
	// function call : bool (*const)(long, short, short)
	// function call : void (*const)(long, e_action)
	todo("implement");
	bool __result = _sub_107EA0D0(unit_index, action_request);
	return __result;
}

_extern bool _sub_107EA320(long, e_action);
_inline bool CPlayerEmoteAction::ActionUpdate(long unit_index, e_action action_type) // 0x107EA320
{
	// `anonymous-namespace'::CPlayerEmoteAction::ActionUpdate
	// e_action action_type;
	// Player::CPlayerEmotes::SActionStateData *emoteStateData;
	// s_mod_player_action *actionDef;
	// s_mod_player_actions_set_definition *actionSet;
	{
		// c_motor_task *task;
		{
			// c_animation_channel *channel;
		}
	}
	// function call : c_motor_task *(*const)(long, e_action)
	// function call : c_animation_channel *(*const)(long, c_motor_task *)
	// function call : void (*const)(c_animation_channel *, float)
	// function call : bool (*const)(long, short, short)
	todo("implement");
	bool __result = _sub_107EA320(unit_index, action_type);
	return __result;
}

_extern void _sub_107EA4F0(long, e_action);
_inline void CPlayerEmoteAction::ActionFinished(long unit_index, e_action action_type) // 0x107EA4F0
{
	// `anonymous-namespace'::CPlayerEmoteAction::ActionFinished
	// e_action action_type;
	// Player::CPlayerEmotes::SActionStateData *emoteStateData;
	// s_mod_player_action *actionDef;
	// s_mod_player_actions_set_definition *actionSet;
	todo("implement");
	_sub_107EA4F0(unit_index, action_type);
}

_inline void CPlayerEmoteAction::ActionInterrupt(long unit_index, e_action action_type) // 0x107EA5D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ActionInterrupt@CPlayerEmoteAction@hades_file_local@@SAXJW4e_action@@@Z");
	// the original is empty
	// `anonymous-namespace'::CPlayerEmoteAction::ActionInterrupt
	// e_action action_type;
}

_inline void CPlayerEmoteAction::ActionAnimationEvent(long unit_index, e_action action_type, unsigned long flags) // 0x107EA5F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ActionAnimationEvent@CPlayerEmoteAction@hades_file_local@@SAXJW4e_action@@K@Z");
	// the original is empty
	// `anonymous-namespace'::CPlayerEmoteAction::ActionAnimationEvent
	// unsigned long flags;
}

_extern bool _sub_107EC2F0(long, unsigned long, unsigned long);
_inline bool CPlayerEmoteAction::StartAnimation(long unit_index, unsigned long mode, unsigned long state) // 0x107EC2F0
{
	// `anonymous-namespace'::CPlayerEmoteAction::StartAnimation
	// static ...; // 0x107EC3CC
	// long unit_index;
	// unsigned long mode;
	// unsigned long state;
	// e_motor_result result;
	// c_motor_request motor_request;
	// function call : e_motor_result (*const)(long, c_motor_request *)
	todo("implement");
	bool __result = _sub_107EC2F0(unit_index, mode, state);
	return __result;
}

extern e_simulation_event_type _sub_107EA610(c_simulation_player_emote_event_definition const *const);
_inline e_simulation_event_type c_simulation_player_emote_event_definition::event_type() const // 0x107EA610
{
	// `anonymous-namespace'::c_simulation_player_emote_event_definition::event_type
	// c_simulation_player_emote_event_definition const *const this;
	todo("implement");
	e_simulation_event_type __result = _sub_107EA610((c_simulation_player_emote_event_definition const *)this);
	return __result;
}

_inline char const *c_simulation_player_emote_event_definition::event_name() const // 0x107EA640
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?event_name@c_simulation_player_emote_event_definition@hades_file_local@@EBEPBDXZ");
	// `anonymous-namespace'::c_simulation_player_emote_event_definition::event_name
	// c_simulation_player_emote_event_definition const *const this;

	return "emote";
}

_inline long c_simulation_player_emote_event_definition::payload_size() const // 0x107EA670
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?payload_size@c_simulation_player_emote_event_definition@hades_file_local@@EBEJXZ");
	// `anonymous-namespace'::c_simulation_player_emote_event_definition::payload_size
	// c_simulation_player_emote_event_definition const *const this;

	return 0xC;
}

_inline long c_simulation_player_emote_event_definition::number_of_entity_references() const // 0x107EA6A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?number_of_entity_references@c_simulation_player_emote_event_definition@hades_file_local@@EBEJXZ");
	// `anonymous-namespace'::c_simulation_player_emote_event_definition::number_of_entity_references
	// c_simulation_player_emote_event_definition const *const this;

	return 0;
}

_inline bool c_simulation_player_emote_event_definition::reference_delays_entity_deletion() const // 0x107EA6C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?reference_delays_entity_deletion@c_simulation_player_emote_event_definition@hades_file_local@@EBE_NXZ");
	// `anonymous-namespace'::c_simulation_player_emote_event_definition::reference_delays_entity_deletion
	// c_simulation_player_emote_event_definition const *const this;

	return false;
}

_inline bool c_simulation_player_emote_event_definition::event_can_be_transmitted(c_replication_outgoing_event const *__formal, s_simulation_view_telemetry_data const *__formal1) const // 0x107EA6E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?event_can_be_transmitted@c_simulation_player_emote_event_definition@hades_file_local@@EBE_NPBUc_replication_outgoing_event@@PBUs_simulation_view_telemetry_data@@@Z");
	// `anonymous-namespace'::c_simulation_player_emote_event_definition::event_can_be_transmitted
	// s_simulation_view_telemetry_data const *__formal;

	return true;
}

_inline long c_simulation_player_emote_event_definition::minimum_required_bits(c_replication_outgoing_event const *__formal, s_simulation_view_telemetry_data const *__formal1, long *__formal2) const // 0x107EA700
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?minimum_required_bits@c_simulation_player_emote_event_definition@hades_file_local@@EBEJPBUc_replication_outgoing_event@@PBUs_simulation_view_telemetry_data@@PAJ@Z");
	// `anonymous-namespace'::c_simulation_player_emote_event_definition::minimum_required_bits
	// long *__formal;

	return 0x38;
}

_extern float _sub_107EA730(c_simulation_player_emote_event_definition const *const, c_replication_outgoing_event const *, s_simulation_view_telemetry_data const *, float);
_inline float c_simulation_player_emote_event_definition::calculate_relevance(c_replication_outgoing_event const *__formal, s_simulation_view_telemetry_data const *__formal1, float __formal2) const // 0x107EA730
{
	// `anonymous-namespace'::c_simulation_player_emote_event_definition::calculate_relevance
	// float __formal;
	todo("implement");
	float __result = _sub_107EA730((c_simulation_player_emote_event_definition const *)this, __formal, __formal1, __formal2);
	return __result;
}

_extern void _sub_107EA750(c_simulation_player_emote_event_definition const *const, c_replication_outgoing_event const *, s_simulation_view_telemetry_data const *, float, long, char *);
_inline void c_simulation_player_emote_event_definition::write_description_to_string(c_replication_outgoing_event const *__formal, s_simulation_view_telemetry_data const *__formal1, float __formal2, long __formal3, char *description) const // 0x107EA750
{
	// `anonymous-namespace'::c_simulation_player_emote_event_definition::write_description_to_string
	// char *description;
	todo("implement");
	_sub_107EA750((c_simulation_player_emote_event_definition const *)this, __formal, __formal1, __formal2, __formal3, description);
}

_inline simulation_event_definition_return_value *c_simulation_player_emote_event_definition::gather_requirements_data(simulation_event_definition_return_value *data, c_replication_outgoing_event const *e, s_simulation_view_telemetry_data const *telemetry) const // 0x107EA7B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?gather_requirements_data@c_simulation_player_emote_event_definition@hades_file_local@@EBEPAUsimulation_event_definition_return_value@@PAU3@PBUc_replication_outgoing_event@@PBUs_simulation_view_telemetry_data@@@Z");
	// `anonymous-namespace'::c_simulation_player_emote_event_definition::gather_requirements_data
	// s_simulation_view_telemetry_data const *telemetry;

	data->value = data->value & 0xFFFFFF01 | 0x101;
	data->value = data->value & 0x1FF | 0xA800;
	return data;
}

_extern void _sub_107EA810(c_simulation_player_emote_event_definition const *const, long, void const *, c_bitstream *, bool);
_inline void c_simulation_player_emote_event_definition::event_payload_encode(long payload_size, void const *payload, c_bitstream *packet, bool predicted) const // 0x107EA810
{
	// `anonymous-namespace'::c_simulation_player_emote_event_definition::event_payload_encode
	// bool predicted;
	// s_simulation_player_emote_event_data *const data;
	// Blam::BitStream *packet_impl;
	todo("implement");
	_sub_107EA810((c_simulation_player_emote_event_definition const *)this, payload_size, payload, packet, predicted);
}

_extern bool _sub_107EA8D0(c_simulation_player_emote_event_definition const *const, long, void *, c_bitstream *, bool);
_inline bool c_simulation_player_emote_event_definition::event_payload_decode(long payload_size, void *payload, c_bitstream *packet, bool predicted) const // 0x107EA8D0
{
	// `anonymous-namespace'::c_simulation_player_emote_event_definition::event_payload_decode
	// bool predicted;
	// s_simulation_player_emote_event_data *data;
	// Blam::BitStream *packet_impl;
	todo("implement");
	bool __result = _sub_107EA8D0((c_simulation_player_emote_event_definition const *)this, payload_size, payload, packet, predicted);
	return __result;
}

_inline void c_simulation_player_emote_event_definition::prepare_event_data_for_gameworld(long payload_size, void *payload) // 0x107EA980
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?prepare_event_data_for_gameworld@c_simulation_player_emote_event_definition@hades_file_local@@EAEXJPAX@Z");
	// the original is empty
	// `anonymous-namespace'::c_simulation_player_emote_event_definition::prepare_event_data_for_gameworld
	// void *payload;
}

_extern bool _sub_107EA9A0(c_simulation_player_emote_event_definition *const, long, long const *, long, void const *);
_inline bool c_simulation_player_emote_event_definition::apply_game_event(long reference_gamestate_count, long const *gamestate_indices, long payload_size, void const *payload) // 0x107EA9A0
{
	// `anonymous-namespace'::c_simulation_player_emote_event_definition::apply_game_event
	// void const *payload;
	// s_player_datum *player;
	// long player_index;
	// s_simulation_player_emote_event_data *data;
	// function call : long (*const)(long)
	todo("implement");
	bool __result = _sub_107EA9A0(this, reference_gamestate_count, gamestate_indices, payload_size, payload);
	return __result;
}

_extern bool _sub_107EB750(__int32, __int32, short);
bool PlayerCanEmote(__int32 playerIndex, __int32 definitionIndex, short emoteIndex) // 0x107EB750
{
	// `anonymous-namespace'::PlayerCanEmote
	// short emoteIndex;
	// s_player_datum *player;
	// s_mod_globals_definition *const modg;
	// s_mod_player_actions_set_definition *const actionSet;
	{
		// __int32 i;
		{
			// s_mod_globals_player_character_customization *const character;
		}
	}
	todo("implement");
	bool __result = _sub_107EB750(playerIndex, definitionIndex, emoteIndex);
	return __result;
}

_extern void _sub_107EB980(__int32, long, long);
void PlayerStartEmote(__int32 playerIndex, long definitionIndex, long emoteIndex) // 0x107EB980
{
	// `anonymous-namespace'::PlayerStartEmote
	// static ...; // 0x107EBAC0
	// static ...; // 0x107EBAB8
	// __int32 playerIndex;
	// long definitionIndex;
	// long emoteIndex;
	// s_player_datum *player;
	// CPlayerEmoteAction::SActionRequest actionRequest;
	{
		// s_simulation_player_emote_event_data data;
	}
	// function call : bool (*const)(long)
	// function call : bool (*const)()
	// function call : void (*const)(e_simulation_event_type, long, long *, long, long, void const *)
	todo("implement");
	_sub_107EB980(playerIndex, definitionIndex, emoteIndex);
}

_extern void _sub_107EBB50(__int32);
void PlayerStopEmote(__int32 playerIndex) // 0x107EBB50
{
	// `anonymous-namespace'::PlayerStopEmote
	// static ...; // 0x107EBD44
	// static ...; // 0x107EBD38
	// static ...; // 0x107EBD30
	// __int32 playerIndex;
	// s_player_datum *player;
	// Player::CPlayerEmotes::SActionStateData *emoteStateData;
	// s_mod_player_action *actionDef;
	// s_mod_player_actions_set_definition *actionSet;
	{
		// s_simulation_player_emote_event_data data;
	}
	// function call : bool (*const)(long, e_action)
	// function call : void (*const)(long, e_action)
	// function call : bool (*const)(long)
	// function call : bool (*const)()
	// function call : void (*const)(e_simulation_event_type, long, long *, long, long, void const *)
	todo("implement");
	_sub_107EBB50(playerIndex);
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
