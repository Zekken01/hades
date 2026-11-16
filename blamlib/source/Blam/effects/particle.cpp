/* ---------- headers */

#include "Blam/effects/particle.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/tls.hpp"

/* ---------- forward declarations */

struct c_particle;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern c_data_array<c_particle> *particles_get();

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

c_data_array<c_particle> *particles_get() // 0x10F18890
{
	return tls_getd().particles;
}

/* ---------- private code */
