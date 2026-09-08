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
#include "Blam/main/game_preferences.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/tls.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/rasterizer/rasterizer_globals.hpp"
#include "Blam/rasterizer/rasterizer_render_targets.hpp"
#include "Blam/rasterizer/rasterizer_samplers.hpp"
#include "Blam/rasterizer/rasterizer_states.hpp"
#include "Blam/render/screen_postprocess.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "CommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Modules/ModuleBase.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
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

struct begin;
struct c_screen_postprocess;
struct end;
struct s_global_preferences;
struct s_surface_group_description;
namespace Modules
{
	class CommandMap;
	class ModuleBase;
	class ModuleSettings;
	struct Command;
}
namespace Patches
{
	namespace Audio
	{
		struct SAudioDeviceInfo;
	}
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

bool VariableSettingsAntialiasingUpdate(std::vector<std::string> const &args, std::string &returnInfo);
bool VariableSettingsAutoCenteringUpdate(std::vector<std::string> const &args, std::string &returnInfo);
bool VariableSettingsBrightnessUpdate(std::vector<std::string> const &args, std::string &returnInfo);
bool VariableSettingsContrastUpdate(std::vector<std::string> const &args, std::string &returnInfo);
bool VariableSettingsDetailsQualityUpdate(std::vector<std::string> const &args, std::string &returnInfo);
bool VariableSettingsDisplayHintsUpdate(std::vector<std::string> const &args, std::string &returnInfo);
bool VariableSettingsEffectsQualityUpdate(std::vector<std::string> const &args, std::string &returnInfo);
bool VariableSettingsFullscreenUpdate(std::vector<std::string> const &args, std::string &returnInfo);
bool VariableSettingsHUDShakeUpdate(std::vector<std::string> const &args, std::string &returnInfo);
bool VariableSettingsInvertLookUpdate(std::vector<std::string> const &args, std::string &returnInfo);
bool VariableSettingsInvertMouseUpdate(std::vector<std::string> const &args, std::string &returnInfo);
bool VariableSettingsLightingQualityUpdate(std::vector<std::string> const &args, std::string &returnInfo);
bool VariableSettingsLookSensitivityUpdate(std::vector<std::string> const &args, std::string &returnInfo);
bool VariableSettingsMotionBlurUpdate(std::vector<std::string> const &args, std::string &returnInfo);
bool VariableSettingsMotionBlurStrengthUpdate(std::vector<std::string> const &args, std::string &returnInfo);
bool VariableSettingsSsaoUpdate(std::vector<std::string> const &args, std::string &returnInfo);
bool VariableSettingsMotionBlurAlwaysUpdate(std::vector<std::string> const &args, std::string &returnInfo);
bool VariableSettingsMouseAccelerationUpdate(std::vector<std::string> const &args, std::string &returnInfo);
bool VariableSettingsMouseSensitivityHorizontalUpdate(std::vector<std::string> const &args, std::string &returnInfo);
bool VariableSettingsMouseSensitivityVerticalUpdate(std::vector<std::string> const &args, std::string &returnInfo);
bool VariableSettingsMouseSensitivityVehicleHorizontalUpdate(std::vector<std::string> const &args, std::string &returnInfo);
bool VariableSettingsMouseSensitivityVehicleVerticalUpdate(std::vector<std::string> const &args, std::string &returnInfo);
bool VariableSettingsPlayerMarkerColorsUpdate(std::vector<std::string> const &args, std::string &returnInfo);
bool VariableSettingsPostprocessingQualityUpdate(std::vector<std::string> const &args, std::string &returnInfo);
bool VariableSettingsShadowQualityUpdate(std::vector<std::string> const &args, std::string &returnInfo);
bool VariableSettingsShadowResolutionUpdate(std::vector<std::string> const &args, std::string &returnInfo);
bool VariableSettingsTextureFilteringQualityUpdate(std::vector<std::string> const &args, std::string &returnInfo);
bool VariableSettingsTextureResolutionUpdate(std::vector<std::string> const &args, std::string &returnInfo);
bool VariableSettingsToggleCrouchUpdate(std::vector<std::string> const &args, std::string &returnInfo);
bool VariableSettingsVSyncUpdate(std::vector<std::string> const &args, std::string &returnInfo);
bool VariableSettingsScreenResolutionUpdate(std::vector<std::string> const &args, std::string &returnInfo);
bool SoundSystemInitialized();
bool VariableSettingsMasterVolumeUpdated(std::vector<std::string> const &args, std::string &returnInfo);
bool VariableSettingsSfxVolumeUpdated(std::vector<std::string> const &args, std::string &returnInfo);
bool VariableSettingsMainMenuMusicVolumeUpdated(std::vector<std::string> const &args, std::string &returnInfo);
bool VariableSettingsMusicVolumeUpdated(std::vector<std::string> const &args, std::string &returnInfo);
bool VariableAudioOutputDeviceUpdated(std::vector<std::string> const &args, std::string &returnInfo);
bool CommandAudioOutputDeviceList(std::vector<std::string> const &args, std::string &returnInfo);
bool VariableSettingsAnisotropicFilteringUpdate(std::vector<std::string> const &args, std::string &returnInfo);
bool VariableSettingsSubtitlesUpdate(std::vector<std::string> const &args, std::string &returnInfo);
bool CommandResetSettings(std::vector<std::string> const &args, std::string &returnInfo);
void UpdateScreenResolution();
bool TryParseInt(std::string const &str, __int32 *value);
bool TryParseResolutionString(std::string const &str, __int32 *width, __int32 *height);

/* ---------- globals */

c_screen_postprocess::s_smaa_globals c_screen_postprocess::smaa_globals; // 0x12457840

/* ---------- private variables */

namespace hades_file_local
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
using namespace hades_file_local;
/* ---------- public code */

namespace Modules
{
	extern ModuleSettings* _sub_10A198C0(Modules::ModuleSettings *const);
	ModuleSettings::ModuleSettings() : ModuleBase(todo_result<std::string>()) // 0x10A198C0
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
		// std::string const &resolutionStr;
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

_extern bool _sub_10A1D1E0(std::vector<std::string> const &, std::string &);
bool VariableSettingsAntialiasingUpdate(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A1D1E0
{
	// `anonymous-namespace'::VariableSettingsAntialiasingUpdate
	// static ...; // 0x10A1D3D4
	// static ...; // 0x10A1D3CC
	// std::vector<std::string> const &args;
	// std::string &returnInfo;
	// std::stringstream ss;
	// bool statusBool;
	// unsigned long value;
	// function call : __int32 (*)(bool)
	todo("implement");
	bool __result = _sub_10A1D1E0(args, returnInfo);
	return __result;
}

_extern bool _sub_10A1D470(std::vector<std::string> const &, std::string &);
bool VariableSettingsAutoCenteringUpdate(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A1D470
{
	// `anonymous-namespace'::VariableSettingsAutoCenteringUpdate
	// static ...; // 0x10A1D60C
	// static ...; // 0x10A1D604
	// std::vector<std::string> const &args;
	// std::string &returnInfo;
	// std::stringstream ss;
	// bool statusBool;
	// unsigned long value;
	// function call : __int32 (*)(bool)
	todo("implement");
	bool __result = _sub_10A1D470(args, returnInfo);
	return __result;
}

_extern bool _sub_10A1D690(std::vector<std::string> const &, std::string &);
bool VariableSettingsBrightnessUpdate(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A1D690
{
	// `anonymous-namespace'::VariableSettingsBrightnessUpdate
	// static ...; // 0x10A1D7D8
	// static ...; // 0x10A1D7D0
	// std::vector<std::string> const &args;
	// std::string &returnInfo;
	// std::stringstream ss;
	// unsigned long value;
	todo("implement");
	bool __result = _sub_10A1D690(args, returnInfo);
	return __result;
}

_extern bool _sub_10A1D840(std::vector<std::string> const &, std::string &);
bool VariableSettingsContrastUpdate(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A1D840
{
	// `anonymous-namespace'::VariableSettingsContrastUpdate
	// static ...; // 0x10A1D9A0
	// static ...; // 0x10A1D998
	// std::vector<std::string> const &args;
	// std::string &returnInfo;
	// std::stringstream ss;
	// unsigned long value;
	// function call : __int32 (*)(__int32)
	todo("implement");
	bool __result = _sub_10A1D840(args, returnInfo);
	return __result;
}

_extern bool _sub_10A1DA10(std::vector<std::string> const &, std::string &);
bool VariableSettingsDetailsQualityUpdate(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A1DA10
{
	// `anonymous-namespace'::VariableSettingsDetailsQualityUpdate
	// static ...; // 0x10A1DC54
	// static ...; // 0x10A1DC3C
	// static ...; // 0x10A1DC34
	// std::vector<std::string> const &args;
	// std::string &returnInfo;
	// std::stringstream ss;
	// std::string value;
	// __int32 intValue;
	// function call : __int32 (*)(__int32)
	todo("implement");
	bool __result = _sub_10A1DA10(args, returnInfo);
	return __result;
}

_extern bool _sub_10A1DCF0(std::vector<std::string> const &, std::string &);
bool VariableSettingsDisplayHintsUpdate(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A1DCF0
{
	// `anonymous-namespace'::VariableSettingsDisplayHintsUpdate
	// static ...; // 0x10A1DE8C
	// static ...; // 0x10A1DE84
	// std::vector<std::string> const &args;
	// std::string &returnInfo;
	// std::stringstream ss;
	// bool statusBool;
	// unsigned long value;
	// function call : __int32 (*)(bool)
	todo("implement");
	bool __result = _sub_10A1DCF0(args, returnInfo);
	return __result;
}

_extern bool _sub_10A1DF10(std::vector<std::string> const &, std::string &);
bool VariableSettingsEffectsQualityUpdate(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A1DF10
{
	// `anonymous-namespace'::VariableSettingsEffectsQualityUpdate
	// static ...; // 0x10A1E15C
	// static ...; // 0x10A1E144
	// static ...; // 0x10A1E13C
	// std::vector<std::string> const &args;
	// std::string &returnInfo;
	// std::stringstream ss;
	// std::string value;
	// __int32 intValue;
	// function call : __int32 (*)(__int32)
	todo("implement");
	bool __result = _sub_10A1DF10(args, returnInfo);
	return __result;
}

_extern bool _sub_10A1E200(std::vector<std::string> const &, std::string &);
bool VariableSettingsFullscreenUpdate(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A1E200
{
	// `anonymous-namespace'::VariableSettingsFullscreenUpdate
	// static ...; // 0x10A1E3A8
	// static ...; // 0x10A1E3A0
	// std::vector<std::string> const &args;
	// std::string &returnInfo;
	// Modules::ModuleSettings const &moduleSettings;
	// std::stringstream ss;
	// bool statusBool;
	// unsigned long value;
	// function call : __int32 (*)(__int32)
	todo("implement");
	bool __result = _sub_10A1E200(args, returnInfo);
	return __result;
}

_extern bool _sub_10A1E430(std::vector<std::string> const &, std::string &);
bool VariableSettingsHUDShakeUpdate(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A1E430
{
	// `anonymous-namespace'::VariableSettingsHUDShakeUpdate
	// static ...; // 0x10A1E5CC
	// static ...; // 0x10A1E5C4
	// std::vector<std::string> const &args;
	// std::string &returnInfo;
	// std::stringstream ss;
	// bool statusBool;
	// unsigned long value;
	// function call : __int32 (*)(bool)
	todo("implement");
	bool __result = _sub_10A1E430(args, returnInfo);
	return __result;
}

_extern bool _sub_10A1E650(std::vector<std::string> const &, std::string &);
bool VariableSettingsInvertLookUpdate(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A1E650
{
	// `anonymous-namespace'::VariableSettingsInvertLookUpdate
	// static ...; // 0x10A1E7EC
	// static ...; // 0x10A1E7E4
	// std::vector<std::string> const &args;
	// std::string &returnInfo;
	// std::stringstream ss;
	// bool statusBool;
	// unsigned long value;
	// function call : __int32 (*)(bool)
	todo("implement");
	bool __result = _sub_10A1E650(args, returnInfo);
	return __result;
}

_extern bool _sub_10A1E870(std::vector<std::string> const &, std::string &);
bool VariableSettingsInvertMouseUpdate(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A1E870
{
	// `anonymous-namespace'::VariableSettingsInvertMouseUpdate
	// static ...; // 0x10A1EA0C
	// static ...; // 0x10A1EA04
	// std::vector<std::string> const &args;
	// std::string &returnInfo;
	// std::stringstream ss;
	// bool statusBool;
	// unsigned long value;
	// function call : __int32 (*)(bool)
	todo("implement");
	bool __result = _sub_10A1E870(args, returnInfo);
	return __result;
}

_extern bool _sub_10A1EA90(std::vector<std::string> const &, std::string &);
bool VariableSettingsLightingQualityUpdate(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A1EA90
{
	// `anonymous-namespace'::VariableSettingsLightingQualityUpdate
	// static ...; // 0x10A1ECD4
	// static ...; // 0x10A1ECBC
	// static ...; // 0x10A1ECB4
	// std::vector<std::string> const &args;
	// std::string &returnInfo;
	// std::stringstream ss;
	// std::string value;
	// __int32 intValue;
	// function call : __int32 (*)(__int32)
	todo("implement");
	bool __result = _sub_10A1EA90(args, returnInfo);
	return __result;
}

_extern bool _sub_10A1ED70(std::vector<std::string> const &, std::string &);
bool VariableSettingsLookSensitivityUpdate(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A1ED70
{
	// `anonymous-namespace'::VariableSettingsLookSensitivityUpdate
	// static ...; // 0x10A1EED0
	// static ...; // 0x10A1EEC8
	// std::vector<std::string> const &args;
	// std::string &returnInfo;
	// std::stringstream ss;
	// unsigned long value;
	// function call : __int32 (*)(__int32)
	todo("implement");
	bool __result = _sub_10A1ED70(args, returnInfo);
	return __result;
}

_extern bool _sub_10A1F6D0(std::vector<std::string> const &, std::string &);
bool VariableSettingsMotionBlurUpdate(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A1F6D0
{
	// `anonymous-namespace'::VariableSettingsMotionBlurUpdate
	// static ...; // 0x10A1F86C
	// static ...; // 0x10A1F864
	// std::vector<std::string> const &args;
	// std::string &returnInfo;
	// std::stringstream ss;
	// bool statusBool;
	// unsigned long value;
	// function call : __int32 (*)(bool)
	todo("implement");
	bool __result = _sub_10A1F6D0(args, returnInfo);
	return __result;
}

_extern bool _sub_10A1F530(std::vector<std::string> const &, std::string &);
bool VariableSettingsMotionBlurStrengthUpdate(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A1F530
{
	// `anonymous-namespace'::VariableSettingsMotionBlurStrengthUpdate
	// static ...; // 0x10A1F668
	// static ...; // 0x10A1F660
	// std::vector<std::string> const &args;
	// std::string &returnInfo;
	// std::stringstream ss;
	// float value;
	todo("implement");
	bool __result = _sub_10A1F530(args, returnInfo);
	return __result;
}

_extern bool _sub_10A213B0(std::vector<std::string> const &, std::string &);
bool VariableSettingsSsaoUpdate(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A213B0
{
	// `anonymous-namespace'::VariableSettingsSsaoUpdate
	// static ...; // 0x10A214F4
	// static ...; // 0x10A214EC
	// std::vector<std::string> const &args;
	// std::string &returnInfo;
	// std::stringstream ss;
	// __int32 value;
	todo("implement");
	bool __result = _sub_10A213B0(args, returnInfo);
	return __result;
}

_extern bool _sub_10A1F340(std::vector<std::string> const &, std::string &);
bool VariableSettingsMotionBlurAlwaysUpdate(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A1F340
{
	// `anonymous-namespace'::VariableSettingsMotionBlurAlwaysUpdate
	// static ...; // 0x10A1F4BC
	// static ...; // 0x10A1F4B4
	// std::vector<std::string> const &args;
	// std::string &returnInfo;
	// std::stringstream ss;
	// bool value;
	todo("implement");
	bool __result = _sub_10A1F340(args, returnInfo);
	return __result;
}

_extern bool _sub_10A1F8F0(std::vector<std::string> const &, std::string &);
bool VariableSettingsMouseAccelerationUpdate(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A1F8F0
{
	// `anonymous-namespace'::VariableSettingsMouseAccelerationUpdate
	// static ...; // 0x10A1FA50
	// static ...; // 0x10A1FA48
	// std::vector<std::string> const &args;
	// std::string &returnInfo;
	// std::stringstream ss;
	// unsigned long value;
	// function call : __int32 (*)(__int32)
	todo("implement");
	bool __result = _sub_10A1F8F0(args, returnInfo);
	return __result;
}

_extern bool _sub_10A1FAC0(std::vector<std::string> const &, std::string &);
bool VariableSettingsMouseSensitivityHorizontalUpdate(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A1FAC0
{
	// `anonymous-namespace'::VariableSettingsMouseSensitivityHorizontalUpdate
	// static ...; // 0x10A1FC20
	// static ...; // 0x10A1FC18
	// std::vector<std::string> const &args;
	// std::string &returnInfo;
	// std::stringstream ss;
	// unsigned long value;
	// function call : __int32 (*)(__int32)
	todo("implement");
	bool __result = _sub_10A1FAC0(args, returnInfo);
	return __result;
}

_extern bool _sub_10A20030(std::vector<std::string> const &, std::string &);
bool VariableSettingsMouseSensitivityVerticalUpdate(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A20030
{
	// `anonymous-namespace'::VariableSettingsMouseSensitivityVerticalUpdate
	// static ...; // 0x10A20190
	// static ...; // 0x10A20188
	// std::vector<std::string> const &args;
	// std::string &returnInfo;
	// std::stringstream ss;
	// unsigned long value;
	// function call : __int32 (*)(__int32)
	todo("implement");
	bool __result = _sub_10A20030(args, returnInfo);
	return __result;
}

_extern bool _sub_10A1FC90(std::vector<std::string> const &, std::string &);
bool VariableSettingsMouseSensitivityVehicleHorizontalUpdate(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A1FC90
{
	// `anonymous-namespace'::VariableSettingsMouseSensitivityVehicleHorizontalUpdate
	// static ...; // 0x10A1FDF0
	// static ...; // 0x10A1FDE8
	// std::vector<std::string> const &args;
	// std::string &returnInfo;
	// std::stringstream ss;
	// unsigned long value;
	// function call : __int32 (*)(__int32)
	todo("implement");
	bool __result = _sub_10A1FC90(args, returnInfo);
	return __result;
}

_extern bool _sub_10A1FE60(std::vector<std::string> const &, std::string &);
bool VariableSettingsMouseSensitivityVehicleVerticalUpdate(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A1FE60
{
	// `anonymous-namespace'::VariableSettingsMouseSensitivityVehicleVerticalUpdate
	// static ...; // 0x10A1FFC0
	// static ...; // 0x10A1FFB8
	// std::vector<std::string> const &args;
	// std::string &returnInfo;
	// std::stringstream ss;
	// unsigned long value;
	// function call : __int32 (*)(__int32)
	todo("implement");
	bool __result = _sub_10A1FE60(args, returnInfo);
	return __result;
}

_extern bool _sub_10A20420(std::vector<std::string> const &, std::string &);
bool VariableSettingsPlayerMarkerColorsUpdate(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A20420
{
	// `anonymous-namespace'::VariableSettingsPlayerMarkerColorsUpdate
	// static ...; // 0x10A20694
	// static ...; // 0x10A2067C
	// static ...; // 0x10A20674
	// std::vector<std::string> const &args;
	// std::string &returnInfo;
	// std::stringstream ss;
	// std::string value;
	// __int32 intValue;
	// function call : __int32 (*)(__int32)
	// function call : __int32 (*)(__int32)
	todo("implement");
	bool __result = _sub_10A20420(args, returnInfo);
	return __result;
}

_extern bool _sub_10A20740(std::vector<std::string> const &, std::string &);
bool VariableSettingsPostprocessingQualityUpdate(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A20740
{
	// `anonymous-namespace'::VariableSettingsPostprocessingQualityUpdate
	// static ...; // 0x10A20984
	// static ...; // 0x10A2096C
	// static ...; // 0x10A20964
	// std::vector<std::string> const &args;
	// std::string &returnInfo;
	// std::stringstream ss;
	// std::string value;
	// __int32 intValue;
	// function call : __int32 (*)(__int32)
	todo("implement");
	bool __result = _sub_10A20740(args, returnInfo);
	return __result;
}

_extern bool _sub_10A20E60(std::vector<std::string> const &, std::string &);
bool VariableSettingsShadowQualityUpdate(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A20E60
{
	// `anonymous-namespace'::VariableSettingsShadowQualityUpdate
	// static ...; // 0x10A210A4
	// static ...; // 0x10A2108C
	// static ...; // 0x10A21084
	// std::vector<std::string> const &args;
	// std::string &returnInfo;
	// std::stringstream ss;
	// std::string value;
	// __int32 intValue;
	// function call : __int32 (*)(__int32)
	todo("implement");
	bool __result = _sub_10A20E60(args, returnInfo);
	return __result;
}

_extern bool _sub_10A21140(std::vector<std::string> const &, std::string &);
bool VariableSettingsShadowResolutionUpdate(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A21140
{
	// `anonymous-namespace'::VariableSettingsShadowResolutionUpdate
	// static ...; // 0x10A2131C
	// static ...; // 0x10A21314
	// std::vector<std::string> const &args;
	// std::string &returnInfo;
	// long const shadow_texture_resolution;
	// s_surface_group_description *shadow_surface;
	// s_surface_group_description *shadow_color_surface;
	// std::stringstream ss;
	// unsigned long value;
	todo("implement");
	bool __result = _sub_10A21140(args, returnInfo);
	return __result;
}

_extern bool _sub_10A215E0(std::vector<std::string> const &, std::string &);
bool VariableSettingsTextureFilteringQualityUpdate(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A215E0
{
	// `anonymous-namespace'::VariableSettingsTextureFilteringQualityUpdate
	// static ...; // 0x10A21828
	// static ...; // 0x10A21810
	// static ...; // 0x10A21808
	// std::vector<std::string> const &args;
	// std::string &returnInfo;
	// std::stringstream ss;
	// std::string value;
	// __int32 intValue;
	// function call : __int32 (*)(__int32)
	todo("implement");
	bool __result = _sub_10A215E0(args, returnInfo);
	return __result;
}

_extern bool _sub_10A218D0(std::vector<std::string> const &, std::string &);
bool VariableSettingsTextureResolutionUpdate(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A218D0
{
	// `anonymous-namespace'::VariableSettingsTextureResolutionUpdate
	// static ...; // 0x10A21B18
	// static ...; // 0x10A21B00
	// static ...; // 0x10A21AF8
	// std::vector<std::string> const &args;
	// std::string &returnInfo;
	// std::stringstream ss;
	// std::string value;
	// __int32 intValue;
	// function call : __int32 (*)(__int32)
	todo("implement");
	bool __result = _sub_10A218D0(args, returnInfo);
	return __result;
}

_extern bool _sub_10A21BC0(std::vector<std::string> const &, std::string &);
bool VariableSettingsToggleCrouchUpdate(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A21BC0
{
	// `anonymous-namespace'::VariableSettingsToggleCrouchUpdate
	// static ...; // 0x10A21D60
	// static ...; // 0x10A21D58
	// std::vector<std::string> const &args;
	// std::string &returnInfo;
	// std::stringstream ss;
	// bool statusBool;
	// unsigned long value;
	// function call : __int32 (*)(__int32)
	todo("implement");
	bool __result = _sub_10A21BC0(args, returnInfo);
	return __result;
}

_extern bool _sub_10A21DE0(std::vector<std::string> const &, std::string &);
bool VariableSettingsVSyncUpdate(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A21DE0
{
	// `anonymous-namespace'::VariableSettingsVSyncUpdate
	// static ...; // 0x10A21F84
	// static ...; // 0x10A21F7C
	// std::vector<std::string> const &args;
	// std::string &returnInfo;
	// std::stringstream ss;
	// bool statusBool;
	// unsigned long value;
	// function call : __int32 (*)(__int32)
	todo("implement");
	bool __result = _sub_10A21DE0(args, returnInfo);
	return __result;
}

_extern bool _sub_10A20A20(std::vector<std::string> const &, std::string &);
bool VariableSettingsScreenResolutionUpdate(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A20A20
{
	// `anonymous-namespace'::VariableSettingsScreenResolutionUpdate
	// static ...; // 0x10A20BF6
	// static ...; // 0x10A20BEF
	// static ...; // 0x10A20BEC
	// static ...; // 0x10A20BBC
	// static ...; // 0x10A20BB4
	// std::vector<std::string> const &args;
	// std::string &returnInfo;
	// Modules::ModuleSettings const &moduleSettings;
	// std::stringstream ss;
	// __int32 width;
	// std::string value;
	// __int32 height;
	todo("implement");
	bool __result = _sub_10A20A20(args, returnInfo);
	return __result;
}

_extern bool _sub_10A1C910();
bool SoundSystemInitialized() // 0x10A1C910
{
	// `anonymous-namespace'::SoundSystemInitialized
	// procedure flags: nofpo
	todo("implement");
	bool __result = _sub_10A1C910();
	return __result;
}

_extern bool _sub_10A1F160(std::vector<std::string> const &, std::string &);
bool VariableSettingsMasterVolumeUpdated(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A1F160
{
	// `anonymous-namespace'::VariableSettingsMasterVolumeUpdated
	// static ...; // 0x10A1F2D0
	// static ...; // 0x10A1F2C8
	// std::vector<std::string> const &args;
	// std::string &returnInfo;
	// std::stringstream ss;
	// unsigned long value;
	// function call : __int32 (*)(__int32, char)
	todo("implement");
	bool __result = _sub_10A1F160(args, returnInfo);
	return __result;
}

_extern bool _sub_10A20C80(std::vector<std::string> const &, std::string &);
bool VariableSettingsSfxVolumeUpdated(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A20C80
{
	// `anonymous-namespace'::VariableSettingsSfxVolumeUpdated
	// static ...; // 0x10A20DF0
	// static ...; // 0x10A20DE8
	// std::vector<std::string> const &args;
	// std::string &returnInfo;
	// std::stringstream ss;
	// unsigned long value;
	// function call : __int32 (*)(__int32, bool)
	todo("implement");
	bool __result = _sub_10A20C80(args, returnInfo);
	return __result;
}

_extern bool _sub_10A1EF40(std::vector<std::string> const &, std::string &);
bool VariableSettingsMainMenuMusicVolumeUpdated(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A1EF40
{
	// `anonymous-namespace'::VariableSettingsMainMenuMusicVolumeUpdated
	// static ...; // 0x10A1F0E0
	// static ...; // 0x10A1F0D8
	// std::vector<std::string> const &args;
	// std::string &returnInfo;
	// std::stringstream ss;
	// unsigned long value;
	// function call : bool (*const)()
	// function call : bool (*const)()
	// function call : __int32 (*)(__int32, bool)
	todo("implement");
	bool __result = _sub_10A1EF40(args, returnInfo);
	return __result;
}

_extern bool _sub_10A20200(std::vector<std::string> const &, std::string &);
bool VariableSettingsMusicVolumeUpdated(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A20200
{
	// `anonymous-namespace'::VariableSettingsMusicVolumeUpdated
	// static ...; // 0x10A203A0
	// static ...; // 0x10A20398
	// std::vector<std::string> const &args;
	// std::string &returnInfo;
	// std::stringstream ss;
	// unsigned long value;
	// function call : bool (*const)()
	// function call : bool (*const)()
	// function call : __int32 (*)(__int32, bool)
	todo("implement");
	bool __result = _sub_10A20200(args, returnInfo);
	return __result;
}

_extern bool _sub_10A1CD50(std::vector<std::string> const &, std::string &);
bool VariableAudioOutputDeviceUpdated(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A1CD50
{
	// `anonymous-namespace'::VariableAudioOutputDeviceUpdated
	// static ...; // 0x10A1CF04
	// static ...; // 0x10A1CEEC
	// static ...; // 0x10A1CEE4
	// std::vector<std::string> const &args;
	// std::string &returnInfo;
	// __int32 device;
	// std::stringstream ss;
	todo("implement");
	bool __result = _sub_10A1CD50(args, returnInfo);
	return __result;
}

_extern bool _sub_10A1C260(std::vector<std::string> const &, std::string &);
bool CommandAudioOutputDeviceList(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A1C260
{
	// `anonymous-namespace'::CommandAudioOutputDeviceList
	// static ...; // 0x10A1C3E5
	// static ...; // 0x10A1C3E0
	// static ...; // 0x10A1C3BC
	// static ...; // 0x10A1C3B4
	// std::vector<std::string> const &args;
	// std::string &returnInfo;
	// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> buffer;
	// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
	// Patches::Audio::SAudioDeviceInfo info;
	{
		// __int32 i;
	}
	todo("implement");
	bool __result = _sub_10A1C260(args, returnInfo);
	return __result;
}

_extern bool _sub_10A1CF80(std::vector<std::string> const &, std::string &);
bool VariableSettingsAnisotropicFilteringUpdate(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A1CF80
{
	// `anonymous-namespace'::VariableSettingsAnisotropicFilteringUpdate
	// static ...; // 0x10A1D13C
	// static ...; // 0x10A1D124
	// static ...; // 0x10A1D11C
	// std::vector<std::string> const &args;
	// std::string &returnInfo;
	// Pointer anisotropic_filtering_level;
	// std::stringstream ss;
	// __int32 value;
	todo("implement");
	bool __result = _sub_10A1CF80(args, returnInfo);
	return __result;
}

_extern bool _sub_10A21560(std::vector<std::string> const &, std::string &);
bool VariableSettingsSubtitlesUpdate(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A21560
{
	// `anonymous-namespace'::VariableSettingsSubtitlesUpdate
	// std::string &returnInfo;
	// s_global_preferences *prefs;
	// __int32 value;
	todo("implement");
	bool __result = _sub_10A21560(args, returnInfo);
	return __result;
}

_extern bool _sub_10A1C460(std::vector<std::string> const &, std::string &);
bool CommandResetSettings(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A1C460
{
	// `anonymous-namespace'::CommandResetSettings
	// static ...; // 0x10A1C740
	// static ...; // 0x10A1C737
	// static ...; // 0x10A1C72C
	// static ...; // 0x10A1C6FC
	// static ...; // 0x10A1C6F4
	// std::vector<std::string> const &args;
	// std::string &returnInfo;
	// std::string previous;
	// Modules::CommandMap &commandMap;
	{
		// std::deque<Modules::Command> &<range>$L0;
		// std::_Deque_unchecked_iterator<std::_Deque_val<std::_Deque_simple_types<Modules::Command> > > <begin>$L0;
		// std::_Deque_unchecked_iterator<std::_Deque_val<std::_Deque_simple_types<Modules::Command> > > <end>$L0;
		{
			// Modules::Command &cmd;
			{
				// std::string returnInfo;
			}
		}
	}
	// function call : bool (*)(std::vector<std::string> const &, std::string &)
	todo("implement");
	bool __result = _sub_10A1C460(args, returnInfo);
	return __result;
}

_extern void _sub_10A1CC20();
void UpdateScreenResolution() // 0x10A1CC20
{
	// `anonymous-namespace'::UpdateScreenResolution
	// procedure flags: nofpo
	// static ...; // 0x10A1CD03
	// static ...; // 0x10A1CCFC
	// static ...; // 0x10A1CCE4
	// static ...; // 0x10A1CCDC
	// Modules::ModuleSettings const &moduleSettings;
	// static void *(*`UpdateScreenResolution'::`2'::GetNewDisplayPreferences)(); // 0x11354108
	// void *newPrefs;
	// unsigned __int32 gameWindow;
	// static void *(*`UpdateScreenResolution'::`2'::GetDisplayPreferences)(); // 0x1135410C
	// __int32 width;
	// __int32 height;
	// function call : void *(*)()
	// function call : void *(*)()
	todo("implement");
	_sub_10A1CC20();
}

_extern bool _sub_10A1C950(std::string const &, __int32 *);
bool TryParseInt(std::string const &str, __int32 *value) // 0x10A1C950
{
	// `anonymous-namespace'::TryParseInt
	// static ...; // 0x10A1C9F0
	// static ...; // 0x10A1C9E8
	// std::string const &str;
	// __int32 *value;
	// char const *c_str;
	// char *endp;
	todo("implement");
	bool __result = _sub_10A1C950(str, value);
	return __result;
}

_extern bool _sub_10A1CA30(std::string const &, __int32 *, __int32 *);
bool TryParseResolutionString(std::string const &str, __int32 *width, __int32 *height) // 0x10A1CA30
{
	// `anonymous-namespace'::TryParseResolutionString
	// static ...; // 0x10A1CB88
	// static ...; // 0x10A1CB80
	// std::string const &str;
	// __int32 *width;
	// __int32 *height;
	// unsigned __int32 separatorPos;
	{
		// std::string heightString;
		// std::string widthString;
	}
	todo("implement");
	bool __result = _sub_10A1CA30(str, width, height);
	return __result;
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template void Pointer::WriteFast<unsigned long>(unsigned long const) const;
