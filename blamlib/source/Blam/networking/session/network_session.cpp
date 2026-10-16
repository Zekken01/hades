/* ---------- headers */

#include "Blam/networking/session/network_session.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/networking/session/network_session_membership.hpp"
#include "Blam/networking/session/network_session_parameters.hpp"
#include "Blam/networking/session/network_session_parameters_base.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"

/* ---------- forward declarations */

class c_network_session;
class c_network_session_membership;
class c_network_session_parameters;
class c_network_observer;
struct s_network_session_peer;
struct s_network_session_player;
struct s_transport_secure_identifier;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

bool c_network_session::established() const // 0x10EF7BE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?established@c_network_session@@QBE_NXZ");

	return current_local_state() >= _network_session_state_peer_peer_established;
}

bool c_network_session::disconnected() const // 0x10EF7B50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?disconnected@c_network_session@@QBE_NXZ");

	return current_local_state() == static_cast<e_network_session_state>(0);
}

bool c_network_session::is_host() const // 0x10EF8620
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?is_host@c_network_session@@QBE_NXZ");

	e_network_session_state state = current_local_state();

	return state == _network_session_state_host_host_established || state == _network_session_state_host_disband;
}

bool c_network_session::is_leader() const // 0x10EF86C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?is_leader@c_network_session@@QBE_NXZ");

	return m_session_membership.is_leader();
}

#line 83
long c_network_session::get_session_membership_update_number() const // 0x10EF8480
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_session_membership_update_number@c_network_session@@QBEJXZ");
	// c_network_session const *const this;

	#line 85 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\blamlib\\source\\blam\\networking\\session\\network_session.cpp"
		if (!(established())) { display_assert("established()", __FILE__, __LINE__, true); system_exit(-1); }
		if (!(m_session_membership.has_membership())) { display_assert("m_session_membership.has_membership()", __FILE__, __LINE__, true); system_exit(-1); }
		#line 92 "F:\\Project Hades\\Hades\\Source\\blamlib\\source\\Blam\\networking\\session\\network_session.cpp"
	return m_session_membership.update_number();
}

c_network_session_membership *c_network_session::get_session_membership() // 0x10EF81F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_session_membership@c_network_session@@QAEPAVc_network_session_membership@@XZ");
	// c_network_session *const this;

	#line 97 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\blamlib\\source\\blam\\networking\\session\\network_session.cpp"
		if (!(established())) { display_assert("established()", __FILE__, __LINE__, true); system_exit(-1); }
		if (!(m_session_membership.has_membership())) { display_assert("m_session_membership.has_membership()", __FILE__, __LINE__, true); system_exit(-1); }
		if (!(m_session_membership.is_peer_valid(m_session_membership.local_peer_index()))) { display_assert("m_session_membership.is_peer_valid(m_session_membership.local_peer_index())", __FILE__, __LINE__, true); system_exit(-1); }
		if (!(m_session_membership.is_peer_valid(m_session_membership.host_peer_index()))) { display_assert("m_session_membership.is_peer_valid(m_session_membership.host_peer_index())", __FILE__, __LINE__, true); system_exit(-1); }
		#line 106 "F:\\Project Hades\\Hades\\Source\\blamlib\\source\\Blam\\networking\\session\\network_session.cpp"
	return &m_session_membership;
}

c_network_session_membership const *c_network_session::get_session_membership_unsafe() const // 0x10EF8390
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_session_membership_unsafe@c_network_session@@QBEPBVc_network_session_membership@@XZ");

	if (established() && m_session_membership.has_membership() && m_session_membership.is_peer_valid(m_session_membership.local_peer_index()) && m_session_membership.is_peer_valid(m_session_membership.host_peer_index()))
	{
		return &m_session_membership;
	}
	return nullptr;
}

bool c_network_session::membership_is_locked() const // 0x10EF8780
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?membership_is_locked@c_network_session@@QBE_NXZ");

	return current_local_state() == _network_session_state_host_disband;
}

c_network_session_parameters *c_network_session::get_session_parameters() // 0x10EF8560
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_session_parameters@c_network_session@@QAEPAVc_network_session_parameters@@XZ");

	return (c_network_session_parameters *)m_session_parameters;
}

c_network_session_parameters const *c_network_session::get_session_parameters() const // 0x10EF85C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_session_parameters@c_network_session@@QBEPBVc_network_session_parameters@@XZ");

	return (c_network_session_parameters const *)m_session_parameters;
}

c_network_observer *c_network_session::get_observer() // 0x10EF7DF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_observer@c_network_session@@QAEPAVc_network_observer@@XZ");

	return (c_network_observer *)m_observer;
}

c_network_observer const *c_network_session::get_observer() const // 0x10EF7E50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_observer@c_network_session@@QBEPBVc_network_observer@@XZ");

	return (c_network_observer const *)m_observer;
}

bool c_network_session::get_session_id(s_transport_secure_identifier *identifier) const // 0x10EF8140
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_session_id@c_network_session@@QBE_NPAUs_transport_secure_identifier@@@Z");

	unsigned char *managed_sessions = (unsigned char *)0x2247818;

	if (m_managed_session_index == -1)
	{
		return false;
	}

	*identifier = *(s_transport_secure_identifier *)(managed_sessions + 1544 * m_managed_session_index);
	return true;
}

long c_network_session::get_player_count() const // 0x10EF80E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_player_count@c_network_session@@QBEJXZ");

	return m_session_membership.get_player_count();
}

#line 186
s_network_session_player *c_network_session::get_player(long player_index) // 0x10EF8020
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_player@c_network_session@@QAEPAUs_network_session_player@@J@Z");
	// long player_index;

	#line 188 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\blamlib\\source\\blam\\networking\\session\\network_session.cpp"
		if (!(!disconnected())) { display_assert("!disconnected()", __FILE__, __LINE__, true); system_exit(-1); }
		#line 194 "F:\\Project Hades\\Hades\\Source\\blamlib\\source\\Blam\\networking\\session\\network_session.cpp"
	return m_session_membership.get_player(player_index);
}

long c_network_session::get_peer_channel_index(long peer_index) const // 0x10EF7F30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_peer_channel_index@c_network_session@@QBEJJ@Z");
	// long peer_index;

	#line 199 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\blamlib\\source\\blam\\networking\\session\\network_session.cpp"
		if (!(established())) { display_assert("established()", __FILE__, __LINE__, true); system_exit(-1); }
		#line 205 "F:\\Project Hades\\Hades\\Source\\blamlib\\source\\Blam\\networking\\session\\network_session.cpp"
	if (m_session_membership.is_peer_valid(peer_index))
	{
		return m_session_membership.get_channel_index(peer_index);
	}

	return -1;
}

s_network_session_peer *c_network_session::get_peer(long peer_index) // 0x10EF7EB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_peer@c_network_session@@QAEPAUs_network_session_peer@@J@Z");

	return m_session_membership.get_peer(peer_index);
}

long c_network_session::get_maximum_player_count() const // 0x10EF7D80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_maximum_player_count@c_network_session@@QBEJXZ");

	return get_session_parameters()->session_size.get_max_player_count();
}

#line 229
void c_network_session::boot_peer(long peer_index, e_network_session_boot_reason reason) // 0x10EF78E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?boot_peer@c_network_session@@QAEXJW4e_network_session_boot_reason@@@Z");
	// e_network_session_boot_reason reason;
	// constexpr bool (*const `c_network_session::boot_peer'::`2'::c_network_session__boot_peer)(c_network_session *, __int32, e_network_session_boot_reason); // constant == 4564160
	// function call : bool (*const)(c_network_session *, __int32, e_network_session_boot_reason)

	#line 231 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\blamlib\\source\\blam\\networking\\session\\network_session.cpp"
		if (!(established() && is_host())) { display_assert("established() && is_host()", __FILE__, __LINE__, true); system_exit(-1); }
		#line 239 "F:\\Project Hades\\Hades\\Source\\blamlib\\source\\Blam\\networking\\session\\network_session.cpp"
	((void (__thiscall *const)(c_network_session *, long, e_network_session_boot_reason))0x45A4C0)(this, peer_index, reason);
}

void c_network_session::boot_player(long player_index, e_network_session_boot_reason reason) // 0x10EF79B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?boot_player@c_network_session@@QAEXJW4e_network_session_boot_reason@@@Z");
	// e_network_session_boot_reason reason;
	// s_network_session_player *player;

	#line 244 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\blamlib\\source\\blam\\networking\\session\\network_session.cpp"
		if (!(established() && is_host())) { display_assert("established() && is_host()", __FILE__, __LINE__, true); system_exit(-1); }
		if (!(m_session_membership.is_player_valid(player_index))) { display_assert("m_session_membership.is_player_valid(player_index)", __FILE__, __LINE__, true); system_exit(-1); }
		#line 252 "F:\\Project Hades\\Hades\\Source\\blamlib\\source\\Blam\\networking\\session\\network_session.cpp"
	s_network_session_player *player = get_player(player_index);
	boot_peer(player->peer_index, reason);
}

long c_network_session_membership::find_first_player() // 0x10EF7C70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?find_first_player@c_network_session_membership@@QAEJXZ");

	return find_next_player(-1);
}

long c_network_session_membership::find_next_player(long previous_player_index) // 0x10EF7CD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?find_next_player@c_network_session_membership@@QAEJJ@Z");

	if (previous_player_index + 1 >= 16)
	{
		return -1;
	}

	long index = previous_player_index + 1;

	while (!is_player_valid(index))
	{
		index++;

		if (index >= 16)
		{
			return -1;
		}
	}

	return index;
}

/* ---------- private code */

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

c_enum<enum e_network_session_state,unsigned char> c_network_session::current_local_state() const // 0x10EF7AE0
{

	return m_local_state;
}

template bool c_enum<enum e_network_session_state,unsigned char>::operator==(e_network_session_state const &) const;
template bool c_enum<enum e_network_session_state,unsigned char>::operator>=(e_network_session_state const &) const;
template c_enum<enum e_network_session_state,unsigned char>::c_enum(c_enum<enum e_network_session_state,unsigned char> const &);
template c_enum<enum e_network_session_state,unsigned char>::c_enum(unsigned char const &);
template c_enum<enum e_network_session_state,unsigned char>::operator enum e_network_session_state() const;
