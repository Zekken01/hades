/* ---------- headers */

#include "Modules/ModuleSettings.hpp"
#include "hades/hades.h"

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
#include "Blam/memory/tls.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/rasterizer/rasterizer_globals.hpp"
#include "Blam/rasterizer/rasterizer_samplers.hpp"
#include "Blam/rasterizer/rasterizer_states.hpp"
#include "Blam/render/screen_postprocess.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "CommandMap.hpp"
#include "Modules/ModuleBase.hpp"
#include "Patch.hpp"
#include "Pointer.hpp"
#include "ThirdParty/rapidjson/allocators.h"
#include "ThirdParty/rapidjson/encodings.h"
#include "ThirdParty/rapidjson/internal/diyfp.h"
#include "ThirdParty/rapidjson/internal/dtoa.h"
#include "ThirdParty/rapidjson/internal/ieee754.h"
#include "ThirdParty/rapidjson/internal/itoa.h"
#include "ThirdParty/rapidjson/internal/stack.h"
#include "ThirdParty/rapidjson/internal/strfunc.h"
#include "ThirdParty/rapidjson/stream.h"
#include "ThirdParty/rapidjson/stringbuffer.h"
#include "ThirdParty/rapidjson/writer.h"
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
#include <deque>
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

struct c_screen_postprocess;
namespace Modules
{
	class ModuleBase;
	class ModuleSettings;
}

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;
namespace base
{
	namespace internal {}
	using namespace base::internal;
}

namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Ui {}
	using namespace Patches::Ui;
	namespace Audio {}
	using namespace Patches::Audio;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

c_screen_postprocess::s_smaa_globals c_screen_postprocess::smaa_globals; // 0x12457840

/* ---------- private variables */

namespace
{
	extern __int32 (*SSL_SetAntialiasing)(bool); // 0x11354098
	extern __int32 (*SSL_SetAutoCentering)(bool); // 0x1135409C
	extern __int32 (*SSL_SetContrast)(__int32); // 0x113540A0
	extern __int32 (*SSL_SetDetailsQuality)(__int32); // 0x113540A4
	extern __int32 (*SSL_SetDisplayHints)(bool); // 0x113540A8
	extern __int32 (*SSL_SetEffectsQuality)(__int32); // 0x113540AC
	extern __int32 (*SSL_SetFullscreen)(__int32); // 0x113540B0
	extern __int32 (*SSL_SetHUDShake)(bool); // 0x113540B4
	extern __int32 (*SSL_SetInvertLook)(bool); // 0x113540B8
	extern __int32 (*SSL_SetInvertMouse)(bool); // 0x113540BC
	extern __int32 (*SSL_SetLightingQuality)(__int32); // 0x113540C0
	extern __int32 (*SSL_SetLookSensitivity)(__int32); // 0x113540C4
	extern __int32 (*SSL_SetMasterVolume)(__int32, char); // 0x113540C8
	extern __int32 (*SSL_SetMotionBlur)(bool); // 0x113540CC
	extern __int32 (*SSL_SetMouseAcceleration)(__int32); // 0x113540D0
	extern __int32 (*SSL_SetMouseSensitivityHor)(__int32); // 0x113540D4
	extern __int32 (*SSL_SetMouseSensitivityVehicleHor)(__int32); // 0x113540D8
	extern __int32 (*SSL_SetMouseSensitivityVehicleVert)(__int32); // 0x113540DC
	extern __int32 (*SSL_SetMouseSensitivityVert)(__int32); // 0x113540E0
	extern __int32 (*SSL_SetMusicVolume)(__int32, bool); // 0x113540E4
	extern __int32 (*SSL_SetPostprocessingQuality)(__int32); // 0x113540E8
	extern __int32 (*SSL_SetSFXVolume)(__int32, bool); // 0x113540EC
	extern __int32 (*SSL_SetShadowQuality)(__int32); // 0x113540F0
	extern __int32 (*SSL_SetTeamColor)(__int32); // 0x113540F4
	extern __int32 (*SSL_SetTextureFilteringQuality)(__int32); // 0x113540F8
	extern __int32 (*SSL_SetTextureResolution)(__int32); // 0x113540FC
	extern __int32 (*SSL_SetToggleCrouch)(__int32); // 0x11354100
	extern __int32 (*SSL_SetVSync)(__int32); // 0x11354104
}
/* ---------- public code */

namespace Modules
{
	extern ModuleSettings* _sub_10A198C0(Modules::ModuleSettings *const);
	ModuleSettings::ModuleSettings() : ModuleBase(todo_result<std::basic_string<char,std::char_traits<char>,std::allocator<char> >>()) // 0x10A198C0
	{
		mangled_x86(MANGLED_TODO, "??0ModuleSettings@Modules@@QAE@XZ");
		// Modules::ModuleSettings *const this;
		todo("implement");
		_sub_10A198C0(this);
	}

	_extern void _sub_10A1C820(Modules::ModuleSettings const *const, __int32 *, __int32 *);
	void ModuleSettings::GetScreenResolution(__int32 *width, __int32 *height) const // 0x10A1C820
	{
		mangled_x86(MANGLED_TODO, "?GetScreenResolution@ModuleSettings@Modules@@QBEXPAH0@Z");
		// __int32 *height;
		// Modules::ModuleSettings const &moduleSettings;
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &resolutionStr;
		{
			// unsigned long fullScreen;
		}
		// function call : __int32 (__int32)
		// function call : __int32 (__int32)
		todo("implement");
		_sub_10A1C820((Modules::ModuleSettings const *)this, width, height);
	}
}

/* ---------- private code */
