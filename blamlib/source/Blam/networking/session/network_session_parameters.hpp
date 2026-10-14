#ifndef __BLAM_NETWORKING_SESSION_NETWORK_SESSION_PARAMETERS_HPP__
#define __BLAM_NETWORKING_SESSION_NETWORK_SESSION_PARAMETERS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/effects/screen_effect.hpp"
#include "Blam/game/campaign/campaign.hpp"
#include "Blam/networking/session/network_session.hpp"
#include "Blam/networking/session/network_session_parameter_saved_film.hpp"
#include "Blam/networking/session/network_session_parameters_base.hpp"
#include "Blam/networking/session/network_session_parameters_game.hpp"
#include "Blam/networking/session/network_session_parameters_game_variant.hpp"
#include "Blam/networking/session/network_session_parameters_generic.hpp"
#include "Blam/networking/session/network_session_parameters_map_variant.hpp"
#include "Blam/networking/session/network_session_parameters_matchmaking.hpp"
#include "Blam/networking/session/network_session_parameters_session.hpp"
#include "Blam/networking/session/network_session_parameters_ui.hpp"
#include "Blam/networking/session/network_session_parameters_voice.hpp"
#include "Common/Http/HttpHeaders.hpp"

/* ---------- forward declarations */

class c_network_session;
class c_network_session_parameter_base;
class c_network_session_parameter_countdown_timer;
class c_network_session_parameter_game_start_status;
class c_network_session_parameter_game_variant;
class c_network_session_parameter_initial_participants;
class c_network_session_parameter_leader_properties;
class c_network_session_parameter_lobby_vote_set;
class c_network_session_parameter_map;
class c_network_session_parameter_map_variant;
class c_network_session_parameter_matchmaking_game_list;
class c_network_session_parameter_matchmaking_hopper;
class c_network_session_parameter_matchmaking_hopper_list;
class c_network_session_parameter_matchmaking_hopper_statistics;
class c_network_session_parameter_matchmaking_messaging;
class c_network_session_parameter_matchmaking_progress;
class c_network_session_parameter_matchmaking_progress_search_criteria;
class c_network_session_parameter_matchmaking_rematch_data;
class c_network_session_parameter_remote_join_data;
class c_network_session_parameter_request_campaign_quit;
class c_network_session_parameter_requested_remote_join_data;
class c_network_session_parameter_saved_film_game_options;
class c_network_session_parameter_session_mode;
class c_network_session_parameter_session_size;
class c_network_session_parameter_synchronous_out_of_sync;
class c_network_session_parameter_ui_game_mode;
class c_network_session_parameter_voice_repeater;
class c_network_session_parameters;
class c_network_observer;
struct s_network_session_privacy_mode;
struct s_saved_film_description;

/* ---------- constants */

/* ---------- definitions */

class c_network_session_parameters
{
public:
	c_network_session_parameter_session_mode session_mode; // 0x0
	c_network_session_parameter_session_size session_size; // 0x48
	c_generic_network_session_parameter<s_network_session_privacy_mode> privacy_mode; // 0x88
	c_network_session_parameter_ui_game_mode ui_game_mode; // 0xD8
	c_generic_network_session_parameter<long> dedicated_server_session_state; // 0x110
	c_network_session_parameter_map map; // 0x148
	c_network_session_parameter_initial_participants initial_participants; // 0x578
	c_generic_network_session_parameter<unsigned __int64> game_instance; // 0x2D008
	c_generic_network_session_parameter<unsigned long> random_long; // 0x2D048
	c_generic_network_session_parameter<enum e_lanquage> lanquage; // 0x2D080
	c_generic_network_session_parameter<long> determinism_version; // 0x2D0B8
	c_generic_network_session_parameter<enum e_network_game_simulation_protocol> game_simulation_protocol; // 0x2D0F0
	c_generic_network_session_parameter<enum e_campaign_difficulty_level> campaign_difficulty; // 0x2D128
	c_generic_network_session_parameter<c_flags<enum e_campaign_skulls_primary,unsigned long> > campaign_active_skulls_primary; // 0x2D160
	c_generic_network_session_parameter<c_flags<enum e_campaign_skulls_secondary,unsigned long> > campaign_active_skulls_secondary; // 0x2D198
	c_generic_network_session_parameter<short> campaign_metagame_scoring; // 0x2D1D0
	c_generic_network_session_parameter<short> campaign_insertion_point; // 0x2D204
	c_generic_network_session_parameter<unsigned char> ui_state; // 0x2D238
	c_generic_network_session_parameter<bool> end_game_requested; // 0x2D26C
	c_generic_network_session_parameter<enum e_network_game_start_mode> start_mode; // 0x2D2A0
	c_network_session_parameter_game_variant game_variant; // 0x2D2D8
	c_network_session_parameter_map_variant map_variant; // 0x30848
	c_generic_network_session_parameter<s_saved_film_description> saved_film; // 0x5AA18
	c_network_session_parameter_saved_film_game_options saved_film_game_options; // 0x5B080
	c_network_session_parameter_game_start_status game_start_status; // 0xB57C0
	c_network_session_parameter_countdown_timer countdown_timer; // 0xB5808
	c_network_session_parameter_voice_repeater voice_repeater; // 0xB5848
	c_network_session_parameter_requested_remote_join_data requested_remote_join_data; // 0xB5880
	c_network_session_parameter_remote_join_data remote_join_data; // 0xB5960
	c_generic_network_session_parameter<unsigned __int64> matchmaking_arbitration_nonce; // 0xB5A40
	c_network_session_parameter_matchmaking_hopper_list matchmaking_hopper_list; // 0xB5A80
	c_network_session_parameter_matchmaking_game_list matchmaking_game_list; // 0xB67F8
	c_generic_network_session_parameter<short> matchmaking_requested_hopper; // 0xB6B88
	c_network_session_parameter_matchmaking_hopper matchmaking_hopper; // 0xB6BBC
	c_generic_network_session_parameter<bool> matchmaking_abort_requested; // 0xB6C84
	c_generic_network_session_parameter<enum e_matchmaking_search_preference> matchmaking_search_preference; // 0xB6CB8
	c_network_session_parameter_matchmaking_progress matchmaking_progress; // 0xB6CF0
	c_network_session_parameter_matchmaking_progress_search_criteria matchmaking_progress_search_criteria; // 0xB6D60
	c_generic_network_session_parameter<unsigned long> matchmaking_assembly_peer_evict_mask; // 0xB6DD8
	c_network_session_parameter_matchmaking_rematch_data matchmaking_rematch_data; // 0xB6E10
	c_network_session_parameter_matchmaking_hopper_statistics matchmaking_hopper_statistics; // 0xB75C8
	c_generic_network_session_parameter<long> matchmaking_tip; // 0xB7608
	c_generic_network_session_parameter<bool> matchmaking_supress_progress; // 0xB7640
	c_network_session_parameter_synchronous_out_of_sync synchronous_out_of_sync; // 0xB7674
	c_network_session_parameter_matchmaking_messaging matchmaking_messaging; // 0xB76A8
	c_generic_network_session_parameter<enum e_network_rough_qualit> host_frame_quality; // 0xB76F0
	c_network_session_parameter_request_campaign_quit request_campaign_quit; // 0xB7728
	c_network_session_parameter_leader_properties leader_properties; // 0xB7768
	c_network_session_parameter_lobby_vote_set lobby_vote_set; // 0xB7818
	c_network_session *session; // 0xB7858
	c_network_observer *observer; // 0xB785C
	c_network_session_parameter_base *parameters[49]; // 0xB7860
	unsigned long flags; // 0xB7924
	unsigned long initial_parameters_update_mask; // 0xB7928
	c_network_session_parameters(c_network_session_parameters &); /* compiler_generated() */
	c_network_session_parameters(c_network_session_parameters const &); /* compiler_generated() */
	c_network_session_parameters(); /* compiler_generated() */
	c_network_session_parameters &operator=(c_network_session_parameters &); /* compiler_generated() */
	c_network_session_parameters &operator=(c_network_session_parameters const &); /* compiler_generated() */
	// void __autoclassinit2(unsigned __int32); /* compiler_generated() */  // hades: /sdl generates it
};
static_assert(sizeof(c_network_session_parameters) == 751920, "Invalid c_network_session_parameters size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_NETWORKING_SESSION_NETWORK_SESSION_PARAMETERS_HPP__
