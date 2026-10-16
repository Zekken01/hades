/* ---------- headers */

#include "Blam/networking/session/network_session_membership.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/static_array.inl"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"

/* ---------- forward declarations */

class c_network_session_membership;
struct s_network_session_peer;
struct s_network_session_player;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

bool c_network_session_membership::is_leader() const // 0x10F00BB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?is_leader@c_network_session_membership@@QBE_NXZ");

	return has_membership() && ((s_network_session_shared_membership const *)m_shared_network_membership)->leader_peer_index == m_local_peer_index;
}

bool c_network_session_membership::is_peer_valid(long peer_index) const // 0x10F00C50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?is_peer_valid@c_network_session_membership@@QBE_NJ@Z");

	return (((s_network_session_shared_membership const *)m_shared_network_membership)->peer_valid_mask >> peer_index) & 1;
}

bool c_network_session_membership::is_player_valid(long player_index) const // 0x10F00CC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?is_player_valid@c_network_session_membership@@QBE_NJ@Z");

	return (((s_network_session_shared_membership const *)m_shared_network_membership)->player_valid_mask >> player_index) & 1;
}

#line 64
s_network_session_player *c_network_session_membership::get_player(long player_index) // 0x10F00B00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_player@c_network_session_membership@@QAEPAUs_network_session_player@@J@Z");
	// long player_index;

	#line 66 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\blamlib\\source\\blam\\networking\\session\\network_session_membership.cpp"
		if (!(is_player_valid(player_index))) { display_assert("is_player_valid(player_index)", __FILE__, __LINE__, true); system_exit(-1); }
		#line 72 "F:\\Project Hades\\Hades\\Source\\blamlib\\source\\Blam\\networking\\session\\network_session_membership.cpp"
	return &((s_network_session_shared_membership *)m_shared_network_membership)->players[player_index];
}

s_network_session_peer *c_network_session_membership::get_peer(long peer_index) // 0x10F00A50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_peer@c_network_session_membership@@QAEPAUs_network_session_peer@@J@Z");
	// long peer_index;

	#line 77 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\blamlib\\source\\blam\\networking\\session\\network_session_membership.cpp"
		if (!(is_peer_valid(peer_index))) { display_assert("is_peer_valid(peer_index)", __FILE__, __LINE__, true); system_exit(-1); }
		#line 83 "F:\\Project Hades\\Hades\\Source\\blamlib\\source\\Blam\\networking\\session\\network_session_membership.cpp"
	return &((s_network_session_shared_membership *)m_shared_network_membership)->peers[peer_index];
}

s_network_session_peer *c_network_session_membership::get_local_peer() // 0x10F008D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_local_peer@c_network_session_membership@@QAEPAUs_network_session_peer@@XZ");
	// c_network_session_membership *const this;

	#line 88 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\blamlib\\source\\blam\\networking\\session\\network_session_membership.cpp"
		if (!(is_peer_valid(m_local_peer_index))) { display_assert("is_peer_valid(m_local_peer_index)", __FILE__, __LINE__, true); system_exit(-1); }
		#line 94 "F:\\Project Hades\\Hades\\Source\\blamlib\\source\\Blam\\networking\\session\\network_session_membership.cpp"
	return get_peer(m_local_peer_index);
}

long c_network_session_membership::get_channel_index(long peer_index) const // 0x10F00780
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_channel_index@c_network_session_membership@@QBEJJ@Z");
	// long peer_index;

	#line 99 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\blamlib\\source\\blam\\networking\\session\\network_session_membership.cpp"
		if (!(is_peer_valid(peer_index))) { display_assert("is_peer_valid(peer_index)", __FILE__, __LINE__, true); system_exit(-1); }
		#line 105 "F:\\Project Hades\\Hades\\Source\\blamlib\\source\\Blam\\networking\\session\\network_session_membership.cpp"
	return (*(s_static_array<s_network_session_peer_channel,17> const *)m_peer_channels)[peer_index].channel_index;
}

long c_network_session_membership::get_first_peer() // 0x10F00840
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_first_peer@c_network_session_membership@@QAEJXZ");

	for (long index = 0; index < 17; index++)
	{
		if (is_peer_valid(index))
			return index;
	}

	return -1;
}

#line 123
long c_network_session_membership::get_next_peer(long peer_index) // 0x10F00980
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_next_peer@c_network_session_membership@@QAEJJ@Z");
	// long peer_index;
		// long index;

	#line 125 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\blamlib\\source\\blam\\networking\\session\\network_session_membership.cpp"
		if (!(peer_index != -1)) { display_assert("peer_index != NONE", __FILE__, __LINE__, true); system_exit(-1); }
		#line 132 "F:\\Project Hades\\Hades\\Source\\blamlib\\source\\Blam\\networking\\session\\network_session_membership.cpp"
	for (long next_peer_index = peer_index + 1; next_peer_index < 17; next_peer_index++)
	{
		if (is_peer_valid(next_peer_index))
		{
			return next_peer_index;
		}
	}

	return -1;
}

/* ---------- private code */

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool s_static_array<s_network_session_peer_channel,17>::valid(__int32);
template s_network_session_peer_channel const & s_static_array<s_network_session_peer_channel,17>::operator[](long) const;
