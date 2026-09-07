#ifndef __MODS_FONT_PACKAGE_HPP__
#define __MODS_FONT_PACKAGE_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/async/async_definitions.hpp"
#include "Blam/game/game_state.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/networking/session/network_session_membership.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "mods/map_variant_loader.hpp"
#include "mods/new/IModManager.hpp"

/* ---------- forward declarations */

class c_mod_package;
struct c_game_variant;
struct s_font_loading_state;
struct s_font_package_cache_entry;
struct s_font_package_file_header;
struct s_game_machine_options;
struct s_game_options;
struct s_game_player_options;
struct s_map_variant;

/* ---------- constants */

/* ---------- definitions */

struct s_game_options
{
	c_enum<enum e_game_mode,long> game_mode; // 0x0
	unsigned char game_simulation; // 0x4
	unsigned char network_type; // 0x5
	short tick_rate; // 0x6
	unsigned long long game_id; // 0x8
	unsigned long random_seed; // 0x10
	long language_id; // 0x14
	long determinism_version; // 0x18
	long campaign_id; // 0x1C
	long map_id; // 0x20
	char scenario_path[256]; // 0x24
	long field_124; // 0x124
	short zoneset_group_index; // 0x128
	unsigned char field_12A[6]; // 0x12A
	unsigned short game_playback; // 0x130
	bool record_saved_film; // 0x132
	unsigned char field_133; // 0x133
	long playback_start_in_ticks; // 0x134
	long playback_length_in_ticks; // 0x138
	short campaign_difficulty; // 0x13C
	short campaign_insertion_index; // 0x13E
	short campaign_metagame_scoring; // 0x140
	bool campaign_metagame_enabled; // 0x142
	bool game_is_survival; // 0x143
	unsigned char field_144; // 0x144
	unsigned char field_145; // 0x145
	unsigned char campaign_arguments[120]; // 0x146
	unsigned char __pad0[2]; // 0x1BE
	unsigned char game_progression[128]; // 0x1C0
	unsigned long campaign_skulls_primary; // 0x240
	unsigned long campaign_skulls_secondary; // 0x244
	char field_248[136]; // 0x248
	char field_2D0[92]; // 0x2D0
	c_game_variant game_variant; // 0x32C
	s_map_variant map_variant; // 0x590
	s_game_machine_options machine_options; // 0xE620
	s_static_array<s_game_player_options,16> player_options; // 0xE748
	s_game_options(s_game_options &); /* compiler_generated() */
	s_game_options(s_game_options const &); /* compiler_generated() */
	_inline s_game_options(); /* compiler_generated() */
	s_game_options &operator=(s_game_options &); /* compiler_generated() */
	s_game_options &operator=(s_game_options const &); /* compiler_generated() */
};
static_assert(sizeof(s_game_options) == 150344, "Invalid s_game_options size");

/* ---------- prototypes */

extern void font_package_do_work(bool blocking, s_font_package_cache_entry *entry);
extern void font_package_cache_flush();
extern void font_package_idle();
extern bool font_package_begin_load_package(char const *filename);
extern bool fonts_begin_loading_internal(bool blocking);
extern void font_package_set_defaults();
extern bool font_load_from_file_blocking(s_font_loading_state *loading_state, unsigned long size, void *buffer, s_font_package_file_header **out_header);
extern bool font_load_from_mod_package_blocking(c_mod_package *mod_package, unsigned long size, void *buffer, s_font_package_file_header **out_header);
extern e_async_completion font_load_callback(void *data);
extern void font_load(s_font_loading_state *loading_state, long font_index, char const *filename, bool blocking);
extern bool font_initialize_for_new_map(s_game_options *options);

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __MODS_FONT_PACKAGE_HPP__
