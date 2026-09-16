/* ---------- headers */

#include "hades/hades.h"

#include "Blam/BlamNetwork.hpp"
#include "Blam/camera/director.hpp"
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
#include "Blam/models/model_definitions.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/objects/object_definitions.hpp"
#include "Blam/objects/object_types.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "Blam/units/units.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Pointer.hpp"
#include "Utils/Singleton.hpp"

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
#include <functional>
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

struct s_model_definition;
struct s_model_variant;
struct s_model_variant_region;
struct s_object_data;
struct s_object_definition;
struct s_object_placement_data;
struct s_object_region_information;
struct s_player_datum;
struct s_unit_data;

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;
namespace Patches
{
	namespace Objects {}
	using namespace Patches::Objects;
}

namespace Patches {}
using namespace ::Patches;
namespace Blam {}
using namespace ::Blam;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Patches
{
	namespace Objects
	{
		extern void ApplyAll();
	}
}

bool object_type_new_hook(long object_index, s_object_placement_data &placement_data, bool *unused);
void objects_handle_deleted_object_hook(__int32 object_index);
void objects_update_hook();
float object_compute_service_tag_function_value(long object_index, short character_index);
float object_compute_region_permutation_function_value(long object_index, long model_region_index);
bool object_compute_function_value_hook(__int32 object_index, unsigned long name, long a4, float *out_value, bool *valid_value, bool *a7);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Patches
{
	namespace Objects
	{
		_extern void _sub_108D6330();
		void ApplyAll() // 0x108D6330
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@Objects@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_108D6330();
		}
	}
}

/* ---------- private code */

bool object_type_new_hook(long object_index, s_object_placement_data &placement_data, bool *unused) // 0x108D7240
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?object_type_new_hook@@YA_NJAAUs_object_placement_data@@PA_N@Z");
	// `anonymous-namespace'::object_type_new_hook
	// bool *unused;
	// bool (*const object_type_new)(long, s_object_placement_data &, bool *);
	// bool result;
	// function call : bool (*const)(long, s_object_placement_data &, bool *)

	bool (__cdecl *const object_type_new)(long, s_object_placement_data &, bool *) = (bool(__cdecl *const)(long, s_object_placement_data &, bool *))0xb73c60;

	bool result = object_type_new(object_index, placement_data, unused);

	if (!result)
		return result;

	return true;
}

void objects_handle_deleted_object_hook(__int32 object_index) // 0x108D72C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?objects_handle_deleted_object_hook@@YAXH@Z");
	// `anonymous-namespace'::objects_handle_deleted_object_hook
	// __int32 object_index;
	// void (*const objects_handle_deleted_object)(__int32);
	// function call : void (*const)(__int32)

	void (__cdecl *const objects_handle_deleted_object)(__int32) = (void(__cdecl *const)(__int32))0xb35870;

	objects_handle_deleted_object(object_index);
}

_extern void _sub_108D7320();
void objects_update_hook() // 0x108D7320
{
	// `anonymous-namespace'::objects_update_hook
	// procedure flags: nofpo
	// void (*const objects_update)();
	// function call : void (*const)()
	todo("implement");
	_sub_108D7320();
}

_extern float _sub_108D7060(long, short);
float object_compute_service_tag_function_value(long object_index, short character_index) // 0x108D7060
{
	// `anonymous-namespace'::object_compute_service_tag_function_value
	// short character_index;
	// wchar_t character;
	{
		// s_unit_data *unit;
		// s_player_datum *player;
	}
	// function call : bool (*const)()
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	todo("implement");
	float __result = _sub_108D7060(object_index, character_index);
	return __result;
}

_extern float _sub_108D6D80(long, long);
float object_compute_region_permutation_function_value(long object_index, long model_region_index) // 0x108D6D80
{
	// `anonymous-namespace'::object_compute_region_permutation_function_value
	// static ...; // 0x108D6F98
	// static ...; // 0x108D6F80
	// static ...; // 0x108D6F78
	// long object_index;
	// long model_region_index;
	// s_model_variant const *variant;
	// s_object_definition const *object_definition;
	// s_model_variant_region const *model_region;
	// long render_region_count;
	// char const *render_region_permutations;
	// s_object_data const *object;
	// void (*const object_get_region_information)(long, long *, char const **, char const **, s_object_region_information const **);
	// s_model_definition const *model;
	{
		// long model_permutation_index;
	}
	// function call : void *(*const)(unsigned long, long)
	// function call : void *(*const)(unsigned long, long)
	// function call : void (*const)(long, long *, char const **, char const **, s_object_region_information const **)
	todo("implement");
	float __result = _sub_108D6D80(object_index, model_region_index);
	return __result;
}

_extern bool _sub_108D6860(__int32, unsigned long, long, float *, bool *, bool *);
bool object_compute_function_value_hook(__int32 object_index, unsigned long name, long a4, float *out_value, bool *valid_value, bool *a7) // 0x108D6860
{
	// `anonymous-namespace'::object_compute_function_value_hook
	// long a4;
	// float *out_value;
	// bool *valid_value;
	// bool *a7;
	// bool (*const object_compute_function_value)(long, unsigned long, long, float *, bool *, bool *);
	{
		// s_unit_data *unit;
		// long output_user_index;
	}
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : long (*const)(long)
	// function call : e_director_perspective (*const)(long)
	// function call : bool (*const)(long, unsigned long, long, float *, bool *, bool *)
	todo("implement");
	bool __result = _sub_108D6860(object_index, name, a4, out_value, valid_value, a7);
	return __result;
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_tag_block<s_model_variant>::try_get_element(__int32, s_model_variant **) const;
template bool c_tag_block<s_model_variant_permutation>::try_get_element(__int32, s_model_variant_permutation **) const;
template bool c_tag_block<s_model_variant_region>::try_get_element(__int32, s_model_variant_region **) const;
template s_model_variant * c_tag_block<s_model_variant>::get_element(__int32) const;
template s_model_variant const & c_tag_block<s_model_variant>::operator[](__int32) const;
template s_model_variant_permutation * c_tag_block<s_model_variant_permutation>::get_element(__int32) const;
template s_model_variant_permutation const & c_tag_block<s_model_variant_permutation>::operator[](__int32) const;
template s_model_variant_region * c_tag_block<s_model_variant_region>::get_element(__int32) const;
template s_model_variant_region const & c_tag_block<s_model_variant_region>::operator[](__int32) const;
template void Pointer::Write<bool (__cdecl*)(int,unsigned long,long,float *,bool *,bool *)>(bool (*const value)(__int32, unsigned long, long, float *, bool *, bool *)) const;
