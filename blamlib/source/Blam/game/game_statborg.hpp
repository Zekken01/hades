#ifndef __BLAM_GAME_GAME_STATBORG_HPP__
#define __BLAM_GAME_GAME_STATBORG_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

/* ---------- forward declarations */

struct c_game_statborg;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
struct c_game_statborg
{
	public:
#pragma pack(push, 2)
	struct s_team_row
	{
		short score; // 0x0
		short total_score; // 0x2
		short kills; // 0x4
		short deaths; // 0x6
		short assists; // 0x8
		unsigned char Unknown0[16]; // 0xA
	};
#pragma pack(pop)
	static_assert(sizeof(s_team_row) == 26, "Invalid s_team_row size");
#pragma pack(push, 4)
	struct s_player_row
	{
		short score; // 0x0
		short total_score; // 0x2
		short kills; // 0x4
		short deaths; // 0x6
		short suicides; // 0x8
		short betrayals; // 0xA
		short assists; // 0xC
		short unknownE[5]; // 0xE
		short consecutive_kills; // 0x18
		short highest_spree; // 0x1A
		short unknown1C[12]; // 0x1C
	};
#pragma pack(pop)
	static_assert(sizeof(s_player_row) == 52, "Invalid s_player_row size");
	public:
	long player_count; // 0x0
	s_player_row players[16]; // 0x4
	s_team_row teams[8]; // 0x344
	unsigned char __pad0[12]; // 0x414
	bool finalized; // 0x420
};
#pragma pack(pop)
static_assert(sizeof(c_game_statborg) == 1060, "Invalid c_game_statborg size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_GAME_GAME_STATBORG_HPP__
