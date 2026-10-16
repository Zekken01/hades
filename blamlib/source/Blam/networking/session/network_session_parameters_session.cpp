/* ---------- headers */

#include "Blam/networking/session/network_session_parameters_session.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/networking/session/network_session_parameters_base.hpp"

/* ---------- forward declarations */

class c_network_session_parameter_session_size;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

long c_network_session_parameter_session_size::get_max_player_count() const // 0x10F1D420
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_max_player_count@c_network_session_parameter_session_size@@QBEJXZ");

	if (get_allowed())
	{
		return m_data.max_player_count;
	}
	else
	{
		return 16;
	}
}

/* ---------- private code */
