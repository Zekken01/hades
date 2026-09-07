#ifndef __BLAM_NETWORKING_TRANSPORT_TRANSPORT_SHIM_HPP__
#define __BLAM_NETWORKING_TRANSPORT_TRANSPORT_SHIM_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

/* ---------- forward declarations */

struct s_xnet_shim_table_row;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 1)
struct s_xnet_shim_table_row
{
	char valid; // 0x0
	unsigned char usable_address[16]; // 0x1
	unsigned char xnaddr[16]; // 0x11
	unsigned char xnkid[16]; // 0x21
};
#pragma pack(pop)
static_assert(sizeof(s_xnet_shim_table_row) == 49, "Invalid s_xnet_shim_table_row size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_NETWORKING_TRANSPORT_TRANSPORT_SHIM_HPP__
