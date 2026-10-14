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

namespace hades_file_local { static PlayerNameString *playerNames[16]; }  // hades: added for 0x10ACADA0

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
		void ApplyAll() // 0x10ACA2A0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAll@Scoreboard@Patches@@YAXXZ");
			// procedure flags: nofpo

			// Scoreboard hooks
			Hook(0x301A47, GLScoreboardPlayerAllocatorHook).Apply();
			Hook(0x2F8ED7, GLScoreboardPlayerConstructorHook).Apply();
			Hook(0x310163, ScoreboardUpdateHook).Apply();

			// Local player UID hook (can probably safely be removed)
			// Hook(0x18A1D6, SetLocalPlayerHook).Apply();

			// Set scoreboard UIDs to player datum indexes
			Patch(0x31000F, { 0x3E, 0x8B, 0x4D, 0xC4 }).Apply(); // mov ecx, [ebp - 0x3C]
			Patch::NopFill(Pointer::Base(0x310013), 2);          // nop out leftover data
			Patch(0x310018, { 0x31, 0xC9 }).Apply();             // xor ecx, ecx
			Patch::NopFill(Pointer::Base(0x31001A), 4);          // nop out leftover data

			// Set podium UIDs to player datum indexes
			Patch(0x2E323E, { 0x8B, 0x47, 0x08 }).Apply(); // mov eax, [edi + 8]
			Patch::NopFill(Pointer::Base(0x2E3241), 4);    // nop out leftover data
			Patch(0x2E3248, { 0x31, 0xC0 }).Apply();       // xor eax, eax
			Patch::NopFill(Pointer::Base(0x2E324A), 5);    // nop out leftover data
		}
	}
}

/* ---------- private code */

__int32 GetUtf16Length(char16_t const *str, __int32 maxLength) // 0x10ACAF70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetUtf16Length@@YAHPB_SH@Z");
	// `anonymous-namespace'::GetUtf16Length
	// __int32 maxLength;
	// __int32 length;

	__int32 length = 0;
	while (length < maxLength && str[length])
	{
		length++;
	}
	return length;
}

PlayerNameString *GetPlayerName(s_player_datum *playerData, __int32 index) // 0x10ACADA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetPlayerName@@YAPAUPlayerNameString@hades_file_local@@PAUs_player_datum@@H@Z");
	// `anonymous-namespace'::GetPlayerName
	// __int32 index;
	// void *(*Allocate)(unsigned __int32);
	// __int32 length;
	// void (*Free)(void *);
	// PlayerNameString *result;
	// function call : void (*)(void *)
	// function call : void *(*)(unsigned __int32)

	if (index == -1)
		return nullptr;
	void *(*Allocate)(unsigned __int32) = reinterpret_cast<void *(*)(unsigned __int32)>(0xD874A0);
	void (*Free)(void *) = reinterpret_cast<void (*)(void *)>(0xD873C0);
	if (!playerData->configuration.host.player_name[0])
		return nullptr;
	PlayerNameString *result = playerNames[index];
	if (result && !memcmp(result->name, playerData->configuration.host.player_name, 32))
		return nullptr;
	if (result)
	{
		result->header.refCount--;
		if (result->header.refCount == 0)
		{
			Free(result);
			result = nullptr;
		}
	}
	result = (PlayerNameString *)Allocate(44);
	memset(result, 0, 44);
	result->header.refCount = 1;
	playerNames[index] = result;
	memcpy(result->name, playerData->configuration.host.player_name, 32);
	__int32 length = GetUtf16Length(result->name, 16);
	result->header.length1 = length;
	result->header.length2 = length;
	return playerNames[index];
}

__declspec(naked) void GLScoreboardPlayerAllocatorHook() // 0x10ACAD50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GLScoreboardPlayerAllocatorHook@@YAXXZ");
	// `anonymous-namespace'::GLScoreboardPlayerAllocatorHook
	// procedure flags: nofpo

	__asm
	{
		push 88h
		push 0701A4Eh
		mov edx, 0D87130h
		jmp edx
	}
}

__declspec(naked) void GLScoreboardPlayerConstructorHook() // 0x10ACAD70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GLScoreboardPlayerConstructorHook@@YAXXZ");
	// `anonymous-namespace'::GLScoreboardPlayerConstructorHook
	// procedure flags: nofpo

	__asm
	{
		push esi
		lea ecx, [esi + 7Ch]
		mov byte ptr [ebp - 4], 0Bh
		mov edx, 06B1590h
		call edx
		mov ecx, [ebp - 0Ch]
		mov eax, esi
		mov edx, 06F8EDCh
		jmp edx
	}
}

__declspec(naked) void ScoreboardUpdateHook() // 0x10ACAFC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ScoreboardUpdateHook@@YAXXZ");
	// `anonymous-namespace'::ScoreboardUpdateHook
	// procedure flags: nofpo
// done:

	__asm
	{
		movzx eax, word ptr [ebp - 3Ch]
		push eax
		push esi
		call GetPlayerName
		add esp, 8
		test eax, eax
		je Ldone
		mov [ebp - 14h], eax
		lea eax, [ebp - 14h]
		push eax
		mov eax, [eax]
		inc byte ptr [eax]
		lea ecx, [edi + 7Ch]
		mov eax, 06C4B30h
		call eax
		mov ecx, eax
		mov edx, 06AC840h
		call edx
		mov eax, [ebp - 14h]
		dec byte ptr [eax]
		Ldone:
		lea eax, [ebp - 40h]
		push eax
		push 071016Ch
		mov edx, 055AE30h
		jmp edx
	}
}
