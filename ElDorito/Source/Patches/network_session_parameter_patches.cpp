/* ---------- headers */

#include "hades/hades.h"

#include "Blam/BitStream.hpp"
#include "Blam/BlamNetwork.hpp"
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
#include "Blam/memory/bitstream.hpp"
#include "Blam/memory/static_array.inl"
#include "Blam/networking/session/network_session.hpp"
#include "Blam/networking/session/network_session_membership.hpp"
#include "Blam/networking/session/network_session_parameter_mod.hpp"
#include "Blam/networking/session/network_session_parameter_types.hpp"
#include "Blam/networking/session/network_session_parameters.hpp"
#include "Blam/networking/session/network_session_parameters_base.hpp"
#include "Blam/networking/session/network_session_parameters_custom.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Patch.hpp"
#include "Pointer.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <atomic>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <initializer_list>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <streambuf>
#include <system_error>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

class c_bitstream;
class c_network_session;
class c_network_session_parameter_base;
class c_network_session_parameter_mod;
class c_network_session_parameter_type_collection;
class c_network_session_parameters;
class c_network_observer;
struct s_session_mod_options;
namespace Blam
{
	class BitStream;
}

namespace Utils {}
using namespace ::Utils;
namespace Blam {}
using namespace ::Blam;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern void network__session_parameter_types_register_hook(c_network_session_parameter_type_collection *collection);
extern void network_session_parameter_patches_apply();

void c_network_session_parameters__initialize_parameters_hook(c_network_session_parameters *thisptr, void *unused, c_network_session *session, c_network_observer *observer);
bool network_sesison_parameter_eldewrito_encode(c_bitstream *bitstream, void *data);
bool network_sesison_parameter_eldewrito_decode(c_bitstream *bitstream, void *data);

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern char const *g_session_mod_parameter_name; // 0x113547E0
	extern s_static_array<c_network_session_parameter_mod,4> g_session_mod_parameters; // 0x12466598
}
using namespace hades_file_local;
/* ---------- public code */

_inline c_network_session_parameter_base::c_network_session_parameter_base() // 0x10AA88D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0c_network_session_parameter_base@@QAE@XZ");
	// c_network_session_parameter_base *const this;

	compiler_generated();
}

_extern void _sub_10AA8F20(c_network_session_parameter_type_collection *);
void network__session_parameter_types_register_hook(c_network_session_parameter_type_collection *collection) // 0x10AA8F20
{
	mangled_x86(MANGLED_TODO, "?network__session_parameter_types_register_hook@@YAXPAVc_network_session_parameter_type_collection@@@Z");
	// c_network_session_parameter_type_collection *collection;
	// constexpr void (*const `network__session_parameter_types_register_hook'::`2'::network_session_parameter_types_register)(c_network_session_parameter_type_collection *); // constant == 5092848
	// function call : void (*const)(c_network_session_parameter_type_collection *)
	todo("implement");
	_sub_10AA8F20(collection);
}

_inline c_network_session_parameter_mod::c_network_session_parameter_mod() // 0x10AA8940
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0c_network_session_parameter_mod@@QAE@XZ");
	// c_network_session_parameter_mod *const this;

	compiler_generated();
}

_extern void _sub_10AA90D0();
void network_session_parameter_patches_apply() // 0x10AA90D0
{
	mangled_x86(MANGLED_TODO, "?network_session_parameter_patches_apply@@YAXXZ");
	// procedure flags: nofpo
	todo("implement");
	_sub_10AA90D0();
}

/* ---------- private code */

_extern void _sub_10AA8A80(c_network_session_parameters *, void *, c_network_session *, c_network_observer *);
void c_network_session_parameters__initialize_parameters_hook(c_network_session_parameters *thisptr, void *unused, c_network_session *session, c_network_observer *observer) // 0x10AA8A80
{
	// `anonymous-namespace'::c_network_session_parameters__initialize_parameters_hook
	// c_network_observer *observer;
	// constexpr void (*const `c_network_session_parameters__initialize_parameters_hook'::`2'::c_network_session_parameters__initialize_parameters)(c_network_session_parameters *, c_network_session *, c_network_observer *); // constant == 4761952
	// c_network_session_parameter_mod *parameter;
	// function call : void (*const)(c_network_session_parameters *, c_network_session *, c_network_observer *)
	todo("implement");
	_sub_10AA8A80(thisptr, unused, session, observer);
}

_extern bool _sub_10AA9040(c_bitstream *, void *);
bool network_sesison_parameter_eldewrito_encode(c_bitstream *bitstream, void *data) // 0x10AA9040
{
	// `anonymous-namespace'::network_sesison_parameter_eldewrito_encode
	// void *data;
	// s_session_mod_options *data_;
	// Blam::BitStream *bitstream_;
	todo("implement");
	bool __result = _sub_10AA9040(bitstream, data);
	return __result;
}

_extern bool _sub_10AA8FB0(c_bitstream *, void *);
bool network_sesison_parameter_eldewrito_decode(c_bitstream *bitstream, void *data) // 0x10AA8FB0
{
	// `anonymous-namespace'::network_sesison_parameter_eldewrito_decode
	// void *data;
	// s_session_mod_options *data_;
	// Blam::BitStream *bitstream_;
	todo("implement");
	bool __result = _sub_10AA8FB0(bitstream, data);
	return __result;
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_custom_network_session_parameter<s_session_mod_options>::handle_change_request_payload(void const *);
template bool c_custom_network_session_parameter<s_session_mod_options>::handle_update_payload(void const *);
template bool s_static_array<c_network_session_parameter_mod,4>::valid(__int32);
template c_custom_network_session_parameter<s_session_mod_options>::c_custom_network_session_parameter();
template c_enum<enum e_network_session_parameter_type,unsigned long> & c_enum<enum e_network_session_parameter_type,unsigned long>::operator=(e_network_session_parameter_type const &);
template c_enum<enum e_network_session_parameter_type,unsigned long>::c_enum();
template c_flags<enum e_network_session_parameter_base_flags,unsigned char> & c_flags<enum e_network_session_parameter_base_flags,unsigned char>::operator=(unsigned char const &);
template c_flags<enum e_network_session_parameter_base_flags,unsigned char>::c_flags();
template c_network_session_parameter_mod & s_static_array<c_network_session_parameter_mod,4>::operator[](long);
template long c_custom_network_session_parameter<s_session_mod_options>::get_change_request_payload_size();
template long c_custom_network_session_parameter<s_session_mod_options>::get_update_payload_size();
template void c_custom_network_session_parameter<s_session_mod_options>::get_change_request_payload(long, void *);
template void c_custom_network_session_parameter<s_session_mod_options>::get_update_payload(long, void *);
template void c_custom_network_session_parameter<s_session_mod_options>::initialize(e_network_session_parameter_type, char const *, long, long, c_network_session *);
template void c_custom_network_session_parameter<s_session_mod_options>::notify_clear();
template void c_custom_network_session_parameter<s_session_mod_options>::notify_reset_peer_state(long);
template void c_custom_network_session_parameter<s_session_mod_options>::notify_transition_state_to_become_host();
template void s_static_array<unsigned char,17>::set_memory(unsigned char);
