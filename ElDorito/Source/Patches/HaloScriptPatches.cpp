/* ---------- headers */

#include "hades/hades.h"

#include "Blam/BitStream.hpp"
#include "Blam/BlamNetwork.hpp"
#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/cseries/static_string.inl"
#include "Blam/cutscene/cinematic_definitions.hpp"
#include "Blam/cutscene/podium_settings.hpp"
#include "Blam/effects/screen_effect.hpp"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_globals.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/items/equipment_definitions.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/bitstream.hpp"
#include "Blam/memory/data.hpp"
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
#include "Blam/simulation/simulation_type_collection.hpp"
#include "Blam/simulation/simulation_types.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_block_index.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "Blam/units/unit_definitions.hpp"
#include "Blam/units/units.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "CommandScript.hpp"
#include "Console/Console.hpp"
#include "Forge/Geoemetry.hpp"
#include "Modules/ModuleDebug.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Pointer.hpp"
#include "Scripting/HaloScript/HsMethodMap.hpp"
#include "Scripting/HaloScript/HsThreadStorage.hpp"
#include "Utils/Singleton.hpp"

#include "Modules/ModuleCampaign.hpp"  // hades: added for 0x107B4120

#include <share.h>  // hades: added for 0x107B6ED0

#include <boost/assert.hpp>
#include <boost/exception/all.hpp>
#include <boost/format.hpp>
#include <boost/none_t.hpp>
#include <boost/optional.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/throw_exception.hpp>

#include <Windows.h>
#include <boost/current_function.hpp>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <algorithm>
#include <atomic>
#include <charconv>
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
#include <memory>
#include <mutex>
#include <ostream>
#include <ratio>
#include <sstream>
#include <stdexcept>
#include <stop_token>
#include <streambuf>
#include <string>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <variant>
#include <vector>

/* ---------- forward declarations */

class c_bitstream;
class c_simulation_event_definition;
class c_simulation_type_collection;
struct c_replication_outgoing_event;
struct hs_stack_frame;
struct hs_value;
struct lambda_1;
struct real_euler_angles3d;
struct real_matrix4x3;
struct real_point3d;
struct real_quaternion;
struct real_rectangle2d;
struct real_vector3d;
struct s_cinematic_scene_definition;
struct s_cinematic_scene_object;
struct s_cinematic_scene_shot;
struct s_cinematic_shot_screen_effect;
struct s_data_array;
struct s_game_globals;
struct s_hs_global_runtime;
struct s_hs_script;
struct s_hs_script_op;
struct s_hs_syntax_node;
struct s_hs_thread;
struct s_object_data;
struct s_player_datum;
struct s_podium_settings;
struct s_scenario;
struct s_scenario_cutscene_camera_point;
struct s_unit_data;
struct s_unit_seat_definition;
struct s_unit_seat_source;
struct simulation_event_definition_return_value;
namespace Blam
{
	class BitStream;
}
namespace Blam
{
	namespace Network
	{
		struct Session;
	}
}
namespace Modules
{
	class ModuleDebug;
}
namespace Scripting
{
	namespace HS
	{
		struct ScriptMethod;
	}
}
namespace hades_file_local
{
	struct s_simulation_hs_script_wake_event_data;
	class c_simulation_hs_script_wake_event_definition;
	struct s_simulation_hs_sync_global_event_data;
	class c_simulation_hs_sync_global_event_definition;
}
using namespace hades_file_local;

namespace Utils {}
using namespace ::Utils;
namespace Server {}
using namespace ::Server;
namespace Server
{
	namespace Stats {}
	using namespace Server::Stats;
	namespace HsGlobalSync {}
	using namespace Server::HsGlobalSync;
}

namespace Modules {}
using namespace ::Modules;
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

namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Core {}
	using namespace Patches::Core;
	namespace HaloScript {}
	using namespace Patches::HaloScript;
}

namespace Console {}
using namespace ::Console;
namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Cache {}
	using namespace Blam::Cache;
	namespace Network {}
	using namespace Blam::Network;
}

/* ---------- constants */

/* ---------- definitions */

namespace hades_file_local
{
	struct s_simulation_hs_script_wake_event_data
	{
		short script_index; // 0x0
	};
	static_assert(sizeof(s_simulation_hs_script_wake_event_data) == 2, "Invalid s_simulation_hs_script_wake_event_data size");

	class c_simulation_hs_script_wake_event_definition :
		public c_simulation_event_definition
	{
	private:
		virtual e_simulation_event_type event_type() const;
		virtual char const *event_name() const;
		virtual long payload_size() const;
		virtual long number_of_entity_references() const;
		virtual bool reference_delays_entity_deletion() const;
		virtual bool event_can_be_transmitted(c_replication_outgoing_event const *, s_simulation_view_telemetry_data const *) const;
		virtual long minimum_required_bits(c_replication_outgoing_event const *, s_simulation_view_telemetry_data const *, long *) const;
		virtual float calculate_relevance(c_replication_outgoing_event const *, s_simulation_view_telemetry_data const *, float) const;
		virtual void write_description_to_string(c_replication_outgoing_event const *, s_simulation_view_telemetry_data const *, float, long, char *) const;
		virtual simulation_event_definition_return_value *gather_requirements_data(simulation_event_definition_return_value *, c_replication_outgoing_event const *, s_simulation_view_telemetry_data const *) const;
		virtual void event_payload_encode(long, void const *, c_bitstream *, bool) const;
		virtual bool event_payload_decode(long, void *, c_bitstream *, bool) const;
		virtual void prepare_event_data_for_gameworld(long, void *);
		virtual bool apply_game_event(long, long const *, long, void const *);
	public:
		// c_simulation_hs_script_wake_event_definition(c_simulation_hs_script_wake_event_definition &); /* compiler_generated(): left implicit, as the original's was */
		// c_simulation_hs_script_wake_event_definition(c_simulation_hs_script_wake_event_definition const &); /* compiler_generated(): left implicit, as the original's was */
		// c_simulation_hs_script_wake_event_definition(); /* compiler_generated(): left implicit, as the original's was */
		// c_simulation_hs_script_wake_event_definition &operator=(c_simulation_hs_script_wake_event_definition &); /* compiler_generated(): left implicit, as the original's was */
		// c_simulation_hs_script_wake_event_definition &operator=(c_simulation_hs_script_wake_event_definition const &); /* compiler_generated(): left implicit, as the original's was */
	};
	static_assert(sizeof(c_simulation_hs_script_wake_event_definition) == 4, "Invalid c_simulation_hs_script_wake_event_definition size");

	struct s_simulation_hs_sync_global_event_data
	{
		long global_index; // 0x0
		long value; // 0x4
	};
	static_assert(sizeof(s_simulation_hs_sync_global_event_data) == 8, "Invalid s_simulation_hs_sync_global_event_data size");

	class c_simulation_hs_sync_global_event_definition :
		public c_simulation_event_definition
	{
	private:
		virtual e_simulation_event_type event_type() const;
		virtual char const *event_name() const;
		virtual long payload_size() const;
		virtual long number_of_entity_references() const;
		virtual bool reference_delays_entity_deletion() const;
		virtual bool event_can_be_transmitted(c_replication_outgoing_event const *, s_simulation_view_telemetry_data const *) const;
		virtual long minimum_required_bits(c_replication_outgoing_event const *, s_simulation_view_telemetry_data const *, long *) const;
		virtual float calculate_relevance(c_replication_outgoing_event const *, s_simulation_view_telemetry_data const *, float) const;
		virtual void write_description_to_string(c_replication_outgoing_event const *, s_simulation_view_telemetry_data const *, float, long, char *) const;
		virtual simulation_event_definition_return_value *gather_requirements_data(simulation_event_definition_return_value *, c_replication_outgoing_event const *, s_simulation_view_telemetry_data const *) const;
		virtual void event_payload_encode(long, void const *, c_bitstream *, bool) const;
		virtual bool event_payload_decode(long, void *, c_bitstream *, bool) const;
		virtual void prepare_event_data_for_gameworld(long, void *);
		virtual bool apply_game_event(long, long const *, long, void const *);
	public:
		// c_simulation_hs_sync_global_event_definition(c_simulation_hs_sync_global_event_definition &); /* compiler_generated(): left implicit, as the original's was */
		// c_simulation_hs_sync_global_event_definition(c_simulation_hs_sync_global_event_definition const &); /* compiler_generated(): left implicit, as the original's was */
		// c_simulation_hs_sync_global_event_definition(); /* compiler_generated(): left implicit, as the original's was */
		// c_simulation_hs_sync_global_event_definition &operator=(c_simulation_hs_sync_global_event_definition &); /* compiler_generated(): left implicit, as the original's was */
		// c_simulation_hs_sync_global_event_definition &operator=(c_simulation_hs_sync_global_event_definition const &); /* compiler_generated(): left implicit, as the original's was */
	};
	static_assert(sizeof(c_simulation_hs_sync_global_event_definition) == 4, "Invalid c_simulation_hs_sync_global_event_definition size");
}
using namespace hades_file_local;
//class Patches::HaloScript::ApplyAll::__l2::<lambda_1>
//{
//public:
//	void operator()(char const *) const;
//};
//static_assert(sizeof(Patches::HaloScript::ApplyAll::__l2::<lambda_1>) == 1, "Invalid Patches::HaloScript::ApplyAll::__l2::<lambda_1> size");

namespace Server
{
	namespace HsGlobalSync
	{
		typedef std::function<void __cdecl(short,unsigned short)> SendGlobalFunc;
	}
}

typedef void (*hs_evaluate_func)(short, long, bool);

/* ---------- prototypes */

namespace eldorado
{
	// Functions in eldorado.exe, named as in ManagedDonkey.
	static auto const game_is_authoritative = reinterpret_cast<bool (*)()>(0x5319C0);
	static auto const hs_evaluate_runtime = reinterpret_cast<bool (*)(long, long, long, long *)>(0x594510);
	static auto const hs_find_thread_by_script = reinterpret_cast<long (*)(short)>(0x596130);
	static auto const hs_global_reconcile_write = reinterpret_cast<void (*)(long)>(0x596C10);
	static auto const hs_macro_function_evaluate = reinterpret_cast<hs_value *(*)(short, long, bool)>(0x5972F0);
	static auto const hs_return = reinterpret_cast<void (*)(long, hs_value)>(0x5974E0);
	static auto const hs_return_2 = reinterpret_cast<void(__cdecl *)(long, hs_value)>(0x5974E0);
	static auto const hs_stack_allocate = reinterpret_cast<void *(*)(long, long, long, short *)>(0x5987D0);
	static auto const hs_stack_pop = reinterpret_cast<void (*)(long)>(0x598900);
	static auto const hs_syntax_get = reinterpret_cast<s_hs_syntax_node *(*)(long)>(0x598A10);
	static auto const hs_thread_new = reinterpret_cast<long (*)(e_hs_script_type, short)>(0x598E70);
	static auto const hs_wake = reinterpret_cast<void (*)(short)>(0x599170);
	static auto const object_get_world_matrix = reinterpret_cast<real_matrix4x3 *(*)(long, real_matrix4x3 *)>(0xB2EC60);
}

namespace Forge { namespace PodiumPoint { extern long FindPodiumObject(); } }  // hades: added for 0x107B4FD0
namespace Player { namespace PlayerPodium { extern bool ForgeCanOverride(); } }  // hades: added for 0x107B4FD0
extern void matrix4x3_rotation_to_angles(real_matrix4x3 const *matrix, real_euler_angles3d *angles);  // hades: added for 0x107B4FD0
extern real_point3d *matrix4x3_transform_point(real_matrix4x3 const *matrix, real_point3d const *point, real_point3d *result);  // hades: added for 0x107B4FD0
extern real_vector3d *matrix4x3_transform_vector(real_matrix4x3 const *matrix, real_vector3d const *vector, real_vector3d *result);  // hades: added for 0x107B4FD0
extern void *tag_try_and_get_and_verify_group(unsigned long group_tag, long tag_index);  // hades: added for 0x107B4FD0

namespace Server { namespace HsGlobalSync { extern void SetupFuncs(std::function<void __cdecl(short,unsigned short)> sendGlobal_); } }  // hades: added for 0x107B2F30
namespace Scripting { namespace HS { extern void RegisterBindings(); extern void InitializeMethodsForNewMap(); } }  // hades: added for 0x107B2F30
namespace Patches { namespace Core { extern void OnMapLoaded(std::function<void __cdecl(char const *)> callback); } }  // hades: added for 0x107B2F30

extern void unit_copy_player_appearance(long unit_index, long object_index);  // hades: added for 0x107B43C0

#include "Blam/Cache/StringIdCache.hpp"  // hades: added for 0x107B79F0
extern char const *tag_get_name(long tag_index);  // hades: added for 0x107B79F0

extern bool (*const game_is_distributed)();  // hades: added for 0x107B8DE0

extern s_object_data *(*const object_try_and_get_and_verify_type)(unsigned long object_index, c_enum<e_object_type, long> object_type_mask);  // hades: added for 0x107B92A0

namespace Server { namespace HsGlobalSync { extern void RegisterGlobal(short globalIndex); } }  // hades: added for 0x107B7FE0
extern char const *hs_global_get_name(short global_index);  // hades: added for 0x107B7FE0

namespace Player { namespace PlayerNetworkUtil { extern long get_player_datum_index_from_session_index(__int32 player_session_index); } }  // hades: added for 0x107B4A80

extern long screen_effect_new(long definition_index, long attach_object_index, short attach_node_index, real_point3d const *position, real_rectangle2d const *bounds);  // hades: added for 0x107B4690
extern long screen_effect_new2(long definition_index, long attach_object_index, short attach_node_index, real_point3d const *attach_offset, real_rectangle2d const *bounds, bool unknown1, bool cannot_die);  // hades: added for 0x107B4690

namespace hades_file_local { extern c_simulation_hs_script_wake_event_definition hs_wake_script_event_definition; extern c_simulation_hs_sync_global_event_definition hs_sync_global_event_definition; }  // hades: added for 0x107B3950

namespace Patches
{
	namespace HaloScript
	{
		extern void ApplyAll();
		extern void RegisterSimulationTypes(c_simulation_type_collection *collection, __int32 *entity_count, __int32 *event_count);
	}
}

void simulation_action_hs_sync_global(short global_index, unsigned short player_mask);
void simulation_action_hs_script_wake(short script_index);
void hs_mp_wake_script_evaluate(short a1, __int32 thread_index, char a3);
void hs_mp_sync_global_evaluate(short op, __int32 thread_index, char a3);
void hs_cinematic_scripting_start_animation_legacy(long cine_index, long scene_index, long cine_object_index, long object_index, unsigned long animation_id);
void hs_cinematic_scripting_start_animation_legacy_evaluate(short a1, __int32 a2, char a3);
void hs_cinematic_scripting_create_object_legacy(long cine_index, long scene_index, long cine_object_index, short object_name_index);
void hs_cinematic_scripting_create_object_legacy_evaluate(short a1, __int32 a2, char a3);
long cinematic_scripting_cinematic_object_get_representation_index(long cine_index, long scene_index, long cine_object_index);
long get_campaign_player_character_type_index(long player_session_index);
void cinematic_scripting_create_cinematic_object_hook(long cine_index, long scene_index, long cine_object_index);
void hs_cinematic_scripting_create_and_animate_object_legacy(long cine_index, long scene_index, long cine_object_index, short object_name_index, long object_index, unsigned long animation_id, bool a5);
void hs_cinematic_scripting_create_and_animate_object_legacy_evaluate(short a1, __int32 a2, char a3);
void hs_cinematic_scripting_create_and_animate_object_no_animation_legacy(long cine_index, long scene_index, long cine_object_index, short object_name_index, long object_index, bool a5);
void hs_cinematic_scripting_create_and_animate_object_no_animation_legacy_evaluate(short a1, __int32 a2, char a3);
void hs_cinematic_scripting_create_and_animate_cinematic_object_legacy(long cine_index, long scene_index, long cine_object_index, long object_index, unsigned long animation_id, bool a5);
void hs_cinematic_scripting_create_and_animate_cinematic_object_legacy_evaluate(short a1, __int32 a2, char a3);
void hs_cinematic_scripting_destroy_object_legacy(long cine_index, long scene_index, long cine_object_index, long object_index);
void hs_cinematic_scripting_destroy_object_legacy_evaluate(short a1, __int32 a2, char a3);
void hs_camera_set_evaluate(short a1, __int32 a2, char a3);
void hs_dew_method_stub_evaluate(short op, __int32 thread_index, char a3);
bool unit_scripting_vehicle_test_seat(long vehicle_index, unsigned long seat_name, long unit_index);
bool unit_scripting_vehicle_test_seat_list_legacy(long vehicle_index, unsigned long seat_name, long list_index);
void hs_vehicle_test_seat_legacy_evaluate(short function_index, __int32 thread_index, char initial);
void hs_vehicle_test_seat_list_legacy_evaluate(short function_index, __int32 thread_index, char initial);
void hs_get_value_string(e_hs_type type, long value, char (&buffer)[256]);
void hs_debug_macro_function_evaluate(long thread_index, long *evaluated_arguments, short function_index);
void hs_thread_main_hook(long thread_index);
long hs_runtime_script_begin_hook(short script_index, e_hs_script_type script_type, e_hs_script_type thread_type);
long *hs_macro_function_evaluate_hook(short function_index, long thread_index, bool initial);
void hs_return_hook(long thread_index, hs_value value);
void hs_evaluate_inspect_hook(short op, long thread_index, bool a3);
void hs_evaluate_set_hook(short op, long thread_index, bool a3);
void cinematic_scripting_start_screen_effect(__int32 cinematic_tag_index, __int32 scene_index, __int32 shot_index, __int32 cinematic_screen_effect_index);
void cinematic_scripting_stop_screen_effect(__int32 cinematic_tag_index, __int32 scene_index, __int32 shot_index, __int32 cinematic_screen_effect_index);
long ui_get_current_music_id_hook();

/* ---------- globals */

namespace Server { namespace Stats { extern bool localPlayerIsPostMatch(); } }  // hades: added for 0x107B91C0
namespace Server { namespace HsGlobalSync { extern void InvalidateGlobal(short globalIndex); } }  // hades: added for 0x107B78C0
extern void *(*const datum_try_and_get)(s_data_array const *, unsigned long);  // hades: added for 0x107B8790
extern void (*const datum_delete)(s_data_array *, long);  // hades: added for 0x107B8790

/* ---------- private variables */

extern "C" { extern s_hs_script_op const *script_ops[1707]; } // 0x1134DDD8
extern "C" { extern char const *script_op_names[1707]; } // 0x1134F888

namespace hades_file_local
{
	namespace hades_file_local_HaloScriptPatches { extern real_rectangle2d global_null_rectangle2d; } using namespace hades_file_local_HaloScriptPatches; // 0x11182F0C
}
using namespace hades_file_local;
/* ---------- public code */

namespace Patches
{
	namespace HaloScript
	{
		void ApplyAll() // 0x107B2F30
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAll@HaloScript@Patches@@YAXXZ");

			Pointer(0x5972FD).Write<unsigned int>(reinterpret_cast<unsigned int>(script_ops));
			Pointer(0x59753A).Write<unsigned int>(reinterpret_cast<unsigned int>(script_ops));
			Pointer(0x598CF1).Write<unsigned int>(reinterpret_cast<unsigned int>(script_ops));
			Hook(0x1981A3, hs_thread_main_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x198050, hs_runtime_script_begin_hook).Apply();
			Pointer(0x167A8F8).Write(hs_evaluate_set_hook);
			Pointer(0x167ADB4).Write(hs_evaluate_inspect_hook);
			Hook(0x1972F0, hs_macro_function_evaluate_hook).Apply();
			Hook(0x1974E0, hs_return_hook).Apply();
			Hook(0x5EC820, cinematic_scripting_start_screen_effect).Apply();
			Hook(0x5EC8E0, cinematic_scripting_stop_screen_effect).Apply();
			Hook(0x2351C0, ui_get_current_music_id_hook).Apply();
			Hook(0x5EBE17, cinematic_scripting_create_cinematic_object_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Server::HsGlobalSync::SetupFuncs(simulation_action_hs_sync_global);
			Scripting::HS::RegisterBindings();
			Patches::Core::OnMapLoaded([](char const *map)
			{
				Scripting::HS::InitializeMethodsForNewMap();
			});
		}

		void RegisterSimulationTypes(c_simulation_type_collection *collection, __int32 *entity_count, __int32 *event_count) // 0x107B3950
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?RegisterSimulationTypes@HaloScript@Patches@@YAXPAVc_simulation_type_collection@@PAH1@Z");

			collection->register_event_definition(_simulation_event_type_hs_wake_script, &hs_wake_script_event_definition);
			(*event_count)++;
			collection->register_event_definition(_simulation_event_type_hs_sync_global, &hs_sync_global_event_definition);
			(*event_count)++;
		}
	}
}

/* ---------- private code */

_inline e_simulation_event_type c_simulation_hs_script_wake_event_definition::event_type() const // 0x107B0A70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?event_type@c_simulation_hs_script_wake_event_definition@hades_file_local@@EBE?AW4e_simulation_event_type@@XZ");

	return _simulation_event_type_hs_wake_script;
}

_inline char const *c_simulation_hs_script_wake_event_definition::event_name() const // 0x107B0AA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?event_name@c_simulation_hs_script_wake_event_definition@hades_file_local@@EBEPBDXZ");

	return "hs_wake_script";
}

_inline long c_simulation_hs_script_wake_event_definition::payload_size() const // 0x107B0AD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?payload_size@c_simulation_hs_script_wake_event_definition@hades_file_local@@EBEJXZ");

	return 2;
}

_inline long c_simulation_hs_script_wake_event_definition::number_of_entity_references() const // 0x107B0B00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?number_of_entity_references@c_simulation_hs_script_wake_event_definition@hades_file_local@@EBEJXZ");

	return 0;
}

_inline bool c_simulation_hs_script_wake_event_definition::reference_delays_entity_deletion() const // 0x107B0B20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?reference_delays_entity_deletion@c_simulation_hs_script_wake_event_definition@hades_file_local@@EBE_NXZ");

	return false;
}

_inline bool c_simulation_hs_script_wake_event_definition::event_can_be_transmitted(c_replication_outgoing_event const *__formal, s_simulation_view_telemetry_data const *__formal1) const // 0x107B0B40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?event_can_be_transmitted@c_simulation_hs_script_wake_event_definition@hades_file_local@@EBE_NPBUc_replication_outgoing_event@@PBUs_simulation_view_telemetry_data@@@Z");

	return true;
}

_inline long c_simulation_hs_script_wake_event_definition::minimum_required_bits(c_replication_outgoing_event const *__formal, s_simulation_view_telemetry_data const *__formal1, long *__formal2) const // 0x107B0B60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?minimum_required_bits@c_simulation_hs_script_wake_event_definition@hades_file_local@@EBEJPBUc_replication_outgoing_event@@PBUs_simulation_view_telemetry_data@@PAJ@Z");

	return 0x4A;
}

_inline float c_simulation_hs_script_wake_event_definition::calculate_relevance(c_replication_outgoing_event const *__formal, s_simulation_view_telemetry_data const *__formal1, float __formal2) const // 0x107B0B90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?calculate_relevance@c_simulation_hs_script_wake_event_definition@hades_file_local@@EBEMPBUc_replication_outgoing_event@@PBUs_simulation_view_telemetry_data@@M@Z");

	return 0.0f;
}

_inline void c_simulation_hs_script_wake_event_definition::write_description_to_string(c_replication_outgoing_event const *__formal, s_simulation_view_telemetry_data const *__formal1, float __formal2, long __formal3, char *__formal4) const // 0x107B0BB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?write_description_to_string@c_simulation_hs_script_wake_event_definition@hades_file_local@@EBEXPBUc_replication_outgoing_event@@PBUs_simulation_view_telemetry_data@@MJPAD@Z");
}

_inline simulation_event_definition_return_value *c_simulation_hs_script_wake_event_definition::gather_requirements_data(simulation_event_definition_return_value *data, c_replication_outgoing_event const *__formal, s_simulation_view_telemetry_data const *__formal1) const // 0x107B0BD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?gather_requirements_data@c_simulation_hs_script_wake_event_definition@hades_file_local@@EBEPAUsimulation_event_definition_return_value@@PAU3@PBUc_replication_outgoing_event@@PBUs_simulation_view_telemetry_data@@@Z");

	data->value = data->value & 0xFFFFFF01 | 0x101;
	data->value = data->value & 0x1FF | 0x9400;
	return data;
}

_inline void c_simulation_hs_script_wake_event_definition::event_payload_encode(long payload_size, void const *payload, c_bitstream *packet, bool predicted) const // 0x107B0C30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?event_payload_encode@c_simulation_hs_script_wake_event_definition@hades_file_local@@EBEXJPBXPAVc_bitstream@@_N@Z");

	Blam::BitStream *stream = (Blam::BitStream *)packet;
	short const *value = (short const *)payload;
	stream->Write<short>(*value, 10);
}

_inline bool c_simulation_hs_script_wake_event_definition::event_payload_decode(long payload_size, void *payload, c_bitstream *packet, bool predicted) const // 0x107B0CA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?event_payload_decode@c_simulation_hs_script_wake_event_definition@hades_file_local@@EBE_NJPAXPAVc_bitstream@@_N@Z");

	Blam::BitStream *packet_impl = (Blam::BitStream *)packet;
	s_simulation_hs_script_wake_event_data *data = (s_simulation_hs_script_wake_event_data *)payload;

	data->script_index = packet_impl->Read<short>(10);
	return true;
}

_inline void c_simulation_hs_script_wake_event_definition::prepare_event_data_for_gameworld(long payload_size, void *payload) // 0x107B0D10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?prepare_event_data_for_gameworld@c_simulation_hs_script_wake_event_definition@hades_file_local@@EAEXJPAX@Z");
}

_inline bool c_simulation_hs_script_wake_event_definition::apply_game_event(long reference_gamestate_count, long const *gamestate_indices, long payload_size, void const *payload) // 0x107B0D30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?apply_game_event@c_simulation_hs_script_wake_event_definition@hades_file_local@@EAE_NJPBJJPBX@Z");

	s_simulation_hs_script_wake_event_data *data = (s_simulation_hs_script_wake_event_data *)payload;
	s_scenario const *scnr = global_scenario_get();

	if (data->script_index < 0 || data->script_index >= scnr->scripts.count)
	{
		return false;
	}

	long thread_index = ((long(__cdecl *)(unsigned short))0x596130)(data->script_index);
	if (thread_index == -1)
	{
		return false;
	}

	((void(__cdecl *)(unsigned short))0x599170)(thread_index);
	return true;
}

_inline e_simulation_event_type c_simulation_hs_sync_global_event_definition::event_type() const // 0x107B0E00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?event_type@c_simulation_hs_sync_global_event_definition@hades_file_local@@EBE?AW4e_simulation_event_type@@XZ");

	return _simulation_event_type_hs_sync_global;
}

_inline char const *c_simulation_hs_sync_global_event_definition::event_name() const // 0x107B0E30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?event_name@c_simulation_hs_sync_global_event_definition@hades_file_local@@EBEPBDXZ");

	return "hs_sync_global";
}

_inline long c_simulation_hs_sync_global_event_definition::payload_size() const // 0x107B0E60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?payload_size@c_simulation_hs_sync_global_event_definition@hades_file_local@@EBEJXZ");

	return 8;
}

_inline long c_simulation_hs_sync_global_event_definition::number_of_entity_references() const // 0x107B0E90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?number_of_entity_references@c_simulation_hs_sync_global_event_definition@hades_file_local@@EBEJXZ");

	return 0;
}

_inline bool c_simulation_hs_sync_global_event_definition::reference_delays_entity_deletion() const // 0x107B0EB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?reference_delays_entity_deletion@c_simulation_hs_sync_global_event_definition@hades_file_local@@EBE_NXZ");

	return false;
}

_inline bool c_simulation_hs_sync_global_event_definition::event_can_be_transmitted(c_replication_outgoing_event const *__formal, s_simulation_view_telemetry_data const *__formal1) const // 0x107B0ED0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?event_can_be_transmitted@c_simulation_hs_sync_global_event_definition@hades_file_local@@EBE_NPBUc_replication_outgoing_event@@PBUs_simulation_view_telemetry_data@@@Z");

	return true;
}

_inline long c_simulation_hs_sync_global_event_definition::minimum_required_bits(c_replication_outgoing_event const *__formal, s_simulation_view_telemetry_data const *__formal1, long *__formal2) const // 0x107B0EF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?minimum_required_bits@c_simulation_hs_sync_global_event_definition@hades_file_local@@EBEJPBUc_replication_outgoing_event@@PBUs_simulation_view_telemetry_data@@PAJ@Z");

	return 0x4A;
}

_inline float c_simulation_hs_sync_global_event_definition::calculate_relevance(c_replication_outgoing_event const *__formal, s_simulation_view_telemetry_data const *__formal1, float __formal2) const // 0x107B0F20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?calculate_relevance@c_simulation_hs_sync_global_event_definition@hades_file_local@@EBEMPBUc_replication_outgoing_event@@PBUs_simulation_view_telemetry_data@@M@Z");

	return 0.0f;
}

_inline void c_simulation_hs_sync_global_event_definition::write_description_to_string(c_replication_outgoing_event const *__formal, s_simulation_view_telemetry_data const *__formal1, float __formal2, long __formal3, char *__formal4) const // 0x107B0F40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?write_description_to_string@c_simulation_hs_sync_global_event_definition@hades_file_local@@EBEXPBUc_replication_outgoing_event@@PBUs_simulation_view_telemetry_data@@MJPAD@Z");
}

_inline simulation_event_definition_return_value *c_simulation_hs_sync_global_event_definition::gather_requirements_data(simulation_event_definition_return_value *data, c_replication_outgoing_event const *__formal, s_simulation_view_telemetry_data const *__formal1) const // 0x107B0F60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?gather_requirements_data@c_simulation_hs_sync_global_event_definition@hades_file_local@@EBEPAUsimulation_event_definition_return_value@@PAU3@PBUc_replication_outgoing_event@@PBUs_simulation_view_telemetry_data@@@Z");

	data->value = (data->value & 0xFFFFFF01) | 0x101;
	data->value = (data->value & 0x1FF) | 0x9400;
	return data;
}

_inline void c_simulation_hs_sync_global_event_definition::event_payload_encode(long payload_size, void const *payload, c_bitstream *packet, bool predicted) const // 0x107B0FC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?event_payload_encode@c_simulation_hs_sync_global_event_definition@hades_file_local@@EBEXJPBXPAVc_bitstream@@_N@Z");

	Blam::BitStream *packet_impl = (Blam::BitStream *)packet;
	s_simulation_hs_sync_global_event_data const *data = (s_simulation_hs_sync_global_event_data const *)payload;

	packet_impl->Write<long>(data->global_index, 32);
	packet_impl->Write<long>(data->value, 32);
}

_inline bool c_simulation_hs_sync_global_event_definition::event_payload_decode(long payload_size, void *payload, c_bitstream *packet, bool predicted) const // 0x107B1040
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?event_payload_decode@c_simulation_hs_sync_global_event_definition@hades_file_local@@EBE_NJPAXPAVc_bitstream@@_N@Z");

	Blam::BitStream *packet_impl = (Blam::BitStream *)packet;
	s_simulation_hs_sync_global_event_data *data = (s_simulation_hs_sync_global_event_data *)payload;

	data->global_index = packet_impl->Read<long>(32);
	data->value = packet_impl->Read<long>(32);
	return true;
}

_inline void c_simulation_hs_sync_global_event_definition::prepare_event_data_for_gameworld(long payload_size, void *payload) // 0x107B10C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?prepare_event_data_for_gameworld@c_simulation_hs_sync_global_event_definition@hades_file_local@@EAEXJPAX@Z");
}

_inline bool c_simulation_hs_sync_global_event_definition::apply_game_event(long reference_gamestate_count, long const *gamestate_indices, long payload_size, void const *payload) // 0x107B10E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?apply_game_event@c_simulation_hs_sync_global_event_definition@hades_file_local@@EAE_NJPBJJPBX@Z");

	s_simulation_hs_sync_global_event_data *data = (s_simulation_hs_sync_global_event_data *)payload;
	s_hs_global_runtime *global = hs_global_runtime_get(data->global_index);
	if (!global)
	{
		return false;
	}

	e_hs_type global_type = hs_global_get_type(data->global_index);
	if (global_type == 9)
	{
		s_scenario const *scnr = global_scenario_get();
		long const string_offset = data->value;
		if (string_offset < 0 || string_offset >= scnr->script_strings.size)
		{
			return false;
		}

		global->value = (long)scnr->script_strings.address + string_offset;
	}
	else
	{
		global->value = data->value;
	}

	eldorado::hs_global_reconcile_write(data->global_index);
	char value_str[256];
	hs_get_value_string(global_type, global->value, value_str);
	Console::WriteLine(std::format("received hs global \"{}\", value: {}", hs_global_get_name(data->global_index), value_str));
	return true;
}

void simulation_action_hs_sync_global(short global_index, unsigned short player_mask) // 0x107B8DE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?simulation_action_hs_sync_global@@YAXFG@Z");

	if (!game_is_distributed())
	{
		return;
	}

	s_hs_global_runtime *global = hs_global_runtime_get(global_index);
	if (!global)
	{
		return;
	}

	long value = global->value;
	if (hs_global_get_type(global_index) == 9)
	{
		long string_offset = global->value - (long)global_scenario_get()->script_strings.address;
		value = string_offset;
	}

	s_simulation_hs_sync_global_event_data data;
	data.global_index = global_index;
	data.value = value;
	((void (*const)(e_simulation_event_type, long, long *, long, long, void const *))0x4E5920)((e_simulation_event_type)0x28, 0, nullptr, player_mask, sizeof(data), &data);
	Console::WriteLine(std::format("sent hs global \"{}\" to player mask: {}", hs_global_get_name(global_index), player_mask));
}

void simulation_action_hs_script_wake(short script_index) // 0x107B8D00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?simulation_action_hs_script_wake@@YAXF@Z");

	bool (*const game_is_distributed)() = (bool(*const)())0x531af0;

	if (!game_is_distributed())
		return;

	if (script_index != NONE)
	{
		s_simulation_hs_script_wake_event_data data{};
		data.script_index = script_index;
		((void(__cdecl *const)(e_simulation_event_type, long, long *, long, long, void const *))0x4e5a30)(_simulation_event_type_hs_wake_script, 0, nullptr, NONE, 2, &data);
	}
}

void hs_mp_wake_script_evaluate(short a1, __int32 thread_index, char a3) // 0x107B8240
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_mp_wake_script_evaluate@@YAXFHD@Z");

	s_hs_thread *thread = tls_getd().hs_thread_deterministic_data->try_and_get(thread_index);
	s_hs_syntax_node *node = eldorado::hs_syntax_get(*(long *)&thread->stack[thread->stack_offset]);
	node = eldorado::hs_syntax_get(*(long *)node->data);
	node = eldorado::hs_syntax_get(node->next_expression_index);
	short script_index = *(short *)node->data;
	s_scenario *scnr = global_scenario_get();
	if (script_index < 0 || script_index >= scnr->scripts.count)
	{
		return;
	}

	if (eldorado::game_is_authoritative())
	{
		long thread_index = eldorado::hs_find_thread_by_script(script_index);
		if (thread_index != -1)
		{
			eldorado::hs_wake((short)thread_index);
		}

		simulation_action_hs_script_wake(script_index);
	}

	eldorado::hs_return(thread_index, hs_value::from_long(0));
}

void hs_mp_sync_global_evaluate(short op, __int32 thread_index, char a3) // 0x107B7FE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_mp_sync_global_evaluate@@YAXFHD@Z");

	s_hs_thread *thread = tls_getd().hs_thread_deterministic_data->try_and_get(thread_index);
	s_hs_syntax_node *node = eldorado::hs_syntax_get(*(long *)&thread->stack[thread->stack_offset]);
	node = eldorado::hs_syntax_get(*(long *)node->data);
	node = eldorado::hs_syntax_get(node->next_expression_index);
	if (!(static_cast<unsigned short>(node->flags) & 4))
	{
		return;
	}

	if (eldorado::game_is_authoritative())
	{
		short global_index = *(short *)node->data;
		Server::HsGlobalSync::RegisterGlobal(global_index);
		Console::WriteLine(std::format("registered global \"{}\" for synchronization", hs_global_get_name(global_index)));
	}

	eldorado::hs_return(thread_index, hs_value::from_long(0));
}

void hs_cinematic_scripting_start_animation_legacy(long cine_index, long scene_index, long cine_object_index, long object_index, unsigned long animation_id) // 0x107B6A10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_cinematic_scripting_start_animation_legacy@@YAXJJJJK@Z");

	s_cinematic_scene_definition * (*const scenario_get_cinematic_scene)(long, long) = reinterpret_cast<s_cinematic_scene_definition * (*)(long, long)>(0x9EC9C0);
	long (*const cinematic_object_get_internal)(long) = reinterpret_cast<long (*)(long)>(0x67DAB0);
	void (*const custom_animation_relative)(long, long, unsigned long, char, long) = reinterpret_cast<void (*)(long, long, unsigned long, char, long)>(0xBB37F0);
	void (*const unit_limit_lipsync_to_mouth_only)(long, bool) = reinterpret_cast<void (*)(long, bool)>(0xBB2AB0);
	void * (*const c_animation_manager__get_mixing_board_facial_animation_channel)(void *) = reinterpret_cast<void * (*)(void *)>(0x6DBF90);
	void (*const scenery_animation_start_relative)(long, long, unsigned long, long) = reinterpret_cast<void (*)(long, long, unsigned long, long)>(0xBB88B0);

	s_cinematic_scene_definition const *cinematic_scene = scenario_get_cinematic_scene(cine_index, scene_index);
	if (cinematic_scene && cine_object_index >= 0 && cine_object_index < cinematic_scene->objects.count)
	{
		s_cinematic_scene_object const *cinematic_object = &cinematic_scene->objects[cine_object_index];
		if (cinematic_object && object_index != -1)
		{
			s_object_data *object_data = object_try_and_get_and_verify_type(object_index, -1);
			__int32 id_bit = 1 << (char)object_data->object_identifier.type;
			if ((!(id_bit & 0x80) && !(id_bit & 0x4000)) || cinematic_object->flags & static_cast<e_cinematic_object_flags>(8))
			{
				if ((id_bit & 0x2003) && !(cinematic_object->flags & static_cast<e_cinematic_object_flags>(8)))
				{
					long object = cinematic_object_get_internal(reinterpret_cast<long>(cinematic_scene->anchor_name));
					custom_animation_relative(object_index, cinematic_object->animation.index, animation_id, 0, object);
					unit_limit_lipsync_to_mouth_only(object_index, true);
					if (cinematic_object->flags & static_cast<e_cinematic_object_flags>(0x20))
					{
						if (long animation_data = reinterpret_cast<long>(object_data) + object_data->animation.offset)
						{
							long anim_channel = reinterpret_cast<long>(c_animation_manager__get_mixing_board_facial_animation_channel(reinterpret_cast<void *>(animation_data)));
							if (anim_channel)
							{
								*reinterpret_cast<char *>(anim_channel + 0x5B) |= 0x10;
							}
						}
					}
				}
			}
			else
			{
				long object = cinematic_object_get_internal(reinterpret_cast<long>(cinematic_scene->anchor_name));
				scenery_animation_start_relative(object_index, cinematic_object->animation.index, animation_id, object);
			}
		}
	}
}

void hs_cinematic_scripting_start_animation_legacy_evaluate(short a1, __int32 a2, char a3) // 0x107B6DD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_cinematic_scripting_start_animation_legacy_evaluate@@YAXFHD@Z");

	int args = ((int(__cdecl *)(unsigned short, int, bool))0x5972f0)(a1, a2, a3);
	if (args)
	{
		hs_cinematic_scripting_start_animation_legacy(*(int *)args, *(int *)(args + 4), *(int *)(args + 8), *(int *)(args + 12), *(int *)(args + 16));
		((void(__cdecl *)(int, int))0x5974e0)(a2, hs_value::from_long(0).long_value);
	}
}

void hs_cinematic_scripting_create_object_legacy(long cine_index, long scene_index, long cine_object_index, short object_name_index) // 0x107B6340
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_cinematic_scripting_create_object_legacy@@YAXJJJF@Z");

	s_cinematic_scene_definition * (*const scenario_get_cinematic_scene)(long, long) = reinterpret_cast<s_cinematic_scene_definition * (*)(long, long)>(0x9EC9C0);
	bool (*const cinematic_index_is_valid)(__int32) = reinterpret_cast<bool (*)(__int32)>(0x4E9580);
	long (*const object_index_from_name_index)(short) = reinterpret_cast<long (*)(short)>(0xB2F0A0);
	long (*const object_new)(short, bool, bool) = reinterpret_cast<long (*)(short, bool, bool)>(0xB30E60);
	long (*const object_create_anew)(short) = reinterpret_cast<long (*)(short)>(0x96D970);
	void (*const object_hide)(long, bool) = reinterpret_cast<void (*)(long, bool)>(0x96E230);
	void (*const object_set_always_active)(long, bool) = reinterpret_cast<void (*)(long, bool)>(0xB32730);

	s_cinematic_scene_definition const *cinematic_scene = scenario_get_cinematic_scene(cine_index, scene_index);
	if (cinematic_scene && cine_index != -1 && cine_index <= 1000 && cinematic_index_is_valid(cine_index) && cine_object_index >= 0 && cine_object_index < cinematic_scene->objects.count)
	{
		s_cinematic_scene_object const *cinematic_object = &cinematic_scene->objects[cine_object_index];
		if (cinematic_object)
		{
			if (cinematic_object->flags & static_cast<e_cinematic_object_flags>(8))
			{
				if (object_name_index != 0xFFFF && object_index_from_name_index(object_name_index) != -1)
				{
					object_new(object_name_index, false, false);
				}
			}
			else
			{
				object_create_anew(object_name_index);
			}

			long object_index = object_index_from_name_index(object_name_index);
			if (object_index != -1)
			{
				object_hide(object_index, false);
				object_set_always_active(object_index, true);
			}
		}
	}
}

void hs_cinematic_scripting_create_object_legacy_evaluate(short a1, __int32 a2, char a3) // 0x107B65B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_cinematic_scripting_create_object_legacy_evaluate@@YAXFHD@Z");

	int args = ((int(__cdecl *)(unsigned short, int, bool))0x5972F0)(a1, a2, (bool)a3);
	if (args)
	{
		hs_cinematic_scripting_create_object_legacy(*(long *)args, *(long *)(args + 4), *(long *)(args + 8), *(unsigned short *)(args + 12));
		((void(__cdecl *)(int, long))0x5974E0)(a2, hs_value::from_long(0).long_value);
	}
}

long cinematic_scripting_cinematic_object_get_representation_index(long cine_index, long scene_index, long cine_object_index) // 0x107B4120
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?cinematic_scripting_cinematic_object_get_representation_index@@YAJJJJ@Z");

	s_cinematic_scene_definition * (*const scenario_get_cinematic_scene)(long, long) = reinterpret_cast<s_cinematic_scene_definition * (*)(long, long)>(0x9EC9C0);
	bool (*const cinematic_index_is_valid)(__int32) = reinterpret_cast<bool (*)(__int32)>(0x4E9580);

	s_cinematic_scene_definition *cinematic_scene = scenario_get_cinematic_scene(cine_index, scene_index);
	if (cinematic_scene)
	{
		if (cine_index != -1 && cine_index <= 1000 && !cinematic_index_is_valid(cine_index))
		{
			return -1;
		}

		if (cine_object_index >= 0 && cine_object_index < cinematic_scene->objects.count)
		{
			s_cinematic_scene_object *cinematic_object = &cinematic_scene->objects[cine_object_index];
			if (cinematic_object)
			{
				__int32 campaign_player_representation_index = -1;
				if (!Modules::ModuleCampaign::Instance().VarPlayerRepresentationEnabledClient->ValueInt)
				{
					if (cinematic_object->flags & static_cast<e_cinematic_object_flags>(0x100))
					{
						campaign_player_representation_index = 0;
					}

					if (cinematic_object->flags & static_cast<e_cinematic_object_flags>(0x200))
					{
						campaign_player_representation_index = 1;
					}

					if (cinematic_object->flags & static_cast<e_cinematic_object_flags>(0x400))
					{
						campaign_player_representation_index = 2;
					}

					if (cinematic_object->flags & static_cast<e_cinematic_object_flags>(0x800))
					{
						campaign_player_representation_index = 3;
					}

					return campaign_player_representation_index;
				}
			}
		}
	}

	return -1;
}

long get_campaign_player_character_type_index(long player_session_index) // 0x107B4A80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_campaign_player_character_type_index@@YAJJ@Z");

	long player_datum_index = Player::PlayerNetworkUtil::get_player_datum_index_from_session_index(player_session_index);
	s_player_datum *player = players_get()->try_and_get(player_datum_index);
	s_game_globals *matg = game_globals_get();
	if (player_session_index != -1 && matg && player)
	{
		s_scenario *scnr = global_scenario_get();
		Blam::Network::Session *session = Blam::Network::GetActiveSession();
		if (session && scnr && scnr->campaign_players.count > 0)
		{
			unsigned long name = scnr->campaign_players[player_session_index].player_representation;
			__int32 player_sidx = session->MembershipInfo.GetPeerPlayer(player->machine_index);
			if (player_sidx == player_session_index)
			{
				for (__int32 i = 0; i < matg->player_character_types.count; i++)
				{
					if (matg->player_character_types[i].name == name)
					{
						return i;
					}
				}
			}
		}
	}

	return -1;
}

void cinematic_scripting_create_cinematic_object_hook(long cine_index, long scene_index, long cine_object_index) // 0x107B43C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?cinematic_scripting_create_cinematic_object_hook@@YAXJJJ@Z");

	s_cinematic_scene_definition * (*const scenario_get_cinematic_scene)(long, long) = reinterpret_cast<s_cinematic_scene_definition * (*)(long, long)>(0x9EC9C0);
	void (*const cinematic_scripting_create_cinematic_object)(long, long, long) = reinterpret_cast<void (*)(long, long, long)>(0x9EBEC0);
	bool (*const cinematic_index_is_valid)(__int32) = reinterpret_cast<bool (*)(__int32)>(0x4E9580);
	long (*const cinematic_object_get_internal)(s_cinematic_scene_object const *) = reinterpret_cast<long (*)(s_cinematic_scene_object const *)>(0x67DAB0);

	s_cinematic_scene_definition *cinematic_scene = scenario_get_cinematic_scene(cine_index, scene_index);
	if (cinematic_scene)
	{
		if (cine_index != -1 && cine_index <= 1000 && !cinematic_index_is_valid(cine_index))
		{
			return;
		}

		if (cine_object_index >= 0 && cine_object_index < cinematic_scene->objects.count)
		{
			s_cinematic_scene_object *cinematic_object = &cinematic_scene->objects[cine_object_index];
			if (cinematic_object)
			{
				long campaign_player_representation_index = cinematic_scripting_cinematic_object_get_representation_index(cine_index, scene_index, cine_object_index);
				long character_type_index = -1;
				if (campaign_player_representation_index != -1)
				{
					character_type_index = get_campaign_player_character_type_index(campaign_player_representation_index);
					s_game_globals *matg = game_globals_get();
					if (character_type_index != -1 && matg)
					{
						long character_rep_index = (char)matg->player_character_types[character_type_index].multiplayer_player_representation_block_index;
						cinematic_object->puppet_object = matg->PlayerRepresentation[character_rep_index].ThirdPersonUnit;
					}
				}

				cinematic_scripting_create_cinematic_object(cine_index, scene_index, cine_object_index);
				long object = cinematic_object_get_internal(cinematic_object);
				if (object != -1 && campaign_player_representation_index != -1 && character_type_index != -1)
				{
					long player_datum_index = Player::PlayerNetworkUtil::get_player_datum_index_from_session_index(campaign_player_representation_index);
					s_player_datum *player = players_get()->try_and_get(player_datum_index);
					if (player)
					{
						unit_copy_player_appearance(player->unit_index, object);
					}
				}
			}
		}
	}
}

void hs_cinematic_scripting_create_and_animate_object_legacy(long cine_index, long scene_index, long cine_object_index, short object_name_index, long object_index, unsigned long animation_id, bool a5) // 0x107B5AF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_cinematic_scripting_create_and_animate_object_legacy@@YAXJJJFJK_N@Z");

	s_cinematic_scene_definition * (*const scenario_get_cinematic_scene)(long, long) = reinterpret_cast<s_cinematic_scene_definition * (*)(long, long)>(0x9EC9C0);
	bool (*const cinematic_index_is_valid)(__int32) = reinterpret_cast<bool (*)(__int32)>(0x4E9580);
	bool (*const cinematic_scripting_object_coop_flags_valid)(long, long, long) = reinterpret_cast<bool (*)(long, long, long)>(0x9EC440);
	void (*const object_set_shadowless)(long, bool) = reinterpret_cast<void (*)(long, bool)>(0xB33E30);
	bool (*const cinematic_scripting_should_reset_object_lighting)(s_cinematic_scene_definition const *) = reinterpret_cast<bool (*)(s_cinematic_scene_definition const *)>(0x9EC570);
	void (*const render_object_invalidate_render_state)(long) = reinterpret_cast<void (*)(long)>(0xA44F70);
	void (*const cinematic_scripting_create_cinematic_object)(long, long, long) = reinterpret_cast<void (*)(long, long, long)>(0x9EBEC0);
	long (*const object_index_from_name_index)(short) = reinterpret_cast<long (*)(short)>(0xB2F0A0);
	long (*const cinematic_object_get_internal)(s_cinematic_scene_object const *) = reinterpret_cast<long (*)(s_cinematic_scene_object const *)>(0x67DAB0);

	s_cinematic_scene_definition *cinematic_scene = scenario_get_cinematic_scene(cine_index, scene_index);
	if (cinematic_scene)
	{
		if (cine_index != -1 && cine_index <= 1000 && !cinematic_index_is_valid(cine_index))
		{
			return;
		}

		if (cine_object_index >= 0 && cine_object_index < cinematic_scene->objects.count)
		{
			s_cinematic_scene_object *cinematic_object = &cinematic_scene->objects[cine_object_index];
			if (cinematic_object && cinematic_scripting_object_coop_flags_valid(cine_index, scene_index, cine_object_index) && a5)
			{
				long object = -1;
				long campaign_player_representation_index = cinematic_scripting_cinematic_object_get_representation_index(cine_index, scene_index, cine_object_index);
				long character_type_index = -1;
				if (campaign_player_representation_index != -1)
				{
					character_type_index = get_campaign_player_character_type_index(campaign_player_representation_index);
					s_game_globals *matg = game_globals_get();
					if (character_type_index != -1 && matg)
					{
						long character_rep_index = (char)matg->player_character_types[character_type_index].multiplayer_player_representation_block_index;
						cinematic_object->puppet_object = matg->PlayerRepresentation[character_rep_index].ThirdPersonUnit;
					}
				}

				if (cinematic_object->flags & static_cast<e_cinematic_object_flags>(2))
				{
					object = object_index;
				}
				else if (cinematic_object->flags & static_cast<e_cinematic_object_flags>(1))
				{
					hs_cinematic_scripting_create_object_legacy(cine_index, scene_index, cine_object_index, object_name_index);
					object = object_index_from_name_index(object_name_index);
				}
				else
				{
					cinematic_scripting_create_cinematic_object(cine_index, scene_index, cine_object_index);
					object = cinematic_object_get_internal(cinematic_object);
				}

				if (object != -1 && campaign_player_representation_index != -1 && character_type_index != -1)
				{
					long player_datum_index = Player::PlayerNetworkUtil::get_player_datum_index_from_session_index(campaign_player_representation_index);
					s_player_datum *player = players_get()->try_and_get(player_datum_index);
					if (player)
					{
						unit_copy_player_appearance(player->unit_index, object);
					}
				}

				if (object != -1)
				{
					if (cinematic_object->flags & static_cast<e_cinematic_object_flags>(0x10))
					{
						object_set_shadowless(object, true);
					}

					if (cinematic_scripting_should_reset_object_lighting(cinematic_scene))
					{
						render_object_invalidate_render_state(object);
					}
				}

				if (!(cinematic_object->flags & static_cast<e_cinematic_object_flags>(8)))
				{
					hs_cinematic_scripting_start_animation_legacy(cine_index, scene_index, cine_object_index, object, animation_id);
				}
			}
		}
	}
}

void hs_cinematic_scripting_create_and_animate_object_legacy_evaluate(short a1, __int32 a2, char a3) // 0x107B60B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_cinematic_scripting_create_and_animate_object_legacy_evaluate@@YAXFHD@Z");

	long const args = (long)((hs_value const *(__cdecl *)(unsigned short, long, bool))0x5972f0)(a1, a2, a3);
	if (args)
	{
		hs_cinematic_scripting_create_and_animate_object_legacy(*(long *)args, *(long *)(args + 4), *(long *)(args + 8), *(unsigned short *)(args + 12), *(long *)(args + 16), *(unsigned long *)(args + 20), *(bool *)(args + 24));
		eldorado::hs_return_2(a2, hs_value::from_long(0));
	}
}

void hs_cinematic_scripting_create_and_animate_object_no_animation_legacy(long cine_index, long scene_index, long cine_object_index, short object_name_index, long object_index, bool a5) // 0x107B61C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_cinematic_scripting_create_and_animate_object_no_animation_legacy@@YAXJJJFJ_N@Z");

	hs_cinematic_scripting_create_and_animate_object_legacy(cine_index, scene_index, cine_object_index, object_name_index, object_index, 0, a5);
}

void hs_cinematic_scripting_create_and_animate_object_no_animation_legacy_evaluate(short a1, __int32 a2, char a3) // 0x107B6230
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_cinematic_scripting_create_and_animate_object_no_animation_legacy_evaluate@@YAXFHD@Z");

	long const args = (long)((hs_value const *(__cdecl *)(unsigned short, long, bool))0x5972f0)(a1, a2, a3);
	if (args)
	{
		hs_cinematic_scripting_create_and_animate_object_no_animation_legacy(*(long *)args, *(long *)(args + 4), *(long *)(args + 8), *(unsigned short *)(args + 12), *(long *)(args + 16), *(bool *)(args + 20));
		eldorado::hs_return_2(a2, hs_value::from_long(0));
	}
}

void hs_cinematic_scripting_create_and_animate_cinematic_object_legacy(long cine_index, long scene_index, long cine_object_index, long object_index, unsigned long animation_id, bool a5) // 0x107B5970
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_cinematic_scripting_create_and_animate_cinematic_object_legacy@@YAXJJJJK_N@Z");

	hs_cinematic_scripting_create_and_animate_object_legacy(cine_index, scene_index, cine_object_index, -1, object_index, animation_id, a5);
}

void hs_cinematic_scripting_create_and_animate_cinematic_object_legacy_evaluate(short a1, __int32 a2, char a3) // 0x107B59E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_cinematic_scripting_create_and_animate_cinematic_object_legacy_evaluate@@YAXFHD@Z");

	long const args = (long)((hs_value const *(__cdecl *)(unsigned short, long, bool))0x5972f0)(a1, a2, a3);
	if (args)
	{
		hs_cinematic_scripting_create_and_animate_cinematic_object_legacy(*(long *)args, *(long *)(args + 4), *(long *)(args + 8), *(long *)(args + 12), *(unsigned long *)(args + 16), *(bool *)(args + 20));
		eldorado::hs_return_2(a2, hs_value::from_long(0));
	}
}

void hs_cinematic_scripting_destroy_object_legacy(long cine_index, long scene_index, long cine_object_index, long object_index) // 0x107B66B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_cinematic_scripting_destroy_object_legacy@@YAXJJJJ@Z");

	s_cinematic_scene_definition * (*const scenario_get_cinematic_scene)(long, long) = reinterpret_cast<s_cinematic_scene_definition * (*)(long, long)>(0x9EC9C0);
	void (*const object_hide)(long, bool) = reinterpret_cast<void (*)(long, bool)>(0x96E230);
	void (*const object_set_always_active)(long, bool) = reinterpret_cast<void (*)(long, bool)>(0xB32730);
	void (*const object_cinematic_visibility)(long, bool) = reinterpret_cast<void (*)(long, bool)>(0xB2AA70);
	void (*const unit_stop_custom_animation)(long) = reinterpret_cast<void (*)(long)>(0xBB3340);
	void (*const unit_limit_lipsync_to_mouth_only)(long, bool) = reinterpret_cast<void (*)(long, bool)>(0xBB2AB0);

	s_cinematic_scene_definition const *cinematic_scene = scenario_get_cinematic_scene(cine_index, scene_index);
	if (cinematic_scene && cine_object_index >= 0 && cine_object_index < cinematic_scene->objects.count)
	{
		s_cinematic_scene_object const *cinematic_object = &cinematic_scene->objects[cine_object_index];
		if (cinematic_object && object_index != -1)
		{
			s_object_data *object_data = object_try_and_get_and_verify_type(object_index, -1);
			__int32 id_bit = 1 << (char)object_data->object_identifier.type;
			if (!(cinematic_object->flags & 3))
			{
				object_hide(object_index, true);
				object_set_always_active(object_index, false);
				object_cinematic_visibility(object_index, false);
			}

			if ((id_bit & 0x2003) && !(id_bit & 0x80) && !(id_bit & 0x4000))
			{
				unit_stop_custom_animation(object_index);
				unit_limit_lipsync_to_mouth_only(object_index, false);
			}
		}
	}
}

void hs_cinematic_scripting_destroy_object_legacy_evaluate(short a1, __int32 a2, char a3) // 0x107B6910
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_cinematic_scripting_destroy_object_legacy_evaluate@@YAXFHD@Z");

	int *args = ((int *(__cdecl *)(unsigned short, int, bool))0x5972f0)(a1, a2, a3);
	if (args)
	{
		hs_cinematic_scripting_destroy_object_legacy(*args, *(args + 1), *(args + 2), *(args + 3));
		((void(__cdecl *)(int, int))0x5974e0)(a2, hs_value::from_long(0).long_value);
	}
}

void hs_camera_set_evaluate(short a1, __int32 a2, char a3) // 0x107B4FD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_camera_set_evaluate@@YAXFHD@Z");

	void (*const camera_control)(__int32) = reinterpret_cast<void (*)(__int32)>(0x592320);
	void (*const matrix4x3_from_point_and_quaternion)(real_matrix4x3 *, real_point3d const *, real_quaternion *) = reinterpret_cast<void (*)(real_matrix4x3 *, real_point3d const *, real_quaternion *)>(0x5B1F30);
	real_euler_angles3d * (*const euler_angles3d_from_vectors3d)(real_euler_angles3d *, real_vector3d const &, real_vector3d const &) = reinterpret_cast<real_euler_angles3d * (*)(real_euler_angles3d *, real_vector3d const &, real_vector3d const &)>(0x4F1490);
	void (*const camera_update_scripted)(__int32, real_vector3d *, real_vector3d *, float, short, unsigned __int32) = reinterpret_cast<void (*)(__int32, real_vector3d *, real_vector3d *, float, short, unsigned __int32)>(0x72DD70);
	void (*const object_get_orientation)(long, real_vector3d *, real_vector3d *) = reinterpret_cast<void (*)(long, real_vector3d *, real_vector3d *)>(0xB2E490);
	long const *args = (long const *)eldorado::hs_macro_function_evaluate(a1, a2, a3);
	void (*const sub4FA020)(real_quaternion *, real_euler_angles3d *) = reinterpret_cast<void (*)(real_quaternion *, real_euler_angles3d *)>(0x4FA020);
	void (*const sub501040)(real_vector3d *, real_vector3d *, real_vector3d *) = reinterpret_cast<void (*)(real_vector3d *, real_vector3d *, real_vector3d *)>(0x501040);
	if (args)
	{
		s_scenario *const scnr = *g_scenario_definition;
		if (scnr)
		{
			short camera = *(short *)args;
			c_tag_block<s_scenario_cutscene_camera_point> cutscenes = scnr->cutscene_camera_points;
			if (camera < cutscenes.count)
			{
				short ticksArg = *(short *)(args + 1);
				float ticks = ticksArg / 30.0f;
				s_scenario_cutscene_camera_point const &cutscene_camera = cutscenes[camera];
				bool isPodiumHack = (cutscene_camera.flags & 4) ? true : false;
				real_quaternion orientation;
				real_matrix4x3 cutscene_camera_matrix;
				real_point3d transformed_point;
				real_vector3d a2a;
				real_vector3d a3;
				real_vector3d v36;
				if (isPodiumHack)
				{
					s_scenario_cutscene_camera_point podiumCamera = cutscene_camera;
					long s_PodiumObjectIndex = Forge::PodiumPoint::FindPodiumObject();
					s_object_data *scenObject = object_try_and_get_and_verify_type(s_PodiumObjectIndex, 0x80);
					if (s_PodiumObjectIndex != -1 && scenObject && Player::PlayerPodium::ForgeCanOverride())
					{
						real_matrix4x3 podiumObjectTransform;
						eldorado::object_get_world_matrix(s_PodiumObjectIndex, &podiumObjectTransform);
						real_euler_angles3d podiumObjectOrientation;
						matrix4x3_rotation_to_angles(&podiumObjectTransform, &podiumObjectOrientation);
						podiumCamera.position.x = podiumObjectTransform.position.x;
						podiumCamera.position.y = podiumObjectTransform.position.y;
						podiumCamera.position.z = podiumObjectTransform.position.z;
						podiumCamera.orientation.yaw = podiumObjectOrientation.yaw;
						podiumCamera.orientation.pitch = 0.0f;
						podiumCamera.orientation.roll = 0.0f;
					}

					sub4FA020(&orientation, &podiumCamera.orientation);
					matrix4x3_from_point_and_quaternion(&cutscene_camera_matrix, &podiumCamera.position, &orientation);
					s_game_globals *matg = game_globals_get();
					if (matg)
					{
						void *podium = tag_try_and_get_and_verify_group('pdm!', matg->PodiumDefinition.index);
						if (podium)
						{
							s_podium_settings *podium_settings = (s_podium_settings *)tag_get('pdm!', matg->PodiumDefinition.index);
							if (podium_settings)
							{
								float &dword_471A4A0 = *(float *)0x471A4A0;
								float &dword_18ECE00 = *(float *)0x18ECE00;
								dword_471A4A0 = dword_18ECE00;
								dword_18ECE00 = podium_settings->camera_fov * 57.29578;
								real_point3d podium_position_offset = { podium_settings->camera_offset_x, podium_settings->camera_offset_y, podium_settings->camera_offset_z };
								real_vector3d podium_rotation_offset = { podium_settings->camera_orientation_offset_y, podium_settings->camera_orientation_offset_p, podium_settings->camera_orientation_offset_r };
								matrix4x3_transform_point(&cutscene_camera_matrix, &podium_position_offset, &transformed_point);
								sub501040(&a2a, &a3, &podium_rotation_offset);
								matrix4x3_transform_vector(&cutscene_camera_matrix, &a2a, &a2a);
								matrix4x3_transform_vector(&cutscene_camera_matrix, &a3, &a3);
								euler_angles3d_from_vectors3d((real_euler_angles3d *)&v36, a2a, a3);
								camera_update_scripted(0, (real_vector3d *)&transformed_point, &v36, ticks, -1, -1);
								eldorado::hs_return(a2, hs_value::from_long(0));
								return;
							}
						}
					}
				}

				real_vector3d cutscene_camera_position = { cutscene_camera.position.x, cutscene_camera.position.y, cutscene_camera.position.z };
				real_vector3d cutscene_camera_vector = { cutscene_camera.orientation.yaw, cutscene_camera.orientation.pitch, cutscene_camera.orientation.roll };
				camera_update_scripted(reinterpret_cast<unsigned short const &>(cutscene_camera.camera_type), &cutscene_camera_position, &cutscene_camera_vector, ticks, camera, -1);
			}
		}

		eldorado::hs_return(a2, hs_value::from_long(0));
	}
}

void hs_dew_method_stub_evaluate(short op, __int32 thread_index, char a3) // 0x107B73E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_dew_method_stub_evaluate@@YAXFHD@Z");

	hs_stack_frame *const stack_frame = hs_thread_stack(thread_index);
	s_hs_syntax_node *const node = eldorado::hs_syntax_get(stack_frame->expression_index);
	s_hs_script const *script = global_scenario_get()->scripts.get_element(node->line_number);
	if (script && script->type == static_cast<e_hs_script_type>(6))
	{
		Scripting::HS::ScriptMethod *method = (Scripting::HS::ScriptMethod *)script->extern_method;
		if (method)
		{
			method->evaluateProc(op, thread_index, a3);
			return;
		}
		eldorado::hs_return(thread_index, hs_value::get_default(script->return_type));
	}
	else
	{
		eldorado::hs_return(thread_index, hs_value::get_default((e_hs_type)4));
	}
}

bool unit_scripting_vehicle_test_seat(long vehicle_index, unsigned long seat_name, long unit_index) // 0x107B92A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?unit_scripting_vehicle_test_seat@@YA_NJKJ@Z");

	s_unit_data *vehicle = (s_unit_data *)object_try_and_get_and_verify_type(vehicle_index, 0x2003);
	s_unit_data *unit = (s_unit_data *)object_try_and_get_and_verify_type(unit_index, 0x2003);
	if (vehicle && unit)
	{
		s_unit_seat_source seats[64];
		long seat_count = ((short (*)(long, s_unit_seat_source *, long, bool))0xB43340)(vehicle_index, seats, 64, false);
		for (long i = 0; i < seat_count; i++)
		{
			s_unit_seat_definition *seat = seats[i].seat;
			if ((!seat_name || seat_name == -1 || seat_name == seat->seat_animation) && unit->parent_object_index == seats[i].parent_unit_index && unit->seat_index == seats[i].seat_index)
			{
				return true;
			}
		}
	}

	return false;
}

bool unit_scripting_vehicle_test_seat_list_legacy(long vehicle_index, unsigned long seat_name, long list_index) // 0x107B94C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?unit_scripting_vehicle_test_seat_list_legacy@@YA_NJKJ@Z");

	if (object_try_and_get_and_verify_type(vehicle_index, 0x2003))
	{
		s_unit_seat_source seats[64];
		long seat_count = ((short (*)(long, s_unit_seat_source *, long, bool))0xB43340)(vehicle_index, seats, 64, false);
		long list_iterator;
		for (long object_index = ((long (*)(long, long *))0x6EAC20)(list_index, &list_iterator); list_index != -1; list_index = ((long (*)(long, long *))0x6EAC70)(list_index, &list_iterator))
		{
			s_unit_data *unit = (s_unit_data *)object_try_and_get_and_verify_type(object_index, 0x2003);
			if (!unit)
			{
				continue;
			}

			for (long i = 0; i < seat_count; i++)
			{
				if (seat_name && seat_name != -1 && seat_name != seats[i].seat->seat_animation)
				{
					continue;
				}

				if (unit->parent_object_index == seats[i].parent_unit_index && unit->seat_index == seats[i].seat_index)
				{
					return true;
				}
			}
		}
	}

	return false;
}

void hs_vehicle_test_seat_legacy_evaluate(short function_index, __int32 thread_index, char initial) // 0x107B88C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_vehicle_test_seat_legacy_evaluate@@YAXFHD@Z");

	if (hs_value const *args = ((hs_value const *(__cdecl *)(unsigned short, long, bool))0x5972f0)(function_index, thread_index, initial))
	{
		bool result = unit_scripting_vehicle_test_seat(args[0].long_value, args[1].long_value, args[2].long_value);
		eldorado::hs_return_2(thread_index, hs_value::from_bool(result));
	}
}

void hs_vehicle_test_seat_list_legacy_evaluate(short function_index, __int32 thread_index, char initial) // 0x107B89D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_vehicle_test_seat_list_legacy_evaluate@@YAXFHD@Z");

	if (hs_value const *args = eldorado::hs_macro_function_evaluate(function_index, thread_index, initial))
	{
		bool result = unit_scripting_vehicle_test_seat_list_legacy(args[0].long_value, args[1].long_value, args[2].long_value);
		eldorado::hs_return(thread_index, hs_value::from_bool(result));
	}
}

void hs_get_value_string(e_hs_type type, long value, char (&buffer)[256]) // 0x107B79F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_get_value_string@@YAXW4e_hs_type@@JAAY0BAA@D@Z");

	switch (type)
	{
	case 0:
		sprintf_s(buffer, "<unknown>");
		break;
	case 5:
		sprintf_s(buffer, "%s", *(bool *)&value ? "true" : "false");
		break;
	case 6:
		sprintf_s(buffer, "%.3f", *(float *)&value);
		break;
	case 7:
		sprintf_s(buffer, "%d", *(short *)&value);
		break;
	case 8:
		sprintf_s(buffer, "%d", value);
		break;
	case 9:
		sprintf_s(buffer, "%s", (char const *)value);
		break;
	case 10:
		sprintf_s(buffer, "%d", value);
		break;
	case 11:
	{
		char *str = Blam::Cache::StringIDCache::GetCurrent()->GetString(value);
		sprintf_s(buffer, "%s", str ? str : "<invalid>");
		break;
	}
	case 66:
	case 67:
	case 68:
	case 69:
	case 70:
	case 71:
	case 72:
	case 73:
	case 74:
	case 75:
	case 76:
	case 77:
	case 78:
	case 79:
		sprintf_s(buffer, "0x%x", value);
		break;
	case 12:
	case 13:
	case 14:
	case 15:
		sprintf_s(buffer, "%d", *(short *)&value);
		break;
	case 33:
	case 34:
	case 35:
	case 36:
	case 37:
	case 38:
	case 39:
	case 40:
	case 41:
	case 42:
	case 43:
	case 44:
	case 45:
	case 46:
	case 47:
	case 48:
	case 49:
		sprintf_s(buffer, "%s", tag_get_name(value));
		break;
	default:
		sprintf_s(buffer, "%08X", value);
		break;
	}
}

void hs_debug_macro_function_evaluate(long thread_index, long *evaluated_arguments, short function_index) // 0x107B6ED0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_debug_macro_function_evaluate@@YAXJPAJF@Z");

	Modules::ModuleDebug &moduleDebug = Modules::ModuleDebug::Instance();
	s_hs_thread const *thread = hs_thread_get(thread_index);
	hs_stack_frame const *frame = hs_thread_stack(thread_index);
	long const expression_index = frame->expression_index;
	s_hs_syntax_node const *expression = eldorado::hs_syntax_get(expression_index);
	if (thread->script_index == -1)
	{
		return;
	}

	s_hs_script const &script = global_scenario_get()->scripts[thread->script_index];
	if (moduleDebug.VarScriptBreakpoint->ValueInt > 0 && (short)expression_index == moduleDebug.VarScriptBreakpoint->ValueInt)
	{
		DebugBreak();
	}

	if (moduleDebug.VarScriptTrace->ValueInt)
	{
		{
			std::string &scriptFilter = moduleDebug.VarScriptName->ValueString;
			if (!scriptFilter.empty() && scriptFilter.compare(script.name.ascii))
			{
				return;
			}
		}

		s_static_string<8> expr_index_buff;
		expr_index_buff.print("%d", (short)expression_index);
		s_static_string<8192> buffer;
		buffer.print("%s :: expr: %-5s (%s ", script.name.ascii, expr_index_buff.get_string(), script_op_names[function_index]);
		s_hs_script_op const *function = script_ops[function_index];
		{
			for (__int32 i = 0; i < function->argument_count; i++)
			{
				char argument_value[256];
				hs_get_value_string(script_ops[function_index]->args[i], evaluated_arguments[i], argument_value);
				buffer.append(argument_value);
				if (i < function->argument_count - 1)
				{
					buffer.append_print(" ");
				}
			}
		}

		buffer.append_print(")");
		std::string &traceFile = moduleDebug.VarScriptTraceFile->ValueString;
		if (!traceFile.empty())
		{
			static FILE *fp;
			{
				static bool file_initialized;
				if (!file_initialized)
				{
					file_initialized = true;
					fp = _fsopen(traceFile.c_str(), "w+", _SH_DENYNO);
				}
			}

			if (fp)
			{
				fprintf(fp, "%-16s %s\n", script.name.ascii, buffer.get_string());
				fflush(fp);
			}
		}
		else
		{
			static bool console_initialized;
			if (!console_initialized)
			{
				console_initialized = true;
				if (AllocConsole())
				{
					FILE *fp;
					freopen_s(&fp, "CONOUT$", "w", stdout);
				}
			}

			printf("%s\n", buffer.get_string());
		}
	}
}

void hs_thread_main_hook(long thread_index) // 0x107B8790
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_thread_main_hook@@YAXJ@Z");

	void (*const hs_thread_main)(long) = (void (*const)(long))0x598bc0;
	c_data_array<s_hs_thread> *threads = tls_getd().hs_thread_deterministic_data;
	s_hs_thread *thread = (s_hs_thread *)datum_try_and_get(threads, thread_index);
	if (thread == nullptr)
	{
		return;
	}
	hs_thread_main(thread_index);
	short stack_top = *(short *)offset_pointer(thread, 16);
	short thread_type = *(short *)offset_pointer(thread, 28);
	if (thread_type == 3 && !stack_top)
	{
		datum_delete(threads, thread_index);
	}
}

long hs_runtime_script_begin_hook(short script_index, e_hs_script_type script_type, e_hs_script_type thread_type) // 0x107B8660
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_runtime_script_begin_hook@@YAJFW4e_hs_script_type@@0@Z");

	s_scenario *scenario = global_scenario_get();
	if (script_index >= 0 && script_index < scenario->scripts.count)
	{
		s_hs_script &script = scenario->scripts[script_index];
		if (script.type == script_type)
		{
			long thread_index = eldorado::hs_thread_new(thread_type, script_index);
			if (thread_index != -1)
			{
				eldorado::hs_evaluate_runtime(thread_index, script.root_expression_index, 3, nullptr);
				return thread_index;
			}
		}
	}
	return -1;
}

long *hs_macro_function_evaluate_hook(short function_index, long thread_index, bool initial) // 0x107B7D90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_macro_function_evaluate_hook@@YAPAJFJ_N@Z");

	long *(*const hs_arguments_evaluate)(long, short, short const *, bool) = reinterpret_cast<long *(*)(long, short, short const *, bool)>(0x594140);
	hs_stack_frame *stack = hs_thread_stack(thread_index);
	s_hs_syntax_node *node = eldorado::hs_syntax_get(stack->expression_index);
	if (node->flags.test((e_hs_syntax_node_flags)5))
	{
		s_hs_script *script = &global_scenario_get()->scripts[node->line_number];
		short types[16];
		for (long i = 0; i < script->parameters.count; i++)
		{
			types[i] = (short)script->parameters[i].type;
		}

		return hs_arguments_evaluate(thread_index, script->parameters.count, types, initial);
	}
	else
	{
		s_hs_script_op const *op = script_ops[function_index];
		long *result = hs_arguments_evaluate(thread_index, op->argument_count, (short const *)&op->args[0], initial);
		if (result)
		{
			hs_debug_macro_function_evaluate(thread_index, result, function_index);
		}

		return result;
	}
}

void hs_return_hook(long thread_index, hs_value value) // 0x107B8410
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_return_hook@@YAXJUhs_value@@@Z");

	long *(*const hs_destination)(s_hs_thread *, long) = reinterpret_cast<long *(*)(s_hs_thread *, long)>(0x594460);
	long (*const hs_cast)(long, e_hs_type, e_hs_type, long) = reinterpret_cast<long (*)(long, e_hs_type, e_hs_type, long)>(0x5943a0);
	s_hs_thread *thread = hs_thread_get(thread_index);
	hs_stack_frame *stack = hs_thread_stack(thread_index);
	s_hs_syntax_node *node = eldorado::hs_syntax_get(stack->expression_index);
	e_hs_type return_type = (e_hs_type)4;
	if (node->flags.test((e_hs_syntax_node_flags)5))
	{
		return_type = global_scenario_get()->scripts[node->line_number].return_type;
	}
	else if (node->flags.test((e_hs_syntax_node_flags)1))
	{
		short script_index = node->opcode;
		if (script_index == -1)
		{
			return_type = (e_hs_type)4;
		}
		else
		{
			return_type = global_scenario_get()->scripts[script_index].return_type;
		}
	}
	else
	{
		return_type = script_ops[node->opcode]->return_type;
	}

	long *return_value = hs_destination(thread, ((hs_stack_frame *)&thread->stack[stack->parent_stack_frame])->result_destination);
	if (return_value)
	{
		*return_value = hs_cast(thread_index, return_type, node->type, value.long_value);
	}

	eldorado::hs_stack_pop(thread_index);
}

void hs_evaluate_inspect_hook(short op, long thread_index, bool a3) // 0x107B75D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_evaluate_inspect_hook@@YAXFJ_N@Z");

	void (**const g_hs_inspect_function_table)(short, long, char *, long) = reinterpret_cast<void (**)(short, long, char *, long)>(0x18A1090);
	short stack_pointer;
	long *value = (long *)eldorado::hs_stack_allocate(thread_index, 4, 2, &stack_pointer);
	if (!value)
	{
		return;
	}

	s_hs_syntax_node *func_expr = eldorado::hs_syntax_get(hs_thread_stack(thread_index)->expression_index);
	s_hs_syntax_node *name_expr = eldorado::hs_syntax_get(*(long *)func_expr->data);
	long value_expr_index = name_expr->next_expression_index;
	if (a3)
	{
		eldorado::hs_evaluate_runtime(thread_index, value_expr_index, (stack_pointer << 16) | 1, nullptr);
	}
	else
	{
		s_hs_syntax_node *value_expr = eldorado::hs_syntax_get(value_expr_index);
		void (*inspect_function)(short, long, char *, long) = g_hs_inspect_function_table[(short)value_expr->type];
		if (inspect_function)
		{
			char buffer[1024];
			inspect_function(value_expr->type, *value, buffer, 1024);
			Console::WriteLine(buffer);
		}

		eldorado::hs_return(thread_index, hs_value::from_long(0));
	}
}

void hs_evaluate_set_hook(short op, long thread_index, bool a3) // 0x107B78C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_evaluate_set_hook@@YAXFJ_N@Z");

	void (*const hs_set_evaluate)(short, long, bool) = (void (*const)(short, long, bool))0x5957f0;
	s_hs_thread *thread = tls_getd().hs_thread_deterministic_data->try_and_get(thread_index);
	s_hs_syntax_node *node = eldorado::hs_syntax_get(*(long *)&thread->stack[thread->stack_offset]);
	node = eldorado::hs_syntax_get(*(long *)node->data);
	node = eldorado::hs_syntax_get(node->next_expression_index);
	hs_set_evaluate(op, thread_index, a3);
	if (!a3)
	{
		InvalidateGlobal(*(short *)node->data);
	}
}

void cinematic_scripting_start_screen_effect(__int32 cinematic_tag_index, __int32 scene_index, __int32 shot_index, __int32 cinematic_screen_effect_index) // 0x107B4690
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?cinematic_scripting_start_screen_effect@@YAXHHHH@Z");

	s_cinematic_scene_definition *(*const scenario_get_cinematic_scene)(__int32, __int32) = reinterpret_cast<s_cinematic_scene_definition *(*)(__int32, __int32)>(0x9EC9C0);
	unsigned long (*const SpawnScreenEffect)(__int32, __int32, __int32, void *, void *) = reinterpret_cast<unsigned long (*)(__int32, __int32, __int32, void *, void *)>(0x683060);
	void (*const cinematic_screen_effect_new)(__int32, unsigned long) = reinterpret_cast<void (*)(__int32, unsigned long)>(0x67E610);

	s_cinematic_scene_definition *const cisc = scenario_get_cinematic_scene(cinematic_tag_index, scene_index);
	if (cisc && shot_index >= 0 && shot_index < cisc->shots.count)
	{
		s_cinematic_scene_shot *const shot = &cisc->shots[shot_index];
		if (shot && cinematic_screen_effect_index >= 0 && cinematic_screen_effect_index < shot->screen_effects.count)
		{
			s_cinematic_shot_screen_effect *cinematic_screen_effect = &shot->screen_effects[cinematic_screen_effect_index];
			if (cinematic_screen_effect->start_frame <= cinematic_screen_effect->end_frame)
			{
				screen_effect_new(cinematic_screen_effect->effect.index, -1, -1, &global_origin3d, &global_null_rectangle2d);
			}
			else
			{
				long datum_index = screen_effect_new2(cinematic_screen_effect->effect.index, -1, -1, &global_origin3d, &global_null_rectangle2d, false, true);
				cinematic_screen_effect_new(cinematic_screen_effect_index, datum_index);
			}
		}
	}
}

void cinematic_scripting_stop_screen_effect(__int32 cinematic_tag_index, __int32 scene_index, __int32 shot_index, __int32 cinematic_screen_effect_index) // 0x107B4840
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?cinematic_scripting_stop_screen_effect@@YAXHHHH@Z");

	s_cinematic_scene_definition *(*const scenario_get_cinematic_scene)(__int32, __int32) = reinterpret_cast<s_cinematic_scene_definition *(*)(__int32, __int32)>(0x9EC9C0);
	unsigned long (*const cinematic_screen_effect_get_datum)(__int32) = reinterpret_cast<unsigned long (*)(__int32)>(0x67E5C0);
	void (*const cinematic_screen_effect_destroy_internal)(__int32) = reinterpret_cast<void (*)(__int32)>(0x67E4F0);

	s_cinematic_scene_definition *const cisc = scenario_get_cinematic_scene(cinematic_tag_index, scene_index);
	if (cisc && shot_index >= 0 && shot_index < cisc->shots.count)
	{
		s_cinematic_scene_shot *const shot = &cisc->shots[shot_index];
		if (shot && cinematic_screen_effect_index >= 0 && cinematic_screen_effect_index < shot->screen_effects.count)
		{
			unsigned long sefc_datum = cinematic_screen_effect_get_datum(cinematic_screen_effect_index);
			if (sefc_datum != 0xFFFFFFFF)
			{
				reinterpret_cast<void (*)(long)>(0x682EC0)(sefc_datum);
				cinematic_screen_effect_destroy_internal(cinematic_screen_effect_index);
			}
		}
	}
}

long ui_get_current_music_id_hook() // 0x107B91C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ui_get_current_music_id_hook@@YAJXZ");

	if (((bool(*)())0x531E90)())
	{
		__int32 lobbyType = Blam::Network::GetLobbyType();
		if (lobbyType == -1)
		{
			return 1;
		}

		Blam::Network::Session *session = Blam::Network::GetActiveSession();
		__int32 networkMode = Blam::Network::GetNetworkMode();

		if (session)
		{
			if (!session->IsHost() || networkMode == 3)
			{
				if (Server::Stats::localPlayerIsPostMatch())
				{
					return 3;
				}
				else
				{
					return 2;
				}
			}
			else
			{
				return 1;
			}
		}
	}

	return -1;
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_flags<enum e_hs_syntax_node_flags,unsigned short>::test(e_hs_syntax_node_flags) const;
template bool c_tag_block<s_cinematic_scene_object>::try_get_element(__int32, s_cinematic_scene_object **) const;
template bool c_tag_block<s_cinematic_scene_shot>::try_get_element(__int32, s_cinematic_scene_shot **) const;
template bool c_tag_block<s_cinematic_shot_screen_effect>::try_get_element(__int32, s_cinematic_shot_screen_effect **) const;
template bool c_tag_block<s_scenario_campaign_player>::try_get_element(__int32, s_scenario_campaign_player **) const;
template c_enum<enum e_hs_type,short>::c_enum(e_hs_type const &);
template c_enum<enum e_hs_type,short>::c_enum(short const &);
template c_enum<enum e_hs_type,short>::operator short() const;
template c_enum<enum e_object_type,char>::operator char() const;
template c_flags<enum e_cinematic_object_flags,long> c_flags<enum e_cinematic_object_flags,long>::operator&(__int32 const) const;
template c_flags<enum e_cinematic_object_flags,long> c_flags<enum e_cinematic_object_flags,long>::operator&(e_cinematic_object_flags const &) const;
template c_flags<enum e_cinematic_object_flags,long>::c_flags(long const &);
template c_flags<enum e_cinematic_object_flags,long>::operator bool() const;
template char const * s_static_string<8192>::append(char const *);
template char const * s_static_string<8192>::append_print(char const *, ...);
template char const * s_static_string<8192>::get_string() const;
template char const * s_static_string<8192>::print(char const *, ...);
template char const * s_static_string<8>::get_string() const;
template char const * s_static_string<8>::print(char const *, ...);
template long s_static_string<8192>::length();
template s_cinematic_scene_object & c_tag_block<s_cinematic_scene_object>::operator[](__int32);
template s_cinematic_scene_object * c_tag_block<s_cinematic_scene_object>::get_element(__int32) const;
template s_cinematic_scene_object const & c_tag_block<s_cinematic_scene_object>::operator[](__int32) const;
template s_cinematic_scene_shot & c_tag_block<s_cinematic_scene_shot>::operator[](__int32);
template s_cinematic_scene_shot * c_tag_block<s_cinematic_scene_shot>::get_element(__int32) const;
template s_cinematic_shot_screen_effect & c_tag_block<s_cinematic_shot_screen_effect>::operator[](__int32);
template s_cinematic_shot_screen_effect * c_tag_block<s_cinematic_shot_screen_effect>::get_element(__int32) const;
template s_game_globals_player_representation & c_tag_block<s_game_globals_player_representation>::operator[](__int32);
template s_game_globals_player_representation * c_tag_block<s_game_globals_player_representation>::get_element(__int32) const;
template s_hs_script_parameter & c_tag_block<s_hs_script_parameter>::operator[](__int32);
template s_scenario_campaign_player & c_tag_block<s_scenario_campaign_player>::operator[](__int32);
template s_scenario_campaign_player * c_tag_block<s_scenario_campaign_player>::get_element(__int32) const;
template unsigned long Blam::BitStream::ReadUnsigned<unsigned long>(__int32);
template unsigned short Blam::BitStream::ReadUnsigned<unsigned short>(__int32);
template void Blam::BitStream::Write<long>(long, __int32);
template void Blam::BitStream::Write<short>(short, __int32);
template void Blam::BitStream::WriteUnsigned<unsigned long>(unsigned long, __int32);
template void Blam::BitStream::WriteUnsigned<unsigned short>(unsigned short, __int32);
template void Pointer::Write<void (__cdecl*)(short,long,bool)>(void (*const value)(short, long, bool)) const;
template void const s_static_string<8192>::print_va(char const *, char *);
template void const s_static_string<8>::print_va(char const *, char *);
template void s_static_string<8192>::append_print_va(char const *, char *);

/* ---------- script op definitions */

// The original registers these ops in script_ops at runtime; each one is a s_hs_script_op
// header followed by its argument types and a zero terminator, built by a dynamic initializer.
namespace hades_file_local
{
	template<int k_argument_count>
	struct s_hs_script_op_definition
	{
		c_enum<e_hs_type,short> return_type;
		void (*callback)(short, __int32, char);
		char const *special_syntax;
		short argument_count;
		c_enum<e_hs_type,short> args[k_argument_count];
		short terminator[1];
	};

	struct s_hs_script_op_definition_no_arguments
	{
		c_enum<e_hs_type,short> return_type;
		void (*callback)(short, __int32, char);
		char const *special_syntax;
		short argument_count;
		short terminator;
	};

	s_hs_script_op_definition<1> hs_mp_wake_script_evaluate_op = { _hs_type_void, hs_mp_wake_script_evaluate, "", 1, { _hs_type_script } };
	s_hs_script_op_definition<1> hs_mp_sync_global_evaluate_op = { _hs_type_void, hs_mp_sync_global_evaluate, "", 1, { _hs_type_string } };
	s_hs_script_op_definition<5> hs_cinematic_scripting_start_animation_legacy_op = { _hs_type_void, hs_cinematic_scripting_start_animation_legacy_evaluate, "", 5, { _hs_type_long, _hs_type_long, _hs_type_long, _hs_type_object, _hs_type_string_id } };
	s_hs_script_op_definition<4> hs_cinematic_scripting_create_object_legacy_op = { _hs_type_void, hs_cinematic_scripting_create_object_legacy_evaluate, "", 4, { _hs_type_long, _hs_type_long, _hs_type_long, _hs_type_object_name } };
	s_hs_script_op_definition<7> hs_cinematic_scripting_create_and_animate_object_legacy_op = { _hs_type_void, hs_cinematic_scripting_create_and_animate_object_legacy_evaluate, "", 7, { _hs_type_long, _hs_type_long, _hs_type_long, _hs_type_object_name, _hs_type_object, _hs_type_string_id, _hs_type_boolean } };
	s_hs_script_op_definition<6> hs_cinematic_scripting_create_and_animate_object_no_animation_legacy_op = { _hs_type_void, hs_cinematic_scripting_create_and_animate_object_no_animation_legacy_evaluate, "", 6, { _hs_type_long, _hs_type_long, _hs_type_long, _hs_type_object_name, _hs_type_object, _hs_type_boolean } };
	s_hs_script_op_definition<6> hs_cinematic_scripting_create_and_animate_cinematic_object_legacy_op = { _hs_type_void, hs_cinematic_scripting_create_and_animate_cinematic_object_legacy_evaluate, "", 6, { _hs_type_long, _hs_type_long, _hs_type_long, _hs_type_object, _hs_type_string_id, _hs_type_boolean } };
	s_hs_script_op_definition<4> hs_cinematic_scripting_destroy_object_legacy_op = { _hs_type_void, hs_cinematic_scripting_destroy_object_legacy_evaluate, "", 4, { _hs_type_long, _hs_type_long, _hs_type_long, _hs_type_object } };
	s_hs_script_op_definition<2> hs_camera_set_op = { _hs_type_void, hs_camera_set_evaluate, "", 2, { _hs_type_cutscene_camera_point, _hs_type_short } };
	s_hs_script_op_definition_no_arguments hs_dew_method_stub_op = { _hs_type_unparsed, hs_dew_method_stub_evaluate, "proxy script function invocation to a registered script method", 0 };
	s_hs_script_op_definition<3> hs_vehicle_test_seat_legacy_op = { _hs_type_boolean, hs_vehicle_test_seat_legacy_evaluate, "", 3, { _hs_type_vehicle, _hs_type_string_id, _hs_type_unit } };
	s_hs_script_op_definition<3> hs_vehicle_test_seat_list_legacy_op = { _hs_type_boolean, hs_vehicle_test_seat_list_legacy_evaluate, "", 3, { _hs_type_vehicle, _hs_type_string_id, _hs_type_object_list } };
}

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { namespace hades_file_local_HaloScriptPatches { real_rectangle2d global_null_rectangle2d; } }
namespace hades_file_local { c_simulation_hs_script_wake_event_definition hs_wake_script_event_definition; }
namespace hades_file_local { c_simulation_hs_sync_global_event_definition hs_sync_global_event_definition; }

// The script op table and its names, as linked into mtndew.dll: the game's own ops, with
// the ones ElDewrito adds or replaces pointing at the definitions above.
extern "C" s_hs_script_op const *script_ops[1707] =
{
	reinterpret_cast<s_hs_script_op const *>(0x167A7D8), reinterpret_cast<s_hs_script_op const *>(0x167A814), reinterpret_cast<s_hs_script_op const *>(0x167A838), reinterpret_cast<s_hs_script_op const *>(0x167A8A8),
	reinterpret_cast<s_hs_script_op const *>(0x167A8F4), reinterpret_cast<s_hs_script_op const *>(0x167A918), reinterpret_cast<s_hs_script_op const *>(0x167A99C), reinterpret_cast<s_hs_script_op const *>(0x167A9AC),
	reinterpret_cast<s_hs_script_op const *>(0x167AA0C), reinterpret_cast<s_hs_script_op const *>(0x167AA48), reinterpret_cast<s_hs_script_op const *>(0x167AA6C), reinterpret_cast<s_hs_script_op const *>(0x167AAD0),
	reinterpret_cast<s_hs_script_op const *>(0x167AAE0), reinterpret_cast<s_hs_script_op const *>(0x167AB28), reinterpret_cast<s_hs_script_op const *>(0x167AB4C), reinterpret_cast<s_hs_script_op const *>(0x167ABAC),
	reinterpret_cast<s_hs_script_op const *>(0x167ABBC), reinterpret_cast<s_hs_script_op const *>(0x167AC00), reinterpret_cast<s_hs_script_op const *>(0x167AC4C), reinterpret_cast<s_hs_script_op const *>(0x167AC5C),
	reinterpret_cast<s_hs_script_op const *>(0x167AC7C), reinterpret_cast<s_hs_script_op const *>(0x167ACDC), reinterpret_cast<s_hs_script_op const *>(0x167AD20), reinterpret_cast<s_hs_script_op const *>(0x167AD58),
	reinterpret_cast<s_hs_script_op const *>(0x167ADB0), reinterpret_cast<s_hs_script_op const *>(0x167AE58), reinterpret_cast<s_hs_script_op const *>(0x167B004), reinterpret_cast<s_hs_script_op const *>(0x1672B50),
	reinterpret_cast<s_hs_script_op const *>(0x1672D08), reinterpret_cast<s_hs_script_op const *>(0x1672E18), reinterpret_cast<s_hs_script_op const *>(0x1672F74), reinterpret_cast<s_hs_script_op const *>(0x1673028),
	reinterpret_cast<s_hs_script_op const *>(0x16730F0), reinterpret_cast<s_hs_script_op const *>(0x1673264), reinterpret_cast<s_hs_script_op const *>(0x16733AC), reinterpret_cast<s_hs_script_op const *>(0x16734E4),
	reinterpret_cast<s_hs_script_op const *>(0x16735CC), reinterpret_cast<s_hs_script_op const *>(0x16736E0), reinterpret_cast<s_hs_script_op const *>(0x16737BC), reinterpret_cast<s_hs_script_op const *>(0x16738D0),
	reinterpret_cast<s_hs_script_op const *>(0x16739D4), reinterpret_cast<s_hs_script_op const *>(0x1673B00), reinterpret_cast<s_hs_script_op const *>(0x1673C78), reinterpret_cast<s_hs_script_op const *>(0x1673D88),
	reinterpret_cast<s_hs_script_op const *>(0x1673EA4), reinterpret_cast<s_hs_script_op const *>(0x167400C), reinterpret_cast<s_hs_script_op const *>(0x167419C), reinterpret_cast<s_hs_script_op const *>(0x16742D4),
	reinterpret_cast<s_hs_script_op const *>(0x1674444), reinterpret_cast<s_hs_script_op const *>(0x16745E4), reinterpret_cast<s_hs_script_op const *>(0x1674774), reinterpret_cast<s_hs_script_op const *>(0x16748C0),
	reinterpret_cast<s_hs_script_op const *>(0x1674A04), reinterpret_cast<s_hs_script_op const *>(0x1674B8C), reinterpret_cast<s_hs_script_op const *>(0x1674CE4), reinterpret_cast<s_hs_script_op const *>(0x1674DEC),
	reinterpret_cast<s_hs_script_op const *>(0x1674FB8), reinterpret_cast<s_hs_script_op const *>(0x1675108), reinterpret_cast<s_hs_script_op const *>(0x1675224), reinterpret_cast<s_hs_script_op const *>(0x167534C),
	reinterpret_cast<s_hs_script_op const *>(0x16754C8), reinterpret_cast<s_hs_script_op const *>(0x16755E0), reinterpret_cast<s_hs_script_op const *>(0x1675744), reinterpret_cast<s_hs_script_op const *>(0x16757F4),
	reinterpret_cast<s_hs_script_op const *>(0x1675978), reinterpret_cast<s_hs_script_op const *>(0x1675A88), reinterpret_cast<s_hs_script_op const *>(0x1675BA8), reinterpret_cast<s_hs_script_op const *>(0x1675D0C),
	reinterpret_cast<s_hs_script_op const *>(0x1675E20), reinterpret_cast<s_hs_script_op const *>(0x1675F90), reinterpret_cast<s_hs_script_op const *>(0x1676094), reinterpret_cast<s_hs_script_op const *>(0x16761EC),
	reinterpret_cast<s_hs_script_op const *>(0x16762F4), reinterpret_cast<s_hs_script_op const *>(0x16763BC), reinterpret_cast<s_hs_script_op const *>(0x1676504), reinterpret_cast<s_hs_script_op const *>(0x167663C),
	reinterpret_cast<s_hs_script_op const *>(0x16767B0), reinterpret_cast<s_hs_script_op const *>(0x16768AC), reinterpret_cast<s_hs_script_op const *>(0x16769B0), reinterpret_cast<s_hs_script_op const *>(0x1676B24),
	reinterpret_cast<s_hs_script_op const *>(0x1676C1C), reinterpret_cast<s_hs_script_op const *>(0x1676D4C), reinterpret_cast<s_hs_script_op const *>(0x1676E08), reinterpret_cast<s_hs_script_op const *>(0x1676F08),
	reinterpret_cast<s_hs_script_op const *>(0x1677028), reinterpret_cast<s_hs_script_op const *>(0x1677168), reinterpret_cast<s_hs_script_op const *>(0x1677290), reinterpret_cast<s_hs_script_op const *>(0x16773F8),
	reinterpret_cast<s_hs_script_op const *>(0x1677548), reinterpret_cast<s_hs_script_op const *>(0x1677668), reinterpret_cast<s_hs_script_op const *>(0x16777C0), reinterpret_cast<s_hs_script_op const *>(0x1677948),
	reinterpret_cast<s_hs_script_op const *>(0x1677A78), reinterpret_cast<s_hs_script_op const *>(0x1677BD0), reinterpret_cast<s_hs_script_op const *>(0x1677D30), reinterpret_cast<s_hs_script_op const *>(0x1677E64),
	reinterpret_cast<s_hs_script_op const *>(0x1677FDC), reinterpret_cast<s_hs_script_op const *>(0x1678144), reinterpret_cast<s_hs_script_op const *>(0x167820C), reinterpret_cast<s_hs_script_op const *>(0x167838C),
	reinterpret_cast<s_hs_script_op const *>(0x1678520), reinterpret_cast<s_hs_script_op const *>(0x1678678), reinterpret_cast<s_hs_script_op const *>(0x16787E0), reinterpret_cast<s_hs_script_op const *>(0x1678968),
	reinterpret_cast<s_hs_script_op const *>(0x1678B6C), reinterpret_cast<s_hs_script_op const *>(0x1678CE4), reinterpret_cast<s_hs_script_op const *>(0x1678DF0), reinterpret_cast<s_hs_script_op const *>(0x1678F7C),
	reinterpret_cast<s_hs_script_op const *>(0x16790E0), reinterpret_cast<s_hs_script_op const *>(0x1679218), reinterpret_cast<s_hs_script_op const *>(0x1679374), reinterpret_cast<s_hs_script_op const *>(0x16794EC),
	reinterpret_cast<s_hs_script_op const *>(0x1679644), reinterpret_cast<s_hs_script_op const *>(0x16797C8), reinterpret_cast<s_hs_script_op const *>(0x1679978), reinterpret_cast<s_hs_script_op const *>(0x1679AD8),
	reinterpret_cast<s_hs_script_op const *>(0x1679BF0), reinterpret_cast<s_hs_script_op const *>(0x1679D88), reinterpret_cast<s_hs_script_op const *>(0x1679E38), reinterpret_cast<s_hs_script_op const *>(0x1679F30),
	reinterpret_cast<s_hs_script_op const *>(0x1679FB4), reinterpret_cast<s_hs_script_op const *>(0x167A12C), reinterpret_cast<s_hs_script_op const *>(0x167A278), reinterpret_cast<s_hs_script_op const *>(0x167A3F8),
	reinterpret_cast<s_hs_script_op const *>(0x167A55C), reinterpret_cast<s_hs_script_op const *>(0x167A6A0), reinterpret_cast<s_hs_script_op const *>(0x167A858), reinterpret_cast<s_hs_script_op const *>(0x167A9BC),
	reinterpret_cast<s_hs_script_op const *>(0x167AB5C), reinterpret_cast<s_hs_script_op const *>(0x167ACB0), reinterpret_cast<s_hs_script_op const *>(0x167AE7C), reinterpret_cast<s_hs_script_op const *>(0x167AFE0),
	reinterpret_cast<s_hs_script_op const *>(0x1672B24), reinterpret_cast<s_hs_script_op const *>(0x1672C24), reinterpret_cast<s_hs_script_op const *>(0x1672DA4), reinterpret_cast<s_hs_script_op const *>(0x1672F3C),
	reinterpret_cast<s_hs_script_op const *>(0x167308C), reinterpret_cast<s_hs_script_op const *>(0x16731E8), reinterpret_cast<s_hs_script_op const *>(0x1673300), reinterpret_cast<s_hs_script_op const *>(0x1673464),
	reinterpret_cast<s_hs_script_op const *>(0x1673594), reinterpret_cast<s_hs_script_op const *>(0x1673708), reinterpret_cast<s_hs_script_op const *>(0x16738A4), reinterpret_cast<s_hs_script_op const *>(0x1673A28),
	reinterpret_cast<s_hs_script_op const *>(0x1673B94), reinterpret_cast<s_hs_script_op const *>(0x1673D3C), reinterpret_cast<s_hs_script_op const *>(0x1673DE8), reinterpret_cast<s_hs_script_op const *>(0x1673F1C),
	reinterpret_cast<s_hs_script_op const *>(0x1674054), reinterpret_cast<s_hs_script_op const *>(0x167423C), reinterpret_cast<s_hs_script_op const *>(0x16742FC), reinterpret_cast<s_hs_script_op const *>(0x16743A8),
	reinterpret_cast<s_hs_script_op const *>(0x1674458), reinterpret_cast<s_hs_script_op const *>(0x1674550), reinterpret_cast<s_hs_script_op const *>(0x1674724), reinterpret_cast<s_hs_script_op const *>(0x16748AC),
	reinterpret_cast<s_hs_script_op const *>(0x1674950), reinterpret_cast<s_hs_script_op const *>(0x1674A68), reinterpret_cast<s_hs_script_op const *>(0x1674BE0), reinterpret_cast<s_hs_script_op const *>(0x1674CF8),
	reinterpret_cast<s_hs_script_op const *>(0x1674DC8), reinterpret_cast<s_hs_script_op const *>(0x1674EB0), reinterpret_cast<s_hs_script_op const *>(0x1674F6C), reinterpret_cast<s_hs_script_op const *>(0x167502C),
	reinterpret_cast<s_hs_script_op const *>(0x16750B8), reinterpret_cast<s_hs_script_op const *>(0x1675184), reinterpret_cast<s_hs_script_op const *>(0x16751FC), reinterpret_cast<s_hs_script_op const *>(0x1675324),
	reinterpret_cast<s_hs_script_op const *>(0x1675428), reinterpret_cast<s_hs_script_op const *>(0x1675560), reinterpret_cast<s_hs_script_op const *>(0x16756C4), reinterpret_cast<s_hs_script_op const *>(0x16757E0),
	reinterpret_cast<s_hs_script_op const *>(0x16758F0), reinterpret_cast<s_hs_script_op const *>(0x1675A4C), reinterpret_cast<s_hs_script_op const *>(0x1675BBC), reinterpret_cast<s_hs_script_op const *>(0x1675C6C),
	reinterpret_cast<s_hs_script_op const *>(0x1675D9C), reinterpret_cast<s_hs_script_op const *>(0x1675F3C), reinterpret_cast<s_hs_script_op const *>(0x167607C), reinterpret_cast<s_hs_script_op const *>(0x1676200),
	reinterpret_cast<s_hs_script_op const *>(0x1676308), reinterpret_cast<s_hs_script_op const *>(0x1676468), reinterpret_cast<s_hs_script_op const *>(0x1676594), reinterpret_cast<s_hs_script_op const *>(0x1676678),
	reinterpret_cast<s_hs_script_op const *>(0x1676778), reinterpret_cast<s_hs_script_op const *>(0x1676888), reinterpret_cast<s_hs_script_op const *>(0x16769C4), reinterpret_cast<s_hs_script_op const *>(0x1676AFC),
	reinterpret_cast<s_hs_script_op const *>(0x1676C44), reinterpret_cast<s_hs_script_op const *>(0x1676D8C), reinterpret_cast<s_hs_script_op const *>(0x1676E7C), reinterpret_cast<s_hs_script_op const *>(0x1676F8C),
	reinterpret_cast<s_hs_script_op const *>(0x1677094), reinterpret_cast<s_hs_script_op const *>(0x16771DC), reinterpret_cast<s_hs_script_op const *>(0x167736C), reinterpret_cast<s_hs_script_op const *>(0x16774E4),
	reinterpret_cast<s_hs_script_op const *>(0x16775D8), reinterpret_cast<s_hs_script_op const *>(0x167777C), reinterpret_cast<s_hs_script_op const *>(0x16778FC), reinterpret_cast<s_hs_script_op const *>(0x1677AA4),
	reinterpret_cast<s_hs_script_op const *>(0x1677BBC), reinterpret_cast<s_hs_script_op const *>(0x1677D58), reinterpret_cast<s_hs_script_op const *>(0x1677E50), reinterpret_cast<s_hs_script_op const *>(0x167803C),
	reinterpret_cast<s_hs_script_op const *>(0x167811C), reinterpret_cast<s_hs_script_op const *>(0x16781D0), reinterpret_cast<s_hs_script_op const *>(0x16782C8), reinterpret_cast<s_hs_script_op const *>(0x16783A0),
	reinterpret_cast<s_hs_script_op const *>(0x1678434), reinterpret_cast<s_hs_script_op const *>(0x1678548), reinterpret_cast<s_hs_script_op const *>(0x16785E4), reinterpret_cast<s_hs_script_op const *>(0x16786C8),
	reinterpret_cast<s_hs_script_op const *>(0x1678794), reinterpret_cast<s_hs_script_op const *>(0x167889C), reinterpret_cast<s_hs_script_op const *>(0x1678928), reinterpret_cast<s_hs_script_op const *>(0x1678A20),
	reinterpret_cast<s_hs_script_op const *>(0x1678B2C), reinterpret_cast<s_hs_script_op const *>(0x1678BF0), reinterpret_cast<s_hs_script_op const *>(0x1678CAC), reinterpret_cast<s_hs_script_op const *>(0x1678D70),
	reinterpret_cast<s_hs_script_op const *>(0x1678E30), reinterpret_cast<s_hs_script_op const *>(0x1678F2C), reinterpret_cast<s_hs_script_op const *>(0x1678FBC), reinterpret_cast<s_hs_script_op const *>(0x16790BC),
	reinterpret_cast<s_hs_script_op const *>(0x1679170), reinterpret_cast<s_hs_script_op const *>(0x1679240), reinterpret_cast<s_hs_script_op const *>(0x16792D0), reinterpret_cast<s_hs_script_op const *>(0x1679458),
	reinterpret_cast<s_hs_script_op const *>(0x16795B8), reinterpret_cast<s_hs_script_op const *>(0x1679764), reinterpret_cast<s_hs_script_op const *>(0x16798E0), reinterpret_cast<s_hs_script_op const *>(0x1679A64),
	reinterpret_cast<s_hs_script_op const *>(0x1679C18), reinterpret_cast<s_hs_script_op const *>(0x1679D74), reinterpret_cast<s_hs_script_op const *>(0x1679ED0), reinterpret_cast<s_hs_script_op const *>(0x167A028),
	reinterpret_cast<s_hs_script_op const *>(0x167A1C8), reinterpret_cast<s_hs_script_op const *>(0x167A31C), reinterpret_cast<s_hs_script_op const *>(0x167A46C), reinterpret_cast<s_hs_script_op const *>(0x167A5A4),
	reinterpret_cast<s_hs_script_op const *>(0x167A6DC), reinterpret_cast<s_hs_script_op const *>(0x167A8E0), reinterpret_cast<s_hs_script_op const *>(0x167AA7C), reinterpret_cast<s_hs_script_op const *>(0x167AC20),
	reinterpret_cast<s_hs_script_op const *>(0x167AEB4), reinterpret_cast<s_hs_script_op const *>(0x1672A44), reinterpret_cast<s_hs_script_op const *>(0x1672C78), reinterpret_cast<s_hs_script_op const *>(0x1672EB8),
	reinterpret_cast<s_hs_script_op const *>(0x1673064), reinterpret_cast<s_hs_script_op const *>(0x16732AC), reinterpret_cast<s_hs_script_op const *>(0x16734A0), reinterpret_cast<s_hs_script_op const *>(0x16735E0),
	reinterpret_cast<s_hs_script_op const *>(0x16736F4), reinterpret_cast<s_hs_script_op const *>(0x1673858), reinterpret_cast<s_hs_script_op const *>(0x1673998), reinterpret_cast<s_hs_script_op const *>(0x1673A50),
	reinterpret_cast<s_hs_script_op const *>(0x1673B80), reinterpret_cast<s_hs_script_op const *>(0x1673D04), reinterpret_cast<s_hs_script_op const *>(0x1673E1C), reinterpret_cast<s_hs_script_op const *>(0x1673F44),
	reinterpret_cast<s_hs_script_op const *>(0x1674134), reinterpret_cast<s_hs_script_op const *>(0x16742A8), reinterpret_cast<s_hs_script_op const *>(0x16743F4), reinterpret_cast<s_hs_script_op const *>(0x1674538),
	reinterpret_cast<s_hs_script_op const *>(0x16746A0), reinterpret_cast<s_hs_script_op const *>(0x16747D8), reinterpret_cast<s_hs_script_op const *>(0x1674960), reinterpret_cast<s_hs_script_op const *>(0x1674AE0),
	reinterpret_cast<s_hs_script_op const *>(0x1674C3C), reinterpret_cast<s_hs_script_op const *>(0x1674D8C), reinterpret_cast<s_hs_script_op const *>(0x1674F14), reinterpret_cast<s_hs_script_op const *>(0x1675050),
	reinterpret_cast<s_hs_script_op const *>(0x1675198), reinterpret_cast<s_hs_script_op const *>(0x16752C0), reinterpret_cast<s_hs_script_op const *>(0x1675400), reinterpret_cast<s_hs_script_op const *>(0x167553C),
	reinterpret_cast<s_hs_script_op const *>(0x16756D8), reinterpret_cast<s_hs_script_op const *>(0x167581C), reinterpret_cast<s_hs_script_op const *>(0x16759B0), reinterpret_cast<s_hs_script_op const *>(0x1675AB0),
	reinterpret_cast<s_hs_script_op const *>(0x1675BE4), reinterpret_cast<s_hs_script_op const *>(0x1675CF8), reinterpret_cast<s_hs_script_op const *>(0x1675E60), reinterpret_cast<s_hs_script_op const *>(0x1675FC8),
	reinterpret_cast<s_hs_script_op const *>(0x1676104), reinterpret_cast<s_hs_script_op const *>(0x1676234), reinterpret_cast<s_hs_script_op const *>(0x16763F4), reinterpret_cast<s_hs_script_op const *>(0x167656C),
	reinterpret_cast<s_hs_script_op const *>(0x167669C), reinterpret_cast<s_hs_script_op const *>(0x16767C4), reinterpret_cast<s_hs_script_op const *>(0x16768EC), reinterpret_cast<s_hs_script_op const *>(0x1676A54),
	reinterpret_cast<s_hs_script_op const *>(0x1676BC8), reinterpret_cast<s_hs_script_op const *>(0x1676D60), reinterpret_cast<s_hs_script_op const *>(0x1676EA4), reinterpret_cast<s_hs_script_op const *>(0x1676FC4),
	reinterpret_cast<s_hs_script_op const *>(0x167717C), reinterpret_cast<s_hs_script_op const *>(0x1677330), reinterpret_cast<s_hs_script_op const *>(0x1677460), reinterpret_cast<s_hs_script_op const *>(0x16775B4),
	reinterpret_cast<s_hs_script_op const *>(0x1677704), reinterpret_cast<s_hs_script_op const *>(0x1677888), reinterpret_cast<s_hs_script_op const *>(0x1677984), reinterpret_cast<s_hs_script_op const *>(0x1677AF0),
	reinterpret_cast<s_hs_script_op const *>(0x1677C0C), reinterpret_cast<s_hs_script_op const *>(0x1677CD8), reinterpret_cast<s_hs_script_op const *>(0x1677DD0), reinterpret_cast<s_hs_script_op const *>(0x1677F20),
	reinterpret_cast<s_hs_script_op const *>(0x1678058), reinterpret_cast<s_hs_script_op const *>(0x1678180), reinterpret_cast<s_hs_script_op const *>(0x1678350), reinterpret_cast<s_hs_script_op const *>(0x16784E0),
	reinterpret_cast<s_hs_script_op const *>(0x16785D0), reinterpret_cast<s_hs_script_op const *>(0x1678748), reinterpret_cast<s_hs_script_op const *>(0x16788D8), reinterpret_cast<s_hs_script_op const *>(0x1678A74),
	reinterpret_cast<s_hs_script_op const *>(0x1678C14), reinterpret_cast<s_hs_script_op const *>(0x1678D5C), reinterpret_cast<s_hs_script_op const *>(0x1678EF4), reinterpret_cast<s_hs_script_op const *>(0x1679048),
	reinterpret_cast<s_hs_script_op const *>(0x16791F0), reinterpret_cast<s_hs_script_op const *>(0x1679324), reinterpret_cast<s_hs_script_op const *>(0x1679498), reinterpret_cast<s_hs_script_op const *>(0x16795D0),
	reinterpret_cast<s_hs_script_op const *>(0x1679728), reinterpret_cast<s_hs_script_op const *>(0x1679884), reinterpret_cast<s_hs_script_op const *>(0x16799C0), reinterpret_cast<s_hs_script_op const *>(0x1679B64),
	reinterpret_cast<s_hs_script_op const *>(0x1679CE8), reinterpret_cast<s_hs_script_op const *>(0x1679EA0), reinterpret_cast<s_hs_script_op const *>(0x167A078), reinterpret_cast<s_hs_script_op const *>(0x167A17C),
	reinterpret_cast<s_hs_script_op const *>(0x167A248), reinterpret_cast<s_hs_script_op const *>(0x167A344), reinterpret_cast<s_hs_script_op const *>(0x167A40C), reinterpret_cast<s_hs_script_op const *>(0x167A4E4),
	reinterpret_cast<s_hs_script_op const *>(0x167A5CC), reinterpret_cast<s_hs_script_op const *>(0x167A67C), reinterpret_cast<s_hs_script_op const *>(0x167A778), reinterpret_cast<s_hs_script_op const *>(0x167A894),
	reinterpret_cast<s_hs_script_op const *>(0x167A978), reinterpret_cast<s_hs_script_op const *>(0x167AB14), reinterpret_cast<s_hs_script_op const *>(0x167AC6C), reinterpret_cast<s_hs_script_op const *>(0x167AE30),
	reinterpret_cast<s_hs_script_op const *>(0x167AF8C), reinterpret_cast<s_hs_script_op const *>(0x1672A84), reinterpret_cast<s_hs_script_op const *>(0x1672BE8), reinterpret_cast<s_hs_script_op const *>(0x1672D20),
	reinterpret_cast<s_hs_script_op const *>(0x1672DE4), reinterpret_cast<s_hs_script_op const *>(0x1672EEC), reinterpret_cast<s_hs_script_op const *>(0x1673050), reinterpret_cast<s_hs_script_op const *>(0x16731B0),
	reinterpret_cast<s_hs_script_op const *>(0x167333C), reinterpret_cast<s_hs_script_op const *>(0x16734BC), reinterpret_cast<s_hs_script_op const *>(0x167361C), reinterpret_cast<s_hs_script_op const *>(0x16737F4),
	reinterpret_cast<s_hs_script_op const *>(0x1673920), reinterpret_cast<s_hs_script_op const *>(0x1673A9C), reinterpret_cast<s_hs_script_op const *>(0x1673BBC), reinterpret_cast<s_hs_script_op const *>(0x1673D18),
	reinterpret_cast<s_hs_script_op const *>(0x1673E30), reinterpret_cast<s_hs_script_op const *>(0x1673F7C), reinterpret_cast<s_hs_script_op const *>(0x167414C), reinterpret_cast<s_hs_script_op const *>(0x1674330),
	reinterpret_cast<s_hs_script_op const *>(0x1674408), reinterpret_cast<s_hs_script_op const *>(0x1674524), reinterpret_cast<s_hs_script_op const *>(0x167468C), reinterpret_cast<s_hs_script_op const *>(0x1674788),
	reinterpret_cast<s_hs_script_op const *>(0x16747EC), reinterpret_cast<s_hs_script_op const *>(0x1674974), reinterpret_cast<s_hs_script_op const *>(0x1674A54), reinterpret_cast<s_hs_script_op const *>(0x1674B64),
	reinterpret_cast<s_hs_script_op const *>(0x1674C8C), reinterpret_cast<s_hs_script_op const *>(0x1674DB4), reinterpret_cast<s_hs_script_op const *>(0x1674F00), reinterpret_cast<s_hs_script_op const *>(0x167503C),
	reinterpret_cast<s_hs_script_op const *>(0x1675170), reinterpret_cast<s_hs_script_op const *>(0x1675298), reinterpret_cast<s_hs_script_op const *>(0x16753C4), reinterpret_cast<s_hs_script_op const *>(0x16754F0),
	reinterpret_cast<s_hs_script_op const *>(0x1675618), reinterpret_cast<s_hs_script_op const *>(0x167571C), reinterpret_cast<s_hs_script_op const *>(0x1675848), reinterpret_cast<s_hs_script_op const *>(0x1675964),
	reinterpret_cast<s_hs_script_op const *>(0x1675A9C), reinterpret_cast<s_hs_script_op const *>(0x1675BD0), reinterpret_cast<s_hs_script_op const *>(0x1675CCC), reinterpret_cast<s_hs_script_op const *>(0x1675DE4),
	reinterpret_cast<s_hs_script_op const *>(0x1675F54), reinterpret_cast<s_hs_script_op const *>(0x1676054), reinterpret_cast<s_hs_script_op const *>(0x16761D8), reinterpret_cast<s_hs_script_op const *>(0x167631C),
	reinterpret_cast<s_hs_script_op const *>(0x167647C), reinterpret_cast<s_hs_script_op const *>(0x16765AC), reinterpret_cast<s_hs_script_op const *>(0x16766DC), reinterpret_cast<s_hs_script_op const *>(0x167682C),
	reinterpret_cast<s_hs_script_op const *>(0x1676974), reinterpret_cast<s_hs_script_op const *>(0x1676AA4), reinterpret_cast<s_hs_script_op const *>(0x1676C6C), reinterpret_cast<s_hs_script_op const *>(0x1676DF4),
	reinterpret_cast<s_hs_script_op const *>(0x1676F3C), reinterpret_cast<s_hs_script_op const *>(0x1677054), reinterpret_cast<s_hs_script_op const *>(0x16771A4), reinterpret_cast<s_hs_script_op const *>(0x167731C),
	reinterpret_cast<s_hs_script_op const *>(0x167741C), reinterpret_cast<s_hs_script_op const *>(0x1677510), reinterpret_cast<s_hs_script_op const *>(0x16775F0), reinterpret_cast<s_hs_script_op const *>(0x1677754),
	reinterpret_cast<s_hs_script_op const *>(0x16778E8), reinterpret_cast<s_hs_script_op const *>(0x1677A28), reinterpret_cast<s_hs_script_op const *>(0x1677B98), reinterpret_cast<s_hs_script_op const *>(0x1677D1C),
	reinterpret_cast<s_hs_script_op const *>(0x1677EAC), reinterpret_cast<s_hs_script_op const *>(0x1678014), reinterpret_cast<s_hs_script_op const *>(0x1678194), reinterpret_cast<s_hs_script_op const *>(0x1678328),
	reinterpret_cast<s_hs_script_op const *>(0x16784B8), reinterpret_cast<s_hs_script_op const *>(0x1678620), reinterpret_cast<s_hs_script_op const *>(0x167876C), reinterpret_cast<s_hs_script_op const *>(0x1678940),
	reinterpret_cast<s_hs_script_op const *>(0x1678B00), reinterpret_cast<s_hs_script_op const *>(0x1678C70), reinterpret_cast<s_hs_script_op const *>(0x1678E18), reinterpret_cast<s_hs_script_op const *>(0x1678FF4),
	reinterpret_cast<s_hs_script_op const *>(0x167915C), reinterpret_cast<s_hs_script_op const *>(0x16792A4), reinterpret_cast<s_hs_script_op const *>(0x1679440), reinterpret_cast<s_hs_script_op const *>(0x16795A0),
	reinterpret_cast<s_hs_script_op const *>(0x167974C), reinterpret_cast<s_hs_script_op const *>(0x1679914), reinterpret_cast<s_hs_script_op const *>(0x1679B04), reinterpret_cast<s_hs_script_op const *>(0x1679C80),
	reinterpret_cast<s_hs_script_op const *>(0x1679E20), reinterpret_cast<s_hs_script_op const *>(0x1679FC4), reinterpret_cast<s_hs_script_op const *>(0x167A168), reinterpret_cast<s_hs_script_op const *>(0x167A330),
	reinterpret_cast<s_hs_script_op const *>(0x167A4BC), reinterpret_cast<s_hs_script_op const *>(0x167A620), reinterpret_cast<s_hs_script_op const *>(0x167A824), reinterpret_cast<s_hs_script_op const *>(0x167A964),
	reinterpret_cast<s_hs_script_op const *>(0x167AB70), reinterpret_cast<s_hs_script_op const *>(0x167AC8C), reinterpret_cast<s_hs_script_op const *>(0x167AD8C), reinterpret_cast<s_hs_script_op const *>(0x167AF38),
	reinterpret_cast<s_hs_script_op const *>(0x1672A5C), reinterpret_cast<s_hs_script_op const *>(0x1672BFC), reinterpret_cast<s_hs_script_op const *>(0x1672D6C), reinterpret_cast<s_hs_script_op const *>(0x1672F28),
	reinterpret_cast<s_hs_script_op const *>(0x16730A0), reinterpret_cast<s_hs_script_op const *>(0x167323C), reinterpret_cast<s_hs_script_op const *>(0x16733E8), reinterpret_cast<s_hs_script_op const *>(0x1673548),
	reinterpret_cast<s_hs_script_op const *>(0x16736A4), reinterpret_cast<s_hs_script_op const *>(0x1673830), reinterpret_cast<s_hs_script_op const *>(0x1673958), reinterpret_cast<s_hs_script_op const *>(0x1673AB0),
	reinterpret_cast<s_hs_script_op const *>(0x1673BF4), reinterpret_cast<s_hs_script_op const *>(0x1673D2C), reinterpret_cast<s_hs_script_op const *>(0x1673E68), reinterpret_cast<s_hs_script_op const *>(0x1673FCC),
	reinterpret_cast<s_hs_script_op const *>(0x16741B0), reinterpret_cast<s_hs_script_op const *>(0x16742E8), reinterpret_cast<s_hs_script_op const *>(0x167441C), reinterpret_cast<s_hs_script_op const *>(0x167458C),
	reinterpret_cast<s_hs_script_op const *>(0x16746B4), reinterpret_cast<s_hs_script_op const *>(0x16747C4), reinterpret_cast<s_hs_script_op const *>(0x16748E8), reinterpret_cast<s_hs_script_op const *>(0x1674A40),
	reinterpret_cast<s_hs_script_op const *>(0x1674BCC), reinterpret_cast<s_hs_script_op const *>(0x1674D0C), reinterpret_cast<s_hs_script_op const *>(0x1674E9C), reinterpret_cast<s_hs_script_op const *>(0x1674FF0),
	reinterpret_cast<s_hs_script_op const *>(0x1675144), reinterpret_cast<s_hs_script_op const *>(0x1675248), reinterpret_cast<s_hs_script_op const *>(0x16752E8), reinterpret_cast<s_hs_script_op const *>(0x16753D8),
	reinterpret_cast<s_hs_script_op const *>(0x1675504), reinterpret_cast<s_hs_script_op const *>(0x167568C), reinterpret_cast<s_hs_script_op const *>(0x16757BC), reinterpret_cast<s_hs_script_op const *>(0x1675940),
	reinterpret_cast<s_hs_script_op const *>(0x1675AE8), reinterpret_cast<s_hs_script_op const *>(0x1675C54), reinterpret_cast<s_hs_script_op const *>(0x1675DCC), reinterpret_cast<s_hs_script_op const *>(0x1675F10),
	reinterpret_cast<s_hs_script_op const *>(0x1676008), reinterpret_cast<s_hs_script_op const *>(0x1676154), reinterpret_cast<s_hs_script_op const *>(0x16762CC), reinterpret_cast<s_hs_script_op const *>(0x16763D0),
	reinterpret_cast<s_hs_script_op const *>(0x16764E0), reinterpret_cast<s_hs_script_op const *>(0x16765EC), reinterpret_cast<s_hs_script_op const *>(0x1676754), reinterpret_cast<s_hs_script_op const *>(0x1676840),
	reinterpret_cast<s_hs_script_op const *>(0x1676934), reinterpret_cast<s_hs_script_op const *>(0x1676A18), reinterpret_cast<s_hs_script_op const *>(0x1676B78), reinterpret_cast<s_hs_script_op const *>(0x1676CAC),
	reinterpret_cast<s_hs_script_op const *>(0x1676E18), reinterpret_cast<s_hs_script_op const *>(0x1676F50), reinterpret_cast<s_hs_script_op const *>(0x16770A8), reinterpret_cast<s_hs_script_op const *>(0x1677214),
	reinterpret_cast<s_hs_script_op const *>(0x1677444), reinterpret_cast<s_hs_script_op const *>(0x1677628), reinterpret_cast<s_hs_script_op const *>(0x16778B0), reinterpret_cast<s_hs_script_op const *>(0x1677AD0),
	reinterpret_cast<s_hs_script_op const *>(0x1677D6C), reinterpret_cast<s_hs_script_op const *>(0x1677FF0), reinterpret_cast<s_hs_script_op const *>(0x167816C), reinterpret_cast<s_hs_script_op const *>(0x16782EC),
	reinterpret_cast<s_hs_script_op const *>(0x1678408), reinterpret_cast<s_hs_script_op const *>(0x1678584), reinterpret_cast<s_hs_script_op const *>(0x1678664), reinterpret_cast<s_hs_script_op const *>(0x16787A8),
	reinterpret_cast<s_hs_script_op const *>(0x1678900), reinterpret_cast<s_hs_script_op const *>(0x1678A4C), reinterpret_cast<s_hs_script_op const *>(0x1678BA8), reinterpret_cast<s_hs_script_op const *>(0x1679070),
	reinterpret_cast<s_hs_script_op const *>(0x1679084), reinterpret_cast<s_hs_script_op const *>(0x1679504), reinterpret_cast<s_hs_script_op const *>(0x167957C), reinterpret_cast<s_hs_script_op const *>(0x16799E4),
	reinterpret_cast<s_hs_script_op const *>(0x1679A18), reinterpret_cast<s_hs_script_op const *>(0x1679EBC), reinterpret_cast<s_hs_script_op const *>(0x1679EF4), reinterpret_cast<s_hs_script_op const *>(0x167A014),
	reinterpret_cast<s_hs_script_op const *>(0x167A154), reinterpret_cast<s_hs_script_op const *>(0x167A258), reinterpret_cast<s_hs_script_op const *>(0x167A41C), reinterpret_cast<s_hs_script_op const *>(0x167A5B8),
	reinterpret_cast<s_hs_script_op const *>(0x167A728), reinterpret_cast<s_hs_script_op const *>(0x167AD68), reinterpret_cast<s_hs_script_op const *>(0x167AD9C), reinterpret_cast<s_hs_script_op const *>(0x167AF78),
	reinterpret_cast<s_hs_script_op const *>(0x1672AA8), reinterpret_cast<s_hs_script_op const *>(0x1672C4C), reinterpret_cast<s_hs_script_op const *>(0x1672DD0), reinterpret_cast<s_hs_script_op const *>(0x16733C0),
	reinterpret_cast<s_hs_script_op const *>(0x1673400), reinterpret_cast<s_hs_script_op const *>(0x1673944), reinterpret_cast<s_hs_script_op const *>(0x167396C), reinterpret_cast<s_hs_script_op const *>(0x1673EE0),
	reinterpret_cast<s_hs_script_op const *>(0x1673EF4), reinterpret_cast<s_hs_script_op const *>(0x16745A0), reinterpret_cast<s_hs_script_op const *>(0x16745B8), reinterpret_cast<s_hs_script_op const *>(0x1674B24),
	reinterpret_cast<s_hs_script_op const *>(0x1674B4C), reinterpret_cast<s_hs_script_op const *>(0x16750C8), reinterpret_cast<s_hs_script_op const *>(0x16750DC), reinterpret_cast<s_hs_script_op const *>(0x16755F4),
	reinterpret_cast<s_hs_script_op const *>(0x167562C), reinterpret_cast<s_hs_script_op const *>(0x1675B58), reinterpret_cast<s_hs_script_op const *>(0x1675B6C), reinterpret_cast<s_hs_script_op const *>(0x16760C4),
	reinterpret_cast<s_hs_script_op const *>(0x16760D8), reinterpret_cast<s_hs_script_op const *>(0x16766B0), reinterpret_cast<s_hs_script_op const *>(0x16766F0), reinterpret_cast<s_hs_script_op const *>(0x1676C98),
	reinterpret_cast<s_hs_script_op const *>(0x1676CC0), reinterpret_cast<s_hs_script_op const *>(0x1677260), reinterpret_cast<s_hs_script_op const *>(0x16772A4), reinterpret_cast<s_hs_script_op const *>(0x16777DC),
	reinterpret_cast<s_hs_script_op const *>(0x16777F0), reinterpret_cast<s_hs_script_op const *>(0x1677E78), reinterpret_cast<s_hs_script_op const *>(0x1677E90), reinterpret_cast<s_hs_script_op const *>(0x167848C),
	reinterpret_cast<s_hs_script_op const *>(0x16784A0), reinterpret_cast<s_hs_script_op const *>(0x1678AC4), reinterpret_cast<s_hs_script_op const *>(0x1678B14), reinterpret_cast<s_hs_script_op const *>(0x16790F4),
	reinterpret_cast<s_hs_script_op const *>(0x1679108), reinterpret_cast<s_hs_script_op const *>(0x16796E8), reinterpret_cast<s_hs_script_op const *>(0x16796FC), reinterpret_cast<s_hs_script_op const *>(0x1679CD4),
	reinterpret_cast<s_hs_script_op const *>(0x1679D48), reinterpret_cast<s_hs_script_op const *>(0x167A2F4), reinterpret_cast<s_hs_script_op const *>(0x167A354), reinterpret_cast<s_hs_script_op const *>(0x167AA1C),
	reinterpret_cast<s_hs_script_op const *>(0x167AA30), reinterpret_cast<s_hs_script_op const *>(0x1672B10), reinterpret_cast<s_hs_script_op const *>(0x1672B38), reinterpret_cast<s_hs_script_op const *>(0x1673130),
	reinterpret_cast<s_hs_script_op const *>(0x1673168), reinterpret_cast<s_hs_script_op const *>(0x1673744), reinterpret_cast<s_hs_script_op const *>(0x1673758), reinterpret_cast<s_hs_script_op const *>(0x1673CA0),
	reinterpret_cast<s_hs_script_op const *>(0x1673CC4), reinterpret_cast<s_hs_script_op const *>(0x1674294), reinterpret_cast<s_hs_script_op const *>(0x16742BC), reinterpret_cast<s_hs_script_op const *>(0x1674824),
	reinterpret_cast<s_hs_script_op const *>(0x1674874), reinterpret_cast<s_hs_script_op const *>(0x1674E00), reinterpret_cast<s_hs_script_op const *>(0x1674E40), reinterpret_cast<s_hs_script_op const *>(0x16753B0),
	reinterpret_cast<s_hs_script_op const *>(0x16753E8), reinterpret_cast<s_hs_script_op const *>(0x1675904), reinterpret_cast<s_hs_script_op const *>(0x1675928), reinterpret_cast<s_hs_script_op const *>(0x1675E38),
	reinterpret_cast<s_hs_script_op const *>(0x1675E78), reinterpret_cast<s_hs_script_op const *>(0x1676434), reinterpret_cast<s_hs_script_op const *>(0x167644C), reinterpret_cast<s_hs_script_op const *>(0x1676A7C),
	reinterpret_cast<s_hs_script_op const *>(0x1676AE0), reinterpret_cast<s_hs_script_op const *>(0x16770D0), reinterpret_cast<s_hs_script_op const *>(0x16770E8), reinterpret_cast<s_hs_script_op const *>(0x16776CC),
	reinterpret_cast<s_hs_script_op const *>(0x16776E8), reinterpret_cast<s_hs_script_op const *>(0x1677C64), reinterpret_cast<s_hs_script_op const *>(0x1677CC0), reinterpret_cast<s_hs_script_op const *>(0x1678234),
	reinterpret_cast<s_hs_script_op const *>(0x167824C), reinterpret_cast<s_hs_script_op const *>(0x167882C), reinterpret_cast<s_hs_script_op const *>(0x1678884), reinterpret_cast<s_hs_script_op const *>(0x1678E54),
	reinterpret_cast<s_hs_script_op const *>(0x1678EA0), reinterpret_cast<s_hs_script_op const *>(0x1679414), reinterpret_cast<s_hs_script_op const *>(0x1679428), reinterpret_cast<s_hs_script_op const *>(0x1679A90),
	reinterpret_cast<s_hs_script_op const *>(0x1679ABC), reinterpret_cast<s_hs_script_op const *>(0x167A0D0), reinterpret_cast<s_hs_script_op const *>(0x167A0FC), reinterpret_cast<s_hs_script_op const *>(0x167A73C),
	reinterpret_cast<s_hs_script_op const *>(0x167A750), reinterpret_cast<s_hs_script_op const *>(0x167AF14), reinterpret_cast<s_hs_script_op const *>(0x167AF4C), reinterpret_cast<s_hs_script_op const *>(0x1672E40),
	reinterpret_cast<s_hs_script_op const *>(0x1672E68), reinterpret_cast<s_hs_script_op const *>(0x1673314), reinterpret_cast<s_hs_script_op const *>(0x1673350), reinterpret_cast<s_hs_script_op const *>(0x16737CC),
	reinterpret_cast<s_hs_script_op const *>(0x167381C), reinterpret_cast<s_hs_script_op const *>(0x1673C2C), reinterpret_cast<s_hs_script_op const *>(0x1673C64), reinterpret_cast<s_hs_script_op const *>(0x1674174),
	reinterpret_cast<s_hs_script_op const *>(0x16741C8), reinterpret_cast<s_hs_script_op const *>(0x167460C), reinterpret_cast<s_hs_script_op const *>(0x1674620), reinterpret_cast<s_hs_script_op const *>(0x1674A7C),
	reinterpret_cast<s_hs_script_op const *>(0x1674ABC), reinterpret_cast<s_hs_script_op const *>(0x1674F7C), reinterpret_cast<s_hs_script_op const *>(0x1674F90), reinterpret_cast<s_hs_script_op const *>(0x1675414),
	reinterpret_cast<s_hs_script_op const *>(0x1675438), reinterpret_cast<s_hs_script_op const *>(0x1675834), reinterpret_cast<s_hs_script_op const *>(0x167585C), reinterpret_cast<s_hs_script_op const *>(0x1675CB8),
	reinterpret_cast<s_hs_script_op const *>(0x1675CE0), reinterpret_cast<s_hs_script_op const *>(0x1676140), reinterpret_cast<s_hs_script_op const *>(0x167617C), reinterpret_cast<s_hs_script_op const *>(0x1676610),
	reinterpret_cast<s_hs_script_op const *>(0x1676650), reinterpret_cast<s_hs_script_op const *>(0x1676B38), reinterpret_cast<s_hs_script_op const *>(0x1676B4C), reinterpret_cast<s_hs_script_op const *>(0x1676FEC),
	reinterpret_cast<s_hs_script_op const *>(0x167703C), reinterpret_cast<s_hs_script_op const *>(0x16774D0), reinterpret_cast<s_hs_script_op const *>(0x16774FC), reinterpret_cast<s_hs_script_op const *>(0x16779D4),
	reinterpret_cast<s_hs_script_op const *>(0x16779FC), reinterpret_cast<s_hs_script_op const *>(0x1677ED4), reinterpret_cast<s_hs_script_op const *>(0x1677EF8), reinterpret_cast<s_hs_script_op const *>(0x16783F4),
	reinterpret_cast<s_hs_script_op const *>(0x167841C), reinterpret_cast<s_hs_script_op const *>(0x167897C), reinterpret_cast<s_hs_script_op const *>(0x16789E4), reinterpret_cast<s_hs_script_op const *>(0x1678E68),
	reinterpret_cast<s_hs_script_op const *>(0x1678EB8), reinterpret_cast<s_hs_script_op const *>(0x167934C), reinterpret_cast<s_hs_script_op const *>(0x1679388), reinterpret_cast<s_hs_script_op const *>(0x1679800),
	reinterpret_cast<s_hs_script_op const *>(0x1679814), reinterpret_cast<s_hs_script_op const *>(0x1679D10), reinterpret_cast<s_hs_script_op const *>(0x1679D24), reinterpret_cast<s_hs_script_op const *>(0x167A220),
	reinterpret_cast<s_hs_script_op const *>(0x167A234), reinterpret_cast<s_hs_script_op const *>(0x167A78C), reinterpret_cast<s_hs_script_op const *>(0x167A7E8), reinterpret_cast<s_hs_script_op const *>(0x167ADFC),
	reinterpret_cast<s_hs_script_op const *>(0x167AE68), reinterpret_cast<s_hs_script_op const *>(0x1672D44), reinterpret_cast<s_hs_script_op const *>(0x1672D58), reinterpret_cast<s_hs_script_op const *>(0x1673250),
	reinterpret_cast<s_hs_script_op const *>(0x1673278), reinterpret_cast<s_hs_script_op const *>(0x1673648), reinterpret_cast<s_hs_script_op const *>(0x1673690), reinterpret_cast<s_hs_script_op const *>(0x1673AD8),
	reinterpret_cast<s_hs_script_op const *>(0x1673B28), reinterpret_cast<s_hs_script_op const *>(0x1673F68), reinterpret_cast<s_hs_script_op const *>(0x1673FB8), reinterpret_cast<s_hs_script_op const *>(0x16744E8),
	reinterpret_cast<s_hs_script_op const *>(0x16744FC), reinterpret_cast<s_hs_script_op const *>(0x1674988), reinterpret_cast<s_hs_script_op const *>(0x167499C), reinterpret_cast<s_hs_script_op const *>(0x1674E2C),
	reinterpret_cast<s_hs_script_op const *>(0x1674E84), reinterpret_cast<s_hs_script_op const *>(0x1675238), reinterpret_cast<s_hs_script_op const *>(0x1675270), reinterpret_cast<s_hs_script_op const *>(0x1675644),
	reinterpret_cast<s_hs_script_op const *>(0x1675654), reinterpret_cast<s_hs_script_op const *>(0x1675A04), reinterpret_cast<s_hs_script_op const *>(0x1675A38), reinterpret_cast<s_hs_script_op const *>(0x1675EA4),
	reinterpret_cast<s_hs_script_op const *>(0x1675EE0), reinterpret_cast<s_hs_script_op const *>(0x16762A8), reinterpret_cast<s_hs_script_op const *>(0x16762E0), reinterpret_cast<s_hs_script_op const *>(0x167679C),
	reinterpret_cast<s_hs_script_op const *>(0x16767E8), reinterpret_cast<s_hs_script_op const *>(0x1676D24), reinterpret_cast<s_hs_script_op const *>(0x1676D74), reinterpret_cast<s_hs_script_op const *>(0x16772BC),
	reinterpret_cast<s_hs_script_op const *>(0x16772E0), reinterpret_cast<s_hs_script_op const *>(0x1677808), reinterpret_cast<s_hs_script_op const *>(0x1677858), reinterpret_cast<s_hs_script_op const *>(0x167795C),
	reinterpret_cast<s_hs_script_op const *>(&hades_file_local::hs_camera_set_op), reinterpret_cast<s_hs_script_op const *>(0x1677C48), reinterpret_cast<s_hs_script_op const *>(0x1677DA4), reinterpret_cast<s_hs_script_op const *>(0x1677F60),
	reinterpret_cast<s_hs_script_op const *>(0x16780D8), reinterpret_cast<s_hs_script_op const *>(0x1678298), reinterpret_cast<s_hs_script_op const *>(0x1678470), reinterpret_cast<s_hs_script_op const *>(0x1678690),
	reinterpret_cast<s_hs_script_op const *>(0x1678854), reinterpret_cast<s_hs_script_op const *>(0x16789B8), reinterpret_cast<s_hs_script_op const *>(0x1678AEC), reinterpret_cast<s_hs_script_op const *>(0x1678BE0),
	reinterpret_cast<s_hs_script_op const *>(0x1678D1C), reinterpret_cast<s_hs_script_op const *>(0x1678DC8), reinterpret_cast<s_hs_script_op const *>(0x1678F08), reinterpret_cast<s_hs_script_op const *>(0x1678FE4),
	reinterpret_cast<s_hs_script_op const *>(0x1679134), reinterpret_cast<s_hs_script_op const *>(0x16792E0), reinterpret_cast<s_hs_script_op const *>(0x16793E8), reinterpret_cast<s_hs_script_op const *>(0x1679554),
	reinterpret_cast<s_hs_script_op const *>(0x167967C), reinterpret_cast<s_hs_script_op const *>(0x1679898), reinterpret_cast<s_hs_script_op const *>(0x1679968), reinterpret_cast<s_hs_script_op const *>(0x16799F8),
	reinterpret_cast<s_hs_script_op const *>(0x1679AF0), reinterpret_cast<s_hs_script_op const *>(0x1679BC8), reinterpret_cast<s_hs_script_op const *>(0x1679C6C), reinterpret_cast<s_hs_script_op const *>(0x1679DAC),
	reinterpret_cast<s_hs_script_op const *>(0x1679E7C), reinterpret_cast<s_hs_script_op const *>(0x1679F7C), reinterpret_cast<s_hs_script_op const *>(0x167A064), reinterpret_cast<s_hs_script_op const *>(0x167A1E0),
	reinterpret_cast<s_hs_script_op const *>(0x167A308), reinterpret_cast<s_hs_script_op const *>(0x167A3E8), reinterpret_cast<s_hs_script_op const *>(0x167A4AC), reinterpret_cast<s_hs_script_op const *>(0x167A594),
	reinterpret_cast<s_hs_script_op const *>(0x167A6C8), reinterpret_cast<s_hs_script_op const *>(0x167A880), reinterpret_cast<s_hs_script_op const *>(0x167A9E4), reinterpret_cast<s_hs_script_op const *>(0x167AB84),
	reinterpret_cast<s_hs_script_op const *>(0x167ACFC), reinterpret_cast<s_hs_script_op const *>(0x167AE90), reinterpret_cast<s_hs_script_op const *>(0x167AFB4), reinterpret_cast<s_hs_script_op const *>(0x1672AD4),
	reinterpret_cast<s_hs_script_op const *>(0x1672BC4), reinterpret_cast<s_hs_script_op const *>(0x1672CF8), reinterpret_cast<s_hs_script_op const *>(0x1672E08), reinterpret_cast<s_hs_script_op const *>(0x1672F50),
	reinterpret_cast<s_hs_script_op const *>(0x1673018), reinterpret_cast<s_hs_script_op const *>(0x1673158), reinterpret_cast<s_hs_script_op const *>(0x167328C), reinterpret_cast<s_hs_script_op const *>(0x1673378),
	reinterpret_cast<s_hs_script_op const *>(0x1673454), reinterpret_cast<s_hs_script_op const *>(0x167355C), reinterpret_cast<s_hs_script_op const *>(0x1673680), reinterpret_cast<s_hs_script_op const *>(0x1673794),
	reinterpret_cast<s_hs_script_op const *>(0x167386C), reinterpret_cast<s_hs_script_op const *>(0x1673934), reinterpret_cast<s_hs_script_op const *>(0x1673A40), reinterpret_cast<s_hs_script_op const *>(0x1673B60),
	reinterpret_cast<s_hs_script_op const *>(0x1673C54), reinterpret_cast<s_hs_script_op const *>(0x1673D60), reinterpret_cast<s_hs_script_op const *>(0x1673E44), reinterpret_cast<s_hs_script_op const *>(0x1673F34),
	reinterpret_cast<s_hs_script_op const *>(0x1674044), reinterpret_cast<s_hs_script_op const *>(0x167422C), reinterpret_cast<s_hs_script_op const *>(0x167430C), reinterpret_cast<s_hs_script_op const *>(0x16743CC),
	reinterpret_cast<s_hs_script_op const *>(0x16744C0), reinterpret_cast<s_hs_script_op const *>(0x16745D4), reinterpret_cast<s_hs_script_op const *>(0x1674738), reinterpret_cast<s_hs_script_op const *>(0x1674810),
	reinterpret_cast<s_hs_script_op const *>(0x16749B0), reinterpret_cast<s_hs_script_op const *>(0x1674B38), reinterpret_cast<s_hs_script_op const *>(0x1674C78), reinterpret_cast<s_hs_script_op const *>(0x1674DD8),
	reinterpret_cast<s_hs_script_op const *>(0x1674F2C), reinterpret_cast<s_hs_script_op const *>(0x167507C), reinterpret_cast<s_hs_script_op const *>(0x16751C0), reinterpret_cast<s_hs_script_op const *>(0x1675310),
	reinterpret_cast<s_hs_script_op const *>(0x167547C), reinterpret_cast<s_hs_script_op const *>(0x16755A0), reinterpret_cast<s_hs_script_op const *>(0x1675708), reinterpret_cast<s_hs_script_op const *>(0x1675808),
	reinterpret_cast<s_hs_script_op const *>(0x167599C), reinterpret_cast<s_hs_script_op const *>(0x1675AD4), reinterpret_cast<s_hs_script_op const *>(0x1675C1C), reinterpret_cast<s_hs_script_op const *>(0x1675D70),
	reinterpret_cast<s_hs_script_op const *>(0x1675EB8), reinterpret_cast<s_hs_script_op const *>(0x1675FF4), reinterpret_cast<s_hs_script_op const *>(0x167611C), reinterpret_cast<s_hs_script_op const *>(0x16762B8),
	reinterpret_cast<s_hs_script_op const *>(0x1676420), reinterpret_cast<s_hs_script_op const *>(0x1676544), reinterpret_cast<s_hs_script_op const *>(0x16766C8), reinterpret_cast<s_hs_script_op const *>(0x167681C),
	reinterpret_cast<s_hs_script_op const *>(0x1676900), reinterpret_cast<s_hs_script_op const *>(0x1676A40), reinterpret_cast<s_hs_script_op const *>(0x1676BA0), reinterpret_cast<s_hs_script_op const *>(0x1676CD8),
	reinterpret_cast<s_hs_script_op const *>(0x1676E44), reinterpret_cast<s_hs_script_op const *>(0x1676F2C), reinterpret_cast<s_hs_script_op const *>(0x1677000), reinterpret_cast<s_hs_script_op const *>(0x1677118),
	reinterpret_cast<s_hs_script_op const *>(0x16771B8), reinterpret_cast<s_hs_script_op const *>(0x1677240), reinterpret_cast<s_hs_script_op const *>(0x1677398), reinterpret_cast<s_hs_script_op const *>(0x16774AC),
	reinterpret_cast<s_hs_script_op const *>(0x167757C), reinterpret_cast<s_hs_script_op const *>(0x1677690), reinterpret_cast<s_hs_script_op const *>(0x1677768), reinterpret_cast<s_hs_script_op const *>(0x167781C),
	reinterpret_cast<s_hs_script_op const *>(0x1677910), reinterpret_cast<s_hs_script_op const *>(0x16779C4), reinterpret_cast<s_hs_script_op const *>(0x1677A8C), reinterpret_cast<s_hs_script_op const *>(0x1677B7C),
	reinterpret_cast<s_hs_script_op const *>(0x1677C34), reinterpret_cast<s_hs_script_op const *>(0x1677D0C), reinterpret_cast<s_hs_script_op const *>(0x1677DE4), reinterpret_cast<s_hs_script_op const *>(0x1677EC0),
	reinterpret_cast<s_hs_script_op const *>(0x1677F8C), reinterpret_cast<s_hs_script_op const *>(0x167806C), reinterpret_cast<s_hs_script_op const *>(0x1678130), reinterpret_cast<s_hs_script_op const *>(0x16781E4),
	reinterpret_cast<s_hs_script_op const *>(0x16782DC), reinterpret_cast<s_hs_script_op const *>(0x1678368), reinterpret_cast<s_hs_script_op const *>(0x16784F8), reinterpret_cast<s_hs_script_op const *>(0x1678648),
	reinterpret_cast<s_hs_script_op const *>(0x167875C), reinterpret_cast<s_hs_script_op const *>(0x1678808), reinterpret_cast<s_hs_script_op const *>(0x16788EC), reinterpret_cast<s_hs_script_op const *>(0x1678A10),
	reinterpret_cast<s_hs_script_op const *>(0x1678AB0), reinterpret_cast<s_hs_script_op const *>(0x1678BBC), reinterpret_cast<s_hs_script_op const *>(0x1678C5C), reinterpret_cast<s_hs_script_op const *>(0x1678D08),
	reinterpret_cast<s_hs_script_op const *>(0x1678DDC), reinterpret_cast<s_hs_script_op const *>(0x1678EE0), reinterpret_cast<s_hs_script_op const *>(0x1678F94), reinterpret_cast<s_hs_script_op const *>(0x167905C),
	reinterpret_cast<s_hs_script_op const *>(0x1679120), reinterpret_cast<s_hs_script_op const *>(0x16791E0), reinterpret_cast<s_hs_script_op const *>(0x1679290), reinterpret_cast<s_hs_script_op const *>(0x16793FC),
	reinterpret_cast<s_hs_script_op const *>(0x16794DC), reinterpret_cast<s_hs_script_op const *>(0x1679590), reinterpret_cast<s_hs_script_op const *>(0x167966C), reinterpret_cast<s_hs_script_op const *>(0x167973C),
	reinterpret_cast<s_hs_script_op const *>(0x16797DC), reinterpret_cast<s_hs_script_op const *>(0x16798CC), reinterpret_cast<s_hs_script_op const *>(0x167999C), reinterpret_cast<s_hs_script_op const *>(0x1679A54),
	reinterpret_cast<s_hs_script_op const *>(0x1679B44), reinterpret_cast<s_hs_script_op const *>(0x1679BDC), reinterpret_cast<s_hs_script_op const *>(0x1679CC4), reinterpret_cast<s_hs_script_op const *>(0x1679D9C),
	reinterpret_cast<s_hs_script_op const *>(0x1679E48), reinterpret_cast<s_hs_script_op const *>(0x1679F08), reinterpret_cast<s_hs_script_op const *>(0x1679FD8), reinterpret_cast<s_hs_script_op const *>(0x167A0A8),
	reinterpret_cast<s_hs_script_op const *>(0x167A18C), reinterpret_cast<s_hs_script_op const *>(0x167A2B4), reinterpret_cast<s_hs_script_op const *>(0x167A380), reinterpret_cast<s_hs_script_op const *>(0x167A444),
	reinterpret_cast<s_hs_script_op const *>(0x167A530), reinterpret_cast<s_hs_script_op const *>(0x167A5F4), reinterpret_cast<s_hs_script_op const *>(0x167A68C), reinterpret_cast<s_hs_script_op const *>(0x167A7A0),
	reinterpret_cast<s_hs_script_op const *>(0x167A8B8), reinterpret_cast<s_hs_script_op const *>(0x167AAA4), reinterpret_cast<s_hs_script_op const *>(0x167ACC4), reinterpret_cast<s_hs_script_op const *>(0x167ADDC),
	reinterpret_cast<s_hs_script_op const *>(0x167AEE0), reinterpret_cast<s_hs_script_op const *>(0x167AFF4), reinterpret_cast<s_hs_script_op const *>(0x1672A34), reinterpret_cast<s_hs_script_op const *>(0x1672BB0),
	reinterpret_cast<s_hs_script_op const *>(0x1672CB8), reinterpret_cast<s_hs_script_op const *>(0x1672E2C), reinterpret_cast<s_hs_script_op const *>(0x1672FA4), reinterpret_cast<s_hs_script_op const *>(0x16730C4),
	reinterpret_cast<s_hs_script_op const *>(0x1673214), reinterpret_cast<s_hs_script_op const *>(0x1673364), reinterpret_cast<s_hs_script_op const *>(0x167348C), reinterpret_cast<s_hs_script_op const *>(0x1673538),
	reinterpret_cast<s_hs_script_op const *>(0x1673634), reinterpret_cast<s_hs_script_op const *>(0x1673770), reinterpret_cast<s_hs_script_op const *>(0x167387C), reinterpret_cast<s_hs_script_op const *>(0x1673984),
	reinterpret_cast<s_hs_script_op const *>(0x1673AC4), reinterpret_cast<s_hs_script_op const *>(0x1673BD0), reinterpret_cast<s_hs_script_op const *>(0x1673CB4), reinterpret_cast<s_hs_script_op const *>(0x1673DD4),
	reinterpret_cast<s_hs_script_op const *>(0x1673E80), reinterpret_cast<s_hs_script_op const *>(0x1673FE0), reinterpret_cast<s_hs_script_op const *>(0x1674068), reinterpret_cast<s_hs_script_op const *>(0x16741F0),
	reinterpret_cast<s_hs_script_op const *>(0x1674344), reinterpret_cast<s_hs_script_op const *>(0x1674430), reinterpret_cast<s_hs_script_op const *>(0x1674514), reinterpret_cast<s_hs_script_op const *>(0x16746C8),
	reinterpret_cast<s_hs_script_op const *>(0x167488C), reinterpret_cast<s_hs_script_op const *>(0x1674A18), reinterpret_cast<s_hs_script_op const *>(0x1674AD0), reinterpret_cast<s_hs_script_op const *>(0x1674BF8),
	reinterpret_cast<s_hs_script_op const *>(0x1674D20), reinterpret_cast<s_hs_script_op const *>(0x1674EEC), reinterpret_cast<s_hs_script_op const *>(0x1675064), reinterpret_cast<s_hs_script_op const *>(0x167520C),
	reinterpret_cast<s_hs_script_op const *>(0x1675374), reinterpret_cast<s_hs_script_op const *>(0x1675574), reinterpret_cast<s_hs_script_op const *>(0x16756F0), reinterpret_cast<s_hs_script_op const *>(0x1675894),
	reinterpret_cast<s_hs_script_op const *>(0x16759D8), reinterpret_cast<s_hs_script_op const *>(0x1675B2C), reinterpret_cast<s_hs_script_op const *>(0x1675C90), reinterpret_cast<s_hs_script_op const *>(0x1675DB4),
	reinterpret_cast<s_hs_script_op const *>(0x1675F24), reinterpret_cast<s_hs_script_op const *>(0x16760A8), reinterpret_cast<s_hs_script_op const *>(0x167621C), reinterpret_cast<s_hs_script_op const *>(0x16763A0),
	reinterpret_cast<s_hs_script_op const *>(0x167652C), reinterpret_cast<s_hs_script_op const *>(0x1676738), reinterpret_cast<s_hs_script_op const *>(0x16768D0), reinterpret_cast<s_hs_script_op const *>(0x1676A28),
	reinterpret_cast<s_hs_script_op const *>(0x1676BF0), reinterpret_cast<s_hs_script_op const *>(0x1676DA0), reinterpret_cast<s_hs_script_op const *>(0x1676E58), reinterpret_cast<s_hs_script_op const *>(0x1676EF4),
	reinterpret_cast<s_hs_script_op const *>(0x1676FB0), reinterpret_cast<s_hs_script_op const *>(0x16770C0), reinterpret_cast<s_hs_script_op const *>(0x16771F0), reinterpret_cast<s_hs_script_op const *>(0x16772D0),
	reinterpret_cast<s_hs_script_op const *>(0x16773C0), reinterpret_cast<s_hs_script_op const *>(0x16774C0), reinterpret_cast<s_hs_script_op const *>(0x167758C), reinterpret_cast<s_hs_script_op const *>(0x1677658),
	reinterpret_cast<s_hs_script_op const *>(0x167771C), reinterpret_cast<s_hs_script_op const *>(0x1677874), reinterpret_cast<s_hs_script_op const *>(0x1677970), reinterpret_cast<s_hs_script_op const *>(0x1677A4C),
	reinterpret_cast<s_hs_script_op const *>(0x1677B2C), reinterpret_cast<s_hs_script_op const *>(0x1677BE4), reinterpret_cast<s_hs_script_op const *>(0x1677CE8), reinterpret_cast<s_hs_script_op const *>(0x1677DB8),
	reinterpret_cast<s_hs_script_op const *>(0x1677F34), reinterpret_cast<s_hs_script_op const *>(0x1678028), reinterpret_cast<s_hs_script_op const *>(0x1678108), reinterpret_cast<s_hs_script_op const *>(0x16781F8),
	reinterpret_cast<s_hs_script_op const *>(0x16782B4), reinterpret_cast<s_hs_script_op const *>(0x1678378), reinterpret_cast<s_hs_script_op const *>(0x167845C), reinterpret_cast<s_hs_script_op const *>(0x167855C),
	reinterpret_cast<s_hs_script_op const *>(0x16785F8), reinterpret_cast<s_hs_script_op const *>(0x1678708), reinterpret_cast<s_hs_script_op const *>(0x1678780), reinterpret_cast<s_hs_script_op const *>(0x1678870),
	reinterpret_cast<s_hs_script_op const *>(0x1678914), reinterpret_cast<s_hs_script_op const *>(0x1678A38), reinterpret_cast<s_hs_script_op const *>(0x1678B40), reinterpret_cast<s_hs_script_op const *>(0x1678C00),
	reinterpret_cast<s_hs_script_op const *>(0x1678C98), reinterpret_cast<s_hs_script_op const *>(0x1678D48), reinterpret_cast<s_hs_script_op const *>(0x1678E40), reinterpret_cast<s_hs_script_op const *>(0x1678F40),
	reinterpret_cast<s_hs_script_op const *>(0x1678FD0), reinterpret_cast<s_hs_script_op const *>(0x16790CC), reinterpret_cast<s_hs_script_op const *>(0x1679180), reinterpret_cast<s_hs_script_op const *>(0x167922C),
	reinterpret_cast<s_hs_script_op const *>(0x16792FC), reinterpret_cast<s_hs_script_op const *>(0x16793B0), reinterpret_cast<s_hs_script_op const *>(0x1679484), reinterpret_cast<s_hs_script_op const *>(0x1679540),
	reinterpret_cast<s_hs_script_op const *>(0x1679620), reinterpret_cast<s_hs_script_op const *>(0x16796A4), reinterpret_cast<s_hs_script_op const *>(0x16797A4), reinterpret_cast<s_hs_script_op const *>(0x1679870),
	reinterpret_cast<s_hs_script_op const *>(0x1679930), reinterpret_cast<s_hs_script_op const *>(0x1679A2C), reinterpret_cast<s_hs_script_op const *>(0x1679B34), reinterpret_cast<s_hs_script_op const *>(0x1679C44),
	reinterpret_cast<s_hs_script_op const *>(0x1679D38), reinterpret_cast<s_hs_script_op const *>(0x1679E0C), reinterpret_cast<s_hs_script_op const *>(0x1679E8C), reinterpret_cast<s_hs_script_op const *>(0x1679F68),
	reinterpret_cast<s_hs_script_op const *>(0x167A03C), reinterpret_cast<s_hs_script_op const *>(0x167A118), reinterpret_cast<s_hs_script_op const *>(0x167A268), reinterpret_cast<s_hs_script_op const *>(0x167A3A8),
	reinterpret_cast<s_hs_script_op const *>(0x167A49C), reinterpret_cast<s_hs_script_op const *>(0x167A570), reinterpret_cast<s_hs_script_op const *>(0x167A634), reinterpret_cast<s_hs_script_op const *>(0x167A704),
	reinterpret_cast<s_hs_script_op const *>(0x167A848), reinterpret_cast<s_hs_script_op const *>(0x167A98C), reinterpret_cast<s_hs_script_op const *>(0x167AAF0), reinterpret_cast<s_hs_script_op const *>(0x167ABF0),
	reinterpret_cast<s_hs_script_op const *>(0x167ACEC), reinterpret_cast<s_hs_script_op const *>(0x167AE10), reinterpret_cast<s_hs_script_op const *>(0x167AF64), reinterpret_cast<s_hs_script_op const *>(0x1672AF8),
	reinterpret_cast<s_hs_script_op const *>(0x1672C60), reinterpret_cast<s_hs_script_op const *>(0x1672E7C), reinterpret_cast<s_hs_script_op const *>(0x1672FF0), reinterpret_cast<s_hs_script_op const *>(0x1673194),
	reinterpret_cast<s_hs_script_op const *>(0x1673328), reinterpret_cast<s_hs_script_op const *>(0x1673440), reinterpret_cast<s_hs_script_op const *>(0x167357C), reinterpret_cast<s_hs_script_op const *>(0x16736CC),
	reinterpret_cast<s_hs_script_op const *>(0x16737A4), reinterpret_cast<s_hs_script_op const *>(0x16738BC), reinterpret_cast<s_hs_script_op const *>(0x16739F8), reinterpret_cast<s_hs_script_op const *>(0x1673B3C),
	reinterpret_cast<s_hs_script_op const *>(0x1673C08), reinterpret_cast<s_hs_script_op const *>(0x1673D98), reinterpret_cast<s_hs_script_op const *>(0x1673E90), reinterpret_cast<s_hs_script_op const *>(0x1673F58),
	reinterpret_cast<s_hs_script_op const *>(0x1674030), reinterpret_cast<s_hs_script_op const *>(0x1674188), reinterpret_cast<s_hs_script_op const *>(0x1674260), reinterpret_cast<s_hs_script_op const *>(0x1674390),
	reinterpret_cast<s_hs_script_op const *>(0x16744D0), reinterpret_cast<s_hs_script_op const *>(0x1674678), reinterpret_cast<s_hs_script_op const *>(0x16746F8), reinterpret_cast<s_hs_script_op const *>(0x16747FC),
	reinterpret_cast<s_hs_script_op const *>(0x167493C), reinterpret_cast<s_hs_script_op const *>(0x1674B08), reinterpret_cast<s_hs_script_op const *>(0x1674C64), reinterpret_cast<s_hs_script_op const *>(0x1674D48),
	reinterpret_cast<s_hs_script_op const *>(0x1674ED8), reinterpret_cast<s_hs_script_op const *>(0x1674FCC), reinterpret_cast<s_hs_script_op const *>(0x16750F4), reinterpret_cast<s_hs_script_op const *>(0x16751D4),
	reinterpret_cast<s_hs_script_op const *>(0x16752FC), reinterpret_cast<s_hs_script_op const *>(0x167538C), reinterpret_cast<s_hs_script_op const *>(0x16754B8), reinterpret_cast<s_hs_script_op const *>(0x167552C),
	reinterpret_cast<s_hs_script_op const *>(0x1675608), reinterpret_cast<s_hs_script_op const *>(0x16756A0), reinterpret_cast<s_hs_script_op const *>(0x1675774), reinterpret_cast<s_hs_script_op const *>(0x16758AC),
	reinterpret_cast<s_hs_script_op const *>(0x16759C4), reinterpret_cast<s_hs_script_op const *>(0x1675B00), reinterpret_cast<s_hs_script_op const *>(0x1675C08), reinterpret_cast<s_hs_script_op const *>(0x1675D24),
	reinterpret_cast<s_hs_script_op const *>(0x1675E0C), reinterpret_cast<s_hs_script_op const *>(0x1675F68), reinterpret_cast<s_hs_script_op const *>(0x167602C), reinterpret_cast<s_hs_script_op const *>(0x1676168),
	reinterpret_cast<s_hs_script_op const *>(0x1676280), reinterpret_cast<s_hs_script_op const *>(0x167637C), reinterpret_cast<s_hs_script_op const *>(0x16764CC), reinterpret_cast<s_hs_script_op const *>(0x16765D8),
	reinterpret_cast<s_hs_script_op const *>(0x1676764), reinterpret_cast<s_hs_script_op const *>(0x1676864), reinterpret_cast<s_hs_script_op const *>(0x1676988), reinterpret_cast<s_hs_script_op const *>(0x1676AB8),
	reinterpret_cast<s_hs_script_op const *>(0x1676BDC), reinterpret_cast<s_hs_script_op const *>(0x1676D10), reinterpret_cast<s_hs_script_op const *>(0x1676E68), reinterpret_cast<s_hs_script_op const *>(0x1676F78),
	reinterpret_cast<s_hs_script_op const *>(0x1677068), reinterpret_cast<s_hs_script_op const *>(0x1677190), reinterpret_cast<s_hs_script_op const *>(0x1677250), reinterpret_cast<s_hs_script_op const *>(0x1677344),
	reinterpret_cast<s_hs_script_op const *>(0x16773D0), reinterpret_cast<s_hs_script_op const *>(0x1677474), reinterpret_cast<s_hs_script_op const *>(0x167756C), reinterpret_cast<s_hs_script_op const *>(0x16775C8),
	reinterpret_cast<s_hs_script_op const *>(0x16776B4), reinterpret_cast<s_hs_script_op const *>(0x1677840), reinterpret_cast<s_hs_script_op const *>(0x16779AC), reinterpret_cast<s_hs_script_op const *>(0x1677B18),
	reinterpret_cast<s_hs_script_op const *>(0x1677C80), reinterpret_cast<s_hs_script_op const *>(0x1677D90), reinterpret_cast<s_hs_script_op const *>(0x1677F48), reinterpret_cast<s_hs_script_op const *>(0x16780F0),
	reinterpret_cast<s_hs_script_op const *>(0x1678268), reinterpret_cast<s_hs_script_op const *>(0x16783DC), reinterpret_cast<s_hs_script_op const *>(0x1678570), reinterpret_cast<s_hs_script_op const *>(0x167860C),
	reinterpret_cast<s_hs_script_op const *>(0x167871C), reinterpret_cast<s_hs_script_op const *>(0x16787BC), reinterpret_cast<s_hs_script_op const *>(0x16788B4), reinterpret_cast<s_hs_script_op const *>(0x1678990),
	reinterpret_cast<s_hs_script_op const *>(0x1678A60), reinterpret_cast<s_hs_script_op const *>(0x1678B84), reinterpret_cast<s_hs_script_op const *>(0x1678C28), reinterpret_cast<s_hs_script_op const *>(0x1678CBC),
	reinterpret_cast<s_hs_script_op const *>(0x1678D80), reinterpret_cast<s_hs_script_op const *>(0x1678ECC), reinterpret_cast<s_hs_script_op const *>(0x1679030), reinterpret_cast<s_hs_script_op const *>(0x1679194),
	reinterpret_cast<s_hs_script_op const *>(0x167926C), reinterpret_cast<s_hs_script_op const *>(0x167939C), reinterpret_cast<s_hs_script_op const *>(0x16794AC), reinterpret_cast<s_hs_script_op const *>(0x1679568),
	reinterpret_cast<s_hs_script_op const *>(0x1679634), reinterpret_cast<s_hs_script_op const *>(0x16796B8), reinterpret_cast<s_hs_script_op const *>(0x16797B8), reinterpret_cast<s_hs_script_op const *>(0x1679858),
	reinterpret_cast<s_hs_script_op const *>(0x167998C), reinterpret_cast<s_hs_script_op const *>(0x1679A7C), reinterpret_cast<s_hs_script_op const *>(0x1679B7C), reinterpret_cast<s_hs_script_op const *>(0x1679C04),
	reinterpret_cast<s_hs_script_op const *>(0x1679D60), reinterpret_cast<s_hs_script_op const *>(0x1679E5C), reinterpret_cast<s_hs_script_op const *>(0x1679F8C), reinterpret_cast<s_hs_script_op const *>(0x167A094),
	reinterpret_cast<s_hs_script_op const *>(0x167A1A0), reinterpret_cast<s_hs_script_op const *>(0x167A28C), reinterpret_cast<s_hs_script_op const *>(0x167A36C), reinterpret_cast<s_hs_script_op const *>(0x167A430),
	reinterpret_cast<s_hs_script_op const *>(0x167A4F8), reinterpret_cast<s_hs_script_op const *>(0x167A5E0), reinterpret_cast<s_hs_script_op const *>(0x167A6B4), reinterpret_cast<s_hs_script_op const *>(0x167A7B0),
	reinterpret_cast<s_hs_script_op const *>(0x167A8CC), reinterpret_cast<s_hs_script_op const *>(0x167A9D0), reinterpret_cast<s_hs_script_op const *>(0x167AABC), reinterpret_cast<s_hs_script_op const *>(0x167ABCC),
	reinterpret_cast<s_hs_script_op const *>(0x167AC9C), reinterpret_cast<s_hs_script_op const *>(0x167ADC0), reinterpret_cast<s_hs_script_op const *>(0x167AECC), reinterpret_cast<s_hs_script_op const *>(0x167AFC4),
	reinterpret_cast<s_hs_script_op const *>(0x1672A70), reinterpret_cast<s_hs_script_op const *>(0x1672B64), reinterpret_cast<s_hs_script_op const *>(0x1672C10), reinterpret_cast<s_hs_script_op const *>(0x1672CCC),
	reinterpret_cast<s_hs_script_op const *>(0x1672DB8), reinterpret_cast<s_hs_script_op const *>(0x1672ED4), reinterpret_cast<s_hs_script_op const *>(0x1672F88), reinterpret_cast<s_hs_script_op const *>(0x167303C),
	reinterpret_cast<s_hs_script_op const *>(0x1673104), reinterpret_cast<s_hs_script_op const *>(0x16731D4), reinterpret_cast<s_hs_script_op const *>(0x16732D8), reinterpret_cast<s_hs_script_op const *>(0x167339C),
	reinterpret_cast<s_hs_script_op const *>(0x167342C), reinterpret_cast<s_hs_script_op const *>(0x1673510), reinterpret_cast<s_hs_script_op const *>(0x16735B8), reinterpret_cast<s_hs_script_op const *>(0x167366C),
	reinterpret_cast<s_hs_script_op const *>(0x1673720), reinterpret_cast<s_hs_script_op const *>(0x16737E0), reinterpret_cast<s_hs_script_op const *>(0x167390C), reinterpret_cast<s_hs_script_op const *>(0x16739C0),
	reinterpret_cast<s_hs_script_op const *>(0x1673A78), reinterpret_cast<s_hs_script_op const *>(0x1673B50), reinterpret_cast<s_hs_script_op const *>(0x1673BE4), reinterpret_cast<s_hs_script_op const *>(0x1673CDC),
	reinterpret_cast<s_hs_script_op const *>(0x1673D70), reinterpret_cast<s_hs_script_op const *>(0x1673E08), reinterpret_cast<s_hs_script_op const *>(0x1673ECC), reinterpret_cast<s_hs_script_op const *>(0x1673F90),
	reinterpret_cast<s_hs_script_op const *>(0x1674078), reinterpret_cast<s_hs_script_op const *>(0x16741DC), reinterpret_cast<s_hs_script_op const *>(0x1674274), reinterpret_cast<s_hs_script_op const *>(0x167436C),
	reinterpret_cast<s_hs_script_op const *>(0x16743DC), reinterpret_cast<s_hs_script_op const *>(0x16744A8), reinterpret_cast<s_hs_script_op const *>(0x1674560), reinterpret_cast<s_hs_script_op const *>(0x1674660),
	reinterpret_cast<s_hs_script_op const *>(0x167470C), reinterpret_cast<s_hs_script_op const *>(0x167479C), reinterpret_cast<s_hs_script_op const *>(0x167485C), reinterpret_cast<s_hs_script_op const *>(0x167490C),
	reinterpret_cast<s_hs_script_op const *>(0x16749D8), reinterpret_cast<s_hs_script_op const *>(0x1674AA4), reinterpret_cast<s_hs_script_op const *>(0x1674BA0), reinterpret_cast<s_hs_script_op const *>(0x1674C0C),
	reinterpret_cast<s_hs_script_op const *>(0x1674CB8), reinterpret_cast<s_hs_script_op const *>(0x1674D74), reinterpret_cast<s_hs_script_op const *>(0x1674E6C), reinterpret_cast<s_hs_script_op const *>(0x1674F54),
	reinterpret_cast<s_hs_script_op const *>(0x1675004), reinterpret_cast<s_hs_script_op const *>(0x16750A4), reinterpret_cast<s_hs_script_op const *>(0x1675130), reinterpret_cast<s_hs_script_op const *>(0x16751E8),
	reinterpret_cast<s_hs_script_op const *>(0x16752D4), reinterpret_cast<s_hs_script_op const *>(0x1675338), reinterpret_cast<s_hs_script_op const *>(0x1675468), reinterpret_cast<s_hs_script_op const *>(0x16754DC),
	reinterpret_cast<s_hs_script_op const *>(0x167558C), reinterpret_cast<s_hs_script_op const *>(0x16756B0), reinterpret_cast<s_hs_script_op const *>(0x1675788), reinterpret_cast<s_hs_script_op const *>(0x16757D0),
	reinterpret_cast<s_hs_script_op const *>(0x16758DC), reinterpret_cast<s_hs_script_op const *>(0x1675A14), reinterpret_cast<s_hs_script_op const *>(0x1675B18), reinterpret_cast<s_hs_script_op const *>(0x1675C40),
	reinterpret_cast<s_hs_script_op const *>(0x1675D38), reinterpret_cast<s_hs_script_op const *>(0x1675E4C), reinterpret_cast<s_hs_script_op const *>(0x1675F7C), reinterpret_cast<s_hs_script_op const *>(0x1676040),
	reinterpret_cast<s_hs_script_op const *>(0x1676194), reinterpret_cast<s_hs_script_op const *>(0x167624C), reinterpret_cast<s_hs_script_op const *>(0x1676334), reinterpret_cast<s_hs_script_op const *>(0x1676390),
	reinterpret_cast<s_hs_script_op const *>(0x16764A4), reinterpret_cast<s_hs_script_op const *>(0x1676518), reinterpret_cast<s_hs_script_op const *>(0x16765FC), reinterpret_cast<s_hs_script_op const *>(0x167670C),
	reinterpret_cast<s_hs_script_op const *>(0x16767FC), reinterpret_cast<s_hs_script_op const *>(0x167689C), reinterpret_cast<s_hs_script_op const *>(0x1676944), reinterpret_cast<s_hs_script_op const *>(0x16769E8),
	reinterpret_cast<s_hs_script_op const *>(0x1676ACC), reinterpret_cast<s_hs_script_op const *>(0x1676B8C), reinterpret_cast<s_hs_script_op const *>(0x1676C58), reinterpret_cast<s_hs_script_op const *>(0x1676D38),
	reinterpret_cast<s_hs_script_op const *>(0x1676DE0), reinterpret_cast<s_hs_script_op const *>(0x1676EB8), reinterpret_cast<s_hs_script_op const *>(0x1676F64), reinterpret_cast<s_hs_script_op const *>(0x1676FD8),
	reinterpret_cast<s_hs_script_op const *>(0x1677104), reinterpret_cast<s_hs_script_op const *>(0x16771C8), reinterpret_cast<s_hs_script_op const *>(0x167722C), reinterpret_cast<s_hs_script_op const *>(0x1677358),
	reinterpret_cast<s_hs_script_op const *>(0x167740C), reinterpret_cast<s_hs_script_op const *>(0x1677488), reinterpret_cast<s_hs_script_op const *>(0x167755C), reinterpret_cast<s_hs_script_op const *>(0x1677604),
	reinterpret_cast<s_hs_script_op const *>(0x16776A4), reinterpret_cast<s_hs_script_op const *>(0x1677794), reinterpret_cast<s_hs_script_op const *>(0x167789C), reinterpret_cast<s_hs_script_op const *>(0x1677934),
	reinterpret_cast<s_hs_script_op const *>(0x1677A14), reinterpret_cast<s_hs_script_op const *>(0x1677AC0), reinterpret_cast<s_hs_script_op const *>(0x1677BAC), reinterpret_cast<s_hs_script_op const *>(0x1677C94),
	reinterpret_cast<s_hs_script_op const *>(0x1677D44), reinterpret_cast<s_hs_script_op const *>(0x1677E28), reinterpret_cast<s_hs_script_op const *>(0x1677F0C), reinterpret_cast<s_hs_script_op const *>(0x1677FC8),
	reinterpret_cast<s_hs_script_op const *>(0x1678098), reinterpret_cast<s_hs_script_op const *>(0x1678158), reinterpret_cast<s_hs_script_op const *>(0x167821C), reinterpret_cast<s_hs_script_op const *>(0x1678300),
	reinterpret_cast<s_hs_script_op const *>(0x16783B4), reinterpret_cast<s_hs_script_op const *>(0x16784CC), reinterpret_cast<s_hs_script_op const *>(0x1678598), reinterpret_cast<s_hs_script_op const *>(0x1678634),
	reinterpret_cast<s_hs_script_op const *>(0x1678730), reinterpret_cast<s_hs_script_op const *>(0x1678840), reinterpret_cast<s_hs_script_op const *>(0x16789FC), reinterpret_cast<s_hs_script_op const *>(0x1678AA0),
	reinterpret_cast<s_hs_script_op const *>(0x1678BD0), reinterpret_cast<s_hs_script_op const *>(0x1678CD0), reinterpret_cast<s_hs_script_op const *>(0x1678E04), reinterpret_cast<s_hs_script_op const *>(0x1678F18),
	reinterpret_cast<s_hs_script_op const *>(0x167901C), reinterpret_cast<s_hs_script_op const *>(0x1679148), reinterpret_cast<s_hs_script_op const *>(0x1679208), reinterpret_cast<s_hs_script_op const *>(0x1679338),
	reinterpret_cast<s_hs_script_op const *>(0x16793C4), reinterpret_cast<s_hs_script_op const *>(0x167952C), reinterpret_cast<s_hs_script_op const *>(0x16795E4), reinterpret_cast<s_hs_script_op const *>(0x1679690),
	reinterpret_cast<s_hs_script_op const *>(0x167977C), reinterpret_cast<s_hs_script_op const *>(0x1679828), reinterpret_cast<s_hs_script_op const *>(0x16798F8), reinterpret_cast<s_hs_script_op const *>(0x16799D4),
	reinterpret_cast<s_hs_script_op const *>(0x1679AA8), reinterpret_cast<s_hs_script_op const *>(0x1679B54), reinterpret_cast<s_hs_script_op const *>(0x1679C34), reinterpret_cast<s_hs_script_op const *>(0x1679CFC),
	reinterpret_cast<s_hs_script_op const *>(0x1679DBC), reinterpret_cast<s_hs_script_op const *>(0x1679E6C), reinterpret_cast<s_hs_script_op const *>(0x1679F54), reinterpret_cast<s_hs_script_op const *>(0x167A000),
	reinterpret_cast<s_hs_script_op const *>(0x167A0E8), reinterpret_cast<s_hs_script_op const *>(0x167A1F4), reinterpret_cast<s_hs_script_op const *>(0x167A2DC), reinterpret_cast<s_hs_script_op const *>(0x167A3B8),
	reinterpret_cast<s_hs_script_op const *>(0x167A480), reinterpret_cast<s_hs_script_op const *>(0x167A544), reinterpret_cast<s_hs_script_op const *>(0x167A608), reinterpret_cast<s_hs_script_op const *>(0x167A6F0),
	reinterpret_cast<s_hs_script_op const *>(0x167A800), reinterpret_cast<s_hs_script_op const *>(0x167A904), reinterpret_cast<s_hs_script_op const *>(0x167A9F8), reinterpret_cast<s_hs_script_op const *>(0x167AB38),
	reinterpret_cast<s_hs_script_op const *>(0x167AC34), reinterpret_cast<s_hs_script_op const *>(0x167AD30), reinterpret_cast<s_hs_script_op const *>(0x167AE44), reinterpret_cast<s_hs_script_op const *>(0x167AF28),
	reinterpret_cast<s_hs_script_op const *>(0x167B018), reinterpret_cast<s_hs_script_op const *>(0x1672A98), reinterpret_cast<s_hs_script_op const *>(0x1672B78), reinterpret_cast<s_hs_script_op const *>(0x1672C38),
	reinterpret_cast<s_hs_script_op const *>(0x1672D34), reinterpret_cast<s_hs_script_op const *>(0x1672DF4), reinterpret_cast<s_hs_script_op const *>(0x1672F14), reinterpret_cast<s_hs_script_op const *>(0x1672FCC),
	reinterpret_cast<s_hs_script_op const *>(0x167307C), reinterpret_cast<s_hs_script_op const *>(0x1673144), reinterpret_cast<s_hs_script_op const *>(0x1673200), reinterpret_cast<s_hs_script_op const *>(0x16732EC),
	reinterpret_cast<s_hs_script_op const *>(0x16733D4), reinterpret_cast<s_hs_script_op const *>(0x167347C), reinterpret_cast<s_hs_script_op const *>(0x1673524), reinterpret_cast<s_hs_script_op const *>(0x16735F4),
	reinterpret_cast<s_hs_script_op const *>(0x16736B8), reinterpret_cast<s_hs_script_op const *>(0x1673844), reinterpret_cast<s_hs_script_op const *>(0x16738E0), reinterpret_cast<s_hs_script_op const *>(0x16739AC),
	reinterpret_cast<s_hs_script_op const *>(0x1673A60), reinterpret_cast<s_hs_script_op const *>(0x1673AEC), reinterpret_cast<s_hs_script_op const *>(0x1673BA8), reinterpret_cast<s_hs_script_op const *>(0x1673C8C),
	reinterpret_cast<s_hs_script_op const *>(0x1673D50), reinterpret_cast<s_hs_script_op const *>(0x1673DF8), reinterpret_cast<s_hs_script_op const *>(0x1673FF4), reinterpret_cast<s_hs_script_op const *>(0x1674214),
	reinterpret_cast<s_hs_script_op const *>(0x167437C), reinterpret_cast<s_hs_script_op const *>(0x167446C), reinterpret_cast<s_hs_script_op const *>(0x16745F8), reinterpret_cast<s_hs_script_op const *>(0x167474C),
	reinterpret_cast<s_hs_script_op const *>(0x16748D4), reinterpret_cast<s_hs_script_op const *>(0x1674A2C), reinterpret_cast<s_hs_script_op const *>(0x1674BB8), reinterpret_cast<s_hs_script_op const *>(0x1674D34),
	reinterpret_cast<s_hs_script_op const *>(0x1674EC4), reinterpret_cast<s_hs_script_op const *>(0x1675018), reinterpret_cast<s_hs_script_op const *>(0x167511C), reinterpret_cast<s_hs_script_op const *>(0x16752AC),
	reinterpret_cast<s_hs_script_op const *>(0x1675450), reinterpret_cast<s_hs_script_op const *>(0x16755B4), reinterpret_cast<s_hs_script_op const *>(0x167575C), reinterpret_cast<s_hs_script_op const *>(0x16758C4),
	reinterpret_cast<s_hs_script_op const *>(0x167598C), reinterpret_cast<s_hs_script_op const *>(0x1675A28), reinterpret_cast<s_hs_script_op const *>(0x1675AC4), reinterpret_cast<s_hs_script_op const *>(0x1675B94),
	reinterpret_cast<s_hs_script_op const *>(0x1675C30), reinterpret_cast<s_hs_script_op const *>(0x1675D84), reinterpret_cast<s_hs_script_op const *>(0x1675EF8), reinterpret_cast<s_hs_script_op const *>(0x1675FE0),
	reinterpret_cast<s_hs_script_op const *>(0x16761A8), reinterpret_cast<s_hs_script_op const *>(0x1676260), reinterpret_cast<s_hs_script_op const *>(0x1676358), reinterpret_cast<s_hs_script_op const *>(0x16763E4),
	reinterpret_cast<s_hs_script_op const *>(0x16764F0), reinterpret_cast<s_hs_script_op const *>(0x16765C4), reinterpret_cast<s_hs_script_op const *>(0x1676688), reinterpret_cast<s_hs_script_op const *>(0x1676788),
	reinterpret_cast<s_hs_script_op const *>(0x1676850), reinterpret_cast<s_hs_script_op const *>(0x1676910), reinterpret_cast<s_hs_script_op const *>(0x167699C), reinterpret_cast<s_hs_script_op const *>(0x1676A68),
	reinterpret_cast<s_hs_script_op const *>(0x1676B64), reinterpret_cast<s_hs_script_op const *>(0x1676C08), reinterpret_cast<s_hs_script_op const *>(0x1676CEC), reinterpret_cast<s_hs_script_op const *>(0x1676DB8),
	reinterpret_cast<s_hs_script_op const *>(0x1676E90), reinterpret_cast<s_hs_script_op const *>(0x1676F1C), reinterpret_cast<s_hs_script_op const *>(0x1676FA0), reinterpret_cast<s_hs_script_op const *>(0x167712C),
	reinterpret_cast<s_hs_script_op const *>(0x1677274), reinterpret_cast<s_hs_script_op const *>(0x16773E4), reinterpret_cast<s_hs_script_op const *>(0x1677534), reinterpret_cast<s_hs_script_op const *>(0x1677614),
	reinterpret_cast<s_hs_script_op const *>(0x1677740), reinterpret_cast<s_hs_script_op const *>(0x16778D4), reinterpret_cast<s_hs_script_op const *>(0x16779E8), reinterpret_cast<s_hs_script_op const *>(0x1677B54),
	reinterpret_cast<s_hs_script_op const *>(0x1677CA8), reinterpret_cast<s_hs_script_op const *>(0x1677E14), reinterpret_cast<s_hs_script_op const *>(0x1677EE8), reinterpret_cast<s_hs_script_op const *>(0x1677FB8),
	reinterpret_cast<s_hs_script_op const *>(0x1678080), reinterpret_cast<s_hs_script_op const *>(0x16781A8), reinterpret_cast<s_hs_script_op const *>(0x167833C), reinterpret_cast<s_hs_script_op const *>(0x167850C),
	reinterpret_cast<s_hs_script_op const *>(0x16785C0), reinterpret_cast<s_hs_script_op const *>(0x16786E0), reinterpret_cast<s_hs_script_op const *>(0x16787F4), reinterpret_cast<s_hs_script_op const *>(0x1678954),
	reinterpret_cast<s_hs_script_op const *>(0x1678AD8), reinterpret_cast<s_hs_script_op const *>(0x1678C38), reinterpret_cast<s_hs_script_op const *>(0x1678D34), reinterpret_cast<s_hs_script_op const *>(0x1678DB8),
	reinterpret_cast<s_hs_script_op const *>(0x1678F54), reinterpret_cast<s_hs_script_op const *>(0x16790A8), reinterpret_cast<s_hs_script_op const *>(0x16791CC), reinterpret_cast<s_hs_script_op const *>(0x16792BC),
	reinterpret_cast<s_hs_script_op const *>(0x16793D4), reinterpret_cast<s_hs_script_op const *>(0x1679518), reinterpret_cast<s_hs_script_op const *>(0x1679658), reinterpret_cast<s_hs_script_op const *>(0x1679790),
	reinterpret_cast<s_hs_script_op const *>(0x1679844), reinterpret_cast<s_hs_script_op const *>(0x16799AC), reinterpret_cast<s_hs_script_op const *>(0x1679B20), reinterpret_cast<s_hs_script_op const *>(0x1679BB4),
	reinterpret_cast<s_hs_script_op const *>(0x1679C5C), reinterpret_cast<s_hs_script_op const *>(0x1679DD0), reinterpret_cast<s_hs_script_op const *>(0x1679F40), reinterpret_cast<s_hs_script_op const *>(0x1679FEC),
	reinterpret_cast<s_hs_script_op const *>(0x167A0BC), reinterpret_cast<s_hs_script_op const *>(0x167A1B4), reinterpret_cast<s_hs_script_op const *>(0x167A2C8), reinterpret_cast<s_hs_script_op const *>(0x167A394),
	reinterpret_cast<s_hs_script_op const *>(0x167A4D0), reinterpret_cast<s_hs_script_op const *>(0x167A580), reinterpret_cast<s_hs_script_op const *>(0x167A658), reinterpret_cast<s_hs_script_op const *>(0x167A714),
	reinterpret_cast<s_hs_script_op const *>(0x167A86C), reinterpret_cast<s_hs_script_op const *>(0x167A950), reinterpret_cast<s_hs_script_op const *>(0x167AA58), reinterpret_cast<s_hs_script_op const *>(0x167AB98),
	reinterpret_cast<s_hs_script_op const *>(0x167AD78), reinterpret_cast<s_hs_script_op const *>(0x167AEA0), reinterpret_cast<s_hs_script_op const *>(0x167AFA0), reinterpret_cast<s_hs_script_op const *>(0x167B03C),
	reinterpret_cast<s_hs_script_op const *>(0x1672AE8), reinterpret_cast<s_hs_script_op const *>(0x1672BD4), reinterpret_cast<s_hs_script_op const *>(0x1672CA4), reinterpret_cast<s_hs_script_op const *>(0x1672D80),
	reinterpret_cast<s_hs_script_op const *>(0x1672F00), reinterpret_cast<s_hs_script_op const *>(0x1672FDC), reinterpret_cast<s_hs_script_op const *>(0x16730B4), reinterpret_cast<s_hs_script_op const *>(0x1673228),
	reinterpret_cast<s_hs_script_op const *>(0x1673388), reinterpret_cast<s_hs_script_op const *>(0x16734D0), reinterpret_cast<s_hs_script_op const *>(0x16735A8), reinterpret_cast<s_hs_script_op const *>(0x1673658),
	reinterpret_cast<s_hs_script_op const *>(0x1673734), reinterpret_cast<s_hs_script_op const *>(0x1673808), reinterpret_cast<s_hs_script_op const *>(0x1673890), reinterpret_cast<s_hs_script_op const *>(0x1673A10),
	reinterpret_cast<s_hs_script_op const *>(0x1673A88), reinterpret_cast<s_hs_script_op const *>(0x1673B70), reinterpret_cast<s_hs_script_op const *>(0x1673C1C), reinterpret_cast<s_hs_script_op const *>(0x1673CF4),
	reinterpret_cast<s_hs_script_op const *>(0x1673DC0), reinterpret_cast<s_hs_script_op const *>(0x1673E54), reinterpret_cast<s_hs_script_op const *>(0x1673F0C), reinterpret_cast<s_hs_script_op const *>(0x1674020),
	reinterpret_cast<s_hs_script_op const *>(0x1674160), reinterpret_cast<s_hs_script_op const *>(0x1674250), reinterpret_cast<s_hs_script_op const *>(0x167431C), reinterpret_cast<s_hs_script_op const *>(0x16743B8),
	reinterpret_cast<s_hs_script_op const *>(0x1674498), reinterpret_cast<s_hs_script_op const *>(0x1674578), reinterpret_cast<s_hs_script_op const *>(0x1674634), reinterpret_cast<s_hs_script_op const *>(0x16746E4),
	reinterpret_cast<s_hs_script_op const *>(0x16747B4), reinterpret_cast<s_hs_script_op const *>(0x1674838), reinterpret_cast<s_hs_script_op const *>(0x16748FC), reinterpret_cast<s_hs_script_op const *>(0x16749C4),
	reinterpret_cast<s_hs_script_op const *>(0x1674AF4), reinterpret_cast<s_hs_script_op const *>(0x1674C50), reinterpret_cast<s_hs_script_op const *>(0x1674CD0), reinterpret_cast<s_hs_script_op const *>(0x1674DA4),
	reinterpret_cast<s_hs_script_op const *>(0x1674E18), reinterpret_cast<s_hs_script_op const *>(0x1674FA4), reinterpret_cast<s_hs_script_op const *>(0x1675090), reinterpret_cast<s_hs_script_op const *>(0x16751AC),
	reinterpret_cast<s_hs_script_op const *>(0x1675284), reinterpret_cast<s_hs_script_op const *>(0x167539C), reinterpret_cast<s_hs_script_op const *>(0x16754A4), reinterpret_cast<s_hs_script_op const *>(0x1675550),
	reinterpret_cast<s_hs_script_op const *>(0x1675668), reinterpret_cast<s_hs_script_op const *>(0x1675730), reinterpret_cast<s_hs_script_op const *>(0x16757AC), reinterpret_cast<s_hs_script_op const *>(0x1675884),
	reinterpret_cast<s_hs_script_op const *>(0x1675918), reinterpret_cast<s_hs_script_op const *>(0x16759F0), reinterpret_cast<s_hs_script_op const *>(0x1675A74), reinterpret_cast<s_hs_script_op const *>(0x1675B44),
	reinterpret_cast<s_hs_script_op const *>(0x1675BF8), reinterpret_cast<s_hs_script_op const *>(0x1675CA8), reinterpret_cast<s_hs_script_op const *>(0x1675D5C), reinterpret_cast<s_hs_script_op const *>(0x1675DF8),
	reinterpret_cast<s_hs_script_op const *>(0x1675ECC), reinterpret_cast<s_hs_script_op const *>(0x1675FB4), reinterpret_cast<s_hs_script_op const *>(0x167601C), reinterpret_cast<s_hs_script_op const *>(0x16760F0),
	reinterpret_cast<s_hs_script_op const *>(0x16761C4), reinterpret_cast<s_hs_script_op const *>(0x1676270), reinterpret_cast<s_hs_script_op const *>(0x1676344), reinterpret_cast<s_hs_script_op const *>(0x167640C),
	reinterpret_cast<s_hs_script_op const *>(0x16764B8), reinterpret_cast<s_hs_script_op const *>(0x1676558), reinterpret_cast<s_hs_script_op const *>(0x1676624), reinterpret_cast<s_hs_script_op const *>(0x1676720),
	reinterpret_cast<s_hs_script_op const *>(0x167680C), reinterpret_cast<s_hs_script_op const *>(0x16768C0), reinterpret_cast<s_hs_script_op const *>(0x1676958), reinterpret_cast<s_hs_script_op const *>(0x16769FC),
	reinterpret_cast<s_hs_script_op const *>(0x1676B10), reinterpret_cast<s_hs_script_op const *>(0x1676BB4), reinterpret_cast<s_hs_script_op const *>(0x1676C84), reinterpret_cast<s_hs_script_op const *>(0x1676E2C),
	reinterpret_cast<s_hs_script_op const *>(0x1676ECC), reinterpret_cast<s_hs_script_op const *>(0x1677010), reinterpret_cast<s_hs_script_op const *>(0x1677140), reinterpret_cast<s_hs_script_op const *>(0x16772F8),
	reinterpret_cast<s_hs_script_op const *>(0x16773AC), reinterpret_cast<s_hs_script_op const *>(0x1677498), reinterpret_cast<s_hs_script_op const *>(0x16775A0), reinterpret_cast<s_hs_script_op const *>(0x167767C),
	reinterpret_cast<s_hs_script_op const *>(0x167772C), reinterpret_cast<s_hs_script_op const *>(0x1677830), reinterpret_cast<s_hs_script_op const *>(0x1677998), reinterpret_cast<s_hs_script_op const *>(0x1677A3C),
	reinterpret_cast<s_hs_script_op const *>(0x1677B40), reinterpret_cast<s_hs_script_op const *>(0x1677BF8), reinterpret_cast<s_hs_script_op const *>(0x1677DF8), reinterpret_cast<s_hs_script_op const *>(0x1677F78),
	reinterpret_cast<s_hs_script_op const *>(0x16780C4), reinterpret_cast<s_hs_script_op const *>(0x16781BC), reinterpret_cast<s_hs_script_op const *>(0x1678314), reinterpret_cast<s_hs_script_op const *>(0x1678448),
	reinterpret_cast<s_hs_script_op const *>(0x16785AC), reinterpret_cast<s_hs_script_op const *>(0x16786F4), reinterpret_cast<s_hs_script_op const *>(0x1678818), reinterpret_cast<s_hs_script_op const *>(0x16789A4),
	reinterpret_cast<s_hs_script_op const *>(0x1678B54), reinterpret_cast<s_hs_script_op const *>(0x1678C84), reinterpret_cast<s_hs_script_op const *>(0x1678D94), reinterpret_cast<s_hs_script_op const *>(0x1678E90),
	reinterpret_cast<s_hs_script_op const *>(0x1678F68), reinterpret_cast<s_hs_script_op const *>(0x167900C), reinterpret_cast<s_hs_script_op const *>(0x16791A8), reinterpret_cast<s_hs_script_op const *>(0x1679254),
	reinterpret_cast<s_hs_script_op const *>(0x1679310), reinterpret_cast<s_hs_script_op const *>(0x1679470), reinterpret_cast<s_hs_script_op const *>(0x16795F4), reinterpret_cast<s_hs_script_op const *>(0x1679714),
	reinterpret_cast<s_hs_script_op const *>(0x16798B8), reinterpret_cast<s_hs_script_op const *>(0x1679954), reinterpret_cast<s_hs_script_op const *>(0x1679A08), reinterpret_cast<s_hs_script_op const *>(0x1679B8C),
	reinterpret_cast<s_hs_script_op const *>(0x1679C9C), reinterpret_cast<s_hs_script_op const *>(0x1679DF8), reinterpret_cast<s_hs_script_op const *>(0x1679EE4), reinterpret_cast<s_hs_script_op const *>(0x167A050),
	reinterpret_cast<s_hs_script_op const *>(0x167A20C), reinterpret_cast<s_hs_script_op const *>(0x167A458), reinterpret_cast<s_hs_script_op const *>(0x167A50C), reinterpret_cast<s_hs_script_op const *>(0x167A668),
	reinterpret_cast<s_hs_script_op const *>(0x167A768), reinterpret_cast<s_hs_script_op const *>(0x167A93C), reinterpret_cast<s_hs_script_op const *>(0x167AB00), reinterpret_cast<s_hs_script_op const *>(0x167AC10),
	reinterpret_cast<s_hs_script_op const *>(0x167AD10), reinterpret_cast<s_hs_script_op const *>(0x167ADEC), reinterpret_cast<s_hs_script_op const *>(0x167AF04), reinterpret_cast<s_hs_script_op const *>(0x1672A20),
	reinterpret_cast<s_hs_script_op const *>(0x1672B8C), reinterpret_cast<s_hs_script_op const *>(0x1672CE4), reinterpret_cast<s_hs_script_op const *>(0x1672E54), reinterpret_cast<s_hs_script_op const *>(0x1672FB8),
	reinterpret_cast<s_hs_script_op const *>(0x1673118), reinterpret_cast<s_hs_script_op const *>(0x16731C4), reinterpret_cast<s_hs_script_op const *>(0x16732C8), reinterpret_cast<s_hs_script_op const *>(0x1673418),
	reinterpret_cast<s_hs_script_op const *>(0x16734F8), reinterpret_cast<s_hs_script_op const *>(0x167356C), reinterpret_cast<s_hs_script_op const *>(0x1673608), reinterpret_cast<s_hs_script_op const *>(0x1673780),
	reinterpret_cast<s_hs_script_op const *>(0x16738F4), reinterpret_cast<s_hs_script_op const *>(0x16739E8), reinterpret_cast<s_hs_script_op const *>(0x1673B14), reinterpret_cast<s_hs_script_op const *>(0x1673C40),
	reinterpret_cast<s_hs_script_op const *>(0x1673DAC), reinterpret_cast<s_hs_script_op const *>(0x1673EB8), reinterpret_cast<s_hs_script_op const *>(0x1673FA4), reinterpret_cast<s_hs_script_op const *>(0x167408C),
	reinterpret_cast<s_hs_script_op const *>(0x1674200), reinterpret_cast<s_hs_script_op const *>(0x1674284), reinterpret_cast<s_hs_script_op const *>(0x167435C), reinterpret_cast<s_hs_script_op const *>(0x1674480),
	reinterpret_cast<s_hs_script_op const *>(0x1674648), reinterpret_cast<s_hs_script_op const *>(0x1674760), reinterpret_cast<s_hs_script_op const *>(0x1674848), reinterpret_cast<s_hs_script_op const *>(0x1674924),
	reinterpret_cast<s_hs_script_op const *>(0x16749F0), reinterpret_cast<s_hs_script_op const *>(0x1674A90), reinterpret_cast<s_hs_script_op const *>(0x1674B74), reinterpret_cast<s_hs_script_op const *>(0x1674C24),
	reinterpret_cast<s_hs_script_op const *>(0x1674CA0), reinterpret_cast<s_hs_script_op const *>(0x1674D5C), reinterpret_cast<s_hs_script_op const *>(0x1674E5C), reinterpret_cast<s_hs_script_op const *>(0x1674F40),
	reinterpret_cast<s_hs_script_op const *>(0x1674FE0), reinterpret_cast<s_hs_script_op const *>(0x1675158), reinterpret_cast<s_hs_script_op const *>(0x167525C), reinterpret_cast<s_hs_script_op const *>(0x1675360),
	reinterpret_cast<s_hs_script_op const *>(0x1675490), reinterpret_cast<s_hs_script_op const *>(0x1675518), reinterpret_cast<s_hs_script_op const *>(0x16755CC), reinterpret_cast<s_hs_script_op const *>(0x167567C),
	reinterpret_cast<s_hs_script_op const *>(0x167579C), reinterpret_cast<s_hs_script_op const *>(0x1675870), reinterpret_cast<s_hs_script_op const *>(0x1675954), reinterpret_cast<s_hs_script_op const *>(0x1675A60),
	reinterpret_cast<s_hs_script_op const *>(0x1675B84), reinterpret_cast<s_hs_script_op const *>(0x1675C7C), reinterpret_cast<s_hs_script_op const *>(0x1675D4C), reinterpret_cast<s_hs_script_op const *>(0x1675E90),
	reinterpret_cast<s_hs_script_op const *>(0x1675FA4), reinterpret_cast<s_hs_script_op const *>(0x1676068), reinterpret_cast<s_hs_script_op const *>(0x1676130), reinterpret_cast<s_hs_script_op const *>(0x1676294),
	reinterpret_cast<s_hs_script_op const *>(0x1676368), reinterpret_cast<s_hs_script_op const *>(0x1676490), reinterpret_cast<s_hs_script_op const *>(0x1676580), reinterpret_cast<s_hs_script_op const *>(0x1676664),
	reinterpret_cast<s_hs_script_op const *>(0x16767D4), reinterpret_cast<s_hs_script_op const *>(0x1676878), reinterpret_cast<s_hs_script_op const *>(0x1676924), reinterpret_cast<s_hs_script_op const *>(0x16769D8),
	reinterpret_cast<s_hs_script_op const *>(0x1676A94), reinterpret_cast<s_hs_script_op const *>(0x1676C30), reinterpret_cast<s_hs_script_op const *>(0x1676D00), reinterpret_cast<s_hs_script_op const *>(0x1676DCC),
	reinterpret_cast<s_hs_script_op const *>(0x1676EE0), reinterpret_cast<s_hs_script_op const *>(0x167707C), reinterpret_cast<s_hs_script_op const *>(0x1677154), reinterpret_cast<s_hs_script_op const *>(0x1677204),
	reinterpret_cast<s_hs_script_op const *>(0x167730C), reinterpret_cast<s_hs_script_op const *>(0x1677384), reinterpret_cast<s_hs_script_op const *>(0x1677430), reinterpret_cast<s_hs_script_op const *>(0x1677520),
	reinterpret_cast<s_hs_script_op const *>(0x1677644), reinterpret_cast<s_hs_script_op const *>(0x16777A8), reinterpret_cast<s_hs_script_op const *>(0x1677920), reinterpret_cast<s_hs_script_op const *>(0x1677A60),
	reinterpret_cast<s_hs_script_op const *>(0x1677B6C), reinterpret_cast<s_hs_script_op const *>(0x1677C20), reinterpret_cast<s_hs_script_op const *>(0x1677CF8), reinterpret_cast<s_hs_script_op const *>(0x1677E3C),
	reinterpret_cast<s_hs_script_op const *>(0x1677FA4), reinterpret_cast<s_hs_script_op const *>(0x16780AC), reinterpret_cast<s_hs_script_op const *>(0x1678280), reinterpret_cast<s_hs_script_op const *>(0x16783C8),
	reinterpret_cast<s_hs_script_op const *>(0x1678534), reinterpret_cast<s_hs_script_op const *>(0x16786B0), reinterpret_cast<s_hs_script_op const *>(0x16787CC), reinterpret_cast<s_hs_script_op const *>(0x16788C8),
	reinterpret_cast<s_hs_script_op const *>(0x16789CC), reinterpret_cast<s_hs_script_op const *>(0x1678A88), reinterpret_cast<s_hs_script_op const *>(0x1678B98), reinterpret_cast<s_hs_script_op const *>(0x1678C48),
	reinterpret_cast<s_hs_script_op const *>(0x1678CF8), reinterpret_cast<s_hs_script_op const *>(0x1678DA8), reinterpret_cast<s_hs_script_op const *>(0x1678E7C), reinterpret_cast<s_hs_script_op const *>(0x1678FA8),
	reinterpret_cast<s_hs_script_op const *>(0x1679098), reinterpret_cast<s_hs_script_op const *>(0x16791BC), reinterpret_cast<s_hs_script_op const *>(0x1679280), reinterpret_cast<s_hs_script_op const *>(0x1679360),
	reinterpret_cast<s_hs_script_op const *>(0x16794C4), reinterpret_cast<s_hs_script_op const *>(0x167960C), reinterpret_cast<s_hs_script_op const *>(0x16796D8), reinterpret_cast<s_hs_script_op const *>(0x16797EC),
	reinterpret_cast<s_hs_script_op const *>(0x1679940), reinterpret_cast<s_hs_script_op const *>(0x1679A40), reinterpret_cast<s_hs_script_op const *>(0x1679BA0), reinterpret_cast<s_hs_script_op const *>(0x1679CB0),
	reinterpret_cast<s_hs_script_op const *>(0x1679DE4), reinterpret_cast<s_hs_script_op const *>(0x1679F1C), reinterpret_cast<s_hs_script_op const *>(0x1679FA0), reinterpret_cast<s_hs_script_op const *>(0x167A140),
	reinterpret_cast<s_hs_script_op const *>(0x167A2A0), reinterpret_cast<s_hs_script_op const *>(0x167A3D4), reinterpret_cast<s_hs_script_op const *>(0x167A51C), reinterpret_cast<s_hs_script_op const *>(0x167A644),
	reinterpret_cast<s_hs_script_op const *>(0x167A7C4), reinterpret_cast<s_hs_script_op const *>(0x167A928), reinterpret_cast<s_hs_script_op const *>(0x167AA90), reinterpret_cast<s_hs_script_op const *>(0x167ABE0),
	reinterpret_cast<s_hs_script_op const *>(0x167AD44), reinterpret_cast<s_hs_script_op const *>(0x167AEF0), reinterpret_cast<s_hs_script_op const *>(0x167B028), reinterpret_cast<s_hs_script_op const *>(0x1672ABC),
	reinterpret_cast<s_hs_script_op const *>(0x1672BA0), reinterpret_cast<s_hs_script_op const *>(0x1672C94), reinterpret_cast<s_hs_script_op const *>(0x1672D94), reinterpret_cast<s_hs_script_op const *>(0x1672E98),
	reinterpret_cast<s_hs_script_op const *>(0x1672F60), reinterpret_cast<s_hs_script_op const *>(0x1673008), reinterpret_cast<s_hs_script_op const *>(0x16730D8), reinterpret_cast<s_hs_script_op const *>(0x1673180),
	reinterpret_cast<s_hs_script_op const *>(0x167329C), reinterpret_cast<s_hs_script_op const *>(&hades_file_local::hs_cinematic_scripting_start_animation_legacy_op), reinterpret_cast<s_hs_script_op const *>(&hades_file_local::hs_cinematic_scripting_create_object_legacy_op), reinterpret_cast<s_hs_script_op const *>(&hades_file_local::hs_cinematic_scripting_create_and_animate_object_legacy_op),
	reinterpret_cast<s_hs_script_op const *>(&hades_file_local::hs_cinematic_scripting_create_and_animate_object_no_animation_legacy_op), reinterpret_cast<s_hs_script_op const *>(&hades_file_local::hs_cinematic_scripting_create_and_animate_cinematic_object_legacy_op), reinterpret_cast<s_hs_script_op const *>(&hades_file_local::hs_cinematic_scripting_destroy_object_legacy_op), reinterpret_cast<s_hs_script_op const *>(&hades_file_local::hs_mp_wake_script_evaluate_op),
	reinterpret_cast<s_hs_script_op const *>(&hades_file_local::hs_dew_method_stub_op), reinterpret_cast<s_hs_script_op const *>(&hades_file_local::hs_vehicle_test_seat_list_legacy_op), reinterpret_cast<s_hs_script_op const *>(&hades_file_local::hs_vehicle_test_seat_legacy_op),
};

extern "C" char const *script_op_names[1707] =
{
	"begin", "begin_random", "if", "cond", "set", "and",
	"or", "+", "-", "*", "/", "%",
	"min", "max", "=", "!=", ">", "",
	">=", "", "sleep", "sleep_forever", "sleep_until", "wake",
	"inspect", "unit", "evaluate", "not", "pin", "print",
	"log_print", "debug_scripting_show_thread", "debug_script_thread", "debug_scripting", "debug_scripting_globals", "debug_scripting_variable",
	"debug_scripting_variable_all", "breakpoint", "kill_active_scripts", "get_executing_running_thread", "kill_thread", "script_started",
	"script_finished", "players", "player_get", "kill_volume_enable", "kill_volume_disable", "volume_teleport_players_not_inside",
	"volume_test_object", "volume_test_objects", "volume_test_objects_all", "volume_test_players", "volume_test_players_all", "volume_return_objects",
	"volume_return_objects_by_type", "zone_set_trigger_volume_enable", "list_get", "list_count", "list_count_not_dead", "effect_new",
	"effect_new_random", "effect_new_at_ai_point", "effect_new_on_object_marker", "effect_new_on_object", "damage_new", "damage_object_effect",
	"damage_objects_effect", "damage_object", "damage_objects", "damage_players", "soft_ceiling_enable", "object_create",
	"object_create_clone", "object_create_anew", "object_create_if_necessary", "object_create_containing", "object_create_clone_containing", "object_create_anew_containing",
	"object_create_folder", "object_create_folder_anew", "object_destroy", "object_destroy_containing", "object_destroy_all", "object_destroy_type_mask",
	"objects_delete_by_definition", "object_destroy_folder", "object_hide", "object_set_shadowless", "object_buckling_magnitude_get", "object_function_set",
	"object_set_function_variable", "object_clear_function_variable", "object_clear_all_function_variables", "object_dynamic_simulation_disable", "object_set_phantom_power", "object_wake_physics",
	"object_set_ranged_attack_inhibited", "object_set_melee_attack_inhibited", "objects_dump_memory", "object_get_health", "object_get_shield", "object_set_shield_effect",
	"object_set_physics", "object_get_parent", "objects_attach", "object_at_marker", "objects_detach", "object_set_scale",
	"object_set_velocity", "object_set_inertia_tensor_scale", "object_set_collision_damage_armor_scale", "object_set_velocity", "object_set_deleted_when_deactivated", "object_model_target_destroyed",
	"object_model_targets_destroyed", "object_damage_damage_section", "object_cannot_die", "object_vitality_pinned", "garbage_collect_now", "garbage_collect_unsafe",
	"garbage_collect_multiplayer", "object_cannot_take_damage", "object_can_take_damage", "object_cinematic_lod", "object_cinematic_collision", "object_cinematic_visibility",
	"objects_predict", "objects_predict_high", "objects_predict_low", "object_type_predict_high", "object_type_predict_low", "object_type_predict",
	"object_teleport", "object_teleport_to_ai_point", "object_set_facing", "object_set_shield", "object_set_shield_normalized", "object_set_shield_stun",
	"object_set_shield_stun_infinite", "object_set_permutation", "object_set_variant", "object_set_region_state", "objects_can_see_object", "objects_can_see_flag",
	"objects_distance_to_object", "objects_distance_to_flag", "map_info", "position_predict", "shader_predict", "bitmap_predict",
	"script_recompile", "script_doc", "help", "game_engine_objects", "random_range", "real_random_range",
	"physics_constants_reset", "physics_set_gravity", "physics_set_velocity_frame", "physics_disable_character_ground_adhesion_forces", "havok_debug_start", "havok_dump_world",
	"havok_dump_world_close_movie", "havok_profile_start", "havok_profile_stop", "havok_profile_range", "havok_reset_allocated_state", "breakable_surfaces_enable",
	"breakable_surfaces_reset", "recording_play", "recording_play_and_delete", "recording_play_and_hover", "recording_kill", "recording_time",
	"render_lights", "print_light_state", "render_lights_enable_cinematic_shadow", "texture_camera_set_object_marker", "texture_camera_set_position", "texture_camera_set_target",
	"texture_camera_attach_to_object", "texture_camera_target_object", "texture_camera_position_world_offset", "texture_camera_on", "texture_camera_off", "texture_camera_set_aspect_ratio",
	"texture_camera_set_resolution", "texture_camera_render_mode", "unknown", "texture_camera_set_fov", "texture_camera_set_fov_frame_target", "texture_camera_enable_dynamic_lights",
	"hud_camera_on", "hud_camera_off", "hud_camera_set_position", "hud_camera_set_target", "hud_camera_attach_to_object", "hud_camera_target_object",
	"hud_camera_structure", "hud_camera_highlight_object", "hud_camera_clear_objects", "hud_camera_spin_around", "hud_camera_from_player_view", "hud_camera_window",
	"render_debug_texture_camera", "debug_structure_cluster", "render_debug_structure_cluster_fog", "render_debug_structure_fog_plane", "render_debug_structure_fog_plane_infinite_extent", "render_debug_structure_fog_zone",
	"render_debug_structure_fog_zone_floodfill", "render_debug_structure_all_fog_planes", "render_debug_structure_all_cluster_errors", "render_debug_structure_line_opacity", "render_debug_structure_text_opacity", "render_debug_structure_opacity",
	"render_debug_structure_non_occluded_fog_planes", "render_debug_structure_lightmaps_use_pervertex", "render_debug_structure_lightmaps_use_reset", "render_debug_structure_lightmaps_sample_enable", "render_debug_structure_lightmaps_sample_disable", "render_debug_query_object_bitmaps",
	"render_debug_query_bsp_resources", "render_debug_query_all_object_resources", "render_debug_query_d3d_resources", "render_debug_text_using_simple_font", "render_postprocess_color_tweaking_reset", "scenery_animation_start",
	"scenery_animation_start_loop", "scenery_animation_start_relative", "scenery_animation_start_relative_loop", "scenery_animation_start_at_frame", "scenery_animation_start_relative_at_frame", "scenery_animation_idle",
	"scenery_get_animation_time", "unit_can_blink", "unit_set_active_camo", "unit_open", "unit_close", "unit_kill",
	"unit_kill_silent", "unit_is_emitting", "unit_get_custom_animation_time", "unit_stop_custom_animation", "custom_animation", "custom_animation_loop",
	"custom_animation_relative", "custom_animation_relative_loop", "custom_animation_list", "unit_custom_animation_at_frame", "unit_custom_animation_relative_at_frame", "unit_is_playing_custom_animation",
	"object_set_custom_animations_hold_on_last_frame", "object_set_custom_animations_prevent_lipsync_head_movement", "preferred_animation_list_add", "preferred_animation_list_clear", "unit_set_actively_controlled", "unit_get_team_index",
	"unit_aim_without_turning", "unit_set_enterable_by_player", "unit_set_seat_enterable_by_player", "unit_get_enterable_by_player", "unit_only_takes_damage_from_players_team", "unit_enter_vehicle",
	"unit_falling_damage_disable", "unit_in_vehicle_type", "object_get_turret_count", "object_get_turret", "unit_board_vehicle", "unit_set_emotion",
	"unit_set_emotion_by_name", "unit_enable_eye_tracking", "unit_set_integrated_flashlight", "unit_set_dialogue", "unit_enable_vision_mode", "unit_in_vehicle",
	"vehicle_test_seat_list", "vehicle_test_seat_unit", "vehicle_test_seat", "unit_set_prefer_tight_camera_track", "unit_exit_vehicle", "unit_exit_vehicle",
	"unit_set_maximum_vitality", "units_set_maximum_vitality", "unit_set_current_vitality", "units_set_current_vitality", "vehicle_load_magic", "vehicle_unload",
	"unit_set_animation_mode", "magic_melee_attack", "vehicle_riders", "vehicle_driver", "vehicle_gunner", "unit_get_health",
	"unit_get_shield", "unit_get_total_grenade_count", "unit_has_weapon", "unit_has_weapon_readied", "unit_has_any_equipment", "unit_has_equipment",
	"unit_lower_weapon", "unit_raise_weapon", "unit_drop_support_weapon", "unit_spew_action", "unit_force_reload", "animation_stats_dump",
	"unit_animation_forced_seat", "unit_doesnt_drop_items", "unit_impervious", "unit_suspended", "unit_add_equipment", "weapon_hold_trigger",
	"weapon_enable_warthog_chaingun_light", "device_set_never_appears_locked", "device_set_power", "device_get_power", "device_set_position", "device_get_position",
	"device_set_position_immediate", "device_group_get", "device_group_set", "device_group_set_immediate", "device_one_sided_set", "device_ignore_player_set",
	"device_operates_automatically_set", "device_closes_automatically_set", "device_group_change_only_once_more_set", "device_set_position_track", "device_set_overlay_track", "device_animate_position",
	"device_animate_overlay", "cheat_all_powerups", "cheat_all_weapons", "cheat_all_vehicles", "cheat_teleport_to_camera", "cheat_active_camouflage",
	"cheat_active_camouflage_by_player", "cheats_load", "drop_safe", "drop", "drop_variant", "ai_enable",
	"ai_enabled", "ai_grenades", "ai_dialogue_enable", "ai_player_dialogue_enable", "ai_infection_suppress", "ai_fast_and_dumb",
	"ai_dialogue_log_reset", "ai_dialogue_log_dump", "ai_get_object", "ai_get_unit", "ai_get_squad", "ai_get_turret_ai",
	"ai_random_smart_point", "ai_nearest_point", "ai_get_point_count", "ai_point_set_get_point", "ai_place", "ai_place",
	"ai_place_in_vehicle", "ai_cannot_die", "ai_vitality_pinned", "ai_index_from_spawn_formation", "ai_resurrect", "ai_kill",
	"ai_kill_silent", "ai_erase", "ai_erase_all", "ai_disposable", "ai_select", "ai_deselect",
	"ai_set_deaf", "ai_set_blind", "ai_set_weapon_up", "ai_flood_disperse", "ai_magically_see", "ai_magically_see_object",
	"ai_set_active_camo", "ai_suppress_combat", "ai_engineer_explode", "ai_grunt_kamikaze", "ai_migrate", "ai_allegiance",
	"ai_allegiance_remove", "ai_allegiance_break", "ai_braindead", "ai_braindead_by_unit", "ai_disregard", "ai_prefer_target",
	"ai_prefer_target_team", "ai_prefer_target_ai", "ai_set_targeting_group", "ai_set_targeting_group", "ai_teleport_to_starting_location_if_outside_bsp", "ai_teleport_to_spawn_point_if_outside_bsp",
	"ai_teleport", "ai_bring_forward", "ai_migrate_form", "ai_morph", "biped_morph", "ai_renew",
	"ai_force_active", "ai_force_active_by_unit", "ai_playfight", "ai_reconnect", "ai_berserk", "ai_set_team",
	"ai_allow_dormant", "ai_is_attacking", "ai_fighting_count", "ai_living_count", "ai_living_fraction", "ai_in_vehicle_count",
	"ai_body_count", "ai_strength", "ai_swarm_count", "ai_nonswarm_count", "ai_actors", "ai_allegiance_broken",
	"ai_spawn_count", "object_get_ai", "ai_rotate_scenario", "ai_translate_scenario", "unknown", "unknown",
	"unknown", "unknown", "unknown", "unknown", "unknown", "unknown",
	"ai_set_task", "ai_set_objective", "ai_task_status", "ai_set_task_condition", "ai_leadership", "ai_leadership_all",
	"ai_task_count", "ai_reset_objective", "ai_squad_patrol_objective_disallow", "generate_pathfinding", "ai_render_paths_all", "ai_activity_set",
	"ai_activity_abort", "ai_vehicle_get", "ai_vehicle_get_from_starting_location", "ai_vehicle_get_from_spawn_point", "ai_vehicle_get_squad_count", "ai_vehicle_get_from_squad",
	"ai_vehicle_reserve_seat", "ai_vehicle_reserve", "ai_player_get_vehicle_squad", "ai_vehicle_count", "ai_carrying_player", "player_in_vehicle",
	"player_in_vehicle?", "ai_player_any_needs_vehicle", "ai_vehicle_enter", "ai_vehicle_enter", "ai_vehicle_enter_immediate", "ai_vehicle_enter_immediate",
	"ai_enter_squad_vehicles", "ai_vehicle_exit", "ai_vehicle_exit", "vehicle_overturned", "vehicle_flip", "ai_combat_status",
	"flock_start", "flock_stop", "flock_create", "flock_delete", "flock_definition_set", "flock_unperch",
	"drop_ai", "ai_verify_tags", "ai_wall_lean", "ai_play_line", "ai_play_line_at_player", "ai_play_line_on_object",
	"ai_play_line_on_object", "ai_play_line_on_point_set", "ai_play_line_on_point_set", "campaign_metagame_time_pause", "campaign_metagame_award_points", "campaign_metagame_award_primary_skull",
	"campaign_metagame_award_secondary_skull", "campaign_metagame_award_event", "campaign_metagame_enabled", "campaign_survival_enabled", "campaign_is_finished_easy", "campaign_is_finished_normal",
	"campaign_is_finished_heroic", "campaign_is_finished_legendary", "cs_run_command_script", "cs_queue_command_script", "cs_stack_command_script", "vs_reserve",
	"vs_reserve", "vs_cast", "vs_cast", "vs_cast", "vs_cast", "vs_cast",
	"vs_cast", "vs_cast", "vs_role", "vs_abort_on_alert", "vs_abort_on_damage", "vs_abort_on_combat_status",
	"vs_abort_on_vehicle_exit", "cs_abort_on_alert", "cs_abort_on_damage", "cs_abort_on_combat_status", "cs_abort_on_vehicle_exit", "cs_abort_on_alert",
	"vs_abort_on_alert", "cs_abort_on_damage", "vs_abort_on_damage", "cs_abort_on_combat_status", "vs_abort_on_combat_status", "cs_abort_on_vehicle_exit",
	"vs_abort_on_vehicle_exit", "vs_set_cleanup_script", "vs_release", "vs_release_all", "cs_command_script_running", "cs_command_script_queued",
	"cs_number_queued", "cs_moving", "cs_moving", "vs_running_atom", "vs_running_atom_movement", "vs_running_atom_?",
	"vs_running_atom_dialogue", "cs_fly_to", "vs_fly_to", "cs_fly_to", "vs_fly_to", "cs_fly_to_and_face",
	"vs_fly_to_and_face", "cs_fly_to_and_face", "vs_fly_to_and_face", "cs_fly_by", "vs_fly_by", "cs_fly_by",
	"vs_fly_by", "cs_go_to", "vs_go_to", "cs_go_to", "vs_go_to", "cs_go_by",
	"vs_go_by", "cs_go_by", "vs_go_by", "cs_go_to_and_face", "vs_go_to_and_face", "cs_go_to_and_posture",
	"vs_go_to_and_posture", "cs_go_to_nearest", "vs_go_to_nearest", "cs_move_in_direction", "vs_move_in_direction", "cs_move_towards?",
	"vs_move_towards?", "cs_move_towards", "vs_move_towards", "cs_move_towards_point", "vs_move_towards_point", "cs_swarm_to",
	"vs_swarm_to", "cs_swarm_from", "vs_swarm_from", "cs_pause", "vs_pause", "cs_grenade",
	"vs_grenade", "cs_equipment", "vs_equipment", "cs_jump", "vs_jump", "cs_jump_to_point",
	"vs_jump_to_point", "cs_vocalize", "vs_vocalize", "cs_play_sound", "vs_play_sound", "cs_play_sound",
	"vs_play_sound", "cs_play_sound", "vs_play_sound", "cs_action", "vs_action", "cs_action_at_object",
	"vs_action_at_object", "cs_action_at_player", "vs_action_at_player", "cs_custom_animation", "vs_custom_animation", "cs_custom_animation",
	"vs_custom_animation", "cs_custom_animation_death", "vs_custom_animation_death", "cs_custom_animation_death", "vs_custom_animation_death", "cs_custom_animation_loop",
	"vs_custom_animation_loop", "cs_custom_animation_loop", "vs_custom_animation_loop", "cs_play_line", "vs_play_line", "cs_die",
	"vs_die", "cs_deploy_turret", "vs_deploy_turret", "cs_approach", "vs_approach", "cs_approach_player",
	"vs_approach_player", "cs_go_to_vehicle", "vs_go_to_vehicle", "cs_go_to_vehicle", "vs_go_to_vehicle", "cs_set_style",
	"vs_set_style", "cs_force_combat_status", "vs_force_combat_status", "cs_enable_targeting", "vs_enable_targeting", "cs_enable_looking",
	"vs_enable_looking", "cs_enable_moving", "vs_enable_moving", "cs_enable_dialogue", "vs_enable_dialogue", "cs_suppress_activity_termination",
	"vs_suppress_activity_termination", "cs_suppress_dialogue_global?", "vs_suppress_dialogue_global?", "cs_look", "vs_look", "cs_look_player",
	"vs_look_player", "cs_look_object", "vs_look_object", "cs_aim", "vs_aim", "cs_aim_player",
	"vs_aim_player", "cs_aim_object", "vs_aim_object", "cs_face", "vs_face", "cs_face_player",
	"vs_face_player", "cs_face_object", "vs_face_object", "cs_shoot", "vs_shoot", "cs_shoot",
	"vs_shoot", "cs_shoot_point", "vs_shoot_point", "cs_shoot_secondary_trigger", "vs_shoot_secondary_trigger", "cs_lower_weapon",
	"vs_lower_weapon", "cs_vehicle_speed", "vs_vehicle_speed", "cs_vehicle_speed_instantaneous", "vs_vehicle_speed_instantaneous", "cs_vehicle_boost",
	"vs_vehicle_boost", "cs_turn_sharpness?", "vs_turn_sharpness?", "cs_enable_pathfinding_failsafe", "vs_enable_pathfinding_failsafe", "cs_set_pathfinding_radius",
	"vs_set_pathfinding_radius", "cs_ignore_obstacles", "vs_ignore_obstacles", "cs_approach_stop", "vs_approach_stop", "cs_movement_mode",
	"vs_movement_mode", "cs_crouch", "vs_crouch", "cs_crouch", "vs_crouch", "cs_walk",
	"vs_walk", "cs_posture_set", "vs_posture_set", "cs_posture_exit", "vs_posture_exit", "cs_stow",
	"vs_stow", "cs_draw", "vs_draw", "cs_teleport", "vs_teleport", "cs_stop_custom_animation",
	"vs_stop_custom_animation", "cs_stop_sound", "vs_stop_sound", "cs_player_melee", "vs_player_melee", "cs_melee_direction",
	"vs_melee_direction", "cs_smash_direction", "vs_smash_direction", "camera_control", "camera_set", "camera_set_relative",
	"camera_set_animation", "camera_set_animation_relative", "camera_set_animation_with_speed", "camera_set_animation_relative_with_speed", "scripted_camera_set_animation_relative_with_speed_loop", "scripted_camera_set_animation_relative_with_speed_loop_offset",
	"camera_predict_resources_at_frame", "camera_predict_resources_at_point", "camera_set_first_person", "camera_set_cinematic", "camera_set_cinematic_scene", "camera_place_relative",
	"camera_place_worldspace", "camera_time", "camera_set_field_of_view", "cinematic_camera_set_easing_in", "cinematic_camera_set_easing_out", "cinematic_print",
	"camera_set_pan", "camera_pan", "debug_camera_save", "debug_camera_load", "debug_camera_save_name", "debug_camera_load_name",
	"director_debug_camera", "game_difficulty_get", "game_difficulty_get_real", "game_insertion_point_get", "game_insertion_point_set", "pvs_set_object",
	"pvs_set_camera", "pvs_clear", "pvs_reset", "players_unzoom_all", "player_enable_input", "player_disable_movement",
	"player_disable_weapon_pickup", "unknown", "unknown", "player_flashlight_on", "player_active_camouflage_on", "player_camera_control",
	"player_action_test_reset", "player_action_test_jump", "player_action_test_primary_trigger", "player_action_test_grenade_trigger", "player_action_test_zoom", "player_action_test_rotate_weapons",
	"player_action_test_rotate_grenades", "player_action_test_melee", "player_action_test_action", "player_action_test_accept", "player_action_test_cancel", "player_action_test_look_relative_up",
	"player_action_test_look_relative_down", "player_action_test_look_relative_left", "player_action_test_look_relative_right", "player_action_test_look_relative_all_directions", "player_action_test_move_relative_all_directions", "player_action_test_back",
	"player_action_test_dpad_left", "player_action_test_dpad_right", "player_action_test_dpad_up", "player_action_test_dpad_down", "player_action_test_x", "player_action_test_y",
	"player_action_test_left_shoulder", "player_action_test_right_shoulder", "unknown", "unit_action_test_reset", "unit_action_test_grenade_trigger", "unit_action_test_vision_trigger",
	"unit_action_test_rotate_weapons", "unit_action_test_rotate_grenades", "unit_action_test_melee", "unit_action_test_action", "unit_action_test_accept", "unit_action_test_cancel",
	"unit_action_test_look_relative_up", "unit_action_test_look_relative_down", "unit_action_test_look_relative_left", "unit_action_test_look_relative_right", "unit_action_test_look_relative_all_directions", "unit_action_test_move_relative_all_directions",
	"unit_action_test_back", "unit_action_test_dpad_left", "unit_action_test_dpad_right", "unit_action_test_dpad_up", "unit_action_test_dpad_down", "unit_action_test_x",
	"unit_action_test_y", "unit_action_test_left_shoulder", "unit_action_test_right_shoulder", "player0_looking_up", "player0_looking_down", "player0_set_pitch",
	"player1_set_pitch", "player2_set_pitch", "player3_set_pitch", "player_action_test_lookstick_forward", "player_action_test_lookstick_backward", "debug_teleport_player",
	"map_reset", "map_reset_random", "switch_bsp", "switch_zone_set", "current_zone_set", "current_zone_set_fully_active",
	"switch_map_and_zone_set", "crash", "version", "status", "record_movie", "record_movie_distributed",
	"screenshot", "screenshot_debug", "screenshot_big", "screenshot_big_raw", "screenshot_size", "screenshot_simple",
	"screenshot_cubemap", "screenshot_webmap", "cubemap_dynamic_generate", "unknown", "unknown", "unknown",
	"main_menu", "main_halt", "map_name", "unknown", "game_multiplayer", "game_splitscreen",
	"game_difficulty", "game_active_skulls", "game_initial_zone_set", "game_initial_bsp", "game_initial_starting_location", "game_tick_rate",
	"game_start", "game_start_when_ready", "game_start_when_joined", "game_rate", "texture_cache_flush", "geometry_cache_flush",
	"sound_cache_flush", "debug_memory", "debug_memory_by_file", "debug_memory_for_file", "debug_tags", "tags_verify_all",
	"unknown", "unknown", "unknown", "unknown", "profiler_enable", "profiler_set_thread",
	"profiler_set_sort_method", "profiler_set_range", "profiler_set_attribute", "trace_next_frame", "trace_next_frame_to_file", "trace_tick",
	"collision_log_enable", "damage_control_get", "damage_control_set", "ai_lines", "ai_dialogue_break_on_vocalization", "fade_in",
	"fade_out", "cinematic_start", "cinematic_stop", "cinematic_skip_start_internal", "cinematic_skip_stop_internal", "cinematic_show_letterbox",
	"cinematic_show_letterbox_immediate", "cinematic_set_title", "cinematic_set_title_delayed", "cinematic_suppress_bsp_object_creation", "cinematic_subtitle", "cinematic_set",
	"cinematic_set_shot", "cinematic_get_shot", "cinematic_set_early_exit", "cinematic_get_early_exit", "cinematic_set_active_camera", "cinematic_object_create",
	"cinematic_object_create_cinematic_anchor", "cinematic_object_destroy", "cinematic_destroy", "cinematic_clips_initialize_for_shot", "cinematic_clips_destroy", "cinematic_lights_initialize_for_shot",
	"cinematic_lights_destroy", "cinematic_lights_destroy_shot", "cinematic_light_object", "cinematic_light_object_off", "cinematic_lighting_rebuild_all", "unknown",
	"cinematic_lighting_update_sample", "cinematic_object_get", "cinematic_reset", "camera_set_briefing", "cinematic_tag_reference_get_cinematic", "cinematic_tag_reference_get_scene",
	"cinematic_tag_reference_get_effect", "cinematic_tag_reference_get_sound", "cinematic_tag_reference_get_dialogue", "cinematic_tag_reference_get_music", "cinematic_tag_reference_get_animation", "cinematic_scripting_object_coop_flags_valid",
	"cinematic_scripting_fade_out", "cinematic_scripting_create_object", "cinematic_scripting_create_cinematic_object", "cinematic_scripting_start_animation", "cinematic_scripting_destroy_object", "cinematic_scripting_start_effect",
	"cinematic_scripting_start_music", "cinematic_scripting_start_dialogue", "cinematic_scripting_stop_music", "cinematic_scripting_create_and_animate_object", "cinematic_scripting_create_and_animate_cinematic_object", "cinematic_scripting_create_and_animate_object_no_animation",
	"cinematic_scripting_create_and_animate_cinematic_object_no_animation", "cinematic_scripting_play_cortana_effect", "attract_mode_start", "attract_mode_set_seconds", "game_level_advance", "game_won",
	"game_lost", "game_revert", "game_is_cooperative", "game_is_playtest", "game_can_use_flashlights", "game_save_and_quit",
	"game_save_unsafe", "game_insertion_point_unlock", "game_insertion_point_lock", "saved_games_enumerate", "saved_games_delete_campaign_save", "saved_games_save_last_film",
	"saved_games_autosave_free_up_space", "content_catalogue_display_status", "achievement_grant_to_player", "achievement_grant_to_all_players", "achievements_enable", "achievements_skip_validation_checks",
	"debug_spawning_influencers", "debug_spawning_respawn_zones", "debug_spawning_proximity_forbid", "debug_spawning_moving_vehicle", "debug_spawning_weapon_influences", "debug_spawning_dangerous_projectiles",
	"debug_spawning_deployed_equipment", "debug_spawning_proximity_enemy", "debug_spawning_teammates", "debug_spawning_random_influence", "debug_spawning_nominal_weight", "debug_spawning_natural_weight",
	"debug_spawning_target", "debug_spawning_use_history", "debug_initial_spawn_point_objects", "debug_respawn_point_objects", "game_export_variant_settings", "game_engine_event_test_general",
	"game_engine_event_test_flavor", "game_engine_event_test_slayer", "game_engine_event_test_ctf", "game_engine_event_test_oddball", "game_engine_event_test_king", "game_engine_event_test_vip",
	"game_engine_event_test_juggernaut", "game_engine_event_test_territories", "game_engine_event_test_assault", "game_engine_event_test_infection", "core_load", "core_load_name",
	"core_save", "core_save_name", "core_load_game", "core_load_game_name", "core_regular_upload_to_debug_server", "core_set_upload_option",
	"force_debugger_not_present", "force_debugger_always_present", "game_safe_to_save", "game_safe_to_speak", "game_all_quiet", "game_save",
	"game_save_cancel", "game_save_no_timeout", "game_save_immediate", "game_saving", "game_reverted", "unknown",
	"unknown", "sound_set_tag_parameter_unsafe", "sound_impulse_predict", "sound_impulse_trigger", "sound_impulse_start", "sound_impulse_start_cinematic",
	"sound_impulse_start_effect", "sound_impulse_start_with_subtitle", "sound_impulse_language_time", "sound_impulse_stop", "sound_impulse_start_3d", "sound_impulse_mark_as_outro",
	"sound_impulse_start_naked", "sound_looping_predict", "sound_looping_start", "sound_looping_stop", "sound_looping_stop_immediately", "sound_looping_set_scale",
	"sound_looping_set_alternate", "sound_loop_spam", "sound_class_show_channel", "sound_class_debug_sound_start", "debug_sounds_enable", "sound_class_set_gain",
	"sound_class_set_gain_db", "sound_class_enable_ducker", "debug_sound_environment_parameter", "sound_set_global_effect", "sound_set_global_effect_scale", "vehicle_auto_turret",
	"vehicle_hover", "vehicle_count_bipeds_killed", "biped_ragdoll", "water_float_reset", "hud_show_training_text", "hud_set_training_text",
	"hud_enable_training", "player_training_activate_flashlight", "player_training_activate_crouch", "player_training_activate_stealth", "player_training_activate_?", "player_training_activate_jump",
	"player_training_reset", "hud_activate_team_nav_point_flag", "hud_deactivate_team_nav_point_flag", "chud_cortana_suck", "chud_texture_cam", "chud_cortana_set_range_multiplier",
	"play_cortana_effect", "chud_show", "chud_show_weapon_stats", "chud_show_crosshair", "chud_show_shield", "chud_show_grenades",
	"chud_show_messages", "chud_show_motion_sensor", "chud_show_spike_grenades", "chud_show_fire_grenades", "chud_show_compass", "chud_show_stamina",
	"chud_show_energy_meters", "chud_show_consumables", "chud_cinematic_fade", "chud_bonus_round_show_timer", "chud_bonus_round_start_timer", "chud_bonus_round_set_timer",
	"cls", "error_overflow_suppression", "error_geometry_show", "error_geometry_hide", "error_geometry_show_all", "error_geometry_hide_all",
	"error_geometry_list", "player_effect_set_max_translation", "player_effect_set_max_rotation", "player_effect_set_max_rumble", "player_effect_start", "player_effect_stop",
	"player_effect_set_max_translation_for_player", "player_effect_set_max_rotation_for_player", "player_effect_set_max_rumble_for_player", "player_effect_start_for_player", "player_effect_stop_for_player", "time_code_show",
	"time_code_start", "time_code_reset", "script_screen_effect_set_value", "cinematic_screen_effect_start", "cinematic_screen_effect_set_crossfade", "cinematic_screen_effect_set_crossfade",
	"cinematic_screen_effect_stop", "cinematic_set_near_clip_distance", "cinematic_set_far_clip_distance", "render_atmosphere_fog", "atmosphere_fog_override_fade", "motion_blur",
	"render_weather", "render_patchy_fog", "cinematic_set_environment_map_attenuation", "cinematic_set_environment_map_bitmap", "cinematic_reset_environment_map_bitmap", "cinematic_set_environment_map_tint",
	"cinematic_reset_environment_map_tint", "cinematic_layer", "player_has_skills", "player_has_mad_secret_skills", "controller_invert_look", "controller_look_speed",
	"controller_set_look_invert", "controller_get_look_invert", "user_interface_controller_get_last_level_played", "controller_set_look_inverted", "controller_set_vibration_enabled", "controller_set_flight_stick_aircraft_controls",
	"controller_set_auto_center_look", "controller_set_crouch_lock", "controller_set_button_preset", "controller_set_joystick_preset", "controller_set_look_sensitivity", "unknown",
	"unknown", "unknown", "unknown", "unknown", "unknown", "controller_set_single_player_level_completed",
	"controller_set_player_character_type", "unknown", "controller_set_voice_output_setting", "controller_set_voice_mask", "controller_set_subtitle_setting", "unknown",
	"unknown", "unknown", "unknown", "unknown", "controller_set_unsignedin_user", "controller_display_storage_device_selection",
	"font_cache_bitmap_save", "ui_debug_load_main_menu", "ui_debug_text_bounds", "ui_debug_text_font", "ui_debug_show_title_safe_bounds", "ui_debug_element_bounds",
	"ui_memory_dump", "ui_time_scale_step", "xoverlapped_debug_render", "gui_load_screen", "unknown", "unknown",
	"unknown", "unknown", "unknown", "gui_error_resolve", "gui_error_clear", "gui_dialog_show",
	"unknown", "unknown", "unknown", "unknown", "gui_debug_screen_name", "gui_debug_screen_animation",
	"gui_debug_screen_bounds", "gui_debug_screen_rotation", "gui_debug_group_name", "gui_debug_group_animation", "gui_debug_group_bounds", "gui_debug_group_rotation",
	"gui_debug_list_name", "gui_debug_list_animation", "gui_debug_list_bounds", "gui_debug_list_rotation", "gui_debug_list_item_name", "gui_debug_list_item_animation",
	"gui_debug_list_item_bounds", "gui_debug_list_item_rotation", "gui_debug_text_name", "gui_debug_text_animation", "gui_debug_text_bounds", "gui_debug_text_rotation",
	"gui_debug_bitmap_name", "gui_debug_bitmap_animation", "gui_debug_bitmap_bounds", "gui_debug_bitmap_rotation", "gui_debug_music_state", "cc_enable",
	"cc_test", "objectives_clear", "objectives_show_up_to", "objectives_finish_up_to", "objectives_show", "objectives_finish",
	"objectives_unavailable", "objectives_secondary_show", "objectives_secondary_finish", "objectives_secondary_unavailable", "input_suppress_rumble", "input_disable_claw_button_combos",
	"update_remote_camera", "net_build_network_config", "net_build_game_variant", "net_verify_game_variant", "net_load_and_use_game_variant", "net_use_hopper_directory",
	"net_quality_dump", "net_quality_clear", "net_quality_set_connection_badness_history", "net_quality_set_squad_host_badness_history", "net_quality_set_squad_client_badness_history", "net_quality_set_group_host_badness_history",
	"net_quality_set_group_client_badness_history", "net_quality_set_estimated_bandwidth", "net_join_friend", "net_join_squad_to_friend", "net_join_sessionid", "net_join_squad_to_sessionid",
	"net_enable_join_friend_loop", "net_set_maximum_player_count", "unknown", "net_status_filter", "unknown", "unknown",
	"unknown", "unknown", "unknown", "net_test_delegate_leader?", "net_test_map_name", "net_test_variant",
	"net_test_campaign_difficulty", "net_test_reset_objects", "net_test_fatal_error", "net_set_machine_name", "unknown", "unknown",
	"unknown", "unknown", "unknown", "unknown", "unknown", "unknown",
	"unknown", "unknown", "unknown", "event_list_categories", "unknown", "play_bink_movie",
	"play_bink_movie_from_tag", "play_credits", "bink_time", "set_global_doppler_factor", "set_global_mixbin_headroom", "debug_sound_environment_source_parameter",
	"data_mine_set_mission_segment", "data_mine_insert", "data_mine_upload", "data_mine_enable", "data_mine_flush", "data_mine_debug_menu_setting",
	"data_mine_open_debug_menu", "data_mine_set_display_mission_segment", "unknown", "test_memory_allocators", "test_memory_allocators", "display_video_standard",
	"test_xcr_monkey_enable", "test_show_guide_status", "test_show_users_xuids", "test_show_are_users_friends", "test_invite_friend", "unknown",
	"test_auto_get_screens", "test_auto_get_screen_widgets", "test_auto_screen_get_datasources", "test_auto_screen_get_data_columns", "test_auto_screen_get_data", "test_auto_screen_invoke_list_item_by_name",
	"test_auto_screen_invoke_list_item_by_text", "test_auto_screen_invoke_list_item_by_handle", "test_auto_screen_send_button_press", "unknown", "unknown", "unknown",
	"unknown", "unknown", "test_fragment_utility_drive", "unknown", "unknown", "unknown",
	"unknown", "unknown", "unknown", "unknown", "unknown", "unknown",
	"unknown", "unknown", "unknown", "unknown", "unknown", "flag_new",
	"flag_new_at_look", "flags_clear", "flags_default_name", "flags_default_comment", "flags_set_filter", "object_list_children",
	"voice_set_outgoing_channel_count", "voice_set_voice_repeater_peer_index", "voice_set_mute", "net_leaderboard_clear_hopper", "net_leaderboard_clear_global_arbitrated", "net_leaderboard_clear_global_unarbitrated",
	"net_leaderboard_refresh", "dump_loaded_tags", "interpolator_start", "interpolator_start_smooth", "interpolator_stop", "interpolator_restart",
	"interpolator_is_active", "interpolator_is_finished", "interpolator_set_current_value", "interpolator_get_current_value", "interpolator_get_start_value", "interpolator_get_final_value",
	"interpolator_get_current_phase", "interpolator_get_current_time_fraction", "interpolator_get_start_time", "interpolator_get_final_time", "interpolator_evaluate_at", "interpolator_evaluate_at_time_fraction",
	"interpolator_evaluate_at_time", "interpolator_evaluate_at_time_delta", "interpolator_stop_all", "interpolator_restart_all", "interpolator_flip", "set_pc_runtime_language",
	"animation_cache_stats_reset", "cinematic_clone_players_weapon", "cinematic_move_attached_objects", "vehicle_enable_ghost_effects", "set_global_sound_environment", "reset_dsp_image",
	"game_save_cinematic_skip", "cinematic_outro_start", "cinematic_enable_ambience_details", "rasterizer_bloom_override", "rasterizer_bloom_override_reset", "rasterizer_bloom_override_blur_amount",
	"rasterizer_bloom_override_threshold", "rasterizer_bloom_override_brightness", "rasterizer_bloom_override_box_factor", "rasterizer_bloom_override_max_factor", "rasterizer_bloom_override_silver_bullet", "rasterizer_bloom_override_only",
	"rasterizer_bloom_override_high_res", "rasterizer_bloom_override_brightness_alpha", "rasterizer_bloom_override_max_factor_alpha", "cache_block_for_one_frame", "sound_suppress_ambience_update_on_revert", "render_autoexposure_enable",
	"render_exposure_full", "render_exposure_fade_in", "render_exposure_fade_out", "render_exposure", "render_autoexposure_instant", "render_exposure_set_environment_darken",
	"render_depth_of_field_enable", "render_depth_of_field", "render_dof_focus_depth", "render_dof_blur_animate", "render_debug_video_mode", "cinematic_lightmap_shadow_disable",
	"cinematic_lightmap_shadow_enable", "predict_animation", "mp_players_by_team", "mp_active_player_count_by_team", "deterministic_end_game", "mp_game_won",
	"mp_respawn_override_timers", "mp_ai_allegiance", "mp_allegiance", "mp_round_started", "give_medal", "mp_scripts_reset",
	"mp_ai_place", "mp_ai_place", "mp_ai_kill", "mp_ai_kill_silent", "mp_object_create", "mp_object_create_clone",
	"mp_object_create_anew", "mp_object_destroy", "tag_file_set_backend", "mp_object_belongs_to_team", "mp_weapon_belongs_to_team", "mp_debug_goal_object_boundary_geometry",
	"mp_dump_candy_monitor_state", "set_camera_third_person", "get_camera_third_person", "determinism_debug_manager_enable_logging", "determinism_debug_manager_set_trace_flags", "determinism_debug_manager_enable_game_state_checksum",
	"determinism_debug_manager_enable_trace", "determinism_debug_manager_set_consumer_sample_level", "unknown", "saved_film_play", "saved_film_play_last", "saved_film_disable_version_checking",
	"saved_film_toggle_debug_saving", "saved_films_delete_on_level_load", "saved_films_show_timestamp", "saved_film_manager_should_record_film_default", "mover_set_program", "determinism_log_compare_log_files",
	"floating_point_exceptions_enable", "determinism_debug_manager_enable_log_file_comparision_on_oos", "event_logs_snapshot", "tag_reload_force", "tag_unload_force", "tag_load_force",
	"predict_bink_movie", "predict_bink_movie_from_tag", "profiler_dump_history", "camera_set_mode", "camera_set_flying_cam_at_point", "unknown",
	"game_coop_player_count", "player_force_mode", "profiler_output_pulse", "string_id_name", "find", "add_recycling_volume",
	"tag_resources_set_per_frame_publish", "object_recycling_clear_history", "dump_cinematics_script", "global_preferences_clear", "network_storage_set_storage_subdirectory", "network_storage_set_storage_user",
	"status_line_dump", "game_tick_get", "loop_it", "loop_clear", "status_lines_enable", "status_lines_disable",
	"on_target_platform", "profile_activate", "profile_deactivate", "net_game_set_player_standing", "net_get_game_id", "net_test_matchmaking_hopper_list",
	"net_test_matchmaking_hopper_game_list", "net_test_matchmaking_hopper_set_game", "saved_film_set_playback_game_speed", "saved_film_set_pending_playback_game_speed", "noguchis_mystery_tour", "designer_zone_sync",
	"dump_designer_zone", "designer_zone_activate", "designer_zone_deactivate", "object_set_always_active", "saved_film_seek_to_film_tick", "tag_is_active",
	"tag_resources_set_incremental_publish", "dump_active_resources", "object_set_persistent", "display_zone_size_estimates", "report_zone_size_estimates", "net_test_disconnect_squad",
	"net_test_disconnect_group", "net_test_clear_squad_session_parameter", "net_test_clear_group_session_parameter", "net_test_life_cycle_pause", "net_test_life_cycle_display_states", "overlapped_display_task_descriptions",
	"overlapped_task_inject_error", "net_leaderboard_clear_hopper_all_users", "net_leaderboard_clear_global_arbitrated_all_users", "net_leaderboard_clear_global_unarbitrated_all_users", "test_sapien_crash", "unknown",
	"unknown", "unknown", "decorators_split", "bandwidth_profiler_enable", "bandwidth_profiler_set_context", "overlapped_task_pause",
	"net_banhammer_set_controller_cheat_flags", "net_banhammer_set_controller_ban_flags", "net_banhammer_dump_strings", "net_banhammer_dump_repeated_play_list", "net_leaderboard_set_user_stats", "net_leaderboard_set_user_game_stats",
	"net_build_map_variant", "net_verify_map_variant", "async_set_work_delay_milliseconds", "sound_looping_start_with_effect", "tag_resources_set_demand_throttle_to_io", "set_performance_throttle",
	"set_gfx_quality", "get_performance_throttle", "voice_set_headset_boost", "cinematic_zone_activate", "cinematic_zone_deactivate", "cinematic_zone_activate_from_editor",
	"cinematic_zone_deactivate_from_editor", "tiling_current", "unit_limit_lipsync_to_mouth_only", "dump_active_zone_tags", "calculate_tag_prediction", "tag_resources_enable_fast_prediction",
	"unit_start_first_person_custom_animation", "unit_is_playing_custom_first_person_animation", "unit_stop_first_person_custom_animation", "prepare_to_switch_to_zone_set", "cinematic_zone_activate_for_debugging", "unit_play_random_ping",
	"player_control_fade_out_all_input", "player_control_fade_in_all_input", "unit_control_fade_out_all_input", "unit_control_fade_in_all_input", "player_control_lock_gaze", "player_control_unlock_gaze",
	"player_control_scale_all_input", "run_like_dvd", "profiler_auto_core_save", "run_no_hdd", "cinematic_tag_reference_get_bink", "voice_set_force_match_configurations",
	"voice_set_force_hud", "object_set_custom_animation_speed", "scenery_animation_start_at_frame_loop", "film_manager_set_reproduction_mode", "cortana_tag_reference_get_scene", "net_banhammer_force_download",
	"font_set_emergency", "biped_force_ground_fitting_on", "cinematic_set_chud_objective", "chud_show_cinematic_title", "terminal_is_being_read", "terminal_was_accessed",
	"terminal_was_completed", "unit_get_primary_weapon", "dump_cortana_script", "budget_resource_get_animation_graph", "game_award_level_complete_achievements", "budget_resource_get_looping_sound",
	"game_safe_to_respawn", "cortana_effect_kill", "test_create_content_item_slayer", "test_create_content_item_screenshot", "cinematic_scripting_destroy_cortana_effect_cinematic", "ai_migrate_infanty",
	"render_cinematic_motion_blur", "ai_dont_do_avoidance", "cinematic_scripting_clean_up", "ai_erase_inactive", "ai_survival_cleanup", "stop_bink_movie",
	"play_credits_unskippable", "budget_resource_get_sound", "controller_set_single_player_level_unlocked", "physical_memory_dump", "tag_resources_validate_all_pages", "cinematic_set_debug_mode",
	"cinematic_scripting_get_object", "unknown", "gp_integer_get", "gp_integer_set", "gp_boolean_get", "gp_boolean_set",
	"unknown", "unknown", "unknown", "unknown", "unknown", "cinematic_scripting_start_screen_effect",
	"cinematic_scripting_stop_screen_effect", "game_level_prepare", "prepare_game_level", "unknown", "unknown", "unknown",
	"unknown", "unknown", "unknown", "unknown", "unknown", "unknown",
	"unknown", "cinematic_scripting_set_user_input_constraints", "skull_primary_enable", "skull_secondary_enable", "unknown", "unknown",
	"unknown", "survival_mode_respawn_dead_players", "survival_mode_lives_get", "survival_mode_lives_set", "survival_mode_set_get", "survival_mode_set_set",
	"survival_mode_round_get", "survival_mode_round_set", "survival_mode_wave_get", "survival_mode_wave_set", "survival_mode_set_multiplier_get", "survival_mode_set_multiplier_set",
	"survival_mode_bonus_multiplier_get", "survival_mode_bonus_multiplier_set", "unknown", "survival_mode_set_rounds_per_set", "survival_mode_set_waves_per_round", "unknown",
	"survival_mode_event_new", "survival_mode_begin_new_set", "survival_mode_begin_new_round", "survival_mode_begin_new_wave", "survival_mode_award_hero_medal", "campaign_metagame_get_player_score",
	"unknown", "unknown", "player_set_look_training_hack", "device_arg_has_been_touched_by_unit", "unknown", "unknown",
	"unknown", "unknown", "unknown", "unknown", "unknown", "achievement_post_chud_progression",
	"object_set_vision_mode_render_default", "chud_show_navpoint", "unknown", "unknown", "unknown", "unit_confirm_message",
	"unit_confirm_cancel_message", "unit_confirm_y_button", "player_get_kills_by_type", "unit_flashlight_on", "clear_command_buffer_cache_from_script", "sound_looping_resume",
	"chud_bonus_round_set_target_score", "unknown", "unknown", "unknown", "unknown", "unknown",
	"unknown", "unknown", "unknown", "unknown", "unknown", "ui_get_player_model_id",
	"ui_get_music_id", "unknown", "biped_set_armor", "biped_unit_set_armor", "session_advertise_local_network", "ssao_enable",
	"ssao_radius", "ssao_intensity", "ssao_sampleZThreshold", "fxaa_enable", "color_grading_enable", "lightshafts_enable",
	"unknown", "reflections_enable", "reflection_blur_enable", "reflection_multisampling_enabled", "reflection_multisample_passes", "reflection_fxaa_enable",
	"reflection_debug_enable", "reflection_color_bilinear_filter_enable", "game_finished_wait_time_add", "unknown", "background_set", "unknown",
	"unknown", "unknown", "unknown", "mouse_is_inverted", "mouse_invert", "unknown",
	"unknown", "unknown", "unknown", "unknown", "unknown", "cinematic_scripting_start_animation_legacy",
	"cinematic_scripting_create_object_legacy", "cinematic_scripting_create_and_animate_object_legacy", "cinematic_scripting_create_and_animate_object_no_animation_legacy", "cinematic_scripting_create_and_animate_cinematic_object_legacy", "cinematic_scripting_destroy_object_legacy", "mp_wake_script",
	"dew_method_stub", "vehicle_test_seat_list_legacy", "vehicle_test_seat_legacy",
};
