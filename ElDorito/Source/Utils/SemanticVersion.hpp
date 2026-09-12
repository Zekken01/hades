#ifndef __UTILS_SEMANTICVERSION_HPP__
#define __UTILS_SEMANTICVERSION_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include <memory>
#include <string>
#include <string_view>

/* ---------- forward declarations */

namespace Utils
{
	struct SemanticVersion;
}

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
namespace Utils
{
	struct SemanticVersion
	{
		__int32 major; // 0x0
		__int32 minor; // 0x4
		__int32 patch; // 0x8
		std::string prerelease; // 0xC
		std::string build; // 0x28
		SemanticVersion(Utils::SemanticVersion &);
		SemanticVersion(Utils::SemanticVersion const &);
		SemanticVersion(__int32 major, __int32 minor, __int32 patch, std::string prerelease, std::string build);
		_inline Utils::SemanticVersion &operator=(Utils::SemanticVersion &&__that);
		Utils::SemanticVersion &operator=(Utils::SemanticVersion const &);
		_inline ~SemanticVersion();
		static bool TryParse(std::string const &input, Utils::SemanticVersion &outVersion);
		static Utils::SemanticVersion Parse(std::string const &input);
	private:
		static __int32 Compare(Utils::SemanticVersion const &a, Utils::SemanticVersion const &b);
	public:
		__int32 Compare(Utils::SemanticVersion const &) const;
		std::string ToString() const;
	private:
		static __int32 ComparePrerelease(std::string_view const &a, std::string_view const &b);
		static __int32 CompareIdentifier(std::string_view const &a, std::string_view const &b);
		static bool ParseNumericIdentifier(std::string_view const &input, __int32 &value);
	public:
		void __dflt_ctor_closure(); /* compiler_generated() */
	};
}

#pragma pack(pop)
static_assert(sizeof(Utils::SemanticVersion) == 68, "Invalid Utils::SemanticVersion size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

namespace Utils
{
	extern SemanticVersion &_sub_10765120(Utils::SemanticVersion *const, Utils::SemanticVersion &);
	_inline Utils::SemanticVersion &SemanticVersion::operator=(Utils::SemanticVersion &&__that) // 0x10765120
	{
		mangled_x86(MANGLED_TODO, "??4SemanticVersion@Utils@@QAEAAU01@$$QAU01@@Z");
		// Utils::SemanticVersion &__that;
		todo("implement");
		Utils::SemanticVersion & __result = _sub_10765120(this, __that);
		return __result;
	}

	_inline SemanticVersion::~SemanticVersion() // 0x10764570
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??1SemanticVersion@Utils@@QAE@XZ");
		// Utils::SemanticVersion *const this;
	}
}

/* ---------- private code */

#endif // __UTILS_SEMANTICVERSION_HPP__
