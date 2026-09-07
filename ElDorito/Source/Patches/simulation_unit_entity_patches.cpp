/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/color_definitions.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/bitstream.hpp"
#include "Blam/memory/data.hpp"
#include "Blam/memory/static_array.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/multiplayer_game_objects.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/scenario/scenario_definitions.hpp"
#include "Blam/simulation/simulation_entity_definition.hpp"
#include "Blam/simulation/simulation_game_objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_block_index.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "Blam/units/units.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Player/PlayerCharacterSystem.hpp"
#include "Pointer.hpp"

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

/* ---------- forward declarations */

class c_bitstream;
struct real_point3d;
struct real_rectangle3d;
struct real_rgb_color;
struct s_damage_owner;
struct s_data_array;
struct s_object_placement_data;
struct s_player_datum;
struct s_player_model_customization;
struct s_simulation_object_creation_data;
struct s_simulation_object_state_data;
struct s_simulation_unit_creation_data;
struct s_simulation_unit_state_data;
struct s_unit_data;
struct tls_data;

namespace Player {}
using namespace ::Player;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Simulation {}
	using namespace Patches::Simulation;
}

/* ---------- constants */

/* ---------- definitions */

namespace hades_file_local
{
	// s_simulation_view_telemetry_data is defined in hades/recovered_types.h, which the synthesised
}
using namespace hades_file_local;
// templates in hades/recovered_templates.h inherit from.

/* ---------- prototypes */

namespace Patches
{
	namespace Simulation
	{
		extern void apply_unit_entity_patches();
	}
}

void c_simulation_unit_entity_definition__build_object_creation_data_hook(void *thisptr, void *__formal, long unit_index, long creation_data_size, s_simulation_unit_creation_data *creation_data);
long c_simulation_unit_entity_definition__create_object_hook(void *thisptr, void *__formal, long creation_data_size, s_simulation_unit_creation_data *creation_data, unsigned long long *flags, long state_data_size, s_simulation_unit_state_data *state_data);
void c_simulation_unit_entity_definition__entity_creation_encode_hook(void *thisptr, void *__formal, long creation_data_size, s_simulation_unit_creation_data *creation_data, s_simulation_view_telemetry_data *telemetry_data, c_bitstream *bitstream, bool unknown);
bool c_simulation_unit_entity_definition__entity_creation_decode_hook(void *thisptr, void *__formal, long creation_data_size, s_simulation_unit_creation_data *data, c_bitstream *bitstream, bool a4);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Patches
{
	namespace Simulation
	{
		_extern void _sub_106D6F20();
		void apply_unit_entity_patches() // 0x106D6F20
		{
			mangled_x86(MANGLED_TODO, "?apply_unit_entity_patches@Simulation@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_106D6F20();
		}
	}
}

/* ---------- private code */

_extern void _sub_106D71E0(void *, void *, long, long, s_simulation_unit_creation_data *);
void c_simulation_unit_entity_definition__build_object_creation_data_hook(void *thisptr, void *__formal, long unit_index, long creation_data_size, s_simulation_unit_creation_data *creation_data) // 0x106D71E0
{
	// `anonymous-namespace'::c_simulation_unit_entity_definition__build_object_creation_data_hook
	// s_simulation_unit_creation_data *creation_data;
	// s_unit_data *unit;
	// long controlling_player_index;
	// long (*const unit_get_last_associated_weak_player_index_for_appearance)(long);
	// void (*const c_simulation_object_entity_definition__object_build_creation_data)(long, s_simulation_object_creation_data *);
	{
		// s_player_datum *player;
	}
	// function call : void (*const)(long, s_simulation_object_creation_data *)
	// function call : long (*const)(long)
	todo("implement");
	_sub_106D71E0(thisptr, __formal, unit_index, creation_data_size, creation_data);
}

_extern long _sub_106D7380(void *, void *, long, s_simulation_unit_creation_data *, unsigned long long *, long, s_simulation_unit_state_data *);
long c_simulation_unit_entity_definition__create_object_hook(void *thisptr, void *__formal, long creation_data_size, s_simulation_unit_creation_data *creation_data, unsigned long long *flags, long state_data_size, s_simulation_unit_state_data *state_data) // 0x106D7380
{
	// `anonymous-namespace'::c_simulation_unit_entity_definition__create_object_hook
	// void *__formal;
	// long creation_data_size;
	// s_simulation_unit_creation_data *creation_data;
	// unsigned long long *flags;
	// long state_data_size;
	// s_simulation_unit_state_data *state_data;
	// real_rgb_color colors[5];
	// long player_index;
	// long object_index;
	// tls_data *tls;
	// s_object_placement_data placement_data;
	// bool custom_change_colors;
	// void (*const Armor_Apply)(void *, long);
	{
		// s_unit_data *unit;
		// s_player_datum *player;
		// long hologram_definition_index;
		{
			// long player_unit_index;
			{
				// long equipment_index;
			}
		}
	}
	// function call : void *(*const)(unsigned long, long)
	// function call : void (*const)(s_object_placement_data *, long, unsigned long, s_damage_owner *)
	// function call : bool (*const)(s_simulation_object_creation_data *, s_simulation_object_state_data *, unsigned long long *, s_object_placement_data *)
	// function call : void *(*const)(s_data_array const *, unsigned long)
	// function call : long (*const)(long)
	// function call : void (*const)(long, s_player_model_customization const *, long, real_rgb_color *, bool *)
	// function call : long (*const)(void *, s_simulation_object_creation_data *, s_simulation_object_state_data *, unsigned long long *, s_object_placement_data *)
	// function call : void (*const)(long)
	// function call : long (*const)(long)
	// function call : void (*const)(long, long, long, real_point3d const *)
	// function call : long (*const)(long, e_equipment_type)
	// function call : void (*const)(long, long)
	// function call : void (*const)(long, long)
	// function call : void (*const)(void *, long)
	todo("implement");
	long __result = _sub_106D7380(thisptr, __formal, creation_data_size, creation_data, flags, state_data_size, state_data);
	return __result;
}

_extern void _sub_106D7BB0(void *, void *, long, s_simulation_unit_creation_data *, s_simulation_view_telemetry_data *, c_bitstream *, bool);
void c_simulation_unit_entity_definition__entity_creation_encode_hook(void *thisptr, void *__formal, long creation_data_size, s_simulation_unit_creation_data *creation_data, s_simulation_view_telemetry_data *telemetry_data, c_bitstream *bitstream, bool unknown) // 0x106D7BB0
{
	// `anonymous-namespace'::c_simulation_unit_entity_definition__entity_creation_encode_hook
	// bool unknown;
	{
		// long i;
	}
	{
	}
	// function call : void (*const)(s_simulation_object_creation_data *, c_bitstream *, long)
	// function call : void (*const)(char const *, c_bitstream *, long)
	// function call : void (*const)(c_bitstream *, real_point3d const *, long, bool, real_rectangle3d const *)
	// function call : void (*const)(c_bitstream *, char const *, long)
	todo("implement");
	_sub_106D7BB0(thisptr, __formal, creation_data_size, creation_data, telemetry_data, bitstream, unknown);
}

_extern bool _sub_106D7980(void *, void *, long, s_simulation_unit_creation_data *, c_bitstream *, bool);
bool c_simulation_unit_entity_definition__entity_creation_decode_hook(void *thisptr, void *__formal, long creation_data_size, s_simulation_unit_creation_data *data, c_bitstream *bitstream, bool a4) // 0x106D7980
{
	// `anonymous-namespace'::c_simulation_unit_entity_definition__entity_creation_decode_hook
	// bool a4;
	// bool success;
	{
		// long i;
	}
	{
	}
	{
		// long controlling_player_index;
	}
	// function call : bool (*const)(s_simulation_object_creation_data *, c_bitstream *)
	// function call : long (*const)(char const *, c_bitstream *)
	// function call : void (*const)(c_bitstream *, real_point3d *, long, real_rectangle3d const *)
	todo("implement");
	bool __result = _sub_106D7980(thisptr, __formal, creation_data_size, data, bitstream, a4);
	return __result;
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template c_enum<enum e_multiplayer_object_placement_spawn_flags,unsigned char> & c_enum<enum e_multiplayer_object_placement_spawn_flags,unsigned char>::operator=(unsigned char const &);
template c_flags<enum e_game_engine_flags,unsigned short> & c_flags<enum e_game_engine_flags,unsigned short>::operator=(unsigned short const &);
template c_flags<enum e_unit_flags,unsigned long>::operator unsigned long() const;
template real_rgb_color * s_static_array<real_rgb_color,5>::begin() const;
template void Pointer::Write<unsigned int>(unsigned __int32 const) const;
