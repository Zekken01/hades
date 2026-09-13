/* ---------- headers */

#include "hades/hades.h"
#include "mods/mod_system.hpp"

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
		virtual ~ModListener() = default; /* compiler_generated() */
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

float __fastcall c_player_health_traits__get_damage_resistance_hook(c_player_trait_shield_vitality *thisptr, void *__formal);
float __fastcall c_player_movement_traits__get_walking_speed_hook(c_player_trait_movement *thisptr, void *__formal);
float __fastcall c_player_movement_traits__get_personal_gravity_hook(c_player_trait_movement *thisptr, void *__formal);
void __fastcall c_player_traits__encode_hook(c_player_traits &traits, void *unused, c_bitstream *stream);
void __fastcall c_player_traits__decode_hook(c_player_traits &traits, void *unused, c_bitstream *stream);
void __fastcall c_player_trait_shield_vitality__encode_hook(c_player_trait_shield_vitality *traits, void *unused, c_bitstream *stream);
void __fastcall c_player_trait_shield_vitality__decode_hook(c_player_trait_shield_vitality *traits, void *unused, c_bitstream *stream);
void __fastcall c_player_trait_weapons__encode_hook(c_player_trait_weapons &traits, void *unused, c_bitstream *stream);
void __fastcall c_player_trait_weapons__decode_hook(c_player_trait_weapons &traits, void *unused, c_bitstream *stream);
void __fastcall c_player_trait_movement__encode_hook(c_player_trait_movement &traits, void *unused, c_bitstream *stream);
void __fastcall c_player_trait_movement__decode_hook(c_player_trait_movement &traits, void *unused, c_bitstream *stream);
void __fastcall c_player_trait_appearance__encode_hook(c_player_trait_appearance &traits, void *unused, c_bitstream *stream);
void __fastcall c_player_trait_appearance__decode_hook(c_player_trait_appearance &traits, void *unused, c_bitstream *stream);
void __fastcall c_player_trait_sensors__encode_hook(c_player_trait_sensors &traits, void *unused, c_bitstream *stream);
void __fastcall c_player_trait_sensors__decode_hook(c_player_trait_sensors &traits, void *unused, c_bitstream *stream);
void __fastcall c_player_traits__initialize_hook(c_player_traits *thisptr);
void __fastcall c_player_traits__set_hook(c_player_traits *thisptr, void *__formal, c_player_traits *traits, bool can_inherit);
void __fastcall c_player_trait_shield_vitality__set_hook(c_player_trait_shield_vitality *thisptr, void *__formal, c_player_trait_shield_vitality const *traits, bool can_inherit);
void __fastcall c_player_trait_weapons__set_hook(c_player_trait_weapons *thisptr, void *__formal, c_player_trait_weapons const *traits, bool can_inherit);
void __fastcall c_player_trait_movement__set_hook(c_player_trait_movement *thisptr, void *__formal, c_player_trait_movement const *traits, bool can_inherit);
void __fastcall c_player_trait_appearance__set_hook(c_player_trait_appearance *thisptr, void *__formal, c_player_trait_appearance const *traits, bool can_inherit);
void __fastcall c_player_trait_sensors__set_hook(c_player_trait_sensors *thisptr, void *__formal, c_player_trait_sensors const *traits, bool can_inherit);
void game_engine_apply_extended_traits(long player_index, c_player_trait_extended const *traits);
void try_force_weapon_set(s_player_datum *player, c_player_trait_weapons const *traits);
void game_engine_apply_weapons_traits_new(long player_index, c_player_trait_weapons const *traits);
void game_engine_apply_player_traits_hook(long player_index, c_player_traits const *traits);
void game_engine_apply_respawn_traits_hook(long player_index, c_player_traits *traits);
void game_engine_apply_powerup_traits_hook(long player_index, c_player_traits *traits);
long game_variant_get_parameter_value_type(long parameter_type);
bool __fastcall c_game_variant__get_game_engine_setting_hook(c_game_variant *thisptr, void *unused, e_game_variant_parameter parameter_type, char value_type, unsigned long *out_value);
bool __fastcall c_game_variant__set_game_engine_setting_hook(c_game_variant *thisptr, void *unused, long parameter_type, char value_type, unsigned long value);
long game_variant_get_parameter_type_for_category_hook(long category, long parameter_type);
long c_gui_screen_game_options__get_category_index(c_gui_screen_game_options *screen);
long c_gui_screen_game_options__get_parameter_type_for_current_category(c_gui_screen_game_options *screen, long parameter_type);
bool c_gui_screen_game_options__try_and_get_parameter_value(c_gui_screen_game_options *screen, long parameter_type, unsigned long *out_value);
bool c_gui_screen_game_options__try_set_parameter_value(c_gui_screen_game_options *screen, long parameter_type, unsigned long value);
s_text_value_pair_definition *text_value_pair_definition_try_and_get_hook(s_multiplayer_variant_settings_interface_definition *definition, long parameter_type);
bool __fastcall c_gui_screen_game_options__get_string_value_hook(c_gui_screen_widget *thisptr, void *unused, unsigned long id, wchar_t *out_value);
void __fastcall c_gui_screen_game_options__begin_transition_hook(c_gui_screen_game_options *thisptr);
bool __fastcall gui_screen_game_options_set_variant_parameter_hook(c_game_variant *thisptr, void *unused, long parameter_type, unsigned long value);

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern bool g_player_model_proxy_dirty; // 0x113547A0
	extern c_user_interface_player_model_text_value_pair_proxy g_player_model_options_proxy; // 0x124648E8
	extern c_user_interface_player_model_set_text_value_pair_proxy g_player_model_set_options_proxy; // 0x12464A48
	extern c_user_interface_mods_player_character_data g_player_characte_data; // 0x12464BA8
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
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAll@GameEngineSettings@Patches@@YAXXZ");
			// procedure flags: nofpo

			Patch(0x1CB9A3, { 0x03 }).Apply();
			Patch(0x1CBF34, { 0x03 }).Apply();
			Patch(0x1CE01C, { 0x03 }).Apply();
			Patch(0x1CD588, { 0x03 }).Apply();
			Patch(0x1CCBEF, { 0x03 }).Apply();
			Patch(0x1CB59C, { 0x05 }).Apply();
			Patch(0x1CDEF8, { 0x05 }).Apply();
			Patch(0x1CBA17, { 0x05 }).Apply();
			Patch(0x1CC69B, { 0x05 }).Apply();
			Patch(0x1CCE55, { 0x05 }).Apply();
			Patch(0x1CB8D0, { 0x0F }).Apply();
			Patch(0x1CDB76, { 0x0F }).Apply();
			Patch(0x1CD2C8, { 0x0F }).Apply();
			Patch(0x1CC94F, { 0x0F }).Apply();
			Patch(0x1CBD70, { 0x0F }).Apply();
			Hook(0x1CC110, c_player_health_traits__get_damage_resistance_hook).Apply();
			Patch(0x1CB9D3, { 0x0F }).Apply();
			Patch(0x1CD7B4, { 0x0F }).Apply();
			Patch(0x1CDD88, { 0x0F }).Apply();
			Patch(0x1CC77F, { 0x0F }).Apply();
			Patch(0x1CB733, { 0x0F }).Apply();
			Hook(0x1CC480, c_player_movement_traits__get_walking_speed_hook).Apply();
			Patch(0x1CB9E3, { 0x0A }).Apply();
			Patch(0x1CD7C7, { 0x0A }).Apply();
			Patch(0x1CD4C8, { 0x0A }).Apply();
			Patch(0x1CC79B, { 0x0A }).Apply();
			Patch(0x1CB767, { 0x0A }).Apply();
			Hook(0x1CC200, c_player_movement_traits__get_personal_gravity_hook).Apply();
			Patch(0x1CB5BB, { 0x12 }).Apply();
			Patch(0x1CBA27, { 0x12 }).Apply();
			Patch(0x1CCEB8, { 0x12 }).Apply();
			Patch(0x1CC6B9, { 0x12 }).Apply();
			Patch(0x1CCE68, { 0x12 }).Apply();
			Patch(0x14F3B6, 0x90, 6).Apply();
			Patch(0x14F3BD, 0x90, 2).Apply();
			Hook(0x1CB4F0, c_player_traits__encode_hook).Apply();
			Hook(0x1CAEB0, c_player_traits__decode_hook).Apply();
			Hook(0x1CD360, c_player_traits__initialize_hook).Apply();
			Hook(0x1CCD30, c_player_traits__set_hook).Apply();
			Hook(0x1CAD20, c_player_trait_shield_vitality__decode_hook).Apply();
			Hook(0x1CB1D0, c_player_trait_shield_vitality__encode_hook).Apply();
			Hook(0x1CADB0, c_player_trait_weapons__decode_hook).Apply();
			Hook(0x1CB320, c_player_trait_weapons__encode_hook).Apply();
			Hook(0x1CAC80, c_player_trait_movement__decode_hook).Apply();
			Hook(0x1CB060, c_player_trait_movement__encode_hook).Apply();
			Hook(0x1CAC10, c_player_trait_appearance__decode_hook).Apply();
			Hook(0x1CAF50, c_player_trait_appearance__encode_hook).Apply();
			Hook(0x1CACE0, c_player_trait_sensors__decode_hook).Apply();
			Hook(0x1CB130, c_player_trait_sensors__encode_hook).Apply();
			Hook(0x1CC940, c_player_trait_shield_vitality__set_hook).Apply();
			Hook(0x1CCB30, c_player_trait_weapons__set_hook).Apply();
			Hook(0x1CC770, c_player_trait_movement__set_hook).Apply();
			Hook(0x1CC670, c_player_trait_appearance__set_hook).Apply();
			Hook(0x1CC830, c_player_trait_sensors__set_hook).Apply();
			Patch::NopFill(0xB0C7D9, 6);
			Patch::NopFill(0xB0B603, 2);
			Patch::NopFill(0xB0DFFF, 2);
			Patch::NopFill(0x5CC9D6, 4);
			Patch::NopFill(0x5CC9DA, 3);
			Patch::NopFill(0x5CC9EB, 4);
			Patch::NopFill(0x5CC9EF, 3);
			Patch::NopFill(0x5CB91B, 4);
			Patch::NopFill(0x5CBB38, 4);
			Hook(0x1CC001, game_engine_apply_player_traits_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x1CBFF7, game_engine_apply_respawn_traits_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x1CBFED, game_engine_apply_powerup_traits_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x71FBC0, game_variant_get_parameter_type_for_category_hook).Apply();
			Hook(0x1799EB, c_game_variant__get_game_engine_setting_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x17A0BB, c_game_variant__get_game_engine_setting_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x18072B, c_game_variant__set_game_engine_setting_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x18093B, c_game_variant__set_game_engine_setting_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x70C86D, game_variant_get_parameter_value_type, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x71FE2A, game_variant_get_parameter_value_type, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x72001A, text_value_pair_definition_try_and_get_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x7200C4, text_value_pair_definition_try_and_get_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x720111, text_value_pair_definition_try_and_get_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x71FED8, text_value_pair_definition_try_and_get_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Pointer(0x16A50AC).Write<unsigned long>(0x0);
			Pointer(0x16A5028).Write<unsigned long>(0x0);
			Hook(0x70C975, gui_screen_game_options_set_variant_parameter_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			c_mod_system::GetModManager().AddListener(new ModListener());
		}
	}
}

/* ---------- private code */

float __fastcall c_player_health_traits__get_damage_resistance_hook(c_player_trait_shield_vitality *thisptr, void *__formal) // 0x10AA5F10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_player_health_traits__get_damage_resistance_hook@@YIMPAUc_player_trait_shield_vitality@@PAX@Z");
	// `anonymous-namespace'::c_player_health_traits__get_damage_resistance_hook
	// void *__formal;

	return thisptr->get_damage_resistance_percentage();
}

float __fastcall c_player_movement_traits__get_walking_speed_hook(c_player_trait_movement *thisptr, void *__formal) // 0x10AA5FB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_player_movement_traits__get_walking_speed_hook@@YIMPAUc_player_trait_movement@@PAX@Z");
	// `anonymous-namespace'::c_player_movement_traits__get_walking_speed_hook
	// void *__formal;

	return thisptr->get_speed();
}

float __fastcall c_player_movement_traits__get_personal_gravity_hook(c_player_trait_movement *thisptr, void *__formal) // 0x10AA5F60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_player_movement_traits__get_personal_gravity_hook@@YIMPAUc_player_trait_movement@@PAX@Z");
	// `anonymous-namespace'::c_player_movement_traits__get_personal_gravity_hook
	// void *__formal;

	return thisptr->get_gravity();
}

void __fastcall c_player_traits__encode_hook(c_player_traits &traits, void *unused, c_bitstream *stream) // 0x10AA6600
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_player_traits__encode_hook@@YIXAAUc_player_traits@@PAXPAVc_bitstream@@@Z");
	// `anonymous-namespace'::c_player_traits__encode_hook
	// c_bitstream *stream;

	traits.encode(stream);
}

void __fastcall c_player_traits__decode_hook(c_player_traits &traits, void *unused, c_bitstream *stream) // 0x10AA65A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_player_traits__decode_hook@@YIXAAUc_player_traits@@PAXPAVc_bitstream@@@Z");
	// `anonymous-namespace'::c_player_traits__decode_hook
	// c_bitstream *stream;

	traits.decode(stream);
}

void __fastcall c_player_trait_shield_vitality__encode_hook(c_player_trait_shield_vitality *traits, void *unused, c_bitstream *stream) // 0x10AA63C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_player_trait_shield_vitality__encode_hook@@YIXPAUc_player_trait_shield_vitality@@PAXPAVc_bitstream@@@Z");
	// `anonymous-namespace'::c_player_trait_shield_vitality__encode_hook
	// c_bitstream *stream;

	traits->encode(stream);
}

void __fastcall c_player_trait_shield_vitality__decode_hook(c_player_trait_shield_vitality *traits, void *unused, c_bitstream *stream) // 0x10AA6360
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_player_trait_shield_vitality__decode_hook@@YIXPAUc_player_trait_shield_vitality@@PAXPAVc_bitstream@@@Z");
	// `anonymous-namespace'::c_player_trait_shield_vitality__decode_hook
	// c_bitstream *stream;

	traits->decode(stream);
}

void __fastcall c_player_trait_weapons__encode_hook(c_player_trait_weapons &traits, void *unused, c_bitstream *stream) // 0x10AA64E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_player_trait_weapons__encode_hook@@YIXAAUc_player_trait_weapons@@PAXPAVc_bitstream@@@Z");
	// `anonymous-namespace'::c_player_trait_weapons__encode_hook
	// c_bitstream *stream;

	traits.encode(stream);
}

void __fastcall c_player_trait_weapons__decode_hook(c_player_trait_weapons &traits, void *unused, c_bitstream *stream) // 0x10AA6480
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_player_trait_weapons__decode_hook@@YIXAAUc_player_trait_weapons@@PAXPAVc_bitstream@@@Z");
	// `anonymous-namespace'::c_player_trait_weapons__decode_hook
	// c_bitstream *stream;

	traits.decode(stream);
}

void __fastcall c_player_trait_movement__encode_hook(c_player_trait_movement &traits, void *unused, c_bitstream *stream) // 0x10AA6180
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_player_trait_movement__encode_hook@@YIXAAUc_player_trait_movement@@PAXPAVc_bitstream@@@Z");
	// `anonymous-namespace'::c_player_trait_movement__encode_hook
	// c_bitstream *stream;

	traits.encode(stream);
}

void __fastcall c_player_trait_movement__decode_hook(c_player_trait_movement &traits, void *unused, c_bitstream *stream) // 0x10AA6120
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_player_trait_movement__decode_hook@@YIXAAUc_player_trait_movement@@PAXPAVc_bitstream@@@Z");
	// `anonymous-namespace'::c_player_trait_movement__decode_hook
	// c_bitstream *stream;

	traits.decode(stream);
}

void __fastcall c_player_trait_appearance__encode_hook(c_player_trait_appearance &traits, void *unused, c_bitstream *stream) // 0x10AA6060
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_player_trait_appearance__encode_hook@@YIXAAUc_player_trait_appearance@@PAXPAVc_bitstream@@@Z");
	// `anonymous-namespace'::c_player_trait_appearance__encode_hook
	// c_bitstream *stream;

	traits.encode(stream);
}

void __fastcall c_player_trait_appearance__decode_hook(c_player_trait_appearance &traits, void *unused, c_bitstream *stream) // 0x10AA6000
{
	// `anonymous-namespace'::c_player_trait_appearance__decode_hook
	// c_bitstream *stream;

	traits.decode(stream);
}

void __fastcall c_player_trait_sensors__encode_hook(c_player_trait_sensors &traits, void *unused, c_bitstream *stream) // 0x10AA62A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_player_trait_sensors__encode_hook@@YIXAAUc_player_trait_sensors@@PAXPAVc_bitstream@@@Z");
	// `anonymous-namespace'::c_player_trait_sensors__encode_hook
	// c_bitstream *stream;

	traits.encode(stream);
}

void __fastcall c_player_trait_sensors__decode_hook(c_player_trait_sensors &traits, void *unused, c_bitstream *stream) // 0x10AA6240
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_player_trait_sensors__decode_hook@@YIXAAUc_player_trait_sensors@@PAXPAVc_bitstream@@@Z");
	// `anonymous-namespace'::c_player_trait_sensors__decode_hook
	// c_bitstream *stream;

	traits.decode(stream);
}

void __fastcall c_player_traits__initialize_hook(c_player_traits *thisptr) // 0x10AA6660
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_player_traits__initialize_hook@@YIXPAUc_player_traits@@@Z");
	// `anonymous-namespace'::c_player_traits__initialize_hook
	// c_player_traits *thisptr;

	thisptr->initialize();
}

void __fastcall c_player_traits__set_hook(c_player_traits *thisptr, void *__formal, c_player_traits *traits, bool can_inherit) // 0x10AA66B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_player_traits__set_hook@@YIXPAUc_player_traits@@PAX0_N@Z");
	// `anonymous-namespace'::c_player_traits__set_hook
	// bool can_inherit;

	thisptr->set(traits, can_inherit);
}

void __fastcall c_player_trait_shield_vitality__set_hook(c_player_trait_shield_vitality *thisptr, void *__formal, c_player_trait_shield_vitality const *traits, bool can_inherit) // 0x10AA6420
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_player_trait_shield_vitality__set_hook@@YIXPAUc_player_trait_shield_vitality@@PAXPBU1@_N@Z");
	// `anonymous-namespace'::c_player_trait_shield_vitality__set_hook
	// bool can_inherit;

	thisptr->set(traits, can_inherit);
}

void __fastcall c_player_trait_weapons__set_hook(c_player_trait_weapons *thisptr, void *__formal, c_player_trait_weapons const *traits, bool can_inherit) // 0x10AA6540
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_player_trait_weapons__set_hook@@YIXPAUc_player_trait_weapons@@PAXPBU1@_N@Z");
	// `anonymous-namespace'::c_player_trait_weapons__set_hook
	// bool can_inherit;

	thisptr->set(traits, can_inherit);
}

void __fastcall c_player_trait_movement__set_hook(c_player_trait_movement *thisptr, void *__formal, c_player_trait_movement const *traits, bool can_inherit) // 0x10AA61E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_player_trait_movement__set_hook@@YIXPAUc_player_trait_movement@@PAXPBU1@_N@Z");
	// `anonymous-namespace'::c_player_trait_movement__set_hook
	// bool can_inherit;

	thisptr->set(traits, can_inherit);
}

void __fastcall c_player_trait_appearance__set_hook(c_player_trait_appearance *thisptr, void *__formal, c_player_trait_appearance const *traits, bool can_inherit) // 0x10AA60C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_player_trait_appearance__set_hook@@YIXPAUc_player_trait_appearance@@PAXPBU1@_N@Z");
	// `anonymous-namespace'::c_player_trait_appearance__set_hook
	// bool can_inherit;

	thisptr->set(traits, can_inherit);
}

void __fastcall c_player_trait_sensors__set_hook(c_player_trait_sensors *thisptr, void *__formal, c_player_trait_sensors const *traits, bool can_inherit) // 0x10AA6300
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_player_trait_sensors__set_hook@@YIXPAUc_player_trait_sensors@@PAXPBU1@_N@Z");
	// `anonymous-namespace'::c_player_trait_sensors__set_hook
	// bool can_inherit;

	thisptr->set(traits, can_inherit);
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

long game_variant_get_parameter_value_type(long parameter_type) // 0x10AA7790
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_variant_get_parameter_value_type@@YAJJ@Z");
	// `anonymous-namespace'::game_variant_get_parameter_value_type
	// long parameter_type;
	// constexpr long (*const `game_variant_get_parameter_value_type'::`2'::game_variant_get_parameter_value_type)(long); // constant == 5716384
	// bool extended;
	// function call : long (*const)(long)

	bool valid = parameter_type >= 626;

	if (valid && parameter_type >= 627)
	{
		return 0;
	}

	return ((long(__cdecl *)(long))0x5739a0)(parameter_type);
}

_extern bool _sub_10AA3BC0(c_game_variant *, void *, e_game_variant_parameter, char, unsigned long *);
bool __fastcall c_game_variant__get_game_engine_setting_hook(c_game_variant *thisptr, void *unused, e_game_variant_parameter parameter_type, char value_type, unsigned long *out_value) // 0x10AA3BC0
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
bool __fastcall c_game_variant__set_game_engine_setting_hook(c_game_variant *thisptr, void *unused, long parameter_type, char value_type, unsigned long value) // 0x10AA4A10
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

long c_gui_screen_game_options__get_category_index(c_gui_screen_game_options *screen) // 0x10AA5C10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_gui_screen_game_options__get_category_index@@YAJPAUc_gui_screen_game_options@@@Z");
	// `anonymous-namespace'::c_gui_screen_game_options__get_category_index
	// c_gui_screen_game_options *screen;
	// long index;
	// long category_index;

	long result = -1;
	long index = *(long *)((char *)screen + 0x202C);
	if (index < 0 || index >= 16)
		result = -1;
	else
		result = *(long *)((char *)screen + 12 * index + 0x1F6C);
	return result;
}

long c_gui_screen_game_options__get_parameter_type_for_current_category(c_gui_screen_game_options *screen, long parameter_type) // 0x10AA5C80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_gui_screen_game_options__get_parameter_type_for_current_category@@YAJPAUc_gui_screen_game_options@@J@Z");
	// `anonymous-namespace'::c_gui_screen_game_options__get_parameter_type_for_current_category
	// long parameter_type;
	// long category_index;

	long category_index = c_gui_screen_game_options__get_category_index(screen);
	return game_variant_get_parameter_type_for_category_hook(category_index, parameter_type);
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

bool c_gui_screen_game_options__try_set_parameter_value(c_gui_screen_game_options *screen, long parameter_type, unsigned long value) // 0x10AA5E80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_gui_screen_game_options__try_set_parameter_value@@YA_NPAUc_gui_screen_game_options@@JK@Z");
	// `anonymous-namespace'::c_gui_screen_game_options__try_set_parameter_value
	// unsigned long value;
	// c_game_variant *variant;

	parameter_type = c_gui_screen_game_options__get_parameter_type_for_current_category(screen, parameter_type);
	if (parameter_type == -1)
		return false;
	c_game_variant *variant = (c_game_variant *)((char *)screen + 0x1AA0);
	return c_game_variant__set_game_engine_setting_hook(variant, nullptr, parameter_type, 0, value);
}

_inline c_user_interface_player_model_text_value_pair_proxy::c_user_interface_player_model_text_value_pair_proxy(c_user_interface_mods_player_character_data *data) // 0x10A9E910
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0c_user_interface_player_model_text_value_pair_proxy@hades_file_local@@QAE@PAVc_user_interface_mods_player_character_data@@@Z");
	// `anonymous-namespace'::c_user_interface_player_model_text_value_pair_proxy::c_user_interface_player_model_text_value_pair_proxy
	// c_user_interface_mods_player_character_data *data;

	m_data = data;
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

_inline ModListener::ModListener() = default; // 0x10A9E880

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

_inline c_user_interface_player_model_set_text_value_pair_proxy::c_user_interface_player_model_set_text_value_pair_proxy(c_user_interface_mods_player_character_data *data) // 0x10A9E8E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0c_user_interface_player_model_set_text_value_pair_proxy@hades_file_local@@QAE@PAVc_user_interface_mods_player_character_data@@@Z");
	// `anonymous-namespace'::c_user_interface_player_model_set_text_value_pair_proxy::c_user_interface_player_model_set_text_value_pair_proxy
	// c_user_interface_mods_player_character_data *data;

	m_data = data;
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
bool __fastcall c_gui_screen_game_options__get_string_value_hook(c_gui_screen_widget *thisptr, void *unused, unsigned long id, wchar_t *out_value) // 0x10AA5CF0
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

void __fastcall c_gui_screen_game_options__begin_transition_hook(c_gui_screen_game_options *thisptr) // 0x10AA5B70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_gui_screen_game_options__begin_transition_hook@@YIXPAUc_gui_screen_game_options@@@Z");
	// `anonymous-namespace'::c_gui_screen_game_options__begin_transition_hook
	// c_gui_screen_game_options *thisptr;
	// constexpr void (*const `c_gui_screen_game_options__begin_transition_hook'::`2'::c_gui_screen_widget__begin_transition)(void *); // constant == 11587296
	// function call : void (*const)(void *)

	if (g_player_model_proxy_dirty)
	{
		g_player_model_proxy_dirty = false;
		g_player_characte_data.update();
	}
	g_player_model_options_proxy.update(thisptr);
	g_player_model_set_options_proxy.update(thisptr);
	((void(__thiscall *)(c_gui_screen_game_options *))0xb0cee0)(thisptr);
}

_extern bool _sub_10AA78A0(c_game_variant *, void *, long, unsigned long);
bool __fastcall gui_screen_game_options_set_variant_parameter_hook(c_game_variant *thisptr, void *unused, long parameter_type, unsigned long value) // 0x10AA78A0
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

/* ---------- explicit instantiations */
template s_text_value_pair_definition * s_user_interface_text_value_pair_proxy<8>::get_tag_definition();
template s_text_value_pair_definition * s_user_interface_text_value_pair_proxy<16>::get_tag_definition();
