#ifndef __BLAM_AI_ACTOR_HPP__
#define __BLAM_AI_ACTOR_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/data.hpp"

/* ---------- forward declarations */

struct real_vector3d;
struct s_actor_activity_data;
struct s_actor_datum;
struct s_actor_firing_position_data;
struct s_actor_metadata;
struct s_actor_patrol_state;
struct s_actor_position_data;
struct s_actor_state_data;
struct s_actor_vehicle_data;
struct s_datum;
struct s_invitation_data;

/* ---------- constants */

/* ---------- definitions */

struct s_actor_metadata
{
	short type; // 0x0
	bool unknown_flag3; // 0x2
	char is_swarm; // 0x3
	char unknown_flag; // 0x4
	char ignored; // 0x5
	char squadless; // 0x6
	char field_8; // 0x7
	char field_9; // 0x8
	char field_A; // 0x9
	char field_B; // 0xA
	unsigned char __pad0[1]; // 0xB
	float original_vitality; // 0xC
	long unit_index; // 0x10
	long swarm_index; // 0x14
	long next_actor_index; // 0x18
	short team; // 0x1C
	char field_1E; // 0x1E
	char field_1F; // 0x1F
	long prevvehicle_squad_index; // 0x20
	short squad_adoption_timeout; // 0x24
	short squad_adoption_attempts; // 0x26
	short outside_map_ticks; // 0x28
	unsigned char __pad1[2]; // 0x2A
	long squad_index; // 0x2C
	short cell_index; // 0x30
	short spawn_point_index; // 0x32
	short field_34; // 0x34
	char field_36; // 0x36
	char field_37; // 0x37
	short field_38; // 0x38
	short field_3A; // 0x3A
	long spawn_time; // 0x3C
	long first_active_time; // 0x40
	long last_active_time; // 0x44
	long last_in_pvs_time; // 0x48
	long inactive_erase_time; // 0x4C
	long field_50; // 0x50
	long character_definition_index; // 0x54
	long equipment_use_index; // 0x58
	long first_prop_ref_index; // 0x5C
	float min_trackable_weight; // 0x60
	long clump_index; // 0x64
	long clump_next_actor_index; // 0x68
};
static_assert(sizeof(s_actor_metadata) == 108, "Invalid s_actor_metadata size");

struct s_invitation_data
{
	__int32 field_0; // 0x0
	__int32 field_4; // 0x4
	__int32 field_8; // 0x8
	char field_C; // 0xC
	char field_D; // 0xD
	char field_E; // 0xE
	char field_F; // 0xF
};
static_assert(sizeof(s_invitation_data) == 16, "Invalid s_invitation_data size");

struct s_actor_activity_data
{
	short field_0; // 0x0
	short field_2; // 0x2
	short field_4; // 0x4
	short field_6; // 0x6
	short field_8; // 0x8
	short field_A; // 0xA
};
static_assert(sizeof(s_actor_activity_data) == 12, "Invalid s_actor_activity_data size");

struct s_actor_patrol_state
{
	short squad_patrol_index; // 0x0
	short field_2; // 0x2
	short field_4; // 0x4
	short field_6; // 0x6
	short field_8; // 0x8
	short field_A; // 0xA
};
static_assert(sizeof(s_actor_patrol_state) == 12, "Invalid s_actor_patrol_state size");

#pragma pack(push, 4)
struct s_actor_position_data
{
	real_vector3d position; // 0x0
	real_vector3d origin; // 0xC
	__int32 field_18; // 0x18
	__int32 field_1C; // 0x1C
	__int32 field_20; // 0x20
	short location; // 0x24
	short field_26; // 0x26
	real_vector3d linear_velocity; // 0x28
};
#pragma pack(pop)
static_assert(sizeof(s_actor_position_data) == 52, "Invalid s_actor_position_data size");

struct s_actor_vehicle_data
{
	__int32 vehicle_index; // 0x0
	__int32 unknown_vehicle_index; // 0x4
	short seat_index; // 0x8
	short field_A; // 0xA
	short flags; // 0xC
	short reservation_index; // 0xE
	short state; // 0x10
	short unknown_timer2; // 0x12
	short unknown_timer3; // 0x14
	short timer; // 0x16
	short attach_delay_timer; // 0x18
	short field_1A; // 0x1A
	long field_1C; // 0x1C
	long field_20; // 0x20
	short field_24; // 0x24
	short field_26; // 0x26
	long field_28; // 0x28
	long field_2C; // 0x2C
};
static_assert(sizeof(s_actor_vehicle_data) == 48, "Invalid s_actor_vehicle_data size");

struct s_actor_state_data
{
	unsigned char behavior_state[512]; // 0x0
	unsigned short behavior_state_offsets[8]; // 0x200
	short leaf_layer; // 0x210
	unsigned char __pad0[2]; // 0x212
	s_invitation_data invitation[4]; // 0x214
	long behavior_check_timer[14]; // 0x254
	short mode; // 0x28C
	short combat_status; // 0x28E
	long combat_status_timer; // 0x290
	long field_294[10]; // 0x294
	long field_2BC; // 0x2BC
	char field_2C0; // 0x2C0
	char field_2C1; // 0x2C1
	bool arrived; // 0x2C2
	bool blind; // 0x2C3
	bool deaf; // 0x2C4
	char field_2C5; // 0x2C5
	char field_2C6; // 0x2C6
	char field_2C7; // 0x2C7
	char field_2C8; // 0x2C8
	char field_2C9; // 0x2C9
	char field_2CA; // 0x2CA
	char field_2CB; // 0x2CB
	char state_broken; // 0x2CC
	char field_2CD; // 0x2CD
	char field_2CE; // 0x2CE
	char field_2CF; // 0x2CF
	char field_2D0; // 0x2D0
	char field_2D1; // 0x2D1
	char field_2D2; // 0x2D2
	char field_2D3; // 0x2D3
	long field_2D4; // 0x2D4
	s_actor_patrol_state patrol; // 0x2D8
	s_actor_position_data perception; // 0x2E4
};
static_assert(sizeof(s_actor_state_data) == 792, "Invalid s_actor_state_data size");

struct s_actor_firing_position_data
{
	long field_0; // 0x0
	long field_4; // 0x4
	char field_8; // 0x8
	char field_9; // 0x9
	unsigned char __pad0[2]; // 0xA
	long field_C; // 0xC
	char field_10; // 0x10
	char search_areas_available; // 0x11
	char field_12; // 0x12
	char field_13; // 0x13
	short goal_status; // 0x14
	short field_16; // 0x16
	long dynamic_firing_set_index; // 0x18
	long dynamic_firing_set_support_object_index; // 0x1C
	short dynamic_firing_set_support_object_inaccessible_tick; // 0x20
	short field_22; // 0x22
	long field_24; // 0x24
	long field_28; // 0x28
	long field_2C; // 0x2C
	long field_30; // 0x30
	long field_34; // 0x34
	long field_38; // 0x38
	long key; // 0x3C
	long field_40; // 0x40
	long field_44; // 0x44
	long field_48; // 0x48
	long field_4C; // 0x4C
	long field_50; // 0x50
};
static_assert(sizeof(s_actor_firing_position_data) == 84, "Invalid s_actor_firing_position_data size");

struct s_actor_datum :
	public s_datum
{
	short pad_; // 0x2
	s_actor_metadata meta; // 0x4
	s_actor_state_data state; // 0x70
	char input[132]; // 0x388
	char obstacle_data[52]; // 0x40C
	char memory[96]; // 0x440
	char situation[12]; // 0x4A0
	char target[36]; // 0x4AC
	char stimuli[128]; // 0x4D0
	s_actor_activity_data activity; // 0x550
	s_actor_vehicle_data vehicle; // 0x55C
	char player[20]; // 0x58C
	s_actor_firing_position_data firing_positions; // 0x5A0
	char orders[208]; // 0x5F4
	char control[968]; // 0x6C4
	long cs_index1; // 0xA8C
	long cs_index2; // 0xA90
	long field_A94; // 0xA94
};
static_assert(sizeof(s_actor_datum) == 2712, "Invalid s_actor_datum size");

/* ---------- prototypes */

extern s_actor_datum *actor_get(long index);

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_AI_ACTOR_HPP__
