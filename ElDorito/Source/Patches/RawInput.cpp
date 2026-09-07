/* ---------- headers */

#include "hades/hades.h"

#include "Blam/BlamInput.hpp"
#include "Blam/camera/director.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/main/game_preferences.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/data_array.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/render/camera_fx_settings.hpp"
#include "Blam/render/views/render_player_view.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "ElDorito.hpp"
#include "Forge/Geoemetry.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Pointer.hpp"
#include "Utils/Macros.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"

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

struct s_global_preferences;
struct s_global_preferences_settings;
namespace
{
	struct RawMouseState;
}

namespace Utils {}
using namespace ::Utils;
namespace Utils
{
	namespace AntiCheat {}
	using namespace Utils::AntiCheat;
}

namespace Modules {}
using namespace ::Modules;
namespace Forge {}
using namespace ::Forge;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace RawInput {}
	using namespace Patches::RawInput;
	namespace Camera {}
	using namespace Patches::Camera;
}

namespace Blam {}
using namespace ::Blam;

/* ---------- constants */

/* ---------- definitions */

namespace
{
	struct RawMouseState
	{
	    enum
		{
			eButtonLeft = (1 << 0),
			eButtonMiddle = (1 << 1),
			eButtonRight = (1 << 2),
			eButton4 = (1 << 3),
			eButton5 = (1 << 4),
		};
		unsigned char buttons; // 0x0
		unsigned char __pad0[3]; // 0x1
		__int32 deltaX; // 0x4
		__int32 deltaY; // 0x8
		__int32 wheelDelta; // 0xC
	};
	static_assert(sizeof(RawMouseState) == 16, "Invalid RawMouseState size");
}
/* ---------- prototypes */

namespace Patches
{
	namespace RawInput
	{
		extern void ApplyAll();
		extern void UpdateCameraYawPitch(float deltaX, float deltaY, float &yaw, float &pitch);
	}
}

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Patches
{
	namespace RawInput
	{
		_extern void _sub_10ABEF90();
		void ApplyAll() // 0x10ABEF90
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@RawInput@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10ABEF90();
		}

		_extern void _sub_10ABF8E0(float, float, float &, float &);
		void UpdateCameraYawPitch(float deltaX, float deltaY, float &yaw, float &pitch) // 0x10ABF8E0
		{
			mangled_x86(MANGLED_TODO, "?UpdateCameraYawPitch@RawInput@Patches@@YAXMMAAM0@Z");
			// float &pitch;
			// s_global_preferences_settings::s_input_settings *const input_settings;
			// float weaponSensitivity;
			// long player_index;
			// float maxVertAngle;
			// float yaxisSens;
			// s_global_preferences *prefs;
			// float xaxisSens;
			// function call : unsigned long (*const)(long)
			// function call : bool (*const)(long)
			todo("implement");
			_sub_10ABF8E0(deltaX, deltaY, yaw, pitch);
		}
	}
}

/* ---------- private code */
