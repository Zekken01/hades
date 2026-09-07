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

extern c_data_array<s_object_header> *_sub_10EF8F00();
c_data_array<s_object_header> *object_headers_get() // 0x10EF8F00
{
	mangled_x86(MANGLED_TODO, "?object_headers_get@@YAPAV?$c_data_array@Us_object_header@@@@XZ");
	// procedure flags: nofpo
	todo("implement");
	c_data_array<s_object_header> * __result = _sub_10EF8F00();
	return __result;
}

extern s_object_header *_sub_10EF8E70(unsigned long);
s_object_header *object_header_get(unsigned long object_index) // 0x10EF8E70
{
	mangled_x86(MANGLED_TODO, "?object_header_get@@YAPAUs_object_header@@K@Z");
	// unsigned long object_index;
	// function call : void *(*const)(s_data_array const *, unsigned long)
	todo("implement");
	s_object_header * __result = _sub_10EF8E70(object_index);
	return __result;
}

extern s_object_data *_sub_10EF8CB0(unsigned long);
s_object_data *object_get(unsigned long object_index) // 0x10EF8CB0
{
	mangled_x86(MANGLED_TODO, "?object_get@@YAPAUs_object_data@@K@Z");
	// unsigned long object_index;
	// s_object_header *object_header;
	todo("implement");
	s_object_data * __result = _sub_10EF8CB0(object_index);
	return __result;
}

_extern __int32 _sub_10EF8BB0(unsigned long, unsigned long);
__int32 object_choose_variant(unsigned long object_index, unsigned long variant_name) // 0x10EF8BB0
{
	mangled_x86(MANGLED_TODO, "?object_choose_variant@@YAHKK@Z");
	// unsigned long variant_name;
	// s_object_data *data;
	// s_object_definition *definition;
	// function call : void *(*const)(unsigned long, long)
	todo("implement");
	__int32 __result = _sub_10EF8BB0(object_index, variant_name);
	return __result;
}

_extern __int32 _sub_10EF8F50(__int32, unsigned long);
__int32 object_lookup_variant_index_from_name(__int32 tag_index, unsigned long variant_name) // 0x10EF8F50
{
	mangled_x86(MANGLED_TODO, "?object_lookup_variant_index_from_name@@YAHHK@Z");
	// unsigned long variant_name;
	// s_model_definition *model_definition;
	// long variant_count;
	// __int32 result;
	{
		// c_tag_block<s_model_variant> &<range>$L0;
		// s_model_variant *<begin>$L0;
		// s_model_variant *<end>$L0;
		{
			// s_model_variant &variant;
		}
	}
	// function call : void *(*const)(unsigned long, long)
	todo("implement");
	__int32 __result = _sub_10EF8F50(tag_index, variant_name);
	return __result;
}

_extern unsigned long _sub_10EF8D20(long);
unsigned long object_get_variant_name(long object_index) // 0x10EF8D20
{
	mangled_x86(MANGLED_TODO, "?object_get_variant_name@@YAKJ@Z");
	// long object_index;
	// s_object_data *object;
	// s_object_definition *const object_def;
	// s_model_definition *const model;
	// function call : void *(*const)(unsigned long, long)
	// function call : void *(*const)(unsigned long, long)
	todo("implement");
	unsigned long __result = _sub_10EF8D20(object_index);
	return __result;
}

/* ---------- private code */

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template s_model_variant * c_tag_block<s_model_variant>::begin();
template s_model_variant * c_tag_block<s_model_variant>::end();
