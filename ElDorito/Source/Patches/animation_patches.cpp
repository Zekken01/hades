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

_extern float _sub_1090D930();
float animation_get_frames_per_second() // 0x1090D930
{
	mangled_x86(MANGLED_TODO, "?animation_get_frames_per_second@@YAMXZ");
	// procedure flags: nofpo
	todo("implement");
	float __result = _sub_1090D930();
	return __result;
}

_extern bool _sub_1090D950(c_animation_channel *, void const *, c_animation_manager *, float, float);
bool __fastcall c_animation_manager__update_animation_channel_hook(c_animation_channel *thisptr, void const *__formal, c_animation_manager *animation_manager, float a3, float a4) // 0x1090D950
{
	mangled_x86(MANGLED_TODO, "?c_animation_manager__update_animation_channel_hook@@YI_NPAUc_animation_channel@@PBXPAUc_animation_manager@@MM@Z");
	// float a4;
	// constexpr bool (*const `c_animation_manager__update_animation_channel_hook'::`2'::c_animation_channel__update_to_frame_position)(c_animation_channel *, float, c_animation_manager *, float, float); // constant == 9978800
	{
		// float t;
	}
	// function call : float (*const)()
	// function call : bool (*const)(c_animation_channel *, float, c_animation_manager *, float, float)
	todo("implement");
	bool __result = _sub_1090D950(thisptr, __formal, animation_manager, a3, a4);
	return __result;
}

namespace Patches
{
	namespace Animation
	{
		_extern void _sub_1090D7D0();
		void ApplyAll() // 0x1090D7D0
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@Animation@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_1090D7D0();
		}
	}
}

/* ---------- private code */
