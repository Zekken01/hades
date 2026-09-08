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

_extern bool _sub_10862920(CForgeUndoManager *const);
bool CForgeUndoManager::CanUndo() // 0x10862920
{
	mangled_x86(MANGLED_TODO, "?CanUndo@CForgeUndoManager@@QAE_NXZ");
	// CForgeUndoManager *const this;
	todo("implement");
	bool __result = _sub_10862920(this);
	return __result;
}

_extern bool _sub_108628A0(CForgeUndoManager *const);
bool CForgeUndoManager::CanRedo() // 0x108628A0
{
	mangled_x86(MANGLED_TODO, "?CanRedo@CForgeUndoManager@@QAE_NXZ");
	// CForgeUndoManager *const this;
	todo("implement");
	bool __result = _sub_108628A0(this);
	return __result;
}

_extern void _sub_10862EE0(CForgeUndoManager *const);
void CForgeUndoManager::RequestUndo() // 0x10862EE0
{
	mangled_x86(MANGLED_TODO, "?RequestUndo@CForgeUndoManager@@QAEXXZ");
	// CForgeUndoManager *const this;
	todo("implement");
	_sub_10862EE0(this);
}

_extern void _sub_10862EB0(CForgeUndoManager *const);
void CForgeUndoManager::RequestRedo() // 0x10862EB0
{
	mangled_x86(MANGLED_TODO, "?RequestRedo@CForgeUndoManager@@QAEXXZ");
	// CForgeUndoManager *const this;
	todo("implement");
	_sub_10862EB0(this);
}

_extern void _sub_108626A0(CForgeUndoManager *const, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &, std::shared_ptr<IForgeUndo>);
void CForgeUndoManager::AddUndo(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &summary, std::shared_ptr<IForgeUndo> undo) // 0x108626A0
{
	mangled_x86(MANGLED_TODO, "?AddUndo@CForgeUndoManager@@QAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$shared_ptr@UIForgeUndo@@@3@@Z");
	// static ...; // 0x1086281C
	// CForgeUndoManager *const this;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &summary;
	// std::shared_ptr<IForgeUndo> undo;
	// CForgeUndoManager::SUndoEntry entry;
	// function call : long (*const)()
	todo("implement");
	_sub_108626A0(this, summary, undo);
}

extern CForgeUndoManager::SUndoEntry* _sub_10862260(CForgeUndoManager::SUndoEntry *const, CForgeUndoManager::SUndoEntry const &);
_inline CForgeUndoManager::SUndoEntry::SUndoEntry(CForgeUndoManager::SUndoEntry const &__that) // 0x10862260
{
	mangled_x86(MANGLED_TODO, "??0SUndoEntry@CForgeUndoManager@@QAE@ABU01@@Z");
	// CForgeUndoManager::SUndoEntry const &__that;
	compiler_generated();
	todo("implement");
	_sub_10862260(this, __that);
}

extern CForgeUndoManager::SUndoEntry* _sub_10862300(CForgeUndoManager::SUndoEntry *const);
_inline CForgeUndoManager::SUndoEntry::SUndoEntry() // 0x10862300
{
	mangled_x86(MANGLED_TODO, "??0SUndoEntry@CForgeUndoManager@@QAE@XZ");
	// CForgeUndoManager::SUndoEntry *const this;
	compiler_generated();
	todo("implement");
	_sub_10862300(this);
}

_extern void _sub_10862540(CForgeUndoManager::SUndoEntry *const);
_inline CForgeUndoManager::SUndoEntry::~SUndoEntry() // 0x10862540
{
	mangled_x86(MANGLED_TODO, "??1SUndoEntry@CForgeUndoManager@@QAE@XZ");
	// CForgeUndoManager::SUndoEntry *const this;
	compiler_generated();
	todo("implement");
	_sub_10862540(this);
}

_extern void _sub_10862F70(CForgeUndoManager *const);
void CForgeUndoManager::Update() // 0x10862F70
{
	mangled_x86(MANGLED_TODO, "?Update@CForgeUndoManager@@QAEXXZ");
	// CForgeUndoManager *const this;
	todo("implement");
	_sub_10862F70(this);
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

_extern void _sub_108629A0(CForgeUndoManager *const);
void CForgeUndoManager::Clear() // 0x108629A0
{
	mangled_x86(MANGLED_TODO, "?Clear@CForgeUndoManager@@QAEXXZ");
	// CForgeUndoManager *const this;
	todo("implement");
	_sub_108629A0(this);
}

bool CForgeUndoManager::IsRecording() const // 0x10862BC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?IsRecording@CForgeUndoManager@@QBE_NXZ");
	// CForgeUndoManager const *const this;

	return m_recording;
}

_extern void _sub_10862F40(CForgeUndoManager *const);
void CForgeUndoManager::StopRecording() // 0x10862F40
{
	mangled_x86(MANGLED_TODO, "?StopRecording@CForgeUndoManager@@QAEXXZ");
	// CForgeUndoManager *const this;
	todo("implement");
	_sub_10862F40(this);
}

_extern void _sub_10862F10(CForgeUndoManager *const);
void CForgeUndoManager::StartRecording() // 0x10862F10
{
	mangled_x86(MANGLED_TODO, "?StartRecording@CForgeUndoManager@@QAEXXZ");
	// CForgeUndoManager *const this;
	todo("implement");
	_sub_10862F10(this);
}

extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > _sub_10862B00(CForgeUndoManager const *const);
std::basic_string<char,std::char_traits<char>,std::allocator<char> > CForgeUndoManager::GetNextUndoSummary() const // 0x10862B00
{
	mangled_x86(MANGLED_TODO, "?GetNextUndoSummary@CForgeUndoManager@@QBE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
	// CForgeUndoManager const *const this;
	todo("implement");
	std::string __result = _sub_10862B00((CForgeUndoManager const *)this);
	return __result;
}

extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > _sub_10862A40(CForgeUndoManager const *const);
std::basic_string<char,std::char_traits<char>,std::allocator<char> > CForgeUndoManager::GetNextRedoSummary() const // 0x10862A40
{
	mangled_x86(MANGLED_TODO, "?GetNextRedoSummary@CForgeUndoManager@@QBE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
	// CForgeUndoManager const *const this;
	todo("implement");
	std::string __result = _sub_10862A40((CForgeUndoManager const *)this);
	return __result;
}

/* ---------- private code */
