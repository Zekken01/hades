/* ---------- headers */

#include "Modules/ModuleDebug.hpp"
#include "hades/hades.h"

#include "Blam/BlamNetwork.hpp"
#include "Blam/cache/cache_files.hpp"
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
#include "Blam/memory/data_array.inl"
#include "Blam/memory/data_iterator.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/object_definitions.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Console/Console.hpp"
#include "ElDorito.hpp"
#include "Modules/ModuleBase.hpp"
#include "Patches/CustomPackets.hpp"
#include "Pointer.hpp"
#include "ThirdParty/rapidjson/allocators.h"
#include "ThirdParty/rapidjson/encodedstream.h"
#include "ThirdParty/rapidjson/error/error.h"
#include "ThirdParty/rapidjson/internal/biginteger.h"
#include "ThirdParty/rapidjson/internal/diyfp.h"
#include "ThirdParty/rapidjson/internal/ieee754.h"
#include "ThirdParty/rapidjson/internal/pow10.h"
#include "ThirdParty/rapidjson/internal/strtod.h"
#include "ThirdParty/rapidjson/memorystream.h"
#include "ThirdParty/rapidjson/reader.h"
#include "Utils/CommandLineUtils.hpp"
#include "Utils/Macros.hpp"
#include "Utils/Rectangle.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"
#include "Web/Ui/Screen.hpp"
#include "Web/Ui/ScreenLayer.hpp"
#include "Web/WebRenderer.hpp"
#include "Web/WebRendererApp.hpp"
#include "Web/WebRendererRenderHandler.hpp"
#include "Web/WebRenderHandlerOsr.hpp"

#include "Modules/ModuleServer.hpp"  // hades: added for 0x10980230
#include <format>  // hades: added for 0x10980230
#include <shellapi.h>  // hades: added for 0x10980230

#include <base/cef_atomic_ref_count.h>
#include <base/cef_lock.h>
#include <base/cef_logging.h>
#include <base/cef_platform_thread.h>
#include <base/cef_ref_counted.h>
#include <base/cef_scoped_refptr.h>
#include <base/cef_thread_checker.h>
#include <base/internal/cef_lock_impl.h>
#include <boost/asio.hpp>
#include <boost/assert.hpp>
#include <boost/exception/all.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/parameter/aux_/use_default_tag.hpp>
#include <boost/throw_exception.hpp>
#include <cef_app.h>
#include <cef_audio_handler.h>
#include <cef_base.h>
#include <cef_browser_process_handler.h>
#include <cef_client.h>
#include <cef_command_handler.h>
#include <cef_context_menu_handler.h>
#include <cef_devtools_message_observer.h>
#include <cef_dialog_handler.h>
#include <cef_display_handler.h>
#include <cef_download_handler.h>
#include <cef_drag_handler.h>
#include <cef_extension_handler.h>
#include <cef_find_handler.h>
#include <cef_focus_handler.h>
#include <cef_frame_handler.h>
#include <cef_jsdialog_handler.h>
#include <cef_keyboard_handler.h>
#include <cef_life_span_handler.h>
#include <cef_load_handler.h>
#include <cef_menu_model_delegate.h>
#include <cef_print_handler.h>
#include <cef_render_handler.h>
#include <cef_render_process_handler.h>
#include <cef_request_handler.h>
#include <cef_resource_handler.h>
#include <cef_resource_request_handler.h>
#include <d3dx9core.h>
#include <d3dx9math.h>
#include <d3dx9math.inl>
#include <internal/cef_string_wrappers.h>
#include <internal/cef_types_wrappers.h>
#include <internal/cef_win.h>

#include <Windows.h>
#include <boost/align/detail/align_up.hpp>
#include <boost/align/detail/is_alignment.hpp>
#include <boost/current_function.hpp>
#include <boost/mp11/algorithm.hpp>
#include <boost/mp11/detail/mp_count.hpp>
#include <boost/parameter/aux_/void.hpp>
#include <intsafe.h>
#include <roapi.h>
#include <roerrorapi.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <weakreference.h>
#include <wrl/client.h>
#include <wrl/event.h>
#include <wrl/implements.h>
#include <wrl/internal.h>
#include <wrl/module.h>
#include <wrl/wrappers/corewrappers.h>
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
#include <istream>
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

struct begin;
struct end;
struct lambda_1;
struct s_object_definition;
struct s_object_header;
namespace Blam
{
	namespace Network
	{
		struct Session;
	}
}
namespace Modules
{
	class ModuleBase;
	class ModuleDebug;
}
namespace Web
{
	namespace Browser
	{
		class WebRenderer;
	}
}
namespace Web
{
	namespace Ui
	{
		namespace ScreenLayer
		{
			struct SDialogShowParams;
		}
	}
}

namespace Utils {}
using namespace ::Utils;
namespace Utils
{
	namespace AntiCheat {}
	using namespace Utils::AntiCheat;
}

namespace base {}
using namespace ::base;
namespace base
{
	namespace cef_subtle {}
	using namespace base::cef_subtle;
	namespace cef_internal {}
	using namespace base::cef_internal;
	namespace internal {}
	using namespace base::internal;
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
namespace Windows {}
using namespace ::Windows;
namespace Windows
{
	namespace Foundation {}
	using namespace Windows::Foundation;
}

namespace Windows
{
	namespace Foundation
	{
		namespace Diagnostics {}
		using namespace Windows::Foundation::Diagnostics;
	}
}

namespace ABI {}
using namespace ::ABI;
namespace Web {}
using namespace ::Web;
namespace Web
{
	namespace Ui {}
	using namespace Web::Ui;
}

namespace Web
{
	namespace Ui
	{
		namespace ScreenLayer {}
		using namespace Web::Ui::ScreenLayer;
	}
}

namespace Web
{
	namespace Browser {}
	using namespace Web::Browser;
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge {}
		using namespace Web::Browser::Bridge;
	}
}

namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace DeterminismDebug {}
	using namespace Patches::DeterminismDebug;
}

namespace Console {}
using namespace ::Console;
namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Network {}
	using namespace Blam::Network;
}

/* ---------- constants */

/* ---------- definitions */

//class CommandDialogTest::__l2::<lambda_1>
//{
//public:
//	void operator()(std::string const &) const;
//};
//static_assert(sizeof(CommandDialogTest::__l2::<lambda_1>) == 1, "Invalid CommandDialogTest::__l2::<lambda_1> size");

/* ---------- prototypes */

namespace Server { namespace VariableSynchronization { extern void Synchronize(Modules::Command *serverVariable, Modules::Command *clientVariable); } }  // hades: added for 0x1097C0F0

extern s_cache_file_tag_globals *g_cache_file_tag_globals;  // hades: added for 0x1097FBB0
extern char const *tag_get_name(long tag_index);  // hades: added for 0x1097FBB0
extern char const *tag_to_string(unsigned long tag, char *dest, long dest_length);  // hades: added for 0x1097FBB0

#include "Blam/objects/multiplayer_game_objects.hpp"  // hades: added for 0x10980000
extern bool (*const game_engine_is_sandbox)();  // hades: added for 0x10980000
extern void *(*const tag_get)(unsigned long, long);  // hades: added for 0x10980000

long tag_find_by_name(unsigned long group_tag, char const *name);  // hades: added for 0x1097FE30

namespace Patches { namespace DeterminismDebug { extern bool StopRandomTrace(); } }  // hades: added for 0x10981420

namespace Patches::DeterminismDebug { bool StartRandomTrace(std::string const &); }  // hades: added for 0X10981370

bool CommandCrash(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandNuke(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandDumpTags(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandDialogTest(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandDebugTint(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandRasterizerSetZPlanes(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandTeleportToCamera(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandReflectionDebug(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandStartRandomTrace(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandStopRandomTrace(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandCefOpenURL(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandLaunchClient(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandTileWindows(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandRenderGeoHitTest(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandGameShowCrte(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandHideForgeObjects(std::vector<std::string> const &Arguments, std::string &returnInfo);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Modules
{
	ModuleDebug::ModuleDebug() : ModuleBase("Debug") /* hades-mem-init: : ModuleBase(todo_result<std::string>()) */ // 0x1097C0F0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0ModuleDebug@Modules@@QAE@XZ");

		teleportToCamera = 0;
		VarCollisionTest = AddVariableInt("CollisionTest", "debug_collision_test", "Displays info about the collision surface under the crosshair", eCommandFlagsNone, 0);
		VarClusters = AddVariableInt("Clusters", "debug_clusters", "Display the clusters of the current structure bsp", CommandFlags(eCommandFlagsClientAllowable | eCommandFlagsHostOnly), 0);
		VarCollisionModels = AddVariableInt("CollisionModels", "debug_collision_models", "Displays object collision model geometry", CommandFlags(eCommandFlagsClientAllowable | eCommandFlagsHostOnly), 0);
		VarPhysicsModels = AddVariableInt("PhysicsModels", "debug_physics_models", "Displays object physics model geometry", CommandFlags(eCommandFlagsClientAllowable | eCommandFlagsHostOnly), 0);
		VarStructureCollision = AddVariableInt("StructureCollision", "debug_structure_collision", "Displays structure collision geometry", CommandFlags(eCommandFlagsClientAllowable | eCommandFlagsHostOnly), 0);
		VarMarkerGroups = AddVariableInt("MarkerGroups", "debug_marker_groups", "Displays object markers", CommandFlags(eCommandFlagsClientAllowable | eCommandFlagsHostOnly), 0);
		VarMarkerGroupFilter = AddVariableString("MarkerGroupFilter", "debug_marker_group_filter", "Filter which marker groups are displayed", eCommandFlagsNone, "");
		VarDamageAoe = AddVariableInt("DamageAOE", "debug_damage_aoe", "Debug damage area of effect", CommandFlags(eCommandFlagsClientAllowable | eCommandFlagsHostOnly), 0);
		VarDamageAoeDisplayTime = AddVariableFloat("DamageAOEDisplayTime", "debug_damage_aoe_display_time", "Controls the duration of damage area of effect display", eCommandFlagsNone, 2.0f);
		VarTriggerVolumes = AddVariableInt("TriggerVolumes", "debug_trigger_volumes", "Displays trigger volumes", CommandFlags(eCommandFlagsClientAllowable | eCommandFlagsHostOnly), 0);
		VarVisibility = AddVariableInt("Visibility", "debug_visibility", "", CommandFlags(eCommandFlagsClientAllowable | eCommandFlagsHostOnly), 0);
		VarAcrophobia = AddVariableInt("Acrophobia", "debug_acrophobia", "", eCommandFlagsHostOnly, 0);
		VarAcrophobiaClient = AddVariableInt("AcrophobiaClient", "debug_acrophobia_client", "", eCommandFlagsInternal, 0);
		Server::VariableSynchronization::Synchronize(VarAcrophobia, VarAcrophobiaClient);
		VarPlayerDamageDisabled = AddVariableInt("PlayerDamageDisabled", "debug_player_damage_disabled", "Players take no damage", eCommandFlagsHostOnly, 0);
		VarPlayerDamageDisabledClient = AddVariableInt("PlayerDamageDisabledClient", "debug_player_damage_disabled_client", "Players take no damage", eCommandFlagsInternal, 0);
		Server::VariableSynchronization::Synchronize(VarPlayerDamageDisabled, VarPlayerDamageDisabledClient);
		VarMapBarriersDisabled = AddVariableInt("MapBarriersDisabled", "debug_map_barriers_disabled", "Disables map push/death barriers", eCommandFlagsHostOnly, 0);
		VarMapBarriersDisabledClient = AddVariableInt("MapBarriersDisabledClient", "debug_map_barriers_disabled_client", "Disables map push/death barriers", eCommandFlagsInternal, 0);
		Server::VariableSynchronization::Synchronize(VarMapBarriersDisabled, VarMapBarriersDisabledClient);
		VarSoundDebug = AddVariableInt("SoundSources", "debug_sound_sources", "Displays info about the current active sound sources.", eCommandFlagsNone, 0);
		VarLoopingSoundDebug = AddVariableInt("LoopingSounds", "debug_looping_sounds", "Displays info about the current active looping sounds.", eCommandFlagsNone, 0);
		VarSoundFilters = AddVariableInt("FilterSounds", "debug_override_sound_class", "Ignore all sound class excepts the specified value. 65 means all sound classes.", eCommandFlagsNone, 0x41);
		VarScriptTrace = AddVariableInt("ScriptTrace", "debug_script_trace", "Enable script tracing", eCommandFlagsNone, 0);
		VarScriptTraceFile = AddVariableString("ScriptTraceFile", "debug_script_trace_file", "File to trace to", eCommandFlagsNone, "");
		VarScriptName = AddVariableString("ScriptName", "debug_script_name", "Filter trace to the given script", eCommandFlagsNone, "");
		VarHideForgeObjects = AddVariableInt("HideForgeObjects", "hide_forge_objects", "Hides all forge specific objects", CommandFlags(eCommandFlagsClientAllowable | eCommandFlagsHostOnly), 0, CommandHideForgeObjects);
		VarHideForgeObjects->ValueIntMin = 0;
		VarHideForgeObjects->ValueIntMax = 1;
		VarHavokStats = AddVariableInt("HavokStats", "debug_havok_stats", "Displays havok memory stats", eCommandFlagsNone, 0);
		VarFModStats = AddVariableInt("FModStats", "debug_fmod", "Displays stats from FMOD", eCommandFlagsNone, 0);
		VarTraceFilter = AddVariableString("TraceFilter", "debug_trace_filter", "Only messages containing this string will be displayed", eCommandFlagsArchived, "");
		VarSoundSystemTrace = AddVariableInt("SoundSystemTrace", "debug_sound_system_trace", "Toggle whether sound system tracing is enabled", eCommandFlagsArchived, 0);
		VarSoundQueueFilter = AddVariableString("SoundQueueFilter", "debug_sound_queue_filter", "Only sounds containing this string will be queued with the sound system", eCommandFlagsArchived, "");
		VarSoundCache = AddVariableInt("SoundCache", "debug_sound_cache", "", eCommandFlagsNone, 4);
		VarScriptBreakpoint = AddVariableInt("ScriptBreakpoint", "debug_script_breakpoint", "Expression index to break on", eCommandFlagsNone, 0xFFFFFFFF);
		VarMouseSupport = AddVariableInt("MouseSupport", "debug_mouse_support", "", eCommandFlagsNone, 0);
		VarZBuffTest = AddVariableInt("ZBuffTest", "z_buff_test", "", eCommandFlagsNone, 1);
		VarAnimationPhoneboothTestDraw = AddVariableInt("AnimationPhoneboothTestDraw", "debug_animation_phonebooth_test_draw", "Renders assassination start & end position checks - red: initiator, green: victim", eCommandFlagsNone, 0);
		VarAnimationPhoneboothDrawTime = AddVariableFloat("AnimationPhoneboothDrawTime", "debug_animation_phonebooth_draw_time", "The duration of time which debug assassination rendering lasts for", eCommandFlagsNone, 1.0f);
		AddCommand("StartRandomTrace", "debug_start_random_trace", "Starts a random trace log", eCommandFlagsNone, CommandStartRandomTrace, { "filename" });
		AddCommand("StopRandomTrace", "debug_stop_random_trace", "Stops a random trace log", eCommandFlagsNone, CommandStopRandomTrace);
		AddCommand("TeleportToCamera", "debug_tpc", "Telports the player to the camera position", eCommandFlagsHostOnly, CommandTeleportToCamera);
		AddCommand("DebugTint", "debug_tint", "Change the shader debug_tint color", eCommandFlagsNone, CommandDebugTint);
		AddCommand("RasterizerSetZPlanes", "rasterizer_set_z_planes", "Change the near and far z plane values", eCommandFlagsNone, CommandRasterizerSetZPlanes);
		AddCommand("dialog", "dialog", "", eCommandFlagsNone, CommandDialogTest);
		AddCommand("CefOpenURL", "cef_open_url", "opens a url in the main frame", eCommandFlagsNone, CommandCefOpenURL);
		AddCommand("Crash", "crash", "Forces a game crash", eCommandFlagsNone, CommandCrash);
		AddCommand("Nuke", "nuke", "Exit back to the os (uncleanly)", eCommandFlagsNone, CommandNuke);
		AddCommand("LaunchClient", "launch_client", "", eCommandFlagsNone, CommandLaunchClient);
		AddCommand("Tilewindows", "tile_windows", "", eCommandFlagsNone, CommandTileWindows);
		AddCommand("ReflectionDebug", "reflection_debug", "", eCommandFlagsNone, CommandReflectionDebug);
		VarSmaaDebugMode = AddVariableInt("SmaaDebugMode", "smaa_debug_mode", "", eCommandFlagsNone, 0);
		VarSmaaDebugMode->ValueIntMin = 0;
		VarSmaaDebugMode->ValueIntMax = 2;
		AddCommand("RenderGeoHitTestEnabled", "render_geo_hit_test", "", eCommandFlagsNone, CommandRenderGeoHitTest);
		VarParticleFilter = AddVariableString("ParticleFilter", "particle_filter", "Filters particles to tag names containing the given string", eCommandFlagsNone, "");
		VarGeometrySamplerQuality = AddVariableInt("GeometrySamplerQuality", "geometry_sampler_quality", "Sets the geometry sampler quality (0 = disabled, 1 = normal, 2 = best)", eCommandFlagsArchived, 1);
		VarGeometrySamplerQuality->ValueIntMin = 0;
		VarGeometrySamplerQuality->ValueIntMax = 2;
		VarD3DResources = AddVariableInt("D3DResources", "d3d_resources", "Display D3D resource allocation counts", eCommandFlagsNone, 0);
		VarCrashReporting = AddVariableInt("CrashReporting", "crash_reporting", "Enables crash reporting", eCommandFlagsArchived, 1);
		VarAssertLevel = AddVariableInt("AssertLevel", "assert_level", "Change the assert level (0 = off, 1 = normal, 2 = high)", eCommandFlagsArchived, 1);
		AddCommand("DumpTags", "dump_tags", "Dumps a list of loaded tags", eCommandFlagsNone, CommandDumpTags);
		AddCommand("ShowCrte", "showcrte", "Forces a crte scene to display. Use tagname or hex index", eCommandFlagsNone, CommandGameShowCrte);
	}
}

/* ---------- private code */

bool CommandCrash(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x1097F460
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandCrash@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	std::stringstream ss;
	ss << "FORCE CRASH\n";
	ss << "You intentionally crashed the game!";
	returnInfo = ss.str();

	volatile int *a = nullptr;
	*a = 1;

	return true;
}

bool CommandNuke(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109807F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandNuke@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	std::stringstream ss;
	ss << "Console Requested application TerminateProcess";
	returnInfo = ss.str();

	TerminateProcess(GetCurrentProcess(), 0);

	return true;
}

bool CommandDumpTags(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x1097FBB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandDumpTags@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	char const *filename = "tag_dump.csv";
	_iobuf *fp;
	if (fopen_s(&fp, filename, "w"))
	{
		returnInfo = "failed to open file";
		return false;
	}
	for (__int32 i = 0; i < g_cache_file_tag_globals->loaded_instance_count; i++)
	{
		long index = g_cache_file_tag_globals->absolute_index_index_map[i];
		if (index == -1)
			continue;
		char const *tag_name = tag_get_name(index);
		char tag_group_name[5];
		tag_to_string(g_cache_file_tag_globals->instances[i]->group.tags[0], tag_group_name, 5);
		fprintf(fp, "0x%04x, %s.%s\n", index, tag_name, tag_group_name);
	}
	fclose(fp);
	returnInfo = std::string("Tags dumped to ") + filename;
	return true;
}

bool CommandDialogTest(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x1097FA00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandDialogTest@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	if (Arguments.size() < 1)
		return false;
	Web::Ui::ScreenLayer::SDialogShowParams params;
	params.templateName = Arguments[0];
	params.callback = [](std::string const &result) { Console::WriteLine("result: " + result); };
	if (Arguments.size() > 1)
		params.customBody = Arguments[1];
	if (Arguments.size() > 2)
		params.customTitle = Arguments[2];
	Web::Ui::ScreenLayer::ShowDialog(params);
	return true;
}

bool CommandDebugTint(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x1097F5F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandDebugTint@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	if (Arguments.size() != 4)
	{
		std::stringstream ss;
		ss << "4 arguments are required!" << std::endl;
		ss << "Usage: [red] [green] [blue] [alpha]";
		returnInfo = ss.str();
		return false;
	}
	Pointer(0xA3C761).WriteFast<float>(std::stof(Arguments[0]));
	Pointer(0xA3C768).WriteFast<float>(std::stof(Arguments[1]));
	Pointer(0xA3C76F).WriteFast<float>(std::stof(Arguments[2]));
	Pointer(0xA3C776).WriteFast<float>(std::stof(Arguments[3]));
	return true;
}

bool CommandRasterizerSetZPlanes(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10980970
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandRasterizerSetZPlanes@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	static float near_clip_plane = 0.0f;
	static float far_clip_plane = 0.0f;
	if (Arguments.size() == 0)
	{
		float near_plane = *(float *)0x191068C;
		float far_plane = *(float *)0x1910690;
		returnInfo = "Near: " + std::to_string(near_plane) + " Far: " + std::to_string(far_plane);
		return true;
	}
	if (Arguments.size() == 1 && Arguments[0] == "reset" && near_clip_plane != 0.0f && far_clip_plane != 0.0f)
	{
		Pointer(0x191068C).WriteFast<float>(near_clip_plane);
		Pointer(0x1910690).WriteFast<float>(far_clip_plane);
		returnInfo = "clip planes reset";
		return true;
	}
	if (Arguments.size() != 2)
	{
		std::stringstream ss;
		ss << "2 arguments are required!" << std::endl;
		ss << "Usage: [near] [far], rest";
		returnInfo = ss.str();
		return false;
	}
	if (near_clip_plane == 0.0f && far_clip_plane == 0.0f)
	{
		near_clip_plane = *(float *)0x191068C;
		far_clip_plane = *(float *)0x1910690;
	}
	Pointer(0x191068C).WriteFast<float>(std::stof(Arguments[0]));
	Pointer(0x1910690).WriteFast<float>(std::stof(Arguments[1]));
	returnInfo = "Planes Set";
	return true;
}

bool CommandTeleportToCamera(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10981480
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandTeleportToCamera@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	Modules::ModuleDebug::Instance().teleportToCamera = true;
	return true;
}

bool CommandReflectionDebug(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10981050
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandReflectionDebug@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	bool &g_reflection_debug = *(bool *)0x5115AFC;
	if (Arguments.size() < 1)
	{
		std::stringstream ss;
		ss << "Value required!" << std::endl;
		returnInfo = ss.str();
		return false;
	}
	__int32 const value = std::stoi(Arguments[0]);
	g_reflection_debug = value > 0;
	return true;
}

bool CommandStartRandomTrace(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10981370
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandStartRandomTrace@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	if (Arguments.size() < 1)
	{
		returnInfo = "Expected path to trace file";
		return false;
	}

	if (Patches::DeterminismDebug::StartRandomTrace(Arguments[0]))
	{
		returnInfo = "Random trace started.";
		return true;
	}
	else
	{
		returnInfo = "Failed to start random trace! Check the path exists and the file is not locked!";
		return false;
	}
}

bool CommandStopRandomTrace(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10981420
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandStopRandomTrace@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	if (Patches::DeterminismDebug::StopRandomTrace())
	{
		returnInfo = "Random trace stopped.";
	}

	return true;
}

bool CommandCefOpenURL(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x1097F2D0
{

	if (Arguments.size() < 1)
		return false;
	auto webRenderer = Web::Browser::WebRenderer::GetInstance();
	if (webRenderer)
	{
		webRenderer->OpenUrl(Arguments[0]);
		webRenderer->ShowRenderer(true, true);
		Web::Ui::ScreenLayer::CaptureInput(true, true);
	}
	return true;
}

bool CommandLaunchClient(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10980230
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandLaunchClient@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	char exePath[260];
	if (!GetModuleFileNameA(NULL, exePath, std::size(exePath)))
	{
		returnInfo = std::format("Failed get exe file path. Error: {}", GetLastError());
		return false;
	}
	bool hasConnect = false;
	for (const auto &arg : Arguments)
	{
		if ((hasConnect = arg.compare("-connect") == 0))
			break;
	}
	std::vector<std::string> args;
	if (!hasConnect)
	{
		args.push_back("-connect");
		args.push_back(std::format("localhost:{}", Utils::Singleton<Modules::ModuleServer>::Instance().VarServerPort->ValueInt));
	}
	std::copy(Arguments.begin(), Arguments.end(), std::back_inserter(args));
	std::string formattedArgs = Utils::FormatCommandLine(args);
	if ((int)ShellExecuteA(NULL, NULL, exePath, formattedArgs.c_str(), NULL, SW_SHOWNORMAL) <= 32)
	{
		returnInfo = std::format("Failed to create process. Error: {}", GetLastError());
		return false;
	}
	return true;
}

bool CommandTileWindows(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109814D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandTileWindows@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	__int32 posX = 0;
	__int32 posY = 0;
	__int32 rowHeight = 0;
	__int32 screenWidth = GetSystemMetrics(SM_CXSCREEN);
	__int32 screenHeight = GetSystemMetrics(SM_CYSCREEN);
	HWND windows[32];
	__int32 numWindows = 0;
	HWND hwnd = nullptr;
	while ((hwnd = FindWindowExA(nullptr, hwnd, nullptr, nullptr)) != nullptr)
	{
		char windowTitle[1024];
		GetWindowTextA(hwnd, windowTitle, std::size(windowTitle));
		if (strstr(windowTitle, "ElDewrito | Version"))
			windows[numWindows++] = hwnd;
	}
	for (__int32 i = 0; i < numWindows; i++)
	{
		HWND window = windows[i];
		ShowWindow(window, SW_RESTORE);
		RECT wr;
		GetWindowRect(window, &wr);
		__int32 width = wr.right - wr.left;
		__int32 height = wr.bottom - wr.top;
		if (posX + width > screenWidth)
		{
			posY += rowHeight;
			posX = 0;
			rowHeight = 0;
		}
		SetWindowPos(window, nullptr, posX, posY, 0, 0, SWP_NOSIZE);
		posX += width;
		if (height > rowHeight)
			rowHeight = height;
	}
	return true;
}

bool CommandRenderGeoHitTest(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10981240
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandRenderGeoHitTest@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	bool &globalVar = *(bool *)0x0471A33E;

	if (Arguments.size() > 0)
		globalVar = !std::stoi(Arguments[0]);

	returnInfo = std::to_string(!globalVar);

	return true;
}

bool CommandGameShowCrte(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x1097FE30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandGameShowCrte@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	if (Arguments.size() < 1)
		return false;
	short tag_index = (short)tag_find_by_name('crte', Arguments[0].c_str());
	static void (*const cortana_globals__play_effect)(__int32) = reinterpret_cast<void (*)(__int32)>(0xABECC0);
	if (tag_index == -1)
	{
		std::stringstream ss;
		ss << std::hex << Arguments[0];
		ss >> tag_index;
	}
	cortana_globals__play_effect(tag_index);
	return true;
}

bool CommandHideForgeObjects(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x10980000
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandHideForgeObjects@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	void (*const object_hide)(long, bool) = reinterpret_cast<void (*)(long, bool)>(0x96E230);
	if (!game_engine_is_sandbox())
	{
		returnInfo = "Only usable in Forge";
		return false;
	}
	Blam::Network::Session *session = Blam::Network::GetActiveSession();
	bool hidden = Modules::ModuleDebug::Instance().VarHideForgeObjects->ValueInt == 1;
	if (session && session->IsEstablished())
	{
		c_data_array<s_object_header> *object_headers = object_headers_get();
		for (c_data_iterator<s_object_header> it = object_headers->begin(); it != object_headers->end(); ++it)
		{
			unsigned long objectIndex = it.current_datum_index;
			long definition_index = it->data->definition_index;
			s_object_definition *object_definition = (s_object_definition *)tag_get('obje', definition_index);
			if (object_definition && object_definition->multiplayer_object.count > 0 && object_definition->multiplayer_object->flags.test((e_multiplayer_object_flags)0))
				object_hide(objectIndex, hidden);
		}
	}
	return true;
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template void Pointer::WriteFast<float>(float const) const;
