/* ---------- headers */

#include "Blam/ai/actor.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/data_array.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/tag_files/tag_groups.hpp"

/* ---------- forward declarations */

struct s_actor_datum;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern s_actor_datum *actor_get(long index);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

extern s_actor_datum *_sub_10F0D8F0(long);
s_actor_datum *actor_get(long index) // 0x10F0D8F0
{
	mangled_x86(MANGLED_TODO, "?actor_get@@YAPAUs_actor_datum@@J@Z");
	// long index;
	todo("implement");
	s_actor_datum * __result = _sub_10F0D8F0(index);
	return __result;
}

/* ---------- private code */

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template s_actor_datum * c_data_array<s_actor_datum>::try_and_get(unsigned long);
