/* ---------- headers */

#include "hades/hades.h"

#include "Blam/BlamInput.hpp"
#include "Blam/camera/camera.hpp"
#include "Blam/camera/director.hpp"
#include "Blam/camera/observer.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/effects/screen_effect.hpp"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/static_array.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/physics/havok_types.hpp"
#include "Blam/rasterizer/draw_string.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Debug/DebugDraw.hpp"
#include "ElDorito.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Patches/Ui.hpp"
#include "Player/PlayerEmotes.hpp"
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
#include <memory>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <system_error>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

class c_director;
struct real_vector3d;
struct s_camera_definition;

namespace Utils {}
using namespace ::Utils;
namespace Utils
{
	namespace AntiCheat {}
	using namespace Utils::AntiCheat;
}

namespace Modules {}
using namespace ::Modules;
namespace Player {}
using namespace ::Player;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace RawInput {}
	using namespace Patches::RawInput;
	namespace Camera {}
	using namespace Patches::Camera;
	namespace Core {}
	using namespace Patches::Core;
}

namespace Blam {}
using namespace ::Blam;

/* ---------- constants */

/* ---------- definitions */

//struct c_following_camera__update_hook::__l2::s_camera_definition
//{
//	real_point3d Position; // 0x0
//	real_vector3d PositionShift; // 0xC
//	float LookShift[2]; // 0x18
//	float Depth; // 0x20
//	float FieldOfView; // 0x24
//	real_vector3d Forward; // 0x28
//	real_vector3d Up; // 0x34
//};
//static_assert(sizeof(c_following_camera__update_hook::__l2::s_camera_definition) == 64, "Invalid c_following_camera__update_hook::__l2::s_camera_definition size");

/* ---------- prototypes */

namespace Patches
{
	namespace Camera
	{
		extern void ApplyAll();
		extern void ApplyAfterTagsLoaded();
		extern bool SetForcedCameraMode(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const mode);
		extern e_camera_mode GetForcedCameraMode();
	}
}

/* ---------- globals */

/* ---------- private variables */

namespace
{
	extern e_camera_mode cameraMode; // 0x11353BB0
	extern float &k_camera_field_of_view_default; // 0x11353BA4
	extern float &k_camera_field_of_view_min; // 0x11353BA8
	extern float &k_camera_field_of_view_max; // 0x11353BAC
}
/* ---------- public code */

namespace Patches
{
	namespace Camera
	{
		_extern void _sub_10956FE0();
		void ApplyAll() // 0x10956FE0
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@Camera@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10956FE0();
		}

		_extern void _sub_10956FC0();
		void ApplyAfterTagsLoaded() // 0x10956FC0
		{
			mangled_x86(MANGLED_TODO, "?ApplyAfterTagsLoaded@Camera@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10956FC0();
		}

		_extern bool _sub_10958AF0(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const);
		bool SetForcedCameraMode(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const mode) // 0x10958AF0
		{
			mangled_x86(MANGLED_TODO, "?SetForcedCameraMode@Camera@Patches@@YA_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > mode;
			// constexpr bool (*const `Patches::Camera::SetForcedCameraMode'::`2'::player_terminal_chud_set)(bool); // constant == 11050832
			{
				// e_camera_mode currentMode;
			}
			{
			}
			{
			}
			{
			}
			{
			}
			{
			}
			// function call : void (*const)(long, e_director_mode)
			// function call : bool (*const)(long, long)
			// function call : c_director *(*const)(long)
			// function call : e_camera_mode ()
			// function call : void (*const)(long, e_director_mode)
			// function call : bool (*const)(long, long)
			// function call : c_director *(*const)(long)
			// function call : e_camera_mode ()
			// function call : void (*const)(long, e_director_mode)
			// function call : bool (*const)(long, long)
			// function call : c_director *(*const)(long)
			// function call : e_camera_mode ()
			// function call : void (*const)(long, e_director_mode)
			// function call : bool (*const)(long, long)
			// function call : c_director *(*const)(long)
			// function call : e_camera_mode ()
			// function call : void (*const)(long, e_director_mode)
			// function call : bool (*const)(long, long)
			// function call : c_director *(*const)(long)
			// function call : e_camera_mode ()
			// function call : void (*const)(long, e_director_mode)
			// function call : bool (*const)(long, long)
			// function call : c_director *(*const)(long)
			// function call : e_camera_mode ()
			// function call : bool (*const)(bool)
			todo("implement");
			bool __result = _sub_10958AF0(mode);
			return __result;
		}
	}
}

extern e_camera_mode _sub_109589A0();
namespace Patches
{
	namespace Camera
	{
		e_camera_mode GetForcedCameraMode() // 0x109589A0
		{
			mangled_x86(MANGLED_TODO, "?GetForcedCameraMode@Camera@Patches@@YA?AW4e_camera_mode@@XZ");
			// procedure flags: nofpo
			todo("implement");
			e_camera_mode __result = _sub_109589A0();
			return __result;
		}
	}
}

/* ---------- private code */
