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
#include "Blam/items/items.hpp"
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

namespace eldorado
{
	// Functions in eldorado.exe, named from the game's own symbols where it has them.
	static auto const unit_copy_armor_customization = reinterpret_cast<void (*)(long, long)>(0xB3E470);  // no symbol; named from what it does
	static auto const unit_get_active_equipment_of_type = reinterpret_cast<long (*)(long, e_equipment_type)>(0xB43C70);  // no symbol; named from what it does
}

namespace eldorado
{
	// Functions in eldorado.exe, named from the game's own symbols.
	static auto const c_simulation_object_entity_definition_object_create_object = reinterpret_cast<long (__thiscall *)(void *, s_simulation_object_creation_data *, s_simulation_object_state_data *, unsigned long long *, s_object_placement_data *)>(0x4AD3E0);
	static auto const c_simulation_object_entity_definition_object_setup_placement_data = reinterpret_cast<bool (*)(s_simulation_object_creation_data *, s_simulation_object_state_data *, unsigned long long *, s_object_placement_data *)>(0x4AE280);
	static auto const game_engine_get_change_colors = reinterpret_cast<void (*)(long, s_player_model_customization const *, long, real_rgb_color *, bool *)>(0x54F250);
	static auto const player_try_and_get_player_index_from_absolute_player_index = reinterpret_cast<long (*)(long)>(0x53FF70);
	static auto const tag_try_and_get_unsafe = reinterpret_cast<void *(*)(unsigned long, long)>(0x503510);
	static auto const unit_delete_all_weapons = reinterpret_cast<void (*)(long)>(0xB3FAD0);
	static auto const unit_set_hologram = reinterpret_cast<void (*)(long, long, long, real_point3d const *)>(0xB48770);
}

namespace eldorado
{
	// Functions in eldorado.exe, named as in ManagedDonkey.
	static auto const player_index_from_absolute_player_index = reinterpret_cast<long (*)(long)>(0x53B1A0);
}

#include "Player/PlayerCustomization.hpp"  // hades: added for 0x106D71E0
extern void (*const object_placement_data_new)(s_object_placement_data *, long, unsigned long, s_damage_owner *);  // hades: added for 0x106D7380
extern void *(*const datum_try_and_get_absolute)(s_data_array const *, unsigned long);  // hades: added for 0x106D7380
extern void (*const player_refresh_object_appearance_full)(long, long);  // hades: added for 0x106D7380
template<typename t_arg0> static t_arg0 *object_get(unsigned long object_index) { return (t_arg0 *)object_get(object_index); }  // hades: a file-local template in the original (undecorated `object_get<T>`), defined so it is emitted;  // hades: added for 0x106D71E0

namespace Patches
{
	namespace Simulation
	{
		extern void apply_unit_entity_patches();
	}
}

void __fastcall c_simulation_unit_entity_definition__build_object_creation_data_hook(void *thisptr, void *__formal, long unit_index, long creation_data_size, s_simulation_unit_creation_data *creation_data);
long __fastcall c_simulation_unit_entity_definition__create_object_hook(void *thisptr, void *__formal, long creation_data_size, s_simulation_unit_creation_data *creation_data, unsigned long long *flags, long state_data_size, s_simulation_unit_state_data *state_data);
void __fastcall c_simulation_unit_entity_definition__entity_creation_encode_hook(void *thisptr, void *__formal, long creation_data_size, s_simulation_unit_creation_data *creation_data, s_simulation_view_telemetry_data *telemetry_data, c_bitstream *bitstream, bool unknown);
bool __fastcall c_simulation_unit_entity_definition__entity_creation_decode_hook(void *thisptr, void *__formal, long creation_data_size, s_simulation_unit_creation_data *data, c_bitstream *bitstream, bool a4);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Patches
{
	namespace Simulation
	{
		void apply_unit_entity_patches() // 0x106D6F20
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?apply_unit_entity_patches@Simulation@Patches@@YAXXZ");

			Pointer(0x1640FA8).Write(c_simulation_unit_entity_definition__build_object_creation_data_hook);
			Pointer(0x1640FB4).Write(c_simulation_unit_entity_definition__create_object_hook);
			Pointer(0x1640F68).Write(c_simulation_unit_entity_definition__entity_creation_encode_hook);
			Pointer(0x1640F6C).Write(c_simulation_unit_entity_definition__entity_creation_decode_hook);
			Pointer(0x4BE5A1).Write<unsigned int>(0x50);
		}
	}
}

/* ---------- private code */

void __fastcall c_simulation_unit_entity_definition__build_object_creation_data_hook(void *thisptr, void *__formal, long unit_index, long creation_data_size, s_simulation_unit_creation_data *creation_data) // 0x106D71E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_simulation_unit_entity_definition__build_object_creation_data_hook@@YIXPAX0JJPAUs_simulation_unit_creation_data@@@Z");

	long (*const unit_get_last_associated_weak_player_index_for_appearance)(long) = reinterpret_cast<long (*)(long)>(0xB44340);
	void (*const c_simulation_object_entity_definition__object_build_creation_data)(long, s_simulation_object_creation_data *) = reinterpret_cast<void (*)(long, s_simulation_object_creation_data *)>(0x4AD200);
	memset(creation_data, 0, sizeof(s_simulation_unit_creation_data));
	c_simulation_object_entity_definition__object_build_creation_data(unit_index, creation_data);
	s_unit_data *unit = object_get<s_unit_data>(unit_index);
	if (unit->player_index != -1)
	{
		s_player_datum *player = player_get(unit->player_index);
		creation_data->player_appearance = *Player::CPlayerCustomization::GetInGamePlayerCustomization(unit->player_index);
	}
	creation_data->variant_name = object_get_variant_name(unit_index);
	creation_data->team = unit->team;
	creation_data->hologram_definition_index = unit->hologram_definition_index;
	creation_data->hologram_position = unit->hologram_destination;
	creation_data->controlling_player_index = -1;
	long controlling_player_index = unit_get_last_associated_weak_player_index_for_appearance(unit_index);
	if (controlling_player_index != -1)
		creation_data->controlling_player_index = (unsigned short)controlling_player_index;
}

long __fastcall c_simulation_unit_entity_definition__create_object_hook(void *thisptr, void *__formal, long creation_data_size, s_simulation_unit_creation_data *creation_data, unsigned long long *flags, long state_data_size, s_simulation_unit_state_data *state_data) // 0x106D7380
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_simulation_unit_entity_definition__create_object_hook@@YIJPAX0JPAUs_simulation_unit_creation_data@@PA_KJPAUs_simulation_unit_state_data@@@Z");

	void (*const Armor_Apply)(void *, long) = (void (*)(void *, long))0x5A4430;
	tls_data *tls = &tls_getd();
	s_object_placement_data placement_data;
	placement_data.multiplayer_properties.engine_flags = (unsigned short)0;
	placement_data.multiplayer_properties.spawn_flags = (unsigned char)0;
	if (creation_data->object_definition_index == -1 || !eldorado::tag_try_and_get_unsafe('unit', creation_data->object_definition_index))
		return -1;
	object_placement_data_new(&placement_data, creation_data->object_definition_index, -1, nullptr);
	eldorado::c_simulation_object_entity_definition_object_setup_placement_data(creation_data, state_data, flags, &placement_data);
	long player_index = -1;
	if (state_data->controlling_player_index != -1 && datum_try_and_get_absolute(tls_getd().players, state_data->controlling_player_index))
		player_index = eldorado::player_index_from_absolute_player_index(state_data->controlling_player_index);
	real_rgb_color colors[5];
	bool custom_change_colors;
	eldorado::game_engine_get_change_colors(player_index, &creation_data->player_appearance, creation_data->team, colors, &custom_change_colors);
	if (custom_change_colors)
	{
		placement_data.valid_change_colors |= 0x1F;
		memcpy(placement_data.change_colors.begin(), colors, sizeof(colors));
	}
	placement_data.variant_name = creation_data->variant_name;
	long object_index = eldorado::c_simulation_object_entity_definition_object_create_object(thisptr, creation_data, state_data, flags, &placement_data);
	if (object_index == -1)
		return object_index;
	if (!object_get_type(object_index))
	{
		eldorado::unit_delete_all_weapons(object_index);
		s_unit_data *unit = object_get<s_unit_data>(object_index);
		if (unit->player_index == -1)
			unit->team = creation_data->team;
		player_index = eldorado::player_try_and_get_player_index_from_absolute_player_index(creation_data->controlling_player_index);
		s_player_datum *player = player_get(player_index);
		long hologram_definition_index = creation_data->hologram_definition_index;
		if (hologram_definition_index != -1 && player_index != -1)
			eldorado::unit_set_hologram(object_index, player->unit_index, hologram_definition_index, &creation_data->hologram_position);
		if (((unsigned long)unit->unit_flags & 0x40000000) && player_index != -1)
		{
			long player_unit_index = player->unit_index;
			if (player_unit_index != -1)
			{
				long equipment_index = eldorado::unit_get_active_equipment_of_type(player_unit_index, _equipment_type_hologram);
				eldorado::unit_copy_armor_customization(player->unit_index, object_index);
				player_refresh_object_appearance_full(player_index, object_index);
				if (equipment_index != -1)
					object_get<s_item_data>(equipment_index)->owner_unit_index = object_index;
			}
			return object_index;
		}
		Armor_Apply(&creation_data->player_appearance, object_index);
	}
	return object_index;
}

void __fastcall c_simulation_unit_entity_definition__entity_creation_encode_hook(void *thisptr, void *__formal, long creation_data_size, s_simulation_unit_creation_data *creation_data, s_simulation_view_telemetry_data *telemetry_data, c_bitstream *bitstream, bool unknown) // 0x106D7BB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_simulation_unit_entity_definition__entity_creation_encode_hook@@YIXPAX0JPAUs_simulation_unit_creation_data@@PAUs_simulation_view_telemetry_data@@PAVc_bitstream@@_N@Z");

	((void (*)(s_simulation_object_creation_data *, c_bitstream *, long))0x4AD670)(creation_data, bitstream, creation_data_size);
	for (long i = 0; i < 5; i++)
		bitstream->write_integer("player-appearance-color", creation_data->player_appearance.colors[i], 24);
	for (long i = 0; i < 16; i++)
		bitstream->write_integer("player-appearance-region-permutations", creation_data->player_appearance.armor_section_indices[i], 8);
	bitstream->write_raw_data("variant-name", &creation_data->variant_name, 32);
	bitstream->write_bool("team-valid", creation_data->team != -1);
	if (creation_data->team != -1)
		bitstream->write_integer("team", creation_data->team != -1, 5);
	((void (*)(char const *, c_bitstream *, long))0x4B1440)("hologram-definition-index", bitstream, creation_data->hologram_definition_index);
	if (creation_data->hologram_definition_index != -1)
	{
		((void (*)(c_bitstream *, real_point3d const *, long, bool, real_rectangle3d const *))0x46FD80)(bitstream, &creation_data->hologram_position, 16, false, nullptr);
		((void (__thiscall *)(c_bitstream *, char const *, long))0x4BC310)(bitstream, "controlling-player-index", creation_data->controlling_player_index);
	}
}

bool __fastcall c_simulation_unit_entity_definition__entity_creation_decode_hook(void *thisptr, void *__formal, long creation_data_size, s_simulation_unit_creation_data *data, c_bitstream *bitstream, bool a4) // 0x106D7980
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_simulation_unit_entity_definition__entity_creation_decode_hook@@YI_NPAX0JPAUs_simulation_unit_creation_data@@PAVc_bitstream@@_N@Z");

	bool success = ((bool (*)(s_simulation_unit_creation_data *, c_bitstream *))0x4AD5E0)(data, bitstream);
	for (long i = 0; i < 5; i++)
		data->player_appearance.colors[i] = bitstream->read_integer("player-appearance-colors", 24);
	for (long i = 0; i < 16; i++)
		data->player_appearance.armor_section_indices[i] = (char)bitstream->read_integer("player-appearance-region-permutations", 8);
	bitstream->read_raw_data("variant-name", &data->variant_name, 32);
	if (bitstream->read_bool("team-valid"))
		data->team = bitstream->read_integer("team", 5);
	else
		data->team = -1;
	data->hologram_definition_index = ((long (*)(char const *, c_bitstream *))0x4B11E0)("hologram-definition-index", bitstream);
	if (data->hologram_definition_index != -1)
	{
		((void (*)(c_bitstream *, real_point3d *, long, bool))0x46F3F0)(bitstream, &data->hologram_position, 16, false);
		long controlling_player_index;
		if (bitstream->read_bool("controlling-player-index-valid"))
			controlling_player_index = -1;
		else
			controlling_player_index = bitstream->read_integer("controlling-player-index", 4);
		data->controlling_player_index = controlling_player_index;
	}
	return !bitstream->overflowed() && success;
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
