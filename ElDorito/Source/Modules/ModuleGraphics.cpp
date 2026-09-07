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

bool VariableSaturationUpdate(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool VariableRedHueUpdate(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool VariableGreenHueUpdate(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool VariableBlueHueUpdate(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool VariableGammaPowerUpdate(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool VariableDepthOfFieldUpdate(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool VariableLetterboxUpdate(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool VariableUIScalingUpdate(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool VariableCustomHUDColorsEnabledUpdate(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool VariableCustomHUDColorsUpdate(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandSupportedResolutions(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);

/* ---------- globals */

s_depth_of_field *(*s_depth_of_field::get)(); // 0x11353FE0

/* ---------- private variables */

/* ---------- public code */

namespace Modules
{
	extern ModuleGraphics* _sub_109A4B30(Modules::ModuleGraphics *const);
	ModuleGraphics::ModuleGraphics() : ModuleBase(todo_result<std::basic_string<char,std::char_traits<char>,std::allocator<char> >>()) // 0x109A4B30
	{
		mangled_x86(MANGLED_TODO, "??0ModuleGraphics@Modules@@QAE@XZ");
		// Modules::ModuleGraphics *const this;
		todo("implement");
		_sub_109A4B30(this);
	}
}

/* ---------- private code */

_extern bool _sub_109A7060(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool VariableSaturationUpdate(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x109A7060
{
	// `anonymous-namespace'::VariableSaturationUpdate
	// static ...; // 0x109A71B4
	// static ...; // 0x109A71AC
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// s_hue_saturation_control *hue_saturation_control;
	// std::basic_stringstream<char,std::char_traits<char>,std::allocator<char> > ss;
	// float saturation;
	todo("implement");
	bool __result = _sub_109A7060(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_109A6EA0(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool VariableRedHueUpdate(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x109A6EA0
{
	// `anonymous-namespace'::VariableRedHueUpdate
	// static ...; // 0x109A6FF4
	// static ...; // 0x109A6FEC
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// s_hue_saturation_control *hue_saturation_control;
	// std::basic_stringstream<char,std::char_traits<char>,std::allocator<char> > ss;
	// float redHue;
	todo("implement");
	bool __result = _sub_109A6EA0(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_109A6AE0(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool VariableGreenHueUpdate(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x109A6AE0
{
	// `anonymous-namespace'::VariableGreenHueUpdate
	// static ...; // 0x109A6C34
	// static ...; // 0x109A6C2C
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// s_hue_saturation_control *hue_saturation_control;
	// float greenHue;
	// std::basic_stringstream<char,std::char_traits<char>,std::allocator<char> > ss;
	todo("implement");
	bool __result = _sub_109A6AE0(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_109A61F0(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool VariableBlueHueUpdate(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x109A61F0
{
	// `anonymous-namespace'::VariableBlueHueUpdate
	// static ...; // 0x109A6344
	// static ...; // 0x109A633C
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// s_hue_saturation_control *hue_saturation_control;
	// std::basic_stringstream<char,std::char_traits<char>,std::allocator<char> > ss;
	// float blueHue;
	todo("implement");
	bool __result = _sub_109A61F0(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_109A6930(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool VariableGammaPowerUpdate(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x109A6930
{
	// `anonymous-namespace'::VariableGammaPowerUpdate
	// static ...; // 0x109A6A74
	// static ...; // 0x109A6A6C
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// float gamma;
	// std::basic_stringstream<char,std::char_traits<char>,std::allocator<char> > ss;
	// float max;
	todo("implement");
	bool __result = _sub_109A6930(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_109A6760(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool VariableDepthOfFieldUpdate(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x109A6760
{
	// `anonymous-namespace'::VariableDepthOfFieldUpdate
	// static ...; // 0x109A68C0
	// static ...; // 0x109A68B8
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// float dof;
	// std::basic_stringstream<char,std::char_traits<char>,std::allocator<char> > ss;
	// s_depth_of_field *globals;
	// function call : s_depth_of_field *(*)()
	todo("implement");
	bool __result = _sub_109A6760(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_109A6CA0(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool VariableLetterboxUpdate(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x109A6CA0
{
	// `anonymous-namespace'::VariableLetterboxUpdate
	// static ...; // 0x109A6E20
	// static ...; // 0x109A6E18
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// unsigned long enabled;
	// std::basic_stringstream<char,std::char_traits<char>,std::allocator<char> > ss;
	// s_cinematic_globals *globals;
	todo("implement");
	bool __result = _sub_109A6CA0(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_109A7220(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool VariableUIScalingUpdate(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x109A7220
{
	// `anonymous-namespace'::VariableUIScalingUpdate
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	todo("implement");
	bool __result = _sub_109A7220(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_109A63B0(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool VariableCustomHUDColorsEnabledUpdate(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x109A63B0
{
	// `anonymous-namespace'::VariableCustomHUDColorsEnabledUpdate
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	todo("implement");
	bool __result = _sub_109A63B0(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_109A6410(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool VariableCustomHUDColorsUpdate(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x109A6410
{
	// `anonymous-namespace'::VariableCustomHUDColorsUpdate
	// static ...; // 0x109A66A4
	// static ...; // 0x109A668C
	// static ...; // 0x109A6684
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// std::basic_regex<char,std::regex_traits<char> > expression;
	// std::match_results<char const *,std::allocator<std::sub_match<char const *> > > what;
	todo("implement");
	bool __result = _sub_109A6410(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_109A5EA0(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandSupportedResolutions(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x109A5EA0
{
	// `anonymous-namespace'::CommandSupportedResolutions
	// static ...; // 0x109A6136
	// static ...; // 0x109A6128
	// static ...; // 0x109A6104
	// static ...; // 0x109A60FC
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> buffer;
	// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
	// __int32 adapterIndex;
	{
		// std::vector<Common::D3DAdapters::DisplayMode,std::allocator<Common::D3DAdapters::DisplayMode> > const &<range>$L0;
		// Common::D3DAdapters::DisplayMode const *<begin>$L0;
		// Common::D3DAdapters::DisplayMode const *<end>$L0;
		{
			// Common::D3DAdapters::DisplayMode const &d;
			{
				// std::basic_string<char,std::char_traits<char>,std::allocator<char> > resolutionStr;
			}
		}
	}
	todo("implement");
	bool __result = _sub_109A5EA0(Arguments, returnInfo);
	return __result;
}
