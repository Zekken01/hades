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
	return m_undoStack.size() > 0;
}

bool CForgeUndoManager::CanRedo() // 0x108628A0
{
	return m_redoStack.size() > 0;
}

void CForgeUndoManager::RequestUndo() // 0x10862EE0
{
	m_undoRequested = true;
}

void CForgeUndoManager::RequestRedo() // 0x10862EB0
{
	m_redoRequested = true;
}

void CForgeUndoManager::AddUndo(std::string const &summary, std::shared_ptr<IForgeUndo> undo) // 0x108626A0
{
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

_inline CForgeUndoManager::SUndoEntry::SUndoEntry(CForgeUndoManager::SUndoEntry const &__that) = default; // 0x10862260

_inline CForgeUndoManager::SUndoEntry::~SUndoEntry() = default; // 0x10862540

void CForgeUndoManager::Update() // 0x10862F70
{
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
	return m_recording;
}

void CForgeUndoManager::StopRecording() // 0x10862F40
{
	m_recording = false;
}

void CForgeUndoManager::StartRecording() // 0x10862F10
{
	m_recording = true;
}

#line 229
std::string CForgeUndoManager::GetNextUndoSummary() const // 0x10862B00
{
#line 233

	#line 231 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Forge\\ForgeUndo.cpp"
	assert(m_undoStack.size() > 0);
	#line 237 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Forge\\ForgeUndo.cpp"
	return m_undoStack.front().summary;
}

std::string CForgeUndoManager::GetNextRedoSummary() const // 0x10862A40
{
#line 244

	#line 242 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Forge\\ForgeUndo.cpp"
	assert(m_redoStack.size() > 0);
	#line 248 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Forge\\ForgeUndo.cpp"
	return m_redoStack.front().summary;
}

/* ---------- private code */
