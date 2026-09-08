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
	virtual _inline ~IGameSystem();
	virtual _inline void Initialize();
	virtual _inline void InitializeForNewMap();
	virtual _inline void DisposeFromOldMap();
	virtual _inline void Dispose();
	virtual _inline void Update();
	IGameSystem(IGameSystem const &); /* compiler_generated() */
	_inline IGameSystem(); /* compiler_generated() */
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

_inline IGameSystem::~IGameSystem() // 0x107996F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??1IGameSystem@@UAE@XZ");
	// IGameSystem *const this;
}

_inline void IGameSystem::Initialize() // 0x10798210
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Initialize@IGameSystem@@UAEXXZ");
	// IGameSystem *const this;
}

_inline void IGameSystem::InitializeForNewMap() // 0x10798230
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?InitializeForNewMap@IGameSystem@@UAEXXZ");
	// IGameSystem *const this;
}

_inline void IGameSystem::DisposeFromOldMap() // 0x108CEC20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?DisposeFromOldMap@IGameSystem@@UAEXXZ");
	// IGameSystem *const this;
}

_inline void IGameSystem::Dispose() // 0x10798250
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Dispose@IGameSystem@@UAEXXZ");
	// IGameSystem *const this;
}

_inline void IGameSystem::Update() // 0x10798270
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Update@IGameSystem@@UAEXXZ");
	// IGameSystem *const this;
}

/* ---------- private code */

#endif // __PATCHES_GAMEPATCHES_HPP__
