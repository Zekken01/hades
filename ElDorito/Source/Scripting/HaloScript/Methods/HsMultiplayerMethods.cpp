/* ---------- headers */

#include "hades/hades.h"

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
				_extern void _sub_106F6DD0(Scripting::HS::ScriptMethodMap &);
				void RegisterMethods(Scripting::HS::ScriptMethodMap &methods) // 0x106F6DD0
				{
					mangled_x86(MANGLED_TODO, "?RegisterMethods@Multiplayer@Methods@HS@Scripting@@YAXAAVScriptMethodMap@34@@Z");
					// Scripting::HS::ScriptMethodMap &methods;
					todo("implement");
					_sub_106F6DD0(methods);
				}
			}
		}
	}
}

/* ---------- private code */

_extern void _sub_106F8D50(short, long, bool);
void hs_hide_all_players_evaluate(short op, long thread_index, bool initial) // 0x106F8D50
{
	// `anonymous-namespace'::hs_hide_all_players_evaluate
	// static ...; // 0x106F8EC4
	// short op;
	// long thread_index;
	// bool initial;
	// void (*const object_hide)(long, bool);
	{
		// hs_value *args;
		{
			// bool hidden;
			// Blam::Network::Session *session;
			{
				// c_data_array<s_object_header> *object_headers;
				{
					// c_data_iterator<s_object_header> it;
					{
						// s_object_data *Bipd;
						// unsigned long objectIndex;
					}
				}
			}
		}
	}
	// function call : hs_value *(*const)(short, long, bool)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void (*const)(long, bool)
	// function call : void (*const)(long, hs_value)
	todo("implement");
	_sub_106F8D50(op, thread_index, initial);
}

_extern void _sub_106F87C0(short, long, bool);
void hs_hide_all_objects_evaluate(short op, long thread_index, bool initial) // 0x106F87C0
{
	// `anonymous-namespace'::hs_hide_all_objects_evaluate
	// static ...; // 0x106F8C14
// continueloop:
	// short op;
	// long thread_index;
	// bool initial;
	// void (*const object_hide)(long, bool);
	{
		// hs_value *args;
		{
			// bool hidden;
			// Blam::Network::Session *session;
			{
				// c_data_array<s_object_header> *object_headers;
				{
					// c_data_iterator<s_object_header> it;
					{
						// s_object_data *Weap;
						// s_object_data *Proj;
						// s_object_data *Eqip;
						// s_object_data *Scen;
						// s_object_data *Bloc;
						// unsigned long objectIndex;
						// char const *tagname;
						// s_forge_globals_definition *forge_globals;
						// s_object_data *Vehi;
						{
							// long definition_index;
							{
								// __int32 i;
								{
									// unsigned long sky_index;
								}
							}
							{
								// s_object_definition *object_definition;
							}
						}
					}
				}
			}
		}
	}
	// function call : hs_value *(*const)(short, long, bool)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : bool (*const)()
	// function call : void *(*const)(unsigned long, long)
	// function call : void (*const)(long, bool)
	// function call : void (*const)(long, hs_value)
	todo("implement");
	_sub_106F87C0(op, thread_index, initial);
}

_extern void _sub_106F7D00(short, long, bool);
void hs_delete_all_objects_evaluate(short op, long thread_index, bool initial) // 0x106F7D00
{
	// `anonymous-namespace'::hs_delete_all_objects_evaluate
	// static ...; // 0x106F84B8
// continueloop:
	// short op;
	// long thread_index;
	// bool initial;
	{
		// hs_value *args;
		{
			// bool delete_modifiers;
			// Blam::Network::Session *session;
			{
				// c_data_array<s_object_header> *object_headers;
				// c_candy_monitor_manager *candyMonitorManager;
				// bool &g_havok_garbage_collection_locked;
				{
					// c_data_iterator<s_object_header> it;
					{
						// s_object_data *Weap;
						// s_object_data *Proj;
						// s_object_data *Eqip;
						// s_object_data *Scen;
						// s_object_data *Ctrl;
						// s_object_data *Bloc;
						// s_object_data *Mach;
						// s_scenario *scenario;
						// unsigned long objectIndex;
						// char const *tagname;
						// s_forge_globals_definition *forge_globals;
						// s_object_data *Vehi;
						{
							// __int32 i;
						}
						{
						}
						{
						}
						{
						}
						{
						}
						{
							// long definition_index;
							// bool isModifier;
							{
								// __int32 i;
								{
									// unsigned long sky_index;
								}
							}
							{
								// s_object_definition *object_definition;
							}
						}
					}
				}
			}
		}
	}
	// function call : hs_value *(*const)(short, long, bool)
	// function call : bool (*const)()
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : bool (*const)()
	// function call : void *(*const)(unsigned long, long)
	// function call : void (*const)(long)
	// function call : void (*const)(long, hs_value)
	todo("implement");
	_sub_106F7D00(op, thread_index, initial);
}

_extern void _sub_106FA150(short, long, bool);
void hs_respawn_map_objects_evaluate(short op, long thread_index, bool initial) // 0x106FA150
{
	// `anonymous-namespace'::hs_respawn_map_objects_evaluate
	// static ...; // 0x106FA32C
	// short op;
	// long thread_index;
	// bool initial;
	{
		// hs_value *args;
		{
			// void (*const game_create_objects)(long);
			// void (*const c_map_variant__create_all_objects)(s_map_variant *);
			// bool &g_havok_garbage_collection_locked;
			// Blam::Network::Session *session;
			// void (*const object_placement_create_active_zone_set_objects)(long);
			{
				// c_candy_monitor_manager *candyMonitorManager;
				// s_map_variant *mapVariant;
				// c_data_array<s_object_header> *objects;
				{
					// c_data_iterator<s_object_header> it;
				}
			}
		}
	}
	// function call : hs_value *(*const)(short, long, bool)
	// function call : bool (*const)()
	// function call : void (*const)(long)
	// function call : void (*const)(long)
	// function call : void (*const)(long)
	// function call : s_map_variant *(*const)()
	// function call : void (*const)(s_map_variant *)
	// function call : void (*const)(long, hs_value)
	todo("implement");
	_sub_106FA150(op, thread_index, initial);
}

_extern void _sub_106F8F40(short, long, bool);
void hs_lobby_size_evaluate(short op, long thread_index, bool initial) // 0x106F8F40
{
	// `anonymous-namespace'::hs_lobby_size_evaluate
	// bool initial;
	{
		// hs_value *args;
		{
			// Blam::Network::Session *session;
		}
	}
	// function call : hs_value *(*const)(short, long, bool)
	// function call : void (*const)(long, hs_value)
	// function call : void (*const)(long, hs_value)
	todo("implement");
	_sub_106F8F40(op, thread_index, initial);
}

_extern void _sub_106F86D0(short, long, bool);
void hs_disable_prematch_camera_evaluate(short op, long thread_index, bool initial) // 0x106F86D0
{
	// `anonymous-namespace'::hs_disable_prematch_camera_evaluate
	// bool initial;
	{
		// hs_value *args;
		{
			// Blam::Network::Session *session;
			{
				// bool disabled;
			}
		}
	}
	// function call : hs_value *(*const)(short, long, bool)
	// function call : void (*const)(long, hs_value)
	todo("implement");
	_sub_106F86D0(op, thread_index, initial);
}

_extern void _sub_106F9940(short, long, bool);
void hs_mp_show_scoreboard_evaluate(short op, long thread_index, bool initial) // 0x106F9940
{
	// `anonymous-namespace'::hs_mp_show_scoreboard_evaluate
	// static ...; // 0x106F9B20
	// static ...; // 0x106F9B18
	// short op;
	// long thread_index;
	// bool initial;
	{
		// hs_value *args;
		{
			// Blam::Network::Session *session;
			{
				// bool animate;
				// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> jsonBuffer;
				// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> jsonWriter;
			}
		}
	}
	// function call : hs_value *(*const)(short, long, bool)
	// function call : void (*const)(long, hs_value)
	todo("implement");
	_sub_106F9940(op, thread_index, initial);
}

_extern void _sub_106F97B0(short, long, bool);
void hs_mp_hide_scoreboard_evaluate(short op, long thread_index, bool initial) // 0x106F97B0
{
	// `anonymous-namespace'::hs_mp_hide_scoreboard_evaluate
	// bool initial;
	{
		// hs_value *args;
		{
			// Blam::Network::Session *session;
		}
	}
	// function call : hs_value *(*const)(short, long, bool)
	// function call : void (*const)(long, hs_value)
	todo("implement");
	_sub_106F97B0(op, thread_index, initial);
}

_extern void _sub_106F9E40(short, long, bool);
void hs_mp_team_get_score_evaluate(short op, long thread_index, bool initial) // 0x106F9E40
{
	// `anonymous-namespace'::hs_mp_team_get_score_evaluate
	// bool initial;
	{
		// hs_value *args;
		{
			// Blam::Network::Session *session;
			{
				// c_game_statborg *scoreboard;
				// short mp_team;
				{
					// short team_score;
				}
			}
		}
	}
	// function call : hs_value *(*const)(short, long, bool)
	// function call : bool (*const)()
	// function call : c_game_statborg *(*const)()
	// function call : void (*const)(long, hs_value)
	// function call : void (*const)(long, hs_value)
	todo("implement");
	_sub_106F9E40(op, thread_index, initial);
}

_extern void _sub_106F9FD0(short, long, bool);
void hs_mp_team_set_score_evaluate(short op, long thread_index, bool initial) // 0x106F9FD0
{
	// `anonymous-namespace'::hs_mp_team_set_score_evaluate
	// bool initial;
	{
		// hs_value *args;
		{
			// Blam::Network::Session *session;
			{
				// float desired_score;
				// c_game_statborg *scoreboard;
				// short mp_team;
			}
		}
	}
	// function call : hs_value *(*const)(short, long, bool)
	// function call : bool (*const)()
	// function call : bool (*const)()
	// function call : c_game_statborg *(*const)()
	// function call : void (*const)(long, hs_value)
	todo("implement");
	_sub_106F9FD0(op, thread_index, initial);
}

_extern void _sub_106F9050(short, long, bool);
void hs_mp_end_round_evaluate(short op, long thread_index, bool initial) // 0x106F9050
{
	// `anonymous-namespace'::hs_mp_end_round_evaluate
	// bool initial;
	{
		// hs_value *args;
		{
			// Blam::Network::Session *session;
		}
	}
	// function call : hs_value *(*const)(short, long, bool)
	// function call : bool (*const)()
	// function call : bool (*const)()
	// function call : void (*const)(long, bool, long)
	// function call : void (*const)(long, hs_value)
	todo("implement");
	_sub_106F9050(op, thread_index, initial);
}

_extern void _sub_106F9660(short, long, bool);
void hs_mp_get_round_count_evaluate(short op, long thread_index, bool initial) // 0x106F9660
{
	// `anonymous-namespace'::hs_mp_get_round_count_evaluate
	// bool initial;
	{
		// hs_value *args;
		{
			// Blam::Network::Session *session;
			{
				// long rounds;
			}
		}
	}
	// function call : hs_value *(*const)(short, long, bool)
	// function call : long (*const)()
	// function call : bool (*const)()
	// function call : void (*const)(long, hs_value)
	// function call : void (*const)(long, hs_value)
	todo("implement");
	_sub_106F9660(op, thread_index, initial);
}

_extern void _sub_106F9170(short, long, bool);
void hs_mp_get_current_round_evaluate(short op, long thread_index, bool initial) // 0x106F9170
{
	// `anonymous-namespace'::hs_mp_get_current_round_evaluate
	// bool initial;
	{
		// hs_value *args;
		{
			// Blam::Network::Session *session;
		}
	}
	// function call : hs_value *(*const)(short, long, bool)
	// function call : bool (*const)()
	// function call : long (*const)()
	// function call : __int32 (*const)()
	// function call : void (*const)(long, hs_value)
	// function call : void (*const)(long, hs_value)
	todo("implement");
	_sub_106F9170(op, thread_index, initial);
}

_extern void _sub_106F9490(short, long, bool);
void hs_mp_get_remaining_match_time_evaluate(short op, long thread_index, bool initial) // 0x106F9490
{
	// `anonymous-namespace'::hs_mp_get_remaining_match_time_evaluate
	// bool initial;
	// long (*const game_engine_get_time_left_in_ticks)(bool);
	{
		// hs_value *args;
		{
			// Blam::Network::Session *session;
			{
				// float time_left;
			}
		}
	}
	// function call : hs_value *(*const)(short, long, bool)
	// function call : c_game_engine *(*const)()
	// function call : bool (*const)()
	// function call : long (*const)(bool)
	// function call : float (*const)(float)
	// function call : void (*const)(long, hs_value)
	// function call : void (*const)(long, hs_value)
	todo("implement");
	_sub_106F9490(op, thread_index, initial);
}

_extern void _sub_106F92D0(short, long, bool);
void hs_mp_get_match_time_elapsed_evaluate(short op, long thread_index, bool initial) // 0x106F92D0
{
	// `anonymous-namespace'::hs_mp_get_match_time_elapsed_evaluate
	// bool initial;
	// long (*const game_engine_get_time_left_in_ticks)(bool);
	{
		// hs_value *args;
		{
			// Blam::Network::Session *session;
			{
				// float time_elapsed;
			}
		}
	}
	// function call : hs_value *(*const)(short, long, bool)
	// function call : c_game_engine *(*const)()
	// function call : bool (*const)()
	// function call : long (*const)()
	// function call : float (*const)(float)
	// function call : void (*const)(long, hs_value)
	// function call : void (*const)(long, hs_value)
	todo("implement");
	_sub_106F92D0(op, thread_index, initial);
}

_extern void _sub_106F9BE0(short, long, bool);
void hs_mp_sync_global_evaluate(short op, long thread_index, bool initial) // 0x106F9BE0
{
	// `anonymous-namespace'::hs_mp_sync_global_evaluate
	// bool initial;
	// s_hs_syntax_node *node;
	// s_hs_thread *thread;
	{
		// short global_index;
	}
	// function call : s_hs_syntax_node *(*const)(long)
	// function call : s_hs_syntax_node *(*const)(long)
	// function call : s_hs_syntax_node *(*const)(long)
	// function call : bool (*const)()
	// function call : void (*const)(long, hs_value)
	todo("implement");
	_sub_106F9BE0(op, thread_index, initial);
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
