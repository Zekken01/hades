/* ---------- headers */

#include "hades/hades.h"
#include "SavedFilms/saved_film_manager.hpp"

#include "Blam/BlamNetwork.hpp"
#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/forge/forge_globals.hpp"
#include "Blam/game/engine/game_engine.hpp"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_engine_candy_monitor.hpp"
#include "Blam/game/game_statborg.hpp"
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
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/objects/object_definitions.hpp"
#include "Blam/objects/object_types.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/physics/havok_types.hpp"
#include "Blam/rasterizer/rasterizer_geometry.hpp"
#include "Blam/scenario/scenario.hpp"
#include "Blam/scenario/scenario_definitions.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Console/Console.hpp"
#include "Forge/Geoemetry.hpp"
#include "mods/map_variant_loader.hpp"
#include "Scripting/HaloScript/HsMethodMap.hpp"
#include "ThirdParty/rapidjson/allocators.h"
#include "ThirdParty/rapidjson/encodedstream.h"
#include "ThirdParty/rapidjson/encodings.h"
#include "ThirdParty/rapidjson/error/error.h"
#include "ThirdParty/rapidjson/internal/biginteger.h"
#include "ThirdParty/rapidjson/internal/diyfp.h"
#include "ThirdParty/rapidjson/internal/dtoa.h"
#include "ThirdParty/rapidjson/internal/ieee754.h"
#include "ThirdParty/rapidjson/internal/itoa.h"
#include "ThirdParty/rapidjson/internal/pow10.h"
#include "ThirdParty/rapidjson/internal/stack.h"
#include "ThirdParty/rapidjson/internal/strfunc.h"
#include "ThirdParty/rapidjson/internal/strtod.h"
#include "ThirdParty/rapidjson/memorystream.h"
#include "ThirdParty/rapidjson/reader.h"
#include "ThirdParty/rapidjson/stream.h"
#include "ThirdParty/rapidjson/stringbuffer.h"
#include "ThirdParty/rapidjson/writer.h"
#include "Web/Ui/Screen.hpp"

#include "Server/HsGlobalSync.hpp"  // hades: added for 0x106F9BE0
#include <format>  // hades: added for 0x106F9BE0

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <atomic>
#include <charconv>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <functional>
#include <initializer_list>
#include <iterator>
#include <limits>
#include <mutex>
#include <ratio>
#include <stdexcept>
#include <stop_token>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>

/* ---------- forward declarations */

struct c_candy_monitor_manager;
struct c_game_engine;
struct c_game_statborg;
struct hs_value;
struct s_forge_globals_definition;
struct s_hs_syntax_node;
struct s_hs_thread;
struct s_map_variant;
struct s_object_data;
struct s_object_definition;
struct s_object_header;
struct s_scenario;
namespace Blam
{
	namespace Network
	{
		struct Session;
	}
}
namespace Scripting
{
	namespace HS
	{
		class ScriptMethodMap;
	}
}

namespace Utils {}
using namespace ::Utils;
namespace Server {}
using namespace ::Server;
namespace Server
{
	namespace HsGlobalSync {}
	using namespace Server::HsGlobalSync;
}

namespace Forge {}
using namespace ::Forge;
namespace Scripting {}
using namespace ::Scripting;
namespace Scripting
{
	namespace HS {}
	using namespace Scripting::HS;
}

namespace base
{
	namespace internal {}
	using namespace base::internal;
}

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

/* ---------- prototypes */

namespace eldorado
{
	// Functions in eldorado.exe, named as in ManagedDonkey.
	static auto const hs_macro_function_evaluate = reinterpret_cast<hs_value *(*)(short, long, bool)>(0x5972F0);
	static auto const hs_return = reinterpret_cast<void (*)(long, hs_value)>(0x5974E0);
}

extern float (*const game_ticks_to_seconds)(float);  // hades: added for 0x106F92D0

extern s_map_variant *(*const game_engine_get_runtime_map_variant)();  // hades: added for 0x106FA150

extern s_object_data *(*const object_try_and_get_and_verify_type)(unsigned long, c_enum<e_object_type, long>);  // hades: added for 0x106F8D50

namespace Forge { namespace PrematchCamera { extern void SetForgePrematchCameraDisabled(bool disabled); } }  // hades: added for 0x106F86D0

namespace Scripting
{
	namespace HS
	{
		namespace Methods
		{
			namespace Multiplayer
			{
				extern void RegisterMethods(Scripting::HS::ScriptMethodMap &methods);
			}
		}
	}
}

void hs_hide_all_players_evaluate(short op, long thread_index, bool initial);
void hs_hide_all_objects_evaluate(short op, long thread_index, bool initial);
void hs_delete_all_objects_evaluate(short op, long thread_index, bool initial);
void hs_respawn_map_objects_evaluate(short op, long thread_index, bool initial);
void hs_lobby_size_evaluate(short op, long thread_index, bool initial);
void hs_disable_prematch_camera_evaluate(short op, long thread_index, bool initial);
void hs_mp_show_scoreboard_evaluate(short op, long thread_index, bool initial);
void hs_mp_hide_scoreboard_evaluate(short op, long thread_index, bool initial);
void hs_mp_team_get_score_evaluate(short op, long thread_index, bool initial);
void hs_mp_team_set_score_evaluate(short op, long thread_index, bool initial);
void hs_mp_end_round_evaluate(short op, long thread_index, bool initial);
void hs_mp_get_round_count_evaluate(short op, long thread_index, bool initial);
void hs_mp_get_current_round_evaluate(short op, long thread_index, bool initial);
void hs_mp_get_remaining_match_time_evaluate(short op, long thread_index, bool initial);
void hs_mp_get_match_time_elapsed_evaluate(short op, long thread_index, bool initial);
void hs_mp_sync_global_evaluate(short op, long thread_index, bool initial);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Scripting
{
	namespace HS
	{
		namespace Methods
		{
			namespace Multiplayer
			{
				void RegisterMethods(Scripting::HS::ScriptMethodMap &methods) // 0x106F6DD0
				{
					mangled_x86(MANGLED_KNOWN_GOOD, "?RegisterMethods@Multiplayer@Methods@HS@Scripting@@YAXAAVScriptMethodMap@34@@Z");

					methods.AddMethod("hide_all_players", "Hide all players currently in the game", NetworkSafe, hs_hide_all_players_evaluate, _hs_type_void, { { _hs_type_boolean, "visible", "True to hide, false to make visible" } });
					methods.AddMethod("hide_all_objects", "Hides all game objects leaving just the map itself and any built in objects", NetworkSafe, hs_hide_all_objects_evaluate, _hs_type_void, { { _hs_type_boolean, "visible", "True to hide, false to make visible" } });
					methods.AddMethod("delete_all_objects", "deletes all game objects leaving just the map itself and any built in objects", NetworkSafe, hs_delete_all_objects_evaluate, _hs_type_void, { { _hs_type_boolean, "delete_modifiers", "Whether to delete all forge modifier objects like the map modifier and lights" } });
					methods.AddMethod("respawn_map_objects", "respawns and cleans up all objects and garbage", NetworkSafe, hs_respawn_map_objects_evaluate, _hs_type_void, {});
					methods.AddMethod("lobby_size", "Gets the current size of the lobby", NetworkSafe, hs_lobby_size_evaluate, _hs_type_short, {});
					methods.AddMethod("disable_prematch_camera", "Disable the built in prematch camera in favor of using one with scripts", NetworkSafe, hs_disable_prematch_camera_evaluate, _hs_type_void, { { _hs_type_boolean, "disabled", "True will disable the built in prematch camera, false will reenable it" } });
					methods.AddMethod("mp_sync_global", "Registers a global variable to be synced with all clients and continue to be synced for the rest of the game session", HostOnly, hs_mp_sync_global_evaluate, _hs_type_void, { { _hs_type_string, "global", "The global variable name to be registered" } });
					methods.AddMethod("mp_show_scoreboard", "Shows the scoreboard", NetworkSafe, hs_mp_show_scoreboard_evaluate, _hs_type_void, { { _hs_type_boolean, "animate", "If set to true the scoreboard will animate where each player is delayed to create a rolling effect" } });
					methods.AddMethod("mp_hide_scoreboard", "Hides the scoreboard", NetworkSafe, hs_mp_hide_scoreboard_evaluate, _hs_type_void, {});
					methods.AddMethod("mp_team_get_score", "Gets the score for the desired mp_team", NetworkSafe, hs_mp_team_get_score_evaluate, _hs_type_short, { { _hs_type_mp_team, "team", "The team to get the score for" } });
					methods.AddMethod("mp_team_set_score", "Sets the score for the desired team", HostOnly, hs_mp_team_set_score_evaluate, _hs_type_void, { { _hs_type_mp_team, "team", "The team to set the score for" }, { _hs_type_real, "score", "The socore to set for the desired team" } });
					methods.AddMethod("mp_end_round", "Ends the current round", HostOnly, hs_mp_end_round_evaluate, _hs_type_void, {});
					methods.AddMethod("mp_get_round_count", "Gets the total number of rounds", NetworkSafe, hs_mp_get_round_count_evaluate, _hs_type_short, {});
					methods.AddMethod("mp_get_current_round", "Gets the current round number", NetworkSafe, hs_mp_get_current_round_evaluate, _hs_type_short, {});
					methods.AddMethod("mp_get_match_time_remaining", "Gets the remaining time for the match in seconds", NetworkSafe, hs_mp_get_remaining_match_time_evaluate, _hs_type_real, {});
					methods.AddMethod("mp_get_match_time_elapsed", "Gets the elapsed time for the match in seconds", NetworkSafe, hs_mp_get_match_time_elapsed_evaluate, _hs_type_real, {});
				}
			}
		}
	}
}

/* ---------- private code */

void hs_hide_all_players_evaluate(short op, long thread_index, bool initial) // 0x106F8D50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_hide_all_players_evaluate@@YAXFJ_N@Z");

	void (*const object_hide)(long, bool) = reinterpret_cast<void (*)(long, bool)>(0x96E230);
	hs_value *args = ((hs_value *(__cdecl *)(short, long, bool))0x5972F0)(op, thread_index, initial);
	if (args)
	{
		Blam::Network::Session *session = Blam::Network::GetActiveSession();
		bool hidden = args[0].bool_value;
		if (session && session->IsEstablished())
		{
			c_data_array<s_object_header> *object_headers = object_headers_get();
			for (c_data_iterator<s_object_header> it = object_headers->begin(); it != object_headers->end(); ++it)
			{
				unsigned long objectIndex = it.current_datum_index;
				s_object_data *Bipd = object_try_and_get_and_verify_type(objectIndex, 1);
				if (Bipd)
					object_hide(objectIndex, hidden);
			}
		}
		((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value{});
	}
}

void hs_hide_all_objects_evaluate(short op, long thread_index, bool initial) // 0x106F87C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_hide_all_objects_evaluate@@YAXFJ_N@Z");

	extern char const *tag_get_name(long);
	extern s_forge_globals_definition *forge_globals_get_definition();
	extern bool (*const game_engine_is_sandbox)();
	extern void *(*const tag_get)(unsigned long, long);
	void (*const object_hide)(long, bool) = reinterpret_cast<void (*)(long, bool)>(0x96E230);
	hs_value *args = ((hs_value *(__cdecl *)(short, long, bool))0x5972F0)(op, thread_index, initial);
	if (args)
	{
		Blam::Network::Session *session = Blam::Network::GetActiveSession();
		bool hidden = args[0].bool_value;
		if (session && session->IsEstablished())
		{
			c_data_array<s_object_header> *object_headers = object_headers_get();
			for (c_data_iterator<s_object_header> it = object_headers->begin(); it != object_headers->end(); ++it)
			{
				unsigned long objectIndex = it.current_datum_index;
				s_object_data *Scen = object_try_and_get_and_verify_type(objectIndex, 128);
				s_object_data *Bloc = object_try_and_get_and_verify_type(objectIndex, 2048);
				s_object_data *Weap = object_try_and_get_and_verify_type(objectIndex, 4);
				s_object_data *Vehi = object_try_and_get_and_verify_type(objectIndex, 2);
				s_object_data *Eqip = object_try_and_get_and_verify_type(objectIndex, 8);
				s_object_data *Proj = object_try_and_get_and_verify_type(objectIndex, 64);
				char const *tagname = tag_get_name(it->data->definition_index);
				s_forge_globals_definition *forge_globals = forge_globals_get_definition();
				if (forge_globals)
				{
					for (__int32 i = 0; i < forge_globals->skies.count; i++)
					{
						unsigned long sky_index = forge_globals->skies[i].object.index;
						if (it->data->definition_index == sky_index)
							goto continueloop;
					}
					long definition_index = it->data->definition_index;
					if (definition_index == forge_globals->map_modifier_object.index)
						continue;
					if (definition_index == forge_globals->fx_light.index)
						continue;
					if (definition_index == forge_globals->fx_object.index)
						continue;
					if (!game_engine_is_sandbox())
					{
						s_object_definition *object_definition = (s_object_definition *)tag_get('obje', definition_index);
						if (object_definition && object_definition->multiplayer_object.count > 0 && object_definition->multiplayer_object->flags.test(_multiplayer_object_only_render_in_editor_bit))
							continue;
					}
				}
				if (Scen || Bloc || (Weap && Weap->parent_object_index == -1) || Vehi || Eqip || Proj)
					object_hide(objectIndex, hidden);
			continueloop:;
			}
		}
		((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value{});
	}
}

void hs_delete_all_objects_evaluate(short op, long thread_index, bool initial) // 0x106F7D00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_delete_all_objects_evaluate@@YAXFJ_N@Z");

	extern char const *tag_get_name(long);
	extern s_forge_globals_definition *forge_globals_get_definition();
	extern s_scenario *global_scenario_get();
	extern bool (*const game_engine_is_sandbox)();
	extern void *(*const tag_get)(unsigned long, long);
	hs_value *args = ((hs_value *(__cdecl *)(short, long, bool))0x5972F0)(op, thread_index, initial);
	if (args)
	{
		bool delete_modifiers = args[0].bool_value;
		Blam::Network::Session *session = Blam::Network::GetActiveSession();
		if (session && session->IsEstablished() && ((bool (*)())0x5319C0)())
		{
			bool &g_havok_garbage_collection_locked = *(bool *)0x18A23C3;
			g_havok_garbage_collection_locked = true;
			c_candy_monitor_manager *candyMonitorManager = get_candy_monitor_manager();
			candyMonitorManager->reset();
			c_data_array<s_object_header> *object_headers = object_headers_get();
			for (c_data_iterator<s_object_header> it = object_headers->begin(); it != object_headers->end(); ++it)
			{
				unsigned long objectIndex = it.current_datum_index;
				s_object_data *Scen = object_try_and_get_and_verify_type(objectIndex, 128);
				s_object_data *Bloc = object_try_and_get_and_verify_type(objectIndex, 2048);
				s_object_data *Weap = object_try_and_get_and_verify_type(objectIndex, 4);
				s_object_data *Vehi = object_try_and_get_and_verify_type(objectIndex, 2);
				s_object_data *Eqip = object_try_and_get_and_verify_type(objectIndex, 8);
				s_object_data *Proj = object_try_and_get_and_verify_type(objectIndex, 64);
				s_object_data *Mach = object_try_and_get_and_verify_type(objectIndex, 256);
				s_object_data *Ctrl = object_try_and_get_and_verify_type(objectIndex, 512);
				char const *tagname = tag_get_name(it->data->definition_index);
				s_forge_globals_definition *forge_globals = forge_globals_get_definition();
				s_scenario *scenario = global_scenario_get();
				if (scenario)
				{
					if (Scen)
					{
						for (__int32 i = 0; i < scenario->skies.count; i++)
						{
							if (Scen->definition_index == scenario->skies[i].sky_object.index)
								goto continueloop;
						}
						for (__int32 i = 0; i < scenario->scenery.count; i++)
						{
							if (Scen->object_identifier.unique_id == scenario->scenery[i].object_id.unique_id)
								goto continueloop;
						}
					}
					if (Mach)
					{
						for (__int32 i = 0; i < scenario->machines.count; i++)
						{
							if (Mach->object_identifier.unique_id == scenario->machines[i].object_id.unique_id)
								goto continueloop;
						}
					}
					if (Bloc)
					{
						for (__int32 i = 0; i < scenario->crates.count; i++)
						{
							if (Bloc->object_identifier.unique_id == scenario->crates[i].object_id.unique_id)
								goto continueloop;
						}
					}
					if (Ctrl)
					{
						for (__int32 i = 0; i < scenario->controls.count; i++)
						{
							if (Ctrl->object_identifier.unique_id == scenario->controls[i].object_id.unique_id)
								goto continueloop;
						}
					}
				}
				if (forge_globals)
				{
					for (__int32 i = 0; i < forge_globals->skies.count; i++)
					{
						unsigned long sky_index = forge_globals->skies[i].object.index;
						if (it->data->definition_index == sky_index)
							goto continueloop;
					}
					long definition_index = it->data->definition_index;
					bool isModifier = false;
					if (definition_index == forge_globals->map_modifier_object.index)
					{
						isModifier = true;
						if (!delete_modifiers)
							continue;
					}
					if (definition_index == forge_globals->fx_light.index)
					{
						isModifier = true;
						if (!delete_modifiers)
							continue;
					}
					if (definition_index == forge_globals->fx_object.index)
					{
						isModifier = true;
						if (!delete_modifiers)
							continue;
					}
					if (definition_index == forge_globals->podium_placement_object.index)
						continue;
					if (!game_engine_is_sandbox() && !isModifier)
					{
						s_object_definition *object_definition = (s_object_definition *)tag_get('obje', definition_index);
						if (object_definition && object_definition->multiplayer_object.count > 0 && object_definition->multiplayer_object->flags.test(_multiplayer_object_only_render_in_editor_bit))
							continue;
					}
				}
				if (Scen || Bloc || (Weap && Weap->parent_object_index == -1) || Vehi || Eqip || Proj || Mach || Ctrl)
					((void (*)(long))0xB2CD10)(objectIndex);
			continueloop:;
			}
			g_havok_garbage_collection_locked = false;
		}
		((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value{});
	}
}

void hs_respawn_map_objects_evaluate(short op, long thread_index, bool initial) // 0x106FA150
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_respawn_map_objects_evaluate@@YAXFJ_N@Z");

	hs_value *args = ((hs_value *(__cdecl *)(short, long, bool))0x5972F0)(op, thread_index, initial);
	if (args)
	{
		void (*const game_create_objects)(long) = reinterpret_cast<void (*)(long)>(0x530B30);
		void (*const object_placement_create_active_zone_set_objects)(long) = reinterpret_cast<void (*)(long)>(0xB591C0);
		void (__thiscall *const c_map_variant__create_all_objects)(s_map_variant *) = reinterpret_cast<void (__thiscall *)(s_map_variant *)>(0x585EE0);
		bool &g_havok_garbage_collection_locked = *(bool *)0x18A23C3;
		Blam::Network::Session *session = Blam::Network::GetActiveSession();
		if (session && session->IsEstablished() && ((bool(__cdecl *)())0x5319C0)())
		{
			g_havok_garbage_collection_locked = true;
			c_data_array<s_object_header> *objects = object_headers_get();
			for (c_data_iterator<s_object_header> it = objects->begin(); it != objects->end(); ++it)
			{
				if (it->data->map_variant_index == -1 && it->data->scenario_datum_index == -1)
					((void(__cdecl *)(long))0xB2CF40)(it.current_datum_index);
			}
			c_candy_monitor_manager *candyMonitorManager = get_candy_monitor_manager();
			candyMonitorManager->reset();
			game_create_objects(1);
			object_placement_create_active_zone_set_objects(0);
			s_map_variant *mapVariant = game_engine_get_runtime_map_variant();
			c_map_variant__create_all_objects(mapVariant);
			g_havok_garbage_collection_locked = false;
		}
		((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value{});
	}
}

void hs_lobby_size_evaluate(short op, long thread_index, bool initial) // 0x106F8F40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_lobby_size_evaluate@@YAXFJ_N@Z");

	hs_value *args = eldorado::hs_macro_function_evaluate(op, thread_index, initial);
	if (args)
	{
		Blam::Network::Session *session = Blam::Network::GetActiveSession();
		if (SavedFilms::film_is_playing())
		{
			// A film's players are the game's; its session holds only the viewer.
			short player_count = 0;
			for (long i = 0; i < 16; i++)
			{
				if (players_get()->try_and_get_absolute(i))
					player_count++;
			}
			eldorado::hs_return(thread_index, hs_value::from_short(player_count));
		}
		else if (session && session->IsEstablished())
		{
			eldorado::hs_return(thread_index, hs_value::from_short(session->MembershipInfo.PlayerCount));
		}
		else
		{
			eldorado::hs_return(thread_index, hs_value{});
		}
	}
}

void hs_disable_prematch_camera_evaluate(short op, long thread_index, bool initial) // 0x106F86D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_disable_prematch_camera_evaluate@@YAXFJ_N@Z");

	hs_value *args = ((hs_value *(__cdecl *)(short, long, bool))0x5972F0)(op, thread_index, initial);
	if (args)
	{
		Blam::Network::Session *session = Blam::Network::GetActiveSession();
		if (session && session->IsEstablished())
		{
			bool disabled = args[0].bool_value;
			Forge::PrematchCamera::SetForgePrematchCameraDisabled(disabled);
		}

		((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value{});
	}
}

void hs_mp_show_scoreboard_evaluate(short op, long thread_index, bool initial) // 0x106F9940
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_mp_show_scoreboard_evaluate@@YAXFJ_N@Z");

	hs_value *args = ((hs_value *(__cdecl *)(short, long, bool))0x5972F0)(op, thread_index, initial);
	if (args)
	{
		Blam::Network::Session *session = Blam::Network::GetActiveSession();
		if (session && session->IsEstablished())
		{
			bool animate = args[0].bool_value;
			rapidjson::StringBuffer jsonBuffer;
			rapidjson::Writer<rapidjson::StringBuffer> jsonWriter(jsonBuffer);
			jsonWriter.StartObject();
			jsonWriter.Key("animate");
			jsonWriter.Bool(animate);
			jsonWriter.EndObject();
			Web::Ui::ScreenLayer::NotifyScreen(Web::Ui::ScreenLayer::Scoreboard, "script-show-scoreboard", jsonBuffer.GetString());
		}
		((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value{});
	}
}

void hs_mp_hide_scoreboard_evaluate(short op, long thread_index, bool initial) // 0x106F97B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_mp_hide_scoreboard_evaluate@@YAXFJ_N@Z");

	hs_value *args = ((hs_value *(__cdecl *)(short, long, bool))0x5972F0)(op, thread_index, initial);
	if (args)
	{
		Blam::Network::Session *session = Blam::Network::GetActiveSession();
		if (session && session->IsEstablished())
			Web::Ui::ScreenLayer::NotifyScreen(Web::Ui::ScreenLayer::Scoreboard, "scoreboard_hide", "{}");
		((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value{});
	}
}

void hs_mp_team_get_score_evaluate(short op, long thread_index, bool initial) // 0x106F9E40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_mp_team_get_score_evaluate@@YAXFJ_N@Z");

	hs_value *args = ((hs_value *(__cdecl *)(short, long, bool))0x5972F0)(op, thread_index, initial);
	if (args)
	{
		Blam::Network::Session *session = Blam::Network::GetActiveSession();
		if (session && session->IsEstablished() && ((bool(__cdecl *)())0x5565E0)())
		{
			short mp_team = args[0].short_value;
			c_game_statborg *scoreboard = ((c_game_statborg *(__cdecl *)())0x550B80)();
			if (scoreboard)
			{
				short team_score = scoreboard->teams[mp_team].score;
				((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value::from_short(team_score));
				return;
			}
		}
		((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value::from_short(-1));
	}
}

void hs_mp_team_set_score_evaluate(short op, long thread_index, bool initial) // 0x106F9FD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_mp_team_set_score_evaluate@@YAXFJ_N@Z");

	hs_value *args = ((hs_value *(__cdecl *)(short, long, bool))0x5972F0)(op, thread_index, initial);
	if (args)
	{
		Blam::Network::Session *session = Blam::Network::GetActiveSession();
		if (session && session->IsEstablished() && ((bool(__cdecl *)())0x5319C0)() && ((bool(__cdecl *)())0x5565E0)())
		{
			short mp_team = args[0].short_value;
			float desired_score = args[1].real_value;
			c_game_statborg *scoreboard = ((c_game_statborg *(__cdecl *)())0x550B80)();
			if (scoreboard)
				scoreboard->teams[mp_team].score = desired_score;
		}
		((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value{});
	}
}

void hs_mp_end_round_evaluate(short op, long thread_index, bool initial) // 0x106F9050
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_mp_end_round_evaluate@@YAXFJ_N@Z");

	hs_value *args = ((hs_value *(__cdecl *)(short, long, bool))0x5972F0)(op, thread_index, initial);
	if (args)
	{
		Blam::Network::Session *session = Blam::Network::GetActiveSession();
		if (session && session->IsEstablished() && ((bool(__cdecl *)())0x5319C0)() && ((bool(__cdecl *)())0x550F90)())
		{
			((void(__cdecl *)(long, bool, long))0x54E390)(-1, false, 0x16);
		}

		((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value{});
	}
}

void hs_mp_get_round_count_evaluate(short op, long thread_index, bool initial) // 0x106F9660
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_mp_get_round_count_evaluate@@YAXFJ_N@Z");

	hs_value *args = ((hs_value *(__cdecl *)(short, long, bool))0x5972F0)(op, thread_index, initial);
	if (args)
	{
		Blam::Network::Session *session = Blam::Network::GetActiveSession();
		if (session && session->IsEstablished())
		{
			long rounds = ((long(__cdecl *)())0x5504C0)();
			if (((bool(__cdecl *)())0x550F90)() && rounds > 1)
			{
				((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value::from_short(rounds));
				return;
			}
		}
		((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value::from_short(1));
	}
}

void hs_mp_get_current_round_evaluate(short op, long thread_index, bool initial) // 0x106F9170
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_mp_get_current_round_evaluate@@YAXFJ_N@Z");

	hs_value *args = ((hs_value *(__cdecl *)(short, long, bool))0x5972F0)(op, thread_index, initial);
	if (args)
	{
		Blam::Network::Session *session = Blam::Network::GetActiveSession();
		if (session && session->IsEstablished() && ((bool(__cdecl *)())0x550F90)() && ((long(__cdecl *)())0x5504C0)() > 1)
		{
			((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value::from_short(((long(__cdecl *)())0x550AD0)() + 1));
			return;
		}
		((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value::from_short(1));
	}
}

void hs_mp_get_remaining_match_time_evaluate(short op, long thread_index, bool initial) // 0x106F9490
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_mp_get_remaining_match_time_evaluate@@YAXFJ_N@Z");

	long (*const game_engine_get_time_left_in_ticks)(bool) = reinterpret_cast<long (*)(bool)>(0x550D70);
	hs_value *args = ((hs_value *(__cdecl *)(short, long, bool))0x5972F0)(op, thread_index, initial);
	if (args)
	{
		Blam::Network::Session *session = Blam::Network::GetActiveSession();
		if (session && session->IsEstablished() && ((c_game_engine *(__cdecl *)())0x5CE150)() && ((bool(__cdecl *)())0x5314B0)())
		{
			float time_left = game_ticks_to_seconds((float)game_engine_get_time_left_in_ticks(true));
			((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value::from_real(time_left));
			return;
		}
		((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value::from_real(-1.0f));
	}
}

void hs_mp_get_match_time_elapsed_evaluate(short op, long thread_index, bool initial) // 0x106F92D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_mp_get_match_time_elapsed_evaluate@@YAXFJ_N@Z");

	long (*const game_engine_get_time_left_in_ticks)(bool) = reinterpret_cast<long (*)(bool)>(0x550D70);
	hs_value *args = ((hs_value *(__cdecl *)(short, long, bool))0x5972F0)(op, thread_index, initial);
	if (args)
	{
		Blam::Network::Session *session = Blam::Network::GetActiveSession();
		if (session && session->IsEstablished() && ((c_game_engine *(__cdecl *)())0x5CE150)() && ((bool(__cdecl *)())0x5314B0)())
		{
			float time_elapsed = game_ticks_to_seconds((float)((long(__cdecl *)())0x5523D0)());
			((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value::from_real(time_elapsed));
			return;
		}
		((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value::from_real(-1.0f));
	}
}

void hs_mp_sync_global_evaluate(short op, long thread_index, bool initial) // 0x106F9BE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_mp_sync_global_evaluate@@YAXFJ_N@Z");

	s_hs_thread *thread = tls_getd().hs_thread_deterministic_data->try_and_get(thread_index);
	s_hs_syntax_node *node = ((s_hs_syntax_node *(*)(long))0x598A10)(*(long *)&thread->stack[thread->stack_offset]);
	node = ((s_hs_syntax_node *(*)(long))0x598A10)(*(long *)node->data);
	node = ((s_hs_syntax_node *(*)(long))0x598A10)(node->next_expression_index);
	if (((unsigned short)node->flags & 4) == 0)
		return;
	if (((bool (*)())0x5319C0)())
	{
		short global_index = *(short *)node->data;
		Server::HsGlobalSync::RegisterGlobal(global_index);
		Console::WriteLine(std::format("registered global \"{}\" for synchronization", hs_global_get_name(global_index)));
	}
	((void (*)(long, hs_value))0x5974E0)(thread_index, hs_value{});
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_flags<enum e_multiplayer_object_flags,unsigned short>::test(e_multiplayer_object_flags) const;
template bool c_tag_block<s_multiplayer_object_definition>::try_get_element(__int32, s_multiplayer_object_definition **) const;
template bool c_tag_block<s_scenario_control>::try_get_element(__int32, s_scenario_control **) const;
template bool c_tag_block<s_scenario_crate>::try_get_element(__int32, s_scenario_crate **) const;
template bool c_tag_block<s_scenario_machine>::try_get_element(__int32, s_scenario_machine **) const;
template bool c_tag_block<s_scenario_scenery>::try_get_element(__int32, s_scenario_scenery **) const;
template c_flags<enum e_hs_syntax_node_flags,unsigned short>::operator unsigned short() const;
template s_hs_thread * c_data_array<s_hs_thread>::try_and_get(unsigned long);
template s_multiplayer_object_definition * c_tag_block<s_multiplayer_object_definition>::get_element(__int32) const;
template s_multiplayer_object_definition * c_tag_block<s_multiplayer_object_definition>::operator->();
template s_scenario_control & c_tag_block<s_scenario_control>::operator[](__int32);
template s_scenario_control * c_tag_block<s_scenario_control>::get_element(__int32) const;
template s_scenario_crate & c_tag_block<s_scenario_crate>::operator[](__int32);
template s_scenario_crate * c_tag_block<s_scenario_crate>::get_element(__int32) const;
template s_scenario_machine & c_tag_block<s_scenario_machine>::operator[](__int32);
template s_scenario_machine * c_tag_block<s_scenario_machine>::get_element(__int32) const;
template s_scenario_scenery & c_tag_block<s_scenario_scenery>::operator[](__int32);
template s_scenario_scenery * c_tag_block<s_scenario_scenery>::get_element(__int32) const;
