/* ---------- headers */

#include "Modules/ModuleBase.hpp"
#include "hades/hades.h"

#include "CommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Utils/Singleton.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <atomic>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <deque>
#include <exception>
#include <functional>
#include <initializer_list>
#include <limits>
#include <memory>
#include <string>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

struct begin;
struct end;
namespace Modules
{
	class ModuleBase;
	struct Command;
}

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Modules
{
	extern ModuleBase* _sub_109776C0(Modules::ModuleBase *const, std::string);
	ModuleBase::ModuleBase(std::string moduleName) // 0x109776C0
	{
		mangled_x86(MANGLED_TODO, "??0ModuleBase@Modules@@QAE@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::string moduleName;
		todo("implement");
		_sub_109776C0(this, moduleName);
	}

	extern Command *_sub_10977780(Modules::ModuleBase *const, std::string const &, std::string const &, std::string const &, CommandFlags, bool (*)(std::vector<std::string> const &, std::string &), std::initializer_list<std::string>);
	Modules::Command *ModuleBase::AddCommand(std::string const &name, std::string const &shortName, std::string const &description, CommandFlags flags, bool (*updateEvent)(std::vector<std::string> const &, std::string &), std::initializer_list<std::string> arguments) // 0x10977780
	{
		mangled_x86(MANGLED_TODO, "?AddCommand@ModuleBase@Modules@@IAEPAUCommand@2@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@00W4CommandFlags@@P6A_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@5@AAV45@@ZV?$initializer_list@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@5@@Z");
		// std::string const &shortName;
		// std::string const &description;
		// CommandFlags flags;
		// bool (*updateEvent)(std::vector<std::string> const &, std::string &);
		// std::initializer_list<std::string> arguments;
		// Modules::Command command;
		{
			// std::initializer_list<std::string> &<range>$L0;
			// std::string const *<begin>$L0;
			// std::string const *<end>$L0;
			{
				// std::string arg;
			}
		}
		todo("implement");
		Modules::Command * __result = _sub_10977780(this, name, shortName, description, flags, updateEvent, arguments);
		return __result;
	}

	extern Command *_sub_10978080(Modules::ModuleBase *const, std::string const &, std::string const &, std::string const &, CommandFlags, unsigned long, bool (*)(std::vector<std::string> const &, std::string &));
	Modules::Command *ModuleBase::AddVariableInt(std::string const &name, std::string const &shortName, std::string const &description, CommandFlags flags, unsigned long defaultValue, bool (*updateEvent)(std::vector<std::string> const &, std::string &)) // 0x10978080
	{
		mangled_x86(MANGLED_TODO, "?AddVariableInt@ModuleBase@Modules@@IAEPAUCommand@2@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@00W4CommandFlags@@KP6A_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@5@AAV45@@Z@Z");
		// std::string const &description;
		// CommandFlags flags;
		// unsigned long defaultValue;
		// bool (*updateEvent)(std::vector<std::string> const &, std::string &);
		// Modules::Command command;
		todo("implement");
		Modules::Command * __result = _sub_10978080(this, name, shortName, description, flags, defaultValue, updateEvent);
		return __result;
	}

	extern Command *_sub_10977D90(Modules::ModuleBase *const, std::string const &, std::string const &, std::string const &, CommandFlags, unsigned long long, bool (*)(std::vector<std::string> const &, std::string &));
	Modules::Command *ModuleBase::AddVariableInt64(std::string const &name, std::string const &shortName, std::string const &description, CommandFlags flags, unsigned long long defaultValue, bool (*updateEvent)(std::vector<std::string> const &, std::string &)) // 0x10977D90
	{
		mangled_x86(MANGLED_TODO, "?AddVariableInt64@ModuleBase@Modules@@IAEPAUCommand@2@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@00W4CommandFlags@@_KP6A_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@5@AAV45@@Z@Z");
		// std::string const &description;
		// CommandFlags flags;
		// unsigned long long defaultValue;
		// bool (*updateEvent)(std::vector<std::string> const &, std::string &);
		// Modules::Command command;
		todo("implement");
		Modules::Command * __result = _sub_10977D90(this, name, shortName, description, flags, defaultValue, updateEvent);
		return __result;
	}

	extern Command *_sub_10977AA0(Modules::ModuleBase *const, std::string const &, std::string const &, std::string const &, CommandFlags, float, bool (*)(std::vector<std::string> const &, std::string &));
	Modules::Command *ModuleBase::AddVariableFloat(std::string const &name, std::string const &shortName, std::string const &description, CommandFlags flags, float defaultValue, bool (*updateEvent)(std::vector<std::string> const &, std::string &)) // 0x10977AA0
	{
		mangled_x86(MANGLED_TODO, "?AddVariableFloat@ModuleBase@Modules@@IAEPAUCommand@2@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@00W4CommandFlags@@MP6A_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@5@AAV45@@Z@Z");
		// std::string const &description;
		// CommandFlags flags;
		// float defaultValue;
		// bool (*updateEvent)(std::vector<std::string> const &, std::string &);
		// Modules::Command command;
		todo("implement");
		Modules::Command * __result = _sub_10977AA0(this, name, shortName, description, flags, defaultValue, updateEvent);
		return __result;
	}

	extern Command *_sub_10978350(Modules::ModuleBase *const, std::string const &, std::string const &, std::string const &, CommandFlags, std::string, bool (*)(std::vector<std::string> const &, std::string &));
	Modules::Command *ModuleBase::AddVariableString(std::string const &name, std::string const &shortName, std::string const &description, CommandFlags flags, std::string defaultValue, bool (*updateEvent)(std::vector<std::string> const &, std::string &)) // 0x10978350
	{
		mangled_x86(MANGLED_TODO, "?AddVariableString@ModuleBase@Modules@@IAEPAUCommand@2@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@00W4CommandFlags@@V45@P6A_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@5@AAV45@@Z@Z");
		// std::string const &description;
		// CommandFlags flags;
		// std::string defaultValue;
		// bool (*updateEvent)(std::vector<std::string> const &, std::string &);
		// Modules::Command command;
		todo("implement");
		Modules::Command * __result = _sub_10978350(this, name, shortName, description, flags, defaultValue, updateEvent);
		return __result;
	}

	_extern bool _sub_10978780(Modules::ModuleBase *const, std::string const &, unsigned long &);
	bool ModuleBase::GetVariableInt(std::string const &name, unsigned long &value) // 0x10978780
	{
		mangled_x86(MANGLED_TODO, "?GetVariableInt@ModuleBase@Modules@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAK@Z");
		// unsigned long &value;
		todo("implement");
		bool __result = _sub_10978780(this, name, value);
		return __result;
	}

	_extern bool _sub_10978600(Modules::ModuleBase *const, std::string const &, float &);
	bool ModuleBase::GetVariableFloat(std::string const &name, float &value) // 0x10978600
	{
		mangled_x86(MANGLED_TODO, "?GetVariableFloat@ModuleBase@Modules@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAM@Z");
		// float &value;
		todo("implement");
		bool __result = _sub_10978600(this, name, value);
		return __result;
	}

	_extern bool _sub_10978900(Modules::ModuleBase *const, std::string const &, std::string &);
	bool ModuleBase::GetVariableString(std::string const &name, std::string &value) // 0x10978900
	{
		mangled_x86(MANGLED_TODO, "?GetVariableString@ModuleBase@Modules@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAV34@@Z");
		// std::string &value;
		todo("implement");
		bool __result = _sub_10978900(this, name, value);
		return __result;
	}
}

/* ---------- private code */
