/* ---------- headers */

#include "Scripting/HaloScript/HaloScript.hpp"
#include "hades/hades.h"

#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/physics/havok_types.hpp"
#include "Blam/rasterizer/rasterizer_geometry.hpp"
#include "Blam/scenario/scenario.hpp"
#include "Blam/scenario/scenario_definitions.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "CommandScript.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Forge/Reforge.hpp"
#include "Scripting/HaloScript/HsThreadStorage.hpp"
#include "Utils/NameValueTable.hpp"
#include "Utils/StlUtil.hpp"
#include "Web/Bridge/WebRendererQueryHandler.hpp"

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
#include <span>
#include <string>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <unordered_map>
#include <utility>
#include <variant>
#include <vector>

/* ---------- forward declarations */

struct begin;
struct end;
struct hs_stack_frame;
struct hs_value;
struct lambda_1;
struct s_hs_script;
struct s_hs_thread;
struct s_scenario;
namespace Scripting
{
	namespace HS
	{
		struct ScriptHook;
	}
}

namespace Scripting {}
using namespace ::Scripting;
namespace Scripting
{
	namespace HS {}
	using namespace Scripting::HS;
}

namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Core {}
	using namespace Patches::Core;
}

/* ---------- constants */

/* ---------- definitions */

// Scripting::HS::ScriptHook is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

//class Scripting::HS::Init::__l2::<lambda_1>
//{
//public:
//	void operator()(char const *) const;
//};
//static_assert(sizeof(Scripting::HS::Init::__l2::<lambda_1>) == 1, "Invalid Scripting::HS::Init::__l2::<lambda_1> size");

/* ---------- prototypes */

namespace Scripting
{
	namespace HS
	{
		extern char const *MarshalString(__int32 threadIndex, std::string_view str);
		extern hs_value MarshalArgument(long threadIndex, e_hs_type type, hs_value const &value);
		extern hs_value MarshalReturn(long threadIndex, e_hs_type type, hs_value value);
		extern __int32 FindScriptByName(std::string_view name);
		extern void InitializeForNewMap();
		extern void Init();
		extern void Tick();
		extern void PushScript(long threadIndex, short scriptIndex, long **outReturnValueAddr, std::span<hs_value const> arguments);
		extern void ExecuteScript(__int32 scriptIndex, std::span<hs_value const> arguments);
		extern void ExecuteScript(std::string_view name, std::span<hs_value const> arguments);
		extern hs_value ExecuteScriptWithReturn(short scriptIndex, std::span<hs_value const> arguments);
		extern hs_value ExecuteScriptWithReturn(std::string_view name, std::span<hs_value const> arguments);
		extern void AddHookCallback(std::string_view name, short callbackScriptIndex);
		extern void RemoveHookCallback(std::string_view name, short callbackScriptIndex);
		extern void CallHook(std::string_view name, std::span<hs_value const> arguments);
	}
}

/* ---------- globals */

namespace Scripting
{
	namespace HS
	{
		extern std::unordered_map<std::string_view,Scripting::HS::ScriptHook> hooks; // 0x1138827C
	}
}

/* ---------- private variables */

/* ---------- public code */

namespace Scripting
{
	namespace HS
	{
		_extern void _sub_106E84C0(Scripting::HS::ScriptHook *const, short);
		_inline void ScriptHook::AddCallback(short callback) // 0x106E84C0
		{
			mangled_x86(MANGLED_TODO, "?AddCallback@ScriptHook@HS@Scripting@@QAEXF@Z");
			// static ...; // 0x106E8600
			// static ...; // 0x106E85F8
			// Scripting::HS::ScriptHook *const this;
			// short callback;
			{
				// std::_Vector_iterator<std::_Vector_val<std::_Simple_types<short> > > it;
			}
			todo("implement");
			_sub_106E84C0(this, callback);
		}

		_extern void _sub_106E91E0(Scripting::HS::ScriptHook *const, short);
		_inline void ScriptHook::RemoveCallback(short callback) // 0x106E91E0
		{
			mangled_x86(MANGLED_TODO, "?RemoveCallback@ScriptHook@HS@Scripting@@QAEXF@Z");
			// short callback;
			todo("implement");
			_sub_106E91E0(this, callback);
		}
	}
}

extern char const *_sub_106E8E10(__int32, std::string_view);
namespace Scripting
{
	namespace HS
	{
		char const *MarshalString(__int32 threadIndex, std::string_view str) // 0x106E8E10
		{
			mangled_x86(MANGLED_TODO, "?MarshalString@HS@Scripting@@YAPBDHV?$basic_string_view@DU?$char_traits@D@std@@@std@@@Z");
			// std::string_view str;
			// char *mem;
			todo("implement");
			char const * __result = _sub_106E8E10(threadIndex, str);
			return __result;
		}
	}
}

extern hs_value _sub_106E8D50(long, e_hs_type, hs_value const &);
namespace Scripting
{
	namespace HS
	{
		hs_value MarshalArgument(long threadIndex, e_hs_type type, hs_value const &value) // 0x106E8D50
		{
			mangled_x86(MANGLED_TODO, "?MarshalArgument@HS@Scripting@@YA?AUhs_value@@JW4e_hs_type@@ABU3@@Z");
			// hs_value const &value;
			todo("implement");
			hs_value __result = _sub_106E8D50(threadIndex, type, value);
			return __result;
		}
	}
}

extern hs_value _sub_106E8DF0(long, e_hs_type, hs_value);
namespace Scripting
{
	namespace HS
	{
		hs_value MarshalReturn(long threadIndex, e_hs_type type, hs_value value) // 0x106E8DF0
		{
			mangled_x86(MANGLED_TODO, "?MarshalReturn@HS@Scripting@@YA?AUhs_value@@JW4e_hs_type@@U3@@Z");
			// hs_value value;
			todo("implement");
			hs_value __result = _sub_106E8DF0(threadIndex, type, value);
			return __result;
		}

		_extern __int32 _sub_106E8BB0(std::string_view);
		__int32 FindScriptByName(std::string_view name) // 0x106E8BB0
		{
			mangled_x86(MANGLED_TODO, "?FindScriptByName@HS@Scripting@@YAHV?$basic_string_view@DU?$char_traits@D@std@@@std@@@Z");
			// std::string_view name;
			// s_scenario const *scnr;
			{
				// __int32 i;
			}
			todo("implement");
			__int32 __result = _sub_106E8BB0(name);
			return __result;
		}

		_extern void _sub_106E8CF0();
		void InitializeForNewMap() // 0x106E8CF0
		{
			mangled_x86(MANGLED_TODO, "?InitializeForNewMap@HS@Scripting@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_106E8CF0();
		}

		_extern void _sub_106E8C80();
		void Init() // 0x106E8C80
		{
			mangled_x86(MANGLED_TODO, "?Init@HS@Scripting@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_106E8C80();
		}

		_extern void _sub_106E9390();
		void Tick() // 0x106E9390
		{
			mangled_x86(MANGLED_TODO, "?Tick@HS@Scripting@@YAXXZ");
			// procedure flags: nofpo
			// unsigned __int32 time;
			todo("implement");
			_sub_106E9390();
		}

		_extern void _sub_106E8EE0(long, short, long **, std::span<hs_value const>);
		void PushScript(long threadIndex, short scriptIndex, long **outReturnValueAddr, std::span<hs_value const> arguments) // 0x106E8EE0
		{
			mangled_x86(MANGLED_TODO, "?PushScript@HS@Scripting@@YAXJFPAPAJV?$span@$$CBUhs_value@@$0PPPPPPPP@@std@@@Z");
			// static ...; // 0x106E9108
			// long threadIndex;
			// short scriptIndex;
			// long **outReturnValueAddr;
			// std::span<hs_value const> arguments;
			// long *return_value;
			// long *arg_count;
			// long *args;
			// s_hs_script const *script;
			// short stack_offset;
			// s_scenario const *scnr;
			// short args_stack_offset;
			// hs_stack_frame *stack;
			// s_hs_thread *thread;
			// long *next_expression_index;
			{
				// long i;
			}
			// function call : void *(*const)(long, long, long, short *)
			// function call : void *(*const)(long, long, long, short *)
			// function call : void *(*const)(long, long, long, short *)
			// function call : void *(*const)(long, long, long, short *)
			// function call : bool (*const)(long, long, long, long *)
			todo("implement");
			_sub_106E8EE0(threadIndex, scriptIndex, outReturnValueAddr, arguments);
		}

		_extern void _sub_106E8790(__int32, std::span<hs_value const>);
		void ExecuteScript(__int32 scriptIndex, std::span<hs_value const> arguments) // 0x106E8790
		{
			mangled_x86(MANGLED_TODO, "?ExecuteScript@HS@Scripting@@YAXHV?$span@$$CBUhs_value@@$0PPPPPPPP@@std@@@Z");
			// std::span<hs_value const> arguments;
			// long thread_index;
			// s_hs_script const *script;
			// s_scenario const *scnr;
			// function call : long (*const)(e_hs_script_type, short)
			todo("implement");
			_sub_106E8790(scriptIndex, arguments);
		}

		// mangled_x86(MANGLED_DEFAULT, "??0ScriptHook@HS@Scripting@@QAE@XZ"); no body to assert in
		_inline ScriptHook::ScriptHook() = default; // 0x106E7570

		// mangled_x86(MANGLED_DEFAULT, "??1ScriptHook@HS@Scripting@@QAE@XZ"); no body to assert in
		_inline ScriptHook::~ScriptHook() = default; // 0x106E7CC0

		_extern void _sub_106E8880(std::string_view, std::span<hs_value const>);
		void ExecuteScript(std::string_view name, std::span<hs_value const> arguments) // 0x106E8880
		{
			mangled_x86(MANGLED_TODO, "?ExecuteScript@HS@Scripting@@YAXV?$basic_string_view@DU?$char_traits@D@std@@@std@@V?$span@$$CBUhs_value@@$0PPPPPPPP@@4@@Z");
			// std::span<hs_value const> arguments;
			// __int32 scriptIndex;
			todo("implement");
			_sub_106E8880(name, arguments);
		}
	}
}

extern hs_value _sub_106E8900(short, std::span<hs_value const>);
namespace Scripting
{
	namespace HS
	{
		hs_value ExecuteScriptWithReturn(short scriptIndex, std::span<hs_value const> arguments) // 0x106E8900
		{
			mangled_x86(MANGLED_TODO, "?ExecuteScriptWithReturn@HS@Scripting@@YA?AUhs_value@@FV?$span@$$CBUhs_value@@$0PPPPPPPP@@std@@@Z");
			// static ...; // 0x106E8A84
			// static ...; // 0x106E8A7C
			// short scriptIndex;
			// std::span<hs_value const> arguments;
			// long thread_index;
			// long *retValueAddr;
			// s_hs_script const *script;
			// s_scenario const *scnr;
			// function call : long (*const)(e_hs_script_type, short)
			// function call : void (*const)(long)
			// function call : void (*const)(long)
			todo("implement");
			hs_value __result = _sub_106E8900(scriptIndex, arguments);
			return __result;
		}
	}
}

extern hs_value _sub_106E8B10(std::string_view, std::span<hs_value const>);
namespace Scripting
{
	namespace HS
	{
		hs_value ExecuteScriptWithReturn(std::string_view name, std::span<hs_value const> arguments) // 0x106E8B10
		{
			mangled_x86(MANGLED_TODO, "?ExecuteScriptWithReturn@HS@Scripting@@YA?AUhs_value@@V?$basic_string_view@DU?$char_traits@D@std@@@std@@V?$span@$$CBUhs_value@@$0PPPPPPPP@@5@@Z");
			// std::span<hs_value const> arguments;
			// __int32 scriptIndex;
			todo("implement");
			hs_value __result = _sub_106E8B10(name, arguments);
			return __result;
		}

		_extern void _sub_106E8670(std::string_view, short);
		void AddHookCallback(std::string_view name, short callbackScriptIndex) // 0x106E8670
		{
			mangled_x86(MANGLED_TODO, "?AddHookCallback@HS@Scripting@@YAXV?$basic_string_view@DU?$char_traits@D@std@@@std@@F@Z");
			// short callbackScriptIndex;
			todo("implement");
			_sub_106E8670(name, callbackScriptIndex);
		}

		_extern void _sub_106E9320(std::string_view, short);
		void RemoveHookCallback(std::string_view name, short callbackScriptIndex) // 0x106E9320
		{
			mangled_x86(MANGLED_TODO, "?RemoveHookCallback@HS@Scripting@@YAXV?$basic_string_view@DU?$char_traits@D@std@@@std@@F@Z");
			// short callbackScriptIndex;
			todo("implement");
			_sub_106E9320(name, callbackScriptIndex);
		}

		_extern void _sub_106E86E0(std::string_view, std::span<hs_value const>);
		void CallHook(std::string_view name, std::span<hs_value const> arguments) // 0x106E86E0
		{
			mangled_x86(MANGLED_TODO, "?CallHook@HS@Scripting@@YAXV?$basic_string_view@DU?$char_traits@D@std@@@std@@V?$span@$$CBUhs_value@@$0PPPPPPPP@@4@@Z");
			// std::span<hs_value const> arguments;
			{
				// std::vector<short> &<range>$L0;
				// short *<begin>$L0;
				// short *<end>$L0;
				{
					// __int32 scriptIndex;
				}
			}
			todo("implement");
			_sub_106E86E0(name, arguments);
		}
	}
}

/* ---------- private code */

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_tag_block<s_hs_script>::try_get_element(__int32, s_hs_script **) const;
template bool c_tag_block<s_hs_script_parameter>::try_get_element(__int32, s_hs_script_parameter **) const;
template c_enum<enum e_hs_script_type,short>::operator enum e_hs_script_type() const;
template c_enum<enum e_hs_type,short>::operator enum e_hs_type() const;
template s_hs_script * c_tag_block<s_hs_script>::get_element(__int32) const;
template s_hs_script const & c_tag_block<s_hs_script>::operator[](__int32) const;
template s_hs_script_parameter * c_tag_block<s_hs_script_parameter>::get_element(__int32) const;
template s_hs_script_parameter const & c_tag_block<s_hs_script_parameter>::operator[](__int32) const;
