#ifndef __BLAM_INTERFACE_USER_INTERFACE_MAPS_HPP__
#define __BLAM_INTERFACE_USER_INTERFACE_MAPS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/items/equipment_definitions.hpp"
#include "Blam/tag_files/tag_groups.hpp"

/* ---------- forward declarations */

struct s_tag_reference;
struct s_user_interface_map_image;
struct s_user_interface_map_list;

/* ---------- constants */

/* ---------- definitions */

struct s_user_interface_map_image
{
	long map_id; // 0x0
	s_tag_reference bitmap; // 0x4
	c_tag_block<s_tag_reference> loading_screens; // 0x14
};
static_assert(sizeof(s_user_interface_map_image) == 32, "Invalid s_user_interface_map_image size");

#pragma pack(push, 4)
struct s_user_interface_map_list
{
	c_tag_block<s_user_interface_map_image> map_images; // 0x0
	s_tag_reference default_map_image; // 0xC
	s_tag_reference default_loading_screen; // 0x1C
};
#pragma pack(pop)
static_assert(sizeof(s_user_interface_map_list) == 44, "Invalid s_user_interface_map_list size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_INTERFACE_USER_INTERFACE_MAPS_HPP__
