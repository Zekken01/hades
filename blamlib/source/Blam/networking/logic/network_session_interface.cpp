/* ---------- headers */

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
#include "Blam/networking/session/network_session.hpp"
#include "Blam/networking/session/network_session_membership.hpp"
#include "Blam/networking/session/network_session_parameter_mod.hpp"
#include "Blam/networking/session/network_session_parameters.hpp"
#include "Blam/networking/session/network_session_parameters_base.hpp"
#include "Blam/networking/session/network_session_parameters_custom.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"

/* ---------- forward declarations */

class c_network_session;
class c_network_session_parameter_base;
class c_network_session_parameters;
struct s_session_mod_options;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace eldorado
{
	// Functions in eldorado.exe, named as in ManagedDonkey.
	static auto const network_life_cycle_in_squad_session = reinterpret_cast<bool (*)(c_network_session **)>(0x454F20);
}

extern bool network_squad_session_set_mod(s_session_mod_options const *options);
extern s_session_mod_options const *network_squad_session_get_mod();

/* ---------- globals */

extern bool (*const network_session_interface_get_squad_session)(c_network_session **); // 0x11248780

/* ---------- private variables */

/* ---------- public code */

bool network_squad_session_set_mod(s_session_mod_options const *options) // 0x10EF8920
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?network_squad_session_set_mod@@YA_NPBUs_session_mod_options@@@Z");
	// static ...; // 0x10EF89EC
	// static ...; // 0x10EF89E0
	// static ...; // 0x10EF89D8
	// s_session_mod_options const *options;
	// c_network_session_parameter_base *session_paramerer;
	// c_network_session_parameters *session_parameters;
	// c_network_session *session;
	// function call : bool (*const)(c_network_session **)

	c_network_session *session;
	if (!eldorado::network_life_cycle_in_squad_session(&session))
	{
		return false;
	}

	c_network_session_parameters *session_parameters = session->get_session_parameters();
	if (!session_parameters)
	{
		return false;
	}

	c_network_session_parameter_base *session_paramerer = session_parameters->parameters[4];
	return ((c_network_session_parameter_mod *)session_paramerer)->request_change(options);
}

s_session_mod_options const *network_squad_session_get_mod() // 0x10EF8810
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?network_squad_session_get_mod@@YAPBUs_session_mod_options@@XZ");
	// procedure flags: nofpo
	// static ...; // 0x10EF88D8
	// static ...; // 0x10EF88CC
	// static ...; // 0x10EF88C4
	// c_network_session_parameter_base *session_paramerer;
	// c_network_session_parameters *session_parameters;
	// c_network_session *session;
	// function call : bool (*const)(c_network_session **)

	c_network_session *session;
	if (!eldorado::network_life_cycle_in_squad_session(&session))
	{
		return nullptr;
	}

	c_network_session_parameters *session_parameters = session->get_session_parameters();
	if (!session_parameters)
	{
		return nullptr;
	}

	c_network_session_parameter_base *session_paramerer = session_parameters->parameters[4];
	return ((c_network_session_parameter_mod *)session_paramerer)->get();
}

/* ---------- private code */

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
bool (*const network_session_interface_get_squad_session)(c_network_session **) = reinterpret_cast<decltype(network_session_interface_get_squad_session)>(0x454F20);
