/* ---------- headers */

#include "Patches/Events.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/effects/screen_effect.hpp"
#include "Blam/game/engine/game_engine_events.hpp"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/static_array.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/networking/session/network_session_membership.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
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
#include <memory>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <streambuf>
#include <system_error>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

struct s_game_engine_event_data;
struct s_multiplayer_event_response_definition;
namespace
{
	struct s_suppressed_game_engine_event;
	struct s_suppressed_game_engine_event_collection;
}

namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Events {}
	using namespace Patches::Events;
}

/* ---------- constants */

enum
{
	k_maximum_number_of_queued_game_engine_events = 64, // 0x0040 '@'
	k_game_engine_event_grief_time_in_seconds = 7, // 0x0007
};

namespace
{
	enum e_suppressed_game_engine_event_flags
	{
		_suppressed_game_engine_event_valid_bit = 0,
		_suppressed_game_engine_event_handled_bit,
		_suppressed_game_engine_event_delayed_for_join_bit,
	};
}
/* ---------- definitions */

namespace
{
	struct s_suppressed_game_engine_event
	{
		long equeued_game_time; // 0x0
		c_flags<enum e_suppressed_game_engine_event_flags,unsigned char> flags; // 0x4
		unsigned char __pad0[3]; // 0x5
		s_game_engine_event_data metadata; // 0x8
		s_suppressed_game_engine_event(s_suppressed_game_engine_event &); /* compiler_generated() */
		s_suppressed_game_engine_event(s_suppressed_game_engine_event const &); /* compiler_generated() */
		s_suppressed_game_engine_event(); /* compiler_generated() */
		s_suppressed_game_engine_event &operator=(s_suppressed_game_engine_event &); /* compiler_generated() */
		s_suppressed_game_engine_event &operator=(s_suppressed_game_engine_event const &); /* compiler_generated() */
	};
	static_assert(sizeof(s_suppressed_game_engine_event) == 48, "Invalid s_suppressed_game_engine_event size");

	//@@anonymous-namespace@@
	#pragma pack(push, 4)
	struct s_suppressed_game_engine_event_collection
	{
		long count; // 0x0
		s_static_array<s_suppressed_game_engine_event,64> elements; // 0x4
		s_suppressed_game_engine_event_collection(s_suppressed_game_engine_event_collection &); /* compiler_generated() */
		s_suppressed_game_engine_event_collection(s_suppressed_game_engine_event_collection const &); /* compiler_generated() */
		s_suppressed_game_engine_event_collection(); /* compiler_generated() */
		s_suppressed_game_engine_event_collection &operator=(s_suppressed_game_engine_event_collection &); /* compiler_generated() */
		s_suppressed_game_engine_event_collection &operator=(s_suppressed_game_engine_event_collection const &); /* compiler_generated() */
	};
	#pragma pack(pop)
	static_assert(sizeof(s_suppressed_game_engine_event_collection) == 3076, "Invalid s_suppressed_game_engine_event_collection size");

}
/* ---------- prototypes */

namespace Patches
{
	namespace Events
	{
		extern void ApplyAll();
		extern void OnEvent(std::function<void __cdecl(unsigned long,s_game_engine_event_data const *,s_multiplayer_event_response_definition const *)> callback);
	}
}

/* ---------- globals */

/* ---------- private variables */

namespace
{
	extern std::vector<std::function<void __cdecl(unsigned long,s_game_engine_event_data const *,s_multiplayer_event_response_definition const *)>,std::allocator<std::function<void __cdecl(unsigned long,s_game_engine_event_data const *,s_multiplayer_event_response_definition const *)> > > OnEventCallbacks; // 0x124584AC
}
/* ---------- public code */

namespace Patches
{
	namespace Events
	{
		_extern void _sub_10A59630();
		void ApplyAll() // 0x10A59630
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@Events@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10A59630();
		}

		_extern void _sub_10A59B30(std::function<void __cdecl(unsigned long,s_game_engine_event_data const *,s_multiplayer_event_response_definition const *)>);
		void OnEvent(std::function<void __cdecl(unsigned long,s_game_engine_event_data const *,s_multiplayer_event_response_definition const *)> callback) // 0x10A59B30
		{
			mangled_x86(MANGLED_TODO, "?OnEvent@Events@Patches@@YAXV?$function@$$A6AXKPBUs_game_engine_event_data@@PBUs_multiplayer_event_response_definition@@@Z@std@@@Z");
			// std::function<void __cdecl(unsigned long,s_game_engine_event_data const *,s_multiplayer_event_response_definition const *)> callback;
			todo("implement");
			_sub_10A59B30(callback);
		}
	}
}

extern s_game_engine_event_data &_sub_10A591B0(s_game_engine_event_data *const, s_game_engine_event_data const &);
_inline s_game_engine_event_data &s_game_engine_event_data::operator=(s_game_engine_event_data const &__that) // 0x10A591B0
{
	mangled_x86(MANGLED_TODO, "??4s_game_engine_event_data@@QAEAAU0@ABU0@@Z");
	// s_game_engine_event_data const &__that;
	compiler_generated();
	todo("implement");
	s_game_engine_event_data & __result = _sub_10A591B0(this, __that);
	return __result;
}

/* ---------- private code */
