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
	namespace hades_file_local_GameEngineSettings { class ModListener; } using namespace hades_file_local_GameEngineSettings;
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
	namespace hades_file_local_GameEngineSettings { class ModListener :
		public IModListener
	{
	private:
		virtual void OnModChanged(EModIndex, IMod *);
	public:
		ModListener(ModListener &); /* compiler_generated() */
		ModListener(ModListener const &); /* compiler_generated() */
		ModListener() = default; /* compiler_generated() */
		virtual ~ModListener() = default; /* compiler_generated() */
		ModListener &operator=(ModListener &); /* compiler_generated() */
		ModListener &operator=(ModListener const &); /* compiler_generated() */
	}; }  // hades_file_local_GameEngineSettings: ModListener is a different class in each translation unit
	static_assert(sizeof(ModListener) == 4, "Invalid ModListener size");
}
using namespace hades_file_local;
/* ---------- prototypes */

namespace eldorado
{
	// Functions in eldorado.exe, named as in ManagedDonkey.
	static auto const simulation_action_game_engine_player_update = reinterpret_cast<void (*)(short, unsigned long long const *)>(0x4B26B0);
}

s_game_globals *game_globals_get();  // hades: added for 0x10AA7A20
extern void *(*const tag_get)(unsigned long, long);  // hades: added for 0x10AA7A20

extern long (*const game_time_get)();  // hades: added for 0x10AA6AB0
extern float (*const game_ticks_to_seconds)(float);  // hades: added for 0x10AA6AB0

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

extern c_game_variant *(*const game_engine_get_variant)(); // 0x11248CB0

/* ---------- private variables */

namespace hades_file_local
{
	extern bool g_player_model_proxy_dirty; // 0x113547A0
	extern c_user_interface_mods_player_character_data g_player_characte_data; // 0x12464BA8
	c_user_interface_player_model_text_value_pair_proxy g_player_model_options_proxy(&g_player_characte_data); // 0x124648E8
	c_user_interface_player_model_set_text_value_pair_proxy g_player_model_set_options_proxy(&g_player_characte_data); // 0x12464A48
}
using namespace hades_file_local;
/* ---------- public code */

namespace Patches
{
	namespace GameEngineSettings
	{

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
			Pointer(0x16A50AC).Write<unsigned long>(reinterpret_cast<unsigned long>(c_gui_screen_game_options__get_string_value_hook));
			Pointer(0x16A5028).Write<unsigned long>(reinterpret_cast<unsigned long>(c_gui_screen_game_options__begin_transition_hook));
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

void game_engine_apply_extended_traits(long player_index, c_player_trait_extended const *traits) // 0x10AA6710
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_engine_apply_extended_traits@@YAXJPBUc_player_trait_extended@@@Z");
	// `anonymous-namespace'::game_engine_apply_extended_traits
	// static ...; // 0x10AA68E0
	// static ...; // 0x10AA68D8
	// long player_index;
	// c_player_trait_extended const *traits;
	// s_player_datum *player;
	// bool changed;
		// unsigned long long const update_mask;
	// function call : void (*const)(short, unsigned long long const *)

	bool changed = false;
	s_player_datum *player = player_get(player_index);
	if (!player)
		return;
	if (player->traits.extended.player_model != traits->player_model)
	{
		player->traits.extended.set_player_model_absolute_index(traits->player_model, false);
		changed = true;
	}
	if (player->traits.extended.player_model_set != traits->player_model_set)
	{
		player->traits.extended.set_player_model_set_absolute_index(traits->player_model_set, false);
		changed = true;
	}
	if (player->traits.extended.sprint_allowed != traits->sprint_allowed)
	{
		player->traits.extended.set_sprint_setting((c_player_trait_extended::e_sprint_setting)traits->sprint_allowed, false);
		changed = true;
	}
	if (player->traits.extended.use_third_person_camera != traits->use_third_person_camera)
	{
		player->traits.extended.set_third_person_camera_setting((c_player_trait_extended::e_third_person_camera)traits->use_third_person_camera, false);
		changed = true;
	}
	if (changed)
	{
		unsigned long long const update_mask = 0x100000;
		eldorado::simulation_action_game_engine_player_update((short)player_index, &update_mask);
	}
}

void try_force_weapon_set(s_player_datum *player, c_player_trait_weapons const *traits) // 0x10AA7A20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?try_force_weapon_set@@YAXPAUs_player_datum@@PBUc_player_trait_weapons@@@Z");
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
		// long secondary_tag_index;
		// char pickup_value;
		// long primary_tag_index;
	// function call : bool (*const)()
	// function call : void *(*const)(unsigned long, long)
	// function call : long (*const)(short, long)
	// function call : long (*const)(short, long)
	// function call : void (*const)(long)
	// function call : __int32 (*const)(long, long, long)
	// function call : __int32 (*const)(long, long, long)

	long (*const game_engine_weapon_item_definition_index_from_absolute_weapons_selection_block_index)(short, long) = reinterpret_cast<long (*)(short, long)>(0x5CECD0);
	unsigned long unit_index = player->unit_index;
	if (!player || unit_index == -1)
		return;
	if (player->game_engine_vehicle_use_timer != -1 || ((bool (*)())0x531B20)())
		return;
	s_game_globals *game_globals = game_globals_get();
	s_multiplayer_globals_definition *multiplayer_globals = (s_multiplayer_globals_definition *)tag_get('mulg', game_globals->MultiplayerGlobals.index);
	c_tag_block<s_multiplayer_universal_globals_definition> universal = multiplayer_globals->universal;
	if (universal.count > 0 && universal->weapons.count > 0)
	{
		long primary_tag_index = game_engine_weapon_item_definition_index_from_absolute_weapons_selection_block_index(traits->initial_primary_weapon, 0);
		long secondary_tag_index = game_engine_weapon_item_definition_index_from_absolute_weapons_selection_block_index(traits->initial_secondary_weapon, 1);
		char pickup_value = player->traits.weapons.weapon_pickup;
		player->traits.weapons.weapon_pickup = 1;
		((void (*)(unsigned long))0xB3FAD0)(unit_index);
		if (primary_tag_index != -1)
			((void (*)(unsigned long, long, long))0x5CE210)(unit_index, primary_tag_index, 0);
		if (secondary_tag_index != -1)
			((void (*)(unsigned long, long, long))0x5CE210)(unit_index, secondary_tag_index, 0);
		player->traits.weapons.weapon_pickup = pickup_value;
	}
}

void game_engine_apply_weapons_traits_new(long player_index, c_player_trait_weapons const *traits) // 0x10AA6D70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_engine_apply_weapons_traits_new@@YAXJPBUc_player_trait_weapons@@@Z");
	// `anonymous-namespace'::game_engine_apply_weapons_traits_new
	// c_player_trait_weapons const *traits;
	// s_player_datum *player;
	// void (*const game_engine_apply_weapons_traits)(long, c_player_trait_weapons const *);
	// short (*const weapon_get_multiplayer_type)(long);
	// char og_init_primary;
	// char og_init_secondary;
		// unsigned long support_weapon_index;
	// function call : void (*const)(long, c_player_trait_weapons const *)
	// function call : char (*const)()
	// function call : bool (*const)(long, long *, long *)
	// function call : long (*const)(long, short)
	// function call : short (*const)(long)

	void (*const game_engine_apply_weapons_traits)(long, c_player_trait_weapons const *) = reinterpret_cast<void (*)(long, c_player_trait_weapons const *)>(0x5CBE20);
	short (*const weapon_get_multiplayer_type)(long) = reinterpret_cast<short (*)(long)>(0xB62DB0);
	s_player_datum *player = player_get(player_index);
	char og_init_primary = player->traits.weapons.initial_primary_weapon;
	char og_init_secondary = player->traits.weapons.initial_secondary_weapon;
	game_engine_apply_weapons_traits(player_index, traits);
	if (player->dead_timer || ((char (*)())0x5670E0)() || ((bool (*)(long, long *, long *))0x59A6F0)(player_index, nullptr, nullptr))
		return;
	if (og_init_primary != traits->initial_primary_weapon || og_init_secondary != traits->initial_secondary_weapon)
	{
		if (player->unit_index != -1)
		{
			unsigned long support_weapon_index = ((unsigned long (*)(long, long))0xB454D0)(player->unit_index, 2);
			if (support_weapon_index != -1 && weapon_get_multiplayer_type(support_weapon_index))
				return;
		}
		try_force_weapon_set(player, traits);
	}
}

void game_engine_apply_player_traits_hook(long player_index, c_player_traits const *traits) // 0x10AA6980
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_engine_apply_player_traits_hook@@YAXJPBUc_player_traits@@@Z");
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

	const auto game_engine_apply_vitality_traits = (void(*)(long, c_player_trait_shield_vitality const *))0x5CBD30;
	const auto game_engine_apply_weapons_traits = (void(*)(long, c_player_trait_weapons const *))0x5CBE20;
	const auto game_engine_apply_movement_traits = (void(*)(long, c_player_trait_movement const *))0x5CB6D0;
	const auto game_engine_apply_appearance_trait = (void(*)(long, c_player_trait_appearance const *))0x5CB530;
	const auto game_engine_apply_sensors_traits = (void(*)(long, c_player_trait_sensors const *))0x5CBC90;

	game_engine_apply_vitality_traits(player_index, &traits->vitality);
	game_engine_apply_extended_traits(player_index, &traits->extended);
	game_engine_apply_weapons_traits_new(player_index, &traits->weapons);
	game_engine_apply_movement_traits(player_index, &traits->movement);
	game_engine_apply_appearance_trait(player_index, &traits->appearance);
	game_engine_apply_sensors_traits(player_index, &traits->sensors);
}

void game_engine_apply_respawn_traits_hook(long player_index, c_player_traits *traits) // 0x10AA6C90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_engine_apply_respawn_traits_hook@@YAXJPAUc_player_traits@@@Z");
	// `anonymous-namespace'::game_engine_apply_respawn_traits_hook
	// c_player_traits *traits;
	// s_player_datum *player;
	// u_game_engine_variant *const variant;
	// c_game_variant *game_variant;
	// function call : c_game_variant *(*const)()

	c_game_variant *game_variant = game_engine_get_variant();
	s_player_datum *player = player_get(player_index);
	if (!game_variant || !player)
		return;

	u_game_engine_variant *const variant = (u_game_engine_variant *)game_variant->storage;
	if (variant->base.respawn_options.respawn_traits_duration > 0 && player->respawn_duration_seconds > 0 && !player->first_spawn && (player->flags & 8) == 0)
	{
		traits->set(&variant->base.respawn_options.player_traits, false);
	}
}

void game_engine_apply_powerup_traits_hook(long player_index, c_player_traits *traits) // 0x10AA6AB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_engine_apply_powerup_traits_hook@@YAXJPAUc_player_traits@@@Z");
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
		// long i;
		// c_player_traits desired_traits;
	// function call : long (*const)()
	// function call : float (*const)(float)
	// function call : float (*const)(unsigned char)
	// function call : void (*const)(unsigned char, c_player_traits *)

	static float (*const game_get_powerup_duration_in_seconds)(unsigned char) = reinterpret_cast<float (*)(unsigned char)>(0x765D60);
	static void (*const game_engine_get_variant_powerup_traits)(unsigned char, c_player_traits *) = reinterpret_cast<void (*)(unsigned char, c_player_traits *)>(0x765DE0);
	s_player_datum *player = player_get(player_index);
	long most_recent_pickup_time = 0;
	long powerup_flavor = -1;
	for (long i = 0; i < 3; i++)
	{
		if (player->powerup_pickup_times[i] > most_recent_pickup_time)
		{
			most_recent_pickup_time = player->powerup_pickup_times[i];
			powerup_flavor = i;
		}
	}
	if (powerup_flavor == -1)
		return;
	long seconds_active = (long)game_ticks_to_seconds((float)(game_time_get() - most_recent_pickup_time));
	if (game_get_powerup_duration_in_seconds((unsigned char)powerup_flavor) >= seconds_active)
	{
		c_player_traits desired_traits;
		game_engine_get_variant_powerup_traits((unsigned char)powerup_flavor, &desired_traits);
		traits->set(&desired_traits, false);
	}
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

bool __fastcall c_game_variant__get_game_engine_setting_hook(c_game_variant *thisptr, void *unused, e_game_variant_parameter parameter_type, char value_type, unsigned long *out_value) // 0x10AA3BC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_game_variant__get_game_engine_setting_hook@@YI_NPAUc_game_variant@@PAXW4e_game_variant_parameter@@DPAK@Z");
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

	u_game_engine_variant *const variant = (u_game_engine_variant *)thisptr->storage;
	switch (parameter_type)
	{
	case _game_variant_parameter__extended__base_traits_player_model:
		*out_value = variant->base.map_override_options.base_player_traits.extended.player_model;
		return true;
	case _game_variant_parameter__extended__respawn_traits_player_model:
		*out_value = variant->base.respawn_options.player_traits.extended.player_model;
		return true;
	case _game_variant_parameter__extended__red_traits_player_model:
		*out_value = variant->base.map_override_options.red_traits.extended.player_model;
		return true;
	case _game_variant_parameter__extended__blue_traits_player_model:
		*out_value = variant->base.map_override_options.blue_traits.extended.player_model;
		return true;
	case _game_variant_parameter__extended__yellow_traits_player_model:
		*out_value = variant->base.map_override_options.yellow_traits.extended.player_model;
		return true;
	case _game_variant_parameter__extended__slayer_leader_traits_player_model:
		*out_value = variant->slayer.leader_traits.extended.player_model;
		return true;
	case _game_variant_parameter__extended__oddball_carrier_traits_player_model:
		*out_value = variant->oddball.ball_carrier_traits.extended.player_model;
		return true;
	case _game_variant_parameter__extended__assault_carrier_traits_player_model:
		*out_value = variant->assault.bomb_carrier_traits.extended.player_model;
		return true;
	case _game_variant_parameter__extended__ctf_carrier_traits_player_model:
		*out_value = variant->ctf.flag_carrier_traits.extended.player_model;
		return true;
	case _game_variant_parameter__extended__juggernaut_carrier_traits_player_model:
		*out_value = variant->juggernaut.juggernaut_traits.extended.player_model;
		return true;
	case _game_variant_parameter__extended__koth_hill_traits_player_model:
		*out_value = variant->koth.hill_traits.extended.player_model;
		return true;
	case _game_variant_parameter__extended__infection_zombie_traits_player_model:
		*out_value = variant->infection.infected_traits.extended.player_model;
		return true;
	case _game_variant_parameter__extended__infection_alpha_zombie_traits_player_model:
		*out_value = variant->infection.alpha_traits.extended.player_model;
		return true;
	case _game_variant_parameter__extended__infection_haven_traits_player_model:
		*out_value = variant->infection.haven_traits.extended.player_model;
		return true;
	case _game_variant_parameter__extended__infection_last_man_standing_traits_player_model:
		*out_value = variant->infection.last_man_standing_traits.extended.player_model;
		return true;
	case _game_variant_parameter__extended__territories_defender_traits_player_model:
		*out_value = variant->territories.defender_traits.extended.player_model;
		return true;
	case _game_variant_parameter__extended__territories_attacker_traits_player_model:
		*out_value = variant->territories.attacker_traits.extended.player_model;
		return true;
	case _game_variant_parameter__extended__vip_defender_traits_player_model:
		*out_value = variant->vip.vip_team_traits.extended.player_model;
		return true;
	case _game_variant_parameter__extended__vip_influence_traits_player_model:
		*out_value = variant->vip.vip_proximity_traits.extended.player_model;
		return true;
	case _game_variant_parameter__extended__vip_vip_traits_player_model:
		*out_value = variant->vip.vip_traits.extended.player_model;
		return true;
	case _game_variant_parameter__extended__editor_traits_player_model:
		*out_value = variant->sandbox.editor_traits.extended.player_model;
		return true;
	case _game_variant_parameter__extended__base_traits_player_model_set:
		*out_value = variant->base.map_override_options.base_player_traits.extended.player_model_set;
		return true;
	case _game_variant_parameter__extended__respawn_traits_player_model_set:
		*out_value = variant->base.respawn_options.player_traits.extended.player_model_set;
		return true;
	case _game_variant_parameter__extended__red_traits_player_model_set:
		*out_value = variant->base.map_override_options.red_traits.extended.player_model_set;
		return true;
	case _game_variant_parameter__extended__blue_traits_player_model_set:
		*out_value = variant->base.map_override_options.blue_traits.extended.player_model_set;
		return true;
	case _game_variant_parameter__extended__yellow_traits_player_model_set:
		*out_value = variant->base.map_override_options.yellow_traits.extended.player_model_set;
		return true;
	case _game_variant_parameter__extended__slayer_leader_traits_player_model_set:
		*out_value = variant->slayer.leader_traits.extended.player_model_set;
		return true;
	case _game_variant_parameter__extended__oddball_carrier_traits_player_model_set:
		*out_value = variant->oddball.ball_carrier_traits.extended.player_model_set;
		return true;
	case _game_variant_parameter__extended__assault_carrier_traits_player_model_set:
		*out_value = variant->assault.bomb_carrier_traits.extended.player_model_set;
		return true;
	case _game_variant_parameter__extended__ctf_carrier_traits_player_model_set:
		*out_value = variant->ctf.flag_carrier_traits.extended.player_model_set;
		return true;
	case _game_variant_parameter__extended__juggernaut_carrier_traits_player_model_set:
		*out_value = variant->juggernaut.juggernaut_traits.extended.player_model_set;
		return true;
	case _game_variant_parameter__extended__koth_hill_traits_player_model_set:
		*out_value = variant->koth.hill_traits.extended.player_model_set;
		return true;
	case _game_variant_parameter__extended__infection_zombie_traits_player_model_set:
		*out_value = variant->infection.infected_traits.extended.player_model_set;
		return true;
	case _game_variant_parameter__extended__infection_alpha_zombie_traits_player_model_set:
		*out_value = variant->infection.alpha_traits.extended.player_model_set;
		return true;
	case _game_variant_parameter__extended__infection_haven_traits_player_model_set:
		*out_value = variant->infection.haven_traits.extended.player_model_set;
		return true;
	case _game_variant_parameter__extended__infection_last_man_standing_traits_player_model_set:
		*out_value = variant->infection.last_man_standing_traits.extended.player_model_set;
		return true;
	case _game_variant_parameter__extended__territories_defender_traits_player_model_set:
		*out_value = variant->territories.defender_traits.extended.player_model_set;
		return true;
	case _game_variant_parameter__extended__territories_attacker_traits_player_model_set:
		*out_value = variant->territories.attacker_traits.extended.player_model_set;
		return true;
	case _game_variant_parameter__extended__vip_defender_traits_player_model_set:
		*out_value = variant->vip.vip_team_traits.extended.player_model_set;
		return true;
	case _game_variant_parameter__extended__vip_influence_traits_player_model_set:
		*out_value = variant->vip.vip_proximity_traits.extended.player_model_set;
		return true;
	case _game_variant_parameter__extended__vip_vip_traits_player_model_set:
		*out_value = variant->vip.vip_traits.extended.player_model_set;
		return true;
	case _game_variant_parameter__extended__editor_traits_player_model_set:
		*out_value = variant->sandbox.editor_traits.extended.player_model_set;
		return true;
	case _game_variant_parameter__extended__base_traits_sprint_allowed:
		*out_value = variant->base.map_override_options.base_player_traits.extended.sprint_allowed;
		return true;
	case _game_variant_parameter__extended__respawn_traits_sprint_allowed:
		*out_value = variant->base.respawn_options.player_traits.extended.sprint_allowed;
		return true;
	case _game_variant_parameter__extended__red_traits_sprint_allowed:
		*out_value = variant->base.map_override_options.red_traits.extended.sprint_allowed;
		return true;
	case _game_variant_parameter__extended__blue_traits_sprint_allowed:
		*out_value = variant->base.map_override_options.blue_traits.extended.sprint_allowed;
		return true;
	case _game_variant_parameter__extended__yellow_traits_sprint_allowed:
		*out_value = variant->base.map_override_options.yellow_traits.extended.sprint_allowed;
		return true;
	case _game_variant_parameter__extended__slayer_leader_traits_sprint_allowed:
		*out_value = variant->slayer.leader_traits.extended.sprint_allowed;
		return true;
	case _game_variant_parameter__extended__oddball_carrier_traits_sprint_allowed:
		*out_value = variant->oddball.ball_carrier_traits.extended.sprint_allowed;
		return true;
	case _game_variant_parameter__extended__assault_carrier_traits_sprint_allowed:
		*out_value = variant->assault.bomb_carrier_traits.extended.sprint_allowed;
		return true;
	case _game_variant_parameter__extended__ctf_carrier_traits_sprint_allowed:
		*out_value = variant->ctf.flag_carrier_traits.extended.sprint_allowed;
		return true;
	case _game_variant_parameter__extended__juggernaut_carrier_traits_sprint_allowed:
		*out_value = variant->juggernaut.juggernaut_traits.extended.sprint_allowed;
		return true;
	case _game_variant_parameter__extended__koth_hill_traits_sprint_allowed:
		*out_value = variant->koth.hill_traits.extended.sprint_allowed;
		return true;
	case _game_variant_parameter__extended__infection_zombie_traits_sprint_allowed:
		*out_value = variant->infection.infected_traits.extended.sprint_allowed;
		return true;
	case _game_variant_parameter__extended__infection_alpha_zombie_traits_sprint_allowed:
		*out_value = variant->infection.alpha_traits.extended.sprint_allowed;
		return true;
	case _game_variant_parameter__extended__infection_haven_traits_sprint_allowed:
		*out_value = variant->infection.haven_traits.extended.sprint_allowed;
		return true;
	case _game_variant_parameter__extended__infection_last_man_standing_traits_sprint_allowed:
		*out_value = variant->infection.last_man_standing_traits.extended.sprint_allowed;
		return true;
	case _game_variant_parameter__extended__territories_defender_traits_sprint_allowed:
		*out_value = variant->territories.defender_traits.extended.sprint_allowed;
		return true;
	case _game_variant_parameter__extended__territories_attacker_traits_sprint_allowed:
		*out_value = variant->territories.attacker_traits.extended.sprint_allowed;
		return true;
	case _game_variant_parameter__extended__vip_defender_traits_sprint_allowed:
		*out_value = variant->vip.vip_team_traits.extended.sprint_allowed;
		return true;
	case _game_variant_parameter__extended__vip_influence_traits_sprint_allowed:
		*out_value = variant->vip.vip_proximity_traits.extended.sprint_allowed;
		return true;
	case _game_variant_parameter__extended__vip_vip_traits_sprint_allowed:
		*out_value = variant->vip.vip_traits.extended.sprint_allowed;
		return true;
	case _game_variant_parameter__extended__editor_traits_sprint_allowed:
		*out_value = variant->sandbox.editor_traits.extended.sprint_allowed;
		return true;
	case _game_variant_parameter__extended__base_traits_use_third_person_camera:
		*out_value = variant->base.map_override_options.base_player_traits.extended.use_third_person_camera;
		return true;
	case _game_variant_parameter__extended__respawn_traits_use_third_person_camera:
		*out_value = variant->base.respawn_options.player_traits.extended.use_third_person_camera;
		return true;
	case _game_variant_parameter__extended__red_traits_use_third_person_camera:
		*out_value = variant->base.map_override_options.red_traits.extended.use_third_person_camera;
		return true;
	case _game_variant_parameter__extended__blue_traits_use_third_person_camera:
		*out_value = variant->base.map_override_options.blue_traits.extended.use_third_person_camera;
		return true;
	case _game_variant_parameter__extended__yellow_traits_use_third_person_camera:
		*out_value = variant->base.map_override_options.yellow_traits.extended.use_third_person_camera;
		return true;
	case _game_variant_parameter__extended__slayer_leader_traits_use_third_person_camera:
		*out_value = variant->slayer.leader_traits.extended.use_third_person_camera;
		return true;
	case _game_variant_parameter__extended__oddball_carrier_traits_use_third_person_camera:
		*out_value = variant->oddball.ball_carrier_traits.extended.use_third_person_camera;
		return true;
	case _game_variant_parameter__extended__assault_carrier_traits_use_third_person_camera:
		*out_value = variant->assault.bomb_carrier_traits.extended.use_third_person_camera;
		return true;
	case _game_variant_parameter__extended__ctf_carrier_traits_use_third_person_camera:
		*out_value = variant->ctf.flag_carrier_traits.extended.use_third_person_camera;
		return true;
	case _game_variant_parameter__extended__juggernaut_carrier_traits_use_third_person_camera:
		*out_value = variant->juggernaut.juggernaut_traits.extended.use_third_person_camera;
		return true;
	case _game_variant_parameter__extended__koth_hill_traits_use_third_person_camera:
		*out_value = variant->koth.hill_traits.extended.use_third_person_camera;
		return true;
	case _game_variant_parameter__extended__infection_zombie_traits_use_third_person_camera:
		*out_value = variant->infection.infected_traits.extended.use_third_person_camera;
		return true;
	case _game_variant_parameter__extended__infection_alpha_zombie_traits_use_third_person_camera:
		*out_value = variant->infection.alpha_traits.extended.use_third_person_camera;
		return true;
	case _game_variant_parameter__extended__infection_haven_traits_use_third_person_camera:
		*out_value = variant->infection.haven_traits.extended.use_third_person_camera;
		return true;
	case _game_variant_parameter__extended__infection_last_man_standing_traits_use_third_person_camera:
		*out_value = variant->infection.last_man_standing_traits.extended.use_third_person_camera;
		return true;
	case _game_variant_parameter__extended__territories_defender_traits_use_third_person_camera:
		*out_value = variant->territories.defender_traits.extended.use_third_person_camera;
		return true;
	case _game_variant_parameter__extended__territories_attacker_traits_use_third_person_camera:
		*out_value = variant->territories.attacker_traits.extended.use_third_person_camera;
		return true;
	case _game_variant_parameter__extended__vip_defender_traits_use_third_person_camera:
		*out_value = variant->vip.vip_team_traits.extended.use_third_person_camera;
		return true;
	case _game_variant_parameter__extended__vip_influence_traits_use_third_person_camera:
		*out_value = variant->vip.vip_proximity_traits.extended.use_third_person_camera;
		return true;
	case _game_variant_parameter__extended__vip_vip_traits_use_third_person_camera:
		*out_value = variant->vip.vip_traits.extended.use_third_person_camera;
		return true;
	case _game_variant_parameter__extended__editor_traits_use_third_person_camera:
		*out_value = variant->sandbox.editor_traits.extended.use_third_person_camera;
		return true;
	default:
		if (parameter_type == _game_variant_parameter__global__base_traits_visualaura && thisptr->get_base_variant()->map_override_options.base_player_traits.appearance.aura == 1)
		{
			*out_value = 0;
			return true;
		}
		return ((bool (__thiscall *)(void *, e_game_variant_parameter, char, unsigned long *))0x574530)(thisptr, parameter_type, value_type, out_value);
	}
}

bool __fastcall c_game_variant__set_game_engine_setting_hook(c_game_variant *thisptr, void *unused, long parameter_type, char value_type, unsigned long value) // 0x10AA4A10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_game_variant__set_game_engine_setting_hook@@YI_NPAUc_game_variant@@PAXJDK@Z");
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

	u_game_engine_variant *const variant = (u_game_engine_variant *)thisptr->storage;
	switch (parameter_type)
	{
	case _game_variant_parameter__extended__base_traits_player_model:
		variant->base.map_override_options.base_player_traits.extended.player_model = value;
		return true;
	case _game_variant_parameter__extended__respawn_traits_player_model:
		variant->base.respawn_options.player_traits.extended.player_model = value;
		return true;
	case _game_variant_parameter__extended__red_traits_player_model:
		variant->base.map_override_options.red_traits.extended.player_model = value;
		return true;
	case _game_variant_parameter__extended__blue_traits_player_model:
		variant->base.map_override_options.blue_traits.extended.player_model = value;
		return true;
	case _game_variant_parameter__extended__yellow_traits_player_model:
		variant->base.map_override_options.yellow_traits.extended.player_model = value;
		return true;
	case _game_variant_parameter__extended__slayer_leader_traits_player_model:
		variant->slayer.leader_traits.extended.player_model = value;
		return true;
	case _game_variant_parameter__extended__oddball_carrier_traits_player_model:
		variant->oddball.ball_carrier_traits.extended.player_model = value;
		return true;
	case _game_variant_parameter__extended__assault_carrier_traits_player_model:
		variant->assault.bomb_carrier_traits.extended.player_model = value;
		return true;
	case _game_variant_parameter__extended__ctf_carrier_traits_player_model:
		variant->ctf.flag_carrier_traits.extended.player_model = value;
		return true;
	case _game_variant_parameter__extended__juggernaut_carrier_traits_player_model:
		variant->juggernaut.juggernaut_traits.extended.player_model = value;
		return true;
	case _game_variant_parameter__extended__koth_hill_traits_player_model:
		variant->koth.hill_traits.extended.player_model = value;
		return true;
	case _game_variant_parameter__extended__infection_zombie_traits_player_model:
		variant->infection.infected_traits.extended.player_model = value;
		return true;
	case _game_variant_parameter__extended__infection_alpha_zombie_traits_player_model:
		variant->infection.alpha_traits.extended.player_model = value;
		return true;
	case _game_variant_parameter__extended__infection_haven_traits_player_model:
		variant->infection.haven_traits.extended.player_model = value;
		return true;
	case _game_variant_parameter__extended__infection_last_man_standing_traits_player_model:
		variant->infection.last_man_standing_traits.extended.player_model = value;
		return true;
	case _game_variant_parameter__extended__territories_defender_traits_player_model:
		variant->territories.defender_traits.extended.player_model = value;
		return true;
	case _game_variant_parameter__extended__territories_attacker_traits_player_model:
		variant->territories.attacker_traits.extended.player_model = value;
		return true;
	case _game_variant_parameter__extended__vip_defender_traits_player_model:
		variant->vip.vip_team_traits.extended.player_model = value;
		return true;
	case _game_variant_parameter__extended__vip_influence_traits_player_model:
		variant->vip.vip_proximity_traits.extended.player_model = value;
		return true;
	case _game_variant_parameter__extended__vip_vip_traits_player_model:
		variant->vip.vip_traits.extended.player_model = value;
		return true;
	case _game_variant_parameter__extended__editor_traits_player_model:
		variant->sandbox.editor_traits.extended.player_model = value;
		return true;
	case _game_variant_parameter__extended__base_traits_player_model_set:
		variant->base.map_override_options.base_player_traits.extended.player_model_set = value;
		return true;
	case _game_variant_parameter__extended__respawn_traits_player_model_set:
		variant->base.respawn_options.player_traits.extended.player_model_set = value;
		return true;
	case _game_variant_parameter__extended__red_traits_player_model_set:
		variant->base.map_override_options.red_traits.extended.player_model_set = value;
		return true;
	case _game_variant_parameter__extended__blue_traits_player_model_set:
		variant->base.map_override_options.blue_traits.extended.player_model_set = value;
		return true;
	case _game_variant_parameter__extended__yellow_traits_player_model_set:
		variant->base.map_override_options.yellow_traits.extended.player_model_set = value;
		return true;
	case _game_variant_parameter__extended__slayer_leader_traits_player_model_set:
		variant->slayer.leader_traits.extended.player_model_set = value;
		return true;
	case _game_variant_parameter__extended__oddball_carrier_traits_player_model_set:
		variant->oddball.ball_carrier_traits.extended.player_model_set = value;
		return true;
	case _game_variant_parameter__extended__assault_carrier_traits_player_model_set:
		variant->assault.bomb_carrier_traits.extended.player_model_set = value;
		return true;
	case _game_variant_parameter__extended__ctf_carrier_traits_player_model_set:
		variant->ctf.flag_carrier_traits.extended.player_model_set = value;
		return true;
	case _game_variant_parameter__extended__juggernaut_carrier_traits_player_model_set:
		variant->juggernaut.juggernaut_traits.extended.player_model_set = value;
		return true;
	case _game_variant_parameter__extended__koth_hill_traits_player_model_set:
		variant->koth.hill_traits.extended.player_model_set = value;
		return true;
	case _game_variant_parameter__extended__infection_zombie_traits_player_model_set:
		variant->infection.infected_traits.extended.player_model_set = value;
		return true;
	case _game_variant_parameter__extended__infection_alpha_zombie_traits_player_model_set:
		variant->infection.alpha_traits.extended.player_model_set = value;
		return true;
	case _game_variant_parameter__extended__infection_haven_traits_player_model_set:
		variant->infection.haven_traits.extended.player_model_set = value;
		return true;
	case _game_variant_parameter__extended__infection_last_man_standing_traits_player_model_set:
		variant->infection.last_man_standing_traits.extended.player_model_set = value;
		return true;
	case _game_variant_parameter__extended__territories_defender_traits_player_model_set:
		variant->territories.defender_traits.extended.player_model_set = value;
		return true;
	case _game_variant_parameter__extended__territories_attacker_traits_player_model_set:
		variant->territories.attacker_traits.extended.player_model_set = value;
		return true;
	case _game_variant_parameter__extended__vip_defender_traits_player_model_set:
		variant->vip.vip_team_traits.extended.player_model_set = value;
		return true;
	case _game_variant_parameter__extended__vip_influence_traits_player_model_set:
		variant->vip.vip_proximity_traits.extended.player_model_set = value;
		return true;
	case _game_variant_parameter__extended__vip_vip_traits_player_model_set:
		variant->vip.vip_traits.extended.player_model_set = value;
		return true;
	case _game_variant_parameter__extended__editor_traits_player_model_set:
		variant->sandbox.editor_traits.extended.player_model_set = value;
		return true;
	case _game_variant_parameter__extended__base_traits_sprint_allowed:
		variant->base.map_override_options.base_player_traits.extended.sprint_allowed = value;
		return true;
	case _game_variant_parameter__extended__respawn_traits_sprint_allowed:
		variant->base.respawn_options.player_traits.extended.sprint_allowed = value;
		return true;
	case _game_variant_parameter__extended__red_traits_sprint_allowed:
		variant->base.map_override_options.red_traits.extended.sprint_allowed = value;
		return true;
	case _game_variant_parameter__extended__blue_traits_sprint_allowed:
		variant->base.map_override_options.blue_traits.extended.sprint_allowed = value;
		return true;
	case _game_variant_parameter__extended__yellow_traits_sprint_allowed:
		variant->base.map_override_options.yellow_traits.extended.sprint_allowed = value;
		return true;
	case _game_variant_parameter__extended__slayer_leader_traits_sprint_allowed:
		variant->slayer.leader_traits.extended.sprint_allowed = value;
		return true;
	case _game_variant_parameter__extended__oddball_carrier_traits_sprint_allowed:
		variant->oddball.ball_carrier_traits.extended.sprint_allowed = value;
		return true;
	case _game_variant_parameter__extended__assault_carrier_traits_sprint_allowed:
		variant->assault.bomb_carrier_traits.extended.sprint_allowed = value;
		return true;
	case _game_variant_parameter__extended__ctf_carrier_traits_sprint_allowed:
		variant->ctf.flag_carrier_traits.extended.sprint_allowed = value;
		return true;
	case _game_variant_parameter__extended__juggernaut_carrier_traits_sprint_allowed:
		variant->juggernaut.juggernaut_traits.extended.sprint_allowed = value;
		return true;
	case _game_variant_parameter__extended__koth_hill_traits_sprint_allowed:
		variant->koth.hill_traits.extended.sprint_allowed = value;
		return true;
	case _game_variant_parameter__extended__infection_zombie_traits_sprint_allowed:
		variant->infection.infected_traits.extended.sprint_allowed = value;
		return true;
	case _game_variant_parameter__extended__infection_alpha_zombie_traits_sprint_allowed:
		variant->infection.alpha_traits.extended.sprint_allowed = value;
		return true;
	case _game_variant_parameter__extended__infection_haven_traits_sprint_allowed:
		variant->infection.haven_traits.extended.sprint_allowed = value;
		return true;
	case _game_variant_parameter__extended__infection_last_man_standing_traits_sprint_allowed:
		variant->infection.last_man_standing_traits.extended.sprint_allowed = value;
		return true;
	case _game_variant_parameter__extended__territories_defender_traits_sprint_allowed:
		variant->territories.defender_traits.extended.sprint_allowed = value;
		return true;
	case _game_variant_parameter__extended__territories_attacker_traits_sprint_allowed:
		variant->territories.attacker_traits.extended.sprint_allowed = value;
		return true;
	case _game_variant_parameter__extended__vip_defender_traits_sprint_allowed:
		variant->vip.vip_team_traits.extended.sprint_allowed = value;
		return true;
	case _game_variant_parameter__extended__vip_influence_traits_sprint_allowed:
		variant->vip.vip_proximity_traits.extended.sprint_allowed = value;
		return true;
	case _game_variant_parameter__extended__vip_vip_traits_sprint_allowed:
		variant->vip.vip_traits.extended.sprint_allowed = value;
		return true;
	case _game_variant_parameter__extended__editor_traits_sprint_allowed:
		variant->sandbox.editor_traits.extended.sprint_allowed = value;
		return true;
	case _game_variant_parameter__extended__base_traits_use_third_person_camera:
		variant->base.map_override_options.base_player_traits.extended.use_third_person_camera = value;
		return true;
	case _game_variant_parameter__extended__respawn_traits_use_third_person_camera:
		variant->base.respawn_options.player_traits.extended.use_third_person_camera = value;
		return true;
	case _game_variant_parameter__extended__red_traits_use_third_person_camera:
		variant->base.map_override_options.red_traits.extended.use_third_person_camera = value;
		return true;
	case _game_variant_parameter__extended__blue_traits_use_third_person_camera:
		variant->base.map_override_options.blue_traits.extended.use_third_person_camera = value;
		return true;
	case _game_variant_parameter__extended__yellow_traits_use_third_person_camera:
		variant->base.map_override_options.yellow_traits.extended.use_third_person_camera = value;
		return true;
	case _game_variant_parameter__extended__slayer_leader_traits_use_third_person_camera:
		variant->slayer.leader_traits.extended.use_third_person_camera = value;
		return true;
	case _game_variant_parameter__extended__oddball_carrier_traits_use_third_person_camera:
		variant->oddball.ball_carrier_traits.extended.use_third_person_camera = value;
		return true;
	case _game_variant_parameter__extended__assault_carrier_traits_use_third_person_camera:
		variant->assault.bomb_carrier_traits.extended.use_third_person_camera = value;
		return true;
	case _game_variant_parameter__extended__ctf_carrier_traits_use_third_person_camera:
		variant->ctf.flag_carrier_traits.extended.use_third_person_camera = value;
		return true;
	case _game_variant_parameter__extended__juggernaut_carrier_traits_use_third_person_camera:
		variant->juggernaut.juggernaut_traits.extended.use_third_person_camera = value;
		return true;
	case _game_variant_parameter__extended__koth_hill_traits_use_third_person_camera:
		variant->koth.hill_traits.extended.use_third_person_camera = value;
		return true;
	case _game_variant_parameter__extended__infection_zombie_traits_use_third_person_camera:
		variant->infection.infected_traits.extended.use_third_person_camera = value;
		return true;
	case _game_variant_parameter__extended__infection_alpha_zombie_traits_use_third_person_camera:
		variant->infection.alpha_traits.extended.use_third_person_camera = value;
		return true;
	case _game_variant_parameter__extended__infection_haven_traits_use_third_person_camera:
		variant->infection.haven_traits.extended.use_third_person_camera = value;
		return true;
	case _game_variant_parameter__extended__infection_last_man_standing_traits_use_third_person_camera:
		variant->infection.last_man_standing_traits.extended.use_third_person_camera = value;
		return true;
	case _game_variant_parameter__extended__territories_defender_traits_use_third_person_camera:
		variant->territories.defender_traits.extended.use_third_person_camera = value;
		return true;
	case _game_variant_parameter__extended__territories_attacker_traits_use_third_person_camera:
		variant->territories.attacker_traits.extended.use_third_person_camera = value;
		return true;
	case _game_variant_parameter__extended__vip_defender_traits_use_third_person_camera:
		variant->vip.vip_team_traits.extended.use_third_person_camera = value;
		return true;
	case _game_variant_parameter__extended__vip_influence_traits_use_third_person_camera:
		variant->vip.vip_proximity_traits.extended.use_third_person_camera = value;
		return true;
	case _game_variant_parameter__extended__vip_vip_traits_use_third_person_camera:
		variant->vip.vip_traits.extended.use_third_person_camera = value;
		return true;
	case _game_variant_parameter__extended__editor_traits_use_third_person_camera:
		variant->sandbox.editor_traits.extended.use_third_person_camera = value;
		return true;
	default:
		return ((bool (__thiscall *)(void *, long, char, unsigned long))0x57AAB0)(thisptr, parameter_type, value_type, value);
	}
}

long game_variant_get_parameter_type_for_category_hook(long category, long parameter_type) // 0x10AA6F10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_variant_get_parameter_type_for_category_hook@@YAJJJ@Z");
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

	bool extended = parameter_type >= 626;
	if (parameter_type >= 605)
	{
		switch (category)
		{
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
			return extended ? parameter_type + 1 : parameter_type - 558;
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
		case 16:
			return extended ? parameter_type + 2 : parameter_type - 588;
		case 18:
		case 19:
		case 20:
		case 21:
		case 22:
		case 23:
			return extended ? parameter_type + 3 : parameter_type - 535;
		case 25:
		case 26:
		case 27:
		case 28:
		case 29:
		case 30:
			return extended ? parameter_type + 4 : parameter_type - 514;
		case 32:
		case 33:
		case 34:
		case 35:
		case 36:
		case 37:
			return extended ? parameter_type + 5 : parameter_type - 493;
		case 40:
		case 41:
		case 42:
		case 43:
		case 44:
		case 45:
			return extended ? parameter_type + 6 : parameter_type - 454;
		case 47:
		case 48:
		case 49:
		case 50:
		case 51:
		case 52:
			return extended ? parameter_type + 7 : parameter_type - 421;
		case 54:
		case 55:
		case 56:
		case 57:
		case 58:
		case 59:
			return extended ? parameter_type + 8 : parameter_type - 55;
		case 61:
		case 62:
		case 63:
		case 64:
		case 65:
		case 66:
			return extended ? parameter_type + 9 : parameter_type - 388;
		case 68:
		case 69:
		case 70:
		case 71:
		case 72:
		case 73:
			return extended ? parameter_type + 10 : parameter_type - 101;
		case 75:
		case 76:
		case 77:
		case 78:
		case 79:
		case 80:
			return extended ? parameter_type + 11 : parameter_type - 263;
		case 82:
		case 83:
		case 84:
		case 85:
		case 86:
		case 87:
			return extended ? parameter_type + 12 : parameter_type - 356;
		case 89:
		case 90:
		case 91:
		case 92:
		case 93:
		case 94:
			return extended ? parameter_type + 13 : parameter_type - 335;
		case 96:
		case 97:
		case 98:
		case 99:
		case 100:
		case 101:
			return extended ? parameter_type + 14 : parameter_type - 314;
		case 103:
		case 104:
		case 105:
		case 106:
		case 107:
		case 108:
			return extended ? parameter_type + 15 : parameter_type - 293;
		case 117:
		case 118:
		case 119:
		case 120:
		case 121:
		case 122:
			return extended ? parameter_type + 16 : parameter_type - 237;
		case 124:
		case 125:
		case 126:
		case 127:
		case 128:
		case 129:
			return extended ? parameter_type + 17 : parameter_type - 216;
		case 131:
		case 132:
		case 133:
		case 134:
		case 135:
		case 136:
			return extended ? parameter_type + 18 : parameter_type - 179;
		case 138:
		case 139:
		case 140:
		case 141:
		case 142:
		case 143:
			return extended ? parameter_type + 19 : parameter_type - 158;
		case 145:
		case 146:
		case 147:
		case 148:
		case 149:
		case 150:
			return extended ? parameter_type + 20 : parameter_type - 137;
		case 152:
		case 153:
		case 154:
		case 155:
		case 156:
		case 157:
			return extended ? parameter_type + 21 : parameter_type - 21;
		}
	}
	return -1;
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

bool c_gui_screen_game_options__try_and_get_parameter_value(c_gui_screen_game_options *screen, long parameter_type, unsigned long *out_value) // 0x10AA5DF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_gui_screen_game_options__try_and_get_parameter_value@@YA_NPAUc_gui_screen_game_options@@JPAK@Z");
	// `anonymous-namespace'::c_gui_screen_game_options__try_and_get_parameter_value
	// unsigned long *out_value;
	// c_game_variant *variant;


	parameter_type = c_gui_screen_game_options__get_parameter_type_for_current_category(screen, parameter_type);
	if (parameter_type == -1)
		return false;
	c_game_variant *variant = (c_game_variant *)((char *)screen + 0x1AA0);
	return c_game_variant__get_game_engine_setting_hook(variant, nullptr, (e_game_variant_parameter)parameter_type, 0, out_value);
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


_inline void c_user_interface_player_model_text_value_pair_proxy::update(c_gui_screen_game_options *screen) // 0x10AA82A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?update@c_user_interface_player_model_text_value_pair_proxy@hades_file_local@@QAEXPAUc_gui_screen_game_options@@@Z");
	// `anonymous-namespace'::c_user_interface_player_model_text_value_pair_proxy::update
	// static ...; // 0x10AA85F0
	// static ...; // 0x10AA85E8
	// c_user_interface_player_model_text_value_pair_proxy *const this;
	// c_gui_screen_game_options *screen;
	// s_game_globals *game_globals;
	// s_multiplayer_globals_definition *multiplayer_globals;
		// unsigned long character_set_trait_value;
			// long character_index;
				// long i;
	// function call : void *(*const)(unsigned long, long)

	s_game_globals *game_globals = game_globals_get();
	s_multiplayer_globals_definition *multiplayer_globals = (s_multiplayer_globals_definition *)tag_get('mulg', game_globals->MultiplayerGlobals.index);
	m_values_count = 0;
	if (m_data->player_characters_count > 0)
	{
		unsigned long character_set_trait_value;
		if (!c_gui_screen_game_options__try_and_get_parameter_value(screen, 648, &character_set_trait_value))
			return;
		if (character_set_trait_value >= 8)
			return;
		if (character_set_trait_value != 2)
		{
			m_values[m_values_count].name = 66476;
			m_values[m_values_count++].integer_value = 0;
		}
		if (character_set_trait_value > 2)
		{
			m_values[m_values_count].name = 262147;
			m_values[m_values_count++].integer_value = 2;
			long character_index = 3;
			for (long i = 0; i < m_data->player_characters_count && m_values_count < 16; i++)
			{
				if (m_data->player_characters[i].character_set_index != character_set_trait_value - 3)
					continue;
				m_values[m_values_count].name = m_data->player_characters[i].name;
				m_values[m_values_count++].integer_value = character_index++;
			}
		}
	}
	else
	{
		m_values[m_values_count].name = 66476;
		m_values[m_values_count++].integer_value = 0;
	}
	m_tag_definition.values.count = m_values_count;
	m_tag_definition.values.address = &m_values[0];
}


_inline bool c_user_interface_player_model_text_value_pair_proxy::try_get_string(unsigned long id, wchar_t *out_value) // 0x10AA7DF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?try_get_string@c_user_interface_player_model_text_value_pair_proxy@hades_file_local@@QAE_NKPA_W@Z");
	// `anonymous-namespace'::c_user_interface_player_model_text_value_pair_proxy::try_get_string
	// static ...; // 0x10AA7F1C
	// c_user_interface_player_model_text_value_pair_proxy *const this;
	// unsigned long id;
	// wchar_t *out_value;
		// long i;
			// unsigned __int32 nc;

	if (id == 0)
	{
		wcsncpy_s(out_value, 1024, L"NOT AVAILABLE", _TRUNCATE);
		return true;
	}
	if (id == 1)
	{
		wcsncpy_s(out_value, 1024, L"DEFAULT", _TRUNCATE);
		return true;
	}
	for (long i = 0; i < m_data->player_characters_count; i++)
	{
		if (m_data->player_characters[i].name == id)
		{
			unsigned __int32 nc;
			mbstowcs_s(&nc, out_value, 1024, m_data->player_characters[i].display_name.ascii, _TRUNCATE);
			return true;
		}
	}
	return false;
}

_inline c_user_interface_player_model_set_text_value_pair_proxy::c_user_interface_player_model_set_text_value_pair_proxy(c_user_interface_mods_player_character_data *data) // 0x10A9E8E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0c_user_interface_player_model_set_text_value_pair_proxy@hades_file_local@@QAE@PAVc_user_interface_mods_player_character_data@@@Z");
	// `anonymous-namespace'::c_user_interface_player_model_set_text_value_pair_proxy::c_user_interface_player_model_set_text_value_pair_proxy
	// c_user_interface_mods_player_character_data *data;

	m_data = data;
}

_inline void c_user_interface_player_model_set_text_value_pair_proxy::update(c_gui_screen_game_options *screen) // 0x10AA7F90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?update@c_user_interface_player_model_set_text_value_pair_proxy@hades_file_local@@QAEXPAUc_gui_screen_game_options@@@Z");
	// `anonymous-namespace'::c_user_interface_player_model_set_text_value_pair_proxy::update
	// c_gui_screen_game_options *screen;
		// long i;

	m_values_count = 0;
	if (m_data->player_character_set_count > 0)
	{
		m_values[m_values_count].name = 0x103AC;
		m_values[m_values_count++].integer_value = 0;
		m_values[m_values_count].name = 0x40003;
		m_values[m_values_count++].integer_value = 2;
		for (long i = 0; i < m_data->player_character_set_count && m_values_count < 8; i++)
		{
			m_values[m_values_count].name = m_data->player_character_sets[i].name;
			m_values[m_values_count++].integer_value = i + 3;
		}
	}
	else
	{
		m_values[m_values_count].name = 0x103AC;
		m_values[m_values_count++].integer_value = 0;
	}
	m_tag_definition.values.count = m_values_count;
	m_tag_definition.values.address = &m_values[0];
}

_inline bool c_user_interface_player_model_set_text_value_pair_proxy::try_get_string(unsigned long id, wchar_t *out_value) // 0x10AA7C90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?try_get_string@c_user_interface_player_model_set_text_value_pair_proxy@hades_file_local@@QAE_NKPA_W@Z");
	// `anonymous-namespace'::c_user_interface_player_model_set_text_value_pair_proxy::try_get_string
	// static ...; // 0x10AA7D8C
	// c_user_interface_player_model_set_text_value_pair_proxy *const this;
	// unsigned long id;
	// wchar_t *out_value;
		// long i;
			// unsigned __int32 nc;

	if (id == 1)
	{
		wcsncpy_s(out_value, 1024, L"NOT AVAILABLE", _TRUNCATE);
		return true;
	}
	for (long i = 0; i < m_data->player_character_set_count; i++)
	{
		if (m_data->player_character_sets[i].name == id)
		{
			unsigned __int32 nc;
			mbstowcs_s(&nc, out_value, 1024, m_data->player_character_sets[i].display_name.ascii, _TRUNCATE);
			return true;
		}
	}
	return false;
}

s_text_value_pair_definition *text_value_pair_definition_try_and_get_hook(s_multiplayer_variant_settings_interface_definition *definition, long parameter_type) // 0x10AA7970
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?text_value_pair_definition_try_and_get_hook@@YAPAUs_text_value_pair_definition@@PAUs_multiplayer_variant_settings_interface_definition@@J@Z");
	// `anonymous-namespace'::text_value_pair_definition_try_and_get_hook
	// long parameter_type;
	// constexpr s_text_value_pair_definition *(*const `text_value_pair_definition_try_and_get_hook'::`2'::text_value_pair_definition_try_and_get_recursive)(s_multiplayer_variant_settings_interface_definition *, long); // constant == 11665456
	// function call : s_text_value_pair_definition *(*const)(s_multiplayer_variant_settings_interface_definition *, long)

	if (parameter_type >= 626 && parameter_type <= 647)
		return g_player_model_options_proxy.get_tag_definition();
	if (parameter_type >= 648 && parameter_type <= 669)
		return g_player_model_set_options_proxy.get_tag_definition();
	return ((s_text_value_pair_definition *(*)(s_multiplayer_variant_settings_interface_definition *, long))0xb20030)(definition, parameter_type);
}

bool __fastcall c_gui_screen_game_options__get_string_value_hook(c_gui_screen_widget *thisptr, void *unused, unsigned long id, wchar_t *out_value) // 0x10AA5CF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_gui_screen_game_options__get_string_value_hook@@YI_NPAVc_gui_screen_widget@@PAXKPA_W@Z");
	// `anonymous-namespace'::c_gui_screen_game_options__get_string_value_hook
	// wchar_t *out_value;
	// constexpr bool (*const `c_gui_screen_game_options__get_string_value_hook'::`2'::c_gui_screen_widget__get_string_value)(c_gui_screen_widget *, unsigned long, wchar_t *); // constant == 11210752
	// constexpr bool (*const `c_gui_screen_game_options__get_string_value_hook'::`2'::string_list_valid_string)(long, unsigned long); // constant == 5365696
	// long strings_definition_index;
	// function call : bool (*const)(long, unsigned long)
	// function call : bool (*const)(c_gui_screen_widget *, unsigned long, wchar_t *)

	long strings_definition_index = *(long *)((char *)thisptr + 0x158);
	if (strings_definition_index != -1 && !((bool(*)(long, unsigned long))0x51dfc0)(strings_definition_index, id))
	{
		if (g_player_model_options_proxy.try_get_string(id, out_value))
			return true;
		if (g_player_model_set_options_proxy.try_get_string(id, out_value))
			return true;
	}
	return ((bool(__thiscall *)(c_gui_screen_widget *, unsigned long, wchar_t *))0xab1000)(thisptr, id, out_value);
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

bool __fastcall gui_screen_game_options_set_variant_parameter_hook(c_game_variant *thisptr, void *unused, long parameter_type, unsigned long value) // 0x10AA78A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?gui_screen_game_options_set_variant_parameter_hook@@YI_NPAUc_game_variant@@PAXJK@Z");
	// `anonymous-namespace'::gui_screen_game_options_set_variant_parameter_hook
	// unsigned long value;
	// bool ret;
	// constexpr bool (*const `gui_screen_game_options_set_variant_parameter_hook'::`2'::c_game_engine_variant__set_parameter)(c_game_variant *, long, unsigned long); // constant == 5768992
		// c_gui_screen_game_options *options_screen;
	// function call : bool (*const)(c_game_variant *, long, unsigned long)

	bool ret = ((bool(__thiscall *)(c_game_variant *, long, unsigned long))0x580720)(thisptr, parameter_type, value);
	if (ret && parameter_type >= 648 && parameter_type <= 669)
	{
		c_gui_screen_game_options *options_screen = (c_gui_screen_game_options *)((char *)thisptr - 0x1AA0);
		g_player_model_options_proxy.update(options_screen);
		c_gui_screen_game_options__try_set_parameter_value(options_screen, 626, 0);
	}
	return ret;
}

_inline void ModListener::OnModChanged(EModIndex index, IMod *mod) // 0x10AA3B90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?OnModChanged@ModListener@hades_file_local@@EAEXW4EModIndex@@PAVIMod@@@Z");
	// `anonymous-namespace'::ModListener::OnModChanged
	// IMod *mod;

	if (index == kGame)
	{
		g_player_model_proxy_dirty = true;
	}
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

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { bool g_player_model_proxy_dirty = true; }
namespace hades_file_local { c_user_interface_mods_player_character_data g_player_characte_data; }
