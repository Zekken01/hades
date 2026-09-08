/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/engine/game_engine_player_traits.hpp"
#include "Blam/game/game_globals.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/game_variant_settings.hpp"
#include "Blam/game/multiplayer_definitions.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/interface/gui/gui_screen_widget.hpp"
#include "Blam/interface/user_interface_multiplayer_game_settings.hpp"
#include "Blam/items/equipment_definitions.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/bitstream.hpp"
#include "Blam/memory/static_array.inl"
#include "Blam/networking/session/network_session_membership.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "mods/FileSystem/ModPackageFileSystemView.hpp"
#include "mods/mod_identifier.hpp"
#include "mods/mod_package_manager.hpp"
#include "mods/new/IModManager.hpp"
#include "mods/user_interface_mods.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
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
#include <functional>
#include <initializer_list>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <mutex>
#include <ostream>
#include <ratio>
#include <sstream>
#include <stdexcept>
#include <stop_token>
#include <streambuf>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

class IMod;
class IModListener;
class c_bitstream;
class c_gui_screen_widget;
class c_user_interface_mods_player_character_data;
struct c_game_engine_assault_variant;
struct c_game_engine_base_variant;
struct c_game_engine_ctf_variant;
struct c_game_engine_infection_variant;
struct c_game_engine_juggernaut_variant;
struct c_game_engine_king_variant;
struct c_game_engine_oddball_variant;
struct c_game_engine_sandbox_variant;
struct c_game_engine_slayer_variant;
struct c_game_engine_territories_variant;
struct c_game_engine_vip_variant;
struct c_game_variant;
struct c_gui_screen_game_options;
struct c_player_trait_appearance;
struct c_player_trait_extended;
struct c_player_trait_movement;
struct c_player_trait_sensors;
struct c_player_trait_shield_vitality;
struct c_player_trait_weapons;
struct c_player_traits;
struct s_game_globals;
struct s_multiplayer_globals_definition;
struct s_multiplayer_universal_globals_definition;
struct s_multiplayer_variant_settings_interface_definition;
struct s_player_datum;
struct s_text_value_pair_definition;
namespace hades_file_local
{
	union u_game_engine_variant;
	class c_user_interface_player_model_text_value_pair_proxy;
	class c_user_interface_player_model_set_text_value_pair_proxy;
	class ModListener;
}
using namespace hades_file_local;

namespace Utils {}
using namespace ::Utils;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace GameEngineSettings {}
	using namespace Patches::GameEngineSettings;
}

namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Cache {}
	using namespace Blam::Cache;
}

/* ---------- constants */

/* ---------- definitions */

namespace hades_file_local
{
	union u_game_engine_variant
	{
		c_game_engine_base_variant base; // 0x0
		c_game_engine_ctf_variant ctf; // 0x0
		c_game_engine_slayer_variant slayer; // 0x0
		c_game_engine_oddball_variant oddball; // 0x0
		c_game_engine_king_variant koth; // 0x0
		c_game_engine_sandbox_variant sandbox; // 0x0
		c_game_engine_vip_variant vip; // 0x0
		c_game_engine_juggernaut_variant juggernaut; // 0x0
		c_game_engine_territories_variant territories; // 0x0
		c_game_engine_assault_variant assault; // 0x0
		c_game_engine_infection_variant infection; // 0x0
	};
	static_assert(sizeof(u_game_engine_variant) == 592, "Invalid u_game_engine_variant size");

	class c_user_interface_player_model_text_value_pair_proxy :
		public s_user_interface_text_value_pair_proxy<16>
	{
	public:
		c_user_interface_player_model_text_value_pair_proxy(c_user_interface_mods_player_character_data *);
		void update(c_gui_screen_game_options *);
		bool try_get_string(unsigned long, wchar_t *);
	private:
		c_user_interface_mods_player_character_data *m_data; // 0x15C
	};
	static_assert(sizeof(c_user_interface_player_model_text_value_pair_proxy) == 352, "Invalid c_user_interface_player_model_text_value_pair_proxy size");

	//@@anonymous-namespace@@
	class c_user_interface_player_model_set_text_value_pair_proxy :
		public s_user_interface_text_value_pair_proxy<8>
	{
	public:
		c_user_interface_player_model_set_text_value_pair_proxy(c_user_interface_mods_player_character_data *);
		void update(c_gui_screen_game_options *);
		bool try_get_string(unsigned long, wchar_t *);
	private:
		c_user_interface_mods_player_character_data *m_data; // 0x15C
	};
	static_assert(sizeof(c_user_interface_player_model_set_text_value_pair_proxy) == 352, "Invalid c_user_interface_player_model_set_text_value_pair_proxy size");

	//@@anonymous-namespace@@
	class ModListener :
		public IModListener
	{
	private:
		virtual void OnModChanged(EModIndex, IMod *);
	public:
		ModListener(ModListener &); /* compiler_generated() */
		ModListener(ModListener const &); /* compiler_generated() */
		ModListener(); /* compiler_generated() */
		virtual ~ModListener(); /* compiler_generated() */
		ModListener &operator=(ModListener &); /* compiler_generated() */
		ModListener &operator=(ModListener const &); /* compiler_generated() */
	};
	static_assert(sizeof(ModListener) == 4, "Invalid ModListener size");
}
using namespace hades_file_local;
/* ---------- prototypes */

namespace Patches
{
	namespace GameEngineSettings
	{
		extern void ApplyAll();
	}
}

float c_player_health_traits__get_damage_resistance_hook(c_player_trait_shield_vitality *thisptr, void *__formal);
float c_player_movement_traits__get_walking_speed_hook(c_player_trait_movement *thisptr, void *__formal);
float c_player_movement_traits__get_personal_gravity_hook(c_player_trait_movement *thisptr, void *__formal);
void c_player_traits__encode_hook(c_player_traits &traits, void *unused, c_bitstream *stream);
void c_player_traits__decode_hook(c_player_traits &traits, void *unused, c_bitstream *stream);
void c_player_trait_shield_vitality__encode_hook(c_player_trait_shield_vitality *traits, void *unused, c_bitstream *stream);
void c_player_trait_shield_vitality__decode_hook(c_player_trait_shield_vitality *traits, void *unused, c_bitstream *stream);
void c_player_trait_weapons__encode_hook(c_player_trait_weapons &traits, void *unused, c_bitstream *stream);
void c_player_trait_weapons__decode_hook(c_player_trait_weapons &traits, void *unused, c_bitstream *stream);
void c_player_trait_movement__encode_hook(c_player_trait_movement &traits, void *unused, c_bitstream *stream);
void c_player_trait_movement__decode_hook(c_player_trait_movement &traits, void *unused, c_bitstream *stream);
void c_player_trait_appearance__encode_hook(c_player_trait_appearance &traits, void *unused, c_bitstream *stream);
void c_player_trait_appearance__decode_hook(c_player_trait_appearance &traits, void *unused, c_bitstream *stream);
void c_player_trait_sensors__encode_hook(c_player_trait_sensors &traits, void *unused, c_bitstream *stream);
void c_player_trait_sensors__decode_hook(c_player_trait_sensors &traits, void *unused, c_bitstream *stream);
void c_player_traits__initialize_hook(c_player_traits *thisptr);
void c_player_traits__set_hook(c_player_traits *thisptr, void *__formal, c_player_traits *traits, bool can_inherit);
void c_player_trait_shield_vitality__set_hook(c_player_trait_shield_vitality *thisptr, void *__formal, c_player_trait_shield_vitality const *traits, bool can_inherit);
void c_player_trait_weapons__set_hook(c_player_trait_weapons *thisptr, void *__formal, c_player_trait_weapons const *traits, bool can_inherit);
void c_player_trait_movement__set_hook(c_player_trait_movement *thisptr, void *__formal, c_player_trait_movement const *traits, bool can_inherit);
void c_player_trait_appearance__set_hook(c_player_trait_appearance *thisptr, void *__formal, c_player_trait_appearance const *traits, bool can_inherit);
void c_player_trait_sensors__set_hook(c_player_trait_sensors *thisptr, void *__formal, c_player_trait_sensors const *traits, bool can_inherit);
void game_engine_apply_extended_traits(long player_index, c_player_trait_extended const *traits);
void try_force_weapon_set(s_player_datum *player, c_player_trait_weapons const *traits);
void game_engine_apply_weapons_traits_new(long player_index, c_player_trait_weapons const *traits);
void game_engine_apply_player_traits_hook(long player_index, c_player_traits const *traits);
void game_engine_apply_respawn_traits_hook(long player_index, c_player_traits *traits);
void game_engine_apply_powerup_traits_hook(long player_index, c_player_traits *traits);
long game_variant_get_parameter_value_type(long parameter_type);
bool c_game_variant__get_game_engine_setting_hook(c_game_variant *thisptr, void *unused, e_game_variant_parameter parameter_type, char value_type, unsigned long *out_value);
bool c_game_variant__set_game_engine_setting_hook(c_game_variant *thisptr, void *unused, long parameter_type, char value_type, unsigned long value);
long game_variant_get_parameter_type_for_category_hook(long category, long parameter_type);
long c_gui_screen_game_options__get_category_index(c_gui_screen_game_options *screen);
long c_gui_screen_game_options__get_parameter_type_for_current_category(c_gui_screen_game_options *screen, long parameter_type);
bool c_gui_screen_game_options__try_and_get_parameter_value(c_gui_screen_game_options *screen, long parameter_type, unsigned long *out_value);
bool c_gui_screen_game_options__try_set_parameter_value(c_gui_screen_game_options *screen, long parameter_type, unsigned long value);
s_text_value_pair_definition *text_value_pair_definition_try_and_get_hook(s_multiplayer_variant_settings_interface_definition *definition, long parameter_type);
bool c_gui_screen_game_options__get_string_value_hook(c_gui_screen_widget *thisptr, void *unused, unsigned long id, wchar_t *out_value);
void c_gui_screen_game_options__begin_transition_hook(c_gui_screen_game_options *thisptr);
bool gui_screen_game_options_set_variant_parameter_hook(c_game_variant *thisptr, void *unused, long parameter_type, unsigned long value);

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern c_user_interface_mods_player_character_data g_player_characte_data; // 0x12464BA8
	extern bool g_player_model_proxy_dirty; // 0x113547A0
}
using namespace hades_file_local;
/* ---------- public code */

namespace Patches
{
	namespace GameEngineSettings
	{
		_extern void _sub_10A9EA80();
		void ApplyAll() // 0x10A9EA80
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@GameEngineSettings@Patches@@YAXXZ");
			// procedure flags: nofpo
			// function call : void (IModListener *)
			todo("implement");
			_sub_10A9EA80();
		}
	}
}

/* ---------- private code */

_extern float _sub_10AA5F10(c_player_trait_shield_vitality *, void *);
float c_player_health_traits__get_damage_resistance_hook(c_player_trait_shield_vitality *thisptr, void *__formal) // 0x10AA5F10
{
	// `anonymous-namespace'::c_player_health_traits__get_damage_resistance_hook
	// void *__formal;
	todo("implement");
	float __result = _sub_10AA5F10(thisptr, __formal);
	return __result;
}

_extern float _sub_10AA5FB0(c_player_trait_movement *, void *);
float c_player_movement_traits__get_walking_speed_hook(c_player_trait_movement *thisptr, void *__formal) // 0x10AA5FB0
{
	// `anonymous-namespace'::c_player_movement_traits__get_walking_speed_hook
	// void *__formal;
	todo("implement");
	float __result = _sub_10AA5FB0(thisptr, __formal);
	return __result;
}

_extern float _sub_10AA5F60(c_player_trait_movement *, void *);
float c_player_movement_traits__get_personal_gravity_hook(c_player_trait_movement *thisptr, void *__formal) // 0x10AA5F60
{
	// `anonymous-namespace'::c_player_movement_traits__get_personal_gravity_hook
	// void *__formal;
	todo("implement");
	float __result = _sub_10AA5F60(thisptr, __formal);
	return __result;
}

_extern void _sub_10AA6600(c_player_traits &, void *, c_bitstream *);
void c_player_traits__encode_hook(c_player_traits &traits, void *unused, c_bitstream *stream) // 0x10AA6600
{
	// `anonymous-namespace'::c_player_traits__encode_hook
	// c_bitstream *stream;
	todo("implement");
	_sub_10AA6600(traits, unused, stream);
}

_extern void _sub_10AA65A0(c_player_traits &, void *, c_bitstream *);
void c_player_traits__decode_hook(c_player_traits &traits, void *unused, c_bitstream *stream) // 0x10AA65A0
{
	// `anonymous-namespace'::c_player_traits__decode_hook
	// c_bitstream *stream;
	todo("implement");
	_sub_10AA65A0(traits, unused, stream);
}

_extern void _sub_10AA63C0(c_player_trait_shield_vitality *, void *, c_bitstream *);
void c_player_trait_shield_vitality__encode_hook(c_player_trait_shield_vitality *traits, void *unused, c_bitstream *stream) // 0x10AA63C0
{
	// `anonymous-namespace'::c_player_trait_shield_vitality__encode_hook
	// c_bitstream *stream;
	todo("implement");
	_sub_10AA63C0(traits, unused, stream);
}

_extern void _sub_10AA6360(c_player_trait_shield_vitality *, void *, c_bitstream *);
void c_player_trait_shield_vitality__decode_hook(c_player_trait_shield_vitality *traits, void *unused, c_bitstream *stream) // 0x10AA6360
{
	// `anonymous-namespace'::c_player_trait_shield_vitality__decode_hook
	// c_bitstream *stream;
	todo("implement");
	_sub_10AA6360(traits, unused, stream);
}

_extern void _sub_10AA64E0(c_player_trait_weapons &, void *, c_bitstream *);
void c_player_trait_weapons__encode_hook(c_player_trait_weapons &traits, void *unused, c_bitstream *stream) // 0x10AA64E0
{
	// `anonymous-namespace'::c_player_trait_weapons__encode_hook
	// c_bitstream *stream;
	todo("implement");
	_sub_10AA64E0(traits, unused, stream);
}

_extern void _sub_10AA6480(c_player_trait_weapons &, void *, c_bitstream *);
void c_player_trait_weapons__decode_hook(c_player_trait_weapons &traits, void *unused, c_bitstream *stream) // 0x10AA6480
{
	// `anonymous-namespace'::c_player_trait_weapons__decode_hook
	// c_bitstream *stream;
	todo("implement");
	_sub_10AA6480(traits, unused, stream);
}

_extern void _sub_10AA6180(c_player_trait_movement &, void *, c_bitstream *);
void c_player_trait_movement__encode_hook(c_player_trait_movement &traits, void *unused, c_bitstream *stream) // 0x10AA6180
{
	// `anonymous-namespace'::c_player_trait_movement__encode_hook
	// c_bitstream *stream;
	todo("implement");
	_sub_10AA6180(traits, unused, stream);
}

_extern void _sub_10AA6120(c_player_trait_movement &, void *, c_bitstream *);
void c_player_trait_movement__decode_hook(c_player_trait_movement &traits, void *unused, c_bitstream *stream) // 0x10AA6120
{
	// `anonymous-namespace'::c_player_trait_movement__decode_hook
	// c_bitstream *stream;
	todo("implement");
	_sub_10AA6120(traits, unused, stream);
}

_extern void _sub_10AA6060(c_player_trait_appearance &, void *, c_bitstream *);
void c_player_trait_appearance__encode_hook(c_player_trait_appearance &traits, void *unused, c_bitstream *stream) // 0x10AA6060
{
	// `anonymous-namespace'::c_player_trait_appearance__encode_hook
	// c_bitstream *stream;
	todo("implement");
	_sub_10AA6060(traits, unused, stream);
}

_extern void _sub_10AA6000(c_player_trait_appearance &, void *, c_bitstream *);
void c_player_trait_appearance__decode_hook(c_player_trait_appearance &traits, void *unused, c_bitstream *stream) // 0x10AA6000
{
	// `anonymous-namespace'::c_player_trait_appearance__decode_hook
	// c_bitstream *stream;
	todo("implement");
	_sub_10AA6000(traits, unused, stream);
}

_extern void _sub_10AA62A0(c_player_trait_sensors &, void *, c_bitstream *);
void c_player_trait_sensors__encode_hook(c_player_trait_sensors &traits, void *unused, c_bitstream *stream) // 0x10AA62A0
{
	// `anonymous-namespace'::c_player_trait_sensors__encode_hook
	// c_bitstream *stream;
	todo("implement");
	_sub_10AA62A0(traits, unused, stream);
}

_extern void _sub_10AA6240(c_player_trait_sensors &, void *, c_bitstream *);
void c_player_trait_sensors__decode_hook(c_player_trait_sensors &traits, void *unused, c_bitstream *stream) // 0x10AA6240
{
	// `anonymous-namespace'::c_player_trait_sensors__decode_hook
	// c_bitstream *stream;
	todo("implement");
	_sub_10AA6240(traits, unused, stream);
}

_extern void _sub_10AA6660(c_player_traits *);
void c_player_traits__initialize_hook(c_player_traits *thisptr) // 0x10AA6660
{
	// `anonymous-namespace'::c_player_traits__initialize_hook
	// c_player_traits *thisptr;
	todo("implement");
	_sub_10AA6660(thisptr);
}

_extern void _sub_10AA66B0(c_player_traits *, void *, c_player_traits *, bool);
void c_player_traits__set_hook(c_player_traits *thisptr, void *__formal, c_player_traits *traits, bool can_inherit) // 0x10AA66B0
{
	// `anonymous-namespace'::c_player_traits__set_hook
	// bool can_inherit;
	todo("implement");
	_sub_10AA66B0(thisptr, __formal, traits, can_inherit);
}

_extern void _sub_10AA6420(c_player_trait_shield_vitality *, void *, c_player_trait_shield_vitality const *, bool);
void c_player_trait_shield_vitality__set_hook(c_player_trait_shield_vitality *thisptr, void *__formal, c_player_trait_shield_vitality const *traits, bool can_inherit) // 0x10AA6420
{
	// `anonymous-namespace'::c_player_trait_shield_vitality__set_hook
	// bool can_inherit;
	todo("implement");
	_sub_10AA6420(thisptr, __formal, traits, can_inherit);
}

_extern void _sub_10AA6540(c_player_trait_weapons *, void *, c_player_trait_weapons const *, bool);
void c_player_trait_weapons__set_hook(c_player_trait_weapons *thisptr, void *__formal, c_player_trait_weapons const *traits, bool can_inherit) // 0x10AA6540
{
	// `anonymous-namespace'::c_player_trait_weapons__set_hook
	// bool can_inherit;
	todo("implement");
	_sub_10AA6540(thisptr, __formal, traits, can_inherit);
}

_extern void _sub_10AA61E0(c_player_trait_movement *, void *, c_player_trait_movement const *, bool);
void c_player_trait_movement__set_hook(c_player_trait_movement *thisptr, void *__formal, c_player_trait_movement const *traits, bool can_inherit) // 0x10AA61E0
{
	// `anonymous-namespace'::c_player_trait_movement__set_hook
	// bool can_inherit;
	todo("implement");
	_sub_10AA61E0(thisptr, __formal, traits, can_inherit);
}

_extern void _sub_10AA60C0(c_player_trait_appearance *, void *, c_player_trait_appearance const *, bool);
void c_player_trait_appearance__set_hook(c_player_trait_appearance *thisptr, void *__formal, c_player_trait_appearance const *traits, bool can_inherit) // 0x10AA60C0
{
	// `anonymous-namespace'::c_player_trait_appearance__set_hook
	// bool can_inherit;
	todo("implement");
	_sub_10AA60C0(thisptr, __formal, traits, can_inherit);
}

_extern void _sub_10AA6300(c_player_trait_sensors *, void *, c_player_trait_sensors const *, bool);
void c_player_trait_sensors__set_hook(c_player_trait_sensors *thisptr, void *__formal, c_player_trait_sensors const *traits, bool can_inherit) // 0x10AA6300
{
	// `anonymous-namespace'::c_player_trait_sensors__set_hook
	// bool can_inherit;
	todo("implement");
	_sub_10AA6300(thisptr, __formal, traits, can_inherit);
}

_extern void _sub_10AA6710(long, c_player_trait_extended const *);
void game_engine_apply_extended_traits(long player_index, c_player_trait_extended const *traits) // 0x10AA6710
{
	// `anonymous-namespace'::game_engine_apply_extended_traits
	// static ...; // 0x10AA68E0
	// static ...; // 0x10AA68D8
	// long player_index;
	// c_player_trait_extended const *traits;
	// s_player_datum *player;
	// bool changed;
	{
		// unsigned long long const update_mask;
	}
	// function call : void (*const)(short, unsigned long long const *)
	todo("implement");
	_sub_10AA6710(player_index, traits);
}

_extern void _sub_10AA7A20(s_player_datum *, c_player_trait_weapons const *);
void try_force_weapon_set(s_player_datum *player, c_player_trait_weapons const *traits) // 0x10AA7A20
{
	// `anonymous-namespace'::try_force_weapon_set
	// static ...; // 0x10AA7BFC
	// static ...; // 0x10AA7BF4
	// s_player_datum *player;
	// c_player_trait_weapons const *traits;
	// s_game_globals *game_globals;
	// long (*const game_engine_weapon_item_definition_index_from_absolute_weapons_selection_block_index)(short, long);
	// unsigned long unit_index;
	// c_tag_block<s_multiplayer_universal_globals_definition> universal;
	// s_multiplayer_globals_definition *multiplayer_globals;
	{
		// long secondary_tag_index;
		// char pickup_value;
		// long primary_tag_index;
	}
	// function call : bool (*const)()
	// function call : void *(*const)(unsigned long, long)
	// function call : long (*const)(short, long)
	// function call : long (*const)(short, long)
	// function call : void (*const)(long)
	// function call : __int32 (*const)(long, long, long)
	// function call : __int32 (*const)(long, long, long)
	todo("implement");
	_sub_10AA7A20(player, traits);
}

_extern void _sub_10AA6D70(long, c_player_trait_weapons const *);
void game_engine_apply_weapons_traits_new(long player_index, c_player_trait_weapons const *traits) // 0x10AA6D70
{
	// `anonymous-namespace'::game_engine_apply_weapons_traits_new
	// c_player_trait_weapons const *traits;
	// s_player_datum *player;
	// void (*const game_engine_apply_weapons_traits)(long, c_player_trait_weapons const *);
	// short (*const weapon_get_multiplayer_type)(long);
	// char og_init_primary;
	// char og_init_secondary;
	{
		// unsigned long support_weapon_index;
	}
	// function call : void (*const)(long, c_player_trait_weapons const *)
	// function call : char (*const)()
	// function call : bool (*const)(long, long *, long *)
	// function call : long (*const)(long, short)
	// function call : short (*const)(long)
	todo("implement");
	_sub_10AA6D70(player_index, traits);
}

_extern void _sub_10AA6980(long, c_player_traits const *);
void game_engine_apply_player_traits_hook(long player_index, c_player_traits const *traits) // 0x10AA6980
{
	// `anonymous-namespace'::game_engine_apply_player_traits_hook
	// c_player_traits const *traits;
	// void (*const game_engine_apply_weapons_traits)(long, c_player_trait_weapons const *);
	// void (*const game_engine_apply_vitality_traits)(long, c_player_trait_shield_vitality const *);
	// void (*const game_engine_apply_appearance_trait)(long, c_player_trait_appearance const *);
	// void (*const game_engine_apply_sensors_traits)(long, c_player_trait_sensors const *);
	// void (*const game_engine_apply_movement_traits)(long, c_player_trait_movement const *);
	// function call : void (*const)(long, c_player_trait_shield_vitality const *)
	// function call : void (*const)(long, c_player_trait_movement const *)
	// function call : void (*const)(long, c_player_trait_appearance const *)
	// function call : void (*const)(long, c_player_trait_sensors const *)
	todo("implement");
	_sub_10AA6980(player_index, traits);
}

_extern void _sub_10AA6C90(long, c_player_traits *);
void game_engine_apply_respawn_traits_hook(long player_index, c_player_traits *traits) // 0x10AA6C90
{
	// `anonymous-namespace'::game_engine_apply_respawn_traits_hook
	// c_player_traits *traits;
	// s_player_datum *player;
	// u_game_engine_variant *const variant;
	// c_game_variant *game_variant;
	// function call : c_game_variant *(*const)()
	todo("implement");
	_sub_10AA6C90(player_index, traits);
}

_extern void _sub_10AA6AB0(long, c_player_traits *);
void game_engine_apply_powerup_traits_hook(long player_index, c_player_traits *traits) // 0x10AA6AB0
{
	// `anonymous-namespace'::game_engine_apply_powerup_traits_hook
	// static ...; // 0x10AA6C14
	// static ...; // 0x10AA6C0C
	// long player_index;
	// c_player_traits *traits;
	// s_player_datum *player;
	// long most_recent_pickup_time;
	// constexpr float (*const `game_engine_apply_powerup_traits_hook'::`2'::game_get_powerup_duration_in_seconds)(unsigned char); // constant == 7757152
	// long seconds_active;
	// constexpr void (*const `game_engine_apply_powerup_traits_hook'::`2'::game_engine_get_variant_powerup_traits)(unsigned char, c_player_traits *); // constant == 7757280
	// long powerup_flavor;
	{
		// long i;
	}
	{
		// c_player_traits desired_traits;
	}
	// function call : long (*const)()
	// function call : float (*const)(float)
	// function call : float (*const)(unsigned char)
	// function call : void (*const)(unsigned char, c_player_traits *)
	todo("implement");
	_sub_10AA6AB0(player_index, traits);
}

_extern long _sub_10AA7790(long);
long game_variant_get_parameter_value_type(long parameter_type) // 0x10AA7790
{
	// `anonymous-namespace'::game_variant_get_parameter_value_type
	// long parameter_type;
	// constexpr long (*const `game_variant_get_parameter_value_type'::`2'::game_variant_get_parameter_value_type)(long); // constant == 5716384
	// bool extended;
	// function call : long (*const)(long)
	todo("implement");
	long __result = _sub_10AA7790(parameter_type);
	return __result;
}

_extern bool _sub_10AA3BC0(c_game_variant *, void *, e_game_variant_parameter, char, unsigned long *);
bool c_game_variant__get_game_engine_setting_hook(c_game_variant *thisptr, void *unused, e_game_variant_parameter parameter_type, char value_type, unsigned long *out_value) // 0x10AA3BC0
{
	// `anonymous-namespace'::c_game_variant__get_game_engine_setting_hook
// $LN84:
// $LN83:
// $LN82:
// $LN81:
// $LN80:
// $LN79:
// $LN78:
// $LN77:
// $LN76:
// $LN75:
// $LN74:
// $LN73:
// $LN72:
// $LN71:
// $LN70:
// $LN69:
// $LN68:
// $LN67:
// $LN66:
// $LN65:
// $LN64:
// $LN63:
// $LN62:
// $LN61:
// $LN60:
// $LN59:
// $LN58:
// $LN57:
// $LN56:
// $LN55:
// $LN54:
// $LN53:
// $LN52:
// $LN51:
// $LN50:
// $LN49:
// $LN48:
// $LN47:
// $LN46:
// $LN45:
// $LN44:
// $LN43:
// $LN42:
// $LN41:
// $LN40:
// $LN39:
// $LN38:
// $LN37:
// $LN36:
// $LN35:
// $LN34:
// $LN33:
// $LN32:
// $LN31:
// $LN30:
// $LN29:
// $LN28:
// $LN27:
// $LN26:
// $LN25:
// $LN24:
// $LN23:
// $LN22:
// $LN21:
// $LN20:
// $LN19:
// $LN18:
// $LN17:
// $LN16:
// $LN15:
// $LN14:
// $LN13:
// $LN12:
// $LN11:
// $LN10:
// $LN9:
// $LN8:
// $LN7:
// $LN6:
// $LN5:
// $LN4:
	// c_game_variant *thisptr;
	// void *unused;
	// e_game_variant_parameter parameter_type;
	// char value_type;
	// unsigned long *out_value;
	// u_game_engine_variant *const variant;
	// constexpr bool (*const `c_game_variant__get_game_engine_setting_hook'::`2'::get_game_engine_setting)(void *, e_game_variant_parameter, char, unsigned long *); // constant == 5719344
	// function call : bool (*const)(void *, e_game_variant_parameter, char, unsigned long *)
	todo("implement");
	bool __result = _sub_10AA3BC0(thisptr, unused, parameter_type, value_type, out_value);
	return __result;
}

_extern bool _sub_10AA4A10(c_game_variant *, void *, long, char, unsigned long);
bool c_game_variant__set_game_engine_setting_hook(c_game_variant *thisptr, void *unused, long parameter_type, char value_type, unsigned long value) // 0x10AA4A10
{
	// `anonymous-namespace'::c_game_variant__set_game_engine_setting_hook
// $LN84:
// $LN83:
// $LN82:
// $LN81:
// $LN80:
// $LN79:
// $LN78:
// $LN77:
// $LN76:
// $LN75:
// $LN74:
// $LN73:
// $LN72:
// $LN71:
// $LN70:
// $LN69:
// $LN68:
// $LN67:
// $LN66:
// $LN65:
// $LN64:
// $LN63:
// $LN62:
// $LN61:
// $LN60:
// $LN59:
// $LN58:
// $LN57:
// $LN56:
// $LN55:
// $LN54:
// $LN53:
// $LN52:
// $LN51:
// $LN50:
// $LN49:
// $LN48:
// $LN47:
// $LN46:
// $LN45:
// $LN44:
// $LN43:
// $LN42:
// $LN41:
// $LN40:
// $LN39:
// $LN38:
// $LN37:
// $LN36:
// $LN35:
// $LN34:
// $LN33:
// $LN32:
// $LN31:
// $LN30:
// $LN29:
// $LN28:
// $LN27:
// $LN26:
// $LN25:
// $LN24:
// $LN23:
// $LN22:
// $LN21:
// $LN20:
// $LN19:
// $LN18:
// $LN17:
// $LN16:
// $LN15:
// $LN14:
// $LN13:
// $LN12:
// $LN11:
// $LN10:
// $LN9:
// $LN8:
// $LN7:
// $LN6:
// $LN5:
// $LN4:
	// c_game_variant *thisptr;
	// void *unused;
	// long parameter_type;
	// char value_type;
	// unsigned long value;
	// u_game_engine_variant *const variant;
	// constexpr bool (*const `c_game_variant__set_game_engine_setting_hook'::`2'::c_game_variant__set_game_engine_setting)(c_game_variant *, long, char, unsigned long); // constant == 5745328
	// function call : bool (*const)(c_game_variant *, long, char, unsigned long)
	todo("implement");
	bool __result = _sub_10AA4A10(thisptr, unused, parameter_type, value_type, value);
	return __result;
}

_extern long _sub_10AA6F10(long, long);
long game_variant_get_parameter_type_for_category_hook(long category, long parameter_type) // 0x10AA6F10
{
	// `anonymous-namespace'::game_variant_get_parameter_type_for_category_hook
// $LN130:
// $LN124:
// $LN118:
// $LN112:
// $LN106:
// $LN100:
// $LN94:
// $LN88:
// $LN82:
// $LN76:
// $LN70:
// $LN64:
// $LN58:
// $LN52:
// $LN46:
// $LN40:
// $LN34:
// $LN28:
// $LN22:
// $LN16:
// $LN10:
	// long category;
	// long parameter_type;
	// bool extended;
	todo("implement");
	long __result = _sub_10AA6F10(category, parameter_type);
	return __result;
}

_extern long _sub_10AA5C10(c_gui_screen_game_options *);
long c_gui_screen_game_options__get_category_index(c_gui_screen_game_options *screen) // 0x10AA5C10
{
	// `anonymous-namespace'::c_gui_screen_game_options__get_category_index
	// c_gui_screen_game_options *screen;
	// long index;
	// long category_index;
	todo("implement");
	long __result = _sub_10AA5C10(screen);
	return __result;
}

_extern long _sub_10AA5C80(c_gui_screen_game_options *, long);
long c_gui_screen_game_options__get_parameter_type_for_current_category(c_gui_screen_game_options *screen, long parameter_type) // 0x10AA5C80
{
	// `anonymous-namespace'::c_gui_screen_game_options__get_parameter_type_for_current_category
	// long parameter_type;
	// long category_index;
	todo("implement");
	long __result = _sub_10AA5C80(screen, parameter_type);
	return __result;
}

_extern bool _sub_10AA5DF0(c_gui_screen_game_options *, long, unsigned long *);
bool c_gui_screen_game_options__try_and_get_parameter_value(c_gui_screen_game_options *screen, long parameter_type, unsigned long *out_value) // 0x10AA5DF0
{
	// `anonymous-namespace'::c_gui_screen_game_options__try_and_get_parameter_value
	// unsigned long *out_value;
	// c_game_variant *variant;
	todo("implement");
	bool __result = _sub_10AA5DF0(screen, parameter_type, out_value);
	return __result;
}

_extern bool _sub_10AA5E80(c_gui_screen_game_options *, long, unsigned long);
bool c_gui_screen_game_options__try_set_parameter_value(c_gui_screen_game_options *screen, long parameter_type, unsigned long value) // 0x10AA5E80
{
	// `anonymous-namespace'::c_gui_screen_game_options__try_set_parameter_value
	// unsigned long value;
	// c_game_variant *variant;
	todo("implement");
	bool __result = _sub_10AA5E80(screen, parameter_type, value);
	return __result;
}

extern c_user_interface_player_model_text_value_pair_proxy* _sub_10A9E910(c_user_interface_player_model_text_value_pair_proxy *const, c_user_interface_mods_player_character_data *);
_inline c_user_interface_player_model_text_value_pair_proxy::c_user_interface_player_model_text_value_pair_proxy(c_user_interface_mods_player_character_data *data) // 0x10A9E910
{
	// `anonymous-namespace'::c_user_interface_player_model_text_value_pair_proxy::c_user_interface_player_model_text_value_pair_proxy
	// c_user_interface_mods_player_character_data *data;
	todo("implement");
	_sub_10A9E910(this, data);
}

_inline ModListener::~ModListener() // 0x10A9E940
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??1ModListener@hades_file_local@@UAE@XZ");
	// `anonymous-namespace'::ModListener::~ModListener
	// ModListener *const this;

	compiler_generated();
}

_extern void _sub_10AA82A0(c_user_interface_player_model_text_value_pair_proxy *const, c_gui_screen_game_options *);
_inline void c_user_interface_player_model_text_value_pair_proxy::update(c_gui_screen_game_options *screen) // 0x10AA82A0
{
	// `anonymous-namespace'::c_user_interface_player_model_text_value_pair_proxy::update
	// static ...; // 0x10AA85F0
	// static ...; // 0x10AA85E8
	// c_user_interface_player_model_text_value_pair_proxy *const this;
	// c_gui_screen_game_options *screen;
	// s_game_globals *game_globals;
	// s_multiplayer_globals_definition *multiplayer_globals;
	{
		// unsigned long character_set_trait_value;
		{
			// long character_index;
			{
				// long i;
			}
		}
	}
	// function call : void *(*const)(unsigned long, long)
	todo("implement");
	_sub_10AA82A0(this, screen);
}

extern ModListener* _sub_10A9E880(ModListener *const);
_inline ModListener::ModListener() // 0x10A9E880
{
	// `anonymous-namespace'::ModListener::ModListener
	// ModListener *const this;
	compiler_generated();
	todo("implement");
	_sub_10A9E880(this);
}

_extern bool _sub_10AA7DF0(c_user_interface_player_model_text_value_pair_proxy *const, unsigned long, wchar_t *);
_inline bool c_user_interface_player_model_text_value_pair_proxy::try_get_string(unsigned long id, wchar_t *out_value) // 0x10AA7DF0
{
	// `anonymous-namespace'::c_user_interface_player_model_text_value_pair_proxy::try_get_string
	// static ...; // 0x10AA7F1C
	// c_user_interface_player_model_text_value_pair_proxy *const this;
	// unsigned long id;
	// wchar_t *out_value;
	{
		// long i;
		{
			// unsigned __int32 nc;
		}
	}
	todo("implement");
	bool __result = _sub_10AA7DF0(this, id, out_value);
	return __result;
}

extern c_user_interface_player_model_set_text_value_pair_proxy* _sub_10A9E8E0(c_user_interface_player_model_set_text_value_pair_proxy *const, c_user_interface_mods_player_character_data *);
_inline c_user_interface_player_model_set_text_value_pair_proxy::c_user_interface_player_model_set_text_value_pair_proxy(c_user_interface_mods_player_character_data *data) // 0x10A9E8E0
{
	// `anonymous-namespace'::c_user_interface_player_model_set_text_value_pair_proxy::c_user_interface_player_model_set_text_value_pair_proxy
	// c_user_interface_mods_player_character_data *data;
	todo("implement");
	_sub_10A9E8E0(this, data);
}

_extern void _sub_10AA7F90(c_user_interface_player_model_set_text_value_pair_proxy *const, c_gui_screen_game_options *);
_inline void c_user_interface_player_model_set_text_value_pair_proxy::update(c_gui_screen_game_options *screen) // 0x10AA7F90
{
	// `anonymous-namespace'::c_user_interface_player_model_set_text_value_pair_proxy::update
	// c_gui_screen_game_options *screen;
	{
		// long i;
	}
	todo("implement");
	_sub_10AA7F90(this, screen);
}

_extern bool _sub_10AA7C90(c_user_interface_player_model_set_text_value_pair_proxy *const, unsigned long, wchar_t *);
_inline bool c_user_interface_player_model_set_text_value_pair_proxy::try_get_string(unsigned long id, wchar_t *out_value) // 0x10AA7C90
{
	// `anonymous-namespace'::c_user_interface_player_model_set_text_value_pair_proxy::try_get_string
	// static ...; // 0x10AA7D8C
	// c_user_interface_player_model_set_text_value_pair_proxy *const this;
	// unsigned long id;
	// wchar_t *out_value;
	{
		// long i;
		{
			// unsigned __int32 nc;
		}
	}
	todo("implement");
	bool __result = _sub_10AA7C90(this, id, out_value);
	return __result;
}

extern s_text_value_pair_definition *_sub_10AA7970(s_multiplayer_variant_settings_interface_definition *, long);
s_text_value_pair_definition *text_value_pair_definition_try_and_get_hook(s_multiplayer_variant_settings_interface_definition *definition, long parameter_type) // 0x10AA7970
{
	// `anonymous-namespace'::text_value_pair_definition_try_and_get_hook
	// long parameter_type;
	// constexpr s_text_value_pair_definition *(*const `text_value_pair_definition_try_and_get_hook'::`2'::text_value_pair_definition_try_and_get_recursive)(s_multiplayer_variant_settings_interface_definition *, long); // constant == 11665456
	// function call : s_text_value_pair_definition *(*const)(s_multiplayer_variant_settings_interface_definition *, long)
	todo("implement");
	s_text_value_pair_definition * __result = _sub_10AA7970(definition, parameter_type);
	return __result;
}

_extern bool _sub_10AA5CF0(c_gui_screen_widget *, void *, unsigned long, wchar_t *);
bool c_gui_screen_game_options__get_string_value_hook(c_gui_screen_widget *thisptr, void *unused, unsigned long id, wchar_t *out_value) // 0x10AA5CF0
{
	// `anonymous-namespace'::c_gui_screen_game_options__get_string_value_hook
	// wchar_t *out_value;
	// constexpr bool (*const `c_gui_screen_game_options__get_string_value_hook'::`2'::c_gui_screen_widget__get_string_value)(c_gui_screen_widget *, unsigned long, wchar_t *); // constant == 11210752
	// constexpr bool (*const `c_gui_screen_game_options__get_string_value_hook'::`2'::string_list_valid_string)(long, unsigned long); // constant == 5365696
	// long strings_definition_index;
	// function call : bool (*const)(long, unsigned long)
	// function call : bool (*const)(c_gui_screen_widget *, unsigned long, wchar_t *)
	todo("implement");
	bool __result = _sub_10AA5CF0(thisptr, unused, id, out_value);
	return __result;
}

_extern void _sub_10AA5B70(c_gui_screen_game_options *);
void c_gui_screen_game_options__begin_transition_hook(c_gui_screen_game_options *thisptr) // 0x10AA5B70
{
	// `anonymous-namespace'::c_gui_screen_game_options__begin_transition_hook
	// c_gui_screen_game_options *thisptr;
	// constexpr void (*const `c_gui_screen_game_options__begin_transition_hook'::`2'::c_gui_screen_widget__begin_transition)(void *); // constant == 11587296
	// function call : void (*const)(void *)
	todo("implement");
	_sub_10AA5B70(thisptr);
}

_extern bool _sub_10AA78A0(c_game_variant *, void *, long, unsigned long);
bool gui_screen_game_options_set_variant_parameter_hook(c_game_variant *thisptr, void *unused, long parameter_type, unsigned long value) // 0x10AA78A0
{
	// `anonymous-namespace'::gui_screen_game_options_set_variant_parameter_hook
	// unsigned long value;
	// bool ret;
	// constexpr bool (*const `gui_screen_game_options_set_variant_parameter_hook'::`2'::c_game_engine_variant__set_parameter)(c_game_variant *, long, unsigned long); // constant == 5768992
	{
		// c_gui_screen_game_options *options_screen;
	}
	// function call : bool (*const)(c_game_variant *, long, unsigned long)
	todo("implement");
	bool __result = _sub_10AA78A0(thisptr, unused, parameter_type, value);
	return __result;
}

_extern void _sub_10AA3B90(ModListener *const, EModIndex, IMod *);
_inline void ModListener::OnModChanged(EModIndex index, IMod *mod) // 0x10AA3B90
{
	// `anonymous-namespace'::ModListener::OnModChanged
	// IMod *mod;
	todo("implement");
	_sub_10AA3B90(this, index, mod);
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool s_static_array<s_text_value_pair,16>::valid(__int32);
template s_text_value_pair & s_static_array<s_text_value_pair,16>::operator[](long);
