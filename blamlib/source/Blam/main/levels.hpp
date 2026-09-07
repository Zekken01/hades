#ifndef __BLAM_MAIN_LEVELS_HPP__
#define __BLAM_MAIN_LEVELS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/memory/data.hpp"
#include "ChatCommands/ChatCommandMap.hpp"

#include <functional>

/* ---------- forward declarations */

struct s_data_array;
struct s_datum;
struct s_level_datum;
struct s_level_insertion_datum;

/* ---------- constants */

enum
{
	k_maximum_multiplayer_levels = 100, // 0x0064 'd'
};

/* ---------- definitions */

struct s_level_datum :
	public s_datum
{
	unsigned short flags; // 0x2
	long map_id; // 0x4
	wchar_t name[32]; // 0x8
	wchar_t description[128]; // 0x48
	char file_path[256]; // 0x148
	char image_file_path[256]; // 0x248
	long field_348; // 0x348
	long field_34C; // 0x34C
	unsigned char teamCounts[16]; // 0x350
};
static_assert(sizeof(s_level_datum) == 864, "Invalid s_level_datum size");

struct s_level_insertion_datum :
	public s_datum
{
	public:
	struct s_names
	{
		wchar_t value[32]; // 0x0
	};
	// static_assert(sizeof(s_names) == 64, "Invalid s_names size");
	// Withheld: the type inventory does not describe this type, so its
	// padding could not be reconstructed.
	struct s_descriptions
	{
		wchar_t value[128]; // 0x0
	};
	// static_assert(sizeof(s_descriptions) == 256, "Invalid s_descriptions size");
	// Withheld: the type inventory does not describe this type, so its
	// padding could not be reconstructed.
	public:
	short index; // 0x2
	long map_id; // 0x4
	s_names names[9]; // 0x8
	s_descriptions descriptions[9]; // 0x248
	unsigned char field_48[9]; // 0xB48
	unsigned char __pad0[3]; // 0xB51
	long field_B54[9]; // 0xB54
	long field_B78[9]; // 0xB78
	unsigned char field_B9C[9]; // 0xB9C
	unsigned char __pad1[3]; // 0xBA5
};
// static_assert(sizeof(s_level_insertion_datum) == 2984, "Invalid s_level_insertion_datum size");
// Withheld: the type inventory does not describe this type, so its
// padding could not be reconstructed.

/* ---------- prototypes */

extern void levels_yield_until_enumerate_done();
extern bool const levels_find_map_by_name_internal(s_data_array *level_data, char const *name, s_level_datum *out_level);
extern bool levels_find_level_by_map_id_internal(s_data_array *level_array, long map_id, s_level_datum *out_level);
extern bool levels_find_level_by_map_id(long map_id, s_level_datum *out_level);
extern void levels_iterate_multiplayer_maps(std::function<void __cdecl(s_level_datum *)> func);
extern void levels_iterate_campaign_maps(std::function<void __cdecl(s_level_datum *)> func);
extern bool levels_find_by_path_internal(s_data_array *level_data, char const *path, s_level_datum *out_level);
extern bool levels_find_map_by_name(char const *name, s_level_datum *out_level);
extern bool levels_find_map_by_path(char const *path, s_level_datum *out_level);
extern void levels_close_all_multiplayer_in_directory(char const *directory);
extern void levels_close_map_internal(s_data_array *level_data, long map_id);
extern void levels_close_all_campaigns();
extern void levels_close_multiplayer_map(long map_id);
extern void levels_close_campaign_map(long map_id);
extern void levels_clear_and_enumerate_async();

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_MAIN_LEVELS_HPP__
