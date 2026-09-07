#ifndef __BLAM_GAME_CAMPAIGN_CAMPAIGN_METAGAME_HPP__
#define __BLAM_GAME_CAMPAIGN_CAMPAIGN_METAGAME_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

/* ---------- forward declarations */

struct s_campaign_metagame_runtime_globals;
struct s_metagame_player_data;

/* ---------- constants */

enum e_campaign_metagame_bucket_flags
{
	_campaign_metagame_bucket_must_have_active_seats_bit = 0,
	k_number_of_campaign_metagame_bucket_flags,
};

enum e_campaign_metagame_unit_type
{
	_campaign_metagame_unit_type_brute = 0,
	_campaign_metagame_unit_type_grunt,
	_campaign_metagame_unit_type_jackal,
	_campaign_metagame_unit_type_marine,
	_campaign_metagame_unit_type_bugger,
	_campaign_metagame_unit_type_hunter,
	_campaign_metagame_unit_type_flood_infection,
	_campaign_metagame_unit_type_flood_carrier,
	_campaign_metagame_unit_type_flood_combat,
	_campaign_metagame_unit_type_flood_pureform,
	_campaign_metagame_unit_type_sentinel,
	_campaign_metagame_unit_type_elite,
	_campaign_metagame_unit_type_turret,
	_campaign_metagame_unit_type_mongoose,
	_campaign_metagame_unit_type_warthog,
	_campaign_metagame_unit_type_scorpion,
	_campaign_metagame_unit_type_hornet,
	_campaign_metagame_unit_type_pelican,
	_campaign_metagame_unit_type_shade,
	_campaign_metagame_unit_type_watchtower,
	_campaign_metagame_unit_type_ghost,
	_campaign_metagame_unit_type_chopper,
	_campaign_metagame_unit_type_mauler,
	_campaign_metagame_unit_type_wraith,
	_campaign_metagame_unit_type_banshee,
	_campaign_metagame_unit_type_phantom,
	_campaign_metagame_unit_type_scarab,
	_campaign_metagame_unit_type_guntower,
	_campaign_metagame_unit_type_engineer,
	_campaign_metagame_unit_type_engineer_recharge_station,
	k_number_of_campaign_metagame_unit_types,
};

enum e_campaign_metagame_unit_class
{
	_campaign_metagame_unit_class_infantry = 0,
	_campaign_metagame_unit_class_leader,
	_campaign_metagame_unit_class_hero,
	_campaign_metagame_unit_class_specialist,
	_campaign_metagame_unit_class_light_vehicle,
	_campaign_metagame_unit_class_heavy_vehicle,
	_campaign_metagame_unit_class_giant_vehicle,
	_campaign_metagame_unit_class_standard_vehicle,
	k_number_of_campaign_metagame_unit_classes,
};

enum e_campaign_metagame_scoring_option
{
	_campaign_metagame_scoring_option_off = 0,
	_campaign_metagame_scoring_option_team,
	_campaign_metagame_scoring_option_free_for_all,
	k_number_of_campaign_metagame_scoring_options,
};

/* ---------- definitions */

struct s_metagame_player_data
{
	unsigned long unknown0; // 0x0
	unsigned long unknown4; // 0x4
	char flags; // 0x8
	unsigned char unknown9[3]; // 0x9
	unsigned long unknownC; // 0xC
	long campaign_points; // 0x10
	unsigned long unknown14; // 0x14
	long campaign_style; // 0x18
	float *unknown1C; // 0x1C
	unsigned short unknown20[2]; // 0x20
	unsigned long secondary_skulls_count; // 0x24
	float *unknown28; // 0x28
	unsigned short unknown2C[234]; // 0x2C
	unsigned short medals[43]; // 0x200
	unsigned short unknown256[64]; // 0x256
	unsigned char unknown2D6[2]; // 0x2D6
	long campaign_friendlyfire; // 0x2D8
	unsigned long unknown2DC[5]; // 0x2DC
	unsigned long unknown2F0; // 0x2F0
	unsigned long unknown2F4; // 0x2F4
	long biggest_kill_points; // 0x2F8
	unsigned char unknown2FC[12]; // 0x2FC
	short campaign_infantry; // 0x308
	short campaign_leader; // 0x30A
	short campaign_hero; // 0x30C
	short campaign_specialist; // 0x30E
	short campaign_light; // 0x310
	short campaign_heavy; // 0x312
	short campaign_giant; // 0x314
	short campaign_standard; // 0x316
	long campaign_kills; // 0x318
	long campaign_medals; // 0x31C
	unsigned char unknown320[16]; // 0x320
};
static_assert(sizeof(s_metagame_player_data) == 816, "Invalid s_metagame_player_data size");

struct s_campaign_metagame_runtime_globals
{
	s_metagame_player_data players[4]; // 0x0
	unsigned char unknownCC0[63556]; // 0xCC0
	unsigned long unknown10504; // 0x10504
	unsigned long unknown10508[10000]; // 0x10508
	float unknown1A148; // 0x1A148
	unsigned long dword_flags; // 0x1A14C
	float multiplier; // 0x1A150
	float unknownCCC; // 0x1A154
};
static_assert(sizeof(s_campaign_metagame_runtime_globals) == 106840, "Invalid s_campaign_metagame_runtime_globals size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_GAME_CAMPAIGN_CAMPAIGN_METAGAME_HPP__
