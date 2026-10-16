#ifndef __DEBUG_CRASHREPORTING_STALKWALKER_HPP__
#define __DEBUG_CRASHREPORTING_STALKWALKER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Debug/CrashReporting/CrashReporter.hpp"

/* ---------- forward declarations */

namespace Debug
{
	namespace CrashReporting
	{
		class StackWalker;
	}
}

/* ---------- constants */

/* ---------- definitions */

namespace Debug
{
	namespace CrashReporting
	{
		class StackWalker
		{
		private:
			void *m_hProc; // 0x0
			void *m_hThread; // 0x4
			_CONTEXT m_context; // 0x8
			_tagSTACKFRAME m_stackFrame; // 0x2D4
			_IMAGEHLP_LINE m_line; // 0x378
			char m_buffer[2088]; // 0x38C
			bool m_hasLineInfo; // 0xBB4
			bool m_hasSymbolInfo; // 0xBB5
			unsigned char __pad0[2]; // 0xBB6
			__int32 m_frameIndex; // 0xBB8
			__int32 m_maxFrames; // 0xBBC
		public:
			_inline StackWalker(_CONTEXT context);
			void SetMaxFrames(__int32);
			_inline __int32 const GetLineNumber() const;
			_inline unsigned __int32 GetPCAddress() const;
			_inline char const *GetFileName() const;
			_inline char const *GetFunctionName() const;
			_inline bool HasSymbolInfo() const;
			_inline bool HasLineInfo() const;
			_inline bool Next();
		private:
			_inline _SYMBOL_INFO const *GetSymbol() const;
		};
		static_assert(sizeof(Debug::CrashReporting::StackWalker) == 3008, "Invalid Debug::CrashReporting::StackWalker size");
	}
}

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

namespace Debug
{
	namespace CrashReporting
	{
		_inline StackWalker::StackWalker(_CONTEXT context) : m_hProc(nullptr), m_hThread(nullptr), m_context(), m_stackFrame(), m_line{ sizeof(_IMAGEHLP_LINE) }, m_buffer(), m_hasLineInfo(false), m_hasSymbolInfo(false), m_frameIndex(0), m_maxFrames(32) /* hades-mem-init:  */ // 0x1068D590
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??0StackWalker@CrashReporting@Debug@@QAE@U_CONTEXT@@@Z");

			m_context = context;
			static bool symbolsInitialized = false;
			if (!symbolsInitialized)
			{
				symbolsInitialized = true;
				SymInitialize(GetCurrentProcess(), nullptr, TRUE);
			}
			m_context = context;
			m_hProc = GetCurrentProcess();
			m_hThread = GetCurrentThread();
			m_stackFrame.AddrPC.Offset = context.Eip;
			m_stackFrame.AddrPC.Mode = AddrModeFlat;
			m_stackFrame.AddrStack.Offset = context.Esp;
			m_stackFrame.AddrStack.Mode = AddrModeFlat;
			m_stackFrame.AddrFrame.Offset = context.Ebp;
			m_stackFrame.AddrFrame.Mode = AddrModeFlat;
		}
	}
}


namespace Debug
{
	namespace CrashReporting
	{
		_inline __int32 const StackWalker::GetLineNumber() const // 0x1068F470
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetLineNumber@StackWalker@CrashReporting@Debug@@QBE?BHXZ");

			return m_hasLineInfo ? m_line.LineNumber : 0;
		}

		_inline unsigned __int32 StackWalker::GetPCAddress() const // 0x1068F6B0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetPCAddress@StackWalker@CrashReporting@Debug@@QBEIXZ");

			return m_stackFrame.AddrPC.Offset;
		}
	}
}


namespace Debug
{
	namespace CrashReporting
	{
		_inline char const *StackWalker::GetFileName() const // 0x1068F2A0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetFileName@StackWalker@CrashReporting@Debug@@QBEPBDXZ");

			return m_hasLineInfo ? m_line.FileName : nullptr;
		}
	}
}


namespace Debug
{
	namespace CrashReporting
	{
		_inline char const *StackWalker::GetFunctionName() const // 0x1068F300
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetFunctionName@StackWalker@CrashReporting@Debug@@QBEPBDXZ");

			return m_hasSymbolInfo ? GetSymbol()->Name : nullptr;
		}

		_inline bool StackWalker::HasSymbolInfo() const // 0x1068F860
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?HasSymbolInfo@StackWalker@CrashReporting@Debug@@QBE_NXZ");

			return m_hasSymbolInfo;
		}

		_inline bool StackWalker::HasLineInfo() const // 0x1068F830
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?HasLineInfo@StackWalker@CrashReporting@Debug@@QBE_NXZ");

			return m_hasLineInfo;
		}

		_inline bool StackWalker::Next() // 0x106900C0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Next@StackWalker@CrashReporting@Debug@@QAE_NXZ");

			if (m_frameIndex++ >= m_maxFrames)
				return false;
			__int32 result = StackWalk(IMAGE_FILE_MACHINE_I386, m_hProc, m_hThread, &m_stackFrame, &m_context, nullptr, SymFunctionTableAccess, SymGetModuleBase, nullptr);
			if (!result)
				return false;
			unsigned long long symbolDisplacement;
			unsigned long lineDisplacement;
			_SYMBOL_INFO *symbol = reinterpret_cast<_SYMBOL_INFO *>(m_buffer);
			symbol->SizeOfStruct = sizeof(_SYMBOL_INFO);
			symbol->MaxNameLen = 2000;
			m_hasSymbolInfo = SymFromAddr(m_hProc, m_stackFrame.AddrPC.Offset, &symbolDisplacement, reinterpret_cast<_SYMBOL_INFO *>(m_buffer));
			m_hasLineInfo = SymGetLineFromAddr(m_hProc, m_stackFrame.AddrPC.Offset, &lineDisplacement, &m_line);
			return true;
		}
	}
}


namespace Debug
{
	namespace CrashReporting
	{
		_inline _SYMBOL_INFO const *StackWalker::GetSymbol() const // 0x1068F7D0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetSymbol@StackWalker@CrashReporting@Debug@@ABEPBU_SYMBOL_INFO@@XZ");

			return m_hasSymbolInfo ? (_SYMBOL_INFO const *)m_buffer : nullptr;
		}
	}
}

/* ---------- private code */

#endif // __DEBUG_CRASHREPORTING_STALKWALKER_HPP__
