/* ---------- headers */

#include "Modules/ModuleInput.hpp"
#include "hades/hades.h"

#include "Blam/BlamInput.hpp"
#include "Blam/input/input.hpp"
#include "CommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Console/Console.hpp"
#include "ElDorito.hpp"
#include "Modules/ModuleBase.hpp"
#include "Pointer.hpp"
#include "ThirdParty/rapidjson/allocators.h"
#include "ThirdParty/rapidjson/encodings.h"
#include "ThirdParty/rapidjson/internal/diyfp.h"
#include "ThirdParty/rapidjson/internal/dtoa.h"
#include "ThirdParty/rapidjson/internal/ieee754.h"
#include "ThirdParty/rapidjson/internal/itoa.h"
#include "ThirdParty/rapidjson/internal/stack.h"
#include "ThirdParty/rapidjson/internal/strfunc.h"
#include "ThirdParty/rapidjson/stream.h"
#include "ThirdParty/rapidjson/stringbuffer.h"
#include "ThirdParty/rapidjson/writer.h"
#include "Utils/Macros.hpp"
#include "Utils/NameValueTable.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/StlUtil.hpp"
#include "Utils/String.hpp"
#include "Web/Bridge/WebRendererQueryHandler.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <algorithm>
#include <atomic>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <deque>
#include <exception>
#include <functional>
#include <initializer_list>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <memory>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <system_error>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <unordered_map>
#include <utility>
#include <vector>

/* ---------- forward declarations */

struct begin;
struct end;
namespace Blam
{
	namespace Input
	{
		enum GameAction : unsigned char;
		enum KeyCode : unsigned short;
		struct BindingsTable;
		struct ConfigurableAction;
	}
}
namespace Modules
{
	class ModuleBase;
	class ModuleInput;
}
namespace
{
	struct CommandBinding;
}

namespace Utils {}
using namespace ::Utils;
namespace Utils
{
	namespace AntiCheat {}
	using namespace Utils::AntiCheat;
}

namespace Modules {}
using namespace ::Modules;
namespace base
{
	namespace internal {}
	using namespace base::internal;
}

namespace Patches {}
using namespace ::Patches;
namespace Blam
{
	namespace Input {}
	using namespace Blam::Input;
}

namespace Console {}
using namespace ::Console;
namespace Blam {}
using namespace ::Blam;

/* ---------- constants */

//enum CommandBind::__l2::s_state
//{
//	KEYNAME_PART = 0,
//	COMMAND_HOLD_PART,
//	COMMAND_PART,
//};

/* ---------- definitions */

namespace
{
	#pragma pack(push, 4)
	struct CommandBinding
	{
		std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > command; // 0x0
		bool isHold; // 0x10
		bool active; // 0x11
		CommandBinding(CommandBinding &); /* compiler_generated() */
		CommandBinding(CommandBinding const &); /* compiler_generated() */
		CommandBinding(); /* compiler_generated() */
		~CommandBinding(); /* compiler_generated() */
		CommandBinding &operator=(CommandBinding &); /* compiler_generated() */
		CommandBinding &operator=(CommandBinding const &); /* compiler_generated() */
		unsigned char __pad0[2]; // 0x12
	};
	#pragma pack(pop)
	static_assert(sizeof(CommandBinding) == 20, "Invalid CommandBinding size");
}
/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

namespace
{
	extern Utils::NameValueTable<enum Blam::Input::ControllerButton> controllerButtons; // 0x124550A0
	extern Utils::NameValueTable<enum Blam::Input::KeyCode> keyCodes; // 0x12454F08
	extern Utils::NameValueTable<enum Blam::Input::MouseButton> mouseButtons; // 0x12455018
	extern Utils::NameValueTable<enum Blam::Input::GameAction> gameActions; // 0x12454F90
	extern std::vector<Blam::Input::ConfigurableAction,std::allocator<Blam::Input::ConfigurableAction> > infantryControls; // 0x12454EF8
	extern std::vector<Blam::Input::ConfigurableAction,std::allocator<Blam::Input::ConfigurableAction> > vehicleControls; // 0x12454EE8
	extern Blam::Input::BindingsTable bindings; // 0x124559B0
}
/* ---------- public code */

namespace Modules
{
	extern ModuleInput* _sub_109C4B60(Modules::ModuleInput *const);
	ModuleInput::ModuleInput() : ModuleBase(todo_result<std::basic_string<char,std::char_traits<char>,std::allocator<char> >>()) // 0x109C4B60
	{
		mangled_x86(MANGLED_TODO, "??0ModuleInput@Modules@@QAE@XZ");
		// Modules::ModuleInput *const this;
		todo("implement");
		_sub_109C4B60(this);
	}
}

namespace Blam
{
	namespace Input
	{
		extern BindingsTable *_sub_109D23F0();
	}
}

namespace Modules
{
	Blam::Input::BindingsTable *ModuleInput::GetBindings() // 0x109D23F0
	{
		mangled_x86(MANGLED_TODO, "?GetBindings@ModuleInput@Modules@@SAPAUBindingsTable@Input@Blam@@XZ");
		// procedure flags: nofpo
		todo("implement");
		Blam::Input::BindingsTable * __result = _sub_109D23F0();
		return __result;
	}

	_extern void _sub_109D39A0();
	void ModuleInput::UpdateBindings() // 0x109D39A0
	{
		mangled_x86(MANGLED_TODO, "?UpdateBindings@ModuleInput@Modules@@SAXXZ");
		// procedure flags: nofpo
		todo("implement");
		_sub_109D39A0();
	}
}

extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > _sub_109D0560(Modules::ModuleInput const *const);
namespace Modules
{
	std::basic_string<char,std::char_traits<char>,std::allocator<char> > ModuleInput::ExportBindings() const // 0x109D0560
	{
		mangled_x86(MANGLED_TODO, "?ExportBindings@ModuleInput@Modules@@QBE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
		// static ...; // 0x109D1086
		// static ...; // 0x109D107B
		// static ...; // 0x109D1072
		// static ...; // 0x109D1067
		// static ...; // 0x109D105C
		// static ...; // 0x109D1053
		// static ...; // 0x109D1047
		// static ...; // 0x109D1039
		// static ...; // 0x109D1030
		// static ...; // 0x109D102B
		// static ...; // 0x109D1024
		// static ...; // 0x109D101C
		// static ...; // 0x109D0F8C
		// static ...; // 0x109D0F84
		// Modules::ModuleInput const *const this;
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > result;
		{
			// Utils::NameValueTable<enum Blam::Input::GameAction> &<range>$L0;
			// std::_Vector_const_iterator<std::_Vector_val<std::_Simple_types<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,enum Blam::Input::GameAction> > > > <begin>$L0;
			// std::_Vector_const_iterator<std::_Vector_val<std::_Simple_types<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,enum Blam::Input::GameAction> > > > <end>$L0;
			{
				// std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,enum Blam::Input::GameAction> const &action;
				{
					// Blam::Input::ControllerButton button;
					// std::basic_string<char,std::char_traits<char>,std::allocator<char> > buttonName;
				}
			}
		}
		{
			// std::_Vector_const_iterator<std::_Vector_val<std::_Simple_types<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,enum Blam::Input::GameAction> > > > <end>$L1;
			// std::_Vector_const_iterator<std::_Vector_val<std::_Simple_types<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,enum Blam::Input::GameAction> > > > <begin>$L1;
			// Utils::NameValueTable<enum Blam::Input::GameAction> &<range>$L1;
			{
				{
					// std::basic_string<char,std::char_traits<char>,std::allocator<char> > primaryName;
					// std::basic_string<char,std::char_traits<char>,std::allocator<char> > secondaryName;
					// Blam::Input::KeyCode primaryKey;
					// Blam::Input::MouseButton primaryMouse;
					// Blam::Input::KeyCode secondaryKey;
					// Blam::Input::MouseButton secondaryMouse;
				}
			}
		}
		{
			// __int32 i;
			{
				// CommandBinding *const binding;
				// std::basic_string<char,std::char_traits<char>,std::allocator<char> > line;
				// std::basic_string<char,std::char_traits<char>,std::allocator<char> > prefix;
				// std::basic_string<char,std::char_traits<char>,std::allocator<char> > key_name;
				{
					// std::basic_string<char,std::char_traits<char>,std::allocator<char> > *<end>$L2;
					// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > &<range>$L2;
					// std::basic_string<char,std::char_traits<char>,std::allocator<char> > *<begin>$L2;
					{
						// std::basic_string<char,std::char_traits<char>,std::allocator<char> > command;
					}
				}
			}
		}
		todo("implement");
		std::string __result = _sub_109D0560((Modules::ModuleInput const *)this);
		return __result;
	}

	_extern bool _sub_109D2480(Modules::ModuleInput *const, std::string);
	bool ModuleInput::IsCommandBound(std::basic_string<char,std::char_traits<char>,std::allocator<char> > command) // 0x109D2480
	{
		mangled_x86(MANGLED_TODO, "?IsCommandBound@ModuleInput@Modules@@QAE_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// static ...; // 0x109D2724
		// static ...; // 0x109D271C
		// Modules::ModuleInput *const this;
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > command;
		{
			// __int32 i;
			{
				// CommandBinding *const binding;
				// std::basic_string<char,std::char_traits<char>,std::allocator<char> > bound_command;
			}
		}
		todo("implement");
		bool __result = _sub_109D2480(this, command);
		return __result;
	}
}

/* ---------- private code */
