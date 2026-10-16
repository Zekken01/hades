/* ---------- headers */

#include "hades/hades.h"

#include "Blam/animations/animation_manager.hpp"
#include "Blam/animations/mixing_board/channels/animation_channel.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Pointer.hpp"
#include "Utils/Singleton.hpp"

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

struct c_animation_manager;
struct c_animation_channel;

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Animation {}
	using namespace Patches::Animation;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern float (*const game_tick_length)();  // hades: added for 0x1090D950
#include "Modules/ModulePlayer.hpp"  // hades: added for 0x1090D950

extern float animation_get_frames_per_second();
extern bool __fastcall c_animation_manager__update_animation_channel_hook(c_animation_channel *thisptr, void const *__formal, c_animation_manager *animation_manager, float a3, float a4);
namespace Patches
{
	namespace Animation
	{
		extern void ApplyAll();
	}
}

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

float animation_get_frames_per_second() // 0x1090D930
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?animation_get_frames_per_second@@YAMXZ");

	return *(float *)0x1615f34;
}

bool __fastcall c_animation_manager__update_animation_channel_hook(c_animation_channel *thisptr, void const *__formal, c_animation_manager *animation_manager, float a3, float a4) // 0x1090D950
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_animation_manager__update_animation_channel_hook@@YI_NPAUc_animation_channel@@PBXPAUc_animation_manager@@MM@Z");

	thisptr->field_34 |= thisptr->field_2C;
	thisptr->field_2C = 0;
	if (thisptr->initialized && thisptr->settings.graph_definition_index != -1 && thisptr->settings.animation_id.animation_index >= 0 && (thisptr->settings.playback_flags & 1) && !(thisptr->state_flags & 5))
	{
		float t = thisptr->playback_speed * animation_get_frames_per_second();
		if (thisptr->settings.animation_name == 0x5FE && Utils::Singleton<Modules::ModulePlayer>::Instance().VarSprintAnimationHack->ValueInt)
			t *= 0.5f;
		return ((bool (__thiscall *)(c_animation_channel *, float, c_animation_manager *, float, float))0x9843B0)(thisptr, game_tick_length() * t + thisptr->frame_position, animation_manager, a3, a4);
	}
	else
		return false;
}

namespace Patches
{
	namespace Animation
	{
		void ApplyAll() // 0x1090D7D0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAll@Animation@Patches@@YAXXZ");

			Hook(0x584010, c_animation_manager__update_animation_channel_hook).Apply();
		}
	}
}

/* ---------- private code */
