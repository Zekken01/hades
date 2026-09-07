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

_extern bool _sub_10F00BB0(c_network_session_membership const *const);
bool c_network_session_membership::is_leader() const // 0x10F00BB0
{
	mangled_x86(MANGLED_TODO, "?is_leader@c_network_session_membership@@QBE_NXZ");
	// c_network_session_membership const *const this;
	todo("implement");
	bool __result = _sub_10F00BB0((c_network_session_membership const *)this);
	return __result;
}

_extern bool _sub_10F00C50(c_network_session_membership const *const, long);
bool c_network_session_membership::is_peer_valid(long peer_index) const // 0x10F00C50
{
	mangled_x86(MANGLED_TODO, "?is_peer_valid@c_network_session_membership@@QBE_NJ@Z");
	// long peer_index;
	todo("implement");
	bool __result = _sub_10F00C50((c_network_session_membership const *)this, peer_index);
	return __result;
}

_extern bool _sub_10F00CC0(c_network_session_membership const *const, long);
bool c_network_session_membership::is_player_valid(long player_index) const // 0x10F00CC0
{
	mangled_x86(MANGLED_TODO, "?is_player_valid@c_network_session_membership@@QBE_NJ@Z");
	// long player_index;
	todo("implement");
	bool __result = _sub_10F00CC0((c_network_session_membership const *)this, player_index);
	return __result;
}

extern s_network_session_player *_sub_10F00B00(c_network_session_membership *const, long);
s_network_session_player *c_network_session_membership::get_player(long player_index) // 0x10F00B00
{
	mangled_x86(MANGLED_TODO, "?get_player@c_network_session_membership@@QAEPAUs_network_session_player@@J@Z");
	// long player_index;
	todo("implement");
	s_network_session_player * __result = _sub_10F00B00(this, player_index);
	return __result;
}

extern s_network_session_peer *_sub_10F00A50(c_network_session_membership *const, long);
s_network_session_peer *c_network_session_membership::get_peer(long peer_index) // 0x10F00A50
{
	mangled_x86(MANGLED_TODO, "?get_peer@c_network_session_membership@@QAEPAUs_network_session_peer@@J@Z");
	// long peer_index;
	todo("implement");
	s_network_session_peer * __result = _sub_10F00A50(this, peer_index);
	return __result;
}

extern s_network_session_peer *_sub_10F008D0(c_network_session_membership *const);
s_network_session_peer *c_network_session_membership::get_local_peer() // 0x10F008D0
{
	mangled_x86(MANGLED_TODO, "?get_local_peer@c_network_session_membership@@QAEPAUs_network_session_peer@@XZ");
	// c_network_session_membership *const this;
	todo("implement");
	s_network_session_peer * __result = _sub_10F008D0(this);
	return __result;
}

_extern long _sub_10F00780(c_network_session_membership const *const, long);
long c_network_session_membership::get_channel_index(long peer_index) const // 0x10F00780
{
	mangled_x86(MANGLED_TODO, "?get_channel_index@c_network_session_membership@@QBEJJ@Z");
	// long peer_index;
	todo("implement");
	long __result = _sub_10F00780((c_network_session_membership const *)this, peer_index);
	return __result;
}

_extern long _sub_10F00840(c_network_session_membership *const);
long c_network_session_membership::get_first_peer() // 0x10F00840
{
	mangled_x86(MANGLED_TODO, "?get_first_peer@c_network_session_membership@@QAEJXZ");
	// c_network_session_membership *const this;
	{
		// long index;
	}
	todo("implement");
	long __result = _sub_10F00840(this);
	return __result;
}

_extern long _sub_10F00980(c_network_session_membership *const, long);
long c_network_session_membership::get_next_peer(long peer_index) // 0x10F00980
{
	mangled_x86(MANGLED_TODO, "?get_next_peer@c_network_session_membership@@QAEJJ@Z");
	// long peer_index;
	{
		// long index;
	}
	todo("implement");
	long __result = _sub_10F00980(this, peer_index);
	return __result;
}

/* ---------- private code */

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool s_static_array<s_network_session_peer_channel,17>::valid(__int32);
template s_network_session_peer_channel const & s_static_array<s_network_session_peer_channel,17>::operator[](long) const;
