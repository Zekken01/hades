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

// mangled_x86(MANGLED_DEFAULT, "??0s_visible_items@@QAE@XZ"); no body to assert in
_inline s_visible_items::s_visible_items() = default; // 0x10F0DB30

_extern void _sub_10F0DC80();
void c_visible_items::clear_all() // 0x10F0DC80
{
	mangled_x86(MANGLED_TODO, "?clear_all@c_visible_items@@SAXXZ");
	// procedure flags: nofpo
	todo("implement");
	_sub_10F0DC80();
}

s_visible_items_stack_marker &c_visible_items::get_current_markers() // 0x10F0DD50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_current_markers@c_visible_items@@SAAAUs_visible_items_stack_marker@@XZ");
	// procedure flags: nofpo

	return m_marker_stack[m_marker_stack_top];
}

/* ---------- private code */

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool s_static_array<s_visible_items_stack_marker,3>::valid(__int32);
template s_visible_items_stack_marker & s_static_array<s_visible_items_stack_marker,3>::operator[](long);
