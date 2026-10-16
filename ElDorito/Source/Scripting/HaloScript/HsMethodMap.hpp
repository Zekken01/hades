#ifndef __SCRIPTING_HALOSCRIPT_HSMETHODMAP_HPP__
#define __SCRIPTING_HALOSCRIPT_HSMETHODMAP_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Common/Http/HttpHeaders.hpp"
#include "Patches/PlayerPropertiesExtension.hpp"
#include "Utils/NameValueTable.hpp"
#include "Utils/StlUtil.hpp"
#include "Web/Bridge/WebRendererQueryHandler.hpp"

#include <functional>
#include <initializer_list>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>

/* ---------- forward declarations */

namespace Scripting
{
	namespace HS
	{
		class ScriptMethodMap;
		struct ScriptMethod;
		struct ScriptParameter;
	}
}

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
namespace Scripting
{
	namespace HS
	{
		struct ScriptParameter
		{
			e_hs_type type; // 0x0
			std::string_view name; // 0x4
			std::string_view description; // 0xC
			// ScriptParameter() is compiler generated; not declared so the struct stays an aggregate.
		};
	}
}

#pragma pack(pop)
static_assert(sizeof(Scripting::HS::ScriptParameter) == 20, "Invalid Scripting::HS::ScriptParameter size");

#pragma pack(push, 4)
namespace Scripting
{
	namespace HS
	{
		struct ScriptMethod
		{
			Scripting::HS::ScriptMethodFlags flags; // 0x0
			std::string_view name; // 0x4
			std::string_view description; // 0xC
			e_hs_type returnType; // 0x14
			void (*evaluateProc)(short, long, bool); // 0x18
			std::vector<Scripting::HS::ScriptParameter> parameters; // 0x1C
			// hades: the constructors are implicit, so the struct stays an aggregate -
			// AddMethod builds its method with `= {}`.
			_inline ~ScriptMethod(); /* compiler_generated() */
			Scripting::HS::ScriptMethod &operator=(Scripting::HS::ScriptMethod &); /* compiler_generated() */
			Scripting::HS::ScriptMethod &operator=(Scripting::HS::ScriptMethod const &); /* compiler_generated() */
		};
	}
}

#pragma pack(pop)
static_assert(sizeof(Scripting::HS::ScriptMethod) == 44, "Invalid Scripting::HS::ScriptMethod size");

#pragma pack(push, 4)
namespace Scripting
{
	namespace HS
	{
		class ScriptMethodMap :
			public Utils::Singleton<Scripting::HS::ScriptMethodMap>
		{
		private:
			void AddMethod(Scripting::HS::ScriptMethod &&method);
		public:
			void AddMethod(std::string_view name, std::string_view description, Scripting::HS::ScriptMethodFlags flags, void (*evaluate)(short, long, bool), e_hs_type returnType, std::initializer_list<Scripting::HS::ScriptParameter> parameters);
			Scripting::HS::ScriptMethod const *FindMethod(std::string_view name) const;
			std::string GenerateDocs() const;
			std::string GenerateHelp(Scripting::HS::ScriptMethod const *method);
			std::string GenerateMethodDeclaration(Scripting::HS::ScriptMethod const *method);
			void Finalize();
		private:
			bool m_finalized = false; // 0x0
			std::unordered_map<std::string_view,Scripting::HS::ScriptMethod> m_methods; // 0x4
		public:
			_inline ScriptMethodMap() = default; /* compiler_generated() - defaulted on its
			    first declaration, so it is NOT user-provided and `new ScriptMethodMap()`
			    zero-initializes before constructing, as the original does. */
			~ScriptMethodMap() = default; /* compiler_generated() */
		};
	}
}

#pragma pack(pop)
static_assert(sizeof(Scripting::HS::ScriptMethodMap) == 44, "Invalid Scripting::HS::ScriptMethodMap size");

/* ---------- prototypes */

namespace Scripting
{
	namespace HS
	{
		extern bool ValidIdentifier(std::string_view name);

		extern _inline Scripting::HS::ScriptMethodFlags operator&(Scripting::HS::ScriptMethodFlags lhs, Scripting::HS::ScriptMethodFlags rhs);
	}
}

/* ---------- globals */

/* ---------- public code */

namespace Scripting
{
	namespace HS
	{
		inline Scripting::HS::ScriptMethodFlags operator&(Scripting::HS::ScriptMethodFlags lhs, Scripting::HS::ScriptMethodFlags rhs) // 0x10701240
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??IHS@Scripting@@YA?AW4ScriptMethodFlags@01@W4201@0@Z");

			return static_cast<Scripting::HS::ScriptMethodFlags>(static_cast<int>(lhs) & static_cast<int>(rhs));
		}
	}
}

/* ---------- private code */

#endif // __SCRIPTING_HALOSCRIPT_HSMETHODMAP_HPP__
