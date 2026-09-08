#ifndef __COMMON_REFCOUNTING_HPP__
#define __COMMON_REFCOUNTING_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "mods/new/IModManager.hpp"
#include "mods/new/Mod.hpp"

/* ---------- forward declarations */

class IMod;
class Mod;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

_inline Ref<Mod>::operator Mod *() const // 0x10791830
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$Ref@VMod@@@@QBEPAVMod@@XZ");
	// Ref<Mod> const *const this;

	return p;
}

_inline Ref<IMod>::operator IMod *() const // 0x1068DF20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??B?$Ref@VIMod@@@@QBEPAVIMod@@XZ");
	// Ref<IMod> const *const this;

	return p;
}

/* ---------- private code */

#endif // __COMMON_REFCOUNTING_HPP__
