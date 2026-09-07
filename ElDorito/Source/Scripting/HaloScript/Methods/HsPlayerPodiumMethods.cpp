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
				_extern void _sub_10704B90(Scripting::HS::ScriptMethodMap &);
				void RegisterMethods(Scripting::HS::ScriptMethodMap &methods) // 0x10704B90
				{
					mangled_x86(MANGLED_TODO, "?RegisterMethods@PlayerPodium@Methods@HS@Scripting@@YAXAAVScriptMethodMap@34@@Z");
					// Scripting::HS::ScriptMethodMap &methods;
					todo("implement");
					_sub_10704B90(methods);
				}
			}
		}
	}
}

/* ---------- private code */

_extern void _sub_10705C60(short, long, bool);
void hs_podium_get_animation_graph_evaluate(short op, long thread_index, bool initial) // 0x10705C60
{
	// `anonymous-namespace'::hs_podium_get_animation_graph_evaluate
	// bool initial;
	{
		// hs_value *args;
		{
			// long animation_tag_index;
			// short idx;
		}
	}
	// function call : hs_value *(*const)(short, long, bool)
	// function call : void (*const)(long, hs_value)
	todo("implement");
	_sub_10705C60(op, thread_index, initial);
}

_extern void _sub_10705E40(short, long, bool);
void hs_podium_get_animation_string_evaluate(short op, long thread_index, bool initial) // 0x10705E40
{
	// `anonymous-namespace'::hs_podium_get_animation_string_evaluate
	// bool initial;
	{
		// hs_value *args;
		{
			// short idx;
			// unsigned long animation_string;
			// short type;
			// long animationIdx;
		}
	}
	// function call : hs_value *(*const)(short, long, bool)
	// function call : void (*const)(long, hs_value)
	todo("implement");
	_sub_10705E40(op, thread_index, initial);
}

_extern void _sub_10705B80(short, long, bool);
void hs_podium_get_animation_count_evaluate(short op, long thread_index, bool initial) // 0x10705B80
{
	// `anonymous-namespace'::hs_podium_get_animation_count_evaluate
	// bool initial;
	{
		// hs_value *args;
		{
			// short idx;
			// short animation_count;
		}
	}
	// function call : hs_value *(*const)(short, long, bool)
	// function call : void (*const)(long, hs_value)
	todo("implement");
	_sub_10705B80(op, thread_index, initial);
}

_extern void _sub_10705D40(short, long, bool);
void hs_podium_get_animation_offset_evaluate(short op, long thread_index, bool initial) // 0x10705D40
{
	// `anonymous-namespace'::hs_podium_get_animation_offset_evaluate
	// bool initial;
	{
		// hs_value *args;
		{
			// short idx;
			// float offset;
			// long animationIdx;
		}
	}
	// function call : hs_value *(*const)(short, long, bool)
	// function call : void (*const)(long, hs_value)
	todo("implement");
	_sub_10705D40(op, thread_index, initial);
}

_extern void _sub_10705F60(short, long, bool);
void hs_podium_get_animation_weapon_evaluate(short op, long thread_index, bool initial) // 0x10705F60
{
	// `anonymous-namespace'::hs_podium_get_animation_weapon_evaluate
	// bool initial;
	{
		// hs_value *args;
		{
			// long weapon_index;
			// bool primary;
			// short idx;
			// long animationIdx;
		}
	}
	// function call : hs_value *(*const)(short, long, bool)
	// function call : void (*const)(long, hs_value)
	todo("implement");
	_sub_10705F60(op, thread_index, initial);
}

_extern void _sub_107066E0(short, long, bool);
void hs_podium_show_ui_place_evaluate(short op, long thread_index, bool initial) // 0x107066E0
{
	// `anonymous-namespace'::hs_podium_show_ui_place_evaluate
	// bool initial;
	{
		// hs_value *args;
		{
			// short desired_place;
			// short extra_stats_player_index;
		}
	}
	// function call : hs_value *(*const)(short, long, bool)
	// function call : void (*const)(long, hs_value)
	todo("implement");
	_sub_107066E0(op, thread_index, initial);
}

_extern void _sub_10706510(short, long, bool);
void hs_podium_respawn_player_offset_evaluate(short op, long thread_index, bool initial) // 0x10706510
{
	// `anonymous-namespace'::hs_podium_respawn_player_offset_evaluate
	// bool initial;
	{
		// hs_value *args;
		{
			// float yaw_offset;
			// short camera;
			// float horizontal_offset;
			// short session_player_index;
			// float vertical_offset;
			// float distance_offset;
			// float pitch;
		}
	}
	// function call : hs_value *(*const)(short, long, bool)
	// function call : bool (*const)()
	// function call : void (*const)(long, hs_value)
	todo("implement");
	_sub_10706510(op, thread_index, initial);
}

_extern void _sub_107059E0(short, long, bool);
void hs_podium_event_evaluate(short op, long thread_index, bool initial) // 0x107059E0
{
	// `anonymous-namespace'::hs_podium_event_evaluate
	// bool initial;
	{
		// hs_value *args;
		{
			// char const *event;
		}
	}
	// function call : hs_value *(*const)(short, long, bool)
	// function call : void (*const)(long, hs_value)
	todo("implement");
	_sub_107059E0(op, thread_index, initial);
}

_extern void _sub_10706250(short, long, bool);
void hs_podium_get_respawn_effect_evaluate(short op, long thread_index, bool initial) // 0x10706250
{
	// `anonymous-namespace'::hs_podium_get_respawn_effect_evaluate
	// bool initial;
	{
		// hs_value *args;
		{
			// long effect;
			// short place;
		}
	}
	// function call : hs_value *(*const)(short, long, bool)
	// function call : void (*const)(long, hs_value)
	todo("implement");
	_sub_10706250(op, thread_index, initial);
}

_extern void _sub_10706070(short, long, bool);
void hs_podium_get_biped_offset_evaluate(short op, long thread_index, bool initial) // 0x10706070
{
	// `anonymous-namespace'::hs_podium_get_biped_offset_evaluate
	// bool initial;
	{
		// hs_value *args;
		{
			// short place;
			// char const *field_name;
			// float offset;
		}
	}
	// function call : hs_value *(*const)(short, long, bool)
	// function call : void (*const)(long, hs_value)
	todo("implement");
	_sub_10706070(op, thread_index, initial);
}

_extern void _sub_10706170(short, long, bool);
void hs_podium_get_biped_spawn_delay_evaluate(short op, long thread_index, bool initial) // 0x10706170
{
	// `anonymous-namespace'::hs_podium_get_biped_spawn_delay_evaluate
	// bool initial;
	{
		// hs_value *args;
		{
			// short biped_place_index;
			// long spawn_delay;
		}
	}
	// function call : hs_value *(*const)(short, long, bool)
	// function call : void (*const)(long, hs_value)
	todo("implement");
	_sub_10706170(op, thread_index, initial);
}

_extern void _sub_10706330(short, long, bool);
void hs_podium_get_tick_delay_evaluate(short op, long thread_index, bool initial) // 0x10706330
{
	// `anonymous-namespace'::hs_podium_get_tick_delay_evaluate
	// bool initial;
	{
		// hs_value *args;
		{
			// long tick_delay;
		}
	}
	// function call : hs_value *(*const)(short, long, bool)
	// function call : void (*const)(long, hs_value)
	todo("implement");
	_sub_10706330(op, thread_index, initial);
}

_extern void _sub_107063F0(short, long, bool);
void hs_podium_has_forge_object_evaluate(short op, long thread_index, bool initial) // 0x107063F0
{
	// `anonymous-namespace'::hs_podium_has_forge_object_evaluate
	// bool initial;
	{
		// hs_value *args;
		{
			// long s_PodiumObjectIndex;
			// bool hasObject;
			// s_object_data *scenObject;
		}
	}
	// function call : hs_value *(*const)(short, long, bool)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void (*const)(long, hs_value)
	todo("implement");
	_sub_107063F0(op, thread_index, initial);
}

_extern void _sub_10705AB0(short, long, bool);
void hs_podium_forge_point_overridable_evaluate(short op, long thread_index, bool initial) // 0x10705AB0
{
	// `anonymous-namespace'::hs_podium_forge_point_overridable_evaluate
	// bool initial;
	{
		// hs_value *args;
		{
			// bool allowed;
		}
	}
	// function call : hs_value *(*const)(short, long, bool)
	// function call : void (*const)(long, hs_value)
	todo("implement");
	_sub_10705AB0(op, thread_index, initial);
}
