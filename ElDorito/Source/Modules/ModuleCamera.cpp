/* ---------- headers */

#include "Modules/ModuleCamera.hpp"
#include "hades/hades.h"

#include "Blam/BlamInput.hpp"
#include "Blam/BlamNetwork.hpp"
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
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/bitstream.hpp"
#include "Blam/memory/tls.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ElDorito.hpp"
#include "Modules/ModuleBase.hpp"
#include "Patch.hpp"
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

struct real_euler_angles2d;
namespace Modules
{
	class ModuleBase;
	class ModuleCamera;
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
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Camera {}
	using namespace Patches::Camera;
}

namespace Blam {}
using namespace ::Blam;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

namespace
{
	extern float &k_camera_field_of_view_default; // 0x11353EC0
	extern real_euler_angles2d inputAngularVelocity; // 0x12454D54
}
/* ---------- public code */

namespace Modules
{
	extern ModuleCamera* _sub_10978AE0(Modules::ModuleCamera *const);
	ModuleCamera::ModuleCamera() : ModuleBase(todo_result<std::basic_string<char,std::char_traits<char>,std::allocator<char> >>()) // 0x10978AE0
	{
		mangled_x86(MANGLED_TODO, "??0ModuleCamera@Modules@@QAE@XZ");
		// Modules::ModuleCamera *const this;
		todo("implement");
		_sub_10978AE0(this);
	}

	_extern void _sub_10979E30(Modules::ModuleCamera *const, real_euler_angles2d const *);
	void ModuleCamera::SetInputAngularVelocity(real_euler_angles2d const *velocity) // 0x10979E30
	{
		mangled_x86(MANGLED_TODO, "?SetInputAngularVelocity@ModuleCamera@Modules@@QAEXPBUreal_euler_angles2d@@@Z");
		// real_euler_angles2d const *velocity;
		todo("implement");
		_sub_10979E30(this, velocity);
	}

	_extern void _sub_10979DF0(Modules::ModuleCamera const *const, real_euler_angles2d *);
	void ModuleCamera::GetInputAngularVelocity(real_euler_angles2d *velocity) const // 0x10979DF0
	{
		mangled_x86(MANGLED_TODO, "?GetInputAngularVelocity@ModuleCamera@Modules@@QBEXPAUreal_euler_angles2d@@@Z");
		// real_euler_angles2d *velocity;
		todo("implement");
		_sub_10979DF0((Modules::ModuleCamera const *)this, velocity);
	}
}

/* ---------- private code */
