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
	ModuleBase::ModuleBase(std::basic_string<char,std::char_traits<char>,std::allocator<char> > moduleName) // 0x109776C0
	{
		mangled_x86(MANGLED_TODO, "??0ModuleBase@Modules@@QAE@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > moduleName;
		todo("implement");
		_sub_109776C0(this, moduleName);
	}

	extern Command *_sub_10977780(Modules::ModuleBase *const, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &, CommandFlags, bool (*)(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &), std::initializer_list<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >);
	Modules::Command *ModuleBase::AddCommand(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &name, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &shortName, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &description, CommandFlags flags, bool (*updateEvent)(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &), std::initializer_list<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > arguments) // 0x10977780
	{
		mangled_x86(MANGLED_TODO, "?AddCommand@ModuleBase@Modules@@IAEPAUCommand@2@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@00W4CommandFlags@@P6A_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@5@AAV45@@ZV?$initializer_list@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@5@@Z");
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &shortName;
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &description;
		// CommandFlags flags;
		// bool (*updateEvent)(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
		// std::initializer_list<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > arguments;
		// Modules::Command command;
		{
			// std::initializer_list<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > &<range>$L0;
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const *<begin>$L0;
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const *<end>$L0;
			{
				// std::basic_string<char,std::char_traits<char>,std::allocator<char> > arg;
			}
		}
		todo("implement");
		Modules::Command * __result = _sub_10977780(this, name, shortName, description, flags, updateEvent, arguments);
		return __result;
	}

	extern Command *_sub_10978080(Modules::ModuleBase *const, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &, CommandFlags, unsigned long, bool (*)(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &));
	Modules::Command *ModuleBase::AddVariableInt(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &name, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &shortName, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &description, CommandFlags flags, unsigned long defaultValue, bool (*updateEvent)(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &)) // 0x10978080
	{
		mangled_x86(MANGLED_TODO, "?AddVariableInt@ModuleBase@Modules@@IAEPAUCommand@2@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@00W4CommandFlags@@KP6A_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@5@AAV45@@Z@Z");
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &description;
		// CommandFlags flags;
		// unsigned long defaultValue;
		// bool (*updateEvent)(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
		// Modules::Command command;
		todo("implement");
		Modules::Command * __result = _sub_10978080(this, name, shortName, description, flags, defaultValue, updateEvent);
		return __result;
	}

	extern Command *_sub_10977D90(Modules::ModuleBase *const, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &, CommandFlags, unsigned long long, bool (*)(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &));
	Modules::Command *ModuleBase::AddVariableInt64(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &name, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &shortName, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &description, CommandFlags flags, unsigned long long defaultValue, bool (*updateEvent)(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &)) // 0x10977D90
	{
		mangled_x86(MANGLED_TODO, "?AddVariableInt64@ModuleBase@Modules@@IAEPAUCommand@2@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@00W4CommandFlags@@_KP6A_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@5@AAV45@@Z@Z");
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &description;
		// CommandFlags flags;
		// unsigned long long defaultValue;
		// bool (*updateEvent)(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
		// Modules::Command command;
		todo("implement");
		Modules::Command * __result = _sub_10977D90(this, name, shortName, description, flags, defaultValue, updateEvent);
		return __result;
	}

	extern Command *_sub_10977AA0(Modules::ModuleBase *const, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &, CommandFlags, float, bool (*)(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &));
	Modules::Command *ModuleBase::AddVariableFloat(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &name, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &shortName, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &description, CommandFlags flags, float defaultValue, bool (*updateEvent)(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &)) // 0x10977AA0
	{
		mangled_x86(MANGLED_TODO, "?AddVariableFloat@ModuleBase@Modules@@IAEPAUCommand@2@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@00W4CommandFlags@@MP6A_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@5@AAV45@@Z@Z");
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &description;
		// CommandFlags flags;
		// float defaultValue;
		// bool (*updateEvent)(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
		// Modules::Command command;
		todo("implement");
		Modules::Command * __result = _sub_10977AA0(this, name, shortName, description, flags, defaultValue, updateEvent);
		return __result;
	}

	extern Command *_sub_10978350(Modules::ModuleBase *const, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &, CommandFlags, std::string, bool (*)(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &));
	Modules::Command *ModuleBase::AddVariableString(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &name, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &shortName, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &description, CommandFlags flags, std::basic_string<char,std::char_traits<char>,std::allocator<char> > defaultValue, bool (*updateEvent)(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &)) // 0x10978350
	{
		mangled_x86(MANGLED_TODO, "?AddVariableString@ModuleBase@Modules@@IAEPAUCommand@2@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@00W4CommandFlags@@V45@P6A_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@5@AAV45@@Z@Z");
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &description;
		// CommandFlags flags;
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > defaultValue;
		// bool (*updateEvent)(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
		// Modules::Command command;
		todo("implement");
		Modules::Command * __result = _sub_10978350(this, name, shortName, description, flags, defaultValue, updateEvent);
		return __result;
	}

	_extern bool _sub_10978780(Modules::ModuleBase *const, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &, unsigned long &);
	bool ModuleBase::GetVariableInt(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &name, unsigned long &value) // 0x10978780
	{
		mangled_x86(MANGLED_TODO, "?GetVariableInt@ModuleBase@Modules@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAK@Z");
		// unsigned long &value;
		todo("implement");
		bool __result = _sub_10978780(this, name, value);
		return __result;
	}

	_extern bool _sub_10978600(Modules::ModuleBase *const, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &, float &);
	bool ModuleBase::GetVariableFloat(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &name, float &value) // 0x10978600
	{
		mangled_x86(MANGLED_TODO, "?GetVariableFloat@ModuleBase@Modules@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAM@Z");
		// float &value;
		todo("implement");
		bool __result = _sub_10978600(this, name, value);
		return __result;
	}

	_extern bool _sub_10978900(Modules::ModuleBase *const, std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
	bool ModuleBase::GetVariableString(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &name, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &value) // 0x10978900
	{
		mangled_x86(MANGLED_TODO, "?GetVariableString@ModuleBase@Modules@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAV34@@Z");
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &value;
		todo("implement");
		bool __result = _sub_10978900(this, name, value);
		return __result;
	}
}

/* ---------- private code */
