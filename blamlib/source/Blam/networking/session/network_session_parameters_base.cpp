/* ---------- headers */

#include "Blam/networking/session/network_session_parameters_base.hpp"
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
#include "Blam/memory/static_array.inl"
#include "Blam/networking/session/network_session.hpp"
#include "Blam/networking/session/network_session_membership.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"

/* ---------- forward declarations */

class c_network_session_parameter_base;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

_extern void _sub_10F1F160(c_network_session_parameter_base *const);
void c_network_session_parameter_base::set_update_required() // 0x10F1F160
{
	mangled_x86(MANGLED_TODO, "?set_update_required@c_network_session_parameter_base@@IAEXXZ");
	// c_network_session_parameter_base *const this;
	// function call : void ()
	todo("implement");
	_sub_10F1F160(this);
}

_extern bool _sub_10F1F040(c_network_session_parameter_base const *const);
bool c_network_session_parameter_base::get_allowed() const // 0x10F1F040
{
	mangled_x86(MANGLED_TODO, "?get_allowed@c_network_session_parameter_base@@QBE_NXZ");
	// c_network_session_parameter_base const *const this;
	todo("implement");
	bool __result = _sub_10F1F040((c_network_session_parameter_base const *)this);
	return __result;
}

bool c_network_session_parameter_base::set_allowed() const // 0x10F1F0C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_allowed@c_network_session_parameter_base@@QBE_NXZ");
	// c_network_session_parameter_base const *const this;

	return m_session->established() && m_session->is_host();
}

/* ---------- private code */

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template c_flags<enum e_network_session_parameter_base_flags,unsigned char> & c_flags<enum e_network_session_parameter_base_flags,unsigned char>::operator|=(__int32 const);
template c_flags<enum e_network_session_parameter_base_flags,unsigned char> c_flags<enum e_network_session_parameter_base_flags,unsigned char>::operator&(__int32 const) const;
template c_flags<enum e_network_session_parameter_base_flags,unsigned char>::c_flags(unsigned char const &);
template c_flags<enum e_network_session_parameter_base_flags,unsigned char>::operator bool() const;
