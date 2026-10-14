/* ---------- headers */

#include "Forge/ForgeUndo.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Forge/Magnets.hpp"
#include "Patches/CustomPackets.hpp"
#include "Utils/EventSink.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <atomic>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <functional>
#include <limits>
#include <list>
#include <memory>
#include <string>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

class CForgeUndoManager;
struct IForgeUndo;

namespace Utils {}
using namespace ::Utils;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern long (*const game_time_get)();  // hades: added for 0x108626A0

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

bool CForgeUndoManager::CanUndo() // 0x10862920
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CanUndo@CForgeUndoManager@@QAE_NXZ");
	// CForgeUndoManager *const this;

	return m_undoStack.size() > 0;
}

bool CForgeUndoManager::CanRedo() // 0x108628A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CanRedo@CForgeUndoManager@@QAE_NXZ");
	// CForgeUndoManager *const this;

	return m_redoStack.size() > 0;
}

void CForgeUndoManager::RequestUndo() // 0x10862EE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?RequestUndo@CForgeUndoManager@@QAEXXZ");
	// CForgeUndoManager *const this;

	m_undoRequested = true;
}

void CForgeUndoManager::RequestRedo() // 0x10862EB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?RequestRedo@CForgeUndoManager@@QAEXXZ");
	// CForgeUndoManager *const this;

	m_redoRequested = true;
}

void CForgeUndoManager::AddUndo(std::string const &summary, std::shared_ptr<IForgeUndo> undo) // 0x108626A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?AddUndo@CForgeUndoManager@@QAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$shared_ptr@UIForgeUndo@@@3@@Z");
	// static ...; // 0x1086281C
	// CForgeUndoManager *const this;
	// std::string const &summary;
	// std::shared_ptr<IForgeUndo> undo;
	// CForgeUndoManager::SUndoEntry entry;
	// function call : long (*const)()

	if (!m_recording)
		return;
	SUndoEntry entry;
	entry.summary = summary;
	entry.undo = undo;
	entry.time = game_time_get();
	if (m_undoing && !m_redoing)
	{
		if (m_redoStack.size() >= kUndoLimit)
			m_redoStack.pop_back();
		m_redoStack.push_front(entry);
	}
	else
	{
		if (m_undoStack.size() >= kUndoLimit)
			m_undoStack.pop_back();
		m_undoStack.push_front(entry);
	}
}

// mangled_x86(MANGLED_DEFAULT, "??0SUndoEntry@CForgeUndoManager@@QAE@ABU01@@Z"); no body to assert in
_inline CForgeUndoManager::SUndoEntry::SUndoEntry(CForgeUndoManager::SUndoEntry const &__that) = default; // 0x10862260

// mangled_x86(MANGLED_DEFAULT, "??0SUndoEntry@CForgeUndoManager@@QAE@XZ"); no body to assert in

// mangled_x86(MANGLED_DEFAULT, "??1SUndoEntry@CForgeUndoManager@@QAE@XZ"); no body to assert in
_inline CForgeUndoManager::SUndoEntry::~SUndoEntry() = default; // 0x10862540

void CForgeUndoManager::Update() // 0x10862F70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Update@CForgeUndoManager@@QAEXXZ");
	// CForgeUndoManager *const this;

	if (m_undoRequested)
	{
		m_undoRequested = false;
		PerformUndo();
	}

	if (m_redoRequested)
	{
		m_redoRequested = false;
		PerformRedo();
	}
}

void CForgeUndoManager::PerformUndo() // 0x10862D50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?PerformUndo@CForgeUndoManager@@AAEXXZ");
	// static ...; // 0x10862E64
	// static ...; // 0x10862E58
	// static ...; // 0x10862E50
	// CForgeUndoManager *const this;
		// CForgeUndoManager::SUndoEntry entry;
	// function call : void ()

	if (m_undoStack.size() > 0)
	{
		SUndoEntry entry = static_cast<SUndoEntry const &>(m_undoStack.front());
		m_undoing = true;
		entry.undo->Undo();
		m_undoing = false;
		m_undoStack.pop_front();
		completedEvent.PostEvent();
	}
}

void CForgeUndoManager::PerformRedo() // 0x10862BF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?PerformRedo@CForgeUndoManager@@AAEXXZ");
	// static ...; // 0x10862D04
	// static ...; // 0x10862CF8
	// static ...; // 0x10862CF0
	// CForgeUndoManager *const this;
		// CForgeUndoManager::SUndoEntry entry;
	// function call : void ()

	if (m_redoStack.size() > 0)
	{
		SUndoEntry entry = static_cast<SUndoEntry const &>(m_redoStack.front());
		m_redoing = true;
		entry.undo->Undo();
		m_redoing = false;
		m_redoStack.pop_front();
		completedEvent.PostEvent();
	}
}

void CForgeUndoManager::Clear() // 0x108629A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Clear@CForgeUndoManager@@QAEXXZ");
	// CForgeUndoManager *const this;

	m_undoRequested = false;
	m_redoRequested = false;

	while (m_undoStack.size() > 0)
	{
		m_undoStack.pop_front();
	}

	while (m_redoStack.size() > 0)
	{
		m_redoStack.pop_front();
	}
}

bool CForgeUndoManager::IsRecording() const // 0x10862BC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?IsRecording@CForgeUndoManager@@QBE_NXZ");
	// CForgeUndoManager const *const this;

	return m_recording;
}

void CForgeUndoManager::StopRecording() // 0x10862F40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?StopRecording@CForgeUndoManager@@QAEXXZ");
	// CForgeUndoManager *const this;

	m_recording = false;
}

void CForgeUndoManager::StartRecording() // 0x10862F10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?StartRecording@CForgeUndoManager@@QAEXXZ");
	// CForgeUndoManager *const this;

	m_recording = true;
}

std::string CForgeUndoManager::GetNextUndoSummary() const // 0x10862B00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetNextUndoSummary@CForgeUndoManager@@QBE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
	// CForgeUndoManager const *const this;

	#line 231 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Forge\\ForgeUndo.cpp"
	assert(m_undoStack.size() > 0);
	#line 237 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Forge\\ForgeUndo.cpp"
	return m_undoStack.front().summary;
}

std::string CForgeUndoManager::GetNextRedoSummary() const // 0x10862A40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetNextRedoSummary@CForgeUndoManager@@QBE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
	// CForgeUndoManager const *const this;

	#line 242 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Forge\\ForgeUndo.cpp"
	assert(m_redoStack.size() > 0);
	#line 248 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Forge\\ForgeUndo.cpp"
	return m_redoStack.front().summary;
}

/* ---------- private code */
