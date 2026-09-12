/* ---------- headers */

#include "Blam/effects/effects.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/tls.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"

/* ---------- forward declarations */

struct s_effect_datum;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern c_data_array<s_effect_datum> *effects_get();

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

c_data_array<s_effect_datum> *effects_get() // 0x10F18840
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?effects_get@@YAPAV?$c_data_array@Us_effect_datum@@@@XZ");
	// procedure flags: nofpo

	return tls_getd().effect;
}

/* ---------- private code */
