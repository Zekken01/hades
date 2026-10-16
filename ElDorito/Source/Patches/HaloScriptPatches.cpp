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

extern "C" { static s_hs_script_op const *script_ops[1707]; } // 0x1134DDD8
extern "C" { static char const *script_op_names[1707]; } // 0x1134F888

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
			// procedure flags: nofpo

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
			// __int32 *event_count;
			// static c_simulation_hs_script_wake_event_definition hs_wake_script_event_definition; // 0x1134DDD4
			// static c_simulation_hs_sync_global_event_definition hs_sync_global_event_definition; // 0x1134F884

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
	// `anonymous-namespace'::c_simulation_hs_script_wake_event_definition::event_type
	// c_simulation_hs_script_wake_event_definition const *const this;

	return _simulation_event_type_hs_wake_script;
}

_inline char const *c_simulation_hs_script_wake_event_definition::event_name() const // 0x107B0AA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?event_name@c_simulation_hs_script_wake_event_definition@hades_file_local@@EBEPBDXZ");
	// `anonymous-namespace'::c_simulation_hs_script_wake_event_definition::event_name
	// c_simulation_hs_script_wake_event_definition const *const this;

	return "hs_wake_script";
}

_inline long c_simulation_hs_script_wake_event_definition::payload_size() const // 0x107B0AD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?payload_size@c_simulation_hs_script_wake_event_definition@hades_file_local@@EBEJXZ");
	// `anonymous-namespace'::c_simulation_hs_script_wake_event_definition::payload_size
	// c_simulation_hs_script_wake_event_definition const *const this;

	return 2;
}

_inline long c_simulation_hs_script_wake_event_definition::number_of_entity_references() const // 0x107B0B00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?number_of_entity_references@c_simulation_hs_script_wake_event_definition@hades_file_local@@EBEJXZ");
	// `anonymous-namespace'::c_simulation_hs_script_wake_event_definition::number_of_entity_references
	// c_simulation_hs_script_wake_event_definition const *const this;

	return 0;
}

_inline bool c_simulation_hs_script_wake_event_definition::reference_delays_entity_deletion() const // 0x107B0B20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?reference_delays_entity_deletion@c_simulation_hs_script_wake_event_definition@hades_file_local@@EBE_NXZ");
	// `anonymous-namespace'::c_simulation_hs_script_wake_event_definition::reference_delays_entity_deletion
	// c_simulation_hs_script_wake_event_definition const *const this;

	return false;
}

_inline bool c_simulation_hs_script_wake_event_definition::event_can_be_transmitted(c_replication_outgoing_event const *__formal, s_simulation_view_telemetry_data const *__formal1) const // 0x107B0B40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?event_can_be_transmitted@c_simulation_hs_script_wake_event_definition@hades_file_local@@EBE_NPBUc_replication_outgoing_event@@PBUs_simulation_view_telemetry_data@@@Z");
	// `anonymous-namespace'::c_simulation_hs_script_wake_event_definition::event_can_be_transmitted
	// s_simulation_view_telemetry_data const *__formal;

	return true;
}

_inline long c_simulation_hs_script_wake_event_definition::minimum_required_bits(c_replication_outgoing_event const *__formal, s_simulation_view_telemetry_data const *__formal1, long *__formal2) const // 0x107B0B60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?minimum_required_bits@c_simulation_hs_script_wake_event_definition@hades_file_local@@EBEJPBUc_replication_outgoing_event@@PBUs_simulation_view_telemetry_data@@PAJ@Z");
	// `anonymous-namespace'::c_simulation_hs_script_wake_event_definition::minimum_required_bits
	// long *__formal;

	return 0x4A;
}

_inline float c_simulation_hs_script_wake_event_definition::calculate_relevance(c_replication_outgoing_event const *__formal, s_simulation_view_telemetry_data const *__formal1, float __formal2) const // 0x107B0B90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?calculate_relevance@c_simulation_hs_script_wake_event_definition@hades_file_local@@EBEMPBUc_replication_outgoing_event@@PBUs_simulation_view_telemetry_data@@M@Z");
	// `anonymous-namespace'::c_simulation_hs_script_wake_event_definition::calculate_relevance
	// float __formal;

	return 0.0f;
}

_inline void c_simulation_hs_script_wake_event_definition::write_description_to_string(c_replication_outgoing_event const *__formal, s_simulation_view_telemetry_data const *__formal1, float __formal2, long __formal3, char *__formal4) const // 0x107B0BB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?write_description_to_string@c_simulation_hs_script_wake_event_definition@hades_file_local@@EBEXPBUc_replication_outgoing_event@@PBUs_simulation_view_telemetry_data@@MJPAD@Z");
	// the original is empty
	// `anonymous-namespace'::c_simulation_hs_script_wake_event_definition::write_description_to_string
	// char *__formal;
}

_inline simulation_event_definition_return_value *c_simulation_hs_script_wake_event_definition::gather_requirements_data(simulation_event_definition_return_value *data, c_replication_outgoing_event const *__formal, s_simulation_view_telemetry_data const *__formal1) const // 0x107B0BD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?gather_requirements_data@c_simulation_hs_script_wake_event_definition@hades_file_local@@EBEPAUsimulation_event_definition_return_value@@PAU3@PBUc_replication_outgoing_event@@PBUs_simulation_view_telemetry_data@@@Z");
	// `anonymous-namespace'::c_simulation_hs_script_wake_event_definition::gather_requirements_data
	// s_simulation_view_telemetry_data const *__formal;

	data->value = data->value & 0xFFFFFF01 | 0x101;
	data->value = data->value & 0x1FF | 0x9400;
	return data;
}

_inline void c_simulation_hs_script_wake_event_definition::event_payload_encode(long payload_size, void const *payload, c_bitstream *packet, bool predicted) const // 0x107B0C30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?event_payload_encode@c_simulation_hs_script_wake_event_definition@hades_file_local@@EBEXJPBXPAVc_bitstream@@_N@Z");
	// `anonymous-namespace'::c_simulation_hs_script_wake_event_definition::event_payload_encode
	// bool predicted;
	// s_simulation_hs_script_wake_event_data *data;
	// Blam::BitStream *packet_impl;

	Blam::BitStream *stream = (Blam::BitStream *)packet;
	short const *value = (short const *)payload;
	stream->Write<short>(*value, 10);
}

_inline bool c_simulation_hs_script_wake_event_definition::event_payload_decode(long payload_size, void *payload, c_bitstream *packet, bool predicted) const // 0x107B0CA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?event_payload_decode@c_simulation_hs_script_wake_event_definition@hades_file_local@@EBE_NJPAXPAVc_bitstream@@_N@Z");
	// `anonymous-namespace'::c_simulation_hs_script_wake_event_definition::event_payload_decode
	// bool predicted;
	// s_simulation_hs_script_wake_event_data *data;
	// Blam::BitStream *packet_impl;

	Blam::BitStream *packet_impl = (Blam::BitStream *)packet;
	s_simulation_hs_script_wake_event_data *data = (s_simulation_hs_script_wake_event_data *)payload;

	data->script_index = packet_impl->Read<short>(10);
	return true;
}

_inline void c_simulation_hs_script_wake_event_definition::prepare_event_data_for_gameworld(long payload_size, void *payload) // 0x107B0D10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?prepare_event_data_for_gameworld@c_simulation_hs_script_wake_event_definition@hades_file_local@@EAEXJPAX@Z");
	// the original is empty
	// `anonymous-namespace'::c_simulation_hs_script_wake_event_definition::prepare_event_data_for_gameworld
	// void *payload;
}

_inline bool c_simulation_hs_script_wake_event_definition::apply_game_event(long reference_gamestate_count, long const *gamestate_indices, long payload_size, void const *payload) // 0x107B0D30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?apply_game_event@c_simulation_hs_script_wake_event_definition@hades_file_local@@EAE_NJPBJJPBX@Z");
	// `anonymous-namespace'::c_simulation_hs_script_wake_event_definition::apply_game_event
	// void const *payload;
	// long thread_index;
	// s_simulation_hs_script_wake_event_data *data;
	// s_scenario const *scnr;
	// function call : long (*const)(short)
	// function call : void (*const)(short)

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
	// `anonymous-namespace'::c_simulation_hs_sync_global_event_definition::event_type
	// c_simulation_hs_sync_global_event_definition const *const this;

	return _simulation_event_type_hs_sync_global;
}

_inline char const *c_simulation_hs_sync_global_event_definition::event_name() const // 0x107B0E30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?event_name@c_simulation_hs_sync_global_event_definition@hades_file_local@@EBEPBDXZ");
	// `anonymous-namespace'::c_simulation_hs_sync_global_event_definition::event_name
	// c_simulation_hs_sync_global_event_definition const *const this;

	return "hs_sync_global";
}

_inline long c_simulation_hs_sync_global_event_definition::payload_size() const // 0x107B0E60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?payload_size@c_simulation_hs_sync_global_event_definition@hades_file_local@@EBEJXZ");
	// `anonymous-namespace'::c_simulation_hs_sync_global_event_definition::payload_size
	// c_simulation_hs_sync_global_event_definition const *const this;

	return 8;
}

_inline long c_simulation_hs_sync_global_event_definition::number_of_entity_references() const // 0x107B0E90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?number_of_entity_references@c_simulation_hs_sync_global_event_definition@hades_file_local@@EBEJXZ");
	// `anonymous-namespace'::c_simulation_hs_sync_global_event_definition::number_of_entity_references
	// c_simulation_hs_sync_global_event_definition const *const this;

	return 0;
}

_inline bool c_simulation_hs_sync_global_event_definition::reference_delays_entity_deletion() const // 0x107B0EB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?reference_delays_entity_deletion@c_simulation_hs_sync_global_event_definition@hades_file_local@@EBE_NXZ");
	// `anonymous-namespace'::c_simulation_hs_sync_global_event_definition::reference_delays_entity_deletion
	// c_simulation_hs_sync_global_event_definition const *const this;

	return false;
}

_inline bool c_simulation_hs_sync_global_event_definition::event_can_be_transmitted(c_replication_outgoing_event const *__formal, s_simulation_view_telemetry_data const *__formal1) const // 0x107B0ED0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?event_can_be_transmitted@c_simulation_hs_sync_global_event_definition@hades_file_local@@EBE_NPBUc_replication_outgoing_event@@PBUs_simulation_view_telemetry_data@@@Z");
	// `anonymous-namespace'::c_simulation_hs_sync_global_event_definition::event_can_be_transmitted
	// s_simulation_view_telemetry_data const *__formal;

	return true;
}

_inline long c_simulation_hs_sync_global_event_definition::minimum_required_bits(c_replication_outgoing_event const *__formal, s_simulation_view_telemetry_data const *__formal1, long *__formal2) const // 0x107B0EF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?minimum_required_bits@c_simulation_hs_sync_global_event_definition@hades_file_local@@EBEJPBUc_replication_outgoing_event@@PBUs_simulation_view_telemetry_data@@PAJ@Z");
	// `anonymous-namespace'::c_simulation_hs_sync_global_event_definition::minimum_required_bits
	// long *__formal;

	return 0x4A;
}

_inline float c_simulation_hs_sync_global_event_definition::calculate_relevance(c_replication_outgoing_event const *__formal, s_simulation_view_telemetry_data const *__formal1, float __formal2) const // 0x107B0F20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?calculate_relevance@c_simulation_hs_sync_global_event_definition@hades_file_local@@EBEMPBUc_replication_outgoing_event@@PBUs_simulation_view_telemetry_data@@M@Z");
	// `anonymous-namespace'::c_simulation_hs_sync_global_event_definition::calculate_relevance
	// float __formal;

	return 0.0f;
}

_inline void c_simulation_hs_sync_global_event_definition::write_description_to_string(c_replication_outgoing_event const *__formal, s_simulation_view_telemetry_data const *__formal1, float __formal2, long __formal3, char *__formal4) const // 0x107B0F40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?write_description_to_string@c_simulation_hs_sync_global_event_definition@hades_file_local@@EBEXPBUc_replication_outgoing_event@@PBUs_simulation_view_telemetry_data@@MJPAD@Z");
	// the original is empty
	// `anonymous-namespace'::c_simulation_hs_sync_global_event_definition::write_description_to_string
	// char *__formal;
}

_inline simulation_event_definition_return_value *c_simulation_hs_sync_global_event_definition::gather_requirements_data(simulation_event_definition_return_value *data, c_replication_outgoing_event const *__formal, s_simulation_view_telemetry_data const *__formal1) const // 0x107B0F60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?gather_requirements_data@c_simulation_hs_sync_global_event_definition@hades_file_local@@EBEPAUsimulation_event_definition_return_value@@PAU3@PBUc_replication_outgoing_event@@PBUs_simulation_view_telemetry_data@@@Z");
	// `anonymous-namespace'::c_simulation_hs_sync_global_event_definition::gather_requirements_data
	// s_simulation_view_telemetry_data const *__formal;

	data->value = (data->value & 0xFFFFFF01) | 0x101;
	data->value = (data->value & 0x1FF) | 0x9400;
	return data;
}

_inline void c_simulation_hs_sync_global_event_definition::event_payload_encode(long payload_size, void const *payload, c_bitstream *packet, bool predicted) const // 0x107B0FC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?event_payload_encode@c_simulation_hs_sync_global_event_definition@hades_file_local@@EBEXJPBXPAVc_bitstream@@_N@Z");
	// `anonymous-namespace'::c_simulation_hs_sync_global_event_definition::event_payload_encode
	// bool predicted;
	// s_simulation_hs_sync_global_event_data *data;
	// Blam::BitStream *packet_impl;

	Blam::BitStream *packet_impl = (Blam::BitStream *)packet;
	s_simulation_hs_sync_global_event_data const *data = (s_simulation_hs_sync_global_event_data const *)payload;

	packet_impl->Write<long>(data->global_index, 32);
	packet_impl->Write<long>(data->value, 32);
}

_inline bool c_simulation_hs_sync_global_event_definition::event_payload_decode(long payload_size, void *payload, c_bitstream *packet, bool predicted) const // 0x107B1040
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?event_payload_decode@c_simulation_hs_sync_global_event_definition@hades_file_local@@EBE_NJPAXPAVc_bitstream@@_N@Z");
	// `anonymous-namespace'::c_simulation_hs_sync_global_event_definition::event_payload_decode
	// bool predicted;
	// s_simulation_hs_sync_global_event_data *data;
	// Blam::BitStream *packet_impl;

	Blam::BitStream *packet_impl = (Blam::BitStream *)packet;
	s_simulation_hs_sync_global_event_data *data = (s_simulation_hs_sync_global_event_data *)payload;

	data->global_index = packet_impl->Read<long>(32);
	data->value = packet_impl->Read<long>(32);
	return true;
}

_inline void c_simulation_hs_sync_global_event_definition::prepare_event_data_for_gameworld(long payload_size, void *payload) // 0x107B10C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?prepare_event_data_for_gameworld@c_simulation_hs_sync_global_event_definition@hades_file_local@@EAEXJPAX@Z");
	// the original is empty
	// `anonymous-namespace'::c_simulation_hs_sync_global_event_definition::prepare_event_data_for_gameworld
	// void *payload;
}

_inline bool c_simulation_hs_sync_global_event_definition::apply_game_event(long reference_gamestate_count, long const *gamestate_indices, long payload_size, void const *payload) // 0x107B10E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?apply_game_event@c_simulation_hs_sync_global_event_definition@hades_file_local@@EAE_NJPBJJPBX@Z");
	// `anonymous-namespace'::c_simulation_hs_sync_global_event_definition::apply_game_event
	// long reference_gamestate_count;
	// long const *gamestate_indices;
	// long payload_size;
	// void const *payload;
	// s_simulation_hs_sync_global_event_data *data;
	// s_hs_global_runtime *global;
	// char value_str[256];
	// e_hs_type global_type;
		// s_scenario const *scnr;
		// long const string_offset;
	// function call : void (*const)(long)

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

	((void (*const)(long))0x596C10)(data->global_index);
	char value_str[256];
	hs_get_value_string(global_type, global->value, value_str);
	Console::WriteLine(std::format("received hs global \"{}\", value: {}", hs_global_get_name(data->global_index), value_str));
	return true;
}

void simulation_action_hs_sync_global(short global_index, unsigned short player_mask) // 0x107B8DE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?simulation_action_hs_sync_global@@YAXFG@Z");
	// `anonymous-namespace'::simulation_action_hs_sync_global
	// static ...; // 0x107B8F88
	// static ...; // 0x107B8F80
	// short global_index;
	// unsigned short player_mask;
	// s_simulation_hs_sync_global_event_data data;
	// s_hs_global_runtime *global;
	// long value;
		// long string_offset;
	// function call : bool (*const)()
	// function call : void (*const)(e_simulation_event_type, long, long *, long, long, void const *)

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
	// `anonymous-namespace'::simulation_action_hs_script_wake
	// static ...; // 0x107B8DAC
	// static ...; // 0x107B8DA0
	// static ...; // 0x107B8D98
	// short script_index;
	// bool (*const game_is_distributed)();
		// s_simulation_hs_script_wake_event_data data;
	// function call : bool (*const)()
	// function call : void (*const)(e_simulation_event_type, long, long *, long, long, void const *)

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
	// `anonymous-namespace'::hs_mp_wake_script_evaluate
	// char a3;
	// s_hs_syntax_node *node;
	// s_scenario *scnr;
	// short script_index;
	// s_hs_thread *thread;
		// long thread_index;
	// function call : s_hs_syntax_node *(*const)(long)
	// function call : s_hs_syntax_node *(*const)(long)
	// function call : s_hs_syntax_node *(*const)(long)
	// function call : bool (*const)()
	// function call : long (*const)(short)
	// function call : void (*const)(short)
	// function call : void (*const)(long, hs_value)

	s_hs_thread *thread = tls_getd().hs_thread_deterministic_data->try_and_get(thread_index);
	s_hs_syntax_node *node = ((s_hs_syntax_node *(*const)(long))0x598a10)(*(long *)&thread->stack[thread->stack_offset]);
	node = ((s_hs_syntax_node *(*const)(long))0x598a10)(*(long *)node->data);
	node = ((s_hs_syntax_node *(*const)(long))0x598a10)(node->next_expression_index);
	short script_index = *(short *)node->data;
	s_scenario *scnr = global_scenario_get();
	if (script_index < 0 || script_index >= scnr->scripts.count)
	{
		return;
	}

	if (((bool (*const)())0x5319c0)())
	{
		long thread_index = ((long (*const)(short))0x596130)(script_index);
		if (thread_index != -1)
		{
			((void (*const)(short))0x599170)((short)thread_index);
		}

		simulation_action_hs_script_wake(script_index);
	}

	((void (*const)(long, hs_value))0x5974e0)(thread_index, hs_value::from_long(0));
}

void hs_mp_sync_global_evaluate(short op, __int32 thread_index, char a3) // 0x107B7FE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_mp_sync_global_evaluate@@YAXFHD@Z");
	// `anonymous-namespace'::hs_mp_sync_global_evaluate
	// char a3;
	// s_hs_syntax_node *node;
	// s_hs_thread *thread;
		// short global_index;
	// function call : s_hs_syntax_node *(*const)(long)
	// function call : s_hs_syntax_node *(*const)(long)
	// function call : s_hs_syntax_node *(*const)(long)
	// function call : bool (*const)()
	// function call : void (*const)(long, hs_value)

	s_hs_thread *thread = tls_getd().hs_thread_deterministic_data->try_and_get(thread_index);
	s_hs_syntax_node *node = ((s_hs_syntax_node *(*const)(long))0x598a10)(*(long *)&thread->stack[thread->stack_offset]);
	node = ((s_hs_syntax_node *(*const)(long))0x598a10)(*(long *)node->data);
	node = ((s_hs_syntax_node *(*const)(long))0x598a10)(node->next_expression_index);
	if (!(static_cast<unsigned short>(node->flags) & 4))
	{
		return;
	}

	if (((bool (*const)())0x5319c0)())
	{
		short global_index = *(short *)node->data;
		Server::HsGlobalSync::RegisterGlobal(global_index);
		Console::WriteLine(std::format("registered global \"{}\" for synchronization", hs_global_get_name(global_index)));
	}

	((void (*const)(long, hs_value))0x5974e0)(thread_index, hs_value::from_long(0));
}

void hs_cinematic_scripting_start_animation_legacy(long cine_index, long scene_index, long cine_object_index, long object_index, unsigned long animation_id) // 0x107B6A10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_cinematic_scripting_start_animation_legacy@@YAXJJJJK@Z");
	// `anonymous-namespace'::hs_cinematic_scripting_start_animation_legacy
	// unsigned long animation_id;
	// long (*const cinematic_object_get_internal)(long);
	// void (*const scenery_animation_start_relative)(long, long, unsigned long, long);
	// void (*const unit_limit_lipsync_to_mouth_only)(long, bool);
	// s_cinematic_scene_definition *(*const scenario_get_cinematic_scene)(long, long);
	// void *(*const c_animation_manager__get_mixing_board_facial_animation_channel)(void *);
	// s_cinematic_scene_definition const *cinematic_scene;
	// void (*const custom_animation_relative)(long, long, unsigned long, char, long);
		// s_cinematic_scene_object const *cinematic_object;
			// s_object_data *object_data;
			// __int32 id_bit;
				// long object;
					// long animation_data;
						// long anim_channel;
	// function call : s_cinematic_scene_definition *(*const)(long, long)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : long (*const)(long)
	// function call : void (*const)(long, long, unsigned long, char, long)
	// function call : void (*const)(long, bool)
	// function call : void *(*const)(void *)
	// function call : long (*const)(long)
	// function call : void (*const)(long, long, unsigned long, long)

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
	// `anonymous-namespace'::hs_cinematic_scripting_start_animation_legacy_evaluate
	// char a3;
	// long const args;
	// function call : hs_value *(*const)(short, long, bool)
	// function call : void (*const)(long, hs_value)

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
	// `anonymous-namespace'::hs_cinematic_scripting_create_object_legacy
	// short object_name_index;
	// void (*const object_hide)(long, bool);
	// long (*const object_index_from_name_index)(short);
	// long (*const object_new)(short, bool, bool);
	// bool (*const cinematic_index_is_valid)(__int32);
	// s_cinematic_scene_definition *(*const scenario_get_cinematic_scene)(long, long);
	// s_cinematic_scene_definition const *cinematic_scene;
	// void (*const object_set_always_active)(long, bool);
	// long (*const object_create_anew)(short);
		// s_cinematic_scene_object const *cinematic_object;
			// long object_index;
	// function call : s_cinematic_scene_definition *(*const)(long, long)
	// function call : bool (*const)(__int32)
	// function call : long (*const)(short)
	// function call : long (*const)(short, bool, bool)
	// function call : long (*const)(short)
	// function call : long (*const)(short)
	// function call : void (*const)(long, bool)
	// function call : void (*const)(long, bool)

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
	// `anonymous-namespace'::hs_cinematic_scripting_create_object_legacy_evaluate
	// char a3;
	// long const args;
	// function call : hs_value *(*const)(short, long, bool)
	// function call : void (*const)(long, hs_value)

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
	// `anonymous-namespace'::cinematic_scripting_cinematic_object_get_representation_index
	// long cine_object_index;
	// bool (*const cinematic_index_is_valid)(__int32);
	// s_cinematic_scene_definition *(*const scenario_get_cinematic_scene)(long, long);
	// s_cinematic_scene_definition *cinematic_scene;
		// s_cinematic_scene_object *cinematic_object;
			// __int32 campaign_player_representation_index;
	// function call : s_cinematic_scene_definition *(*const)(long, long)
	// function call : bool (*const)(__int32)

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
	// `anonymous-namespace'::get_campaign_player_character_type_index
	// long player_session_index;
	// s_player_datum *player;
	// s_game_globals *matg;
	// long player_datum_index;
		// s_scenario *scnr;
		// Blam::Network::Session *session;
			// __int32 player_sidx;
			// unsigned long name;
				// __int32 i;

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
	// `anonymous-namespace'::cinematic_scripting_create_cinematic_object_hook
	// long cine_object_index;
	// long (*const cinematic_object_get_internal)(s_cinematic_scene_object const *);
	// bool (*const cinematic_index_is_valid)(__int32);
	// s_cinematic_scene_definition *(*const scenario_get_cinematic_scene)(long, long);
	// s_cinematic_scene_definition *cinematic_scene;
	// void (*const cinematic_scripting_create_cinematic_object)(long, long, long);
		// s_cinematic_scene_object *cinematic_object;
			// long campaign_player_representation_index;
			// long object;
			// long character_type_index;
				// s_game_globals *matg;
					// long character_rep_index;
				// s_player_datum *player;
				// long player_datum_index;
	// function call : s_cinematic_scene_definition *(*const)(long, long)
	// function call : bool (*const)(__int32)
	// function call : void (*const)(long, long, long)
	// function call : long (*const)(s_cinematic_scene_object const *)

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
	// `anonymous-namespace'::hs_cinematic_scripting_create_and_animate_object_legacy
	// bool a5;
	// long (*const cinematic_object_get_internal)(s_cinematic_scene_object const *);
	// long (*const object_index_from_name_index)(short);
	// bool (*const cinematic_index_is_valid)(__int32);
	// s_cinematic_scene_definition *(*const scenario_get_cinematic_scene)(long, long);
	// void (*const render_object_invalidate_render_state)(long);
	// bool (*const cinematic_scripting_object_coop_flags_valid)(long, long, long);
	// s_cinematic_scene_definition *cinematic_scene;
	// void (*const object_set_shadowless)(long, bool);
	// void (*const cinematic_scripting_create_cinematic_object)(long, long, long);
	// bool (*const cinematic_scripting_should_reset_object_lighting)(s_cinematic_scene_definition const *);
		// s_cinematic_scene_object *cinematic_object;
			// long campaign_player_representation_index;
			// long object;
			// long character_type_index;
				// s_game_globals *matg;
					// long character_rep_index;
				// s_player_datum *player;
				// long player_datum_index;
	// function call : s_cinematic_scene_definition *(*const)(long, long)
	// function call : bool (*const)(__int32)
	// function call : bool (*const)(long, long, long)
	// function call : long (*const)(short)
	// function call : void (*const)(long, long, long)
	// function call : long (*const)(s_cinematic_scene_object const *)
	// function call : void (*const)(long, bool)
	// function call : bool (*const)(s_cinematic_scene_definition const *)
	// function call : void (*const)(long)

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
	// `anonymous-namespace'::hs_cinematic_scripting_create_and_animate_object_legacy_evaluate
	// char a3;
	// long const args;
	// function call : hs_value *(*const)(short, long, bool)
	// function call : void (*const)(long, hs_value)

	long const args = (long)((hs_value const *(__cdecl *)(unsigned short, long, bool))0x5972f0)(a1, a2, a3);
	if (args)
	{
		hs_cinematic_scripting_create_and_animate_object_legacy(*(long *)args, *(long *)(args + 4), *(long *)(args + 8), *(unsigned short *)(args + 12), *(long *)(args + 16), *(unsigned long *)(args + 20), *(bool *)(args + 24));
		((void(__cdecl *const)(long, hs_value))0x5974e0)(a2, hs_value::from_long(0));
	}
}

void hs_cinematic_scripting_create_and_animate_object_no_animation_legacy(long cine_index, long scene_index, long cine_object_index, short object_name_index, long object_index, bool a5) // 0x107B61C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_cinematic_scripting_create_and_animate_object_no_animation_legacy@@YAXJJJFJ_N@Z");
	// `anonymous-namespace'::hs_cinematic_scripting_create_and_animate_object_no_animation_legacy
	// bool a5;

	hs_cinematic_scripting_create_and_animate_object_legacy(cine_index, scene_index, cine_object_index, object_name_index, object_index, 0, a5);
}

void hs_cinematic_scripting_create_and_animate_object_no_animation_legacy_evaluate(short a1, __int32 a2, char a3) // 0x107B6230
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_cinematic_scripting_create_and_animate_object_no_animation_legacy_evaluate@@YAXFHD@Z");
	// `anonymous-namespace'::hs_cinematic_scripting_create_and_animate_object_no_animation_legacy_evaluate
	// char a3;
	// long const args;
	// function call : hs_value *(*const)(short, long, bool)
	// function call : void (*const)(long, hs_value)

	long const args = (long)((hs_value const *(__cdecl *)(unsigned short, long, bool))0x5972f0)(a1, a2, a3);
	if (args)
	{
		hs_cinematic_scripting_create_and_animate_object_no_animation_legacy(*(long *)args, *(long *)(args + 4), *(long *)(args + 8), *(unsigned short *)(args + 12), *(long *)(args + 16), *(bool *)(args + 20));
		((void(__cdecl *const)(long, hs_value))0x5974e0)(a2, hs_value::from_long(0));
	}
}

void hs_cinematic_scripting_create_and_animate_cinematic_object_legacy(long cine_index, long scene_index, long cine_object_index, long object_index, unsigned long animation_id, bool a5) // 0x107B5970
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_cinematic_scripting_create_and_animate_cinematic_object_legacy@@YAXJJJJK_N@Z");
	// `anonymous-namespace'::hs_cinematic_scripting_create_and_animate_cinematic_object_legacy
	// bool a5;

	hs_cinematic_scripting_create_and_animate_object_legacy(cine_index, scene_index, cine_object_index, -1, object_index, animation_id, a5);
}

void hs_cinematic_scripting_create_and_animate_cinematic_object_legacy_evaluate(short a1, __int32 a2, char a3) // 0x107B59E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_cinematic_scripting_create_and_animate_cinematic_object_legacy_evaluate@@YAXFHD@Z");
	// `anonymous-namespace'::hs_cinematic_scripting_create_and_animate_cinematic_object_legacy_evaluate
	// char a3;
	// long const args;
	// function call : hs_value *(*const)(short, long, bool)
	// function call : void (*const)(long, hs_value)

	long const args = (long)((hs_value const *(__cdecl *)(unsigned short, long, bool))0x5972f0)(a1, a2, a3);
	if (args)
	{
		hs_cinematic_scripting_create_and_animate_cinematic_object_legacy(*(long *)args, *(long *)(args + 4), *(long *)(args + 8), *(long *)(args + 12), *(unsigned long *)(args + 16), *(bool *)(args + 20));
		((void(__cdecl *const)(long, hs_value))0x5974e0)(a2, hs_value::from_long(0));
	}
}

void hs_cinematic_scripting_destroy_object_legacy(long cine_index, long scene_index, long cine_object_index, long object_index) // 0x107B66B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_cinematic_scripting_destroy_object_legacy@@YAXJJJJ@Z");
	// `anonymous-namespace'::hs_cinematic_scripting_destroy_object_legacy
	// long object_index;
	// void (*const object_hide)(long, bool);
	// void (*const unit_limit_lipsync_to_mouth_only)(long, bool);
	// s_cinematic_scene_definition *(*const scenario_get_cinematic_scene)(long, long);
	// void (*const unit_stop_custom_animation)(long);
	// s_cinematic_scene_definition const *cinematic_scene;
	// void (*const object_set_always_active)(long, bool);
	// void (*const object_cinematic_visibility)(long, bool);
		// s_cinematic_scene_object const *cinematic_object;
			// s_object_data *object_data;
			// __int32 id_bit;
	// function call : s_cinematic_scene_definition *(*const)(long, long)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void (*const)(long, bool)
	// function call : void (*const)(long, bool)
	// function call : void (*const)(long, bool)
	// function call : void (*const)(long)
	// function call : void (*const)(long, bool)

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
	// `anonymous-namespace'::hs_cinematic_scripting_destroy_object_legacy_evaluate
	// char a3;
	// long const args;
	// function call : hs_value *(*const)(short, long, bool)
	// function call : void (*const)(long, hs_value)

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
	// `anonymous-namespace'::hs_camera_set_evaluate
	// static ...; // 0x107B5752
	// static ...; // 0x107B5740
	// static ...; // 0x107B573C
	// static ...; // 0x107B5739
	// static ...; // 0x107B5735
	// static ...; // 0x107B5728
	// static ...; // 0x107B5712
	// static ...; // 0x107B56FA
	// static ...; // 0x107B56E3
	// static ...; // 0x107B56CC
	// static ...; // 0x107B56B3
	// static ...; // 0x107B569C
	// static ...; // 0x107B55F4
	// static ...; // 0x107B55EC
	// short a1;
	// __int32 a2;
	// char a3;
	// void (*const object_get_orientation)(long, real_vector3d *, real_vector3d *);
	// real_euler_angles3d *(*const euler_angles3d_from_vectors3d)(real_euler_angles3d *, real_vector3d const &, real_vector3d const &);
	// long const args;
	// void (*const sub501040)(real_vector3d *, real_vector3d *, real_vector3d *);
	// void (*const matrix4x3_from_point_and_quaternion)(real_matrix4x3 *, real_point3d const *, real_quaternion *);
	// void (*const sub4FA020)(real_quaternion *, real_euler_angles3d *);
	// void (*const camera_control)(__int32);
	// void (*const camera_update_scripted)(__int32, real_vector3d *, real_vector3d *, float, short, unsigned __int32);
		// s_scenario *const scnr;
			// short camera;
			// c_tag_block<s_scenario_cutscene_camera_point> cutscenes;
				// real_vector3d v36;
				// real_vector3d a2a;
				// real_vector3d cutscene_camera_position;
				// real_vector3d cutscene_camera_vector;
				// real_quaternion orientation;
				// short ticksArg;
				// real_point3d transformed_point;
				// float ticks;
				// s_scenario_cutscene_camera_point &cutscene_camera;
				// bool isPodiumHack;
				// real_matrix4x3 cutscene_camera_matrix;
				// real_vector3d a3;
					// long s_PodiumObjectIndex;
					// s_game_globals *matg;
					// s_object_data *scenObject;
					// s_scenario_cutscene_camera_point podiumCamera;
						// real_matrix4x3 podiumObjectTransform;
						// real_euler_angles3d podiumObjectOrientation;
						// void *podium;
							// s_podium_settings *podium_settings;
								// float &dword_471A4A0;
								// real_point3d podium_position_offset;
								// float &dword_18ECE00;
								// real_vector3d podium_rotation_offset;
	// function call : hs_value *(*const)(short, long, bool)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : real_matrix4x3 *(*const)(long, real_matrix4x3 *)
	// function call : void (*const)(real_quaternion *, real_euler_angles3d *)
	// function call : void (*const)(real_matrix4x3 *, real_point3d const *, real_quaternion *)
	// function call : void *(*const)(unsigned long, long)
	// function call : void (*const)(real_vector3d *, real_vector3d *, real_vector3d *)
	// function call : real_euler_angles3d *(*const)(real_euler_angles3d *, real_vector3d const &, real_vector3d const &)
	// function call : void (*const)(__int32, real_vector3d *, real_vector3d *, float, short, unsigned __int32)
	// function call : void (*const)(long, hs_value)
	// function call : void (*const)(__int32, real_vector3d *, real_vector3d *, float, short, unsigned __int32)
	// function call : void (*const)(long, hs_value)

	void (*const camera_control)(__int32) = reinterpret_cast<void (*)(__int32)>(0x592320);
	void (*const matrix4x3_from_point_and_quaternion)(real_matrix4x3 *, real_point3d const *, real_quaternion *) = reinterpret_cast<void (*)(real_matrix4x3 *, real_point3d const *, real_quaternion *)>(0x5B1F30);
	real_euler_angles3d * (*const euler_angles3d_from_vectors3d)(real_euler_angles3d *, real_vector3d const &, real_vector3d const &) = reinterpret_cast<real_euler_angles3d * (*)(real_euler_angles3d *, real_vector3d const &, real_vector3d const &)>(0x4F1490);
	void (*const camera_update_scripted)(__int32, real_vector3d *, real_vector3d *, float, short, unsigned __int32) = reinterpret_cast<void (*)(__int32, real_vector3d *, real_vector3d *, float, short, unsigned __int32)>(0x72DD70);
	void (*const object_get_orientation)(long, real_vector3d *, real_vector3d *) = reinterpret_cast<void (*)(long, real_vector3d *, real_vector3d *)>(0xB2E490);
	long const *args = (long const *)((hs_value *(*const)(short, long, bool))0x5972f0)(a1, a2, a3);
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
						((real_matrix4x3 *(*const)(long, real_matrix4x3 *))0xb2ec60)(s_PodiumObjectIndex, &podiumObjectTransform);
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
								((void (*const)(long, hs_value))0x5974e0)(a2, hs_value::from_long(0));
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

		((void (*const)(long, hs_value))0x5974e0)(a2, hs_value::from_long(0));
	}
}

void hs_dew_method_stub_evaluate(short op, __int32 thread_index, char a3) // 0x107B73E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_dew_method_stub_evaluate@@YAXFHD@Z");
	// `anonymous-namespace'::hs_dew_method_stub_evaluate
	// char a3;
	// s_hs_script const *script;
	// hs_stack_frame *const stack_frame;
	// s_hs_syntax_node *const node;
		// Scripting::HS::ScriptMethod *method;
	// function call : s_hs_syntax_node *(*const)(long)
	// function call : void (*)(short, long, bool)
	// function call : void (*const)(long, hs_value)
	// function call : void (*const)(long, hs_value)

	hs_stack_frame *const stack_frame = hs_thread_stack(thread_index);
	s_hs_syntax_node *const node = ((s_hs_syntax_node *(*const)(long))0x598a10)(stack_frame->expression_index);
	s_hs_script const *script = global_scenario_get()->scripts.get_element(node->line_number);
	if (script && script->type == static_cast<e_hs_script_type>(6))
	{
		Scripting::HS::ScriptMethod *method = (Scripting::HS::ScriptMethod *)script->extern_method;
		if (method)
		{
			method->evaluateProc(op, thread_index, a3);
			return;
		}
		((void (*const)(long, hs_value))0x5974e0)(thread_index, hs_value::get_default(script->return_type));
	}
	else
	{
		((void (*const)(long, hs_value))0x5974e0)(thread_index, hs_value::get_default((e_hs_type)4));
	}
}

bool unit_scripting_vehicle_test_seat(long vehicle_index, unsigned long seat_name, long unit_index) // 0x107B92A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?unit_scripting_vehicle_test_seat@@YA_NJKJ@Z");
	// `anonymous-namespace'::unit_scripting_vehicle_test_seat
	// static ...; // 0x107B9434
	// long vehicle_index;
	// unsigned long seat_name;
	// long unit_index;
	// s_unit_data *vehicle;
	// s_unit_data *unit;
		// s_unit_seat_source seats[64];
		// long seat_count;
			// long i;
				// s_unit_seat_definition *seat;
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : short (*const)(long, s_unit_seat_source const *, long, bool)

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
	// `anonymous-namespace'::unit_scripting_vehicle_test_seat_list_legacy
	// static ...; // 0x107B96AC
	// static ...; // 0x107B96A4
	// long vehicle_index;
	// unsigned long seat_name;
	// long list_index;
		// s_unit_seat_source seats[64];
		// long list_iterator;
		// long seat_count;
			// long object_index;
				// s_unit_data *unit;
					// long i;
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : short (*const)(long, s_unit_seat_source const *, long, bool)
	// function call : long (*const)(long, long *)
	// function call : long (*const)(long, long *)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)

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
	// `anonymous-namespace'::hs_vehicle_test_seat_legacy_evaluate
	// char initial;
		// hs_value const *args;
			// bool result;
	// function call : hs_value *(*const)(short, long, bool)
	// function call : void (*const)(long, hs_value)

	if (hs_value const *args = ((hs_value const *(__cdecl *)(unsigned short, long, bool))0x5972f0)(function_index, thread_index, initial))
	{
		bool result = unit_scripting_vehicle_test_seat(args[0].long_value, args[1].long_value, args[2].long_value);
		((void(__cdecl *const)(long, hs_value))0x5974e0)(thread_index, hs_value::from_bool(result));
	}
}

void hs_vehicle_test_seat_list_legacy_evaluate(short function_index, __int32 thread_index, char initial) // 0x107B89D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_vehicle_test_seat_list_legacy_evaluate@@YAXFHD@Z");
	// `anonymous-namespace'::hs_vehicle_test_seat_list_legacy_evaluate
	// char initial;
		// hs_value const *args;
			// bool result;
	// function call : hs_value *(*const)(short, long, bool)
	// function call : void (*const)(long, hs_value)

	if (hs_value const *args = ((hs_value *(*const)(short, long, bool))0x5972f0)(function_index, thread_index, initial))
	{
		bool result = unit_scripting_vehicle_test_seat_list_legacy(args[0].long_value, args[1].long_value, args[2].long_value);
		((void (*const)(long, hs_value))0x5974e0)(thread_index, hs_value::from_bool(result));
	}
}

void hs_get_value_string(e_hs_type type, long value, char (&buffer)[256]) // 0x107B79F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_get_value_string@@YAXW4e_hs_type@@JAAY0BAA@D@Z");
	// `anonymous-namespace'::hs_get_value_string
// $LN47:
// $LN30:
// $LN26:
// $LN12:
// $LN11:
// $LN10:
// $LN9:
// $LN8:
// $LN7:
// $LN6:
// $LN5:
// $LN4:
	// e_hs_type type;
	// long value;
	// char (&buffer)[256];
		// char *str;

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
	// `anonymous-namespace'::hs_debug_macro_function_evaluate
	// static ...; // 0x107B72B7
	// static ...; // 0x107B72B4
	// static ...; // 0x107B7284
	// static ...; // 0x107B727C
	// long thread_index;
	// long *evaluated_arguments;
	// short function_index;
	// hs_stack_frame const *frame;
	// s_hs_syntax_node const *expression;
	// s_hs_script const &script;
	// Modules::ModuleDebug &moduleDebug;
	// long const expression_index;
	// s_hs_thread const *thread;
		// s_static_string<8192> buffer;
		// s_hs_script_op const *function;
		// s_static_string<8> expr_index_buff;
			// std::string &scriptFilter;
			// __int32 i;
				// char argument_value[256];
			// std::string &traceFile;
				// static _iobuf *`hs_debug_macro_function_evaluate'::`24'::fp; // 0x1138DE9C
					// static bool `hs_debug_macro_function_evaluate'::`25'::file_initialized; // 0x1138DD7A
				// static bool `hs_debug_macro_function_evaluate'::`33'::console_initialized; // 0x1138DD7B
					// _iobuf *fp;
	// function call : s_hs_syntax_node *(*const)(long)
	// function call : void ()
	// function call : __int32 ()

	Modules::ModuleDebug &moduleDebug = Modules::ModuleDebug::Instance();
	s_hs_thread const *thread = hs_thread_get(thread_index);
	hs_stack_frame const *frame = hs_thread_stack(thread_index);
	long const expression_index = frame->expression_index;
	s_hs_syntax_node const *expression = ((s_hs_syntax_node *(*const)(long))0x598a10)(expression_index);
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
	// `anonymous-namespace'::hs_thread_main_hook
	// long thread_index;
	// short stack_top;
	// short thread_type;
	// c_data_array<s_hs_thread> *threads;
	// void (*const hs_thread_main)(long);
	// s_hs_thread *thread;
	// function call : void *(*const)(s_data_array const *, unsigned long)
	// function call : void (*const)(long)
	// function call : void (*const)(s_data_array *, long)

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
	// `anonymous-namespace'::hs_runtime_script_begin_hook
	// e_hs_script_type thread_type;
	// s_scenario *scenario;
		// s_hs_script &script;
			// long thread_index;
	// function call : long (*const)(e_hs_script_type, short)
	// function call : bool (*const)(long, long, long, long *)

	s_scenario *scenario = global_scenario_get();
	if (script_index >= 0 && script_index < scenario->scripts.count)
	{
		s_hs_script &script = scenario->scripts[script_index];
		if (script.type == script_type)
		{
			long thread_index = ((long (*const)(e_hs_script_type, short))0x598e70)(thread_type, script_index);
			if (thread_index != -1)
			{
				((bool (*const)(long, long, long, long *))0x594510)(thread_index, script.root_expression_index, 3, nullptr);
				return thread_index;
			}
		}
	}
	return -1;
}

long *hs_macro_function_evaluate_hook(short function_index, long thread_index, bool initial) // 0x107B7D90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_macro_function_evaluate_hook@@YAPAJFJ_N@Z");
	// `anonymous-namespace'::hs_macro_function_evaluate_hook
	// static ...; // 0x107B7F4C
	// short function_index;
	// long thread_index;
	// bool initial;
	// long *(*const hs_arguments_evaluate)(long, short, short const *, bool);
	// s_hs_syntax_node *node;
	// hs_stack_frame *stack;
		// s_hs_script *script;
		// short types[16];
			// long i;
		// s_hs_script_op const *function_def;
		// long *evaluated_arguments;
	// function call : s_hs_syntax_node *(*const)(long)
	// function call : long *(*const)(long, short, short const *, bool)
	// function call : long *(*const)(long, short, short const *, bool)

	long *(*const hs_arguments_evaluate)(long, short, short const *, bool) = reinterpret_cast<long *(*)(long, short, short const *, bool)>(0x594140);
	hs_stack_frame *stack = hs_thread_stack(thread_index);
	s_hs_syntax_node *node = ((s_hs_syntax_node *(*const)(long))0x598a10)(stack->expression_index);
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
	// `anonymous-namespace'::hs_return_hook
	// hs_value value;
	// long *return_value;
	// long *(*const hs_destination)(s_hs_thread *, long);
	// s_hs_syntax_node *node;
	// hs_stack_frame *stack;
	// e_hs_type return_type;
	// long (*const hs_cast)(long, e_hs_type, e_hs_type, long);
	// s_hs_thread *thread;
		// short script_index;
	// function call : s_hs_syntax_node *(*const)(long)
	// function call : long *(*const)(s_hs_thread *, long)
	// function call : long (*const)(long, e_hs_type, e_hs_type, long)
	// function call : void (*const)(long)

	long *(*const hs_destination)(s_hs_thread *, long) = reinterpret_cast<long *(*)(s_hs_thread *, long)>(0x594460);
	long (*const hs_cast)(long, e_hs_type, e_hs_type, long) = reinterpret_cast<long (*)(long, e_hs_type, e_hs_type, long)>(0x5943a0);
	s_hs_thread *thread = hs_thread_get(thread_index);
	hs_stack_frame *stack = hs_thread_stack(thread_index);
	s_hs_syntax_node *node = ((s_hs_syntax_node *(*const)(long))0x598a10)(stack->expression_index);
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

	((void (*const)(long))0x598900)(thread_index);
}

void hs_evaluate_inspect_hook(short op, long thread_index, bool a3) // 0x107B75D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_evaluate_inspect_hook@@YAXFJ_N@Z");
	// `anonymous-namespace'::hs_evaluate_inspect_hook
	// static ...; // 0x107B77FC
	// static ...; // 0x107B77F4
	// short op;
	// long thread_index;
	// bool a3;
	// long value_expr_index;
	// short stack_pointer;
	// void (**const g_hs_inspect_function_table)(short, long, char *, long);
	// s_hs_syntax_node *func_expr;
	// s_hs_syntax_node *name_expr;
	// long *value;
		// void (*inspect_function)(short, long, char *, long);
		// s_hs_syntax_node *value_expr;
			// char buffer[1024];
	// function call : void *(*const)(long, long, long, short *)
	// function call : s_hs_syntax_node *(*const)(long)
	// function call : s_hs_syntax_node *(*const)(long)
	// function call : bool (*const)(long, long, long, long *)
	// function call : s_hs_syntax_node *(*const)(long)
	// function call : void (*)(short, long, char *, long)
	// function call : void (*const)(long, hs_value)

	void (**const g_hs_inspect_function_table)(short, long, char *, long) = reinterpret_cast<void (**)(short, long, char *, long)>(0x18A1090);
	short stack_pointer;
	long *value = (long *)((void *(*const)(long, long, long, short *))0x5987d0)(thread_index, 4, 2, &stack_pointer);
	if (!value)
	{
		return;
	}

	s_hs_syntax_node *func_expr = ((s_hs_syntax_node *(*const)(long))0x598a10)(hs_thread_stack(thread_index)->expression_index);
	s_hs_syntax_node *name_expr = ((s_hs_syntax_node *(*const)(long))0x598a10)(*(long *)func_expr->data);
	long value_expr_index = name_expr->next_expression_index;
	if (a3)
	{
		((bool (*const)(long, long, long, long *))0x594510)(thread_index, value_expr_index, (stack_pointer << 16) | 1, nullptr);
	}
	else
	{
		s_hs_syntax_node *value_expr = ((s_hs_syntax_node *(*const)(long))0x598a10)(value_expr_index);
		void (*inspect_function)(short, long, char *, long) = g_hs_inspect_function_table[(short)value_expr->type];
		if (inspect_function)
		{
			char buffer[1024];
			inspect_function(value_expr->type, *value, buffer, 1024);
			Console::WriteLine(buffer);
		}

		((void (*const)(long, hs_value))0x5974e0)(thread_index, hs_value::from_long(0));
	}
}

void hs_evaluate_set_hook(short op, long thread_index, bool a3) // 0x107B78C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_evaluate_set_hook@@YAXFJ_N@Z");
	// `anonymous-namespace'::hs_evaluate_set_hook
	// bool a3;
	// s_hs_syntax_node *node;
	// void (*const hs_set_evaluate)(short, long, bool);
	// s_hs_thread *thread;
	// function call : s_hs_syntax_node *(*const)(long)
	// function call : s_hs_syntax_node *(*const)(long)
	// function call : s_hs_syntax_node *(*const)(long)
	// function call : void (*const)(short, long, bool)

	void (*const hs_set_evaluate)(short, long, bool) = (void (*const)(short, long, bool))0x5957f0;
	s_hs_thread *thread = tls_getd().hs_thread_deterministic_data->try_and_get(thread_index);
	s_hs_syntax_node *node = ((s_hs_syntax_node *(*const)(long))0x598a10)(*(long *)&thread->stack[thread->stack_offset]);
	node = ((s_hs_syntax_node *(*const)(long))0x598a10)(*(long *)node->data);
	node = ((s_hs_syntax_node *(*const)(long))0x598a10)(node->next_expression_index);
	hs_set_evaluate(op, thread_index, a3);
	if (!a3)
	{
		InvalidateGlobal(*(short *)node->data);
	}
}

void cinematic_scripting_start_screen_effect(__int32 cinematic_tag_index, __int32 scene_index, __int32 shot_index, __int32 cinematic_screen_effect_index) // 0x107B4690
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?cinematic_scripting_start_screen_effect@@YAXHHHH@Z");
	// `anonymous-namespace'::cinematic_scripting_start_screen_effect
	// __int32 cinematic_screen_effect_index;
	// void (*const cinematic_screen_effect_new)(__int32, unsigned long);
	// unsigned long (*const SpawnScreenEffect)(__int32, __int32, __int32, void *, void *);
	// s_cinematic_scene_definition *(*const scenario_get_cinematic_scene)(__int32, __int32);
	// s_cinematic_scene_definition *const cisc;
		// s_cinematic_scene_shot *const shot;
			// s_cinematic_shot_screen_effect *cinematic_screen_effect;
				// long datum_index;
	// function call : s_cinematic_scene_definition *(*const)(__int32, __int32)
	// function call : void (*const)(__int32, unsigned long)

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
	// `anonymous-namespace'::cinematic_scripting_stop_screen_effect
	// __int32 cinematic_screen_effect_index;
	// s_cinematic_scene_definition *(*const scenario_get_cinematic_scene)(__int32, __int32);
	// s_cinematic_scene_definition *const cisc;
	// unsigned long (*const cinematic_screen_effect_get_datum)(__int32);
	// void (*const cinematic_screen_effect_destroy_internal)(__int32);
		// s_cinematic_scene_shot *const shot;
			// unsigned long sefc_datum;
	// function call : s_cinematic_scene_definition *(*const)(__int32, __int32)
	// function call : unsigned long (*const)(__int32)
	// function call : void (*const)(long)
	// function call : void (*const)(__int32)

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
	// `anonymous-namespace'::ui_get_current_music_id_hook
	// procedure flags: nofpo
		// __int32 lobbyType;
		// __int32 networkMode;
		// Blam::Network::Session *session;
	// function call : bool (*const)()

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
