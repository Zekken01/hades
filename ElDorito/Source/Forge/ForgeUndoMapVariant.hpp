#ifndef __FORGE_FORGEUNDOMAPVARIANT_HPP__
#define __FORGE_FORGEUNDOMAPVARIANT_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Forge/ForgeUndo.hpp"
#include "mods/map_variant_loader.hpp"

#include <memory>
#include <string>

/* ---------- forward declarations */

struct CForgeUndoMapVariant;
struct IForgeUndo;
struct s_map_variant;

/* ---------- constants */

/* ---------- definitions */

struct CForgeUndoMapVariant :
	public IForgeUndo
{
	CForgeUndoMapVariant(CForgeUndoMapVariant &); /* compiler_generated() */
	CForgeUndoMapVariant(CForgeUndoMapVariant const &); /* compiler_generated() */
	CForgeUndoMapVariant(std::string const &summary, s_map_variant const &mapVariant);
private:
	std::string m_summary; // 0x4
	s_map_variant m_storedMapVariant; // 0x20
	virtual void Undo();
	virtual _inline EForgeUndoType GetType();
public:
	virtual _inline ~CForgeUndoMapVariant() = default; /* compiler_generated() */ // 0x10864C10
	CForgeUndoMapVariant &operator=(CForgeUndoMapVariant &); /* compiler_generated() */
	CForgeUndoMapVariant &operator=(CForgeUndoMapVariant const &); /* compiler_generated() */
};
static_assert(sizeof(CForgeUndoMapVariant) == 57520, "Invalid CForgeUndoMapVariant size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

_inline EForgeUndoType CForgeUndoMapVariant::GetType() // 0x10864DE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetType@CForgeUndoMapVariant@@EAE?AW4EForgeUndoType@@XZ");
	// CForgeUndoMapVariant *const this;

	return UndoMapVariant;
}

/* ---------- private code */

#endif // __FORGE_FORGEUNDOMAPVARIANT_HPP__
