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

_extern void _sub_107996F0(IGameSystem *const);
_inline IGameSystem::~IGameSystem() // 0x107996F0
{
	mangled_x86(MANGLED_TODO, "??1IGameSystem@@UAE@XZ");
	// IGameSystem *const this;
	todo("implement");
	_sub_107996F0(this);
}

_extern void _sub_10798210(IGameSystem *const);
_inline void IGameSystem::Initialize() // 0x10798210
{
	mangled_x86(MANGLED_TODO, "?Initialize@IGameSystem@@UAEXXZ");
	// IGameSystem *const this;
	todo("implement");
	_sub_10798210(this);
}

_extern void _sub_10798230(IGameSystem *const);
_inline void IGameSystem::InitializeForNewMap() // 0x10798230
{
	mangled_x86(MANGLED_TODO, "?InitializeForNewMap@IGameSystem@@UAEXXZ");
	// IGameSystem *const this;
	todo("implement");
	_sub_10798230(this);
}

_extern void _sub_108CEC20(IGameSystem *const);
_inline void IGameSystem::DisposeFromOldMap() // 0x108CEC20
{
	mangled_x86(MANGLED_TODO, "?DisposeFromOldMap@IGameSystem@@UAEXXZ");
	// IGameSystem *const this;
	todo("implement");
	_sub_108CEC20(this);
}

_extern void _sub_10798250(IGameSystem *const);
_inline void IGameSystem::Dispose() // 0x10798250
{
	mangled_x86(MANGLED_TODO, "?Dispose@IGameSystem@@UAEXXZ");
	// IGameSystem *const this;
	todo("implement");
	_sub_10798250(this);
}

_extern void _sub_10798270(IGameSystem *const);
_inline void IGameSystem::Update() // 0x10798270
{
	mangled_x86(MANGLED_TODO, "?Update@IGameSystem@@UAEXXZ");
	// IGameSystem *const this;
	todo("implement");
	_sub_10798270(this);
}

/* ---------- private code */

#endif // __PATCHES_GAMEPATCHES_HPP__
