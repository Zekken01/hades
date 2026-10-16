/* ---------- headers */

#include "hades/hades.h"

#include "Blam/ai/actor.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_events.hpp"
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
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Patches/Events.hpp"
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

struct s_game_engine_event_data;
struct s_multiplayer_event_response_definition;

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Events {}
	using namespace Patches::Events;
	namespace Medals {}
	using namespace Patches::Medals;
}

/* ---------- constants */

/* ---------- definitions */

//struct chud_update_h3_medal_animation_hook::__l2::s_chud_h3_medal_state
//{
//	char Active; // 0x0
//	__int32 field_4; // 0x4
//	__int32 StartTime; // 0x8
//	__int32 InEndTime; // 0xC
//	__int32 Duration; // 0x10
//	char InAnimationFinished; // 0x14
//	__int32 OutPercent; // 0x18
//	__int32 field_1C; // 0x1C
//	__int32 field_20; // 0x20
//	float Opacity; // 0x24
//};
//static_assert(sizeof(chud_update_h3_medal_animation_hook::__l2::s_chud_h3_medal_state) == 40, "Invalid chud_update_h3_medal_animation_hook::__l2::s_chud_h3_medal_state size");

/* ---------- prototypes */

extern long (*const game_seconds_to_ticks_round)(float);  // hades: added for 0x10A8A270
extern long (*const game_time_get)();  // hades: added for 0x10A8A270

namespace Patches
{
	namespace Medals
	{
		extern void ApplyAll();
	}
}

static void OnEvent(unsigned long player, s_game_engine_event_data const *event, s_multiplayer_event_response_definition const *definition);
void __fastcall chud_update_saber_medal_animation_hook(__int32 thisptr, void *unused, __int32 a2);
void __fastcall chud_update_h3_medal_animation_hook(__int32 thisptr, void *unused, __int32 a2);
void sound_enqueue_announcer_sound_hook(unsigned __int32 sndTagIndex, __int32 delayTicks);
void HeadshotHook();

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Patches
{
	namespace Medals
	{
		void ApplyAll() // 0x10A89990
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAll@Medals@Patches@@YAXXZ");

			Patches::Events::OnEvent(::OnEvent);
			Patch::NopFill(Pointer::Base(0x697680), 5);
			Patch::NopFill(Pointer::Base(0x697687), 4);
			Hook(0x6970D6, chud_update_h3_medal_animation_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x6970DE, chud_update_saber_medal_animation_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x2E41D1, sound_enqueue_announcer_sound_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x1A1E70, HeadshotHook).Apply();
		}
	}
}

/* ---------- private code */

static void OnEvent(unsigned long player, s_game_engine_event_data const *event, s_multiplayer_event_response_definition const *definition) // 0x10A89ED0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?OnEvent@@YAXKPBUs_game_engine_event_data@@PBUs_multiplayer_event_response_definition@@@Z");

	if (definition->medal_award && definition->medal_award != -1)
	{
		if (player != ((unsigned long(*)(long))0x589C30)(0))
		{
			return;
		}

		const auto chud_show_medal = (void(*)(__int32, __int32))0xA95A40;

		chud_show_medal(0, definition->medal_award);
	}
}

void __fastcall chud_update_saber_medal_animation_hook(__int32 thisptr, void *unused, __int32 a2) // 0x10A8A430
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?chud_update_saber_medal_animation_hook@@YIXHPAXH@Z");
}

void __fastcall chud_update_h3_medal_animation_hook(__int32 thisptr, void *unused, __int32 a2) // 0x10A8A270
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?chud_update_h3_medal_animation_hook@@YIXHPAXH@Z");

	struct s_chud_h3_medal_state
	{
		char Active;
		__int32 field_4;
		__int32 StartTime;
		__int32 InEndTime;
		__int32 Duration;
		char InAnimationFinished;
		__int32 OutPercent;
		__int32 field_1C;
		__int32 field_20;
		float Opacity;
	};
	void (__thiscall *const chud_update_h3_medal_animation)(__int32, __int32) = reinterpret_cast<void (__thiscall *)(__int32, __int32)>(0xA973F0);
	chud_update_h3_medal_animation(thisptr, a2);
	s_chud_h3_medal_state *medals = (s_chud_h3_medal_state *)thisptr;
	long const fadeOutDuration = game_seconds_to_ticks_round(1.0f);
	for (__int32 i = 0; i < 4; i++)
	{
		if (medals[i].Active && medals[i].InAnimationFinished)
		{
			long dt = game_time_get() - medals[i].StartTime;
			if (dt > 250)
			{
				long fadeOutDelta = dt - 250;
				if (fadeOutDelta > fadeOutDuration)
					medals[i].Active = false;
				float &opacity = medals[i].Opacity;
				opacity = 1.0f - (float)fadeOutDelta / fadeOutDuration;
				if (opacity < 0.0f)
					opacity = 0.0f;
			}
		}
	}
}

void sound_enqueue_announcer_sound_hook(unsigned __int32 sndTagIndex, __int32 delayTicks) // 0x10A8A460
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?sound_enqueue_announcer_sound_hook@@YAXIH@Z");

	void (__cdecl *const sound_enqueue_announcer_sound)(unsigned __int32, __int32) = (void(__cdecl *const)(unsigned __int32, __int32))0x6e4630;

	sound_enqueue_announcer_sound(sndTagIndex, delayTicks);
}

__declspec(naked) void HeadshotHook() // 0x10A89EA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?HeadshotHook@@YAXXZ");

	__asm
	{
		cmp eax, 1
		jnz LNO_MEDAL
		mov eax, [ebp + 18h]
		mov ax, word ptr [eax]
		cmp ax, 10h
		jz LDEFAULT
		cmp ax, 11h
		jz LDEFAULT
		LNO_MEDAL:
		push 5A1ED5h
		ret
		LDEFAULT:
		push 5A1E75h
		ret
	}
}
