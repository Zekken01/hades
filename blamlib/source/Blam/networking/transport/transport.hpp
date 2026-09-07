#ifndef __BLAM_NETWORKING_TRANSPORT_TRANSPORT_HPP__
#define __BLAM_NETWORKING_TRANSPORT_TRANSPORT_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Forge/ForgeUndo.hpp"

/* ---------- forward declarations */

struct s_transport_address;
struct s_transport_secure_key;

/* ---------- constants */

/* ---------- definitions */

struct s_transport_secure_key
{
	unsigned char data[16]; // 0x0
};
static_assert(sizeof(s_transport_secure_key) == 16, "Invalid s_transport_secure_key size");

struct s_transport_address
{
	public:
	union s_address
	{
		unsigned long ipv4; // 0x0
		unsigned char data[16]; // 0x0
	};
	// static_assert(sizeof(s_address) == 16, "Invalid s_address size");
	// Withheld: the type inventory does not describe this type, so its
	// padding could not be reconstructed.
	public:
	union
	{
		unsigned long ipv4; // 0x0
		unsigned char data[16]; // 0x0
	} address; // 0x0
	unsigned short port; // 0x10
	unsigned short address_size; // 0x12
};
// static_assert(sizeof(s_transport_address) == 20, "Invalid s_transport_address size");
// The layout above is the PDB's member list without its padding, so the
// size assertion is withheld: it would fail on alignment alone.

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_NETWORKING_TRANSPORT_TRANSPORT_HPP__
