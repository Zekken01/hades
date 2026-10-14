#ifndef __FORGE_FORGEUNDO_HPP__
#define __FORGE_FORGEUNDO_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Audio/AudioDeviceManager.hpp"
#include "Forge/Magnets.hpp"
#include "Patches/CustomPackets.hpp"
#include "Patches/PlayerPropertiesExtension.hpp"

#include <list>
#include <memory>
#include <string>

/* ---------- forward declarations */

class CForgeUndoManager;
struct IForgeUndo;

/* ---------- constants */

/* ---------- definitions */

struct IForgeUndo
{
	virtual _inline ~IForgeUndo() = default; // 0x10864C70
	virtual EForgeUndoType GetType() = 0;
	virtual void Undo() = 0;
	IForgeUndo(IForgeUndo const &); /* compiler_generated() */
	_inline IForgeUndo() = default; /* compiler_generated() */
	IForgeUndo &operator=(IForgeUndo const &); /* compiler_generated() */
};
static_assert(sizeof(IForgeUndo) == 4, "Invalid IForgeUndo size");

#pragma pack(push, 4)
class CForgeUndoManager :
	public Utils::Singleton<CForgeUndoManager>
{
private:
	public:
	struct SUndoEntry
	{
		long time; // 0x0
		std::string summary; // 0x4
		std::shared_ptr<IForgeUndo> undo; // 0x20
		SUndoEntry(SUndoEntry &); /* compiler_generated() */
		_inline SUndoEntry(SUndoEntry const &__that); /* compiler_generated() */
		_inline SUndoEntry() = default; /* compiler_generated() */
		_inline ~SUndoEntry(); /* compiler_generated() */
		SUndoEntry &operator=(SUndoEntry &); /* compiler_generated() */
		SUndoEntry &operator=(SUndoEntry const &); /* compiler_generated() */
	};
	static_assert(sizeof(SUndoEntry) == 40, "Invalid SUndoEntry size");
	private:
	static unsigned __int32 const kUndoLimit = 16;  // hades: value from AddUndo (cmp eax, 0x10)
public:
	bool CanUndo();
	bool CanRedo();
	void RequestUndo();
	void RequestRedo();
	void AddUndo(std::string const &summary, std::shared_ptr<IForgeUndo> undo);
	void Update();
	void Clear();
	bool IsRecording() const;
	void StopRecording();
	void StartRecording();
	std::string GetNextUndoSummary() const;
	std::string GetNextRedoSummary() const;
	CEventSink<> completedEvent; // 0x0
private:
	bool m_undoRequested = false; // 0x14
	bool m_redoRequested = false; // 0x15
	bool m_recording = false; // 0x16
	bool m_undoing = false; // 0x17
	bool m_redoing = false; // 0x18
	std::list<SUndoEntry> m_undoStack; // 0x1C
	std::list<SUndoEntry> m_redoStack; // 0x28
	void PerformUndo();
	void PerformRedo();
public:
	_inline CForgeUndoManager() = default; /* compiler_generated() - defaulted on its
	    first declaration, so it is NOT user-provided and `new CForgeUndoManager()`
	    zero-initializes before constructing, as the original does. */
	~CForgeUndoManager() = default; /* compiler_generated() */
};
#pragma pack(pop)
static_assert(sizeof(CForgeUndoManager) == 52, "Invalid CForgeUndoManager size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __FORGE_FORGEUNDO_HPP__
