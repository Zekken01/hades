/* ---------- headers */

#include "hades/hades.h"

#include "Blam/ai/actor.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Forge/ForgeUndo.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Pointer.hpp"

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
#include <initializer_list>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <streambuf>
#include <system_error>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

struct s_player_datum;
namespace hades_file_local
{
	struct SslWStringHeader;
	struct PlayerNameString;
}
using namespace hades_file_local;

namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Scoreboard {}
	using namespace Patches::Scoreboard;
}

/* ---------- constants */

/* ---------- definitions */

namespace hades_file_local
{
	struct SslWStringHeader
	{
		__int32 refCount; // 0x0
		__int32 length1; // 0x4
		__int32 length2; // 0x8
	};
	static_assert(sizeof(SslWStringHeader) == 12, "Invalid SslWStringHeader size");

	struct PlayerNameString
	{
		SslWStringHeader header; // 0x0
		char16_t name[16]; // 0xC
	};
}
using namespace hades_file_local;
// static_assert(sizeof(PlayerNameString) == 44, "Invalid PlayerNameString size");
// The layout above is the PDB's member list without its padding, so the
// size assertion is withheld: it would fail on alignment alone.

/* ---------- prototypes */

namespace Patches
{
	namespace Scoreboard
	{
		extern void ApplyAll();
	}
}

__int32 GetUtf16Length(char16_t const *str, __int32 maxLength);
PlayerNameString *GetPlayerName(s_player_datum *playerData, __int32 index);
void GLScoreboardPlayerAllocatorHook();
void GLScoreboardPlayerConstructorHook();
void ScoreboardUpdateHook();

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Patches
{
	namespace Scoreboard
	{
		_extern void _sub_10ACA2A0();
		void ApplyAll() // 0x10ACA2A0
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@Scoreboard@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10ACA2A0();
		}
	}
}

/* ---------- private code */

_extern __int32 _sub_10ACAF70(char16_t const *, __int32);
__int32 GetUtf16Length(char16_t const *str, __int32 maxLength) // 0x10ACAF70
{
	// `anonymous-namespace'::GetUtf16Length
	// __int32 maxLength;
	// __int32 length;
	todo("implement");
	__int32 __result = _sub_10ACAF70(str, maxLength);
	return __result;
}

extern PlayerNameString *_sub_10ACADA0(s_player_datum *, __int32);
PlayerNameString *GetPlayerName(s_player_datum *playerData, __int32 index) // 0x10ACADA0
{
	// `anonymous-namespace'::GetPlayerName
	// __int32 index;
	// void *(*Allocate)(unsigned __int32);
	// __int32 length;
	// void (*Free)(void *);
	// PlayerNameString *result;
	// function call : void (*)(void *)
	// function call : void *(*)(unsigned __int32)
	todo("implement");
	PlayerNameString * __result = _sub_10ACADA0(playerData, index);
	return __result;
}

extern void _sub_10ACAD50();
__declspec(naked) void GLScoreboardPlayerAllocatorHook() // 0x10ACAD50
{
	// `anonymous-namespace'::GLScoreboardPlayerAllocatorHook
	// procedure flags: nofpo
	todo("implement");
	_sub_10ACAD50();
}

extern void _sub_10ACAD70();
__declspec(naked) void GLScoreboardPlayerConstructorHook() // 0x10ACAD70
{
	// `anonymous-namespace'::GLScoreboardPlayerConstructorHook
	// procedure flags: nofpo
	todo("implement");
	_sub_10ACAD70();
}

extern void _sub_10ACAFC0();
__declspec(naked) void ScoreboardUpdateHook() // 0x10ACAFC0
{
	// `anonymous-namespace'::ScoreboardUpdateHook
	// procedure flags: nofpo
// done:
	todo("implement");
	_sub_10ACAFC0();
}
