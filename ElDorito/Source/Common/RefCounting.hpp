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

extern Mod *_sub_10791830(Ref<Mod> const *const);
_inline Ref<Mod>::operator Mod *() const // 0x10791830
{
	mangled_x86(MANGLED_TODO, "??B?$Ref@VMod@@@@QBEPAVMod@@XZ");
	// Ref<Mod> const *const this;
	todo("implement");
	Mod * __result = _sub_10791830((Ref<Mod> const *)this);
	return __result;
}

extern IMod *_sub_1068DF20(Ref<IMod> const *const);
_inline Ref<IMod>::operator IMod *() const // 0x1068DF20
{
	mangled_x86(MANGLED_TODO, "??B?$Ref@VIMod@@@@QBEPAVIMod@@XZ");
	// Ref<IMod> const *const this;
	todo("implement");
	IMod * __result = _sub_1068DF20((Ref<IMod> const *)this);
	return __result;
}

/* ---------- private code */

#endif // __COMMON_REFCOUNTING_HPP__
