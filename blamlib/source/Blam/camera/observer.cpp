/* ---------- headers */

#include "Blam/camera/observer.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/tls.hpp"
#include "Blam/structures/cluster_reference.hpp"

/* ---------- forward declarations */

struct s_observer;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern s_observer *observer_get(long output_user_index);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

s_observer *observer_get(long output_user_index) // 0x10F19300
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?observer_get@@YAPAUs_observer@@J@Z");
	// long output_user_index;

	return &tls_getd().observer_globals->observers[output_user_index];
}

/* ---------- private code */
