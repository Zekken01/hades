#ifndef __BLAM_MEMORY_TLS_HPP__
#define __BLAM_MEMORY_TLS_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/ai/actor.hpp"
#include "Blam/bink/bink.hpp"
#include "Blam/camera/director.hpp"
#include "Blam/camera/observer.hpp"
#include "Blam/camera/scripted_camera.hpp"
#include "Blam/cutscene/cinematics.hpp"
#include "Blam/devices/devices.hpp"
#include "Blam/effects/contrails.hpp"
#include "Blam/effects/effects.hpp"
#include "Blam/effects/particle.hpp"
#include "Blam/effects/particle_emitter.hpp"
#include "Blam/effects/particle_system.hpp"
#include "Blam/effects/screen_effect.hpp"
#include "Blam/game/engine/game_engine.hpp"
#include "Blam/game/game_engine_globals.hpp"
#include "Blam/game/game_globals.hpp"
#include "Blam/game/game_time.hpp"
#include "Blam/game/player_control.hpp"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/interface/chud/chud.hpp"
#include "Blam/interface/first_person_weapons.hpp"
#include "Blam/main/game_preferences.hpp"
#include "Blam/main/main_time.hpp"
#include "Blam/memory/data.hpp"
#include "Blam/objects/lights.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/physics/breakable_surfaces.hpp"
#include "Blam/rasterizer/rasterizer_game_states.hpp"
#include "Blam/render/camera_fx_settings.hpp"
#include "Blam/render/depth_of_field.hpp"
#include "Blam/render/render_object.hpp"
#include "Blam/render/render_object_globals.hpp"
#include "Blam/sounds/sound_memory.hpp"
#include "Blam/structures/structure_seams.hpp"
#include "Blam/vision_mode/vision_mode_globals.hpp"

/* ---------- forward declarations */

struct c_beam;
struct c_beam_location;
struct c_beam_system;
struct c_chud_persistent_global_data;
struct c_particle;
struct c_particle_emitter;
struct c_particle_emitter_gpu;
struct c_particle_emitter_gpu_row;
struct c_particle_system;
struct hs_distributed_global_data;
struct hs_runtime;
struct hs_thread_non_deterministic_data;
struct hs_thread_tracking_data;
struct s_actor_datum;
struct s_actor_firing_position;
struct s_ai_globals;
struct s_ai_player_state;
struct s_ai_reference_frame;
struct s_antenna;
struct s_atmosphere_fog_globals;
struct s_beam_gpu;
struct s_beam_gpu_row;
struct s_bink_gamestate;
struct s_breakable_surface_globals;
struct s_campaign_metagame;
struct s_campaign_objectives;
struct s_chud_shared_persistent_user_data;
struct s_cinematic_globals;
struct s_cinematic_light_globals;
struct s_cinematic_new_globals;
struct s_cloth;
struct s_clump;
struct s_contrail;
struct s_contrail_gpu;
struct s_contrail_gpu_row;
struct s_contrail_location;
struct s_contrail_profile;
struct s_contrail_system;
struct s_cortana_globals;
struct s_damage_globals;
struct s_data_array;
struct s_decal;
struct s_decal_counts;
struct s_decal_messaging_queue;
struct s_decal_system_datum;
struct s_depth_of_field;
struct s_deterministic_game_sound_globals;
struct s_device_group_datum;
struct s_director_globals;
struct s_director_scripting;
struct s_dynamic_firing_points;
struct s_effect_counts;
struct s_effect_datum;
struct s_effect_event_datum;
struct s_effect_geometry_sample;
struct s_effect_lightprobes;
struct s_effect_location_datum;
struct s_effect_messaging_queue;
struct s_first_person_orientation_globals;
struct s_first_person_weapon;
struct s_flocks;
struct s_formations;
struct s_game_allegiance_globals;
struct s_game_engine_globals;
struct s_game_globals;
struct s_game_looping_sound_datum;
struct s_game_save_globals;
struct s_game_sound_globals;
struct s_game_sound_player_effects_globals;
struct s_game_sound_scripted_impulses;
struct s_game_tick_time_samples;
struct s_game_time_globals;
struct s_global_preferences;
struct s_havok_gamestate;
struct s_hs_global_runtime;
struct s_hs_thread;
struct s_hue_saturation_control;
struct s_impact_arrays;
struct s_impact_globals;
struct s_impacts;
struct s_joint_state;
struct s_leaf_system;
struct s_light_datum;
struct s_light_volume;
struct s_light_volume_gpu;
struct s_light_volume_gpu_row;
struct s_light_volume_location;
struct s_light_volume_system;
struct s_lights_globals;
struct s_list_object;
struct s_local_game_engine_globals;
struct s_main_render_timing;
struct s_main_time_globals;
struct s_memory_pool;
struct s_nondeterministic_render_light_data;
struct s_object_activation_regions;
struct s_object_broadphase;
struct s_object_cached_render_state_datum;
struct s_object_early_movers;
struct s_object_globals;
struct s_object_header;
struct s_object_list_header;
struct s_object_messaging_queue;
struct s_object_placement;
struct s_object_render_data;
struct s_object_schedule_globals;
struct s_object_scripting;
struct s_objectives;
struct s_observer_gamestate;
struct s_observer_globals;
struct s_particle_location;
struct s_physics_constants;
struct s_player_control_globals;
struct s_player_control_globals_deterministic;
struct s_player_datum;
struct s_player_effect_globals;
struct s_player_mapping;
struct s_player_training_globals;
struct s_players_globals;
struct s_prop;
struct s_propref;
struct s_ragdolls;
struct s_random_math_globals;
struct s_rasterizer_game_states;
struct s_recorded_animations;
struct s_recycling_group;
struct s_recycling_volumes;
struct s_render_game_globals;
struct s_render_hud_globals;
struct s_render_object_globals;
struct s_render_texture_globals;
struct s_rumble_globals;
struct s_scenario_interpolator_globals;
struct s_scenario_kill_trigger_volume_state;
struct s_scenario_soft_surface_globals;
struct s_screen_effect_datum;
struct s_scripted_camera_globals;
struct s_scripted_exposure_globals;
struct s_shield_render_cache_message;
struct s_simulation_gamestate_entities;
struct s_sound_classes;
struct s_spawner_globals;
struct s_squad;
struct s_squad_group;
struct s_squad_patrol;
struct s_structure_seam_globals;
struct s_survival_mode_globals;
struct s_swarm;
struct s_swarm_spawner;
struct s_task_records;
struct s_tracking;
struct s_user_widget;
struct s_visibility_active_portals;
struct s_vision_mode_globals;
struct s_vocalization_records;
struct s_vocalization_timers;
struct s_water_interaction_ripples;
struct s_widget;
struct tls_data;

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
struct tls_data
{
	void *unknown1; // 0x0
	void *unknown2; // 0x4
	s_simulation_gamestate_entities *simulation_gamestate_entities; // 0x8
	s_game_tick_time_samples *main_gamestate_timing; // 0xC
	s_main_render_timing *main_render_timing; // 0x10
	s_main_time_globals *main_time_globals; // 0x14
	s_global_preferences *preferences; // 0x18
	void *unknown3; // 0x1C
	long current_thread_index; // 0x20
	void *unknown5; // 0x24
	void *unknown6; // 0x28
	void *unknown7; // 0x2C
	void *unknown8; // 0x30
	s_random_math_globals *random_math_globals; // 0x34
	void *unknown9; // 0x38
	s_game_globals *game_globals; // 0x3C
	c_data_array<s_player_datum> *players; // 0x40
	s_players_globals *players_globals; // 0x44
	s_game_engine_globals *game_engine_globals; // 0x48
	s_local_game_engine_globals *local_game_engine_globals; // 0x4C
	s_game_time_globals *game_time; // 0x50
	s_breakable_surface_globals *breakable_surface_globals; // 0x54
	s_data_array *breakable_surface_set_broken_event; // 0x58
	s_player_mapping *player_mapping; // 0x5C
	s_director_globals *director_globals; // 0x60
	s_director_scripting *director_scripting; // 0x64
	c_data_array<s_hs_thread> *hs_thread_deterministic_data; // 0x68
	hs_runtime *hs_runtime; // 0x6C
	c_data_array<s_hs_global_runtime> *hs_global_data; // 0x70
	hs_distributed_global_data *hs_distributed_global_data; // 0x74
	hs_thread_tracking_data *hs_thread_tracking_data; // 0x78
	hs_thread_non_deterministic_data *hs_thread_non_deterministic_data; // 0x7C
	void *unknown10; // 0x80
	void *unknown11; // 0x84
	void *unknown12; // 0x88
	void *unknown13; // 0x8C
	void *unknown14; // 0x90
	void *unknown15; // 0x94
	void *unknown16; // 0x98
	void *unknown17; // 0x9C
	c_data_array<s_effect_datum> *effect; // 0xA0
	c_data_array<s_effect_event_datum> *effect_event; // 0xA4
	c_data_array<s_effect_location_datum> *effect_location; // 0xA8
	s_effect_counts *effect_counts; // 0xAC
	s_effect_geometry_sample *effect_geometry_sample; // 0xB0
	s_effect_messaging_queue *effect_messaging_queue; // 0xB4
	s_effect_lightprobes *effect_lightprobes; // 0xB8
	s_havok_gamestate *havok_gamestate; // 0xBC
	void *unknown18; // 0xC0
	s_player_control_globals *player_control_globals; // 0xC4
	s_player_control_globals_deterministic *player_control_globals_deterministic; // 0xC8
	c_data_array<s_game_looping_sound_datum> *object_looping_sounds; // 0xCC
	s_game_sound_globals *game_sound_globals; // 0xD0
	s_game_sound_scripted_impulses *game_sound_scripted_impulses; // 0xD4
	s_structure_seam_globals *structure_seam_globals; // 0xD8
	s_visibility_active_portals *visibility_active_portals; // 0xDC
	s_campaign_metagame *campaign_metagame; // 0xE0
	s_observer_gamestate *observer_gamestate; // 0xE4
	s_observer_globals *observer_globals; // 0xE8
	s_rumble_globals *rumble_globals; // 0xEC
	s_bink_gamestate *bink_gamestate; // 0xF0
	void *unknown19; // 0xF4
	char *font_character; // 0xF8
	s_sound_classes *sound_classes; // 0xFC
	s_game_allegiance_globals *game_allegiance_globals; // 0x100
	s_atmosphere_fog_globals *atmosphere_fog_globals; // 0x104
	s_scenario_soft_surface_globals *scenario_soft_surface_globals; // 0x108
	s_game_sound_player_effects_globals *game_sound_player_effects_globals; // 0x10C
	char *havok_proxies; // 0x110
	void *unknown114[131]; // 0x114
	s_cinematic_new_globals *cinematic_new_globals; // 0x320
	s_cinematic_globals *cinematic_globals; // 0x324
	s_cinematic_light_globals *cinematic_light_globals; // 0x328
	s_physics_constants *physics_constants; // 0x32C
	s_recorded_animations *recorded_animations; // 0x330
	s_game_save_globals *game_save_globals; // 0x334
	c_data_array<s_screen_effect_datum> *screen_effects; // 0x338
	s_player_effect_globals *player_effect_globals; // 0x33C
	s_scenario_interpolator_globals *scenario_interpolator_globals; // 0x340
	s_survival_mode_globals *survival_mode_globals; // 0x344
	s_player_training_globals *player_training_globals; // 0x348
	s_scenario_kill_trigger_volume_state *scenario_kill_trigger_volume_state; // 0x34C
	s_deterministic_game_sound_globals *deterministic_game_sound_globals; // 0x350
	c_data_array<s_decal_system_datum> *decal_system; // 0x354
	s_decal_counts *decal_counts; // 0x358
	s_decal *decal; // 0x35C
	s_decal_messaging_queue *decal_messaging_queue; // 0x360
	s_impact_globals *impact_globals; // 0x364
	s_impacts *impacts; // 0x368
	s_impact_arrays *impact_arrays; // 0x36C
	s_object_list_header *object_list_header; // 0x370
	s_list_object *list_object; // 0x374
	s_scripted_camera_globals *scripted_camera_globals; // 0x378
	c_data_array<c_particle> *particles; // 0x37C
	c_data_array<c_particle_system> *particle_systems; // 0x380
	s_contrail_system *contrail_system; // 0x384
	s_contrail *contrail; // 0x388
	s_contrail_location *contrail_location; // 0x38C
	s_contrail_profile *contrail_profile; // 0x390
	s_particle_location *particle_location; // 0x394
	s_light_volume_system *light_volume_system; // 0x398
	s_light_volume_location *light_volume_location; // 0x39C
	s_light_volume *light_volume; // 0x3A0
	c_data_array<c_beam_system> *beam_system; // 0x3A4
	c_data_array<c_beam> *beam; // 0x3A8
	c_data_array<c_beam_location> *beam_location; // 0x3AC
	char *unknown3B0_render_postprocess_color_tweaking; // 0x3B0
	s_ragdolls *ragdolls; // 0x3B4
	c_particle_emitter *particle_emitter; // 0x3B8
	s_rasterizer_game_states *rasterizer_game_states; // 0x3BC
	s_hue_saturation_control *hue_saturation_control; // 0x3C0
	char *unknown3C4; // 0x3C4
	s_scripted_exposure_globals *scripted_exposure_globals; // 0x3C8
	s_render_hud_globals *render_hud_globals; // 0x3CC
	s_water_interaction_ripples *water_interaction_ripples; // 0x3D0
	s_render_texture_globals *render_texture_globals; // 0x3D4
	s_render_game_globals *render_game_globals; // 0x3D8
	s_depth_of_field *depth_of_field; // 0x3DC
	c_data_array<s_object_cached_render_state_datum> *cached_object_render_states; // 0x3E0
	c_data_array<c_particle_emitter_gpu_row> *particle_emitter_gpu_row; // 0x3E4
	c_data_array<c_particle_emitter_gpu> *particle_emitter_gpu; // 0x3E8
	char *particle_emitter_gpu_2; // 0x3EC
	s_beam_gpu *beam_gpu; // 0x3F0
	s_beam_gpu_row *beam_gpu_row; // 0x3F4
	char *particle_emitter_gpu_3; // 0x3F8
	s_contrail_gpu_row *contrail_gpu_row; // 0x3FC
	s_contrail_gpu *contrail_gpu; // 0x400
	char *particle_emitter_gpu_4; // 0x404
	s_light_volume_gpu *light_volume_gpu; // 0x408
	s_light_volume_gpu_row *light_volume_gpu_row; // 0x40C
	char *particle_emitter_gpu_5; // 0x410
	char *rasterizer_implicit_geometry_data; // 0x414
	s_render_object_globals *render_object_globals; // 0x418
	s_shield_render_cache_message *shield_render_cache_message; // 0x41C
	s_chud_shared_persistent_user_data *chud_persistent_user_data; // 0x420
	c_chud_persistent_global_data *chud_persistent_global_data; // 0x424
	s_user_widget *user_widget_0; // 0x428
	s_user_widget *user_widget_1; // 0x42C
	s_user_widget *user_widget_2; // 0x430
	s_user_widget *user_widget_3; // 0x434
	s_first_person_orientation_globals *first_person_orientation_globals; // 0x438
	s_first_person_weapon *first_person_weapons; // 0x43C
	s_cortana_globals *cortana_globals; // 0x440
	s_campaign_objectives *campaign_objectives; // 0x444
	c_data_array<s_object_header> *object_header; // 0x448
	s_object_globals *object_globals; // 0x44C
	s_memory_pool *objects_memory_pool; // 0x450
	long *object_name_list; // 0x454
	s_object_messaging_queue *object_messaging_queue; // 0x458
	char *collideable_object; // 0x45C
	s_damage_globals *damage_globals; // 0x460
	char *unknown464; // 0x464
	char *noncollideable_object; // 0x468
	char *unknown46C[2]; // 0x46C
	s_object_render_data *object_render_data; // 0x474
	char *damage; // 0x478
	s_object_placement *object_placement; // 0x47C
	c_data_array<s_device_group_datum> *device_groups; // 0x480
	s_object_scripting *object_scripting; // 0x484
	s_object_broadphase *object_broadphase; // 0x488
	s_object_early_movers *object_early_movers; // 0x48C
	s_object_schedule_globals *object_schedule_globals; // 0x490
	s_object_activation_regions *object_activation_regions; // 0x494
	c_data_array<s_light_datum> *lights; // 0x498
	s_lights_globals *lights_globals; // 0x49C
	char *light_data_reference; // 0x4A0
	char *light_cluster_reference; // 0x4A4
	char *light_first_data; // 0x4A8
	s_nondeterministic_render_light_data *nondeterministic_render_light_data; // 0x4AC
	s_widget *widget; // 0x4B0
	s_recycling_volumes *recycling_volumes; // 0x4B4
	s_recycling_group *recycling_group; // 0x4B8
	s_data_array *muffin; // 0x4BC
	s_leaf_system *leaf_system; // 0x4C0
	s_antenna *antenna; // 0x4C4
	s_cloth *cloth; // 0x4C8
	char *unknown4CC[20]; // 0x4CC
	c_data_array<s_actor_datum> *actor; // 0x51C
	s_actor_firing_position *actor_firing_position; // 0x520
	s_ai_reference_frame *ai_reference_frame; // 0x524
	s_ai_globals *ai_globals; // 0x528
	s_ai_player_state *ai_player_state; // 0x52C
	s_vocalization_records *vocalization_records; // 0x530
	s_vocalization_timers *vocalization_timers; // 0x534
	s_data_array *command_scripts; // 0x538
	s_objectives *objectives; // 0x53C
	s_task_records *task_records; // 0x540
	s_squad *squad; // 0x544
	s_squad_group *squad_group; // 0x548
	s_swarm *swarm; // 0x54C
	s_swarm_spawner *swarm_spawner; // 0x550
	s_spawner_globals *spawner_globals; // 0x554
	s_dynamic_firing_points *dynamic_firing_points; // 0x558
	s_propref *propref; // 0x55C
	s_prop *prop; // 0x560
	s_tracking *tracking; // 0x564
	s_joint_state *joint_state; // 0x568
	s_clump *clump; // 0x56C
	s_squad_patrol *squad_patrol; // 0x570
	s_flocks *flocks; // 0x574
	s_formations *formations; // 0x578
	s_vision_mode_globals *vision_mode; // 0x57C
	char *unknown580; // 0x580
};
#pragma pack(pop)
static_assert(sizeof(tls_data) == 1412, "Invalid tls_data size");

/* ---------- prototypes */

extern void *tls_get(unsigned long const offset);

extern _inline tls_data &tls_getd();

/* ---------- globals */

/* ---------- public code */

inline tls_data &tls_getd() // 0x1067CE40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?tls_getd@@YAAAUtls_data@@XZ");

	return *(tls_data *)tls_get(0);
}

/* ---------- private code */

#endif // __BLAM_MEMORY_TLS_HPP__
