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

_extern void _sub_108626A0(CForgeUndoManager *const, std::string const &, std::shared_ptr<IForgeUndo>);
void CForgeUndoManager::AddUndo(std::string const &summary, std::shared_ptr<IForgeUndo> undo) // 0x108626A0
{
	mangled_x86(MANGLED_TODO, "?AddUndo@CForgeUndoManager@@QAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$shared_ptr@UIForgeUndo@@@3@@Z");
	// static ...; // 0x1086281C
	// CForgeUndoManager *const this;
	// std::string const &summary;
	// std::shared_ptr<IForgeUndo> undo;
	// CForgeUndoManager::SUndoEntry entry;
	// function call : long (*const)()
	todo("implement");
	_sub_108626A0(this, summary, undo);
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

_extern void _sub_10862D50(CForgeUndoManager *const);
void CForgeUndoManager::PerformUndo() // 0x10862D50
{
	mangled_x86(MANGLED_TODO, "?PerformUndo@CForgeUndoManager@@AAEXXZ");
	// static ...; // 0x10862E64
	// static ...; // 0x10862E58
	// static ...; // 0x10862E50
	// CForgeUndoManager *const this;
	{
		// CForgeUndoManager::SUndoEntry entry;
	}
	// function call : void ()
	todo("implement");
	_sub_10862D50(this);
}

_extern void _sub_10862BF0(CForgeUndoManager *const);
void CForgeUndoManager::PerformRedo() // 0x10862BF0
{
	mangled_x86(MANGLED_TODO, "?PerformRedo@CForgeUndoManager@@AAEXXZ");
	// static ...; // 0x10862D04
	// static ...; // 0x10862CF8
	// static ...; // 0x10862CF0
	// CForgeUndoManager *const this;
	{
		// CForgeUndoManager::SUndoEntry entry;
	}
	// function call : void ()
	todo("implement");
	_sub_10862BF0(this);
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

extern std::string _sub_10862B00(CForgeUndoManager const *const);
std::string CForgeUndoManager::GetNextUndoSummary() const // 0x10862B00
{
	mangled_x86(MANGLED_TODO, "?GetNextUndoSummary@CForgeUndoManager@@QBE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
	// CForgeUndoManager const *const this;
	todo("implement");
	std::string __result = _sub_10862B00((CForgeUndoManager const *)this);
	return __result;
}

extern std::string _sub_10862A40(CForgeUndoManager const *const);
std::string CForgeUndoManager::GetNextRedoSummary() const // 0x10862A40
{
	mangled_x86(MANGLED_TODO, "?GetNextRedoSummary@CForgeUndoManager@@QBE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
	// CForgeUndoManager const *const this;
	todo("implement");
	std::string __result = _sub_10862A40((CForgeUndoManager const *)this);
	return __result;
}

/* ---------- private code */
