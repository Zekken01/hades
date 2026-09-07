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

_extern bool _sub_10EF7BE0(c_network_session const *const);
bool c_network_session::established() const // 0x10EF7BE0
{
	mangled_x86(MANGLED_TODO, "?established@c_network_session@@QBE_NXZ");
	// c_network_session const *const this;
	todo("implement");
	bool __result = _sub_10EF7BE0((c_network_session const *)this);
	return __result;
}

_extern bool _sub_10EF7B50(c_network_session const *const);
bool c_network_session::disconnected() const // 0x10EF7B50
{
	mangled_x86(MANGLED_TODO, "?disconnected@c_network_session@@QBE_NXZ");
	// c_network_session const *const this;
	todo("implement");
	bool __result = _sub_10EF7B50((c_network_session const *)this);
	return __result;
}

_extern bool _sub_10EF8620(c_network_session const *const);
bool c_network_session::is_host() const // 0x10EF8620
{
	mangled_x86(MANGLED_TODO, "?is_host@c_network_session@@QBE_NXZ");
	// c_network_session const *const this;
	// e_network_session_state state;
	todo("implement");
	bool __result = _sub_10EF8620((c_network_session const *)this);
	return __result;
}

_extern bool _sub_10EF86C0(c_network_session const *const);
bool c_network_session::is_leader() const // 0x10EF86C0
{
	mangled_x86(MANGLED_TODO, "?is_leader@c_network_session@@QBE_NXZ");
	// c_network_session const *const this;
	todo("implement");
	bool __result = _sub_10EF86C0((c_network_session const *)this);
	return __result;
}

_extern long _sub_10EF8480(c_network_session const *const);
long c_network_session::get_session_membership_update_number() const // 0x10EF8480
{
	mangled_x86(MANGLED_TODO, "?get_session_membership_update_number@c_network_session@@QBEJXZ");
	// c_network_session const *const this;
	todo("implement");
	long __result = _sub_10EF8480((c_network_session const *)this);
	return __result;
}

extern c_network_session_membership *_sub_10EF81F0(c_network_session *const);
c_network_session_membership *c_network_session::get_session_membership() // 0x10EF81F0
{
	mangled_x86(MANGLED_TODO, "?get_session_membership@c_network_session@@QAEPAVc_network_session_membership@@XZ");
	// c_network_session *const this;
	todo("implement");
	c_network_session_membership * __result = _sub_10EF81F0(this);
	return __result;
}

extern c_network_session_membership const *_sub_10EF8390(c_network_session const *const);
c_network_session_membership const *c_network_session::get_session_membership_unsafe() const // 0x10EF8390
{
	mangled_x86(MANGLED_TODO, "?get_session_membership_unsafe@c_network_session@@QBEPBVc_network_session_membership@@XZ");
	// c_network_session const *const this;
	todo("implement");
	c_network_session_membership const * __result = _sub_10EF8390((c_network_session const *)this);
	return __result;
}

_extern bool _sub_10EF8780(c_network_session const *const);
bool c_network_session::membership_is_locked() const // 0x10EF8780
{
	mangled_x86(MANGLED_TODO, "?membership_is_locked@c_network_session@@QBE_NXZ");
	// c_network_session const *const this;
	todo("implement");
	bool __result = _sub_10EF8780((c_network_session const *)this);
	return __result;
}

extern c_network_session_parameters *_sub_10EF8560(c_network_session *const);
c_network_session_parameters *c_network_session::get_session_parameters() // 0x10EF8560
{
	mangled_x86(MANGLED_TODO, "?get_session_parameters@c_network_session@@QAEPAVc_network_session_parameters@@XZ");
	// c_network_session *const this;
	todo("implement");
	c_network_session_parameters * __result = _sub_10EF8560(this);
	return __result;
}

extern c_network_session_parameters const *_sub_10EF85C0(c_network_session const *const);
c_network_session_parameters const *c_network_session::get_session_parameters() const // 0x10EF85C0
{
	mangled_x86(MANGLED_TODO, "?get_session_parameters@c_network_session@@QBEPBVc_network_session_parameters@@XZ");
	// c_network_session const *const this;
	todo("implement");
	c_network_session_parameters const * __result = _sub_10EF85C0((c_network_session const *)this);
	return __result;
}

extern c_network_observer *_sub_10EF7DF0(c_network_session *const);
c_network_observer *c_network_session::get_observer() // 0x10EF7DF0
{
	mangled_x86(MANGLED_TODO, "?get_observer@c_network_session@@QAEPAVc_network_observer@@XZ");
	// c_network_session *const this;
	todo("implement");
	c_network_observer * __result = _sub_10EF7DF0(this);
	return __result;
}

extern c_network_observer const *_sub_10EF7E50(c_network_session const *const);
c_network_observer const *c_network_session::get_observer() const // 0x10EF7E50
{
	mangled_x86(MANGLED_TODO, "?get_observer@c_network_session@@QBEPBVc_network_observer@@XZ");
	// c_network_session const *const this;
	todo("implement");
	c_network_observer const * __result = _sub_10EF7E50((c_network_session const *)this);
	return __result;
}

_extern bool _sub_10EF8140(c_network_session const *const, s_transport_secure_identifier *);
bool c_network_session::get_session_id(s_transport_secure_identifier *identifier) const // 0x10EF8140
{
	mangled_x86(MANGLED_TODO, "?get_session_id@c_network_session@@QBE_NPAUs_transport_secure_identifier@@@Z");
	// s_transport_secure_identifier *identifier;
	// char const *g_managed_sessions;
	todo("implement");
	bool __result = _sub_10EF8140((c_network_session const *)this, identifier);
	return __result;
}

_extern long _sub_10EF80E0(c_network_session const *const);
long c_network_session::get_player_count() const // 0x10EF80E0
{
	mangled_x86(MANGLED_TODO, "?get_player_count@c_network_session@@QBEJXZ");
	// c_network_session const *const this;
	todo("implement");
	long __result = _sub_10EF80E0((c_network_session const *)this);
	return __result;
}

extern s_network_session_player *_sub_10EF8020(c_network_session *const, long);
s_network_session_player *c_network_session::get_player(long player_index) // 0x10EF8020
{
	mangled_x86(MANGLED_TODO, "?get_player@c_network_session@@QAEPAUs_network_session_player@@J@Z");
	// long player_index;
	todo("implement");
	s_network_session_player * __result = _sub_10EF8020(this, player_index);
	return __result;
}

_extern long _sub_10EF7F30(c_network_session const *const, long);
long c_network_session::get_peer_channel_index(long peer_index) const // 0x10EF7F30
{
	mangled_x86(MANGLED_TODO, "?get_peer_channel_index@c_network_session@@QBEJJ@Z");
	// long peer_index;
	todo("implement");
	long __result = _sub_10EF7F30((c_network_session const *)this, peer_index);
	return __result;
}

extern s_network_session_peer *_sub_10EF7EB0(c_network_session *const, long);
s_network_session_peer *c_network_session::get_peer(long peer_index) // 0x10EF7EB0
{
	mangled_x86(MANGLED_TODO, "?get_peer@c_network_session@@QAEPAUs_network_session_peer@@J@Z");
	// long peer_index;
	todo("implement");
	s_network_session_peer * __result = _sub_10EF7EB0(this, peer_index);
	return __result;
}

_extern long _sub_10EF7D80(c_network_session const *const);
long c_network_session::get_maximum_player_count() const // 0x10EF7D80
{
	mangled_x86(MANGLED_TODO, "?get_maximum_player_count@c_network_session@@QBEJXZ");
	// c_network_session const *const this;
	todo("implement");
	long __result = _sub_10EF7D80((c_network_session const *)this);
	return __result;
}

_extern void _sub_10EF78E0(c_network_session *const, long, e_network_session_boot_reason);
void c_network_session::boot_peer(long peer_index, e_network_session_boot_reason reason) // 0x10EF78E0
{
	mangled_x86(MANGLED_TODO, "?boot_peer@c_network_session@@QAEXJW4e_network_session_boot_reason@@@Z");
	// e_network_session_boot_reason reason;
	// constexpr bool (*const `c_network_session::boot_peer'::`2'::c_network_session__boot_peer)(c_network_session *, __int32, e_network_session_boot_reason); // constant == 4564160
	// function call : bool (*const)(c_network_session *, __int32, e_network_session_boot_reason)
	todo("implement");
	_sub_10EF78E0(this, peer_index, reason);
}

_extern void _sub_10EF79B0(c_network_session *const, long, e_network_session_boot_reason);
void c_network_session::boot_player(long player_index, e_network_session_boot_reason reason) // 0x10EF79B0
{
	mangled_x86(MANGLED_TODO, "?boot_player@c_network_session@@QAEXJW4e_network_session_boot_reason@@@Z");
	// e_network_session_boot_reason reason;
	// s_network_session_player *player;
	todo("implement");
	_sub_10EF79B0(this, player_index, reason);
}

_extern long _sub_10EF7C70(c_network_session_membership *const);
long c_network_session_membership::find_first_player() // 0x10EF7C70
{
	mangled_x86(MANGLED_TODO, "?find_first_player@c_network_session_membership@@QAEJXZ");
	// c_network_session_membership *const this;
	todo("implement");
	long __result = _sub_10EF7C70(this);
	return __result;
}

_extern long _sub_10EF7CD0(c_network_session_membership *const, long);
long c_network_session_membership::find_next_player(long previous_player_index) // 0x10EF7CD0
{
	mangled_x86(MANGLED_TODO, "?find_next_player@c_network_session_membership@@QAEJJ@Z");
	// long previous_player_index;
	// long index;
	todo("implement");
	long __result = _sub_10EF7CD0(this, previous_player_index);
	return __result;
}

/* ---------- private code */

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_enum<enum e_network_session_state,unsigned char>::operator==(e_network_session_state const &) const;
template bool c_enum<enum e_network_session_state,unsigned char>::operator>=(e_network_session_state const &) const;
template c_enum<enum e_network_session_state,unsigned char>::c_enum(c_enum<enum e_network_session_state,unsigned char> const &);
template c_enum<enum e_network_session_state,unsigned char>::c_enum(unsigned char const &);
template c_enum<enum e_network_session_state,unsigned char>::operator enum e_network_session_state() const;
