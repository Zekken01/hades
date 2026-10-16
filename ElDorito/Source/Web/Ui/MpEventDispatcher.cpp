/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/game/engine/game_engine_events.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Patches/Events.hpp"
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
#include "Utils/NameValueTable.hpp"
#include "Utils/StlUtil.hpp"
#include "Web/Bridge/WebRendererQueryHandler.hpp"
#include "Web/Ui/Screen.hpp"

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
#include <initializer_list>
#include <ios>
#include <iosfwd>
#include <iterator>
#include <limits>
#include <list>
#include <memory>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <system_error>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <unordered_map>
#include <utility>
#include <vector>

/* ---------- forward declarations */

struct s_game_engine_event_data;
struct s_multiplayer_event_response_definition;

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
		namespace MpEventDispatcher {}
		using namespace Web::Ui::MpEventDispatcher;
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

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Web
{
	namespace Ui
	{
		namespace MpEventDispatcher
		{
			extern void Init();
		}
	}
}

static void OnEvent(unsigned long player, s_game_engine_event_data const *event, s_multiplayer_event_response_definition const *definition);
std::string GetEventName(unsigned __int32 stringId);

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	std::unordered_map<unsigned int,std::string> EventNames = { { 0x40010, "earn_wp_event_kill" }, { 0x40011, "earn_wp_event_assist" }, { 0x40012, "earn_wp_event_perfection" }, { 0x40013, "earn_wp_event_extermination" }, { 0x40014, "earn_wp_event_multikill_2" }, { 0x40015, "earn_wp_event_multikill_3" }, { 0x40016, "earn_wp_event_multikill_4" }, { 0x40017, "earn_wp_event_multikill_5" }, { 0x40018, "earn_wp_event_multikill_6" }, { 0x40019, "earn_wp_event_multikill_7" }, { 0x4001a, "earn_wp_event_multikill_8" }, { 0x4001b, "earn_wp_event_multikill_9" }, { 0x4001c, "earn_wp_event_multikill_10" }, { 0x4001d, "earn_wp_event_bash_kill" }, { 0x4001e, "earn_wp_event_bashbehind_kill" }, { 0x4001f, "earn_wp_event_kill_sniper" }, { 0x40020, "earn_wp_event_stickygrenade_kill" }, { 0x40021, "earn_wp_event_spartanlaser_kill" }, { 0x40022, "earn_wp_event_oddball_carrier_kill_player" }, { 0x40023, "earn_wp_event_ctf_flag_carrier_kill_player" }, { 0x40024, "earn_wp_event_flame_kill" }, { 0x40025, "earn_wp_event_player_kill_spreeplayer" }, { 0x40026, "earn_wp_event_deadplayer_kill" }, { 0x40027, "earn_wp_event_vehicle_impact_kill" }, { 0x40028, "earn_wp_event_vehicle_hijack" }, { 0x40029, "earn_wp_event_shotgun_kill_sword" }, { 0x4002a, "earn_wp_event_driver_assist_gunner" }, { 0x4002b, "earn_wp_event_aircraft_hijack" }, { 0x4002c, "earn_wp_event_ctf_flag_player_kill_carrier" }, { 0x4002d, "earn_wp_event_ctf_flag_captured" }, { 0x4002e, "earn_wp_event_koth_5" }, { 0x4002f, "earn_wp_event_revenge" }, { 0x40030, "earn_wp_event_flag_grabbed_from_stand" }, { 0x40031, "earn_wp_event_flag_returned_by_player" }, { 0x40032, "earn_wp_event_5_kills_in_a_row" }, { 0x40033, "earn_wp_event_10_kills_in_a_row" }, { 0x40034, "earn_wp_event_15_kills_in_a_row" }, { 0x40035, "earn_wp_event_20_kills_in_a_row" }, { 0x40036, "earn_wp_event_25_kills_in_a_row" }, { 0x40037, "earn_wp_event_30_kills_in_a_row" }, { 0x40038, "earn_wp_event_vehicle_5" }, { 0x40039, "earn_wp_event_headshot" }, { 0x4003a, "general_event_kill" }, { 0x4003b, "general_event_suicide" }, { 0x4003c, "general_event_kill_teammate" }, { 0x4003d, "general_event_victory" }, { 0x4003e, "general_event_team_victory" }, { 0x40045, "general_event_player_quit" }, { 0x40046, "general_event_player_joined" }, { 0x40047, "general_event_killed_by_unknown" }, { 0x40048, "general_event_30_minutes_left" }, { 0x40049, "general_event_15_minutes_left" }, { 0x4004a, "general_event_5_minutes_left" }, { 0x4004b, "general_event_1_minute_left" }, { 0x4004d, "general_event_game_over" }, { 0x4004e, "general_event_respawn_tick" }, { 0x4004f, "general_event_respawn_final_tick" }, { 0x40050, "general_event_teleporter_used" }, { 0x40051, "general_event_teleporter_blocked" }, { 0x40052, "general_event_player_switched_team" }, { 0x40053, "general_event_player_rejoined" }, { 0x40054, "general_event_gained_lead" }, { 0x40055, "general_event_gained_team_lead" }, { 0x40056, "general_event_lost_lead" }, { 0x40057, "general_event_lost_team_lead" }, { 0x40058, "general_event_tied_leader" }, { 0x40059, "general_event_tied_team_leader" }, { 0x4005a, "general_event_round_over" }, { 0x4005b, "general_event_30_seconds_left" }, { 0x4005c, "general_event_10_seconds_left" }, { 0x4005d, "general_event_killed_by_falling" }, { 0x4005e, "general_event_kill_collision" }, { 0x4005f, "general_event_kill_melee" }, { 0x40060, "general_event_sudden_death" }, { 0x40061, "general_event_player_booted_player" }, { 0x40062, "general_event_kill_flag_carrier" }, { 0x40063, "general_event_kill_bomb_carrier" }, { 0x40064, "general_event_kill_sticky_grenade" }, { 0x40065, "general_event_kill_sniper" }, { 0x40066, "general_event_kill_stealth_melee" }, { 0x40067, "general_event_boarded_vehicle" }, { 0x40068, "general_event_game_start_team_notification" }, { 0x40069, "general_event_teleporter_telefrag" }, { 0x4006c, "general_event_shotgun_kill_sword" }, { 0x4006d, "general_event_kill_deadplayer" }, { 0x4006e, "general_event_vehicle_hijack" }, { 0x4006f, "general_event_aircraft_hijack" }, { 0x40070, "general_event_kill_spartanlaser" }, { 0x40071, "general_event_kill_flame" }, { 0x40072, "general_event_driver_assist_gunner" }, { 0x40073, "flavor_event_extermination" }, { 0x40074, "flavor_event_perfection" }, { 0x40075, "flavor_event_multikill_2" }, { 0x40076, "flavor_event_multikill_3" }, { 0x40077, "flavor_event_multikill_4" }, { 0x40078, "flavor_event_multikill_5" }, { 0x40079, "flavor_event_multikill_6" }, { 0x4007a, "flavor_event_multikill_7" }, { 0x4007b, "flavor_event_multikill_8" }, { 0x4007c, "flavor_event_multikill_9" }, { 0x4007d, "flavor_event_multikill_10" }, { 0x4007e, "flavor_event_5_kills_in_a_row" }, { 0x4007f, "flavor_event_10_kills_in_a_row" }, { 0x40080, "flavor_event_15_kills_in_a_row" }, { 0x40081, "flavor_event_20_kills_in_a_row" }, { 0x40082, "flavor_event_25_kills_in_a_row" }, { 0x40083, "flavor_event_30_kills_in_a_row" }, { 0x40084, "flavor_event_sniper_5" }, { 0x40085, "flavor_event_sniper_10" }, { 0x40086, "flavor_event_shotgun_5" }, { 0x40087, "flavor_event_shotgun_10" }, { 0x40088, "flavor_event_vehicle_5" }, { 0x40089, "flavor_event_vehicle_10" }, { 0x4008a, "flavor_event_sword_5" }, { 0x4008b, "flavor_event_sword_10" }, { 0x4008c, "flavor_event_juggernaut_5" }, { 0x4008d, "flavor_event_juggernaut_10" }, { 0x4008e, "flavor_event_zombie_5" }, { 0x4008f, "flavor_event_zombie_10" }, { 0x40090, "flavor_event_human_5" }, { 0x40091, "flavor_event_human_10" }, { 0x40092, "flavor_event_human_15" }, { 0x40093, "flavor_event_koth_5" }, { 0x40094, "flavor_event_shotgun_kill_sword" }, { 0x40095, "flavor_event_vehicle_impact_kill" }, { 0x40096, "flavor_event_vehicle_hijack" }, { 0x40097, "flavor_event_aircraft_hijack" }, { 0x40098, "flavor_event_deadplayer_kill" }, { 0x40099, "flavor_event_player_kill_spreeplayer" }, { 0x4009a, "flavor_event_spartanlaser_kill" }, { 0x4009b, "flavor_event_stickygrenade_kill" }, { 0x4009c, "flavor_event_sniper_kill" }, { 0x4009d, "flavor_event_bashbehind_kill" }, { 0x4009e, "flavor_event_bash_kill" }, { 0x4009f, "flavor_event_flame_kill" }, { 0x400a0, "flavor_event_driver_assist_gunner" }, { 0x400a1, "flavor_event_assault_bomb_planted" }, { 0x400a2, "flavor_event_assault_player_kill_carrier" }, { 0x400a3, "flavor_event_vip_player_kill_vip" }, { 0x400a4, "flavor_event_juggernaut_player_kill_juggernaut" }, { 0x400a5, "flavor_event_oddball_carrier_kill_player" }, { 0x400a6, "flavor_event_ctf_flag_captured" }, { 0x400a7, "flavor_event_ctf_flag_player_kill_carrier" }, { 0x400a8, "flavor_event_ctf_flag_carrier_kill_player" }, { 0x400a9, "flavor_event_infection_survive" }, { 0x400aa, "flavor_event_nemesis" }, { 0x400ab, "flavor_event_avenger" }, { 0x400ac, "flavor_forge_cannot_place_object" }, { 0x400ad, "flavor_forge_theoretical_object_limit_reached" }, { 0x400ae, "slayer_event_game_start" }, { 0x400af, "slayer_event_new_target" }, { 0x400b0, "ctf_event_game_start" }, { 0x400b1, "ctf_event_flag_taken" }, { 0x400b2, "ctf_event_flag_grabbed_from_stand" }, { 0x400b3, "ctf_event_flag_dropped" }, { 0x400b4, "ctf_event_flag_returned_by_player" }, { 0x400b5, "ctf_event_flag_returned_by_timeout" }, { 0x400b6, "ctf_event_flag_captured" }, { 0x400b7, "ctf_event_flag_new_defensive_team" }, { 0x400be, "ctf_event_flag_capture_faliure" }, { 0x400bf, "oddball_event_game_start" }, { 0x400c0, "oddball_event_ball_spawned" }, { 0x400c1, "oddball_event_ball_picked_up" }, { 0x400c2, "oddball_event_ball_dropped" }, { 0x400c3, "oddball_event_ball_reset" }, { 0x400c5, "oddball_event_10_points_remaining" }, { 0x400c6, "oddball_event_25_points_remaining" }, { 0x400c8, "king_event_game_start" }, { 0x400c9, "king_event_hill_controlled" }, { 0x400ca, "king_event_hill_contested" }, { 0x400cc, "king_event_hill_move" }, { 0x400cd, "king_event_hill_controlled_team" }, { 0x400ce, "king_event_hill_contested_team" }, { 0x400cf, "vip_event_game_start" }, { 0x400d0, "vip_event_new_vip" }, { 0x400d1, "vip_event_vip_killed" }, { 0x400d2, "vip_event_vip_died" }, { 0x400d3, "vip_event_side_switch" }, { 0x400d4, "vip_event_reached_destination_area" }, { 0x400d5, "vip_event_destination_area_moved" }, { 0x400d6, "juggernaut_event_game_start" }, { 0x400d7, "juggernaut_event_new_juggernaut" }, { 0x400d8, "juggernaut_event_zone_moved" }, { 0x400d9, "juggernaut_event_player_kill_juggernaut" }, { 0x400da, "territories_event_game_start" }, { 0x400db, "territories_event_territory_captured" }, { 0x400de, "territories_event_side_switch" }, { 0x400df, "assault_event_game_start" }, { 0x400e0, "assault_event_bomb_taken" }, { 0x400e1, "assault_event_bomb_dropped" }, { 0x400e2, "assault_event_bomb_returned_by_player" }, { 0x400e3, "assault_event_bomb_returned_by_timeout" }, { 0x400e4, "assault_event_bomb_captured" }, { 0x400eb, "assault_event_bomb_disarmed" }, { 0x400ec, "assault_event_bomb_placed_on_enemy_post" }, { 0x400f0, "assault_event_neutral_bomb_returned" }, { 0x400f1, "assault_event_last_player_on_team" }, { 0x400f2, "infection_event_game_start" }, { 0x400f3, "infection_event_new_infection" }, { 0x400f4, "infection_event_zombie_spawn" }, { 0x400f5, "infection_event_alpha_zombie_spawn" }, { 0x400f6, "infection_event_survive" } }; // 0x1247ECA0
}
using namespace hades_file_local;
/* ---------- public code */

namespace Web
{
	namespace Ui
	{
		namespace MpEventDispatcher
		{
			void Init() // 0x10C8A6A0
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?Init@MpEventDispatcher@Ui@Web@@YAXXZ");

				Patches::Events::OnEvent(::OnEvent);
			}
		}
	}
}

/* ---------- private code */

static void OnEvent(unsigned long player, s_game_engine_event_data const *event, s_multiplayer_event_response_definition const *definition) // 0x10C8A700
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?OnEvent@@YAXKPBUs_game_engine_event_data@@PBUs_multiplayer_event_response_definition@@@Z");

	unsigned __int32 (*GetLocalPlayer)(__int32) = reinterpret_cast<unsigned __int32 (*)(__int32)>(0x589C30);
	if (player != GetLocalPlayer(0))
		return;
	rapidjson::StringBuffer jsonBuffer;
	rapidjson::Writer<rapidjson::StringBuffer> jsonWriter(jsonBuffer);
	jsonWriter.StartObject();
	std::string eventName = GetEventName(event->name);
	jsonWriter.Key("name");
	jsonWriter.String(eventName.c_str());
	jsonWriter.Key("category");
	jsonWriter.Int((char)event->type);
	jsonWriter.Key("audience");
	jsonWriter.Int((short)definition->audience);
	jsonWriter.EndObject();
	Web::Ui::ScreenLayer::Notify("mpevent", jsonBuffer.GetString(), true);
}

std::string GetEventName(unsigned __int32 stringId) // 0x10C8A3E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetEventName@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@I@Z");

	// Try to find the stringID in the event names list
	std::string name;
	auto it = EventNames.find(stringId);
	if (it != EventNames.end())
		return it->second;

	// If it wasn't found, then just convert it to a hex number
	std::ostringstream ss;
	ss << "0x" << std::hex << stringId;
	return ss.str();
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template c_enum<enum e_game_engine_event_audience,short>::operator short() const;
template c_enum<enum e_game_engine_event_type,char>::operator char() const;
