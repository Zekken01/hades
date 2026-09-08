/* ---------- headers */

#include "hades/hades.h"

#include "Blam/BlamInput.hpp"
#include "Blam/BlamNetwork.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/cseries/static_string.inl"
#include "Blam/game/engine/game_engine.hpp"
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
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "mods/FileSystem/ModPackageFileSystemView.hpp"
#include "mods/font_package.hpp"
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

class c_mod_package_manager;
class c_network_session;
struct c_game_engine;
struct c_game_statborg;
struct s_game_engine_event_data;
struct s_game_options;
struct s_game_results_player_statistics;
struct s_globals;
struct s_multiplayer_event_response_definition;
struct s_network_session_player;
struct s_player_datum;
namespace Blam
{
	namespace Input
	{
		struct ActionState;
	}
}
namespace hades_file_local
{
	struct s_session_player;
	struct s_session_update;
	struct s_scores_update;
	struct s_scoreboard_update;
}
using namespace hades_file_local;

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

namespace hades_file_local
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
using namespace hades_file_local;
/* ---------- definitions */

namespace hades_file_local
{
	struct s_session_player
	{
		bool is_host; // 0x0
		unsigned char __pad0[3]; // 0x1
		long session_player_index; // 0x4
		long team_index; // 0x8
		unsigned long color; // 0xC
		unsigned long long uid; // 0x10
		std::string player_name; // 0x18
		std::string service_tag; // 0x34
		std::string emblem; // 0x50
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
		std::string players_info; // 0x71C
		std::string players_ping_info; // 0x738
		std::string map_variant_name; // 0x754
		std::string game_variant_name; // 0x770
		long sessionMaxPlayers; // 0x78C
		std::string mod_name; // 0x790
		std::string mod_author; // 0x7AC
		std::string mod_version; // 0x7C8
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
using namespace hades_file_local;
typedef unsigned long argb_color;

namespace hades_file_local
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
using namespace hades_file_local;
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

namespace hades_file_local
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
using namespace hades_file_local;
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
			extern std::string getScoreboard();
		}
	}
}

void serialize_session_player(rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &writer, s_session_player const &player);
void serialize_session_update(rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &writer, s_session_update const &update);
void serialize_scores_update(rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &writer, s_scores_update const &update);
void serialize_update(rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &writer, s_scoreboard_update const &update);
void build_score_update(s_scores_update &update);
void build_session_update(s_session_update &update);
void build_full_update(s_scoreboard_update &update);
void check_to_send_update();

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

extern std::string _sub_10CB37C0();
namespace Web
{
	namespace Ui
	{
		namespace WebScoreboard
		{
			std::string getScoreboard() // 0x10CB37C0
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

extern s_globals* _sub_10CAFEF0(s_globals *const);
_inline s_globals::s_globals() // 0x10CAFEF0
{
	// `anonymous-namespace'::<unnamed-type-globals>::<unnamed-type-globals>
	// s_globals *const this;
	compiler_generated();
	todo("implement");
	_sub_10CAFEF0(this);
}

_inline s_scoreboard_update::~s_scoreboard_update() // 0x10CB0080
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??1s_scoreboard_update@hades_file_local@@QAE@XZ");
	// `anonymous-namespace'::s_scoreboard_update::~s_scoreboard_update
	// s_scoreboard_update *const this;

	compiler_generated();
}

_inline s_session_player::~s_session_player() // 0x10CB00D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??1s_session_player@hades_file_local@@QAE@XZ");
	// `anonymous-namespace'::s_session_player::~s_session_player
	// s_session_player *const this;

	compiler_generated();
}

_inline s_session_update::~s_session_update() // 0x10CB0140
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??1s_session_update@hades_file_local@@QAE@XZ");
	// `anonymous-namespace'::s_session_update::~s_session_update
	// s_session_update *const this;

	compiler_generated();
}

_extern void _sub_10CB4150(rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &, s_session_player const &);
void serialize_session_player(rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &writer, s_session_player const &player) // 0x10CB4150
{
	// `anonymous-namespace'::serialize_session_player
	// static ...; // 0x10CB4300
	// static ...; // 0x10CB42F8
	// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &writer;
	// s_session_player const &player;
	// char buff[17];
	todo("implement");
	_sub_10CB4150(writer, player);
}

_extern void _sub_10CB4390(rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &, s_session_update const &);
void serialize_session_update(rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &writer, s_session_update const &update) // 0x10CB4390
{
	// `anonymous-namespace'::serialize_session_update
	// s_session_update const &update;
	{
		// long i;
	}
	todo("implement");
	_sub_10CB4390(writer, update);
}

_extern void _sub_10CB3AF0(rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &, s_scores_update const &);
void serialize_scores_update(rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &writer, s_scores_update const &update) // 0x10CB3AF0
{
	// `anonymous-namespace'::serialize_scores_update
	// s_scores_update const &update;
	{
		// long i;
		{
			// s_game_results_player_statistics const &stats;
			// c_game_statborg::s_player_row const &scores;
		}
	}
	{
	}
	todo("implement");
	_sub_10CB3AF0(writer, update);
}

_extern void _sub_10CB4760(rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &, s_scoreboard_update const &);
void serialize_update(rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &writer, s_scoreboard_update const &update) // 0x10CB4760
{
	// `anonymous-namespace'::serialize_update
	// s_scoreboard_update const &update;
	todo("implement");
	_sub_10CB4760(writer, update);
}

_extern void _sub_10CB1DE0(s_scores_update &);
void build_score_update(s_scores_update &update) // 0x10CB1DE0
{
	// `anonymous-namespace'::build_score_update
	// static ...; // 0x10CB25B9
	// static ...; // 0x10CB25A8
	// static ...; // 0x10CB2590
	// static ...; // 0x10CB2588
	// s_scores_update &update;
	// bool in_game_engine;
	// bool (*const player_is_vip)(long, __int32 *);
	// c_game_statborg *scoreboard;
	// c_network_session *session;
	{
		// long i;
		{
			// s_player_datum *player;
			// long player_datum_index;
			{
				// c_enum<enum e_game_engine_type,long> current_gametype;
				// bool is_juggernaut;
				// bool is_zombie;
				// bool is_alpha_zombie;
			}
		}
	}
	{
	}
	{
		// bool tie;
	}
	// function call : bool (*const)(c_network_session **)
	// function call : c_game_statborg *(*const)()
	// function call : bool (*const)()
	// function call : long (*const)(long)
	// function call : bool (*const)()
	// function call : bool (*const)()
	// function call : bool (*)()
	// function call : bool (*const)()
	// function call : c_game_engine *(*const)()
	// function call : s_game_options *(*const)()
	// function call : bool (*const)()
	// function call : bool (*const)(long, __int32 *)
	// function call : bool (*const)()
	// function call : long (*const)(long)
	// function call : bool (*const)(long)
	// function call : long (*const)(long)
	// function call : bool (*const)()
	// function call : s_game_options *(*const)()
	// function call : bool (*const)()
	// function call : bool (*const)()
	// function call : bool (*const)()
	// function call : bool (*const)()
	// function call : bool (*const)()
	// function call : bool (*const)()
	todo("implement");
	_sub_10CB1DE0(update);
}

_extern void _sub_10CB27C0(s_session_update &);
void build_session_update(s_session_update &update) // 0x10CB27C0
{
	// `anonymous-namespace'::build_session_update
	// static ...; // 0x10CB303C
	// static ...; // 0x10CB3030
	// static ...; // 0x10CB3024
	// static ...; // 0x10CB3018
	// static ...; // 0x10CB3010
	// static ...; // 0x10CB3004
	// static ...; // 0x10CB2FBC
	// static ...; // 0x10CB2FB4
	// s_session_update &update;
	// s_game_options *game_options;
	// bool hasModSet;
	// std::string playersInfo;
	// std::string modhash;
	// c_network_session *session;
	// c_mod_package_manager::s_entry mod_package;
	{
		// long i;
		{
			// s_network_session_player *player;
			// s_static_string<5> service_tag;
			// s_player_datum *game_player;
			// s_session_player *player_update;
			// s_static_string<16> player_name;
		}
	}
	// function call : bool (*const)(c_network_session **)
	// function call : s_game_options *(*const)()
	// function call : bool (*const)()
	// function call : long (*const)()
	// function call : __int32 (*const)()
	todo("implement");
	_sub_10CB27C0(update);
}

_extern void _sub_10CB1D80(s_scoreboard_update &);
void build_full_update(s_scoreboard_update &update) // 0x10CB1D80
{
	// `anonymous-namespace'::build_full_update
	// s_scoreboard_update &update;
	todo("implement");
	_sub_10CB1D80(update);
}

_extern void _sub_10CB3270();
void check_to_send_update() // 0x10CB3270
{
	// `anonymous-namespace'::check_to_send_update
	// procedure flags: nofpo
	// static ...; // 0x10CB36A3
	// static ...; // 0x10CB369C
	// static ...; // 0x10CB3690
	// static ...; // 0x10CB3684
	// static ...; // 0x10CB3654
	// static ...; // 0x10CB364C
	// bool membership_changed;
	// bool is_final_update;
	// bool (*const game_results_get_game_finalized)();
	// c_network_session *session;
	{
		// s_scoreboard_update update;
		{
			// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> string_buff;
			// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> json_writer;
		}
	}
	// function call : bool (*const)(c_network_session **)
	// function call : bool (*const)()
	// function call : bool (*const)()
	// function call : float (*const)(float)
	todo("implement");
	_sub_10CB3270();
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool s_static_array<c_game_statborg::s_player_row,16>::valid(__int32);
template bool s_static_array<c_game_statborg::s_team_row,8>::valid(__int32);
template bool s_static_array<long,16>::valid(__int32);
template bool s_static_array<long,8>::valid(__int32);
template bool s_static_array<s_game_results_player_statistics,16>::valid(__int32);
template c_enum<enum e_game_engine_type,long>::c_enum(c_enum<enum e_game_engine_type,long> const &);
template c_enum<enum e_game_engine_type,long>::c_enum(long const &);
template c_game_statborg::s_player_row & s_static_array<c_game_statborg::s_player_row,16>::operator[](long);
template c_game_statborg::s_player_row const & s_static_array<c_game_statborg::s_player_row,16>::operator[](long) const;
template c_game_statborg::s_team_row & s_static_array<c_game_statborg::s_team_row,8>::operator[](long);
template c_game_statborg::s_team_row const & s_static_array<c_game_statborg::s_team_row,8>::operator[](long) const;
template char const * s_static_string<5>::get_string() const;
template long & s_static_array<long,16>::operator[](long);
template long & s_static_array<long,8>::operator[](long);
template long const & s_static_array<long,16>::operator[](long) const;
template long const & s_static_array<long,8>::operator[](long) const;
template s_game_results_player_statistics & s_static_array<s_game_results_player_statistics,16>::operator[](long);
template s_game_results_player_statistics const & s_static_array<s_game_results_player_statistics,16>::operator[](long) const;
template void s_static_string<5>::set_wchar(wchar_t const *);
