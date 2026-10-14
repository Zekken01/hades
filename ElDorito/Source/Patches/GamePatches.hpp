#ifndef __PATCHES_GAMEPATCHES_HPP__
#define __PATCHES_GAMEPATCHES_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Forge/Magnets.hpp"
#include "Forge/Reforge.hpp"
#include "Forge/SelectionRenderer.hpp"
#include "Patches/Audio.hpp"

/* ---------- forward declarations */

struct IGameSystem;

/* ---------- constants */

/* ---------- definitions */

struct IGameSystem
{
	// mangled_x86(MANGLED_DEFAULT, "??1IGameSystem@@UAE@XZ"); defaulted on its declaration, which skips the vfptr store
	virtual _inline ~IGameSystem() = default; // 0x107996F0
	virtual _inline void Initialize();
	virtual _inline void InitializeForNewMap();
	virtual _inline void DisposeFromOldMap();
	virtual _inline void Dispose();
	virtual _inline void Update();
	IGameSystem(IGameSystem const &); /* compiler_generated() */
	_inline IGameSystem() = default; /* compiler_generated() */
	IGameSystem &operator=(IGameSystem const &); /* compiler_generated() */
};
static_assert(sizeof(IGameSystem) == 4, "Invalid IGameSystem size");

/* ---------- prototypes */

namespace Patches
{
	namespace Game
	{
		extern void ApplyAll();
		extern void RegisterGameSystem(IGameSystem *system);
	}
}

/* ---------- globals */

/* ---------- public code */













inline void IGameSystem::DisposeFromOldMap() // 0x108CEC20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?DisposeFromOldMap@IGameSystem@@UAEXXZ");
	// IGameSystem *const this;
}













/* ---------- private code */

#endif // __PATCHES_GAMEPATCHES_HPP__
