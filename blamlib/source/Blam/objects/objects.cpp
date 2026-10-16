/* ---------- headers */

#include "Blam/objects/objects.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/effects/screen_effect.hpp"
#include "Blam/game/player_model_customization.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/items/equipment_definitions.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/data.hpp"
#include "Blam/memory/tls.hpp"
#include "Blam/models/model_definitions.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/objects/multiplayer_game_objects.hpp"
#include "Blam/objects/object_definitions.hpp"
#include "Blam/objects/object_types.hpp"
#include "Blam/scenario/scenario_definitions.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"

/* ---------- forward declarations */

struct begin;
struct end;
struct real_point3d;
struct real_vector3d;
struct s_damage_owner;
struct s_data_array;
struct s_model_customization_region_permutation;
struct s_model_definition;
struct s_model_variant;
struct s_multiplayer_object_properties;
struct s_object_data;
struct s_object_definition;
struct s_object_header;
struct s_object_placement_data;
struct s_scenario_location;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern void *(*const datum_try_and_get)(s_data_array const *, unsigned long);  // hades: added for 0x10EF8E70

s_object_header *object_header_get(unsigned long object_index);  // hades: added for 0X10EF8CB0

s_object_data *object_get(unsigned long object_index);  // hades: added for 0X10EF8BB0
__int32 object_lookup_variant_index_from_name(__int32 model_index, unsigned long variant_name);  // hades: added for 0X10EF8BB0

extern c_data_array<s_object_header> *object_headers_get();
extern s_object_header *object_header_get(unsigned long object_index);
extern s_object_data *object_get(unsigned long object_index);
extern __int32 object_choose_variant(unsigned long object_index, unsigned long variant_name);
extern __int32 object_lookup_variant_index_from_name(__int32 tag_index, unsigned long variant_name);
extern unsigned long object_get_variant_name(long object_index);

/* ---------- globals */

extern s_multiplayer_object_properties *(*const object_get_multiplayer)(unsigned long); // 0x1124884C
extern s_object_data *(*const object_try_and_get_and_verify_type)(unsigned long, c_enum<enum e_object_type,long>); // 0x11248848
extern void (*const object_choose_initial_permutation)(long, unsigned long, s_model_customization_region_permutation const *, long); // 0x1124882C
extern void (*const object_set_position)(unsigned long, real_point3d *, real_vector3d *, real_vector3d *, s_scenario_location *); // 0x11248844
extern void (*const object_get_world_position)(unsigned long, real_point3d *); // 0x11248834
extern void (*const object_placement_data_new)(s_object_placement_data *, long, unsigned long, s_damage_owner *); // 0x11248838
extern bool (*const object_find_initial_location)(unsigned long, s_scenario_location *); // 0x11248830
extern __int32 (*const object_reconnect_to_map)(unsigned long, bool, s_scenario_location *); // 0x1124883C
extern void (*const object_register_scenario_object)(unsigned long); // 0x11248840
extern short (*const objects_get_in_cluster)(long, c_flags<enum e_object_type,long>, s_scenario_location *, real_point3d *, float, unsigned long *, short); // 0x11248850

/* ---------- private variables */

/* ---------- public code */

c_data_array<s_object_header> *object_headers_get() // 0x10EF8F00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?object_headers_get@@YAPAV?$c_data_array@Us_object_header@@@@XZ");

	return tls_getd().object_header;
}

s_object_header *object_header_get(unsigned long object_index) // 0x10EF8E70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?object_header_get@@YAPAUs_object_header@@K@Z");

	if (object_index == -1)
	{
		return nullptr;
	}

	return (s_object_header *)datum_try_and_get(object_headers_get(), object_index);
}

s_object_data *object_get(unsigned long object_index) // 0x10EF8CB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?object_get@@YAPAUs_object_data@@K@Z");

	s_object_header *object_header = object_header_get(object_index);
	if (object_header == nullptr)
		return nullptr;
	return object_header->data;
}

__int32 object_choose_variant(unsigned long object_index, unsigned long variant_name) // 0x10EF8BB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?object_choose_variant@@YAHKK@Z");

	s_object_data *data = object_get(object_index);
	if (!data)
		return -1;

	s_object_definition *definition = (s_object_definition *)tag_get(0x6F626A65, data->definition_index);
	if (!definition)
		return -1;

	if (!variant_name)
		variant_name = definition->default_model_variant;

	return data->variant_index = object_lookup_variant_index_from_name(definition->model.index, variant_name);
}

__int32 object_lookup_variant_index_from_name(__int32 tag_index, unsigned long variant_name) // 0x10EF8F50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?object_lookup_variant_index_from_name@@YAHHK@Z");

	if (tag_index == -1)
		return -1;
	s_model_definition *model_definition = (s_model_definition *)tag_get('hlmt', tag_index);
	if (!variant_name)
	{
		if (model_definition->variants.count > 0)
			return 0;
		return -1;
	}
	long variant_count = model_definition->variants.count;
	__int32 result = 0;
	if (variant_count <= 0)
		return -1;
	for (s_model_variant &variant : model_definition->variants)
	{
		if (variant.name != variant_name)
			break;
		result++;
		if (result >= variant_count)
			return -1;
	}
	return result;
}

unsigned long object_get_variant_name(long object_index) // 0x10EF8D20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?object_get_variant_name@@YAKJ@Z");

	s_object_data *object = object_get(object_index);
	if (!object)
	{
		return 0;
	}

	if (object->variant_index == -1)
	{
		return 0;
	}

	s_object_definition *const object_def = (s_object_definition *)tag_get('obje', object->definition_index);
	if (object_def->model.index == -1)
	{
		return 0;
	}

	s_model_definition *const model = (s_model_definition *)tag_get('hlmt', object_def->model.index);
	if (object->variant_index >= model->variants.count)
	{
		return 0;
	}

	return model->variants[object->variant_index].name;
}

/* ---------- private code */

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template s_model_variant * c_tag_block<s_model_variant>::begin();
template s_model_variant * c_tag_block<s_model_variant>::end();

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
s_object_data *(*const object_try_and_get_and_verify_type)(unsigned long, c_enum<enum e_object_type,long>) = reinterpret_cast<decltype(object_try_and_get_and_verify_type)>(0xB34490);
s_multiplayer_object_properties *(*const object_get_multiplayer)(unsigned long) = reinterpret_cast<decltype(object_get_multiplayer)>(0xB344E0);
void (*const object_set_position)(unsigned long, real_point3d *, real_vector3d *, real_vector3d *, s_scenario_location *) = reinterpret_cast<decltype(object_set_position)>(0xB33530);
void (*const object_placement_data_new)(s_object_placement_data *, long, unsigned long, s_damage_owner *) = reinterpret_cast<decltype(object_placement_data_new)>(0xB31590);
void (*const object_get_world_position)(unsigned long, real_point3d *) = reinterpret_cast<decltype(object_get_world_position)>(0xB2E5A0);
void (*const object_choose_initial_permutation)(long, unsigned long, s_model_customization_region_permutation const *, long) = reinterpret_cast<decltype(object_choose_initial_permutation)>(0xB2A820);
