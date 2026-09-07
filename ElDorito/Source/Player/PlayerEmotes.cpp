/* ---------- headers */

#include "Player/PlayerEmotes.hpp"
#include "hades/hades.h"

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
#include "Blam/mods/mod_globals.hpp"
#include "Blam/mods/player_action_set.hpp"
#include "Blam/motor/action_system.hpp"
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
class c_simulation_event_definition;
class c_simulation_type_collection;
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
struct s_player_datum;
struct s_unit_camera_definition;
struct s_unit_data;
struct simulation_event_definition_return_value;
namespace Player
{
	class CPlayerEmotes;
}
namespace
{
	struct s_simulation_player_emote_event_data;
	class CPlayerEmoteAction;
	class c_simulation_player_emote_event_definition;
}

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

namespace
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

	_extern bool _sub_107EB8D0(__int32);
	bool CPlayerEmotes::PlayerIsEmoting(__int32 playerIndex) // 0x107EB8D0
	{
		mangled_x86(MANGLED_TODO, "?PlayerIsEmoting@CPlayerEmotes@Player@@SA_NH@Z");
		// __int32 playerIndex;
		// s_player_datum *player;
		// function call : bool (*const)(long, e_action)
		todo("implement");
		bool __result = _sub_107EB8D0(playerIndex);
		return __result;
	}

	_extern bool _sub_107EC7E0(__int32);
	bool CPlayerEmotes::UnitRequiresThirdPersonCamera(__int32 unitIndex) // 0x107EC7E0
	{
		mangled_x86(MANGLED_TODO, "?UnitRequiresThirdPersonCamera@CPlayerEmotes@Player@@SA_NH@Z");
		// __int32 unitIndex;
		// s_mod_player_action *actionDef;
		// s_mod_player_actions_set_definition *actionSet;
		// Player::CPlayerEmotes::SActionStateData *stateData;
		// function call : bool (*const)(long, e_action)
		todo("implement");
		bool __result = _sub_107EC7E0(unitIndex);
		return __result;
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

	_extern bool _sub_107EC6D0(__int32);
	bool CPlayerEmotes::UnitMovementInhibited(__int32 unitIndex) // 0x107EC6D0
	{
		mangled_x86(MANGLED_TODO, "?UnitMovementInhibited@CPlayerEmotes@Player@@SA_NH@Z");
		// __int32 unitIndex;
		// s_mod_player_action *actionDef;
		// s_mod_player_actions_set_definition *actionSet;
		// Player::CPlayerEmotes::SActionStateData *stateData;
		// function call : bool (*const)(long, e_action)
		todo("implement");
		bool __result = _sub_107EC6D0(unitIndex);
		return __result;
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

	_extern bool _sub_107EB640(__int32, s_unit_camera_definition **);
	bool CPlayerEmotes::GetUnitCamera(__int32 unitIndex, s_unit_camera_definition **camera) // 0x107EB640
	{
		mangled_x86(MANGLED_TODO, "?GetUnitCamera@CPlayerEmotes@Player@@SA_NHPAPAUs_unit_camera_definition@@@Z");
		// s_unit_camera_definition **camera;
		// s_mod_player_action *actionDef;
		// s_mod_player_actions_set_definition *actionSet;
		// Player::CPlayerEmotes::SActionStateData *stateData;
		// function call : bool (*const)(long, e_action)
		todo("implement");
		bool __result = _sub_107EB640(unitIndex, camera);
		return __result;
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
