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
		_extern void _sub_1090DC40();
		void ApplyAll() // 0x1090DC40
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@campaign_patches@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_1090DC40();
		}

		_extern void _sub_1090F9E0();
		void fixup_campaign_metagame_flags() // 0x1090F9E0
		{
			mangled_x86(MANGLED_TODO, "?fixup_campaign_metagame_flags@campaign_patches@Patches@@YAXXZ");
			// procedure flags: nofpo
			// unsigned long flags;
			todo("implement");
			_sub_1090F9E0();
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

		_extern void _sub_1090EE60(unsigned long);
		void assassin_skull_hook(unsigned long unit_index) // 0x1090EE60
		{
			mangled_x86(MANGLED_TODO, "?assassin_skull_hook@campaign_patches@Patches@@YAXK@Z");
			// static ...; // 0x1090EFE8
			// static ...; // 0x1090EFDC
			// static ...; // 0x1090EFD4
			// unsigned long unit_index;
			// bool (*const game_team_is_enemy)(long, long);
			// void (*const unit_camo_update)(unsigned long);
			// unsigned long secondary_skulls;
			{
				// s_unit_data *player_unit_object;
				// long player_unit_index;
				// s_unit_data *unit_object;
			}
			// function call : unsigned long *(*const)(unsigned long *)
			// function call : bool (*)()
			// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
			// function call : unsigned long (*const)(long)
			// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
			// function call : bool (*const)(long, long)
			// function call : void (*const)(unsigned long)
			todo("implement");
			_sub_1090EE60(unit_index);
		}

		_extern void _sub_1090F8E0();
		void cinematic_start_hook() // 0x1090F8E0
		{
			mangled_x86(MANGLED_TODO, "?cinematic_start_hook@campaign_patches@Patches@@YAXXZ");
			// procedure flags: nofpo
			// void (*const cinematic_start)();
			// function call : void (*const)()
			// function call : void (*const)(float)
			todo("implement");
			_sub_1090F8E0();
		}

		_extern void _sub_1090F960();
		void cinematic_stop_hook() // 0x1090F960
		{
			mangled_x86(MANGLED_TODO, "?cinematic_stop_hook@campaign_patches@Patches@@YAXXZ");
			// procedure flags: nofpo
			// void (*const scripted_camera_set_cinematic)();
			// function call : void (*const)()
			// function call : void (*const)(float)
			todo("implement");
			_sub_1090F960();
		}

		_extern long _sub_1090F500(long, long, long);
		long cinematic_scripting_get_scene_object_hook(long cinematic_index, long scene_index, long index) // 0x1090F500
		{
			mangled_x86(MANGLED_TODO, "?cinematic_scripting_get_scene_object_hook@campaign_patches@Patches@@YAJJJJ@Z");
			// static ...; // 0x1090F7F0
			// long cinematic_index;
			// long scene_index;
			// long index;
			// long (*const cinematic_object_from_string)(char const *);
			// s_cinematic_scene_definition *scene;
			// long (*const object_index_from_name_index)(short);
			// short (*const scenario_object_name_index_from_string)(s_scenario *, char const *);
			// s_cinematic_scene_object *scene_object;
			{
				// char const *player_names[4];
				{
					// __int32 i;
					{
						// s_player_datum *player;
					}
				}
			}
			{
				// long name_index;
			}
			// function call : s_cinematic_scene_definition *(*const)(long, long)
			// function call : bool (*const)(long)
			// function call : bool (*const)()
			// function call : bool (*const)()
			// function call : short (*const)(s_scenario *, char const *)
			// function call : long (*const)(short)
			// function call : long (*const)(char const *)
			todo("implement");
			long __result = _sub_1090F500(cinematic_index, scene_index, index);
			return __result;
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

		_extern bool _sub_1090EBC0(long);
		bool actor_general_update_hook(long actor_index) // 0x1090EBC0
		{
			mangled_x86(MANGLED_TODO, "?actor_general_update_hook@campaign_patches@Patches@@YA_NJ@Z");
			// long actor_index;
			// void (*const actor_erase)(long, bool);
			// bool (*const actor_runtime_within_structure_bsp)(long);
			// long (*const object_get_root_object)(long);
			// s_actor_datum *actor;
			// bool result;
			// bool (*const actor_set_active)(long, bool);
			// void (*const dynamic_firing_set_discard)(long);
			{
				// long parent_index;
			}
			// function call : void (*const)(long, bool)
			// function call : long (*const)(float)
			// function call : bool (*const)(long)
			// function call : bool (*const)(long, e_action)
			// function call : bool (*const)(long, bool)
			// function call : long (*const)(long)
			todo("implement");
			bool __result = _sub_1090EBC0(actor_index);
			return __result;
		}

		_extern void _sub_1090F180(long);
		void cinematic_clips_initialize_for_shot(long shot_index) // 0x1090F180
		{
			mangled_x86(MANGLED_TODO, "?cinematic_clips_initialize_for_shot@campaign_patches@Patches@@YAXJ@Z");
			// long shot_index;
			// tls_data const &tls_data;
			// unsigned long (*const cinematic_scene_get_puppet_object_handle)(long);
			// void (*const cinematic_clips_destroy)();
			{
				// s_cinematic_scene_definition *const cinematic_scene;
				{
					// s_cinematic_scene_shot *const shot_definition;
					{
						// long game_time;
						{
							// __int32 i;
							{
								// s_cinematic_shot_clip *const clip_definition;
								// s_cinematic_new_globals::s_cinematic_clip *clip;
								// float tick_scale;
								{
									// __int32 j;
									{
										// long puppet_index;
										{
											// unsigned long puppet_datum_index;
											{
												// s_object_data *object_data;
											}
										}
									}
								}
							}
						}
					}
				}
			}
			// function call : void (*const)()
			// function call : void *(*const)(unsigned long, long)
			// function call : long (*const)()
			// function call : long (*const)()
			// function call : unsigned long (*const)(long)
			todo("implement");
			_sub_1090F180(shot_index);
		}

		void main_save_map_hook() // 0x1090FC60
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?main_save_map_hook@campaign_patches@Patches@@YAXXZ");
			// procedure flags: nofpo
			// void (*const main_save_map)();
			// function call : void (*const)()

			if (!Utils::Singleton<Modules::ModuleCampaign>::Instance().VarCheckpointsDisabled->ValueInt)
			{
				((void(__cdecl *)())0x506d80)();
			}
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
