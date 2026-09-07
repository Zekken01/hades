#ifndef __BLAM_ANIMATIONS_ANIMATION_MANAGER_HPP__
#define __BLAM_ANIMATIONS_ANIMATION_MANAGER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/animations/animation_definitions.hpp"
#include "Blam/animations/mixing_board/channels/animation_channel.hpp"
#include "Blam/tag_files/tag_groups.hpp"

/* ---------- forward declarations */

class c_animation_id;
struct c_animation_manager;
class c_model_animation;
struct s_animation_graph_sound_reference;
struct s_animation_sync_action;
struct s_tag_reference;

/* ---------- constants */

/* ---------- definitions */

class c_model_animation
{
public:
	short get_sound_reference_index();
};
static_assert(sizeof(c_model_animation) == 1, "Invalid c_model_animation size");

#pragma pack(push, 4)
struct s_animation_graph_sound_reference
{
	s_tag_reference sound; // 0x0
	short flags; // 0x10
	unsigned char __pad0[2]; // 0x12
};
#pragma pack(pop)
static_assert(sizeof(s_animation_graph_sound_reference) == 20, "Invalid s_animation_graph_sound_reference size");

struct c_animation_manager
{
public:
	c_animation_manager();
	~c_animation_manager();
	bool reset_graph(long, long, bool);
	c_model_animation *find_impulse_or_state_animation(long, long, long);
	c_animation_id *find_impulse_or_state_animation_id(c_animation_id *, long, long, long);
	s_animation_graph_sound_reference *get_sound_reference(long);
	static s_animation_sync_action *(*const find_sync_action)(c_animation_manager const *, unsigned long, unsigned long, unsigned long);
private:
	unsigned char m_data[192]; // 0x0
};
static_assert(sizeof(c_animation_manager) == 192, "Invalid c_animation_manager size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_ANIMATIONS_ANIMATION_MANAGER_HPP__
