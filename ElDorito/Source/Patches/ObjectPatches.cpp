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

#include "Objects/ObjectMessaging.hpp"  // hades: added for 0x108D7320

#include "Modules/ModuleCamera.hpp"  // hades: added for 0x108D6860

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

extern void *(*const tag_get)(unsigned long, long);  // hades: added for 0x108D6D80

#include "Modules/ModulePlayer.hpp"  // hades: added for 0x108D7060
extern s_object_data *(*const object_try_and_get_and_verify_type)(unsigned long, c_enum<enum e_object_type,long>);  // hades: added for 0x108D7060

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
		void ApplyAll() // 0x108D6330
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAll@Objects@Patches@@YAXXZ");
			// procedure flags: nofpo

			Hook(0x730BD8, object_type_new_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Pointer(0x194AB04).Write<unsigned int>(reinterpret_cast<unsigned int>(objects_handle_deleted_object_hook));
			Hook(0x133887, objects_update_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Pointer(0x1947F6C).Write(object_compute_function_value_hook);
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

void objects_update_hook() // 0x108D7320
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?objects_update_hook@@YAXXZ");
	// `anonymous-namespace'::objects_update_hook
	// procedure flags: nofpo
	// void (*const objects_update)();
	// function call : void (*const)()

	void (*const objects_update)() = reinterpret_cast<void (*)()>(0xB36840);
	::Objects::CObjectMessaging::RunActions();
	objects_update();
}

float object_compute_service_tag_function_value(long object_index, short character_index) // 0x108D7060
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?object_compute_service_tag_function_value@@YAMJF@Z");
	// `anonymous-namespace'::object_compute_service_tag_function_value
	// short character_index;
	// wchar_t character;
		// s_unit_data *unit;
		// s_player_datum *player;
	// function call : bool (*const)()
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)

	wchar_t character = 0;
	if (character_index < 0 || character_index > 3)
		return 0.0f;
	if (((bool (*const)())0x531E90)())
	{
		character = Modules::ModulePlayer::Instance().VarPlayerServiceTag->ValueString[character_index];
	}
	else
	{
		s_unit_data *unit = (s_unit_data *)object_try_and_get_and_verify_type(object_index, 0x2003);
		if (!unit || unit->player_index == -1)
			return 0.0f;
		s_player_datum *player = player_get(unit->player_index);
		if (player)
			character = player->configuration.host.appearance.service_tag[character_index];
		else
			return 0.0f;
	}
	if (character >= '0' && character <= '9')
		character -= '0';
	else if (character >= 'A' && character <= 'Z')
		character -= 'A' - 10;
	else
		character = 36;
	return character / 36.0f;
}

float object_compute_region_permutation_function_value(long object_index, long model_region_index) // 0x108D6D80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?object_compute_region_permutation_function_value@@YAMJJ@Z");
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
		// long model_permutation_index;
	// function call : void *(*const)(unsigned long, long)
	// function call : void *(*const)(unsigned long, long)
	// function call : void (*const)(long, long *, char const **, char const **, s_object_region_information const **)

	void (*const object_get_region_information)(long, long *, char const **, char const **, s_object_region_information const **) = reinterpret_cast<void (*)(long, long *, char const **, char const **, s_object_region_information const **)>(0xB2E770);
	s_object_data const *object = object_get(object_index);
	s_object_definition const *object_definition = (s_object_definition const *)tag_get('obje', object->definition_index);
	if (object_definition->model.index == -1)
		return 0.0f;
	s_model_definition const *model = (s_model_definition const *)tag_get('hlmt', object_definition->model.index);
	if (object->variant_index < 0 || object->variant_index >= model->variants.count)
		return 0.0f;
	s_model_variant const *variant = &model->variants[object->variant_index];
	if (model_region_index < 0 || model_region_index >= variant->regions.count)
		return 0.0f;
	long render_region_count;
	char const *render_region_permutations;
	object_get_region_information(object_index, &render_region_count, &render_region_permutations, nullptr, nullptr);
	s_model_variant_region const *model_region = &variant->regions[model_region_index];
	if (model_region->render_model_region < 0 || model_region->render_model_region >= render_region_count)
		return 0.0f;
	for (long model_permutation_index = 0; model_permutation_index < model_region->permutations.count; model_permutation_index++)
	{
		if (model_region->permutations[model_permutation_index].render_model_permutation == render_region_permutations[model_region->render_model_region])
			return (float)(model_permutation_index + 1) / model_region->permutations.count;
	}
	return 0.0f;
}

bool object_compute_function_value_hook(__int32 object_index, unsigned long name, long a4, float *out_value, bool *valid_value, bool *a7) // 0x108D6860
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?object_compute_function_value_hook@@YA_NHKJPAMPA_N1@Z");
	// `anonymous-namespace'::object_compute_function_value_hook
	// long a4;
	// float *out_value;
	// bool *valid_value;
	// bool *a7;
	// bool (*const object_compute_function_value)(long, unsigned long, long, float *, bool *, bool *);
		// s_unit_data *unit;
		// long output_user_index;
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : long (*const)(long)
	// function call : e_director_perspective (*const)(long)
	// function call : bool (*const)(long, unsigned long, long, float *, bool *, bool *)

	bool (*const object_compute_function_value)(long, unsigned long, long, float *, bool *, bool *) = reinterpret_cast<bool (*)(long, unsigned long, long, float *, bool *, bool *)>(0xB2B120);
	switch (name)
	{
	case 0x9CEB:
	case 0x9CEC:
	case 0x9CED:
	case 0x9CEE:
	case 0x9CEF:
	case 0x9CF0:
	case 0x9CF1:
	case 0x9CF2:
	case 0x9CF3:
	case 0x9CF4:
	case 0x9CF5:
	case 0x9CF6:
	case 0x9CF7:
	case 0x9CF8:
	case 0x9CF9:
	case 0x9CFA:
		*out_value = object_compute_region_permutation_function_value(object_index, name - 0x9CEB);
		*valid_value = *out_value > 0.0f;
		return true;
	case 0x9CFB:
	{
		s_unit_data *unit = (s_unit_data *)object_try_and_get_and_verify_type(object_index, 0x2003);
		if (!unit || unit->player_index == -1)
			return false;
		long output_user_index = ((long (*)(long))0x589A70)(unit->player_index);
		if (output_user_index != -1)
		{
			if (!((long (*)(long))0x591A40)(output_user_index))
				*out_value = Utils::Singleton<Modules::ModuleCamera>::Instance().VarCameraCenteredCrosshairThird->ValueInt != 0;
			else
				*out_value = Utils::Singleton<Modules::ModuleCamera>::Instance().VarCameraCenteredCrosshairFirst->ValueInt != 0;
		}
		*valid_value = *out_value > 0.0f;
		return true;
	}
	case 0x103F3:
		*out_value = object_compute_service_tag_function_value(object_index, 0);
		*valid_value = *out_value >= 0.0f && *out_value <= 36.0f;
		return true;
	case 0x103F4:
		*out_value = object_compute_service_tag_function_value(object_index, 1);
		*valid_value = *out_value >= 0.0f && *out_value <= 36.0f;
		return true;
	case 0x103F5:
		*out_value = object_compute_service_tag_function_value(object_index, 2);
		*valid_value = *out_value >= 0.0f && *out_value <= 36.0f;
		return true;
	case 0x103F6:
		*out_value = object_compute_service_tag_function_value(object_index, 3);
		*valid_value = *out_value >= 0.0f && *out_value <= 36.0f;
		return true;
	default:
		return object_compute_function_value(object_index, name, a4, out_value, valid_value, a7);
	}
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
