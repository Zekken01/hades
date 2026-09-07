/* ---------- headers */

#include "hades/hades.h"

#include "Blam/BlamInput.hpp"
#include "Blam/BlamNetwork.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/cseries/static_string.inl"
#include "Blam/game/engine/game_engine_events.hpp"
#include "Blam/game/engine/game_engine_infection.hpp"
#include "Blam/game/engine/game_engine_juggernaut.hpp"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_engine_candy_monitor.hpp"
#include "Blam/game/game_results.hpp"
#include "Blam/game/game_statborg.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/input/input.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/bitstream.hpp"
#include "Blam/memory/data_array.inl"
#include "Blam/memory/static_array.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/networking/session/network_session.hpp"
#include "Blam/networking/session/network_session_membership.hpp"
#include "Blam/networking/session/network_session_parameters_base.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "mods/FileSystem/ModPackageFileSystemView.hpp"
#include "mods/mod_definitions.hpp"
#include "mods/mod_identifier.hpp"
#include "mods/mod_package_manager.hpp"
#include "mods/new/IModManager.hpp"
#include "Patches/Events.hpp"
#include "Patches/Network.hpp"
#include "Pointer.hpp"
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
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"
#include "Web/Ui/Screen.hpp"
#include "Web/Ui/ScreenLayer.hpp"
#include "Web/Ui/WebMods.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <atomic>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <functional>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <memory>
#include <mutex>
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

/* ---------- forward declarations */

struct c_game_statborg;
struct s_game_engine_event_data;
struct s_game_results_player_statistics;
struct s_globals;
struct s_multiplayer_event_response_definition;
struct s_player_datum;
namespace Blam
{
	namespace Input
	{
		struct ActionState;
	}
}
namespace
{
	struct s_session_player;
	struct s_session_update;
	struct s_scores_update;
	struct s_scoreboard_update;
}

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;
namespace Player {}
using namespace ::Player;
namespace Player
{
	namespace PlayerPodium {}
	using namespace Player::PlayerPodium;
	namespace Emblems {}
	using namespace Player::Emblems;
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
		namespace WebScoreboard {}
		using namespace Web::Ui::WebScoreboard;
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
	namespace Events {}
	using namespace Patches::Events;
}

namespace Blam
{
	namespace Input {}
	using namespace Blam::Input;
	namespace Network {}
	using namespace Blam::Network;
}

namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Cache {}
	using namespace Blam::Cache;
}

/* ---------- constants */

namespace
{
	enum e_game_scoreboard_state
	{
		_game_scoreboard_state_none = 0,
		_game_scoreboard_state_in_round,
		_game_scoreboard_state_in_round_waiting_for_intro_ui,
		_game_scoreboard_state_in_round_intro_ui_shown,
		_game_scoreboard_state_in_round_alive,
		_game_scoreboard_state_in_round_dead,
		_game_scoreboard_state_in_round_about_to_respawn,
		_game_scoreboard_state_round_over,
		_game_scoreboard_state_preparing_for_new_round,
		_game_scoreboard_state_game_over,
		_game_scoreboard_state_game_returning_to_lobby,
	};
}
/* ---------- definitions */

namespace
{
	struct s_session_player
	{
		bool is_host; // 0x0
		unsigned char __pad0[3]; // 0x1
		long session_player_index; // 0x4
		long team_index; // 0x8
		unsigned long color; // 0xC
		unsigned long long uid; // 0x10
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > player_name; // 0x18
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > service_tag; // 0x34
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > emblem; // 0x50
		s_session_player(s_session_player &); /* compiler_generated() */
		s_session_player(s_session_player const &); /* compiler_generated() */
		s_session_player(); /* compiler_generated() */
		~s_session_player(); /* compiler_generated() */
		s_session_player &operator=(s_session_player &); /* compiler_generated() */
		s_session_player &operator=(s_session_player const &); /* compiler_generated() */
		unsigned char __pad1[4]; // 0x6C
	};
	static_assert(sizeof(s_session_player) == 112, "Invalid s_session_player size");

	struct s_session_update
	{
		bool valid; // 0x0
		bool has_teams; // 0x1
		bool is_host; // 0x2
		unsigned char __pad0[1]; // 0x3
		short game_engine_type; // 0x4
		short game_lobby_type; // 0x6
		short number_of_rounds; // 0x8
		short current_round; // 0xA
		long game_mode; // 0xC
		unsigned long long game_id; // 0x10
		s_static_array<s_session_player,16> players; // 0x18
		long player_count; // 0x718
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > players_info; // 0x71C
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > players_ping_info; // 0x738
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > map_variant_name; // 0x754
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > game_variant_name; // 0x770
		long sessionMaxPlayers; // 0x78C
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > mod_name; // 0x790
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > mod_author; // 0x7AC
		std::basic_string<char,std::char_traits<char>,std::allocator<char> > mod_version; // 0x7C8
		s_session_update(s_session_update &); /* compiler_generated() */
		s_session_update(s_session_update const &); /* compiler_generated() */
		s_session_update(); /* compiler_generated() */
		~s_session_update(); /* compiler_generated() */
		s_session_update &operator=(s_session_update &); /* compiler_generated() */
		s_session_update &operator=(s_session_update const &); /* compiler_generated() */
		unsigned char __pad1[4]; // 0x7E4
	};
	static_assert(sizeof(s_session_update) == 2024, "Invalid s_session_update size");

}
typedef unsigned long argb_color;

namespace
{
	#pragma pack(push, 4)
	struct s_scores_update
	{
		bool valid; // 0x0
		bool game_finished; // 0x1
		bool game_tied; // 0x2
		bool round_over; // 0x3
		short game_engine_type; // 0x4
		short game_lobby_type; // 0x6
		s_static_array<long,16> player_place; // 0x8
		s_static_array<c_game_statborg::s_player_row,16> player_scores; // 0x48
		s_static_array<s_game_results_player_statistics,16> player_stats; // 0x388
		unsigned long valid_player_mask; // 0x4708
		s_static_array<c_game_statborg::s_team_row,8> team_scores; // 0x470C
		s_static_array<long,8> team_place; // 0x47DC
		unsigned long valid_team_mask; // 0x47FC
		unsigned long dead_player_mask; // 0x4800
		unsigned long objective_player_mask; // 0x4804
		unsigned long alpha_player_mask; // 0x4808
	};
	#pragma pack(pop)
	static_assert(sizeof(s_scores_update) == 18444, "Invalid s_scores_update size");
}
typedef unsigned long rgb_color;
namespace Patches
{
	namespace Events
	{
		typedef std::function<void __cdecl(unsigned long,s_game_engine_event_data const *,s_multiplayer_event_response_definition const *)> EventCallback;
	}
}

namespace Patches
{
	namespace Network
	{
		typedef std::function<void __cdecl(enum Blam::Network::LifeCycleState)> LifeCycleStateChangedCallback;
	}
}

namespace
{
	struct s_scoreboard_update
	{
		s_session_update session_update; // 0x0
		s_scores_update scores_update; // 0x7E8
		s_scoreboard_update(s_scoreboard_update &); /* compiler_generated() */
		s_scoreboard_update(s_scoreboard_update const &); /* compiler_generated() */
		s_scoreboard_update(); /* compiler_generated() */
		~s_scoreboard_update(); /* compiler_generated() */
		s_scoreboard_update &operator=(s_scoreboard_update &); /* compiler_generated() */
		s_scoreboard_update &operator=(s_scoreboard_update const &); /* compiler_generated() */
		unsigned char __pad0[4]; // 0x4FF4
	};
	static_assert(sizeof(s_scoreboard_update) == 20472, "Invalid s_scoreboard_update size");
}
struct s_globals
{
	bool shown; // 0x0
	bool locked; // 0x1
	bool was_tapped_last_tick; // 0x2
	long last_tapped_game_time; // 0x4
	long update_timer; // 0x8
	long post_game_timer; // 0xC
	long last_membership_update_number; // 0x10
	bool requires_session_update; // 0x14
	e_game_scoreboard_state scoreboard_state; // 0x18
	bool postgame; // 0x1C
	bool pregame; // 0x1D
	bool returningToLobby; // 0x1E
	bool acceptsInput; // 0x1F
	bool spawning_soon; // 0x20
	long post_game_time; // 0x24
	bool sent_final_update; // 0x28
	s_globals(); /* compiler_generated() */
};
// static_assert(sizeof(s_globals) == 44, "Invalid s_globals size");
// Withheld: the type inventory does not describe this type, so its
// padding could not be reconstructed.

/* ---------- prototypes */

namespace Web
{
	namespace Ui
	{
		namespace WebScoreboard
		{
			extern void OnGameInputUpdated();
			extern void OnLifeCycleStateChanged(Blam::Network::LifeCycleState newState);
			extern void OnEvent(unsigned long player, s_game_engine_event_data const *event, s_multiplayer_event_response_definition const *definition);
			extern void Init();
			extern void Show(bool locked, bool pregame, bool animate);
			extern void Hide();
			extern void Tick();
			extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > getScoreboard();
		}
	}
}

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Web
{
	namespace Ui
	{
		namespace WebScoreboard
		{
			_extern void _sub_10CB0C10();
			void OnGameInputUpdated() // 0x10CB0C10
			{
				mangled_x86(MANGLED_TODO, "?OnGameInputUpdated@WebScoreboard@Ui@Web@@YAXXZ");
				// procedure flags: nofpo
				// Blam::Input::ActionState *uiSelect;
				{
					// float movementAmount;
					// float *values;
					{
						// __int32 i;
					}
				}
				todo("implement");
				_sub_10CB0C10();
			}

			_extern void _sub_10CB10C0(Blam::Network::LifeCycleState);
			void OnLifeCycleStateChanged(Blam::Network::LifeCycleState newState) // 0x10CB10C0
			{
				mangled_x86(MANGLED_TODO, "?OnLifeCycleStateChanged@WebScoreboard@Ui@Web@@YAXW4LifeCycleState@Network@Blam@@@Z");
				// Blam::Network::LifeCycleState newState;
				todo("implement");
				_sub_10CB10C0(newState);
			}

			_extern void _sub_10CB0990(unsigned long, s_game_engine_event_data const *, s_multiplayer_event_response_definition const *);
			void OnEvent(unsigned long player, s_game_engine_event_data const *event, s_multiplayer_event_response_definition const *definition) // 0x10CB0990
			{
				mangled_x86(MANGLED_TODO, "?OnEvent@WebScoreboard@Ui@Web@@YAXKPBUs_game_engine_event_data@@PBUs_multiplayer_event_response_definition@@@Z");
				// s_multiplayer_event_response_definition const *definition;
				{
					// s_player_datum *player;
					{
						// unsigned long firstTimeSpawning;
						// long secondsUntilSpawn;
					}
				}
				// function call : long (*const)()
				// function call : unsigned long (*const)(long)
				todo("implement");
				_sub_10CB0990(player, event, definition);
			}

			_extern void _sub_10CB08F0();
			void Init() // 0x10CB08F0
			{
				mangled_x86(MANGLED_TODO, "?Init@WebScoreboard@Ui@Web@@YAXXZ");
				// procedure flags: nofpo
				todo("implement");
				_sub_10CB08F0();
			}

			_extern void _sub_10CB1200(bool, bool, bool);
			void Show(bool locked, bool pregame, bool animate) // 0x10CB1200
			{
				mangled_x86(MANGLED_TODO, "?Show@WebScoreboard@Ui@Web@@YAX_N00@Z");
				// static ...; // 0x10CB14CC
				// static ...; // 0x10CB14A8
				// static ...; // 0x10CB14A0
				// bool locked;
				// bool pregame;
				// bool animate;
				// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
				// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> string_buff;
				// s_scoreboard_update update;
				todo("implement");
				_sub_10CB1200(locked, pregame, animate);
			}

			_extern void _sub_10CB0810();
			void Hide() // 0x10CB0810
			{
				mangled_x86(MANGLED_TODO, "?Hide@WebScoreboard@Ui@Web@@YAXXZ");
				// procedure flags: nofpo
				todo("implement");
				_sub_10CB0810();
			}

			_extern void _sub_10CB15A0();
			void Tick() // 0x10CB15A0
			{
				mangled_x86(MANGLED_TODO, "?Tick@WebScoreboard@Ui@Web@@YAXXZ");
				// procedure flags: nofpo
				// s_player_datum *player;
				// static bool previousHasUnit; // 0x1247EE10
				// short round_condition_flags;
				// static __int32 previousMapLoadingState; // 0x1247EE08
				// unsigned long roundCountdown;
				// void *engine_globals;
				// static __int32 previous_round_condition_flags; // 0x1247EE0C
				// bool currentMapLoadingState;
				// function call : bool (*const)()
				// function call : bool (*const)()
				// function call : long (*const)()
				// function call : float (*const)(float)
				// function call : bool (*const)()
				// function call : bool (*const)()
				// function call : bool (*const)()
				// function call : bool (*const)()
				// function call : unsigned long (*const)(long)
				todo("implement");
				_sub_10CB15A0();
			}
		}
	}
}

extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > _sub_10CB37C0();
namespace Web
{
	namespace Ui
	{
		namespace WebScoreboard
		{
			std::basic_string<char,std::char_traits<char>,std::allocator<char> > getScoreboard() // 0x10CB37C0
			{
				mangled_x86(MANGLED_TODO, "?getScoreboard@WebScoreboard@Ui@Web@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
				// procedure flags: nofpo
				// static ...; // 0x10CB39CA
				// static ...; // 0x10CB39C3
				// static ...; // 0x10CB39BC
				// static ...; // 0x10CB3998
				// static ...; // 0x10CB3990
				// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
				// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> string_buff;
				// s_session_update update;
				todo("implement");
				std::string __result = _sub_10CB37C0();
				return __result;
			}
		}
	}
}

/* ---------- private code */
