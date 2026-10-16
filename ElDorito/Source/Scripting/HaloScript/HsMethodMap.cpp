/* ---------- headers */

#include "Scripting/HaloScript/HsMethodMap.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Utils/NameValueTable.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/StlUtil.hpp"
#include "Utils/String.hpp"
#include "Web/Bridge/WebRendererQueryHandler.hpp"

#include <format>  // hades: added for 0x10701E90  // hades: added for 0x10701E90

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <atomic>
#include <charconv>
#include <cmath>
#include <cstddef>
#include <cstdlib>
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
#include <mutex>
#include <ostream>
#include <ratio>
#include <sstream>
#include <stdexcept>
#include <stop_token>
#include <streambuf>
#include <string>
#include <string_view>
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
		extern bool ValidIdentifier(std::string_view name);
	}
}

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Scripting
{
	namespace HS
	{
		bool ValidIdentifier(std::string_view name) // 0x10702520
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ValidIdentifier@HS@Scripting@@YA_NV?$basic_string_view@DU?$char_traits@D@std@@@std@@@Z");

			if (name.empty())
				return false;
			if (!isalpha(name[0]))
				return false;
			for (unsigned __int32 i = 0; i < name.size(); i++)
			{
				if (name[i] == '_')
					continue;
				if (!isalnum(name[i]) || !islower(name[i]))
					return false;
			}
			return true;
		}

#line 124
		void ScriptMethodMap::AddMethod(Scripting::HS::ScriptMethod &&method) // 0x10701260
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?AddMethod@ScriptMethodMap@HS@Scripting@@AAEX$$QAUScriptMethod@23@@Z");
#line 132

			#line 126 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Scripting\\HaloScript\\HsMethodMap.cpp"
			assert(!m_finalized && "A method cannot be added after Finalize() has been called");

			if (method.name.length() > 30)
				assert(!"A method name must be 30 characters or less");

			assert(ValidIdentifier(method.name));

			if (method.description.empty())
				assert(!"A method must have a description");
			else if (!method.evaluateProc)
				assert(!"A method must have an evaluate function");



			else if ((method.flags & HostOnly) && (method.flags & NetworkSafe))
				assert(!"A method cannot be flagged as both 'HostOnly' and 'NetworkSafe'");
			else
			{
				if ((int)method.parameters.size() > 16)
					assert(!"The method has too many parameters");

				for (auto const &parameter : method.parameters)
					assert(ValidIdentifier(parameter.name));


				if (m_methods.find(method.name) != m_methods.end())
					assert(!"A method with that name has already been added.");
				m_methods.emplace(method.name, method);
			}
			#line 164 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Scripting\\HaloScript\\HsMethodMap.cpp"
		}

		// mangled_x86(MANGLED_DEFAULT, "??0ScriptMethod@HS@Scripting@@QAE@ABU012@@Z"); no body to assert in
		// _inline ScriptMethod::ScriptMethod(Scripting::HS::ScriptMethod const &__that) = default; // 0x10700770  // hades: implicit (ScriptMethod is an aggregate)

		void ScriptMethodMap::AddMethod(std::string_view name, std::string_view description, Scripting::HS::ScriptMethodFlags flags, void (*evaluate)(short, long, bool), e_hs_type returnType, std::initializer_list<Scripting::HS::ScriptParameter> parameters) // 0x10701690
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?AddMethod@ScriptMethodMap@HS@Scripting@@QAEXV?$basic_string_view@DU?$char_traits@D@std@@@std@@0W4ScriptMethodFlags@23@P6AXFJ_N@ZW4e_hs_type@@V?$initializer_list@UScriptParameter@HS@Scripting@@@5@@Z");

			ScriptMethod method = {};
			method.name = name;
			method.description = description;
			method.flags = flags;
			method.evaluateProc = evaluate;
			method.returnType = returnType;
			method.parameters = parameters;
			AddMethod(std::move(method));
		}

#line 188
		Scripting::HS::ScriptMethod const *ScriptMethodMap::FindMethod(std::string_view name) const // 0x10701880
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?FindMethod@ScriptMethodMap@HS@Scripting@@QBEPBUScriptMethod@23@V?$basic_string_view@DU?$char_traits@D@std@@@std@@@Z");
#line 196

			#line 190 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Scripting\\HaloScript\\HsMethodMap.cpp"
				assert(m_finalized && "Finalize() must be called first.");
				#line 200 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Scripting\\HaloScript\\HsMethodMap.cpp"
			if (auto it = m_methods.find(name); it != m_methods.end())
				return &it->second;
			return nullptr;
		}
	}
}


namespace Scripting
{
	namespace HS
	{
		std::string ScriptMethodMap::GenerateHelp(Scripting::HS::ScriptMethod const *method) // 0x10701E00
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GenerateHelp@ScriptMethodMap@HS@Scripting@@QAE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PBUScriptMethod@23@@Z");

			return std::string(method->description);
		}
	}
}


namespace Scripting
{
	namespace HS
	{
		std::string ScriptMethodMap::GenerateMethodDeclaration(Scripting::HS::ScriptMethod const *method) // 0x10701E90
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GenerateMethodDeclaration@ScriptMethodMap@HS@Scripting@@QAE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PBUScriptMethod@23@@Z");

			if (!method)
				return "(null)";
			std::string_view returnType = hs_get_type_name(method->returnType);
			if (method->parameters.empty())
			{
				return std::format("(script extern {} {})", returnType, method->name);
			}
			else
			{
				std::stringstream ss;
				for (unsigned __int32 i = 0; i < method->parameters.size(); i++)
				{
					std::string_view type = hs_get_type_name(method->parameters[i].type);
					std::string typeStr(type);
					Utils::String::ReplaceString(typeStr, " ", "_");
					typeStr.erase(std::remove(typeStr.begin(), typeStr.end(), '_'), typeStr.end());
					ss << std::format("({} {})", typeStr, method->parameters[i].name);
					if (i < method->parameters.size() - 1)
						ss << " ";
				}
				std::string parameters = ss.str();
				return std::format("(script extern {} ({} {}))", returnType, method->name, parameters);
			}
		}
	}
}


namespace Scripting
{
	namespace HS
	{
#line 277
		std::string ScriptMethodMap::GenerateDocs() const // 0x10701A20
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GenerateDocs@ScriptMethodMap@HS@Scripting@@QBE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
#line 293

			#line 279 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Scripting\\HaloScript\\HsMethodMap.cpp"
				assert(m_finalized && "Finalize() must be called before generating documentation.");
				#line 297 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Scripting\\HaloScript\\HsMethodMap.cpp"
			std::stringstream docs;
			ScriptMethodMap &methods = Utils::Singleton<ScriptMethodMap>::Instance();
			for (auto const &[name, method] : methods.m_methods)
			{
				if (method.flags & (ScriptMethodFlags)8)
					continue;
				docs << methods.GenerateMethodDeclaration(&method) << "\n";
				docs << method.description << "\n";
				if (method.flags & ScriptMethodFlags::HostOnly)
					docs << "NETWORK SAFE: Host Only\n";
				else if (method.flags & ScriptMethodFlags::NetworkSafe)
					docs << "NETWORK SAFE: Yes\n";
				else
					docs << "NETWORK SAFE: Unknown\n";
				docs << "\n";
			}
			return docs.str();
		}

		void ScriptMethodMap::Finalize() // 0x107017F0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Finalize@ScriptMethodMap@HS@Scripting@@QAEXXZ");
#line 320

			#line 318 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Scripting\\HaloScript\\HsMethodMap.cpp"
				assert(!m_finalized && "Finalize() has already been called");
				#line 324 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Scripting\\HaloScript\\HsMethodMap.cpp"
			m_finalized = true;
		}
	}
}

/* ---------- private code */
