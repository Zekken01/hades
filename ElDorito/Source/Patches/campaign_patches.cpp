/* ---------- headers */

#include "hades/hades.h"

#include "Blam/ai/actor.hpp"
#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/cutscene/cinematic_definitions.hpp"
#include "Blam/cutscene/cinematics.hpp"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/data_array.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/networking/session/network_session.hpp"
#include "Blam/networking/session/network_session_membership.hpp"
#include "Blam/networking/session/network_session_parameters_base.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/damage_definitions.hpp"
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
#include "Blam/units/units.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Pointer.hpp"
#include "Utils/Singleton.hpp"

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
#include <istream>
#include <iterator>
#include <limits>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <streambuf>
#include <system_error>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

struct s_actor_datum;
struct s_cinematic_new_globals;
struct s_cinematic_scene_definition;
struct s_cinematic_scene_object;
struct s_cinematic_scene_shot;
struct s_cinematic_shot_clip;
struct s_object_data;
struct s_player_datum;
struct s_scenario;
struct s_unit_data;
struct tls_data;

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;
namespace Debug {}
using namespace ::Debug;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace campaign_patches {}
	using namespace Patches::campaign_patches;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace eldorado
{
	// Functions in eldorado.exe, named as in ManagedDonkey.
	static auto const action_executing = reinterpret_cast<bool (*)(long, long)>(0xB69BA0);
	static auto const cinematic_get_debug_mode = reinterpret_cast<bool (*)()>(0x67CF90);
	static auto const get_scene_from_cinematic_or_cortana_effect = reinterpret_cast<s_cinematic_scene_definition *(*)(long, long)>(0x9EC9C0);
	static auto const player_mapping_get_unit_by_output_user = reinterpret_cast<unsigned long (*)(long)>(0x589CC0);
}
#line 106

namespace Debug { extern void AssertHandle(char const *filename, char const *funcName, __int32 lineNum, char const *expr, char const *msg, ...); }  // hades: added for 0x1090F500

extern void *(*const tag_get)(unsigned long, long);  // hades: added for 0x1090F180
extern long (*const game_tick_rate)();  // hades: added for 0x1090F180

extern s_object_data *(*const object_try_and_get_and_verify_type)(unsigned long, c_enum<enum e_object_type,long>);  // hades: added for 0x1090EE60

extern s_actor_datum *actor_get(long index);  // hades: added for 0x1090EBC0
extern long (*const game_seconds_to_ticks_round)(float);  // hades: added for 0x1090EBC0
extern s_object_data *object_get(unsigned long object_index);  // hades: added for 0x1090EBC0

#include "Blam/game/campaign/campaign_metagame.hpp"  // hades: added for 0x1090F9E0
extern s_campaign_metagame_runtime_globals **g_campaign_metagame;  // hades: added for 0x1090F9E0

#include "Modules/ModuleCampaign.hpp"  // hades: added for 0x1090FC60

extern long (__cdecl *const game_time_get)();  // hades: added for 0X1090FA30

extern long (*campaign_metagame_globals_initialize_for_new_map)();  // hades: added for 0X1090F060

extern long (*game_get_current_engine)();  // hades: added for 0X1090F0E0
extern bool (*game_is_campaign)();  // hades: added for 0X1090F0E0
extern long *(*survival_mode_get_scoreboard)();  // hades: added for 0X1090F0E0
void *tls_get(unsigned long index);  // hades: added for 0X1090F0E0

namespace Patches
{
	namespace campaign_patches
	{
		extern void ApplyAll();
		extern void fixup_campaign_metagame_flags();
		extern long campaign_metagame_globals_initialize_for_new_map_patch();
		extern long *campaign_scoreboard_patch();
		extern void assassin_skull_hook(unsigned long unit_index);
		extern void cinematic_start_hook();
		extern void cinematic_stop_hook();
		extern long cinematic_scripting_get_scene_object_hook(long cinematic_index, long scene_index, long index);
		extern bool game_reverted_hook();
		extern bool actor_general_update_hook(long actor_index);
		extern void cinematic_clips_initialize_for_shot(long shot_index);
		extern void main_save_map_hook();
	}
}

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Patches
{
	namespace campaign_patches
	{
		void ApplyAll() // 0x1090DC40
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAll@campaign_patches@Patches@@YAXXZ");
			// procedure flags: nofpo

			Hook(0x207DD1, campaign_metagame_globals_initialize_for_new_map_patch, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x150B80, campaign_scoreboard_patch).Apply();
			Pointer(0x1656108).Write<unsigned long>(reinterpret_cast<unsigned long>(campaign_metagame_globals_initialize_for_new_map_patch));
			Patch(0x207E00, { 0xC3 }).Apply();
			Patch(0x208090, { 0xC3 }).Apply();
			Patch(0x208710, { 0xC3 }).Apply();
			Patch(0x208940, { 0xC3 }).Apply();
			Hook(0x749FB4, assassin_skull_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x348033, cinematic_start_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x27EAA4, cinematic_stop_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x5EC100, cinematic_scripting_get_scene_object_hook).Apply();
			Hook(0x110530, game_reverted_hook).Apply();
			Hook(0x102A480, actor_general_update_hook).Apply();
			Hook(0x27C7A0, cinematic_clips_initialize_for_shot).Apply();
			Hook(0x2826BE, main_save_map_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
		}

		void fixup_campaign_metagame_flags() // 0x1090F9E0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?fixup_campaign_metagame_flags@campaign_patches@Patches@@YAXXZ");
			// procedure flags: nofpo
			// unsigned long flags;

			unsigned long flags = (*g_campaign_metagame)->dword_flags;
			(*g_campaign_metagame)->dword_flags &= ~0x10;
		}

		long campaign_metagame_globals_initialize_for_new_map_patch() // 0x1090F060
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?campaign_metagame_globals_initialize_for_new_map_patch@campaign_patches@Patches@@YAJXZ");
			// procedure flags: nofpo
			// long result;
			// function call : long (*)()
			// function call : bool (*)()

			long result = campaign_metagame_globals_initialize_for_new_map();
			if (game_is_campaign())
				Patches::campaign_patches::fixup_campaign_metagame_flags();
			return result;
		}

		long *campaign_scoreboard_patch() // 0x1090F0E0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?campaign_scoreboard_patch@campaign_patches@Patches@@YAPAJXZ");
			// procedure flags: nofpo
			// function call : long (*)()
			// function call : bool (*)()
			// function call : long *(*)()

			if (game_get_current_engine())
			{
				return (long *)(*(long *)tls_get(0x48) + 0xFEB0);
			}
			if (game_is_campaign())
			{
				return survival_mode_get_scoreboard();
			}
			return nullptr;
		}

		void assassin_skull_hook(unsigned long unit_index) // 0x1090EE60
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?assassin_skull_hook@campaign_patches@Patches@@YAXK@Z");
			// static ...; // 0x1090EFE8
			// static ...; // 0x1090EFDC
			// static ...; // 0x1090EFD4
			// unsigned long unit_index;
			// bool (*const game_team_is_enemy)(long, long);
			// void (*const unit_camo_update)(unsigned long);
			// unsigned long secondary_skulls;
				// s_unit_data *player_unit_object;
				// long player_unit_index;
				// s_unit_data *unit_object;
			// function call : unsigned long *(*const)(unsigned long *)
			// function call : bool (*)()
			// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
			// function call : unsigned long (*const)(long)
			// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
			// function call : bool (*const)(long, long)
			// function call : void (*const)(unsigned long)

			void (*const unit_camo_update)(unsigned long) = (void (*)(unsigned long))0xB4A020;
			bool (*const game_team_is_enemy)(long, long) = (bool (*)(long, long))0x670B80;
			unsigned long secondary_skulls = 0;
			((unsigned long *(*const)(unsigned long *))0x434FB0)(&secondary_skulls);
			if (game_is_campaign() && (secondary_skulls & 1))
			{
				s_unit_data *unit_object = (s_unit_data *)object_try_and_get_and_verify_type(unit_index, 1);
				long player_unit_index = eldorado::player_mapping_get_unit_by_output_user(0);
				s_unit_data *player_unit_object = (s_unit_data *)object_try_and_get_and_verify_type(player_unit_index, 0x2003);
				if (unit_object)
				{
					if (player_unit_object && game_team_is_enemy(player_unit_object->team, unit_object->team))
						unit_object->unit_flags |= 8;
				}
			}
			unit_camo_update(unit_index);
		}

		void cinematic_start_hook() // 0x1090F8E0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?cinematic_start_hook@campaign_patches@Patches@@YAXXZ");
			// procedure flags: nofpo
			// void (*const cinematic_start)();
			// function call : void (*const)()
			// function call : void (*const)(float)

			const auto cinematic_start = (void(*)())0x67E990;

			cinematic_start();
			((void(*)(float))0x565110)(1.0f);
		}

		void cinematic_stop_hook() // 0x1090F960
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?cinematic_stop_hook@campaign_patches@Patches@@YAXXZ");
			// procedure flags: nofpo
			// void (*const scripted_camera_set_cinematic)();
			// function call : void (*const)()
			// function call : void (*const)(float)

			const auto cinematic_stop = (void(*)())0x72D920;

			cinematic_stop();
			((void(*)(float))0x565110)(1.0f);
		}

		long cinematic_scripting_get_scene_object_hook(long cinematic_index, long scene_index, long index) // 0x1090F500
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?cinematic_scripting_get_scene_object_hook@campaign_patches@Patches@@YAJJJJ@Z");
			// static ...; // 0x1090F7F0
			// long cinematic_index;
			// long scene_index;
			// long index;
			// long (*const cinematic_object_from_string)(char const *);
			// s_cinematic_scene_definition *scene;
			// long (*const object_index_from_name_index)(short);
			// short (*const scenario_object_name_index_from_string)(s_scenario *, char const *);
			// s_cinematic_scene_object *scene_object;
				// char const *player_names[4];
					// __int32 i;
						// s_player_datum *player;
				// long name_index;
			// function call : s_cinematic_scene_definition *(*const)(long, long)
			// function call : bool (*const)(long)
			// function call : bool (*const)()
			// function call : bool (*const)()
			// function call : short (*const)(s_scenario *, char const *)
			// function call : long (*const)(short)
			// function call : long (*const)(char const *)

			long (*const cinematic_object_from_string)(char const *) = reinterpret_cast<long (*)(char const *)>(0x67DAB0);
			short (*const scenario_object_name_index_from_string)(s_scenario *, char const *) = reinterpret_cast<short (*)(s_scenario *, char const *)>(0x4EB080);
			long (*const object_index_from_name_index)(short) = reinterpret_cast<long (*)(short)>(0xB2F0A0);
			s_cinematic_scene_definition *scene = eldorado::get_scene_from_cinematic_or_cortana_effect(cinematic_index, scene_index);
			if (!scene || (cinematic_index != -1 && cinematic_index <= 1000 && !((bool (*const)(long))0x4E9580)(cinematic_index)))
				return -1;
			s_cinematic_scene_object *scene_object = scene->objects.get_element(index);
			#line 304 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\campaign_patches.cpp"
			if (!scene_object) Debug::AssertHandle(__FILE__, __FUNCTION__, __LINE__, "scene_object", "scene object index out of range. cinematic_index: %d, scene_index: %d, object_index: %d", cinematic_index, scene_index, index);
			#line 327 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\campaign_patches.cpp"
			if ((scene_object->flags & _cinematic_object_special_case_like_player0) && !eldorado::cinematic_get_debug_mode())
			{
				char const *player_names[4] = { "player0", "player1", "player2", "player3" };
				for (__int32 i = 0; i < _countof(player_names); i++)
				{
					if (strcmp(scene_object->import_name, player_names[i]) == 0)
					{
						s_player_datum *player = players_get()->try_and_get_absolute(i);
						if (player)
							return player->unit_index;
						else
							return -1;
					}
				}
			}
			if (((scene_object->flags & _cinematic_object_comes_from_game) || (scene_object->flags & _cinematic_object_placed_manually_in_sapien)) && !eldorado::cinematic_get_debug_mode())
			{
				long name_index = scenario_object_name_index_from_string(global_scenario_get(), scene_object->import_name);
				if (name_index != -1)
					return object_index_from_name_index((short)name_index);
				else
					return -1;
			}
			return cinematic_object_from_string(scene_object->import_name);
		}

		bool game_reverted_hook() // 0x1090FA30
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?game_reverted_hook@campaign_patches@Patches@@YA_NXZ");
			// procedure flags: nofpo
			// __int32 game_state_revert_time;
			// function call : long (*const)()
			// function call : long (*const)()
			// function call : long (*const)()

			int game_state_revert_time = *(int *)0x238db14;
			if (game_state_revert_time != -1 && (game_state_revert_time == game_time_get() - 1 || game_state_revert_time == game_time_get() + 1))
			{
				return true;
			}
			return game_state_revert_time == game_time_get();
		}

		bool actor_general_update_hook(long actor_index) // 0x1090EBC0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?actor_general_update_hook@campaign_patches@Patches@@YA_NJ@Z");
			// long actor_index;
			// void (*const actor_erase)(long, bool);
			// bool (*const actor_runtime_within_structure_bsp)(long);
			// long (*const object_get_root_object)(long);
			// s_actor_datum *actor;
			// bool result;
			// bool (*const actor_set_active)(long, bool);
			// void (*const dynamic_firing_set_discard)(long);
				// long parent_index;
			// function call : void (*const)(long, bool)
			// function call : long (*const)(float)
			// function call : bool (*const)(long)
			// function call : bool (*const)(long, e_action)
			// function call : bool (*const)(long, bool)
			// function call : long (*const)(long)

			void (*const actor_erase)(long, bool) = (void (*)(long, bool))0x1429DF0;
			bool (*const actor_runtime_within_structure_bsp)(long) = (bool (*)(long))0x142E1A0;
			void (*const dynamic_firing_set_discard)(long) = (void (*)(long))0x14A5390;
			long (*const object_get_root_object)(long) = (long (*)(long))0xB2E8F0;
			bool (*const actor_set_active)(long, bool) = (bool (*)(long, bool))0x142E6E0;
			bool result = true;
			s_actor_datum *actor = actor_get(actor_index);
			if (actor->meta.is_swarm && actor->meta.swarm_index == -1)
				actor_erase(actor_index, false);
			else
				actor->control[110] = 0;
			if (actor->meta.min_trackable_weight > 0.0)
				actor->meta.min_trackable_weight *= 0.99f;
			if (++actor->meta.outside_map_ticks >= game_seconds_to_ticks_round(0.5f))
			{
				if (actor_runtime_within_structure_bsp(actor_index) || actor->meta.unit_index != -1 && eldorado::action_executing(actor->meta.unit_index, 7))
					actor->meta.outside_map_ticks = 0;
				else
				{
					actor_set_active(actor_index, false);
					result = false;
				}
			}
			if (!global_scenario_get()->flags.test(_scenario_flags_h3_compat_bit) && actor->meta.unit_index != -1)
			{
				long parent_index = object_get(actor->meta.unit_index)->parent_object_index;
				if (parent_index != -1)
				{
					if (object_get(object_get_root_object(parent_index))->parent_object_index != -1)
						result = false;
				}
			}
			actor->meta.unknown_flag3 = result;
			return result;
		}

		void cinematic_clips_initialize_for_shot(long shot_index) // 0x1090F180
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?cinematic_clips_initialize_for_shot@campaign_patches@Patches@@YAXJ@Z");
			// long shot_index;
			// tls_data const &tls_data;
			// unsigned long (*const cinematic_scene_get_puppet_object_handle)(long);
			// void (*const cinematic_clips_destroy)();
				// s_cinematic_scene_definition *const cinematic_scene;
					// s_cinematic_scene_shot *const shot_definition;
						// long game_time;
							// __int32 i;
								// s_cinematic_shot_clip *const clip_definition;
								// s_cinematic_new_globals::s_cinematic_clip *clip;
								// float tick_scale;
									// __int32 j;
										// long puppet_index;
											// unsigned long puppet_datum_index;
												// s_object_data *object_data;
			// function call : void (*const)()
			// function call : void *(*const)(unsigned long, long)
			// function call : long (*const)()
			// function call : long (*const)()
			// function call : unsigned long (*const)(long)

			void (*const cinematic_clips_destroy)() = reinterpret_cast<void (*)()>(0x67C570);
			unsigned long (*const cinematic_scene_get_puppet_object_handle)(long) = reinterpret_cast<unsigned long (*)(long)>(0x67DBC0);
			cinematic_clips_destroy();
			tls_data const &tls_data = tls_getd();
			if (tls_data.cinematic_new_globals->scene_tag_index != -1)
			{
				s_cinematic_scene_definition *const cinematic_scene = (s_cinematic_scene_definition *)tag_get('cisc', tls_data.cinematic_new_globals->scene_tag_index);
				if (cinematic_scene)
				{
					if (shot_index >= 0 && shot_index < cinematic_scene->shots.count)
					{
						s_cinematic_scene_shot *const shot_definition = &cinematic_scene->shots[shot_index];
						if (shot_definition->clips.count > 0)
						{
							long game_time = game_time_get();
							for (__int32 i = 0; i < shot_definition->clips.count; i++)
							{
								s_cinematic_shot_clip *const clip_definition = &shot_definition->clips[i];
								s_cinematic_new_globals::s_cinematic_clip *clip = &tls_data.cinematic_new_globals->clips[i];
								float tick_scale = game_tick_rate() / 30.0f;
								clip->plane_center = clip_definition->plane_center;
								clip->plane_direction = clip_definition->plane_direction;
								clip->game_time_start = (long)(game_time + clip_definition->frame_start * tick_scale);
								clip->game_time_end = (long)(game_time + clip_definition->frame_end * tick_scale);
								clip->objects_count = clip_definition->puppet_indices.count;
								for (__int32 j = 0; j < clip_definition->puppet_indices.count; j++)
								{
									long puppet_index = clip_definition->puppet_indices[j];
									if (puppet_index != -1)
									{
										unsigned long puppet_datum_index = cinematic_scene_get_puppet_object_handle(puppet_index);
										if (puppet_datum_index != -1)
										{
											clip->object_indices[j] = puppet_datum_index;
											s_object_data *object_data = object_get(puppet_datum_index);
											object_data->object_flags |= 0x8000;
										}
									}
								}
							}
						}
						tls_data.cinematic_new_globals->active_clip_count = shot_definition->clips.count;
					}
				}
			}
		}

		void main_save_map_hook() // 0x1090FC60
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?main_save_map_hook@campaign_patches@Patches@@YAXXZ");
			// procedure flags: nofpo
			// void (*const main_save_map)();
			// function call : void (*const)()

			if (Utils::Singleton<Modules::ModuleCampaign>::Instance().VarCheckpointsDisabled->ValueInt)
			{
				return;
			}

			void (*const main_save_map)() = reinterpret_cast<void (*)()>(0x506D80);
			main_save_map();
		}
	}
}

/* ---------- private code */

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_flags<enum e_scenario_flags,unsigned short>::test(e_scenario_flags) const;
template bool c_tag_block<long>::try_get_element(__int32, long **) const;
template bool c_tag_block<s_cinematic_shot_clip>::try_get_element(__int32, s_cinematic_shot_clip **) const;
template c_flags<enum e_object_flags,long> & c_flags<enum e_object_flags,long>::operator|=(__int32 const);
template c_flags<enum e_unit_flags,unsigned long> & c_flags<enum e_unit_flags,unsigned long>::operator|=(__int32 const);
template long & c_tag_block<long>::operator[](__int32);
template long * c_tag_block<long>::get_element(__int32) const;
template s_cinematic_shot_clip & c_tag_block<s_cinematic_shot_clip>::operator[](__int32);
template s_cinematic_shot_clip * c_tag_block<s_cinematic_shot_clip>::get_element(__int32) const;
