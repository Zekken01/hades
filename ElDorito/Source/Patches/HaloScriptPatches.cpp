/* ---------- headers */

#include "hades/hades.h"

#include "Blam/BlamNetwork.hpp"
#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/cseries/static_string.inl"
#include "Blam/effects/screen_effect.hpp"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/bitstream.hpp"
#include "Blam/memory/data_array.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/networking/session/network_session.hpp"
#include "Blam/networking/session/network_session_membership.hpp"
#include "Blam/networking/session/network_session_parameters_base.hpp"
#include "Blam/objects/damage.hpp"
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
#include "ChatCommands/ChatCommandMap.hpp"
#include "Console/Console.hpp"
#include "Forge/Geoemetry.hpp"
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
#include <variant>
#include <vector>

/* ---------- forward declarations */

class c_bitstream;
class c_simulation_event_definition;
class c_simulation_type_collection;
struct c_replication_outgoing_event;
struct lambda_1;
struct real_rectangle2d;
struct s_hs_script_op;
struct simulation_event_definition_return_value;
namespace
{
	struct s_simulation_hs_script_wake_event_data;
	class c_simulation_hs_script_wake_event_definition;
	struct s_simulation_hs_sync_global_event_data;
	class c_simulation_hs_sync_global_event_definition;
}

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
}

/* ---------- constants */

/* ---------- definitions */

namespace
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

namespace Patches
{
	namespace HaloScript
	{
		extern void ApplyAll();
		extern void RegisterSimulationTypes(c_simulation_type_collection *collection, __int32 *entity_count, __int32 *event_count);
	}
}

/* ---------- globals */

/* ---------- private variables */

namespace
{
	extern s_hs_script_op const *script_ops[1707]; // 0x1134DDD8
	extern real_rectangle2d global_null_rectangle2d; // 0x11182F0C
	extern char const *script_op_names[1707]; // 0x1134F888
}
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

		_extern void _sub_107B3950(c_simulation_type_collection *, __int32 *, __int32 *);
		void RegisterSimulationTypes(c_simulation_type_collection *collection, __int32 *entity_count, __int32 *event_count) // 0x107B3950
		{
			mangled_x86(MANGLED_TODO, "?RegisterSimulationTypes@HaloScript@Patches@@YAXPAVc_simulation_type_collection@@PAH1@Z");
			// __int32 *event_count;
			// static c_simulation_hs_script_wake_event_definition hs_wake_script_event_definition; // 0x1134DDD4
			// static c_simulation_hs_sync_global_event_definition hs_sync_global_event_definition; // 0x1134F884
			todo("implement");
			_sub_107B3950(collection, entity_count, event_count);
		}
	}
}

/* ---------- private code */
