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

#include "Modules/ModuleInput.hpp"  // hades: added for 0x10CB0C10
#include "Modules/ModuleServer.hpp"  // hades: added for 0x10CB27C0
#include "Player/PlayerCustomization.hpp"  // hades: added for 0x10CB27C0
#include "Player/PlayerInfo.hpp"  // hades: added for 0x10CB27C0
#include "mods/mod_system.hpp"  // hades: added for 0x10CB27C0

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
		long session_player_index; // 0x4
		long team_index; // 0x8
		unsigned long color; // 0xC
		unsigned long long uid; // 0x10
		std::string player_name; // 0x18
		std::string service_tag; // 0x34
		std::string emblem; // 0x50
		// s_session_player(s_session_player &); /* compiler_generated() */
		// s_session_player(s_session_player const &); /* compiler_generated() */
		// s_session_player(); /* compiler_generated() */
		~s_session_player(); /* compiler_generated() */
		// s_session_player &operator=(s_session_player &); /* compiler_generated() */
		// s_session_player &operator=(s_session_player const &); /* compiler_generated() */
	};
	static_assert(sizeof(s_session_player) == 112, "Invalid s_session_player size");

	struct s_session_update
	{
		bool valid; // 0x0
		bool has_teams; // 0x1
		bool is_host; // 0x2
		// unsigned char __pad0[1]; // 0x3
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
		// s_session_update(s_session_update &); /* compiler_generated() */
		// s_session_update(s_session_update const &); /* compiler_generated() */
		// s_session_update(); /* compiler_generated() */
		~s_session_update(); /* compiler_generated() */
		// s_session_update &operator=(s_session_update &); /* compiler_generated() */
		// s_session_update &operator=(s_session_update const &); /* compiler_generated() */
		// unsigned char __pad1[4]; // 0x7E4
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
		// s_scoreboard_update(s_scoreboard_update &); /* compiler_generated() */
		// s_scoreboard_update(s_scoreboard_update const &); /* compiler_generated() */
		// s_scoreboard_update(); /* compiler_generated() */
		~s_scoreboard_update(); /* compiler_generated() */
		// s_scoreboard_update &operator=(s_scoreboard_update &); /* compiler_generated() */
		// s_scoreboard_update &operator=(s_scoreboard_update const &); /* compiler_generated() */
		// unsigned char __pad0[4]; // 0x4FF4
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
	bool postgame = false; // 0x1C
	bool pregame = false; // 0x1D
	bool returningToLobby = false; // 0x1E
	bool acceptsInput = true; // 0x1F
	bool spawning_soon = false; // 0x20
	long post_game_time; // 0x24
	bool sent_final_update = false; // 0x28
	s_globals(); /* compiler_generated() */
};
// static_assert(sizeof(s_globals) == 44, "Invalid s_globals size");
// Withheld: the type inventory does not describe this type, so its
// padding could not be reconstructed.

/* ---------- prototypes */

extern bool (*const game_is_multiplayer)();  // hades: added for 0x10CB15A0  // hades: added for 0x10CB15A0
namespace Player { namespace PlayerPodium { extern bool PodiumEnabled(); extern bool PodiumhasInitialized(); extern bool PodiumIsReady(); } }  // hades: added for 0x10CB15A0  // hades: added for 0x10CB15A0

extern void player_format_uid(char *string, unsigned long long id);  // hades: added for 0x10CB4150

extern bool (*const network_session_interface_get_squad_session)(c_network_session **);  // hades: added for 0x10CB3270
namespace Player { namespace Emblems { extern std::string BuildUrl(s_player_emblem_configuration config); } }  // hades: added for 0x10CB27C0
extern float (*const game_ticks_to_seconds)(float);  // hades: added for 0x10CB3270
extern bool (*game_is_campaign)();  // hades: added for 0x10CB1DE0
extern bool unit_is_holding_objective(long unit_index);  // hades: added for 0x10CB1DE0

namespace Patches::Input { void RegisterDefaultInputHandler(void (*func)()); }  // hades: added for 0X10CB08F0

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

extern long (*const game_time_get)();  // hades: added for 0x10CB0990

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern s_globals globals; // 0x1247EDDC
}
using namespace hades_file_local;
/* ---------- public code */

namespace Web
{
	namespace Ui
	{
		namespace WebScoreboard
		{
			void OnGameInputUpdated() // 0x10CB0C10
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?OnGameInputUpdated@WebScoreboard@Ui@Web@@YAXXZ");
				// procedure flags: nofpo
				// Blam::Input::ActionState *uiSelect;
					// float movementAmount;
					// float *values;
						// __int32 i;

				if (globals.scoreboard_state == _game_scoreboard_state_round_over || globals.scoreboard_state == _game_scoreboard_state_game_over)
					return;
				Blam::Input::ActionState *uiSelect = Blam::Input::GetActionState(Blam::Input::eGameActionUiSelect);
				if (!(uiSelect->Flags & Blam::Input::eActionStateFlagsHandled) && uiSelect->Ticks == 1)
				{
					uiSelect->Flags |= Blam::Input::eActionStateFlagsHandled;
					if (strcmp((char *)Pointer(0x22AB018)(0x1A4, 1), "mainmenu") != 0)
					{
						globals.locked = false;
						float *values = (float *)0x244D4EC;
						float movementAmount = 0.0f;
						for (__int32 i = 0; i < 8; i++)
							movementAmount += values[i] * values[i];
						if (Modules::ModuleInput::Instance().VarSmartScoreboard->ValueInt == 1 && abs(movementAmount) < 0.125f)
							globals.locked = true;
						if (Blam::Input::GetKeyTicks(Blam::Input::eKeyCodeShift, Blam::Input::eInputTypeUi) || difftime(time(nullptr), globals.last_tapped_game_time) < 0.25 && Modules::ModuleInput::Instance().VarTapScoreboard->ValueInt == 1)
							globals.locked = true;
						Show(globals.locked, globals.pregame, false);
						globals.last_tapped_game_time = time(nullptr);
						globals.was_tapped_last_tick = true;
					}
					else
					{
						Show(true, globals.pregame, false);
					}
				}
				else if (!globals.locked && globals.scoreboard_state < _game_scoreboard_state_round_over && globals.was_tapped_last_tick && !uiSelect->Ticks)
				{
					Web::Ui::ScreenLayer::NotifyScreen("scoreboard", "scoreboard_hide", {});
					globals.was_tapped_last_tick = false;
				}
			}

			void OnLifeCycleStateChanged(Blam::Network::LifeCycleState newState) // 0x10CB10C0
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?OnLifeCycleStateChanged@WebScoreboard@Ui@Web@@YAXW4LifeCycleState@Network@Blam@@@Z");
				// Blam::Network::LifeCycleState newState;

				if (newState == Blam::Network::eLifeCycleStateStartGame)
				{
					Web::Ui::ScreenLayer::NotifyScreen("scoreboard", "scoreboard_reset", {});
				}
			}

			void OnEvent(unsigned long player, s_game_engine_event_data const *event, s_multiplayer_event_response_definition const *definition) // 0x10CB0990
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?OnEvent@WebScoreboard@Ui@Web@@YAXKPBUs_game_engine_event_data@@PBUs_multiplayer_event_response_definition@@@Z");
				// s_multiplayer_event_response_definition const *definition;
					// s_player_datum *player;
						// unsigned long firstTimeSpawning;
						// long secondsUntilSpawn;
				// function call : long (*const)()
				// function call : unsigned long (*const)(long)

				if (event->name == 0x4004D || event->name == 0x4005A)
				{
					globals.post_game_time = game_time_get();
					globals.postgame = true;
				}
				if (event->name == 0x4004E)
				{
					s_player_datum *player = player_get(((unsigned long (*const)(long))0x589C30)(0));
					if (player)
					{
						long secondsUntilSpawn = player->respawn_timer_countdown_seconds;
						unsigned long firstTimeSpawning = player->flags & 8;
						if (!globals.spawning_soon && !firstTimeSpawning && secondsUntilSpawn > 0 && secondsUntilSpawn < 2)
						{
							globals.spawning_soon = true;
							globals.locked = false;
							globals.postgame = false;
							globals.acceptsInput = false;
							Show(globals.locked, globals.pregame, false);
						}
					}
				}
				if (event->name == 0x4004F && globals.spawning_soon)
				{
					globals.pregame = false;
					globals.spawning_soon = false;
					globals.acceptsInput = true;
					Web::Ui::ScreenLayer::NotifyScreen("scoreboard", "scoreboard_hide", {});
				}
			}

			void Init() // 0x10CB08F0
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?Init@WebScoreboard@Ui@Web@@YAXXZ");
				// procedure flags: nofpo

				Patches::Input::RegisterDefaultInputHandler(OnGameInputUpdated);
				Patches::Network::OnLifeCycleStateChanged(OnLifeCycleStateChanged);
				Patches::Events::OnEvent(OnEvent);
			}

			void Show(bool locked, bool pregame, bool animate) // 0x10CB1200
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?Show@WebScoreboard@Ui@Web@@YAX_N00@Z");
				// static ...; // 0x10CB14CC
				// static ...; // 0x10CB14A8
				// static ...; // 0x10CB14A0
				// bool locked;
				// bool pregame;
				// bool animate;
				// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
				// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> string_buff;
				// s_scoreboard_update update;

				rapidjson::StringBuffer string_buff;
				rapidjson::Writer<rapidjson::StringBuffer> writer(string_buff);
				s_scoreboard_update update = { false };
				build_full_update(update);
				writer.StartObject();
				writer.Key("update");
				serialize_update(writer, update);
				writer.Key("locked");
				writer.Bool(locked);
				writer.Key("pregame");
				writer.Bool(pregame);
				writer.Key("animate");
				writer.Bool(animate);
				writer.EndObject();
				globals.shown = true;
				Web::Ui::ScreenLayer::Show("scoreboard", string_buff.GetString());
			}

			void Hide() // 0x10CB0810
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?Hide@WebScoreboard@Ui@Web@@YAXXZ");
				// procedure flags: nofpo

				globals.shown = false;
				globals.was_tapped_last_tick = false;
				Web::Ui::ScreenLayer::Hide("scoreboard");
			}

			void Tick() // 0x10CB15A0
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?Tick@WebScoreboard@Ui@Web@@YAXXZ");
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

				static __int32 previousMapLoadingState = 0;
				static __int32 previous_round_condition_flags = 0;
				static bool previousHasUnit = false;
				if (!(game_is_multiplayer() || ((bool (*const)())0x531E90)()))
					return;
				check_to_send_update();
				if (globals.postgame)
				{
					if (game_ticks_to_seconds((float)(game_time_get() - globals.post_game_time)) > 2.0f)
					{
						if (!((bool (*const)())0x531B20)() || !Player::PlayerPodium::PodiumEnabled() || !Player::PlayerPodium::PodiumIsReady() || !Player::PlayerPodium::PodiumhasInitialized())
							Show(globals.locked, globals.pregame, false);
						globals.acceptsInput = false;
						globals.postgame = false;
						globals.returningToLobby = true;
					}
				}
				bool currentMapLoadingState = *(bool *)0x23917F0;
				if (previousMapLoadingState && !currentMapLoadingState)
				{
					if (((bool (*const)())0x531E90)())
					{
						globals.returningToLobby = false;
						globals.acceptsInput = true;
						Web::Ui::ScreenLayer::NotifyScreen("scoreboard", "scoreboard_hide", {});
					}
					else
					{
						globals.locked = false;
						globals.postgame = false;
						globals.acceptsInput = false;
						globals.pregame = true;
						Show(globals.locked, globals.pregame, false);
					}
				}
				else if (!previousMapLoadingState && currentMapLoadingState && ((bool (*const)())0x531E90)() && !globals.returningToLobby)
				{
					globals.locked = false;
					globals.postgame = false;
					Web::Ui::ScreenLayer::NotifyScreen("scoreboard", "scoreboard_hide", {});
				}
				previousMapLoadingState = currentMapLoadingState;
				if (!((bool (*const)())0x550F90)())
					return;
				void *engine_globals = *(void **)tls_get(0x48);
				short round_condition_flags = *(short *)((char *)engine_globals + 0xE110);
				unsigned long roundCountdown = Modules::ModuleServer::Instance().VarServerCountdownClient->ValueInt;
				if (roundCountdown && (previous_round_condition_flags & 8) && !(round_condition_flags & 8))
				{
					globals.locked = false;
					globals.postgame = false;
					globals.acceptsInput = true;
					Web::Ui::ScreenLayer::NotifyScreen("scoreboard", "scoreboard_hide", {});
				}
				previous_round_condition_flags = round_condition_flags;
				s_player_datum *player = player_get(((unsigned long (*const)(long))0x589C30)(0));
				if (!player)
					return;
				if (!roundCountdown && player->unit_index != -1 && !previousHasUnit)
				{
					globals.locked = false;
					globals.postgame = false;
					globals.acceptsInput = true;
					Web::Ui::ScreenLayer::NotifyScreen("scoreboard", "scoreboard_hide", {});
				}
				if (player->unit_index != -1 && !previousHasUnit && globals.pregame)
				{
					globals.pregame = false;
					globals.acceptsInput = true;
					Web::Ui::ScreenLayer::NotifyScreen("scoreboard", "scoreboard_hide", {});
				}
				previousHasUnit = player->unit_index != -1;
			}
		}
	}
}


namespace Web
{
	namespace Ui
	{
		namespace WebScoreboard
		{
			std::string getScoreboard() // 0x10CB37C0
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?getScoreboard@WebScoreboard@Ui@Web@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
				// procedure flags: nofpo
				// static ...; // 0x10CB39CA
				// static ...; // 0x10CB39C3
				// static ...; // 0x10CB39BC
				// static ...; // 0x10CB3998
				// static ...; // 0x10CB3990
				// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
				// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> string_buff;
				// s_session_update update;

				rapidjson::StringBuffer string_buff;
				rapidjson::Writer<rapidjson::StringBuffer> writer(string_buff);
				s_session_update update{};
				build_session_update(update);
				serialize_session_update(writer, update);
				return string_buff.GetString();
			}
		}
	}
}

/* ---------- private code */

_inline s_globals::s_globals() = default; // 0x10CAFEF0

// mangled_x86(MANGLED_DEFAULT, "??1s_scoreboard_update@hades_file_local@@QAE@XZ"); no body to assert in
_inline s_scoreboard_update::~s_scoreboard_update() = default; // 0x10CB0080

// mangled_x86(MANGLED_DEFAULT, "??1s_session_player@hades_file_local@@QAE@XZ"); no body to assert in
_inline s_session_player::~s_session_player() = default; // 0x10CB00D0

// mangled_x86(MANGLED_DEFAULT, "??1s_session_update@hades_file_local@@QAE@XZ"); no body to assert in
_inline s_session_update::~s_session_update() = default; // 0x10CB0140

void serialize_session_player(rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &writer, s_session_player const &player) // 0x10CB4150
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?serialize_session_player@@YAXAAV?$Writer@V?$GenericStringBuffer@U?$UTF8@D@rapidjson@@VCrtAllocator@2@@rapidjson@@U?$UTF8@D@2@U32@VCrtAllocator@2@$0A@@rapidjson@@ABUs_session_player@hades_file_local@@@Z");
	// `anonymous-namespace'::serialize_session_player
	// static ...; // 0x10CB4300
	// static ...; // 0x10CB42F8
	// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &writer;
	// s_session_player const &player;
	// char buff[17];

	writer.StartObject();
	writer.Key("isHost");
	writer.Bool(player.is_host);
	writer.Key("playerIndex");
	writer.Int(player.session_player_index);
	writer.Key("teamIndex");
	writer.Int(player.team_index);
	writer.Key("name");
	writer.String(player.player_name.c_str());
	char buff[17];
	buff[0] = 0;
	player_format_uid(buff, player.uid);
	writer.Key("uid");
	writer.String(buff);
	writer.Key("stag");
	writer.String(player.service_tag.c_str());
	sprintf_s(buff, "#%06X", player.color);
	writer.Key("color");
	writer.String(buff);
	writer.Key("emblem");
	writer.String(player.emblem.c_str());
	writer.EndObject();
}

void serialize_session_update(rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &writer, s_session_update const &update) // 0x10CB4390
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?serialize_session_update@@YAXAAV?$Writer@V?$GenericStringBuffer@U?$UTF8@D@rapidjson@@VCrtAllocator@2@@rapidjson@@U?$UTF8@D@2@U32@VCrtAllocator@2@$0A@@rapidjson@@ABUs_session_update@hades_file_local@@@Z");
	// `anonymous-namespace'::serialize_session_update
	// s_session_update const &update;
		// long i;

	writer.StartObject();
	writer.Key("gameMode");
	writer.Int(update.game_mode);
	writer.Key("gameId");
	writer.Int64(update.game_id);
	writer.Key("gameType");
	writer.Int(update.game_engine_type);
	writer.Key("lobbyType");
	writer.Int(update.game_lobby_type);
	writer.Key("modName");
	writer.String(update.mod_name.c_str());
	writer.Key("modAuthor");
	writer.String(update.mod_author.c_str());
	writer.Key("modVersion");
	writer.String(update.mod_version.c_str());
	writer.Key("numRounds");
	writer.Int(update.number_of_rounds);
	writer.Key("currentRound");
	writer.Int(update.current_round);
	writer.Key("hasTeams");
	writer.Bool(update.has_teams);
	writer.Key("isHost");
	writer.Bool(update.is_host);
	writer.Key("mapVariant");
	writer.String(update.map_variant_name.c_str());
	writer.Key("gameVariant");
	writer.String(update.game_variant_name.c_str());
	writer.Key("sessionMaxPlayers");
	writer.Int(update.sessionMaxPlayers);
	writer.Key("playersInfo");
	writer.RawValue(update.players_info.c_str(), update.players_info.size(), rapidjson::kObjectType);
	writer.Key("playersPingInfo");
	writer.RawValue(update.players_ping_info.c_str(), update.players_ping_info.size(), rapidjson::kObjectType);
	writer.Key("players");
	writer.StartArray();
	for (long i = 0; i < update.player_count; i++)
		serialize_session_player(writer, update.players[i]);
	writer.EndArray();
	writer.EndObject();
}

void serialize_scores_update(rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &writer, s_scores_update const &update) // 0x10CB3AF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?serialize_scores_update@@YAXAAV?$Writer@V?$GenericStringBuffer@U?$UTF8@D@rapidjson@@VCrtAllocator@2@@rapidjson@@U?$UTF8@D@2@U32@VCrtAllocator@2@$0A@@rapidjson@@ABUs_scores_update@hades_file_local@@@Z");
	// `anonymous-namespace'::serialize_scores_update
	// s_scores_update const &update;
		// long i;
			// s_game_results_player_statistics const &stats;
			// c_game_statborg::s_player_row const &scores;

	writer.StartObject();
	writer.Key("gameFinished");
	writer.Bool(update.game_finished);
	writer.Key("gameTied");
	writer.Bool(update.game_tied);
	writer.Key("roundOver");
	writer.Bool(update.round_over);
	writer.Key("playerScores");
	writer.StartArray();
	for (long i = 0; i < 16; i++)
	{
		c_game_statborg::s_player_row const &scores = update.player_scores[i];
		s_game_results_player_statistics const &stats = update.player_stats[i];
		if (!(update.valid_player_mask & (1 << i)))
			continue;
		writer.StartObject();
		if (update.game_lobby_type != 0 && update.game_lobby_type != 5)
		{
			writer.Key("place");
			writer.Int(update.player_place[i]);
			writer.Key("score");
			writer.Int(scores.score);
			writer.Key("total");
			writer.Int(scores.total_score);
			writer.Key("kills");
			writer.Int(scores.kills);
			writer.Key("deaths");
			writer.Int(scores.deaths);
			writer.Key("suicides");
			writer.Int(scores.suicides);
			writer.Key("betrayals");
			writer.Int(scores.betrayals);
			writer.Key("assists");
			writer.Int(scores.assists);
			writer.Key("bestStreak");
			writer.Int(stats.best_streak);
		}
		if (update.game_engine_type == 1 || update.game_engine_type == 9 || update.game_engine_type == 3)
		{
			writer.Key("flagKills");
			writer.Int(stats.weapon_stats[33].kills);
			writer.Key("ballKills");
			writer.Int(stats.weapon_stats[36].kills);
		}
		else if (update.game_engine_type == 4)
		{
			writer.Key("kingsKilled");
			writer.Int(stats.kings_killed);
			writer.Key("timeInHill");
			writer.Int(stats.time_in_hill);
			writer.Key("timeControllingHill");
			writer.Int(stats.time_controlling_hill);
		}
		else if (update.game_engine_type == 10)
		{
			writer.Key("humansInfected");
			writer.Int(stats.infection_infections);
			writer.Key("zombiesKilled");
			writer.Int(stats.infection_zombie_kills);
		}
		writer.EndObject();
	}
	writer.EndArray();
	writer.Key("teamScores");
	writer.StartArray();
	for (long i = 0; i < 8; i++)
	{
		if (!(update.valid_team_mask & (1 << i)))
		{
			writer.Null();
			continue;
		}
		writer.StartObject();
		writer.Key("place");
		writer.Int(update.team_place[i]);
		writer.Key("score");
		writer.Int(update.team_scores[i].score);
		writer.Key("total");
		writer.Int(update.team_scores[i].total_score);
		writer.EndObject();
	}
	writer.EndArray();
	writer.Key("deadPlayerMask");
	writer.Int(update.dead_player_mask);
	writer.Key("objectivePlayerMask");
	writer.Int(update.objective_player_mask);
	writer.Key("alphaPlayerMask");
	writer.Int(update.alpha_player_mask);
	writer.EndObject();
}

void serialize_update(rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &writer, s_scoreboard_update const &update) // 0x10CB4760
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?serialize_update@@YAXAAV?$Writer@V?$GenericStringBuffer@U?$UTF8@D@rapidjson@@VCrtAllocator@2@@rapidjson@@U?$UTF8@D@2@U32@VCrtAllocator@2@$0A@@rapidjson@@ABUs_scoreboard_update@hades_file_local@@@Z");
	// `anonymous-namespace'::serialize_update
	// s_scoreboard_update const &update;

	writer.StartObject();
	if (update.session_update.valid)
	{
		writer.Key("session");
		serialize_session_update(writer, update.session_update);
	}
	if (update.scores_update.valid)
	{
		writer.Key("scores");
		serialize_scores_update(writer, update.scores_update);
	}
	writer.EndObject(0);
}

void build_score_update(s_scores_update &update) // 0x10CB1DE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?build_score_update@@YAXAAUs_scores_update@hades_file_local@@@Z");
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
		// long i;
			// s_player_datum *player;
			// long player_datum_index;
				// c_enum<enum e_game_engine_type,long> current_gametype;
				// bool is_juggernaut;
				// bool is_zombie;
				// bool is_alpha_zombie;
		// bool tie;
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

	bool (*const player_is_vip)(long, __int32 *) = (bool (*)(long, __int32 *))0x9DEBD0;
	c_network_session *session;
	if (!network_session_interface_get_squad_session(&session))
		return;
	c_game_statborg *scoreboard = ((c_game_statborg *(*const)())0x550B80)();
	if (!scoreboard)
		return;
	bool in_game_engine = ((bool (*const)())0x552410)();
	update.valid_player_mask = 0;
	update.dead_player_mask = 0;
	update.objective_player_mask = 0;
	update.alpha_player_mask = 0;
	for (long i = 0; i < 16; i++)
	{
		if (!session->get_session_membership()->is_player_valid(i))
			continue;
		s_player_datum *player = players_get()->try_and_get_absolute(i);
		if (!player)
			continue;
		long player_datum_index = ((long (*const)(long))0x53B1A0)(i);
		if ((!((bool (*const)())0x531B20)() && player->respawn_timer_countdown_seconds > 0 && !(player->flags & 8)) || (!((bool (*const)())0x531B20)() && (game_is_campaign() || ((bool (*const)())0x531E20)()) && (player->respawn_in_progress == 1 || player->single_player_respawn_timer != 0)))
			update.dead_player_mask |= 1 << i;
		if (((c_game_engine *(*const)())0x5CE150)())
		{
			c_enum<enum e_game_engine_type,long> current_gametype = ((s_game_options *(*const)())0x5322D0)()->game_variant.game_engine_type;
			bool is_zombie = (get_infection_globals()->zombie_bit_vector & (1 << i)) != 0;
			bool is_alpha_zombie = (get_infection_globals()->first_zombie_bit_vector & (1 << i)) != 0;
			bool is_juggernaut = get_juggernaut_globals()->juggernaut_player_index == player_datum_index;
			if (!((bool (*const)())0x531B20)() && ((unit_is_holding_objective(player->unit_index) && (current_gametype == _game_engine_type_ctf || current_gametype == _game_engine_type_oddball || current_gametype == _game_engine_type_assault)) || (is_zombie && current_gametype == _game_engine_type_infection) || (player_is_vip(player_datum_index, nullptr) && current_gametype == _game_engine_type_vip) || (is_juggernaut && current_gametype == _game_engine_type_juggernaut)))
				update.objective_player_mask |= 1 << i;
			if (!((bool (*const)())0x531B20)() && is_alpha_zombie && current_gametype == _game_engine_type_infection)
				update.alpha_player_mask |= 1 << i;
		}
		if (in_game_engine)
			update.player_place[i] = ((long (*const)(long))0x5506F0)(player_datum_index);
		update.player_scores[i] = scoreboard->players[i];
		update.player_stats[i] = *game_results_get_player_stats(i);
		update.valid_player_mask |= 1 << i;
	}
	update.valid_team_mask = 0;
	for (long i = 0; i < 8; i++)
	{
		if (!((bool (*const)(long))0x556610)(i))
			continue;
		if (in_game_engine)
			update.team_place[i] = ((long (*const)(long))0x550BF0)(i);
		update.team_scores[i] = scoreboard->teams[i];
		update.valid_team_mask |= 1 << i;
	}
	if (game_is_multiplayer())
		update.game_engine_type = (short)(long)((s_game_options *(*const)())0x5322D0)()->game_variant.game_engine_type;
	update.game_lobby_type = Blam::Network::GetLobbyType();
	update.game_finished = ((bool (*const)())0x531B20)();
	if (update.game_finished)
	{
		bool tie = ((bool (*const)())0x5565E0)() ? ((bool (*const)())0x54DA50)() : ((bool (*const)())0x54D9C0)();
		update.game_tied = tie;
	}
	update.round_over = !((bool (*const)())0x531B20)() && !((bool (*const)())0x550F90)();
	update.valid = true;
}

void build_session_update(s_session_update &update) // 0x10CB27C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?build_session_update@@YAXAAUs_session_update@hades_file_local@@@Z");
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
		// long i;
			// s_network_session_player *player;
			// s_static_string<5> service_tag;
			// s_player_datum *game_player;
			// s_session_player *player_update;
			// s_static_string<16> player_name;
	// function call : bool (*const)(c_network_session **)
	// function call : s_game_options *(*const)()
	// function call : bool (*const)()
	// function call : long (*const)()
	// function call : __int32 (*const)()

	c_network_session *session;
	if (!network_session_interface_get_squad_session(&session))
		return;
	s_game_options *game_options = ((s_game_options *(*const)())0x5322D0)();
	for (long i = 0; i < 16; i++)
	{
		if (!session->get_session_membership()->is_player_valid(i))
			continue;
		s_player_datum *game_player = players_get()->try_and_get_absolute(i);
		s_network_session_player *player = session->get_session_membership()->get_player(i);
		s_session_player *player_update = &update.players[update.player_count++];
		s_static_string<16> player_name;
		s_static_string<5> service_tag;
		service_tag.set_wchar(player->configuration.host.appearance.service_tag);
		player_name.set_wchar(player->configuration.host.player_name);
		player_update->uid = player->configuration.host.player_uid;
		player_update->service_tag = service_tag.get_string();
		player_update->player_name = player_name.get_string();
		if (Modules::ModuleServer::Instance().VarServerDedicatedClient->ValueInt == 1)
			player_update->is_host = false;
		else
			player_update->is_host = i == session->get_session_membership()->host_peer_index();
		player_update->session_player_index = i;
		player_update->team_index = player->configuration.host.team;
		player_update->color = Player::CPlayerCustomization::GetPlayerPrimaryColor(i);
		player_update->emblem = Player::Emblems::BuildUrl(player->configuration.host.appearance.emblem_config);
	}
	update.is_host = session->is_host();
	update.game_engine_type = (long)game_options->game_variant.game_engine_type;
	update.game_lobby_type = Blam::Network::GetLobbyType();
	update.game_mode = game_options->game_mode;
	update.game_id = game_options->game_id;
	update.has_teams = ((bool (*const)())0x5565E0)();
	update.number_of_rounds = ((long (*const)())0x5504C0)();
	update.current_round = ((__int32 (*const)())0x550AD0)() + 1;
	std::string playersInfo = Modules::ModuleServer::Instance().VarPlayersInfoClient->ValueString;
	if (playersInfo.empty() || playersInfo == "{}")
		playersInfo = Player::CPlayersInfo::GeneratePlayerInfo();
	update.players_info = playersInfo;
	update.players_ping_info = Modules::ModuleServer::Instance().VarPlayersPingInfoClient->ValueString;
	update.valid = true;
	update.sessionMaxPlayers = session->get_maximum_player_count();
	std::string modhash = c_mod_system::get_current_package_hash();
	c_mod_package_manager::s_entry mod_package;
	bool hasModSet = c_mod_system::get_mod_info_by_hash(modhash.c_str(), &mod_package);
	update.mod_author = hasModSet ? mod_package.author : "";
	update.mod_name = hasModSet ? Utils::String::ThinString(mod_package.name) : std::string("");
	update.mod_version = hasModSet ? std::to_string(mod_package.version_major) + "." + std::to_string(mod_package.version_minor) : std::string("");
}

void build_full_update(s_scoreboard_update &update) // 0x10CB1D80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?build_full_update@@YAXAAUs_scoreboard_update@hades_file_local@@@Z");
	// `anonymous-namespace'::build_full_update
	// s_scoreboard_update &update;

	build_session_update(update.session_update);
	build_score_update(update.scores_update);
}

void check_to_send_update() // 0x10CB3270
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?check_to_send_update@@YAXXZ");
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
		// s_scoreboard_update update;
			// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> string_buff;
			// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> json_writer;
	// function call : bool (*const)(c_network_session **)
	// function call : bool (*const)()
	// function call : bool (*const)()
	// function call : float (*const)(float)

	bool (*const game_results_get_game_finalized)() = reinterpret_cast<bool (*)()>(0x56E570);
	c_network_session *session;
	if (!network_session_interface_get_squad_session(&session) || !session->established())
		return;
	if (!((bool(__cdecl *)())0x5314B0)())
	{
		globals.sent_final_update = false;
		return;
	}
	bool is_final_update = false;
	if (game_results_get_game_finalized())
	{
		if (globals.sent_final_update)
			return;
		globals.sent_final_update = true;
		is_final_update = true;
	}
	bool membership_changed = false;
	if (globals.last_membership_update_number != session->get_session_membership_update_number())
	{
		membership_changed = true;
		globals.last_membership_update_number = session->get_session_membership_update_number();
	}
	globals.update_timer++;
	if (game_ticks_to_seconds((float)globals.update_timer) >= 0.25f || membership_changed || is_final_update)
	{
		s_scoreboard_update update = { false };
		globals.update_timer = 0;
		if (globals.requires_session_update || membership_changed)
		{
			build_session_update(update.session_update);
			globals.requires_session_update = false;
		}
		build_score_update(update.scores_update);
		if (update.scores_update.valid || update.session_update.valid)
		{
			rapidjson::StringBuffer string_buff;
			rapidjson::Writer<rapidjson::StringBuffer> json_writer(string_buff);
			serialize_update(json_writer, update);
			Web::Ui::ScreenLayer::NotifyScreen("scoreboard", "scoreboard_update", string_buff.GetString());
		}
	}
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

/* ---------- explicit instantiations */
template bool s_static_array<s_session_player,16>::valid(__int32);
template s_session_player const & s_static_array<s_session_player,16>::operator[](long) const; // 0x10CB0690
template s_session_player & s_static_array<s_session_player,16>::operator[](long); // 0x10CB0610
