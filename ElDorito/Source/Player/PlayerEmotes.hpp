#ifndef __PLAYER_PLAYEREMOTES_HPP__
#define __PLAYER_PLAYEREMOTES_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/effects/screen_effect.hpp"
#include "Blam/items/equipment_definitions.hpp"
#include "Blam/motor/action_system.hpp"
#include "Blam/simulation/simulation_type_collection.hpp"

/* ---------- forward declarations */

class c_simulation_type_collection;
struct s_action_definition;
struct s_unit_camera_acceleration_definition;
struct s_unit_camera_definition;
struct s_unit_camera_track_definition;
namespace Player
{
	class CPlayerEmotes;
}

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
struct s_unit_camera_definition
{
	c_flags<enum e_unit_camera_flags,short> flags; // 0x0
	unsigned char __pad0[2]; // 0x2
	unsigned long camera_marker_name; // 0x4
	unsigned long camera_submerged_marker_name; // 0x8
	float pitch_auto_level; // 0xC
	float pitch_range[2]; // 0x10
	c_tag_block<s_unit_camera_track_definition> camera_tracks; // 0x18
	float pitch_spring_bounds[2]; // 0x24
	float spring_velocity; // 0x2C
	c_tag_block<s_unit_camera_acceleration_definition> camera_accelerations; // 0x30
	s_unit_camera_definition(s_unit_camera_definition &); /* compiler_generated() */
	s_unit_camera_definition(s_unit_camera_definition const &); /* compiler_generated() */
	s_unit_camera_definition(); /* compiler_generated() */
	s_unit_camera_definition &operator=(s_unit_camera_definition &); /* compiler_generated() */
	s_unit_camera_definition &operator=(s_unit_camera_definition const &); /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(s_unit_camera_definition) == 60, "Invalid s_unit_camera_definition size");

namespace Player
{
	class CPlayerEmotes
	{
	public:
		public:
		struct SActionStateData
		{
			__int32 definitionIndex; // 0x0
			short emoteIndex; // 0x4
			bool cancelled : 1; // 0x6
			bool playedExit : 1; // 0x6
			void Reset();
		};
		static_assert(sizeof(SActionStateData) == 8, "Invalid SActionStateData size");
		public:
		static void RegisterSimulationTypes(c_simulation_type_collection *type_collection, __int32 *enitty_type_count, __int32 *event_type_count);
		static SActionStateData *GetUnitActionState(__int32 unitIndex);
		static bool UnitRequiresThirdPersonCamera(__int32 unitIndex);
		static bool UnitCameraMovementInhibited(__int32 unitIndex);
		static bool UnitMovementInhibited(__int32 unitIndex);
		static bool UnitCancelInhibited(__int32 unitIndex);
		static bool GetUnitCamera(__int32 unitIndex, s_unit_camera_definition **camera);
		static bool RequestStartEmote(short emoteIndex);
		static void RequestStopEmote();
		static bool PlayerIsEmoting(__int32 playerIndex);
		static s_action_definition *m_emote_action_definition;
	};
	static_assert(sizeof(Player::CPlayerEmotes) == 1, "Invalid Player::CPlayerEmotes size");
}

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __PLAYER_PLAYEREMOTES_HPP__
