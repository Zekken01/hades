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

namespace Patches
{
	namespace Medals
	{
		extern void ApplyAll();
	}
}

void OnEvent(unsigned long player, s_game_engine_event_data const *event, s_multiplayer_event_response_definition const *definition);
void chud_update_saber_medal_animation_hook(__int32 thisptr, void *unused, __int32 a2);
void chud_update_h3_medal_animation_hook(__int32 thisptr, void *unused, __int32 a2);
void sound_enqueue_announcer_sound_hook(unsigned __int32 sndTagIndex, __int32 delayTicks);
void HeadshotHook();

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Patches
{
	namespace Medals
	{
		_extern void _sub_10A89990();
		void ApplyAll() // 0x10A89990
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@Medals@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10A89990();
		}
	}
}

/* ---------- private code */

_extern void _sub_10A89ED0(unsigned long, s_game_engine_event_data const *, s_multiplayer_event_response_definition const *);
void OnEvent(unsigned long player, s_game_engine_event_data const *event, s_multiplayer_event_response_definition const *definition) // 0x10A89ED0
{
	// `anonymous-namespace'::OnEvent
	// s_multiplayer_event_response_definition const *definition;
	{
		// void (*const chud_show_medal)(__int32, __int32);
	}
	// function call : unsigned long (*const)(long)
	// function call : void (*const)(__int32, __int32)
	todo("implement");
	_sub_10A89ED0(player, event, definition);
}

_extern void _sub_10A8A430(__int32, void *, __int32);
void chud_update_saber_medal_animation_hook(__int32 thisptr, void *unused, __int32 a2) // 0x10A8A430
{
	// `anonymous-namespace'::chud_update_saber_medal_animation_hook
	// __int32 a2;
	todo("implement");
	_sub_10A8A430(thisptr, unused, a2);
}

_extern void _sub_10A8A270(__int32, void *, __int32);
void chud_update_h3_medal_animation_hook(__int32 thisptr, void *unused, __int32 a2) // 0x10A8A270
{
	// `anonymous-namespace'::chud_update_h3_medal_animation_hook
	// __int32 a2;
	// void (*const chud_update_h3_medal_animation)(__int32, __int32);
	// chud_update_h3_medal_animation_hook::__l2::s_chud_h3_medal_state *medals;
	// long const fadeOutDuration;
	{
		// __int32 i;
		{
			// long dt;
			{
				// float &opacity;
				// long fadeOutDelta;
			}
		}
	}
	// function call : void (*const)(__int32, __int32)
	// function call : long (*const)(float)
	// function call : long (*const)()
	todo("implement");
	_sub_10A8A270(thisptr, unused, a2);
}

_extern void _sub_10A8A460(unsigned __int32, __int32);
void sound_enqueue_announcer_sound_hook(unsigned __int32 sndTagIndex, __int32 delayTicks) // 0x10A8A460
{
	// `anonymous-namespace'::sound_enqueue_announcer_sound_hook
	// __int32 delayTicks;
	// void (*const sound_enqueue_announcer_sound)(unsigned __int32, __int32);
	// function call : void (*const)(unsigned __int32, __int32)
	todo("implement");
	_sub_10A8A460(sndTagIndex, delayTicks);
}

extern void _sub_10A89EA0();
__declspec(naked) void HeadshotHook() // 0x10A89EA0
{
	// `anonymous-namespace'::HeadshotHook
	// procedure flags: nofpo
// DEFAULT:
// NO_MEDAL:
	todo("implement");
	_sub_10A89EA0();
}
