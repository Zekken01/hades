#ifndef __MODULES_MODULEDOWNLOAD_HPP__
#define __MODULES_MODULEDOWNLOAD_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "CommandMap.hpp"
#include "Modules/ModuleBase.hpp"
#include "Patches/PlayerPropertiesExtension.hpp"

/* ---------- forward declarations */

namespace Modules
{
	class ModuleBase;
	class ModuleDownload;
	struct Command;
}

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
namespace Modules
{
	class ModuleDownload :
		public Modules::ModuleBase,
		public Utils::Singleton<Modules::ModuleDownload>
	{
	public:
		Modules::Command *VarMaxHttpConnections; // 0x1C
		Modules::Command *VarMinHttpSegmentSize; // 0x20
		Modules::Command *VarMaxHttpSegmentRetry; // 0x24
		Modules::Command *VarDebugTrace; // 0x28
		ModuleDownload();
		~ModuleDownload() = default; /* compiler_generated() */
	};
}

#pragma pack(pop)
static_assert(sizeof(Modules::ModuleDownload) == 44, "Invalid Modules::ModuleDownload size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __MODULES_MODULEDOWNLOAD_HPP__
