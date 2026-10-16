/* ---------- headers */

#include "hades/hades.h"

#include "Blam/BlamNetwork.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/bitstream.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/objects/object_types.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Forge/Geoemetry.hpp"
#include "Scripting/HaloScript/HsMethodMap.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <wchar.h>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <initializer_list>
#include <limits>
#include <tuple>
#include <type_traits>
#include <utility>

/* ---------- forward declarations */

struct hs_value;
struct s_object_data;
namespace Scripting
{
	namespace HS
	{
		class ScriptMethodMap;
	}
}

namespace Utils {}
using namespace ::Utils;
namespace Player {}
using namespace ::Player;
namespace Player
{
	namespace PlayerPodium {}
	using namespace Player::PlayerPodium;
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

namespace Blam {}
using namespace ::Blam;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Player { namespace PlayerPodium { extern unsigned long GetPlayerAnimationString(short player_session_idx, short animationType, short animationIndex); } }  // hades: added for 0x10705E40

namespace Player { namespace PlayerPodium { extern float GetAnimationOffset(short player_session_idx, short animationIndex); } }  // hades: added for 0x10705D40

namespace Player { namespace PlayerPodium { extern long GetAnimationWeaponIndex(short player_session_idx, short animationIndex, bool isPrimary); } }  // hades: added for 0x10705F60

namespace Player { namespace PlayerPodium { extern void ShowPlace(short desiredPlace, short stats_player_session_idx); } }  // hades: added for 0x107066E0

namespace Player { namespace PlayerPodium { extern void RespawnPlayerOffset(short player_session_idx, short cutscene_camera_point_index, float distance_offset, float horizontal_offset, float vertical_offset, float yaw_offset, float pitch); } }  // hades: added for 0x10706510

namespace Player { namespace PlayerPodium { extern float GetPodiumBipedOffset(char const *offset_type, short place); } }  // hades: added for 0x10706070

extern s_object_data *(*const object_try_and_get_and_verify_type)(unsigned long object_index, c_enum<e_object_type, long> object_type_mask);  // hades: added for 0x107063F0
namespace Forge { namespace PodiumPoint { extern long FindPodiumObject(); } }  // hades: added for 0x107063F0

namespace Player
{
	namespace PlayerPodium
	{
		// hades: declared only in Player/PlayerPodium.cpp.
		extern long GetPlayerAnimationGraph(short);
		extern long GetPodiumBipedSpawnDelay(short);
		extern long GetPodiumRespawnEffectIndex(short);
		extern long GetPodiumTickDelay();
		extern short GetPlayerAnimationCount(short);
		extern void HandleEvent(char const *);
		extern void SetForgeCanOverride(bool);
	}
}

namespace Player
{
	namespace PlayerPodium
	{
		// hades: declared only in Player/PlayerPodium.cpp, and these evaluators
		// call them.
		extern short GetPlayerAnimationCount(short player_session_idx);
		extern long GetPlayerAnimationGraph(short player_session_idx);
		extern long GetPodiumBipedSpawnDelay(short biped_place_index);
		extern long GetPodiumRespawnEffectIndex(short place);
	}
}

namespace Scripting
{
	namespace HS
	{
		namespace Methods
		{
			namespace PlayerPodium
			{
				extern void RegisterMethods(Scripting::HS::ScriptMethodMap &methods);
			}
		}
	}
}

void hs_podium_get_animation_graph_evaluate(short op, long thread_index, bool initial);
void hs_podium_get_animation_string_evaluate(short op, long thread_index, bool initial);
void hs_podium_get_animation_count_evaluate(short op, long thread_index, bool initial);
void hs_podium_get_animation_offset_evaluate(short op, long thread_index, bool initial);
void hs_podium_get_animation_weapon_evaluate(short op, long thread_index, bool initial);
void hs_podium_show_ui_place_evaluate(short op, long thread_index, bool initial);
void hs_podium_respawn_player_offset_evaluate(short op, long thread_index, bool initial);
void hs_podium_event_evaluate(short op, long thread_index, bool initial);
void hs_podium_get_respawn_effect_evaluate(short op, long thread_index, bool initial);
void hs_podium_get_biped_offset_evaluate(short op, long thread_index, bool initial);
void hs_podium_get_biped_spawn_delay_evaluate(short op, long thread_index, bool initial);
void hs_podium_get_tick_delay_evaluate(short op, long thread_index, bool initial);
void hs_podium_has_forge_object_evaluate(short op, long thread_index, bool initial);
void hs_podium_forge_point_overridable_evaluate(short op, long thread_index, bool initial);

/* ---------- globals */

extern void ShowPlace(short desiredPlace, short stats_player_session_idx);
extern unsigned long GetPlayerAnimationString(short player_session_idx, short animationType, short animationIndex);
extern long GetAnimationWeaponIndex(short player_session_idx, short animationIndex, bool isPrimary);
extern float GetAnimationOffset(short player_session_idx, short animationIndex);
extern float GetPodiumBipedOffset(char const *offset_type, short place);

/* ---------- private variables */

/* ---------- public code */

namespace Scripting
{
	namespace HS
	{
		namespace Methods
		{
			namespace PlayerPodium
			{
				void RegisterMethods(Scripting::HS::ScriptMethodMap &methods) // 0x10704B90
				{
					mangled_x86(MANGLED_KNOWN_GOOD, "?RegisterMethods@PlayerPodium@Methods@HS@Scripting@@YAXAAVScriptMethodMap@34@@Z");

					methods.AddMethod("pdm_get_player_animation_tag", "gets a player podium animation jmad for the given player session index", NetworkSafe, hs_podium_get_animation_graph_evaluate, _hs_type_animation_graph, { { _hs_type_short, "idx", "the player session index" } });
					methods.AddMethod("pdm_get_player_animation_str", "gets a player podium animation string for the given player session index and animation index", NetworkSafe, hs_podium_get_animation_string_evaluate, _hs_type_string_id, { { _hs_type_short, "type", "the animation type index 0=in 1=loop 2=out" }, { _hs_type_short, "idx", "the player session index" }, { _hs_type_long, "animation_idx", "the podium animation index for the given player" } });
					methods.AddMethod("pdm_get_player_animation_count", "gets a player podium animation count for the given player session index and animation index", NetworkSafe, hs_podium_get_animation_count_evaluate, _hs_type_long, { { _hs_type_short, "idx", "the player session index" } });
					methods.AddMethod("pdm_get_animation_offset", "gets a podium animation offset for the given animation index and player index", NetworkSafe, hs_podium_get_animation_offset_evaluate, _hs_type_real, { { _hs_type_short, "idx", "the player session index" }, { _hs_type_long, "animation_idx", "the the podium animation index for the given player" } });
					methods.AddMethod("pdm_get_animation_weapon", "gets a podium animation weapon for the given animation index and player index", NetworkSafe, hs_podium_get_animation_weapon_evaluate, _hs_type_any_tag, { { _hs_type_short, "idx", "the player session index" }, { _hs_type_long, "animation_idx", "the the podium animation index for the given player" }, { _hs_type_boolean, "primary", "True = Primary Weapon; False = secondary Weapon" } });
					methods.AddMethod("pdm_show_ui_place", "Trigger the podium UI screen to show based on the given index", NetworkSafe, hs_podium_show_ui_place_evaluate, _hs_type_void, { { _hs_type_short, "place", "The desired place to show" }, { _hs_type_short, "extra_stats", "the player session index for the player whos stats will show on the right window" } });
					methods.AddMethod("pdm_respawn_player_offset", "Respawn the player at a given offset away from a cutscene camera position", HostOnly, hs_podium_respawn_player_offset_evaluate, _hs_type_void, { { _hs_type_short, "idx", "Player session index" }, { _hs_type_cutscene_camera_point, "camera", "cutscene camera point name" }, { _hs_type_real, "distance_offset", "The offset distance away from the camera" }, { _hs_type_real, "horizontal_offset", "Offset Distance Horizontally" }, { _hs_type_real, "vertical_offset", "Offset Distance Vertically" }, { _hs_type_real, "yaw_offset", "Offset yaw for the player to respawn facing" }, { _hs_type_real, "pitch", "Pitch for the player to be aiming at when respawned" } });
					methods.AddMethod("pdm_event", "Trigger a podium event by string", NetworkSafe, hs_podium_event_evaluate, _hs_type_void, { { _hs_type_string, "event", "The desired event to trigger" } });
					methods.AddMethod("pdm_get_respawn_effect", "gets a podium respawn effect for a biped index", NetworkSafe, hs_podium_get_respawn_effect_evaluate, _hs_type_effect, { { _hs_type_short, "biped_index", "the index of the biped in podium_settings to grab the offset for" } });
					methods.AddMethod("pdm_get_biped_offset", "gets a podium settings field value biped index", NetworkSafe, hs_podium_get_biped_offset_evaluate, _hs_type_real, { { _hs_type_string, "offset_type", "The type of offset to grab \"x\" \"y\" \"z\" \"i\" \"j\" \"k\" in podium_settings global tag for the biped index" }, { _hs_type_short, "biped_index", "the index of the biped in podium_settings to grab the offset for" } });
					methods.AddMethod("pdm_get_biped_spawn_delay", "gets the number of ticks to delay a biped spawning", NetworkSafe, hs_podium_get_biped_spawn_delay_evaluate, _hs_type_long, { { _hs_type_short, "biped_index", "the index of the biped in podium_settings to grab the offset for" } });
					methods.AddMethod("pdm_get_tick_delay", "gets the number of ticks before the podium should start", NetworkSafe, hs_podium_get_tick_delay_evaluate, _hs_type_long, {});
					methods.AddMethod("pdm_has_forge_object", "returns true if the current forged map variant has a podium point placed on it", NetworkSafe, hs_podium_has_forge_object_evaluate, _hs_type_boolean, {});
					methods.AddMethod("pdm_forge_override_allowed", "sets whether forge placed podium point can override the pdm_respawn_player_offset script and camera_set script with " "a camera using the podium hack flag ", NetworkSafe, hs_podium_forge_point_overridable_evaluate, _hs_type_void, { { _hs_type_boolean, "allowed", "Sets whether forge placed podium objects can override this matches podium" } });
				}
			}
		}
	}
}

/* ---------- private code */

void hs_podium_get_animation_graph_evaluate(short op, long thread_index, bool initial) // 0x10705C60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_podium_get_animation_graph_evaluate@@YAXFJ_N@Z");

	hs_value *args = ((hs_value *(__cdecl *)(short, long, bool))0x5972F0)(op, thread_index, initial);
	if (args)
	{
		short input = args[0].short_value;
		auto result = Player::PlayerPodium::GetPlayerAnimationGraph(input);
		((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value::from_long(result));
	}
}

void hs_podium_get_animation_string_evaluate(short op, long thread_index, bool initial) // 0x10705E40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_podium_get_animation_string_evaluate@@YAXFJ_N@Z");

	hs_value *args = ((hs_value *(__cdecl *)(short, long, bool))0x5972F0)(op, thread_index, initial);
	if (args)
	{
		short idx = args[0].short_value;
		short type = args[1].short_value;
		long animationIdx = args[2].long_value;
		unsigned long animation_string = Player::PlayerPodium::GetPlayerAnimationString(type, idx, animationIdx);
		((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value::from_long(animation_string));
	}
}

void hs_podium_get_animation_count_evaluate(short op, long thread_index, bool initial) // 0x10705B80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_podium_get_animation_count_evaluate@@YAXFJ_N@Z");

	hs_value *args = ((hs_value *(__cdecl *)(short, long, bool))0x5972F0)(op, thread_index, initial);
	if (args)
	{
		short input = args[0].short_value;
		auto result = Player::PlayerPodium::GetPlayerAnimationCount(input);
		((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value::from_long(result));
	}
}

void hs_podium_get_animation_offset_evaluate(short op, long thread_index, bool initial) // 0x10705D40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_podium_get_animation_offset_evaluate@@YAXFJ_N@Z");

	hs_value *args = ((hs_value *(__cdecl *)(short, long, bool))0x5972F0)(op, thread_index, initial);
	if (args)
	{
		short idx = args[0].short_value;
		long animationIdx = args[1].long_value;
		float offset = Player::PlayerPodium::GetAnimationOffset(idx, animationIdx);
		((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value::from_real(offset));
	}
}

void hs_podium_get_animation_weapon_evaluate(short op, long thread_index, bool initial) // 0x10705F60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_podium_get_animation_weapon_evaluate@@YAXFJ_N@Z");

	hs_value *args = ((hs_value *(__cdecl *)(short, long, bool))0x5972F0)(op, thread_index, initial);
	if (args)
	{
		short idx = args[0].short_value;
		long animationIdx = args[1].long_value;
		bool primary = args[2].bool_value;
		long weapon_index = Player::PlayerPodium::GetAnimationWeaponIndex(idx, animationIdx, primary);
		((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value::from_long(weapon_index));
	}
}

void hs_podium_show_ui_place_evaluate(short op, long thread_index, bool initial) // 0x107066E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_podium_show_ui_place_evaluate@@YAXFJ_N@Z");

	hs_value *args = ((hs_value *(__cdecl *)(short, long, bool))0x5972F0)(op, thread_index, initial);
	if (args)
	{
		short desired_place = args[0].short_value;
		short extra_stats_player_index = args[1].short_value;
		Player::PlayerPodium::ShowPlace(desired_place, extra_stats_player_index);
		((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value{});
	}
}

void hs_podium_respawn_player_offset_evaluate(short op, long thread_index, bool initial) // 0x10706510
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_podium_respawn_player_offset_evaluate@@YAXFJ_N@Z");

	hs_value *args = ((hs_value *(__cdecl *)(short, long, bool))0x5972F0)(op, thread_index, initial);
	if (args)
	{
		short session_player_index = args[0].short_value;
		short camera = args[1].short_value;
		float horizontal_offset = args[2].real_value;
		float vertical_offset = args[3].real_value;
		float distance_offset = args[4].real_value;
		float yaw_offset = args[5].real_value;
		float pitch = args[6].real_value;
		if (((bool(__cdecl *)())0x5319C0)())
		{
			Player::PlayerPodium::RespawnPlayerOffset(session_player_index, camera, horizontal_offset, vertical_offset, distance_offset, yaw_offset, pitch);
		}
		((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value{});
	}
}

void hs_podium_event_evaluate(short op, long thread_index, bool initial) // 0x107059E0
{

	hs_value *args = ((hs_value *(__cdecl *)(short, long, bool))0x5972F0)(op, thread_index, initial);
	if (args)
	{
		auto input = args[0].string_value;
		Player::PlayerPodium::HandleEvent(input);
		((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value{});
	}
}

void hs_podium_get_respawn_effect_evaluate(short op, long thread_index, bool initial) // 0x10706250
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_podium_get_respawn_effect_evaluate@@YAXFJ_N@Z");

	hs_value *args = ((hs_value *(__cdecl *)(short, long, bool))0x5972F0)(op, thread_index, initial);
	if (args)
	{
		short input = args[0].short_value;
		auto result = Player::PlayerPodium::GetPodiumRespawnEffectIndex(input);
		((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value::from_long(result));
	}
}

void hs_podium_get_biped_offset_evaluate(short op, long thread_index, bool initial) // 0x10706070
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_podium_get_biped_offset_evaluate@@YAXFJ_N@Z");

	hs_value *args = ((hs_value *(__cdecl *)(short, long, bool))0x5972F0)(op, thread_index, initial);
	if (args)
	{
		char const *field_name = args[0].string_value;
		short place = args[1].short_value;
		float offset = Player::PlayerPodium::GetPodiumBipedOffset(field_name, place);
		((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value::from_real(offset));
	}
}

void hs_podium_get_biped_spawn_delay_evaluate(short op, long thread_index, bool initial) // 0x10706170
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_podium_get_biped_spawn_delay_evaluate@@YAXFJ_N@Z");

	hs_value *args = ((hs_value *(__cdecl *)(short, long, bool))0x5972F0)(op, thread_index, initial);
	if (args)
	{
		short input = args[0].short_value;
		auto result = Player::PlayerPodium::GetPodiumBipedSpawnDelay(input);
		((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value::from_long(result));
	}
}

void hs_podium_get_tick_delay_evaluate(short op, long thread_index, bool initial) // 0x10706330
{

	hs_value *args = ((hs_value *(__cdecl *)(short, long, bool))0x5972F0)(op, thread_index, initial);
	if (args)
	{
		auto result = Player::PlayerPodium::GetPodiumTickDelay();
		((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value::from_long(result));
	}
}

void hs_podium_has_forge_object_evaluate(short op, long thread_index, bool initial) // 0x107063F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_podium_has_forge_object_evaluate@@YAXFJ_N@Z");

	hs_value *args = ((hs_value *(__cdecl *)(short, long, bool))0x5972F0)(op, thread_index, initial);
	if (args)
	{
		long s_PodiumObjectIndex = Forge::PodiumPoint::FindPodiumObject();
		s_object_data *scenObject = object_try_and_get_and_verify_type(s_PodiumObjectIndex, 0x80);
		bool hasObject = false;
		if (s_PodiumObjectIndex != -1 && scenObject)
		{
			hasObject = true;
		}
		((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value::from_bool(hasObject));
	}
}

void hs_podium_forge_point_overridable_evaluate(short op, long thread_index, bool initial) // 0x10705AB0
{

	hs_value *args = ((hs_value *(__cdecl *)(short, long, bool))0x5972F0)(op, thread_index, initial);
	if (args)
	{
		auto input = args[0].bool_value;
		Player::PlayerPodium::SetForgeCanOverride(input);
		((void(__cdecl *)(long, hs_value))0x5974E0)(thread_index, hs_value{});
	}
}
