#ifndef __MODS_CACHE_FILE_TAG_OPTIMIZATION_HPP__
#define __MODS_CACHE_FILE_TAG_OPTIMIZATION_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cache/cache_files.hpp"
#include "Blam/game/engine/game_engine.hpp"
#include "Patches/Events.hpp"

/* ---------- forward declarations */

struct s_cache_tag_instance;
struct s_multiplayer_event_response_definition;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern void optimize_scenario(s_cache_tag_instance *tag_instance);
extern void optimize_game_engine_event_response(s_multiplayer_event_response_definition const *response, e_game_engine_type game_engine_type, c_static_bit_vector<65535> *dependencies_to_null);
extern void optimize_object(long runtime_tag_index, s_cache_tag_instance *tag_instance);
extern void optimize_model(long runtime_tag_index, s_cache_tag_instance *tag_instance);
extern void optimize_render_model(long runtime_tag_index, s_cache_tag_instance *tag_instance);
extern void cache_file_tags_optimize(long runtime_tag_index, s_cache_tag_instance *tag_instance);

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __MODS_CACHE_FILE_TAG_OPTIMIZATION_HPP__
