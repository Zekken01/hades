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

namespace Patches { namespace Ui { extern __int32 customPrimaryHUDColor; extern __int32 customSecondaryHUDColor; } }  // hades: added for 0x109A6410

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

s_depth_of_field *(*s_depth_of_field::get)() = reinterpret_cast<decltype(s_depth_of_field::get)>(0xA3EB00); // 0x11353FE0

/* ---------- private variables */

/* ---------- public code */

namespace Modules
{
	ModuleGraphics::ModuleGraphics() : ModuleBase("Graphics") /* hades-mem-init: : ModuleBase(todo_result<std::string>()) */ // 0x109A4B30
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0ModuleGraphics@Modules@@QAE@XZ");

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

bool VariableSaturationUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109A7060
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariableSaturationUpdate@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	float saturation = Modules::ModuleGraphics::Instance().VarSaturation->ValueFloat;
	s_hue_saturation_control *hue_saturation_control = tls_getd().hue_saturation_control;
	if (!hue_saturation_control)
		return false;

	hue_saturation_control->saturation_base = saturation;
	std::stringstream ss;
	ss << "Set saturation to " << saturation;
	returnInfo = ss.str();
	return true;
}

bool VariableRedHueUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109A6EA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariableRedHueUpdate@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	float redHue = Modules::ModuleGraphics::Instance().VarRedHue->ValueFloat;
	s_hue_saturation_control *hue_saturation_control = tls_getd().hue_saturation_control;
	if (!hue_saturation_control)
		return false;

	hue_saturation_control->red_scale = redHue;
	std::stringstream ss;
	ss << "Set red hue to " << redHue;
	returnInfo = ss.str();
	return true;
}

bool VariableGreenHueUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109A6AE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariableGreenHueUpdate@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	float greenHue = Modules::ModuleGraphics::Instance().VarGreenHue->ValueFloat;
	s_hue_saturation_control *hue_saturation_control = tls_getd().hue_saturation_control;
	if (!hue_saturation_control)
		return false;

	hue_saturation_control->green_scale = greenHue;
	std::stringstream ss;
	ss << "Set green hue to " << greenHue;
	returnInfo = ss.str();
	return true;
}

bool VariableBlueHueUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109A61F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariableBlueHueUpdate@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	float blueHue = Modules::ModuleGraphics::Instance().VarGreenHue->ValueFloat;
	s_hue_saturation_control *hue_saturation_control = tls_getd().hue_saturation_control;
	if (!hue_saturation_control)
		return false;

	hue_saturation_control->blue_scale = blueHue;
	std::stringstream ss;
	ss << "Set blue hue to " << blueHue;
	returnInfo = ss.str();
	return true;
}

bool VariableGammaPowerUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109A6930
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariableGammaPowerUpdate@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	float max = Modules::ModuleGraphics::Instance().VarGammaPower->ValueFloatMax;
	float gamma = Modules::ModuleGraphics::Instance().VarGammaPower->ValueFloat;
	std::stringstream ss;
	ss << "Set gamma to " << gamma;
	returnInfo = ss.str();
	return true;
}

bool VariableDepthOfFieldUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109A6760
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariableDepthOfFieldUpdate@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	float dof = Modules::ModuleGraphics::Instance().VarDepthOfField->ValueFloat;
	s_depth_of_field *globals = s_depth_of_field::get();
	if (!globals)
		return false;

	globals->enabled = true;
	globals->focus_depth = dof;
	std::stringstream ss;
	ss << "Set depth of field intensity to " << dof;
	returnInfo = ss.str();
	return true;
}

bool VariableLetterboxUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109A6CA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariableLetterboxUpdate@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	unsigned long enabled = Modules::ModuleGraphics::Instance().VarLetterbox->ValueInt;
	s_cinematic_globals *globals = tls_getd().cinematic_globals;
	if (!globals)
		return false;

	globals->letter_box_enabled = enabled ? true : false;
	std::stringstream ss;
	ss << (enabled ? "Enabled" : "Disabled") << " letterbox";
	returnInfo = ss.str();
	return true;
}

bool VariableUIScalingUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109A7220
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariableUIScalingUpdate@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

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

bool VariableCustomHUDColorsUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109A6410
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariableCustomHUDColorsUpdate@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	std::match_results<char const *,std::allocator<std::sub_match<char const *> > > what;
	std::regex expression("#([A-Fa-f0-9]{6}|[A-Fa-f0-9]{3})");
	if (std::regex_match(Modules::ModuleGraphics::Instance().VarCustomHUDColorsPrimary->ValueString.c_str(), what, expression))
		Patches::Ui::customPrimaryHUDColor = std::stoi(Modules::ModuleGraphics::Instance().VarCustomHUDColorsPrimary->ValueString.substr(1), 0, 16);
	else
	{
		returnInfo = "Invalid Primary Color";
		return false;
	}

	if (std::regex_match(Modules::ModuleGraphics::Instance().VarCustomHUDColorsSecondary->ValueString.c_str(), what, expression))
		Patches::Ui::customSecondaryHUDColor = std::stoi(Modules::ModuleGraphics::Instance().VarCustomHUDColorsSecondary->ValueString.substr(1), 0, 16);
	else
	{
		returnInfo = "Invalid Secondary Color";
		return false;
	}
	return true;
}

bool CommandSupportedResolutions(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109A5EA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandSupportedResolutions@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	__int32 adapterIndex = Common::D3DAdapters::GetCurrentAdapterIndex();
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	writer.StartArray();
	for (auto &d : Common::D3DAdapters::GetAdapterDisplayModes(adapterIndex))
	{
		std::string resolutionStr = std::to_string(d.width) + "x" + std::to_string(d.height);
		writer.String(resolutionStr.c_str());
	}
	writer.EndArray();
	returnInfo = buffer.GetString();
	return true;
}
