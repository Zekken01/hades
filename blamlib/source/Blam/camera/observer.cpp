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

extern s_observer *_sub_10F19300(long);
s_observer *observer_get(long output_user_index) // 0x10F19300
{
	mangled_x86(MANGLED_TODO, "?observer_get@@YAPAUs_observer@@J@Z");
	// long output_user_index;
	todo("implement");
	s_observer * __result = _sub_10F19300(output_user_index);
	return __result;
}

/* ---------- private code */
