/* ---------- headers */

#include "Modules/ModuleGraphics.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/cutscene/cinematics.hpp"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/tls.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/render/camera_fx_settings.hpp"
#include "Blam/render/depth_of_field.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/D3D/D3DAdapters.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "ElDorito.hpp"
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
#include "Utils/Macros.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <algorithm>
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
#include <locale>
#include <memory>
#include <ostream>
#include <regex>
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
struct end;
struct s_cinematic_globals;
struct s_depth_of_field;
struct s_hue_saturation_control;
namespace Common
{
	namespace D3DAdapters
	{
		struct DisplayMode;
	}
}
namespace Modules
{
	class ModuleBase;
	class ModuleGraphics;
}

namespace Utils {}
using namespace ::Utils;
namespace Utils
{
	namespace AntiCheat {}
	using namespace Utils::AntiCheat;
}

namespace Server {}
using namespace ::Server;
namespace Server
{
	namespace VariableSynchronization {}
	using namespace Server::VariableSynchronization;
}

namespace Modules {}
using namespace ::Modules;
namespace Common {}
using namespace ::Common;
namespace Common
{
	namespace D3DAdapters {}
	using namespace Common::D3DAdapters;
}

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
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Patches { namespace Ui { extern bool enableCustomHUDColors; } }  // hades: added for 0x109A63B0

namespace Patches::Ui { void ApplyUIResolution(); }  // hades: added for 0X109A7220

bool VariableSaturationUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool VariableRedHueUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool VariableGreenHueUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool VariableBlueHueUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool VariableGammaPowerUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool VariableDepthOfFieldUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool VariableLetterboxUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool VariableUIScalingUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool VariableCustomHUDColorsEnabledUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool VariableCustomHUDColorsUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandSupportedResolutions(std::vector<std::string> const &Arguments, std::string &returnInfo);

/* ---------- globals */

s_depth_of_field *(*s_depth_of_field::get)(); // 0x11353FE0

/* ---------- private variables */

/* ---------- public code */

namespace Modules
{
	ModuleGraphics::ModuleGraphics() : ModuleBase("Graphics") /* hades-mem-init: : ModuleBase(todo_result<std::string>()) */ // 0x109A4B30
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0ModuleGraphics@Modules@@QAE@XZ");
		// Modules::ModuleGraphics *const this;

		VarSaturation = AddVariableFloat("Saturation", "saturation", "The saturation", eCommandFlagsArchived, 1.0f, VariableSaturationUpdate);
		VarSaturation->ValueFloatMin = -10.0f;
		VarSaturation->ValueFloatMax = 10.0f;

		VarRedHue = AddVariableFloat("RedHue", "red_hue", "The red hue", eCommandFlagsNone, 1.0f, VariableRedHueUpdate);
		VarRedHue->ValueFloatMin = 0.0f;
		VarRedHue->ValueFloatMax = 1.0f;

		VarGreenHue = AddVariableFloat("GreenHue", "green_hue", "The green hue", eCommandFlagsNone, 1.0f, VariableGreenHueUpdate);
		VarGreenHue->ValueFloatMin = 0.0f;
		VarGreenHue->ValueFloatMax = 1.0f;

		VarBlueHue = AddVariableFloat("BlueHue", "blue_hue", "The blue hue", eCommandFlagsNone, 1.0f, VariableBlueHueUpdate);
		VarBlueHue->ValueFloatMin = 0.0f;
		VarBlueHue->ValueFloatMax = 1.0f;

		VarGammaPower = AddVariableFloat("Gamma", "gamma", "Global gamma. 3.6 is the default, 4.0 is equivalent to the gamma in previous versions of ElDewrito.", eCommandFlagsArchived, 3.6f, VariableGammaPowerUpdate);
		VarGammaPower->ValueFloatMin = 0.0f;
		VarGammaPower->ValueFloatMax = 5.0f;

		VarContrailsEnabled = AddVariableInt("ContrailsEnabled", "gfx_contrails", "Determines whether contrail systems are enabled.", eCommandFlagsArchived, 1, nullptr);
		VarContrailsEnabled->ValueIntMin = 0;
		VarContrailsEnabled->ValueIntMax = 1;

		VarParticlesEnabled = AddVariableInt("ParticlesEnabled", "gfx_particles", "Determines whether particle systems are enabled.", eCommandFlagsArchived, 1, nullptr);
		VarParticlesEnabled->ValueIntMin = 0;
		VarParticlesEnabled->ValueIntMax = 1;

		VarDecalsEnabled = AddVariableInt("DecalsEnabled", "gfx_decals", "Determines whether decal systems are enabled.", eCommandFlagsArchived, 1, nullptr);
		VarDecalsEnabled->ValueIntMin = 0;
		VarDecalsEnabled->ValueIntMax = 1;

		VarReflectionsEnabled = AddVariableInt("ReflectionsEnabled", "gfx_reflections", "Determines whether reflections are enabled.", eCommandFlagsArchived, 0, nullptr);
		VarReflectionsEnabled->ValueIntMin = 0;
		VarReflectionsEnabled->ValueIntMax = 1;

		VarDepthOfField = AddVariableFloat("DepthOfField", "dof", "The camera's depth of field", eCommandFlagsNone, 0.0f, VariableDepthOfFieldUpdate);
		VarDepthOfField->ValueFloatMin = 0.0f;
		VarDepthOfField->ValueFloatMax = 1.0f;

		VarLetterbox = AddVariableInt("Letterbox", "letterbox", "A cinematic letterbox.", eCommandFlagsNone, 0, VariableLetterboxUpdate);
		VarLetterbox->ValueIntMin = 0;
		VarLetterbox->ValueIntMax = 1;

		VarUIScaling = AddVariableInt("UIScaling", "uiscaling", "Enables proper UI scaling to match your monitor's resolution.", eCommandFlagsArchived, 1, VariableUIScalingUpdate);
		VarUIScaling->ValueIntMin = 0;
		VarUIScaling->ValueIntMax = 1;

		VarDisableContrails = AddVariableInt("DisableContrails", "disablecontrails", "Disables the contrail renderer.", eCommandFlagsArchived, 0, nullptr);
		VarDisableContrails->ValueIntMin = 0;
		VarDisableContrails->ValueIntMax = 1;

		VarCustomHUDColorsEnabled = AddVariableInt("CustomHUDColorsEnabled", "hud_colors", "Enables custom heads up display colors.", eCommandFlagsArchived, 0, VariableCustomHUDColorsEnabledUpdate);
		VarCustomHUDColorsEnabled->ValueIntMin = 0;
		VarCustomHUDColorsEnabled->ValueIntMax = 1;

		VarCenteredHUD = AddVariableInt("CenteredHUD", "hud_centered", "Center the HUD for ultrawide displays", eCommandFlagsArchived, 1, nullptr);
		VarCenteredHUD->ValueIntMin = 0;
		VarCenteredHUD->ValueIntMax = 1;

		VarHUDScaleX = AddVariableFloat("HUDScaleX", "hud_scale_x", "", eCommandFlagsNone, 1.0f, nullptr);

		VarForceDefaultLighting = AddVariableInt("ForceDefaultLighting", "force_default_lighting", "When disabled uses a single SH light probe for all lighting", eCommandFlagsNone, 0, nullptr);
		VarForceDefaultLighting->ValueIntMin = 0;
		VarForceDefaultLighting->ValueIntMax = 1;

		VarCustomHUDColorsPrimary = AddVariableString("CustomHUDColorsPrimary", "hud_colors_1", "Change the primary custom HUD color.", eCommandFlagsArchived, "#0E6249", VariableCustomHUDColorsUpdate);
		VarCustomHUDColorsSecondary = AddVariableString("CustomHUDColorsSecondary", "hud_colors_2", "Change the primary custom HUD color.", eCommandFlagsArchived, "#27CB9B", VariableCustomHUDColorsUpdate);

		VarFrameRateLimit = AddVariableInt("FrameRateLimit", "frame_rate_limit", "Limits the render frame rate. Set to 0 to unlock the frame rate (VSync must also be disabled)", eCommandFlagsHidden, 60, nullptr);

		AddCommand("SupportedResolutions", "supported_resolutions", "List the supported screen resolutions", eCommandFlagsNone, CommandSupportedResolutions);
	}
}

/* ---------- private code */

_extern bool _sub_109A7060(std::vector<std::string> const &, std::string &);
bool VariableSaturationUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109A7060
{
	// `anonymous-namespace'::VariableSaturationUpdate
	// static ...; // 0x109A71B4
	// static ...; // 0x109A71AC
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// s_hue_saturation_control *hue_saturation_control;
	// std::stringstream ss;
	// float saturation;
	todo("implement");
	bool __result = _sub_109A7060(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_109A6EA0(std::vector<std::string> const &, std::string &);
bool VariableRedHueUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109A6EA0
{
	// `anonymous-namespace'::VariableRedHueUpdate
	// static ...; // 0x109A6FF4
	// static ...; // 0x109A6FEC
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// s_hue_saturation_control *hue_saturation_control;
	// std::stringstream ss;
	// float redHue;
	todo("implement");
	bool __result = _sub_109A6EA0(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_109A6AE0(std::vector<std::string> const &, std::string &);
bool VariableGreenHueUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109A6AE0
{
	// `anonymous-namespace'::VariableGreenHueUpdate
	// static ...; // 0x109A6C34
	// static ...; // 0x109A6C2C
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// s_hue_saturation_control *hue_saturation_control;
	// float greenHue;
	// std::stringstream ss;
	todo("implement");
	bool __result = _sub_109A6AE0(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_109A61F0(std::vector<std::string> const &, std::string &);
bool VariableBlueHueUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109A61F0
{
	// `anonymous-namespace'::VariableBlueHueUpdate
	// static ...; // 0x109A6344
	// static ...; // 0x109A633C
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// s_hue_saturation_control *hue_saturation_control;
	// std::stringstream ss;
	// float blueHue;
	todo("implement");
	bool __result = _sub_109A61F0(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_109A6930(std::vector<std::string> const &, std::string &);
bool VariableGammaPowerUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109A6930
{
	// `anonymous-namespace'::VariableGammaPowerUpdate
	// static ...; // 0x109A6A74
	// static ...; // 0x109A6A6C
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// float gamma;
	// std::stringstream ss;
	// float max;
	todo("implement");
	bool __result = _sub_109A6930(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_109A6760(std::vector<std::string> const &, std::string &);
bool VariableDepthOfFieldUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109A6760
{
	// `anonymous-namespace'::VariableDepthOfFieldUpdate
	// static ...; // 0x109A68C0
	// static ...; // 0x109A68B8
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// float dof;
	// std::stringstream ss;
	// s_depth_of_field *globals;
	// function call : s_depth_of_field *(*)()
	todo("implement");
	bool __result = _sub_109A6760(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_109A6CA0(std::vector<std::string> const &, std::string &);
bool VariableLetterboxUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109A6CA0
{
	// `anonymous-namespace'::VariableLetterboxUpdate
	// static ...; // 0x109A6E20
	// static ...; // 0x109A6E18
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// unsigned long enabled;
	// std::stringstream ss;
	// s_cinematic_globals *globals;
	todo("implement");
	bool __result = _sub_109A6CA0(Arguments, returnInfo);
	return __result;
}

bool VariableUIScalingUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109A7220
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariableUIScalingUpdate@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::VariableUIScalingUpdate
	// std::string &returnInfo;

	if (!Modules::ModuleGraphics::Instance().VarUIScaling->ValueInt)
	{
		returnInfo = "The changes will apply on game restart";
	}
	else if (ElDorito::Instance().GameHasMenuShown)
	{
		Patches::Ui::ApplyUIResolution();
	}
	return true;
}

bool VariableCustomHUDColorsEnabledUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109A63B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariableCustomHUDColorsEnabledUpdate@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::VariableCustomHUDColorsEnabledUpdate
	// std::string &returnInfo;

	if (Utils::Singleton<Modules::ModuleGraphics>::Instance().VarCustomHUDColorsEnabled->ValueInt == 1)
	{
		Patches::Ui::enableCustomHUDColors = true;
	}
	else
	{
		Patches::Ui::enableCustomHUDColors = false;
	}

	return true;
}

_extern bool _sub_109A6410(std::vector<std::string> const &, std::string &);
bool VariableCustomHUDColorsUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109A6410
{
	// `anonymous-namespace'::VariableCustomHUDColorsUpdate
	// static ...; // 0x109A66A4
	// static ...; // 0x109A668C
	// static ...; // 0x109A6684
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// std::regex expression;
	// std::match_results<char const *,std::allocator<std::sub_match<char const *> > > what;
	todo("implement");
	bool __result = _sub_109A6410(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_109A5EA0(std::vector<std::string> const &, std::string &);
bool CommandSupportedResolutions(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109A5EA0
{
	// `anonymous-namespace'::CommandSupportedResolutions
	// static ...; // 0x109A6136
	// static ...; // 0x109A6128
	// static ...; // 0x109A6104
	// static ...; // 0x109A60FC
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> buffer;
	// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
	// __int32 adapterIndex;
	{
		// std::vector<Common::D3DAdapters::DisplayMode> const &<range>$L0;
		// Common::D3DAdapters::DisplayMode const *<begin>$L0;
		// Common::D3DAdapters::DisplayMode const *<end>$L0;
		{
			// Common::D3DAdapters::DisplayMode const &d;
			{
				// std::string resolutionStr;
			}
		}
	}
	todo("implement");
	bool __result = _sub_109A5EA0(Arguments, returnInfo);
	return __result;
}
