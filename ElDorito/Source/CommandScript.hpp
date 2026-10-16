#ifndef __COMMANDSCRIPT_HPP__
#define __COMMANDSCRIPT_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "CommandLineArgs.hpp"
#include "CommandMap.hpp"
#include "Forge/Magnets.hpp"
#include "Patches/CustomPackets.hpp"
#include "Scripting/HaloScript/HaloScript.hpp"
#include "Web/WebRenderHandlerGpu.hpp"

#include <deque>
#include <functional>
#include <istream>
#include <memory>
#include <sstream>
#include <stack>
#include <string>
#include <utility>

/* ---------- forward declarations */

class CommandLineArgs;
namespace Modules
{
	class CommandScript;
	class CommandScriptStack;
}

/* ---------- constants */

/* ---------- definitions */

namespace Modules
{
	class CommandScript
	{
	public:
		CommandScript(Modules::CommandScript &); /* compiler_generated() */
		_inline CommandScript(std::unique_ptr<std::istream> stream, bool isUserInput, bool stopOnFirstError);
		void Execute();
		void Complete();
		bool IsFinished() const;
		bool HasError() const;
		std::string GetErrorMessage() const;
	private:
		bool ReadNextLine();
		void HandleError(std::string const &message);
		void ExecuteSleep(CommandLineArgs const &args);
		void ExecuteWaitFor(CommandLineArgs const &args);
		bool m_isUserInput; // 0x0
		bool m_finished; // 0x1
		bool m_stopOnFirstError; // 0x2
		unsigned char __pad0[1]; // 0x3
		std::unique_ptr<std::istream> m_stream; // 0x4
		std::string m_line; // 0x8
		__int32 m_lineNum; // 0x24
		bool m_hasError; // 0x28
		unsigned char __pad1[7]; // 0x29
		std::stringstream m_error; // 0x30
		std::function<bool __cdecl(void)> m_wakeCond; // 0xE0
	public:
		_inline ~CommandScript(); /* compiler_generated() */
		Modules::CommandScript &operator=(Modules::CommandScript &); /* compiler_generated() */
	};
	static_assert(sizeof(Modules::CommandScript) == 264, "Invalid Modules::CommandScript size");
}

#pragma pack(push, 4)
namespace Modules
{
	class CommandScriptStack
	{
	public:
		void PushScript(std::shared_ptr<Modules::CommandScript> script);
		void Update();
	private:
		std::stack<std::shared_ptr<Modules::CommandScript> > m_stack; // 0x0
	public:
		CommandScriptStack(Modules::CommandScriptStack &); /* compiler_generated() */
		CommandScriptStack(Modules::CommandScriptStack const &); /* compiler_generated() */
		_inline CommandScriptStack() = default; /* compiler_generated() */
		_inline ~CommandScriptStack(); /* compiler_generated() */
		Modules::CommandScriptStack &operator=(Modules::CommandScriptStack &); /* compiler_generated() */
		Modules::CommandScriptStack &operator=(Modules::CommandScriptStack const &); /* compiler_generated() */
	};
}

#pragma pack(pop)
static_assert(sizeof(Modules::CommandScriptStack) == 20, "Invalid Modules::CommandScriptStack size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

namespace Modules
{
	inline CommandScript::CommandScript(std::unique_ptr<std::istream> stream, bool isUserInput, bool stopOnFirstError) : m_isUserInput(isUserInput), m_finished(false), m_stopOnFirstError(stopOnFirstError), m_stream(std::move(stream)), m_lineNum(0), m_hasError(false) /* hades-mem-init:  */ // 0x10944E20
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0CommandScript@Modules@@QAE@V?$unique_ptr@V?$basic_istream@DU?$char_traits@D@std@@@std@@U?$default_delete@V?$basic_istream@DU?$char_traits@D@std@@@std@@@2@@std@@_N1@Z");
	}
}

/* ---------- private code */

#endif // __COMMANDSCRIPT_HPP__
