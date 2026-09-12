/* ---------- headers */

#include "Modules/ModuleForge.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Forge/ForgeUndo.hpp"
#include "Forge/ForgeUtil.hpp"
#include "Forge/Geoemetry.hpp"
#include "Forge/Prefab.hpp"
#include "Modules/ModuleBase.hpp"
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
#include "Utils/EventSink.hpp"
#include "Utils/Singleton.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <algorithm>
#include <atomic>
#include <charconv>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <filesystem>
#include <forward_list>
#include <functional>
#include <initializer_list>
#include <ios>
#include <iosfwd>
#include <iterator>
#include <limits>
#include <list>
#include <memory>
#include <mutex>
#include <optional>
#include <ostream>
#include <ratio>
#include <sstream>
#include <stdexcept>
#include <stop_token>
#include <streambuf>
#include <string>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

namespace Forge
{
	struct ForgeObjectQuota;
}
namespace Forge
{
	namespace Prefabs
	{
		struct PrefabHeader;
	}
}
namespace Modules
{
	class ModuleBase;
	class ModuleForge;
}

namespace Utils {}
using namespace ::Utils;
namespace Server {}
using namespace ::Server;
namespace Server
{
	namespace VariableSynchronization {}
	using namespace Server::VariableSynchronization;
}

namespace Modules {}
using namespace ::Modules;
namespace Forge {}
using namespace ::Forge;
namespace Forge
{
	namespace Selection {}
	using namespace Forge::Selection;
	namespace Prefabs {}
	using namespace Forge::Prefabs;
}

namespace base
{
	namespace internal {}
	using namespace base::internal;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Forge::Selection { void Delete(); }  // hades: added for 0x109842D0

namespace Forge::Selection { void Clear(); }  // hades: added for 0x10984590

namespace Forge::Selection { void DeselectAllOf(); }  // hades: added for 0x109845D0

namespace Forge::Selection { void SelectAll(); }  // hades: added for 0x10985880

namespace Forge::Selection { void SelectAllMaterial(); }  // hades: added for 0x109858C0

namespace Forge::Selection { void SelectEverything(); }  // hades: added for 0x10985900

namespace Forge::Selection { void Invert(); }  // hades: added for 0x10985040

namespace Server { namespace VariableSynchronization {
	extern void Synchronize(Modules::Command *serverVariable, Modules::Command *clientVariable);
} }  // hades: added for 0x10C3D8F0, declared only inside VariableSynchronization.cpp

bool CommandDeleteAll(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandCanvas(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandDeselectAll(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandDeselectAllOf(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandSelectAll(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandSelectAllMaterial(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandSelectEverything(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandExpandSelection(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandInvertSelection(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandSavePrefab(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandLoadPrefab(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandDumpPrefabs(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandDeletePrefab(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool TryParseTagIndex(std::string const &str, unsigned __int32 *value);
bool CommandSpawnItem(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool TryParseInt(std::string const &str, __int32 *value);
bool CommandPrematchCamera(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandResetRuntime(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandForgeBudget(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandMapOptions(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandForgeUndo(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandForgeRedo(std::vector<std::string> const &Arguments, std::string &returnInfo);

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern char const PREFAB_DIR[14]; // 0x1119CB90
	extern char const PREFAB_EXT[8]; // 0x1119CBA0
}
using namespace hades_file_local;
/* ---------- public code */

namespace Modules
{
	ModuleForge::ModuleForge() : ModuleBase("Forge") /* hades-mem-init: : ModuleBase(todo_result<std::string>()) */ // 0x10982310
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0ModuleForge@Modules@@QAE@XZ");
		// Modules::ModuleForge *const this;

		VarCloneDepth = AddVariableFloat("CloneDepth", "forge_clone_depth", "Depth at which the object will be cloned", eCommandFlagsNone, 1.0f);
		VarCloneMultiplier = AddVariableInt("CloneMultiplier", "forge_clone_multiplier", "Number of consecutive times the object will be cloned", eCommandFlagsNone, 1);
		VarRotationSnap = AddVariableInt("RotationSnap", "forge_rotation_snap", "Angle at which object rotation will be snapped", eCommandFlagsArchived, 0);
		VarRotationSnap->ValueIntMin = 0;
		VarRotationSnap->ValueIntMax = 6;
		VarRotationSensitivity = AddVariableFloat("RotationSensitivity", "forge_rotation_sensitivity", "Controls the sensitivity of object rotation", eCommandFlagsArchived, 1.0f);
		VarMonitorSpeed = AddVariableInt("MonitorSpeed", "forge_monitor_speed", "Controls the movement speed of the monitor", eCommandFlagsArchived, 3);
		VarMonitorSpeed->ValueIntMin = 0;
		VarMonitorSpeed->ValueIntMax = 6;
		VarMonitorNoclip = AddVariableInt("MonitorNoclip", "forge_monitor_noclip", "Allows the monitor to pass through bsp and other objects", CommandFlags(eCommandFlagsHostOnly | eCommandFlagsArchived), 0);
		VarSelectionRenderer = AddVariableInt("SelectionRenderer", "forge_selection_renderer", "Set the selection renderer to use", eCommandFlagsArchived, 0);
		VarSelectionRenderer->ValueIntMin = 0;
		VarSelectionRenderer->ValueIntMax = 1;
		VarMagnetsEnabled = AddVariableInt("Magnets", "forge_magnets", "Controls whether magnets are enabled (1) or disabled (0)", eCommandFlagsArchived, 0);
		VarMagnetsEnabled->ValueIntMin = 0;
		VarMagnetsEnabled->ValueIntMax = 1;
		VarMagnetsVisible = AddVariableInt("MagnetsVisible", "forge_magnets_visible", "Controls whether magnets are shown (1) or hidden (0)", eCommandFlagsArchived, 1);
		VarMagnetsVisible->ValueIntMin = 0;
		VarMagnetsVisible->ValueIntMax = 1;
		VarMagnetAutogen = AddVariableInt("MagnetAutogen", "forge_magnet_autogen", "Generates forge magnets from the collision model", eCommandFlagsArchived, 0);
		VarMagnetAutogen->ValueIntMin = 0;
		VarMagnetAutogen->ValueIntMax = 1;
		VarMaxGrabDistance = AddVariableFloat("GrabDistance", "forge_grab_distance", "Controls the maximum distance from which objects can be grabbed", eCommandFlagsArchived, 5.0f);
		VarMagnetsStrength = AddVariableFloat("MagnetsStrength", "forge_magnets_strength", "Controls the minimum distance at which magnets snap", eCommandFlagsArchived, 0.3f);
		VarShowInvisibles = AddVariableInt("ShowInvisibles", "forge_show_invisibles", "When enabled forces invisible materials to be visible", CommandFlags(eCommandFlagsHostOnly | eCommandFlagsReplicated), 0);
		VarShowInvisibles->ValueIntMin = 0;
		VarShowInvisibles->ValueIntMax = 1;
		VarShowInvisiblesClient = AddVariableInt("ShowInvisiblesClient", "forge_show_invisibles_client", "When enabled forces invisible materials to be visible", eCommandFlagsInternal, 0);
		Server::VariableSynchronization::Synchronize(VarShowInvisibles, VarShowInvisiblesClient);
		VarShowWorldBounds = AddVariableInt("ShowWorldBounds", "forge_show_world_bounds", "Show the bsp world bounds", CommandFlags(eCommandFlagsHostOnly | eCommandFlagsReplicated), 0);
		VarShowWorldBounds->ValueIntMin = 0;
		VarShowWorldBounds->ValueIntMax = 1;
		VarShowWorldBoundsClient = AddVariableInt("ShowWorldBoundsClient", "forge_show_world_bounds_client", "Show the bsp world bounds", eCommandFlagsInternal, 0);
		Server::VariableSynchronization::Synchronize(VarShowWorldBounds, VarShowWorldBoundsClient);
		VarSelectionColor = AddVariableString("SelectionColor", "forge_selection_color", "Controls the forge selection color", eCommandFlagsArchived, "#7FF31F");

		AddCommand("DeleteAll", "forge_delete_all", "Delete all objects that are the same as the object under the crosshair", CommandFlags(eCommandFlagsHostOnly | eCommandFlagsForge), CommandDeleteAll);
		AddCommand("Canvas", "forge_canvas", "Delete all objects on the map", CommandFlags(eCommandFlagsHostOnly | eCommandFlagsForge), CommandCanvas);
		AddCommand("ResetRuntime", "forge_reset_runtime", "Respawn any abandoned/despawned objects", CommandFlags(eCommandFlagsHostOnly | eCommandFlagsForge), CommandResetRuntime);
		AddCommand("SelectAll", "forge_select_all", "Select all objects that are the same as the object under the crosshair", CommandFlags(eCommandFlagsHostOnly | eCommandFlagsForge), CommandSelectAll);
		AddCommand("SelectAllMaterial", "forge_select_all_material", "Select all objects with the same material", CommandFlags(eCommandFlagsHostOnly | eCommandFlagsForge), CommandSelectAllMaterial);
		AddCommand("SelectEverything", "forge_select_everything", "Select all objects on the map", CommandFlags(eCommandFlagsHostOnly | eCommandFlagsForge), CommandSelectEverything);
		AddCommand("ExpandSelection", "forge_expand_selection", "Expand the selection by a given radius", CommandFlags(eCommandFlagsHostOnly | eCommandFlagsForge), CommandExpandSelection);
		AddCommand("InvertSelection", "forge_invert_selection", "Invert the current selection", CommandFlags(eCommandFlagsHostOnly | eCommandFlagsForge), CommandInvertSelection);
		AddCommand("DeselectAll", "forge_deselect_all", "Deselect all selected objects", eCommandFlagsForge, CommandDeselectAll);
		AddCommand("DeselectAllOf", "forge_deselect_all_of", "Deselect all selected objects that are the same as the object under the crosshair", CommandFlags(eCommandFlagsHostOnly | eCommandFlagsForge), CommandDeselectAllOf);
		AddCommand("SavePrefab", "forge_prefab_save", "Save prefab to a file", CommandFlags(eCommandFlagsHostOnly | eCommandFlagsForge), CommandSavePrefab);
		AddCommand("LoadPrefab", "forge_prefab_load", "Load prefab from a file", CommandFlags(eCommandFlagsHostOnly | eCommandFlagsForge), CommandLoadPrefab);
		AddCommand("DumpPrefabs", "forge_prefab_dump", "Dump a list of saved prefabs in json", eCommandFlagsForge, CommandDumpPrefabs);
		AddCommand("DeletePrefab", "forge_prefab_delete", "Delete a saved prefab", eCommandFlagsForge, CommandDeletePrefab);
		AddCommand("SpawnItem", "forge_spawn", "Spawn an item from the forge palette", eCommandFlagsForge, CommandSpawnItem);
		AddCommand("Budget", "forge_budget", "Displays information about remaining objects", eCommandFlagsForge, CommandForgeBudget);
		AddCommand("MapOptions", "forge_map_options", "Opens map modifier object properties", eCommandFlagsForge, CommandMapOptions);
		AddCommand("SetPrematchCamera", "forge_set_prematch_camera", "Set the position/orientation of the prematch camera", CommandFlags(eCommandFlagsHostOnly | eCommandFlagsForge), CommandPrematchCamera);
		AddCommand("Undo", "forge_undo", "Undo the last action", CommandFlags(eCommandFlagsHostOnly | eCommandFlagsForge), CommandForgeUndo);
		AddCommand("Redo", "forge_redo", "Redo the undone action", CommandFlags(eCommandFlagsHostOnly | eCommandFlagsForge), CommandForgeRedo);
	}
}

/* ---------- private code */

bool CommandDeleteAll(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109842D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandDeleteAll@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandDeleteAll
	// std::string &returnInfo;

	Forge::Selection::Delete();
	return true;
}

bool CommandCanvas(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10984280
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandCanvas@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandCanvas
	// std::string &returnInfo;
	// Modules::ModuleForge &moduleForge;

	Modules::ModuleForge &moduleForge = Modules::ModuleForge::Instance();

	moduleForge.CommandState.MapCanvas = true;
	return true;
}

bool CommandDeselectAll(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10984590
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandDeselectAll@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandDeselectAll
	// std::string &returnInfo;

	Forge::Selection::Clear();
	return true;
}

bool CommandDeselectAllOf(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109845D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandDeselectAllOf@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandDeselectAllOf
	// std::string &returnInfo;

	Forge::Selection::DeselectAllOf();
	return true;
}

bool CommandSelectAll(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10985880
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandSelectAll@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandSelectAll
	// std::string &returnInfo;

	Forge::Selection::SelectAll();
	return true;
}

bool CommandSelectAllMaterial(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109858C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandSelectAllMaterial@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandSelectAllMaterial
	// std::string &returnInfo;

	Forge::Selection::SelectAllMaterial();
	return true;
}

bool CommandSelectEverything(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10985900
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandSelectEverything@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandSelectEverything
	// std::string &returnInfo;

	Forge::Selection::SelectEverything();
	return true;
}

_extern bool _sub_10984C40(std::vector<std::string> const &, std::string &);
bool CommandExpandSelection(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10984C40
{
	// `anonymous-namespace'::CommandExpandSelection
	// static ...; // 0x10984CEC
	// static ...; // 0x10984CE4
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// char *endp;
	// float radius;
	todo("implement");
	bool __result = _sub_10984C40(Arguments, returnInfo);
	return __result;
}

bool CommandInvertSelection(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10985040
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandInvertSelection@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandInvertSelection
	// std::string &returnInfo;

	Forge::Selection::Invert();
	return true;
}

_extern bool _sub_10985550(std::vector<std::string> const &, std::string &);
bool CommandSavePrefab(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10985550
{
	// `anonymous-namespace'::CommandSavePrefab
	// static ...; // 0x109857C0
	// static ...; // 0x109857A8
	// static ...; // 0x109857A0
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// Modules::ModuleForge &moduleForge;
	// std::filesystem::path p;
	// std::filesystem::path prefabDirectory;
	// std::string const &name;
	todo("implement");
	bool __result = _sub_10985550(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10985080(std::vector<std::string> const &, std::string &);
bool CommandLoadPrefab(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10985080
{
	// `anonymous-namespace'::CommandLoadPrefab
	// static ...; // 0x109852CC
	// static ...; // 0x109852B4
	// static ...; // 0x109852AC
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// Modules::ModuleForge &moduleForge;
	// std::filesystem::path p;
	// std::filesystem::path prefabDirectory;
	todo("implement");
	bool __result = _sub_10985080(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10984610(std::vector<std::string> const &, std::string &);
bool CommandDumpPrefabs(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10984610
{
	// `anonymous-namespace'::CommandDumpPrefabs
	// static ...; // 0x10984AF2
	// static ...; // 0x10984AEB
	// static ...; // 0x10984AE4
	// static ...; // 0x10984AE0
	// static ...; // 0x10984ADB
	// static ...; // 0x10984AD7
	// static ...; // 0x10984AD3
	// static ...; // 0x10984ACC
	// static ...; // 0x10984A60
	// static ...; // 0x10984A58
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// std::filesystem::directory_iterator end_itr;
	// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> buffer;
	// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
	// std::filesystem::path p;
	{
		// std::filesystem::directory_iterator itr;
		{
			// std::filesystem::path path;
			// std::string const &ext;
			// std::string const &name;
			{
				// Forge::Prefabs::PrefabHeader header;
			}
		}
	}
	todo("implement");
	bool __result = _sub_10984610(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_10984310(std::vector<std::string> const &, std::string &);
bool CommandDeletePrefab(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10984310
{
	// `anonymous-namespace'::CommandDeletePrefab
	// static ...; // 0x109844F4
	// static ...; // 0x109844DC
	// static ...; // 0x109844D4
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// std::filesystem::path p;
	// std::filesystem::path prefabDirectory;
	todo("implement");
	bool __result = _sub_10984310(Arguments, returnInfo);
	return __result;
}

bool TryParseTagIndex(std::string const &str, unsigned __int32 *value) // 0x10985B00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?TryParseTagIndex@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PAI@Z");
	// `anonymous-namespace'::TryParseTagIndex
	// static ...; // 0x10985BA0
	// static ...; // 0x10985B98
	// std::string const &str;
	// unsigned __int32 *value;
	// char const *c_str;
	// char *endp;

	if (str.length() == 0)
		return false;

	auto c_str = str.c_str();
	char* endp;

	*value = std::strtol(c_str, &endp, 16);

	return endp != c_str;
}

bool CommandSpawnItem(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10985940
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandSpawnItem@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandSpawnItem
	// static ...; // 0x109859D8
	// static ...; // 0x109859D0
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// Modules::ModuleForge &moduleForge;
	// unsigned __int32 tagIndex;

	uint32_t tagIndex;
	if (Arguments.size() < 1 || !TryParseTagIndex(Arguments[0], &tagIndex)) {
		returnInfo = "Invalid tag index";
		return false;
	}

	auto &moduleForge = Modules::ModuleForge::Instance();
	moduleForge.CommandState.SpawnItem = tagIndex;
	return true;
}

_extern bool _sub_10985A20(std::string const &, __int32 *);
bool TryParseInt(std::string const &str, __int32 *value) // 0x10985A20
{
	// `anonymous-namespace'::TryParseInt
	// static ...; // 0x10985AC0
	// static ...; // 0x10985AB8
	// std::string const &str;
	// __int32 *value;
	// char const *c_str;
	// char *endp;
	todo("implement");
	bool __result = _sub_10985A20(str, value);
	return __result;
}

_extern bool _sub_109853D0(std::vector<std::string> const &, std::string &);
bool CommandPrematchCamera(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109853D0
{
	// `anonymous-namespace'::CommandPrematchCamera
	// static ...; // 0x109854B0
	// static ...; // 0x109854A8
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// Modules::ModuleForge &moduleForge;
	{
		// __int32 team;
	}
	todo("implement");
	bool __result = _sub_109853D0(Arguments, returnInfo);
	return __result;
}

bool CommandResetRuntime(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10985500
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandResetRuntime@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandResetRuntime
	// std::string &returnInfo;
	// Modules::ModuleForge &moduleForge;

	Modules::ModuleForge &moduleForge = Modules::ModuleForge::Instance();

	moduleForge.CommandState.RuntimeReset = true;
	return true;
}

bool CommandForgeBudget(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10984D30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandForgeBudget@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandForgeBudget
	// static ...; // 0x10984EBF
	// static ...; // 0x10984EB8
	// static ...; // 0x10984E94
	// static ...; // 0x10984E8C
	// std::vector<std::string> const &Arguments;
	// std::string &returnInfo;
	// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> buffer;
	// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
	// Forge::ForgeObjectQuota const &quota;

	const auto &quota = Forge::CalculateObjectQuota();

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);

	writer.StartObject();
	writer.Key("total_used");
	writer.Int(quota.TotalObjectsUsed);
	writer.Key("total_available");
	writer.Int(quota.TotalObjectsAvailable);
	writer.Key("total_remaining");
	writer.Int(quota.TotalObjectsAvailable - quota.TotalObjectsUsed);
	writer.EndObject();

	returnInfo = buffer.GetString();
	return true;
}

bool CommandMapOptions(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10985380
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandMapOptions@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandMapOptions
	// std::string &returnInfo;
	// Modules::ModuleForge &moduleForge;

	Modules::ModuleForge &moduleForge = Modules::ModuleForge::Instance();

	moduleForge.CommandState.OpenMapOptions = true;
	return true;
}

_extern bool _sub_10984FC0(std::vector<std::string> const &, std::string &);
bool CommandForgeUndo(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10984FC0
{
	// `anonymous-namespace'::CommandForgeUndo
	// std::string &returnInfo;
	todo("implement");
	bool __result = _sub_10984FC0(Arguments, returnInfo);
	return __result;
}

bool CommandForgeRedo(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10984F40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandForgeRedo@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");
	// `anonymous-namespace'::CommandForgeRedo
	// std::string &returnInfo;

	if (!CForgeUndoManager::Instance().CanRedo())
	{
		returnInfo = "Nothing to redo";
		return false;
	}

	CForgeUndoManager::Instance().RequestRedo();
	return true;
}

namespace Modules
{
	_inline ModuleForge::s_CommandState::~s_CommandState() = default; // 0x109841D0

	_inline ModuleForge::s_CommandState::s_Prefabs::~s_Prefabs() = default; // 0x10984220
}
