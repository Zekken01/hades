/* ---------- headers */

#include "Blam/visibility/visibility_items.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/static_array.inl"
#include "Blam/structures/cluster_reference.hpp"

/* ---------- forward declarations */

class c_visible_items;
struct s_visible_items;
struct s_visible_items_stack_marker;

/* ---------- constants */

/* ---------- definitions */

typedef void vorbis_info_residue;
typedef void vorbis_info_floor;
typedef void vorbis_look_transform;
typedef void vorbis_info_mapping;
typedef short vorbis_fpu_control;
typedef void vorbis_look_floor;
typedef void vorbis_look_residue;

/* ---------- prototypes */

/* ---------- globals */

s_visible_items c_visible_items::m_items; // 0x124C2C90

/* ---------- private variables */

/* ---------- public code */

_extern void _sub_10F0DF10();
void c_visible_items::push_marker() // 0x10F0DF10
{
	mangled_x86(MANGLED_TODO, "?push_marker@c_visible_items@@SAXXZ");
	// procedure flags: nofpo
	// s_visible_items_stack_marker &top;
	todo("implement");
	_sub_10F0DF10();
}

_extern void _sub_10F0DDB0();
void c_visible_items::pop_marker() // 0x10F0DDB0
{
	mangled_x86(MANGLED_TODO, "?pop_marker@c_visible_items@@SAXXZ");
	// procedure flags: nofpo
	// s_visible_items_stack_marker &top;
	todo("implement");
	_sub_10F0DDB0();
}

extern s_visible_items* _sub_10F0DB30(s_visible_items *const);
_inline s_visible_items::s_visible_items() // 0x10F0DB30
{
	mangled_x86(MANGLED_TODO, "??0s_visible_items@@QAE@XZ");
	// s_visible_items *const this;
	compiler_generated();
	todo("implement");
	_sub_10F0DB30(this);
}

_extern void _sub_10F0DC80();
void c_visible_items::clear_all() // 0x10F0DC80
{
	mangled_x86(MANGLED_TODO, "?clear_all@c_visible_items@@SAXXZ");
	// procedure flags: nofpo
	todo("implement");
	_sub_10F0DC80();
}

extern s_visible_items_stack_marker &_sub_10F0DD50();
s_visible_items_stack_marker &c_visible_items::get_current_markers() // 0x10F0DD50
{
	mangled_x86(MANGLED_TODO, "?get_current_markers@c_visible_items@@SAAAUs_visible_items_stack_marker@@XZ");
	// procedure flags: nofpo
	todo("implement");
	s_visible_items_stack_marker & __result = _sub_10F0DD50();
	return __result;
}

/* ---------- private code */

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool s_static_array<s_visible_items_stack_marker,3>::valid(__int32);
template s_visible_items_stack_marker & s_static_array<s_visible_items_stack_marker,3>::operator[](long);
