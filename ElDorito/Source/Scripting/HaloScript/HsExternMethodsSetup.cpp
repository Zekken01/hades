/* ---------- headers */

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
#include "Common/Http/HttpHeaders.hpp"
#include "Scripting/HaloScript/HsMethodMap.hpp"
#include "Utils/Singleton.hpp"

#include "Utils/Logger.hpp"  // hades: added for 0x106EED90
#include <format>  // hades: added for 0x106EED90

#include <boost/asio.hpp>
#include <boost/assert.hpp>
#include <boost/exception/all.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/parameter/aux_/use_default_tag.hpp>
#include <boost/throw_exception.hpp>

#include <Windows.h>
#include <boost/align/detail/align_up.hpp>
#include <boost/align/detail/is_alignment.hpp>
#include <boost/current_function.hpp>
#include <boost/mp11/algorithm.hpp>
#include <boost/mp11/detail/mp_count.hpp>
#include <boost/parameter/aux_/void.hpp>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <algorithm>
#include <atomic>
#include <charconv>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <functional>
#include <iterator>
#include <limits>
#include <list>
#include <memory>
#include <mutex>
#include <ratio>
#include <stdexcept>
#include <stop_token>
#include <string>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <unordered_map>
#include <utility>
#include <vector>

/* ---------- forward declarations */

struct begin;
struct end;
struct s_hs_script;
struct s_hs_script_parameter;
struct s_scenario;
namespace Scripting
{
	namespace HS
	{
		class ScriptMethodMap;
		struct ScriptMethod;
		struct ScriptParameter;
	}
}

namespace Utils {}
using namespace ::Utils;
namespace Scripting {}
using namespace ::Scripting;
namespace Scripting
{
	namespace HS {}
	using namespace Scripting::HS;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Scripting
{
	namespace HS
	{
		extern void ValidateExternScript(s_hs_script const *script, Scripting::HS::ScriptMethod const *method, std::vector<std::string> &errors);
		extern void InitializeMethodsForNewMap();
	}
}

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Scripting
{
	namespace HS
	{
		void ValidateExternScript(s_hs_script const *script, Scripting::HS::ScriptMethod const *method, std::vector<std::string> &errors) // 0x106EF0C0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ValidateExternScript@HS@Scripting@@YAXPBUs_hs_script@@PBUScriptMethod@12@AAV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@@Z");

			errors.clear();
			if (script->parameters.count != method->parameters.size())
				errors.push_back(std::format("Parameter count mismatch: {} <-> {}", reinterpret_cast<long const &>(script->parameters.count), (__int32)method->parameters.size()));
			if (script->return_type != method->returnType)
				errors.push_back(std::format("Return type mismatch: {} <-> {}", hs_get_type_name(script->return_type), hs_get_type_name(method->returnType)));
			if (script->parameters.count == method->parameters.size())
			{
				for (__int32 i = 0; i < script->parameters.count; i++)
				{
					s_hs_script_parameter const &scriptParam = script->parameters[i];
					Scripting::HS::ScriptParameter const &methodParam = method->parameters[i];
					if (script->parameters[i].type != method->parameters[i].type)
						errors.push_back(std::format("Parameter: '{}' type mismatch: {} <-> {}", methodParam.name, hs_get_type_name(scriptParam.type), hs_get_type_name(methodParam.type)));
				}
			}
		}

		void InitializeMethodsForNewMap() // 0x106EED90
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?InitializeMethodsForNewMap@HS@Scripting@@YAXXZ");

			Scripting::HS::ScriptMethodMap &methodMap = Utils::Singleton<Scripting::HS::ScriptMethodMap>::Instance();
			std::vector<std::string> validationErrors;
			s_scenario *scnr = global_scenario_get();
			for (__int32 i = 0; i < scnr->scripts.count; i++)
			{
				s_hs_script *script = &scnr->scripts[i];
				if (script->type != _hs_script_type_extern)
					continue;
				script->root_expression_index = 0;
				Scripting::HS::ScriptMethod const *method = methodMap.FindMethod(script->name.ascii);
				if (method)
				{
					ValidateExternScript(script, method, validationErrors);
					for (std::string const &error : validationErrors)
						Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Game, Utils::LogLevel::Warning, std::format("HS :: Validation failed for extern method '{}'. {}.", method->name, error));
					script->extern_method = (void *)method;
				}
				else
					Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Game, Utils::LogLevel::Warning, std::format("HS :: Script references extern method '{}' but was not found.", script->name.ascii));
			}
		}
	}
}

/* ---------- private code */

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_enum<enum e_hs_script_type,short>::operator!=(e_hs_script_type const &) const;
template bool c_enum<enum e_hs_script_type,short>::operator==(e_hs_script_type const &) const;
template bool c_enum<enum e_hs_type,short>::operator!=(e_hs_type const &) const;
template bool c_enum<enum e_hs_type,short>::operator==(e_hs_type const &) const;
template s_hs_script & c_tag_block<s_hs_script>::operator[](__int32);
