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

#include "Patches/Core.hpp"  // hades: added for 0x106E8C80

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

namespace eldorado
{
	// Functions in eldorado.exe, named as in ManagedDonkey.
	static auto const hs_evaluate_runtime = reinterpret_cast<bool (*)(long, long, long, long *)>(0x594510);
	static auto const hs_stack_allocate = reinterpret_cast<void *(*)(long, long, long, short *)>(0x5987D0);
	static auto const hs_thread_delete = reinterpret_cast<void (*)(long)>(0x598A60);
	static auto const hs_thread_main = reinterpret_cast<void (*)(long)>(0x598BC0);
	static auto const hs_thread_new = reinterpret_cast<long (*)(e_hs_script_type, short)>(0x598E70);
}

unsigned long system_milliseconds();  // hades: added for 0X106E9390

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
		std::unordered_map<std::string_view,Scripting::HS::ScriptHook> hooks; // 0x1138827C
	}
}

/* ---------- private variables */

/* ---------- public code */

namespace Scripting
{
	namespace HS
	{
		_inline void ScriptHook::AddCallback(short callback) // 0x106E84C0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?AddCallback@ScriptHook@HS@Scripting@@QAEXF@Z");

			if (auto it = std::find(callbacks.begin(), callbacks.end(), callback); it != callbacks.end())
				return;
			callbacks.push_back(callback);
		}

		_inline void ScriptHook::RemoveCallback(short callback) // 0x106E91E0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?RemoveCallback@ScriptHook@HS@Scripting@@QAEXF@Z");

			callbacks.erase(std::remove(callbacks.begin(), callbacks.end(), callback));
		}
	}
}


namespace Scripting
{
	namespace HS
	{
		char const *MarshalString(__int32 threadIndex, std::string_view str) // 0x106E8E10
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?MarshalString@HS@Scripting@@YAPBDHV?$basic_string_view@DU?$char_traits@D@std@@@std@@@Z");

			char *mem = (char *)HsThreadStorageManager::Get()->MemAlloc(threadIndex, str.size() + 1);
			memcpy(mem, &str[0], str.size() + 1);
			return mem;
		}
	}
}


namespace Scripting
{
	namespace HS
	{
		hs_value MarshalArgument(long threadIndex, e_hs_type type, hs_value const &value) // 0x106E8D50
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?MarshalArgument@HS@Scripting@@YA?AUhs_value@@JW4e_hs_type@@ABU3@@Z");

			switch (type)
			{
			case _hs_type_string:
				return hs_value::from_string(MarshalString(threadIndex, *(char const **)&value));
			}
			return value;
		}
	}
}


namespace Scripting
{
	namespace HS
	{
		hs_value MarshalReturn(long threadIndex, e_hs_type type, hs_value value) // 0x106E8DF0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?MarshalReturn@HS@Scripting@@YA?AUhs_value@@JW4e_hs_type@@U3@@Z");

			return value;
		}

		__int32 FindScriptByName(std::string_view name) // 0x106E8BB0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?FindScriptByName@HS@Scripting@@YAHV?$basic_string_view@DU?$char_traits@D@std@@@std@@@Z");

			s_scenario const *scnr = global_scenario_get();
			for (__int32 i = 0; i < scnr->scripts.count; i++)
			{
				if (name == scnr->scripts[i].name.ascii)
					return i;
			}
			return -1;
		}

		void InitializeForNewMap() // 0x106E8CF0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?InitializeForNewMap@HS@Scripting@@YAXXZ");

			Scripting::HS::HsThreadStorageManager::Get()->Reset();
			Scripting::HS::hooks.clear();
		}

		void Init() // 0x106E8C80
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Init@HS@Scripting@@YAXXZ");

			Patches::Core::OnMapLoaded([](char const *map)
			{
				InitializeForNewMap();
			});
		}

		void Tick() // 0x106E9390
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Tick@HS@Scripting@@YAXXZ");

			unsigned int time = system_milliseconds();
			Scripting::HS::HsThreadStorageManager::Get()->Update(time);
		}

		void PushScript(long threadIndex, short scriptIndex, long **outReturnValueAddr, std::span<hs_value const> arguments) // 0x106E8EE0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?PushScript@HS@Scripting@@YAXJFPAPAJV?$span@$$CBUhs_value@@$0PPPPPPPP@@std@@@Z");

			s_scenario const *scnr = global_scenario_get();
			if (scriptIndex < 0 || scriptIndex >= scnr->scripts.count)
				return;
			s_hs_script const *script = &scnr->scripts[scriptIndex];
			s_hs_thread *thread = hs_thread_get(threadIndex);
			short stack_offset;
			short args_stack_offset;
			long *arg_count = (long *)eldorado::hs_stack_allocate(threadIndex, 2, 2, nullptr);
			long *next_expression_index = (long *)eldorado::hs_stack_allocate(threadIndex, 4, 2, nullptr);
			long *return_value = (long *)eldorado::hs_stack_allocate(threadIndex, 4, 2, &stack_offset);
			long *args = (long *)eldorado::hs_stack_allocate(threadIndex, arguments.size() * 4, 2, &args_stack_offset);
			*arg_count = arguments.size();
			*next_expression_index = -1;
			for (long i = 0; i < script->parameters.count; i++)
				args[i] = MarshalArgument(threadIndex, script->parameters[i].type, arguments[i]).long_value;
			eldorado::hs_evaluate_runtime(threadIndex, script->root_expression_index, (stack_offset << 16) | 1, nullptr);
			hs_stack_frame *stack = hs_thread_stack(threadIndex);
			stack->script_index = scriptIndex;
			stack->parameters = args_stack_offset;
			if (outReturnValueAddr)
				*outReturnValueAddr = return_value;
		}

		void ExecuteScript(__int32 scriptIndex, std::span<hs_value const> arguments) // 0x106E8790
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ExecuteScript@HS@Scripting@@YAXHV?$span@$$CBUhs_value@@$0PPPPPPPP@@std@@@Z");

			s_scenario const *scnr = global_scenario_get();
			if (scriptIndex < 0 || scriptIndex >= scnr->scripts.count)
				return;
			s_hs_script const *script = &scnr->scripts[scriptIndex];
			long thread_index = eldorado::hs_thread_new(script->type, -1);
			if (thread_index == -1)
				return;
			PushScript(thread_index, scriptIndex, nullptr, arguments);
		}

		// mangled_x86(MANGLED_DEFAULT, "??0ScriptHook@HS@Scripting@@QAE@XZ"); no body to assert in
		// _inline ScriptHook::ScriptHook() = default; // 0x106E7570  // hades: defaulted on its declaration

		// mangled_x86(MANGLED_DEFAULT, "??1ScriptHook@HS@Scripting@@QAE@XZ"); no body to assert in
		_inline ScriptHook::~ScriptHook() = default; // 0x106E7CC0

		void ExecuteScript(std::string_view name, std::span<hs_value const> arguments) // 0x106E8880
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ExecuteScript@HS@Scripting@@YAXV?$basic_string_view@DU?$char_traits@D@std@@@std@@V?$span@$$CBUhs_value@@$0PPPPPPPP@@4@@Z");

			__int32 scriptIndex = FindScriptByName(name);
			if (scriptIndex != -1)
				ExecuteScript(scriptIndex, arguments);
		}
	}
}


namespace Scripting
{
	namespace HS
	{
		hs_value ExecuteScriptWithReturn(short scriptIndex, std::span<hs_value const> arguments) // 0x106E8900
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ExecuteScriptWithReturn@HS@Scripting@@YA?AUhs_value@@FV?$span@$$CBUhs_value@@$0PPPPPPPP@@std@@@Z");

			s_scenario const *scnr = global_scenario_get();
			if (scriptIndex < 0 || scriptIndex >= scnr->scripts.count)
				return hs_value{};
			s_hs_script const *script = &scnr->scripts[scriptIndex];
			long thread_index = eldorado::hs_thread_new(script->type, -1);
			if (thread_index == -1)
				return hs_value{};
			long *retValueAddr = nullptr;
			PushScript(thread_index, scriptIndex, &retValueAddr, arguments);
			eldorado::hs_thread_main(thread_index);
			eldorado::hs_thread_delete(thread_index);
			return MarshalReturn(thread_index, script->return_type, hs_value::from_long(*retValueAddr));
		}
	}
}


namespace Scripting
{
	namespace HS
	{
		hs_value ExecuteScriptWithReturn(std::string_view name, std::span<hs_value const> arguments) // 0x106E8B10
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ExecuteScriptWithReturn@HS@Scripting@@YA?AUhs_value@@V?$basic_string_view@DU?$char_traits@D@std@@@std@@V?$span@$$CBUhs_value@@$0PPPPPPPP@@5@@Z");

			__int32 scriptIndex = FindScriptByName(name);
			if (scriptIndex != -1)
				return ExecuteScriptWithReturn((short)scriptIndex, arguments);
			return {};
		}

		void AddHookCallback(std::string_view name, short callbackScriptIndex) // 0x106E8670
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?AddHookCallback@HS@Scripting@@YAXV?$basic_string_view@DU?$char_traits@D@std@@@std@@F@Z");

			hooks[name].AddCallback(callbackScriptIndex);
		}

		void RemoveHookCallback(std::string_view name, short callbackScriptIndex) // 0x106E9320
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?RemoveHookCallback@HS@Scripting@@YAXV?$basic_string_view@DU?$char_traits@D@std@@@std@@F@Z");

			hooks[name].RemoveCallback(callbackScriptIndex);
		}

		void CallHook(std::string_view name, std::span<hs_value const> arguments) // 0x106E86E0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?CallHook@HS@Scripting@@YAXV?$basic_string_view@DU?$char_traits@D@std@@@std@@V?$span@$$CBUhs_value@@$0PPPPPPPP@@4@@Z");

			for (__int32 scriptIndex : hooks[name].callbacks)
				ExecuteScript(scriptIndex, arguments);
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
