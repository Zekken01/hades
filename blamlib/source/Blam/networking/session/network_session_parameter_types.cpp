/* ---------- headers */

#include "Blam/networking/session/network_session_parameter_types.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/memory/bitstream.hpp"
#include "Blam/memory/static_array.inl"

/* ---------- forward declarations */

class c_bitstream;
class c_network_session_parameter_type_collection;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

_extern void _sub_10F1AC00(c_network_session_parameter_type_collection *const, e_network_session_parameter_type, char const *, bool (*)(c_bitstream *, void *), bool (*)(c_bitstream *, void *), long, bool (*)(c_bitstream *, void *), bool (*)(c_bitstream *, void *), long);
void c_network_session_parameter_type_collection::register_session_parameter_type(e_network_session_parameter_type session_parameter_type, char const *session_parameter_name, bool (*update_encode)(c_bitstream *, void *), bool (*update_decode)(c_bitstream *, void *), long update_size, bool (*change_request_encode)(c_bitstream *, void *), bool (*change_request_decode)(c_bitstream *, void *), long change_request_size) // 0x10F1AC00
{
	mangled_x86(MANGLED_TODO, "?register_session_parameter_type@c_network_session_parameter_type_collection@@QAEXW4e_network_session_parameter_type@@PBDP6A_NPAVc_bitstream@@PAX@Z4J44J@Z");
	// long change_request_size;
	// c_network_session_parameter_type_collection::s_type *element;
	todo("implement");
	_sub_10F1AC00(this, session_parameter_type, session_parameter_name, update_encode, update_decode, update_size, change_request_encode, change_request_decode, change_request_size);
}

/* ---------- private code */

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool s_static_array<c_network_session_parameter_type_collection::s_type,49>::valid(__int32);
template c_network_session_parameter_type_collection::s_type & s_static_array<c_network_session_parameter_type_collection::s_type,49>::operator[](long);
