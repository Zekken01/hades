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
	extern __int32 (__stdcall *SSL_SetAntialiasing)(bool);  // 0x11354098
	extern "C" __int32 (__stdcall *SSL_SetAutoCentering)(bool); // 0x1135409C
	extern "C" __int32 (__stdcall *SSL_SetContrast)(__int32); // 0x113540A0
	extern "C" __int32 (__stdcall *SSL_SetDetailsQuality)(__int32); // 0x113540A4
	extern "C" __int32 (__stdcall *SSL_SetDisplayHints)(bool); // 0x113540A8
	extern "C" __int32 (__stdcall *SSL_SetEffectsQuality)(__int32); // 0x113540AC
	extern "C" __int32 (__stdcall *SSL_SetFullscreen)(__int32); // 0x113540B0
	extern "C" __int32 (__stdcall *SSL_SetHUDShake)(bool); // 0x113540B4
	extern "C" __int32 (__stdcall *SSL_SetInvertLook)(bool); // 0x113540B8
	extern "C" __int32 (__stdcall *SSL_SetInvertMouse)(bool); // 0x113540BC
	extern "C" __int32 (__stdcall *SSL_SetLightingQuality)(__int32); // 0x113540C0
	extern "C" __int32 (__stdcall *SSL_SetLookSensitivity)(__int32); // 0x113540C4
	extern "C" __int32 (__stdcall *SSL_SetMasterVolume)(__int32, char); // 0x113540C8
	extern "C" __int32 (__stdcall *SSL_SetMotionBlur)(bool); // 0x113540CC
	extern "C" __int32 (__stdcall *SSL_SetMouseAcceleration)(__int32); // 0x113540D0
	extern "C" __int32 (__stdcall *SSL_SetMouseSensitivityHor)(__int32); // 0x113540D4
	extern "C" __int32 (__stdcall *SSL_SetMouseSensitivityVehicleHor)(__int32); // 0x113540D8
	extern "C" __int32 (__stdcall *SSL_SetMouseSensitivityVehicleVert)(__int32); // 0x113540DC
	extern "C" __int32 (__stdcall *SSL_SetMouseSensitivityVert)(__int32); // 0x113540E0
	extern __int32 (__stdcall *SSL_SetMusicVolume)(__int32, bool);  // 0x113540E4
	extern "C" __int32 (__stdcall *SSL_SetPostprocessingQuality)(__int32); // 0x113540E8
	extern "C" __int32 (__stdcall *SSL_SetSFXVolume)(__int32, bool); // 0x113540EC
	extern "C" __int32 (__stdcall *SSL_SetShadowQuality)(__int32); // 0x113540F0
	extern __int32 (__stdcall *SSL_SetTeamColor)(__int32);  // 0x113540F4
	extern "C" __int32 (__stdcall *SSL_SetTextureFilteringQuality)(__int32); // 0x113540F8
	extern "C" __int32 (__stdcall *SSL_SetTextureResolution)(__int32); // 0x113540FC
	extern "C" __int32 (__stdcall *SSL_SetToggleCrouch)(__int32); // 0x11354100
	extern "C" __int32 (*SSL_SetVSync)(__int32); // 0x11354104
}
using namespace hades_file_local;
/* ---------- public code */

namespace Modules
{
	ModuleSettings::ModuleSettings() : ModuleBase("Settings") /* hades-mem-init: : ModuleBase(todo_result<std::string>()) */ // 0x10A198C0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0ModuleSettings@Modules@@QAE@XZ");
		// Modules::ModuleSettings *const this;

		VarAntialiasing = AddVariableInt("Antialiasing", "antialiasing", "Controls whether antialiasing is disabled (0), FXAA is enabled (1)", eCommandFlagsArchived, 1, VariableSettingsAntialiasingUpdate);
		VarAutoCentering = AddVariableInt("AutoCentering", "autocenter", "Controls whether auto-centering is enabled (1) or disabled (0)", eCommandFlagsArchived, 0, VariableSettingsAutoCenteringUpdate);
		VarBrightness = AddVariableInt("Brightness", "brightness", "Controls the brightness level (0 - 100)", eCommandFlagsArchived, 50, VariableSettingsBrightnessUpdate);
		VarContrast = AddVariableInt("Contrast", "Contrast", "Controls the contrast level (0 - 100)", eCommandFlagsArchived, 50, VariableSettingsContrastUpdate);
		VarDetailsQuality = AddVariableString("DetailsQuality", "details", "Controls whether the details quality level is low, medium or high", eCommandFlagsArchived, "high", VariableSettingsDetailsQualityUpdate);
		VarDisplayHints = AddVariableInt("DisplayHints", "hints", "Controls whether displaying of hints is enabled (1) or disabled (0)", eCommandFlagsArchived, 0, VariableSettingsDisplayHintsUpdate);
		VarEffectsQuality = AddVariableString("EffectsQuality", "effects", "Controls whether the effects quality level is low, medium or high", eCommandFlagsArchived, "high", VariableSettingsEffectsQualityUpdate);
		VarFullscreen = AddVariableInt("Fullscreen", "fullscreen", "Controls whether the game is windowed (0) or fullscreen (1)", eCommandFlagsArchived, 1, VariableSettingsFullscreenUpdate);
		VarScreenResolution = AddVariableString("ScreenResolution", "resolution", "Controls the screen resolution", eCommandFlagsArchived, "default", VariableSettingsScreenResolutionUpdate);
		VarHUDShake = AddVariableInt("HUDShake", "hud_shake", "Controls whether hud shake is enabled (1) or disabled (0)", eCommandFlagsArchived, 0, VariableSettingsHUDShakeUpdate);
		VarInvertLook = AddVariableInt("InvertLook", "invert_look", "Controls whether look-inversion is enabled (1) or disabled (0)", eCommandFlagsHidden, 0, VariableSettingsInvertLookUpdate);
		VarInvertMouse = AddVariableInt("InvertMouse", "invert_mouse", "Controls whether mouse-inversion is enabled (1) or disabled (0)", eCommandFlagsArchived, 0, VariableSettingsInvertMouseUpdate);
		VarLightingQuality = AddVariableString("LightingQuality", "lighting", "Controls whether the lighting quality level is low, medium or high", eCommandFlagsArchived, "high", VariableSettingsLightingQualityUpdate);
		VarLookSensitivity = AddVariableInt("LookSensitivity", "look_sensitivity", "Controls the controller look sensitivity (0 - 100)", eCommandFlagsArchived, 50, VariableSettingsLookSensitivityUpdate);
		VarMotionBlur = AddVariableInt("MotionBlur", "motion_blur", "Controls whether motion blur is enabled (1) or disabled (0)", eCommandFlagsArchived, 1, VariableSettingsMotionBlurUpdate);
		VarMouseAcceleration = AddVariableInt("MouseAcceleration", "mouse_accel", "Controls the level of mouse acceleration (0 - 100)", eCommandFlagsArchived, 0, VariableSettingsMouseAccelerationUpdate);
		VarGamepadEnabled = AddVariableInt("Gamepad", "gamepad", "Gets whether gamepad is enabled (1) or disabled (0)", eCommandFlagsHidden, 0, nullptr);
		VarMouseSensitivityHorizontal = AddVariableInt("MouseSensitivityHorizontal", "mouse_sensitivity_hor", "Controls the horizontal mouse sensitivity (0 - 100)", eCommandFlagsArchived, 25, VariableSettingsMouseSensitivityHorizontalUpdate);
		VarMouseSensitivityVertical = AddVariableInt("MouseSensitivityVertical", "mouse_sensitivity_vert", "Controls the vertical mouse sensitivity (0 - 100)", eCommandFlagsArchived, 25, VariableSettingsMouseSensitivityVerticalUpdate);
		VarMouseSensitivityVehicleHorizontal = AddVariableInt("MouseSensitivityVehicleHorizontal", "mouse_sensitivity_vehicle_hor", "Controls the horizontal mouse sensitivity for vehicles (0 - 100)", eCommandFlagsArchived, 25, VariableSettingsMouseSensitivityVehicleHorizontalUpdate);
		VarMouseSensitivityVehicleVertical = AddVariableInt("MouseSensitivityVehicleVertical", "mouse_sensitivity_vehicle_vert", "Controls the vertical mouse sensitivity for vehicles (0 - 100)", eCommandFlagsArchived, 25, VariableSettingsMouseSensitivityVehicleVerticalUpdate);
		VarPlayerMarkerColors = AddVariableString("PlayerMarkerColors", "markers", "Controls whether the player marker colors are default, ally or armor", eCommandFlagsArchived, "default", VariableSettingsPlayerMarkerColorsUpdate);
		VarPostprocessingQuality = AddVariableString("PostprocessingQuality", "postprocessing", "Controls whether the postprocessing quality level is low, medium or high", eCommandFlagsArchived, "high", VariableSettingsPostprocessingQualityUpdate);
		VarShadowQuality = AddVariableString("ShadowQuality", "shadows", "Controls whether the shadow quality level is low, medium or high", eCommandFlagsArchived, "high", VariableSettingsShadowQualityUpdate);
		VarShadowResolution = AddVariableInt("ShadowResolution", "shadow_res", "Controls global shadow map resolution", CommandFlags(eCommandFlagsArchived | eCommandFlagsDontUpdateInitial), 1024, VariableSettingsShadowResolutionUpdate);
		VarTextureFilteringQuality = AddVariableString("TextureFilteringQuality", "texture_filtering", "Controls whether the texture-filtering quality level is low, medium or high", eCommandFlagsArchived, "high", VariableSettingsTextureFilteringQualityUpdate);
		VarTextureResolution = AddVariableString("TextureResolution", "textures", "Controls whether the texture resolution level is low, medium or high", eCommandFlagsArchived, "high", VariableSettingsTextureResolutionUpdate);
		VarToggleCrouch = AddVariableInt("ToggleCrouch", "toggle_crouch", "Controls whether crouch-toggling is enabled (1) or disabled (0)", eCommandFlagsArchived, 0, VariableSettingsToggleCrouchUpdate);
		VarFpJumpLandAnimationsDisabled = AddVariableInt("FirstPersonJumpAndLand", "FirstPersonJumpAndLand", "Controls whether the Halo Online FP Jump/Land/Fall Animations are enabled", eCommandFlagsArchived, 1, nullptr);
		VarVSync = AddVariableInt("VSync", "vsync", "Controls whether vertical sync is enabled (1) or disabled (0)", eCommandFlagsArchived, 1, VariableSettingsVSyncUpdate);
		VarMasterVolume = AddVariableInt("MasterVolume", "volume", "Controls the master volume", CommandFlags(eCommandFlagsArchived | eCommandFlagsDontUpdateInitial), 100, VariableSettingsMasterVolumeUpdated);
		VarSfxVolume = AddVariableInt("SfxVolume", "volume_sfx", "Controls the sfx volume", CommandFlags(eCommandFlagsArchived | eCommandFlagsDontUpdateInitial), 100, VariableSettingsSfxVolumeUpdated);
		VarMusicVolume = AddVariableInt("InGameMusicVolume", "volume_music_in_game", "Controls the music volume during matches", CommandFlags(eCommandFlagsArchived | eCommandFlagsDontUpdateInitial), 100, VariableSettingsMusicVolumeUpdated);
		VarMainMenuMusicVolume = AddVariableInt("MainMenuMusicVolume", "volume_main_menu_music", "Controls the main menu music volume", CommandFlags(eCommandFlagsArchived | eCommandFlagsDontUpdateInitial), 100, VariableSettingsMainMenuMusicVolumeUpdated);
		VarAudioOutputDevice = AddVariableInt("AudioOutputDevice", "audio_out", "Sets the audio output device to use (0) being system default", eCommandFlagsArchived, 0, VariableAudioOutputDeviceUpdated);
		VarAnisotropicFiltering = AddVariableInt("AnisotropicFiltering", "anisotropic_filtering", "Sets the anisotropic filtering quality level", eCommandFlagsArchived, 0, VariableSettingsAnisotropicFilteringUpdate);
		VarMusicInLobby = AddVariableInt("MusicInLobby", "music_in_lobby", "Sets whether music should play after returning to the lobby", eCommandFlagsArchived, 1, nullptr);
		VarMusicInLobby->ValueIntMin = 0;
		VarMusicInLobby->ValueIntMax = 1;
		VarPersistentLobby = AddVariableInt("PersistentLobby", "persistent_lobby", "Sets whether the lobby will try to set the previously loaded map, variant type and mod from previous sessions", eCommandFlagsArchived, 1, nullptr);
		VarPersistentLobby->ValueIntMin = 0;
		VarPersistentLobby->ValueIntMax = 1;
		VarMotionBlurStrength = AddVariableFloat("MotionBlurStrength", "motion_blur_strength", "Controls motion blur strength", eCommandFlagsArchived, 0.125f, VariableSettingsMotionBlurStrengthUpdate);
		VarMotionBlurStrength->ValueFloatMin = 0.0f;
		VarMotionBlurStrength->ValueFloatMax = 1.0f;
		VarMotionBlurAlways = AddVariableInt("MotionBlurAlways", "motion_blur_always", "Specifies whether to always apply motion blur or only with camera movement", eCommandFlagsArchived, 0, VariableSettingsMotionBlurAlwaysUpdate);
		VarMotionBlurAlways->ValueIntMin = 0;
		VarMotionBlurAlways->ValueIntMax = 1;
		VarDecoratorDistance = AddVariableFloat("DecoratorDistance", "decorator_distance", "Decorator render distance", eCommandFlagsArchived, 1.0f, nullptr);
		VarDecoratorDistance->ValueFloatMin = 0.0f;
		VarLODDistance = AddVariableFloat("LODDistance", "lod_distance", "LOD render distance scale", eCommandFlagsArchived, 1.0f, nullptr);
		VarLODDistance->ValueFloatMin = 1.0f;
		VarLODDistance->ValueFloatMax = 10.0f;
		VarSsao = AddVariableInt("SSAO", "ssao", "Enable or disable SSAO", eCommandFlagsArchived, 1, VariableSettingsSsaoUpdate);
		VarSsao->ValueIntMin = 0;
		VarSsao->ValueIntMax = 1;
		VarSubtitles = AddVariableInt("Subtitles", "subtitles", "Changes subtitles display setting (0 = Auto; 1 = On; 2 = Off)", eCommandFlagsArchived, 0, VariableSettingsSubtitlesUpdate);
		VarSubtitles->ValueIntMin = 0;
		VarSubtitles->ValueIntMax = 2;
		VarExposureCpu = AddVariableInt("ExposureCpu", "exposure_cpu", "Disables GPU occlusion for exposure/bloom and calculates it on the CPU instead", eCommandFlagsArchived, 0, nullptr);
		VarExposureCpu->ValueIntMin = 0;
		VarExposureCpu->ValueIntMax = 1;

		AddCommand("AudioOutputDeviceList", "audio_out_devs", "List available audio output devices", eCommandFlagsNone, CommandAudioOutputDeviceList);
		AddCommand("Reset", "settings_reset", "Restores default settings", eCommandFlagsNone, CommandResetSettings);
	}

	void ModuleSettings::GetScreenResolution(__int32 *width, __int32 *height) const // 0x10A1C820
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetScreenResolution@ModuleSettings@Modules@@QBEXPAH0@Z");
		// __int32 *height;
		// Modules::ModuleSettings const &moduleSettings;
		// std::string const &resolutionStr;
			// unsigned long fullScreen;
		// function call : __int32 (__int32)
		// function call : __int32 (__int32)

		const auto& moduleSettings = Modules::ModuleSettings::Instance();
		const auto& resolutionStr = moduleSettings.VarScreenResolution->ValueString;

		if (!TryParseResolutionString(resolutionStr, width, height))
		{
			auto fullScreen = Modules::ModuleSettings::Instance().VarFullscreen->ValueInt;
			if (fullScreen)
			{
				*width = GetSystemMetrics(SM_CXSCREEN);
				*height = GetSystemMetrics(SM_CYSCREEN);
			}
			else
			{
				*width = 1280;
				*height = 720;
			}
		}
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

bool VariableSettingsAutoCenteringUpdate(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A1D470
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariableSettingsAutoCenteringUpdate@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::VariableSettingsAutoCenteringUpdate
	// static ...; // 0x10A1D60C
	// static ...; // 0x10A1D604
	// std::vector<std::string> const &args;
	// std::string &returnInfo;
	// std::stringstream ss;
	// bool statusBool;
	// unsigned long value;
	// function call : __int32 (*)(bool)

	auto value = Modules::ModuleSettings::Instance().VarAutoCentering->ValueInt;
	auto statusBool = (value != 0);

	if (value < 0 || value > 1)
		return false;

	SSL_SetAutoCentering(statusBool);

	std::stringstream ss;
	ss << "Auto-Centering " << (statusBool ? "enabled." : "disabled.");
	returnInfo = ss.str();
	return true;
}

bool VariableSettingsBrightnessUpdate(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A1D690
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariableSettingsBrightnessUpdate@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::VariableSettingsBrightnessUpdate
	// static ...; // 0x10A1D7D8
	// static ...; // 0x10A1D7D0
	// std::vector<std::string> const &args;
	// std::string &returnInfo;
	// std::stringstream ss;
	// unsigned long value;

	auto value = Modules::ModuleSettings::Instance().VarBrightness->ValueInt;

	if (value < 0 || value > 100)
		return false;

	*reinterpret_cast<int*>(0x022C0128 + 0x41BD8) = static_cast<int>(value);

	std::stringstream ss;
	ss << "Brightness set to " << value << ".";
	returnInfo = ss.str();
	return true;
}

bool VariableSettingsContrastUpdate(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A1D840
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariableSettingsContrastUpdate@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::VariableSettingsContrastUpdate
	// static ...; // 0x10A1D9A0
	// static ...; // 0x10A1D998
	// std::vector<std::string> const &args;
	// std::string &returnInfo;
	// std::stringstream ss;
	// unsigned long value;
	// function call : __int32 (*)(__int32)

	auto value = Modules::ModuleSettings::Instance().VarContrast->ValueInt;

	if (value < 0 || value > 100)
		return false;

	SSL_SetContrast(value);

	std::stringstream ss;
	ss << "Contrast set to " << value << ".";
	returnInfo = ss.str();
	return true;
}

bool VariableSettingsDetailsQualityUpdate(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A1DA10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariableSettingsDetailsQualityUpdate@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
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

	auto value = Modules::ModuleSettings::Instance().VarDetailsQuality->ValueString;

	if (!(value == "low" || value == "medium" || value == "high"))
		return false;

	auto intValue = value == "low" ? 0 : value == "medium" ? 1 : 2;

	SSL_SetDetailsQuality(intValue);

	std::stringstream ss;
	ss << "Details Quality set to " << value << ".";
	returnInfo = ss.str();
	return true;
}

bool VariableSettingsDisplayHintsUpdate(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A1DCF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariableSettingsDisplayHintsUpdate@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::VariableSettingsDisplayHintsUpdate
	// static ...; // 0x10A1DE8C
	// static ...; // 0x10A1DE84
	// std::vector<std::string> const &args;
	// std::string &returnInfo;
	// std::stringstream ss;
	// bool statusBool;
	// unsigned long value;
	// function call : __int32 (*)(bool)

	auto value = Modules::ModuleSettings::Instance().VarDisplayHints->ValueInt;
	auto statusBool = (value != 0);

	if (value < 0 || value > 1)
		return false;

	SSL_SetDisplayHints(statusBool);

	std::stringstream ss;
	ss << "Displaying of hints " << (statusBool ? "enabled." : "disabled.");
	returnInfo = ss.str();
	return true;
}

bool VariableSettingsEffectsQualityUpdate(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A1DF10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariableSettingsEffectsQualityUpdate@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
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

	auto value = Modules::ModuleSettings::Instance().VarEffectsQuality->ValueString;

	if (!(value == "low" || value == "medium" || value == "high"))
		return false;

	auto intValue = value == "low" ? 0 : value == "medium" ? 1 : 2;

	SSL_SetEffectsQuality(intValue);

	std::stringstream ss;
	ss << "Effects Quality set to " << value << ".";
	returnInfo = ss.str();
	return true;
}

bool VariableSettingsFullscreenUpdate(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A1E200
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariableSettingsFullscreenUpdate@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
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

	const auto& moduleSettings = Modules::ModuleSettings::Instance();
	auto value = moduleSettings.VarFullscreen->ValueInt;
	auto statusBool = (value != 0);

	if (value < 0 || value > 1)
		return false;

	SSL_SetFullscreen(statusBool);
	UpdateScreenResolution();

	std::stringstream ss;
	ss << "Fullscreen " << (statusBool ? "enabled." : "disabled.");
	returnInfo = ss.str();
	return true;
}

bool VariableSettingsHUDShakeUpdate(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A1E430
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariableSettingsHUDShakeUpdate@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::VariableSettingsHUDShakeUpdate
	// static ...; // 0x10A1E5CC
	// static ...; // 0x10A1E5C4
	// std::vector<std::string> const &args;
	// std::string &returnInfo;
	// std::stringstream ss;
	// bool statusBool;
	// unsigned long value;
	// function call : __int32 (*)(bool)

	auto value = Modules::ModuleSettings::Instance().VarHUDShake->ValueInt;
	auto statusBool = (value != 0);

	if (value < 0 || value > 1)
		return false;

	SSL_SetHUDShake(statusBool);

	std::stringstream ss;
	ss << "HUD Shake " << (statusBool ? "enabled." : "disabled.");
	returnInfo = ss.str();
	return true;
}

bool VariableSettingsInvertLookUpdate(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A1E650
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariableSettingsInvertLookUpdate@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::VariableSettingsInvertLookUpdate
	// static ...; // 0x10A1E7EC
	// static ...; // 0x10A1E7E4
	// std::vector<std::string> const &args;
	// std::string &returnInfo;
	// std::stringstream ss;
	// bool statusBool;
	// unsigned long value;
	// function call : __int32 (*)(bool)

	auto value = Modules::ModuleSettings::Instance().VarInvertLook->ValueInt;
	auto statusBool = (value != 0);

	if (value < 0 || value > 1)
		return false;

	SSL_SetInvertLook(statusBool);

	std::stringstream ss;
	ss << "Invert Look " << (statusBool ? "enabled." : "disabled.");
	returnInfo = ss.str();
	return true;
}

bool VariableSettingsInvertMouseUpdate(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A1E870
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariableSettingsInvertMouseUpdate@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::VariableSettingsInvertMouseUpdate
	// static ...; // 0x10A1EA0C
	// static ...; // 0x10A1EA04
	// std::vector<std::string> const &args;
	// std::string &returnInfo;
	// std::stringstream ss;
	// bool statusBool;
	// unsigned long value;
	// function call : __int32 (*)(bool)

	auto value = Modules::ModuleSettings::Instance().VarInvertMouse->ValueInt;
	auto statusBool = (value != 0);

	if (value < 0 || value > 1)
		return false;

	SSL_SetInvertMouse(statusBool);

	std::stringstream ss;
	ss << "Invert Mouse " << (statusBool ? "enabled." : "disabled.");
	returnInfo = ss.str();
	return true;
}

bool VariableSettingsLightingQualityUpdate(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A1EA90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariableSettingsLightingQualityUpdate@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
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

	auto value = Modules::ModuleSettings::Instance().VarLightingQuality->ValueString;

	if (!(value == "low" || value == "medium" || value == "high"))
		return false;

	auto intValue = value == "low" ? 0 : value == "medium" ? 1 : 2;

	SSL_SetLightingQuality(intValue);

	std::stringstream ss;
	ss << "Lighting Quality set to " << value << ".";
	returnInfo = ss.str();
	return true;
}

bool VariableSettingsLookSensitivityUpdate(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A1ED70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariableSettingsLookSensitivityUpdate@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::VariableSettingsLookSensitivityUpdate
	// static ...; // 0x10A1EED0
	// static ...; // 0x10A1EEC8
	// std::vector<std::string> const &args;
	// std::string &returnInfo;
	// std::stringstream ss;
	// unsigned long value;
	// function call : __int32 (*)(__int32)

	auto value = Modules::ModuleSettings::Instance().VarLookSensitivity->ValueInt;

	if (value < 0 || value > 100)
		return false;

	SSL_SetLookSensitivity(value);

	std::stringstream ss;
	ss << "Look Sensitivity set to " << value << ".";
	returnInfo = ss.str();
	return true;
}

bool VariableSettingsMotionBlurUpdate(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A1F6D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariableSettingsMotionBlurUpdate@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::VariableSettingsMotionBlurUpdate
	// static ...; // 0x10A1F86C
	// static ...; // 0x10A1F864
	// std::vector<std::string> const &args;
	// std::string &returnInfo;
	// std::stringstream ss;
	// bool statusBool;
	// unsigned long value;
	// function call : __int32 (*)(bool)

	auto value = Modules::ModuleSettings::Instance().VarMotionBlur->ValueInt;
	auto statusBool = (value != 0);

	if (value < 0 || value > 1)
		return false;

	SSL_SetMotionBlur(statusBool);

	std::stringstream ss;
	ss << "Motion Blur " << (statusBool ? "enabled." : "disabled.");
	returnInfo = ss.str();
	return true;
}

bool VariableSettingsMotionBlurStrengthUpdate(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A1F530
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariableSettingsMotionBlurStrengthUpdate@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::VariableSettingsMotionBlurStrengthUpdate
	// static ...; // 0x10A1F668
	// static ...; // 0x10A1F660
	// std::vector<std::string> const &args;
	// std::string &returnInfo;
	// std::stringstream ss;
	// float value;

	auto value = Modules::ModuleSettings::Instance().VarMotionBlurStrength->ValueFloat;

	c_rasterizer_globals::g_motion_blur_parameters_set = 0;

	std::stringstream ss;
	ss << "Motion blur strength set to " << value;
	returnInfo = ss.str();
	return true;
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

bool VariableSettingsMouseAccelerationUpdate(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A1F8F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariableSettingsMouseAccelerationUpdate@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::VariableSettingsMouseAccelerationUpdate
	// static ...; // 0x10A1FA50
	// static ...; // 0x10A1FA48
	// std::vector<std::string> const &args;
	// std::string &returnInfo;
	// std::stringstream ss;
	// unsigned long value;
	// function call : __int32 (*)(__int32)

	auto value = Modules::ModuleSettings::Instance().VarMouseAcceleration->ValueInt;

	if (value < 0 || value > 100)
		return false;

	SSL_SetMouseAcceleration(value);

	std::stringstream ss;
	ss << "Mouse Acceleration set to " << value << ".";
	returnInfo = ss.str();
	return true;
}

bool VariableSettingsMouseSensitivityHorizontalUpdate(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A1FAC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariableSettingsMouseSensitivityHorizontalUpdate@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::VariableSettingsMouseSensitivityHorizontalUpdate
	// static ...; // 0x10A1FC20
	// static ...; // 0x10A1FC18
	// std::vector<std::string> const &args;
	// std::string &returnInfo;
	// std::stringstream ss;
	// unsigned long value;
	// function call : __int32 (*)(__int32)

	auto value = Modules::ModuleSettings::Instance().VarMouseSensitivityHorizontal->ValueInt;

	if (value < 0 || value > 100)
		return false;

	SSL_SetMouseSensitivityHor(value);

	std::stringstream ss;
	ss << "Mouse Sensitivity Horizontal set to " << value << ".";
	returnInfo = ss.str();
	return true;
}

bool VariableSettingsMouseSensitivityVerticalUpdate(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A20030
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariableSettingsMouseSensitivityVerticalUpdate@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::VariableSettingsMouseSensitivityVerticalUpdate
	// static ...; // 0x10A20190
	// static ...; // 0x10A20188
	// std::vector<std::string> const &args;
	// std::string &returnInfo;
	// std::stringstream ss;
	// unsigned long value;
	// function call : __int32 (*)(__int32)

	auto value = Modules::ModuleSettings::Instance().VarMouseSensitivityVertical->ValueInt;

	if (value < 0 || value > 100)
		return false;

	SSL_SetMouseSensitivityVert(value);

	std::stringstream ss;
	ss << "Mouse Sensitivity Vertical set to " << value << ".";
	returnInfo = ss.str();
	return true;
}

bool VariableSettingsMouseSensitivityVehicleHorizontalUpdate(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A1FC90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariableSettingsMouseSensitivityVehicleHorizontalUpdate@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::VariableSettingsMouseSensitivityVehicleHorizontalUpdate
	// static ...; // 0x10A1FDF0
	// static ...; // 0x10A1FDE8
	// std::vector<std::string> const &args;
	// std::string &returnInfo;
	// std::stringstream ss;
	// unsigned long value;
	// function call : __int32 (*)(__int32)

	auto value = Modules::ModuleSettings::Instance().VarMouseSensitivityVehicleHorizontal->ValueInt;

	if (value < 0 || value > 100)
		return false;

	SSL_SetMouseSensitivityVehicleHor(value);

	std::stringstream ss;
	ss << "Mouse Sensitivity Vehicle Horizontal set to " << value << ".";
	returnInfo = ss.str();
	return true;
}

bool VariableSettingsMouseSensitivityVehicleVerticalUpdate(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A1FE60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariableSettingsMouseSensitivityVehicleVerticalUpdate@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::VariableSettingsMouseSensitivityVehicleVerticalUpdate
	// static ...; // 0x10A1FFC0
	// static ...; // 0x10A1FFB8
	// std::vector<std::string> const &args;
	// std::string &returnInfo;
	// std::stringstream ss;
	// unsigned long value;
	// function call : __int32 (*)(__int32)

	auto value = Modules::ModuleSettings::Instance().VarMouseSensitivityVehicleVertical->ValueInt;

	if (value < 0 || value > 100)
		return false;

	SSL_SetMouseSensitivityVehicleVert(value);

	std::stringstream ss;
	ss << "Mouse Sensitivity Vehicle Vertical set to " << value << ".";
	returnInfo = ss.str();
	return true;
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

bool VariableSettingsPostprocessingQualityUpdate(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A20740
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariableSettingsPostprocessingQualityUpdate@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
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

	auto value = Modules::ModuleSettings::Instance().VarPostprocessingQuality->ValueString;

	if (!(value == "low" || value == "medium" || value == "high"))
		return false;

	auto intValue = value == "low" ? 0 : value == "medium" ? 1 : 2;

	SSL_SetPostprocessingQuality(intValue);

	std::stringstream ss;
	ss << "Postprocessing Quality set to " << value << ".";
	returnInfo = ss.str();
	return true;
}

bool VariableSettingsShadowQualityUpdate(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A20E60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariableSettingsShadowQualityUpdate@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
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

	auto value = Modules::ModuleSettings::Instance().VarShadowQuality->ValueString;

	if (!(value == "low" || value == "medium" || value == "high"))
		return false;

	auto intValue = value == "low" ? 0 : value == "medium" ? 1 : 2;

	SSL_SetShadowQuality(intValue);

	std::stringstream ss;
	ss << "Shadow Quality set to " << value << ".";
	returnInfo = ss.str();
	return true;
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

bool VariableSettingsTextureFilteringQualityUpdate(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A215E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariableSettingsTextureFilteringQualityUpdate@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
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

	auto value = Modules::ModuleSettings::Instance().VarTextureFilteringQuality->ValueString;

	if (!(value == "low" || value == "medium" || value == "high"))
		return false;

	auto intValue = value == "low" ? 0 : value == "medium" ? 1 : 2;

	SSL_SetTextureFilteringQuality(intValue);

	std::stringstream ss;
	ss << "Texture Filtering Quality set to " << value << ".";
	returnInfo = ss.str();
	return true;
}

bool VariableSettingsTextureResolutionUpdate(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A218D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariableSettingsTextureResolutionUpdate@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
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

	auto value = Modules::ModuleSettings::Instance().VarTextureResolution->ValueString;

	if (!(value == "low" || value == "medium" || value == "high"))
		return false;

	auto intValue = value == "low" ? 0 : value == "medium" ? 1 : 2;

	SSL_SetTextureResolution(intValue);

	std::stringstream ss;
	ss << "Texture Resolution set to " << value << ".";
	returnInfo = ss.str();
	return true;
}

bool VariableSettingsToggleCrouchUpdate(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A21BC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariableSettingsToggleCrouchUpdate@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::VariableSettingsToggleCrouchUpdate
	// static ...; // 0x10A21D60
	// static ...; // 0x10A21D58
	// std::vector<std::string> const &args;
	// std::string &returnInfo;
	// std::stringstream ss;
	// bool statusBool;
	// unsigned long value;
	// function call : __int32 (*)(__int32)

	auto value = Modules::ModuleSettings::Instance().VarToggleCrouch->ValueInt;
	auto statusBool = (value != 0);

	if (value < 0 || value > 1)
		return false;

	SSL_SetToggleCrouch(statusBool);

	std::stringstream ss;
	ss << "Toggle Crouch " << (statusBool ? "enabled." : "disabled.");
	returnInfo = ss.str();
	return true;
}

bool VariableSettingsVSyncUpdate(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A21DE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariableSettingsVSyncUpdate@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::VariableSettingsVSyncUpdate
	// static ...; // 0x10A21F84
	// static ...; // 0x10A21F7C
	// std::vector<std::string> const &args;
	// std::string &returnInfo;
	// std::stringstream ss;
	// bool statusBool;
	// unsigned long value;
	// function call : __int32 (*)(__int32)

	auto value = Modules::ModuleSettings::Instance().VarVSync->ValueInt;
	auto statusBool = (value != 0);

	if (value < 0 || value > 1)
		return false;

	SSL_SetVSync(statusBool);

	std::stringstream ss;
	ss << "Vertical Sync " << (statusBool ? "enabled." : "disabled.");
	returnInfo = ss.str();
	return true;
}

bool VariableSettingsScreenResolutionUpdate(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A20A20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariableSettingsScreenResolutionUpdate@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
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

	const auto& moduleSettings = Modules::ModuleSettings::Instance();
	auto value = moduleSettings.VarScreenResolution->ValueString;

	int width, height;
	if (!TryParseResolutionString(value, &width, &height) && value != "default")
		return false;

	UpdateScreenResolution();

	std::stringstream ss;
	ss << "Screen Resolution set to " << value << ".";
	returnInfo = ss.str();

	return true;
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

bool VariableSettingsMasterVolumeUpdated(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A1F160
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariableSettingsMasterVolumeUpdated@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::VariableSettingsMasterVolumeUpdated
	// static ...; // 0x10A1F2D0
	// static ...; // 0x10A1F2C8
	// std::vector<std::string> const &args;
	// std::string &returnInfo;
	// std::stringstream ss;
	// unsigned long value;
	// function call : __int32 (*)(__int32, char)

	auto value = Modules::ModuleSettings::Instance().VarMasterVolume->ValueInt;
	if (value < 0 || value > 100)
		return false;

	if (SoundSystemInitialized())
		SSL_SetMasterVolume(value, true);

	std::stringstream ss;
	ss << "Master Volume set to " << value << ".";
	returnInfo = ss.str();

	return true;
}

bool VariableSettingsSfxVolumeUpdated(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A20C80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariableSettingsSfxVolumeUpdated@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::VariableSettingsSfxVolumeUpdated
	// static ...; // 0x10A20DF0
	// static ...; // 0x10A20DE8
	// std::vector<std::string> const &args;
	// std::string &returnInfo;
	// std::stringstream ss;
	// unsigned long value;
	// function call : __int32 (*)(__int32, bool)

	auto value = Modules::ModuleSettings::Instance().VarSfxVolume->ValueInt;
	if (value < 0 || value > 100)
		return false;

	if (SoundSystemInitialized())
		SSL_SetSFXVolume(value, true);

	std::stringstream ss;
	ss << "Sfx Volume set to " << value << ".";
	returnInfo = ss.str();

	return true;
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

bool VariableAudioOutputDeviceUpdated(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A1CD50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariableAudioOutputDeviceUpdated@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::VariableAudioOutputDeviceUpdated
	// static ...; // 0x10A1CF04
	// static ...; // 0x10A1CEEC
	// static ...; // 0x10A1CEE4
	// std::vector<std::string> const &args;
	// std::string &returnInfo;
	// __int32 device;
	// std::stringstream ss;

	if (!SoundSystemInitialized())
		return true;

	int device;
	if (args.size() < 1 || !TryParseInt(args[0], &device) || device < 0)
		return false;


	if (!Patches::Audio::SetOutputDevice(device))
	{
		returnInfo = "Error setting audo output device.";
		return false;
	}

	std::stringstream ss;
	ss << "Audio output device set to " << device << ".";
	returnInfo = ss.str();

	return true;
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

bool VariableSettingsSubtitlesUpdate(std::vector<std::string> const &args, std::string &returnInfo) // 0x10A21560
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariableSettingsSubtitlesUpdate@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::VariableSettingsSubtitlesUpdate
	// std::string &returnInfo;
	// s_global_preferences *prefs;
	// __int32 value;

	__int32 value = Modules::ModuleSettings::Instance().VarSubtitles->ValueInt;

	s_global_preferences *prefs = tls_getd().preferences;
	if (!prefs)
		prefs = reinterpret_cast<s_global_preferences *>(0x022C0128);

	prefs->current.settings.display_subtitles = static_cast<s_global_preferences_settings::e_display_subtitles>(value);
	return true;
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

void UpdateScreenResolution() // 0x10A1CC20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?UpdateScreenResolution@@YAXXZ");
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

	auto gameWindow = *(uint32_t*)0x0199C014;
	if (!gameWindow)
		return;

	const auto& moduleSettings = Modules::ModuleSettings::Instance();

	int width, height;
	moduleSettings.GetScreenResolution(&width, &height);

	static auto GetNewDisplayPreferences = (void*(*)())(0xA1FC60);
	static auto GetDisplayPreferences = (void*(*)())(0x00A1FC50);
	auto newPrefs = GetNewDisplayPreferences();
	memcpy(newPrefs, GetDisplayPreferences(), 0x38u);

	*(int32_t *)newPrefs = width;
	*((int32_t*)newPrefs + 1) = height;
	*(uint8_t*)0x050DD9D1 = 1; // dirty
}

bool TryParseInt(std::string const &str, __int32 *value) // 0x10A1C950
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?TryParseInt@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PAH@Z");
	// `anonymous-namespace'::TryParseInt
	// static ...; // 0x10A1C9F0
	// static ...; // 0x10A1C9E8
	// std::string const &str;
	// __int32 *value;
	// char const *c_str;
	// char *endp;

	if (str.length() == 0)
		return false;

	auto c_str = str.c_str();
	char *endp;

	*value = std::strtol(c_str, &endp, 10);

	return endp != c_str;
}

bool TryParseResolutionString(std::string const &str, __int32 *width, __int32 *height) // 0x10A1CA30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?TryParseResolutionString@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PAH1@Z");
	// `anonymous-namespace'::TryParseResolutionString
	// static ...; // 0x10A1CB88
	// static ...; // 0x10A1CB80
	// std::string const &str;
	// __int32 *width;
	// __int32 *height;
	// unsigned __int32 separatorPos;
		// std::string heightString;
		// std::string widthString;

	auto separatorPos = str.find("x");
	if (separatorPos != std::string::npos && separatorPos + 1 < str.length())
	{
		auto widthString = str.substr(0, separatorPos);
		auto heightString = str.substr(separatorPos + 1);

		return TryParseInt(widthString, width) && TryParseInt(heightString, height);
	}

	return false;
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template void Pointer::WriteFast<unsigned long>(unsigned long const) const;
