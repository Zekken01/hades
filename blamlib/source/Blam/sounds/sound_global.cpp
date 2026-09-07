/* ---------- headers */

#include "Blam/sounds/sound_global.hpp"
#include "hades/hades.h"

#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/math/sound_math.hpp"
#include "Blam/memory/tls.hpp"
#include "Blam/sounds/sound_memory.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_groups.hpp"

/* ---------- forward declarations */

struct c_playback_controller;
struct looping_sound_datum;
struct s_sound_effect_datum;
struct s_sound_manager_globals;
struct s_sound_source_datum;
struct s_sound_tracker_datum;
struct s_xbox_sound_datum;
struct sound_channel_datum;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

extern c_data_array<s_xbox_sound_datum> **g_xbox_sounds; // 0x1135A218
extern c_data_array<c_playback_controller> **g_sound_playback_controllers; // 0x1135A21C
extern c_data_array<s_sound_source_datum> **g_sound_sources; // 0x1135A220
extern c_data_array<looping_sound_datum> **g_looping_sounds; // 0x1135A224
extern c_data_array<s_sound_effect_datum> **g_sound_effects; // 0x1135A228
extern c_data_array<s_sound_tracker_datum> **g_sound_trackers; // 0x1135A22C
extern sound_channel_datum **g_sound_channels; // 0x1135A230
extern s_sound_manager_globals **g_sound_manager_globals; // 0x1135A234
extern long *g_encodings; // 0x1135A238
extern long *g_looping_sound_references; // 0x1135A23C
extern long g_looping_sound_next_sound[7]; // 0x1135A240
extern long g_looping_sound_alternate_next_sound[7]; // 0x1135A25C
extern long g_looping_sound_sound_offset[7]; // 0x1135A278
extern bool (*sound_is_active)(); // 0x1135A294

/* ---------- private variables */

/* ---------- public code */

/* ---------- private code */
