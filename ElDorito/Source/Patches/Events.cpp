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

struct begin;
struct end;
struct s_game_engine_event_data;
struct s_multiplayer_event_response_definition;
struct s_player_datum;
namespace hades_file_local
{
	struct s_suppressed_game_engine_event;
	struct s_suppressed_game_engine_event_collection;
}
using namespace hades_file_local;

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

namespace hades_file_local
{
	enum e_suppressed_game_engine_event_flags
	{
		_suppressed_game_engine_event_valid_bit = 0,
		_suppressed_game_engine_event_handled_bit,
		_suppressed_game_engine_event_delayed_for_join_bit,
	};
}
using namespace hades_file_local;
/* ---------- definitions */

namespace hades_file_local
{
	struct s_suppressed_game_engine_event
	{
		long equeued_game_time; // 0x0
		c_flags<enum e_suppressed_game_engine_event_flags,unsigned char> flags; // 0x4
		unsigned char : 8; unsigned char : 8; unsigned char : 8; // 0x5  // hades: unnamed, so the implicit copies skip it as the original's do
		s_game_engine_event_data metadata; // 0x8
		// s_suppressed_game_engine_event(s_suppressed_game_engine_event &); /* compiler_generated(): left implicit, as the original's was */
		// s_suppressed_game_engine_event(s_suppressed_game_engine_event const &); /* compiler_generated(): left implicit, as the original's was */
		s_suppressed_game_engine_event(); /* compiler_generated() */
		// s_suppressed_game_engine_event &operator=(s_suppressed_game_engine_event &); /* compiler_generated(): left implicit, as the original's was */
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
using namespace hades_file_local; template<> c_flags<enum e_suppressed_game_engine_event_flags,unsigned char>::operator bool() const { return (bool)m_value; } // hades: the original casts, as the flags.inl specializations do
/* ---------- prototypes */

namespace Patches
{
	namespace Events
	{
		extern void ApplyAll();
		extern void OnEvent(std::function<void __cdecl(unsigned long,s_game_engine_event_data const *,s_multiplayer_event_response_definition const *)> callback);
	}
}

void RunEventHook(unsigned long player, s_game_engine_event_data const *event, s_multiplayer_event_response_definition const *definition);
bool player_has_name(long player_index);
void game_engine_update_game_events_hook();
void game_event_set_cause_player_hook(long player_index, s_game_engine_event_data *event);

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	std::vector<std::function<void __cdecl(unsigned long,s_game_engine_event_data const *,s_multiplayer_event_response_definition const *)> > OnEventCallbacks; // 0x124584AC
}
using namespace hades_file_local;
/* ---------- public code */

namespace Patches
{
	namespace Events
	{
		void ApplyAll() // 0x10A59630
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAll@Events@Patches@@YAXXZ");
			// procedure flags: nofpo

					Hook(0x16669C, RunEventHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
					Hook(0x165CE2, RunEventHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
					Hook(0x165D0D, RunEventHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
					Hook(0x165E80, game_engine_update_game_events_hook).Apply();
					Hook(0x1CEB60, game_event_set_cause_player_hook).Apply();
		}

		void OnEvent(std::function<void __cdecl(unsigned long,s_game_engine_event_data const *,s_multiplayer_event_response_definition const *)> callback) // 0x10A59B30
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OnEvent@Events@Patches@@YAXV?$function@$$A6AXKPBUs_game_engine_event_data@@PBUs_multiplayer_event_response_definition@@@Z@std@@@Z");
			// std::function<void __cdecl(unsigned long,s_game_engine_event_data const *,s_multiplayer_event_response_definition const *)> callback;

			OnEventCallbacks.push_back(callback);
		}
	}
}

// mangled_x86(MANGLED_DEFAULT, "??4s_game_engine_event_data@@QAEAAU0@ABU0@@Z"); no body to assert in
_inline s_game_engine_event_data &s_game_engine_event_data::operator=(s_game_engine_event_data const &__that) = default; // 0x10A591B0

/* ---------- private code */

void RunEventHook(unsigned long player, s_game_engine_event_data const *event, s_multiplayer_event_response_definition const *definition) // 0x10A59BD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?RunEventHook@@YAXKPBUs_game_engine_event_data@@PBUs_multiplayer_event_response_definition@@@Z");
	// `anonymous-namespace'::RunEventHook
	// s_multiplayer_event_response_definition const *definition;
	// void (*RunEvent)(unsigned long, s_game_engine_event_data const *, s_multiplayer_event_response_definition const *);
		// std::vector<std::function<void __cdecl(unsigned long,s_game_engine_event_data const *,s_multiplayer_event_response_definition const *)> > &<range>$L0;
		// std::function<void __cdecl(unsigned long,s_game_engine_event_data const *,s_multiplayer_event_response_definition const *)> *<begin>$L0;
		// std::function<void __cdecl(unsigned long,s_game_engine_event_data const *,s_multiplayer_event_response_definition const *)> *<end>$L0;
			// std::function<void __cdecl(unsigned long,s_game_engine_event_data const *,s_multiplayer_event_response_definition const *)> &callback;
	// function call : void (*)(unsigned long, s_game_engine_event_data const *, s_multiplayer_event_response_definition const *)

	for (auto &callback : OnEventCallbacks)
		callback(player, event, definition);
	void (*RunEvent)(unsigned long, s_game_engine_event_data const *, s_multiplayer_event_response_definition const *) = (void (*)(unsigned long, s_game_engine_event_data const *, s_multiplayer_event_response_definition const *))0x5666b0;
	RunEvent(player, event, definition);
}

// mangled_x86(MANGLED_DEFAULT, "??0s_suppressed_game_engine_event@hades_file_local@@QAE@XZ"); no body to assert in
_inline s_suppressed_game_engine_event::s_suppressed_game_engine_event() = default; // 0x10A58EA0

// mangled_x86(MANGLED_DEFAULT, "??0s_suppressed_game_engine_event_collection@hades_file_local@@QAE@XZ"); no body to assert in
_inline s_suppressed_game_engine_event_collection::s_suppressed_game_engine_event_collection() = default; // 0x10A58F00

bool player_has_name(long player_index) // 0x10A5B150
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?player_has_name@@YA_NJ@Z");
	// `anonymous-namespace'::player_has_name
	// long player_index;
	// s_player_datum *player;

	if (player_index == -1)
	{
		return false;
	}

	s_player_datum *player = player_get(player_index);
	return player && player->configuration.host.player_name[0];
}

_inline s_suppressed_game_engine_event &s_suppressed_game_engine_event::operator=(s_suppressed_game_engine_event const &__that) = default; // 0x10A59290

void game_engine_update_game_events_hook() // 0x10A5AAA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_engine_update_game_events_hook@@YAXXZ");
	// `anonymous-namespace'::game_engine_update_game_events_hook
	// procedure flags: nofpo
	// static ...; // 0x10A5AEEC
	// static ...; // 0x10A5AEE0
	// static ...; // 0x10A5AED8
	// constexpr void (*const `game_engine_update_game_events_hook'::`2'::game_engine_event_play)(s_game_engine_event_data const *); // constant == 5659808
	// long default_delay_ticks;
	// char *game_engine_globals;
	// long delay_for_join_in_ticks;
	// s_suppressed_game_engine_event_collection sorted_events;
	// long current_time;
	// s_suppressed_game_engine_event_collection *events;
	// long grief_time_in_ticks;
		// s_static_array<s_suppressed_game_engine_event,64> &<range>$L0;
		// s_suppressed_game_engine_event *<begin>$L0;
		// s_suppressed_game_engine_event *<end>$L0;
			// s_suppressed_game_engine_event &event;
				// long delay_for_ticks;
		// __int32 (*comparator)(void const *, void const *);
			// s_suppressed_game_engine_event *<end>$L1;
			// s_suppressed_game_engine_event *<begin>$L1;
			// s_static_array<s_suppressed_game_engine_event,64> &<range>$L1;
				// s_suppressed_game_engine_event const &sorted_event;
					// s_suppressed_game_engine_event &event;
	// function call : long (*const)()
	// function call : long (*const)(float)
	// function call : long (*const)(float)
	// function call : long (*const)(float)
	// function call : void (*const)(s_game_engine_event_data const *)

	extern long (*const game_time_get)();
	extern long (*const game_seconds_to_ticks_round)(float);
	static void (*const game_engine_event_play)(s_game_engine_event_data const *) = (void (*)(s_game_engine_event_data const *))0x565CA0;
	char *game_engine_globals = *(char **)tls_get(0x48);
	s_suppressed_game_engine_event_collection *events = (s_suppressed_game_engine_event_collection *)(game_engine_globals + 0x14C48);
	s_suppressed_game_engine_event_collection sorted_events;
	sorted_events.elements.set_memory(0);
	sorted_events.count = 0;
	long current_time = game_time_get();
	long default_delay_ticks = game_seconds_to_ticks_round(0.15f);
	long delay_for_join_in_ticks = game_seconds_to_ticks_round(2.0f);
	long grief_time_in_ticks = game_seconds_to_ticks_round(7.0f);
	for (s_suppressed_game_engine_event &event : events->elements)
	{
		if (!(event.flags & (1 << _suppressed_game_engine_event_valid_bit)))
			continue;
		if (event.flags & (1 << _suppressed_game_engine_event_handled_bit))
			continue;
		long delay_for_ticks = default_delay_ticks;
		if (event.flags & (1 << _suppressed_game_engine_event_delayed_for_join_bit))
			delay_for_ticks = delay_for_join_in_ticks;
		if (current_time > event.equeued_game_time + delay_for_ticks + grief_time_in_ticks)
		{
			event.flags &= ~(1 << _suppressed_game_engine_event_valid_bit);
			event.flags |= (1 << _suppressed_game_engine_event_handled_bit);
			continue;
		}
		if (current_time > event.equeued_game_time + delay_for_ticks)
		{
			if (event.metadata.cause_player_index != -1 && !player_has_name(event.metadata.cause_player_index))
				continue;
			if (event.metadata.effect_player_index != -1 && !player_has_name(event.metadata.effect_player_index))
				continue;
			sorted_events.elements[sorted_events.count++] = event;
		}
	}
	if (sorted_events.count > 0)
	{
		__int32 (*comparator)(void const *, void const *) = (__int32 (*)(void const *, void const *))0x565D20;
		qsort(&sorted_events.elements, sorted_events.count, sizeof(s_suppressed_game_engine_event), comparator);
		for (s_suppressed_game_engine_event const &sorted_event : sorted_events.elements)
		{
			game_engine_event_play(&sorted_event.metadata);
			s_suppressed_game_engine_event &event = events->elements[sorted_event.metadata.index];
			event.flags &= ~(1 << _suppressed_game_engine_event_valid_bit);
			event.flags |= (1 << _suppressed_game_engine_event_handled_bit);
		}
	}
}

void game_event_set_cause_player_hook(long player_index, s_game_engine_event_data *event) // 0x10A5B010
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_event_set_cause_player_hook@@YAXJPAUs_game_engine_event_data@@@Z");
	// `anonymous-namespace'::game_event_set_cause_player_hook
	// s_game_engine_event_data *event;
	// s_player_datum *player;

	event->cause_player_index = -1;
	event->cause_team_index = -1;

	s_player_datum *player = player_get(player_index);
	if (!player)
		return;

	event->cause_player_index = player_index;
	event->cause_team_index = player->configuration.host.team;
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template c_enum<enum e_game_engine_event_type,char> & c_enum<enum e_game_engine_event_type,char>::operator=(c_enum<enum e_game_engine_event_type,char> const &);
template c_flags<enum e_suppressed_game_engine_event_flags,unsigned char> & c_flags<enum e_suppressed_game_engine_event_flags,unsigned char>::operator&=(__int32 const);
template c_flags<enum e_suppressed_game_engine_event_flags,unsigned char> & c_flags<enum e_suppressed_game_engine_event_flags,unsigned char>::operator=(c_flags<enum e_suppressed_game_engine_event_flags,unsigned char> const &);
template c_flags<enum e_suppressed_game_engine_event_flags,unsigned char> & c_flags<enum e_suppressed_game_engine_event_flags,unsigned char>::operator|=(__int32 const);
template c_flags<enum e_suppressed_game_engine_event_flags,unsigned char> c_flags<enum e_suppressed_game_engine_event_flags,unsigned char>::operator&(__int32 const) const;
template c_flags<enum e_suppressed_game_engine_event_flags,unsigned char>::c_flags();
template c_flags<enum e_suppressed_game_engine_event_flags,unsigned char>::c_flags(unsigned char const &);
// template c_flags<enum e_suppressed_game_engine_event_flags,unsigned char>::operator bool() const; // hades: specialized after the type definitions

/* ---------- explicit instantiations */
template s_static_array<s_suppressed_game_engine_event,64>::s_static_array();
template s_suppressed_game_engine_event * s_static_array<s_suppressed_game_engine_event,64>::begin() const;
template s_suppressed_game_engine_event * s_static_array<s_suppressed_game_engine_event,64>::end() const;
