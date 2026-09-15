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
		c_simulation_hs_script_wake_event_definition(c_simulation_hs_script_wake_event_definition &); /* compiler_generated() */
		c_simulation_hs_script_wake_event_definition(c_simulation_hs_script_wake_event_definition const &); /* compiler_generated() */
		c_simulation_hs_script_wake_event_definition(); /* compiler_generated() */
		c_simulation_hs_script_wake_event_definition &operator=(c_simulation_hs_script_wake_event_definition &); /* compiler_generated() */
		c_simulation_hs_script_wake_event_definition &operator=(c_simulation_hs_script_wake_event_definition const &); /* compiler_generated() */
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
		c_simulation_hs_sync_global_event_definition(c_simulation_hs_sync_global_event_definition &); /* compiler_generated() */
		c_simulation_hs_sync_global_event_definition(c_simulation_hs_sync_global_event_definition const &); /* compiler_generated() */
		c_simulation_hs_sync_global_event_definition(); /* compiler_generated() */
		c_simulation_hs_sync_global_event_definition &operator=(c_simulation_hs_sync_global_event_definition &); /* compiler_generated() */
		c_simulation_hs_sync_global_event_definition &operator=(c_simulation_hs_sync_global_event_definition const &); /* compiler_generated() */
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

namespace hades_file_local
{
	extern s_hs_script_op const *script_ops[1707]; // 0x1134DDD8
	extern real_rectangle2d global_null_rectangle2d; // 0x11182F0C
	extern char const *script_op_names[1707]; // 0x1134F888
}
using namespace hades_file_local;
/* ---------- public code */

namespace Patches
{
	namespace HaloScript
	{
		_extern void _sub_107B2F30();
		void ApplyAll() // 0x107B2F30
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@HaloScript@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_107B2F30();
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

	*(short *)payload = ((Blam::BitStream *)packet)->Read<short>(10);
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

	((Blam::BitStream *)packet)->Write<long>(((long *)payload)[0], 32);
	((Blam::BitStream *)packet)->Write<long>(((long *)payload)[1], 32);
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

_extern bool _sub_107B10E0(c_simulation_hs_sync_global_event_definition *const, long, long const *, long, void const *);
_inline bool c_simulation_hs_sync_global_event_definition::apply_game_event(long reference_gamestate_count, long const *gamestate_indices, long payload_size, void const *payload) // 0x107B10E0
{
	// `anonymous-namespace'::c_simulation_hs_sync_global_event_definition::apply_game_event
	// long reference_gamestate_count;
	// long const *gamestate_indices;
	// long payload_size;
	// void const *payload;
	// s_simulation_hs_sync_global_event_data *data;
	// s_hs_global_runtime *global;
	// char value_str[256];
	// e_hs_type global_type;
	{
		// s_scenario const *scnr;
		// long const string_offset;
	}
	// function call : void (*const)(long)
	todo("implement");
	bool __result = _sub_107B10E0(this, reference_gamestate_count, gamestate_indices, payload_size, payload);
	return __result;
}

_extern void _sub_107B8DE0(short, unsigned short);
void simulation_action_hs_sync_global(short global_index, unsigned short player_mask) // 0x107B8DE0
{
	// `anonymous-namespace'::simulation_action_hs_sync_global
	// static ...; // 0x107B8F88
	// static ...; // 0x107B8F80
	// short global_index;
	// unsigned short player_mask;
	// s_simulation_hs_sync_global_event_data data;
	// s_hs_global_runtime *global;
	// long value;
	{
		// long string_offset;
	}
	// function call : bool (*const)()
	// function call : void (*const)(e_simulation_event_type, long, long *, long, long, void const *)
	todo("implement");
	_sub_107B8DE0(global_index, player_mask);
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

_extern void _sub_107B8240(short, __int32, char);
void hs_mp_wake_script_evaluate(short a1, __int32 thread_index, char a3) // 0x107B8240
{
	// `anonymous-namespace'::hs_mp_wake_script_evaluate
	// char a3;
	// s_hs_syntax_node *node;
	// s_scenario *scnr;
	// short script_index;
	// s_hs_thread *thread;
	{
		// long thread_index;
	}
	// function call : s_hs_syntax_node *(*const)(long)
	// function call : s_hs_syntax_node *(*const)(long)
	// function call : s_hs_syntax_node *(*const)(long)
	// function call : bool (*const)()
	// function call : long (*const)(short)
	// function call : void (*const)(short)
	// function call : void (*const)(long, hs_value)
	todo("implement");
	_sub_107B8240(a1, thread_index, a3);
}

_extern void _sub_107B7FE0(short, __int32, char);
void hs_mp_sync_global_evaluate(short op, __int32 thread_index, char a3) // 0x107B7FE0
{
	// `anonymous-namespace'::hs_mp_sync_global_evaluate
	// char a3;
	// s_hs_syntax_node *node;
	// s_hs_thread *thread;
	{
		// short global_index;
	}
	// function call : s_hs_syntax_node *(*const)(long)
	// function call : s_hs_syntax_node *(*const)(long)
	// function call : s_hs_syntax_node *(*const)(long)
	// function call : bool (*const)()
	// function call : void (*const)(long, hs_value)
	todo("implement");
	_sub_107B7FE0(op, thread_index, a3);
}

_extern void _sub_107B6A10(long, long, long, long, unsigned long);
void hs_cinematic_scripting_start_animation_legacy(long cine_index, long scene_index, long cine_object_index, long object_index, unsigned long animation_id) // 0x107B6A10
{
	// `anonymous-namespace'::hs_cinematic_scripting_start_animation_legacy
	// unsigned long animation_id;
	// long (*const cinematic_object_get_internal)(long);
	// void (*const scenery_animation_start_relative)(long, long, unsigned long, long);
	// void (*const unit_limit_lipsync_to_mouth_only)(long, bool);
	// s_cinematic_scene_definition *(*const scenario_get_cinematic_scene)(long, long);
	// void *(*const c_animation_manager__get_mixing_board_facial_animation_channel)(void *);
	// s_cinematic_scene_definition const *cinematic_scene;
	// void (*const custom_animation_relative)(long, long, unsigned long, char, long);
	{
		// s_cinematic_scene_object const *cinematic_object;
		{
			// s_object_data *object_data;
			// __int32 id_bit;
			{
				// long object;
				{
					// long animation_data;
					{
						// long anim_channel;
					}
				}
			}
			{
			}
		}
	}
	// function call : s_cinematic_scene_definition *(*const)(long, long)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : long (*const)(long)
	// function call : void (*const)(long, long, unsigned long, char, long)
	// function call : void (*const)(long, bool)
	// function call : void *(*const)(void *)
	// function call : long (*const)(long)
	// function call : void (*const)(long, long, unsigned long, long)
	todo("implement");
	_sub_107B6A10(cine_index, scene_index, cine_object_index, object_index, animation_id);
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

_extern void _sub_107B6340(long, long, long, short);
void hs_cinematic_scripting_create_object_legacy(long cine_index, long scene_index, long cine_object_index, short object_name_index) // 0x107B6340
{
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
	{
		// s_cinematic_scene_object const *cinematic_object;
		{
			// long object_index;
		}
	}
	// function call : s_cinematic_scene_definition *(*const)(long, long)
	// function call : bool (*const)(__int32)
	// function call : long (*const)(short)
	// function call : long (*const)(short, bool, bool)
	// function call : long (*const)(short)
	// function call : long (*const)(short)
	// function call : void (*const)(long, bool)
	// function call : void (*const)(long, bool)
	todo("implement");
	_sub_107B6340(cine_index, scene_index, cine_object_index, object_name_index);
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

_extern long _sub_107B4120(long, long, long);
long cinematic_scripting_cinematic_object_get_representation_index(long cine_index, long scene_index, long cine_object_index) // 0x107B4120
{
	// `anonymous-namespace'::cinematic_scripting_cinematic_object_get_representation_index
	// long cine_object_index;
	// bool (*const cinematic_index_is_valid)(__int32);
	// s_cinematic_scene_definition *(*const scenario_get_cinematic_scene)(long, long);
	// s_cinematic_scene_definition *cinematic_scene;
	{
		// s_cinematic_scene_object *cinematic_object;
		{
			// __int32 campaign_player_representation_index;
		}
	}
	// function call : s_cinematic_scene_definition *(*const)(long, long)
	// function call : bool (*const)(__int32)
	todo("implement");
	long __result = _sub_107B4120(cine_index, scene_index, cine_object_index);
	return __result;
}

_extern long _sub_107B4A80(long);
long get_campaign_player_character_type_index(long player_session_index) // 0x107B4A80
{
	// `anonymous-namespace'::get_campaign_player_character_type_index
	// long player_session_index;
	// s_player_datum *player;
	// s_game_globals *matg;
	// long player_datum_index;
	{
		// s_scenario *scnr;
		// Blam::Network::Session *session;
		{
			// __int32 player_sidx;
			// unsigned long name;
			{
				// __int32 i;
			}
		}
	}
	todo("implement");
	long __result = _sub_107B4A80(player_session_index);
	return __result;
}

_extern void _sub_107B43C0(long, long, long);
void cinematic_scripting_create_cinematic_object_hook(long cine_index, long scene_index, long cine_object_index) // 0x107B43C0
{
	// `anonymous-namespace'::cinematic_scripting_create_cinematic_object_hook
	// long cine_object_index;
	// long (*const cinematic_object_get_internal)(s_cinematic_scene_object const *);
	// bool (*const cinematic_index_is_valid)(__int32);
	// s_cinematic_scene_definition *(*const scenario_get_cinematic_scene)(long, long);
	// s_cinematic_scene_definition *cinematic_scene;
	// void (*const cinematic_scripting_create_cinematic_object)(long, long, long);
	{
		// s_cinematic_scene_object *cinematic_object;
		{
			// long campaign_player_representation_index;
			// long object;
			// long character_type_index;
			{
				// s_game_globals *matg;
				{
					// long character_rep_index;
				}
			}
			{
				// s_player_datum *player;
				// long player_datum_index;
			}
		}
	}
	// function call : s_cinematic_scene_definition *(*const)(long, long)
	// function call : bool (*const)(__int32)
	// function call : void (*const)(long, long, long)
	// function call : long (*const)(s_cinematic_scene_object const *)
	todo("implement");
	_sub_107B43C0(cine_index, scene_index, cine_object_index);
}

_extern void _sub_107B5AF0(long, long, long, short, long, unsigned long, bool);
void hs_cinematic_scripting_create_and_animate_object_legacy(long cine_index, long scene_index, long cine_object_index, short object_name_index, long object_index, unsigned long animation_id, bool a5) // 0x107B5AF0
{
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
	{
		// s_cinematic_scene_object *cinematic_object;
		{
			// long campaign_player_representation_index;
			// long object;
			// long character_type_index;
			{
				// s_game_globals *matg;
				{
					// long character_rep_index;
				}
			}
			{
				// s_player_datum *player;
				// long player_datum_index;
			}
		}
	}
	// function call : s_cinematic_scene_definition *(*const)(long, long)
	// function call : bool (*const)(__int32)
	// function call : bool (*const)(long, long, long)
	// function call : long (*const)(short)
	// function call : void (*const)(long, long, long)
	// function call : long (*const)(s_cinematic_scene_object const *)
	// function call : void (*const)(long, bool)
	// function call : bool (*const)(s_cinematic_scene_definition const *)
	// function call : void (*const)(long)
	todo("implement");
	_sub_107B5AF0(cine_index, scene_index, cine_object_index, object_name_index, object_index, animation_id, a5);
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

_extern void _sub_107B66B0(long, long, long, long);
void hs_cinematic_scripting_destroy_object_legacy(long cine_index, long scene_index, long cine_object_index, long object_index) // 0x107B66B0
{
	// `anonymous-namespace'::hs_cinematic_scripting_destroy_object_legacy
	// long object_index;
	// void (*const object_hide)(long, bool);
	// void (*const unit_limit_lipsync_to_mouth_only)(long, bool);
	// s_cinematic_scene_definition *(*const scenario_get_cinematic_scene)(long, long);
	// void (*const unit_stop_custom_animation)(long);
	// s_cinematic_scene_definition const *cinematic_scene;
	// void (*const object_set_always_active)(long, bool);
	// void (*const object_cinematic_visibility)(long, bool);
	{
		// s_cinematic_scene_object const *cinematic_object;
		{
			// s_object_data *object_data;
			// __int32 id_bit;
		}
	}
	// function call : s_cinematic_scene_definition *(*const)(long, long)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void (*const)(long, bool)
	// function call : void (*const)(long, bool)
	// function call : void (*const)(long, bool)
	// function call : void (*const)(long)
	// function call : void (*const)(long, bool)
	todo("implement");
	_sub_107B66B0(cine_index, scene_index, cine_object_index, object_index);
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

_extern void _sub_107B4FD0(short, __int32, char);
void hs_camera_set_evaluate(short a1, __int32 a2, char a3) // 0x107B4FD0
{
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
	{
		// s_scenario *const scnr;
		{
			// short camera;
			// c_tag_block<s_scenario_cutscene_camera_point> cutscenes;
			{
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
				{
					// long s_PodiumObjectIndex;
					// s_game_globals *matg;
					// s_object_data *scenObject;
					// s_scenario_cutscene_camera_point podiumCamera;
					{
						// real_matrix4x3 podiumObjectTransform;
						// real_euler_angles3d podiumObjectOrientation;
					}
					{
						// void *podium;
						{
							// s_podium_settings *podium_settings;
							{
								// float &dword_471A4A0;
								// real_point3d podium_position_offset;
								// float &dword_18ECE00;
								// real_vector3d podium_rotation_offset;
							}
						}
					}
				}
			}
		}
	}
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
	todo("implement");
	_sub_107B4FD0(a1, a2, a3);
}

_extern void _sub_107B73E0(short, __int32, char);
void hs_dew_method_stub_evaluate(short op, __int32 thread_index, char a3) // 0x107B73E0
{
	// `anonymous-namespace'::hs_dew_method_stub_evaluate
	// char a3;
	// s_hs_script const *script;
	// hs_stack_frame *const stack_frame;
	// s_hs_syntax_node *const node;
	{
		// Scripting::HS::ScriptMethod *method;
	}
	// function call : s_hs_syntax_node *(*const)(long)
	// function call : void (*)(short, long, bool)
	// function call : void (*const)(long, hs_value)
	// function call : void (*const)(long, hs_value)
	todo("implement");
	_sub_107B73E0(op, thread_index, a3);
}

_extern bool _sub_107B92A0(long, unsigned long, long);
bool unit_scripting_vehicle_test_seat(long vehicle_index, unsigned long seat_name, long unit_index) // 0x107B92A0
{
	// `anonymous-namespace'::unit_scripting_vehicle_test_seat
	// static ...; // 0x107B9434
	// long vehicle_index;
	// unsigned long seat_name;
	// long unit_index;
	// s_unit_data *vehicle;
	// s_unit_data *unit;
	{
		// s_unit_seat_source seats[64];
		// long seat_count;
		{
			// long i;
			{
				// s_unit_seat_definition *seat;
			}
		}
	}
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : short (*const)(long, s_unit_seat_source const *, long, bool)
	todo("implement");
	bool __result = _sub_107B92A0(vehicle_index, seat_name, unit_index);
	return __result;
}

_extern bool _sub_107B94C0(long, unsigned long, long);
bool unit_scripting_vehicle_test_seat_list_legacy(long vehicle_index, unsigned long seat_name, long list_index) // 0x107B94C0
{
	// `anonymous-namespace'::unit_scripting_vehicle_test_seat_list_legacy
	// static ...; // 0x107B96AC
	// static ...; // 0x107B96A4
	// long vehicle_index;
	// unsigned long seat_name;
	// long list_index;
	{
		// s_unit_seat_source seats[64];
		// long list_iterator;
		// long seat_count;
		{
			// long object_index;
			{
				// s_unit_data *unit;
				{
					// long i;
				}
			}
		}
	}
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : short (*const)(long, s_unit_seat_source const *, long, bool)
	// function call : long (*const)(long, long *)
	// function call : long (*const)(long, long *)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	todo("implement");
	bool __result = _sub_107B94C0(vehicle_index, seat_name, list_index);
	return __result;
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

_extern void _sub_107B79F0(e_hs_type, long, char (&)[256]);
void hs_get_value_string(e_hs_type type, long value, char (&buffer)[256]) // 0x107B79F0
{
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
	{
		// char *str;
	}
	todo("implement");
	_sub_107B79F0(type, value, buffer);
}

_extern void _sub_107B6ED0(long, long *, short);
void hs_debug_macro_function_evaluate(long thread_index, long *evaluated_arguments, short function_index) // 0x107B6ED0
{
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
	{
		// s_static_string<8192> buffer;
		// s_hs_script_op const *function;
		// s_static_string<8> expr_index_buff;
		{
			// std::string &scriptFilter;
		}
		{
			// __int32 i;
			{
				// char argument_value[256];
			}
		}
		{
			// std::string &traceFile;
			{
				// static _iobuf *`hs_debug_macro_function_evaluate'::`24'::fp; // 0x1138DE9C
				{
					// static bool `hs_debug_macro_function_evaluate'::`25'::file_initialized; // 0x1138DD7A
				}
			}
			{
				// static bool `hs_debug_macro_function_evaluate'::`33'::console_initialized; // 0x1138DD7B
				{
					// _iobuf *fp;
				}
			}
		}
	}
	// function call : s_hs_syntax_node *(*const)(long)
	// function call : void ()
	// function call : __int32 ()
	todo("implement");
	_sub_107B6ED0(thread_index, evaluated_arguments, function_index);
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

_extern long *_sub_107B7D90(short, long, bool);
long *hs_macro_function_evaluate_hook(short function_index, long thread_index, bool initial) // 0x107B7D90
{
	// `anonymous-namespace'::hs_macro_function_evaluate_hook
	// static ...; // 0x107B7F4C
	// short function_index;
	// long thread_index;
	// bool initial;
	// long *(*const hs_arguments_evaluate)(long, short, short const *, bool);
	// s_hs_syntax_node *node;
	// hs_stack_frame *stack;
	{
		// s_hs_script *script;
		// short types[16];
		{
			// long i;
		}
	}
	{
		// s_hs_script_op const *function_def;
		// long *evaluated_arguments;
	}
	// function call : s_hs_syntax_node *(*const)(long)
	// function call : long *(*const)(long, short, short const *, bool)
	// function call : long *(*const)(long, short, short const *, bool)
	todo("implement");
	long * __result = _sub_107B7D90(function_index, thread_index, initial);
	return __result;
}

_extern void _sub_107B8410(long, hs_value);
void hs_return_hook(long thread_index, hs_value value) // 0x107B8410
{
	// `anonymous-namespace'::hs_return_hook
	// hs_value value;
	// long *return_value;
	// long *(*const hs_destination)(s_hs_thread *, long);
	// s_hs_syntax_node *node;
	// hs_stack_frame *stack;
	// e_hs_type return_type;
	// long (*const hs_cast)(long, e_hs_type, e_hs_type, long);
	// s_hs_thread *thread;
	{
		// short script_index;
	}
	// function call : s_hs_syntax_node *(*const)(long)
	// function call : long *(*const)(s_hs_thread *, long)
	// function call : long (*const)(long, e_hs_type, e_hs_type, long)
	// function call : void (*const)(long)
	todo("implement");
	_sub_107B8410(thread_index, value);
}

_extern void _sub_107B75D0(short, long, bool);
void hs_evaluate_inspect_hook(short op, long thread_index, bool a3) // 0x107B75D0
{
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
	{
		// void (*inspect_function)(short, long, char *, long);
		// s_hs_syntax_node *value_expr;
		{
			// char buffer[1024];
		}
	}
	// function call : void *(*const)(long, long, long, short *)
	// function call : s_hs_syntax_node *(*const)(long)
	// function call : s_hs_syntax_node *(*const)(long)
	// function call : bool (*const)(long, long, long, long *)
	// function call : s_hs_syntax_node *(*const)(long)
	// function call : void (*)(short, long, char *, long)
	// function call : void (*const)(long, hs_value)
	todo("implement");
	_sub_107B75D0(op, thread_index, a3);
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

_extern void _sub_107B4690(__int32, __int32, __int32, __int32);
void cinematic_scripting_start_screen_effect(__int32 cinematic_tag_index, __int32 scene_index, __int32 shot_index, __int32 cinematic_screen_effect_index) // 0x107B4690
{
	// `anonymous-namespace'::cinematic_scripting_start_screen_effect
	// __int32 cinematic_screen_effect_index;
	// void (*const cinematic_screen_effect_new)(__int32, unsigned long);
	// unsigned long (*const SpawnScreenEffect)(__int32, __int32, __int32, void *, void *);
	// s_cinematic_scene_definition *(*const scenario_get_cinematic_scene)(__int32, __int32);
	// s_cinematic_scene_definition *const cisc;
	{
		// s_cinematic_scene_shot *const shot;
		{
			// s_cinematic_shot_screen_effect *cinematic_screen_effect;
			{
				// long datum_index;
			}
		}
	}
	// function call : s_cinematic_scene_definition *(*const)(__int32, __int32)
	// function call : void (*const)(__int32, unsigned long)
	todo("implement");
	_sub_107B4690(cinematic_tag_index, scene_index, shot_index, cinematic_screen_effect_index);
}

_extern void _sub_107B4840(__int32, __int32, __int32, __int32);
void cinematic_scripting_stop_screen_effect(__int32 cinematic_tag_index, __int32 scene_index, __int32 shot_index, __int32 cinematic_screen_effect_index) // 0x107B4840
{
	// `anonymous-namespace'::cinematic_scripting_stop_screen_effect
	// __int32 cinematic_screen_effect_index;
	// s_cinematic_scene_definition *(*const scenario_get_cinematic_scene)(__int32, __int32);
	// s_cinematic_scene_definition *const cisc;
	// unsigned long (*const cinematic_screen_effect_get_datum)(__int32);
	// void (*const cinematic_screen_effect_destroy_internal)(__int32);
	{
		// s_cinematic_scene_shot *const shot;
		{
			// unsigned long sefc_datum;
		}
	}
	// function call : s_cinematic_scene_definition *(*const)(__int32, __int32)
	// function call : unsigned long (*const)(__int32)
	// function call : void (*const)(long)
	// function call : void (*const)(__int32)
	todo("implement");
	_sub_107B4840(cinematic_tag_index, scene_index, shot_index, cinematic_screen_effect_index);
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
