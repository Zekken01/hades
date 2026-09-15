/* ---------- headers */

#include "mods/cache_file_tag_optimization.hpp"
#include "hades/hades.h"

#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/forge/forge_globals.hpp"
#include "Blam/game/engine/game_engine.hpp"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_globals.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/multiplayer_definitions.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/interface/user_interface_maps.hpp"
#include "Blam/items/equipment_definitions.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/bit_vector.inl"
#include "Blam/models/model_definitions.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/object_definitions.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/rasterizer/rasterizer_geometry.hpp"
#include "Blam/render/render_model.hpp"
#include "Blam/saved_games/scenario_map_variant.hpp"
#include "Blam/scenario/scenario_definitions.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "mods/font_package.hpp"
#include "mods/map_variant_loader.hpp"
#include "Patches/Events.hpp"

/* ---------- forward declarations */

struct begin;
struct end;
struct s_cache_tag_instance;
struct s_forge_globals_definition;
struct s_forge_palette_item;
struct s_game_globals;
struct s_game_options;
struct s_global_material_definition;
struct s_map_variant;
struct s_model_definition;
struct s_multiplayer_consumable;
struct s_multiplayer_equipment;
struct s_multiplayer_event_response_definition;
struct s_multiplayer_globals_definition;
struct s_multiplayer_object_set;
struct s_multiplayer_object_substitution;
struct s_multiplayer_runtime_globals_definition;
struct s_multiplayer_universal_globals_definition;
struct s_multiplayer_vehicle;
struct s_object_definition;
struct s_render_model;
struct s_scenario_object_palette_entry;
struct s_tag_block;
struct s_tag_reference;
struct s_user_interface_map_image;
struct s_user_interface_map_list;
struct s_variant_quota;

/* ---------- constants */

/* ---------- definitions */

typedef c_static_bit_vector<65535> s_tag_bit_vector;

/* ---------- prototypes */

extern void optimize_scenario(s_cache_tag_instance *tag_instance);
extern void optimize_game_engine_event_response(s_multiplayer_event_response_definition const *response, e_game_engine_type game_engine_type, c_static_bit_vector<65535> *dependencies_to_null);
extern void optimize_object(long runtime_tag_index, s_cache_tag_instance *tag_instance);
extern void optimize_model(long runtime_tag_index, s_cache_tag_instance *tag_instance);
extern void optimize_render_model(long runtime_tag_index, s_cache_tag_instance *tag_instance);
extern void cache_file_tags_optimize(long runtime_tag_index, s_cache_tag_instance *tag_instance);

extern "C" s_game_options *get_intermediate_game_options();
extern "C" void null_tag_dependencies(s_cache_tag_instance *tag_instance, c_static_bit_vector<65535> *dependencies_to_null);
extern "C" void optimize_main_menu(s_cache_tag_instance *tag_instance, c_static_bit_vector<65535> *dependencies_to_null);
extern "C" void optimize_reforge_objects(s_forge_globals_definition *definition);
extern "C" void optimize_forge_globals(s_cache_tag_instance *tag_instance);
extern "C" void optimize_game_engine_event_response_tag_block(s_cache_tag_instance *tag_instance, c_tag_block<s_multiplayer_event_response_definition> *tag_block, e_game_engine_type game_engine_type, c_static_bit_vector<65535> *dependencies_to_null);
extern "C" void optimize_multiplayer_runtime_globals_for_engine_type(s_cache_tag_instance *tag_instance, s_multiplayer_runtime_globals_definition *runtime, e_game_engine_type game_engine_type, c_static_bit_vector<65535> *dependencies_to_null);
extern "C" void optimize_multiplayer_globals(s_cache_tag_instance *tag_instance);
extern "C" void optimize_user_interface_shared_globals(s_cache_tag_instance *tag_instance);
extern "C" void optimize_globals(s_cache_tag_instance *tag_instance);
extern "C" void optimize_user_interface_map_list(s_cache_tag_instance *tag_instance);

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	// The original names these with C decoration (`_g_reforge_objects`), not a C++
	// mangling, so every reference to one has to be spelled that way too.
	extern "C" {
	extern c_static_bit_vector<65535> g_reforge_objects; // 0x123AEF30
	extern c_static_bit_vector<65535> g_reforge_models; // 0x123B0F30
	extern c_static_bit_vector<65535> g_reforge_render_models; // 0x123B2F30
	extern c_static_bit_vector<256> g_reforge_material_indices; // 0x123B4F30
	extern c_static_bit_vector<65535> g_reforge_material_tags; // 0x123B4F58
	}
}
using namespace hades_file_local;
/* ---------- public code */

void optimize_scenario(s_cache_tag_instance *tag_instance) // 0x1087CB10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?optimize_scenario@@YAXPAUs_cache_tag_instance@@@Z");
	// static ...; // 0x1087CBEC
	// static ...; // 0x1087CBE0
	// static ...; // 0x1087CBD8
	// s_cache_tag_instance *tag_instance;
	// s_game_options const *game_options;
	// c_static_bit_vector<65535> dependencies_to_null;

	c_static_bit_vector<65535> dependencies_to_null;

	dependencies_to_null.clear();

	s_game_options const *game_options = get_intermediate_game_options();

	if (game_options->game_mode == _game_mode_mainmenu)
	{
		optimize_main_menu(tag_instance, &dependencies_to_null);
	}

	null_tag_dependencies(tag_instance, &dependencies_to_null);
}

void optimize_game_engine_event_response(s_multiplayer_event_response_definition const *response, e_game_engine_type game_engine_type, c_static_bit_vector<65535> *dependencies_to_null) // 0x1087B4B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?optimize_game_engine_event_response@@YAXPBUs_multiplayer_event_response_definition@@W4e_game_engine_type@@PAU?$c_static_bit_vector@$0PPPP@@@@Z");
	// c_static_bit_vector<65535> *dependencies_to_null;
	// s_game_options const *game_options;
		// long i;

	s_game_options const *game_options = get_intermediate_game_options();

	if (game_options->game_variant.game_engine_type == game_engine_type && game_engine_type != _game_engine_type_none)
	{
		return;
	}

	for (long i = 0; i < 12; i++)
	{
		if (response->sounds[i].index != -1)
		{
			dependencies_to_null->set(response->sounds[i].index);
		}
	}
}

void optimize_object(long runtime_tag_index, s_cache_tag_instance *tag_instance) // 0x1087C690
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?optimize_object@@YAXJPAUs_cache_tag_instance@@@Z");
	// s_cache_tag_instance *tag_instance;
		// void *object;
		// s_object_definition *const definition;
	// function call : void *(*const)(unsigned long, long)

	if (g_reforge_objects.test(runtime_tag_index))
	{
		void *object = tag_get(0x6F626A65, runtime_tag_index);
		s_object_definition *const definition = (s_object_definition *)((char *)tag_instance + tag_instance->definition_offset);

		if (definition->model.index != -1)
		{
			g_reforge_models.set(definition->model.index);
		}
	}
}

void optimize_model(long runtime_tag_index, s_cache_tag_instance *tag_instance) // 0x1087B940
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?optimize_model@@YAXJPAUs_cache_tag_instance@@@Z");
	// s_cache_tag_instance *tag_instance;
		// s_model_definition *const definition;
		// void *model;
	// function call : void *(*const)(unsigned long, long)

	if (g_reforge_models.test(runtime_tag_index))
	{
		void *model = tag_get(0x686C6D74, runtime_tag_index);
		s_model_definition *const definition = (s_model_definition *)((char *)tag_instance + tag_instance->definition_offset);

		if (definition->render_model.index != -1)
		{
			g_reforge_render_models.set(definition->render_model.index);
		}
	}
}

_extern void _sub_1087C8B0(long, s_cache_tag_instance *);
void optimize_render_model(long runtime_tag_index, s_cache_tag_instance *tag_instance) // 0x1087C8B0
{
	mangled_x86(MANGLED_TODO, "?optimize_render_model@@YAXJPAUs_cache_tag_instance@@@Z");
	// static ...; // 0x1087CA74
	// static ...; // 0x1087CA6C
	// long runtime_tag_index;
	// s_cache_tag_instance *tag_instance;
	// c_static_bit_vector<65535> dependencies_to_null;
	// s_render_model *const definition;
	{
		// unsigned char material_index;
		{
			// long render_method_index;
		}
	}
	{
		{
		}
	}
	todo("implement");
	_sub_1087C8B0(runtime_tag_index, tag_instance);
}

_extern void _sub_1087AA80(long, s_cache_tag_instance *);
void cache_file_tags_optimize(long runtime_tag_index, s_cache_tag_instance *tag_instance) // 0x1087AA80
{
	mangled_x86(MANGLED_TODO, "?cache_file_tags_optimize@@YAXJPAUs_cache_tag_instance@@@Z");
	// s_cache_tag_instance *tag_instance;
	todo("implement");
	_sub_1087AA80(runtime_tag_index, tag_instance);
}

/* ---------- private code */

extern "C" s_game_options *get_intermediate_game_options() // 0x1087B0F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_get_intermediate_game_options");
	// get_intermediate_game_options
	// procedure flags: nofpo

	return (s_game_options *)0x2391800;
}

extern "C" void null_tag_dependencies(s_cache_tag_instance *tag_instance, c_static_bit_vector<65535> *dependencies_to_null) // 0x1087B110
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_null_tag_dependencies");
	// null_tag_dependencies
	// c_static_bit_vector<65535> *dependencies_to_null;
	// long *dependencies;
		// long i;
			// long tag_index;

	long *dependencies = (long *)&tag_instance[1];

	for (long i = 0; i < tag_instance->dependency_count; i++)
	{
		long tag_index = dependencies[i];

		if (tag_index > 0 && tag_index < 0xFFFF && dependencies_to_null->test(tag_index))
		{
			dependencies[i] = -1;
		}
	}
}

extern "C" void optimize_main_menu(s_cache_tag_instance *tag_instance, c_static_bit_vector<65535> *dependencies_to_null) // 0x1087B830
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_optimize_main_menu");
	// optimize_main_menu
	// c_static_bit_vector<65535> *dependencies_to_null;
	// s_tag_block *sound_scenery_palette_block;
	// s_tag_block *sound_scenery_block;
	// char *definition;
		// long i;
			// short palette_index;
			// long tag_index;
			// s_scenario_object_palette_entry *item;

	char *definition = (char *)tag_instance + tag_instance->definition_offset;
	s_tag_block *sound_scenery_block = (s_tag_block *)(definition + 0x1AC);
	s_tag_block *sound_scenery_palette_block = (s_tag_block *)(definition + 0x1B8);

	for (long i = 0; i < sound_scenery_block->count; i++)
	{
		short palette_index = ((s_scenario_sound_scenery *)sound_scenery_block->address)[i].palette_index;

		if (palette_index < 0 || palette_index >= sound_scenery_palette_block->count)
		{
			continue;
		}

		s_scenario_object_palette_entry *item = &((s_scenario_object_palette_entry *)sound_scenery_palette_block->address)[palette_index];
		long tag_index = ((s_tag_reference *)item->object)->index;

		if (tag_index >= 0 && tag_index < 0xFFFF)
		{
			dependencies_to_null->set(tag_index);
		}
	}

	*(long *)(definition + 0x1AC) = 0;
}

_extern void _sub_1087C750(s_forge_globals_definition *);
extern "C" void optimize_reforge_objects(s_forge_globals_definition *definition) // 0x1087C750
{
	// optimize_reforge_objects
	// s_forge_globals_definition *definition;
	// s_game_options const *game_options;
	// s_map_variant const *map_variant;
	{
		// __int32 i;
		{
			// long object_tag_index;
		}
	}
	{
		// __int32 placement_index;
		{
			// long palette_index;
			// s_variant_quota const *palette_entry;
		}
	}
	todo("implement");
	_sub_1087C750(definition);
}

_extern void _sub_1087B1D0(s_cache_tag_instance *);
extern "C" void optimize_forge_globals(s_cache_tag_instance *tag_instance) // 0x1087B1D0
{
	// optimize_forge_globals
	// static ...; // 0x1087B408
	// static ...; // 0x1087B3FC
	// static ...; // 0x1087B3F4
	// s_cache_tag_instance *tag_instance;
	// s_game_options const *game_options;
	// c_static_bit_vector<65535> dependencies_to_null;
	{
		// c_tag_block<s_forge_palette_item> &palette;
		// s_forge_globals_definition *const definition;
		{
			// long i;
			{
				// s_forge_palette_item *palette_entry;
			}
		}
		{
			{
				// long tag_index;
			}
		}
	}
	todo("implement");
	_sub_1087B1D0(tag_instance);
}

extern "C" void optimize_game_engine_event_response_tag_block(s_cache_tag_instance *tag_instance, c_tag_block<s_multiplayer_event_response_definition> *tag_block, e_game_engine_type game_engine_type, c_static_bit_vector<65535> *dependencies_to_null) // 0x1087B580
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_optimize_game_engine_event_response_tag_block");
	// optimize_game_engine_event_response_tag_block
	// c_static_bit_vector<65535> *dependencies_to_null;
		// c_tag_block<s_multiplayer_event_response_definition> &<range>$L0;
		// s_multiplayer_event_response_definition *<begin>$L0;
		// s_multiplayer_event_response_definition *<end>$L0;
			// s_multiplayer_event_response_definition &response;

	for (s_multiplayer_event_response_definition &response : *tag_block)
	{
		optimize_game_engine_event_response(&response, game_engine_type, dependencies_to_null);
	}
}

_extern void _sub_1087C070(s_cache_tag_instance *, s_multiplayer_runtime_globals_definition *, e_game_engine_type, c_static_bit_vector<65535> *);
extern "C" void optimize_multiplayer_runtime_globals_for_engine_type(s_cache_tag_instance *tag_instance, s_multiplayer_runtime_globals_definition *runtime, e_game_engine_type game_engine_type, c_static_bit_vector<65535> *dependencies_to_null) // 0x1087C070
{
	// optimize_multiplayer_runtime_globals_for_engine_type
	// c_static_bit_vector<65535> *dependencies_to_null;
	// s_game_options const *game_options;
	{
		// s_tag_block &projectiles_block;
		// s_tag_block &multiplayer_constants_block;
		// s_tag_block &weapons_block;
		// s_tag_block &vehicles_block;
		// s_tag_block &equipment_block;
		{
			// long i;
			{
				// s_tag_reference *weapon;
			}
		}
		{
			{
				// s_tag_reference *vehicle;
			}
		}
		{
			{
				// s_tag_reference *projectile;
			}
		}
		{
			{
				// s_tag_reference *equipment;
			}
		}
	}
	todo("implement");
	_sub_1087C070(tag_instance, runtime, game_engine_type, dependencies_to_null);
}

_extern void _sub_1087BA00(s_cache_tag_instance *);
extern "C" void optimize_multiplayer_globals(s_cache_tag_instance *tag_instance) // 0x1087BA00
{
	// optimize_multiplayer_globals
	// static ...; // 0x1087BF10
	// static ...; // 0x1087BF04
	// static ...; // 0x1087BEFC
	// s_cache_tag_instance *tag_instance;
	// s_game_options const *game_options;
	// c_tag_block<s_multiplayer_runtime_globals_definition> &runtime_block;
	// c_static_bit_vector<65535> dependencies_to_null;
	// c_tag_block<s_multiplayer_universal_globals_definition> &universal_block;
	// c_tag_block<s_multiplayer_consumable> &consumables_block;
	// c_tag_block<s_multiplayer_object_set> &vehicle_sets_list;
	// s_multiplayer_globals_definition *const definition;
	// c_tag_block<s_multiplayer_vehicle> &vehicles_block;
	// c_tag_block<s_multiplayer_equipment> &equipment_block;
	{
		// c_tag_block<s_multiplayer_consumable> &<range>$L0;
		// s_multiplayer_consumable *<begin>$L0;
		// s_multiplayer_consumable *<end>$L0;
		{
			// s_multiplayer_consumable &consumable;
		}
	}
	{
		// s_multiplayer_equipment *<end>$L1;
		// s_multiplayer_equipment *<begin>$L1;
		// c_tag_block<s_multiplayer_equipment> &<range>$L1;
		{
			// s_multiplayer_equipment &equipment;
		}
	}
	{
		// s_multiplayer_vehicle *<end>$L2;
		// c_tag_block<s_multiplayer_vehicle> &<range>$L2;
		// s_multiplayer_vehicle *<begin>$L2;
		{
			// s_multiplayer_vehicle &vehicle;
			{
				// bool null_this;
				{
					// c_tag_block<s_multiplayer_object_set> &<range>$L3;
					// s_multiplayer_object_set *<begin>$L3;
					// s_multiplayer_object_set *<end>$L3;
					{
						// s_multiplayer_object_set &set;
						{
							// s_multiplayer_object_substitution *<end>$L4;
							// s_multiplayer_object_substitution *<begin>$L4;
							// c_tag_block<s_multiplayer_object_substitution> &<range>$L4;
							{
								// s_multiplayer_object_substitution &sub;
							}
						}
					}
				}
			}
		}
	}
	todo("implement");
	_sub_1087BA00(tag_instance);
}

extern "C" void optimize_user_interface_shared_globals(s_cache_tag_instance *tag_instance) // 0x1087CE20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_optimize_user_interface_shared_globals");
	// optimize_user_interface_shared_globals
	// static ...; // 0x1087CF20
	// static ...; // 0x1087CF14
	// static ...; // 0x1087CF0C
	// s_cache_tag_instance *tag_instance;
	// s_game_options const *game_options;
	// c_static_bit_vector<65535> dependencies_to_null;
	// s_multiplayer_globals_definition *const definition;
	// long main_menu_loop_index;

	c_static_bit_vector<65535> dependencies_to_null;

	dependencies_to_null.clear();

	char *definition = (char *)tag_instance + tag_instance->definition_offset;
	long bit = *(long *)(definition + 0x4C);
	s_game_options const *game_options = get_intermediate_game_options();

	if (game_options->game_mode != _game_mode_mainmenu && bit != -1)
	{
		dependencies_to_null.set(bit);
	}

	null_tag_dependencies(tag_instance, &dependencies_to_null);
}

_extern void _sub_1087B620(s_cache_tag_instance *);
extern "C" void optimize_globals(s_cache_tag_instance *tag_instance) // 0x1087B620
{
	// optimize_globals
	// static ...; // 0x1087B7A8
	// static ...; // 0x1087B79C
	// static ...; // 0x1087B794
	// s_cache_tag_instance *tag_instance;
	// s_game_options const *game_options;
	// c_static_bit_vector<65535> dependencies_to_null;
	// s_game_globals *const definition;
	{
		// c_tag_block<s_global_material_definition> &materials_block;
		{
			// c_tag_block<s_global_material_definition> &<range>$L0;
			// s_global_material_definition *<begin>$L0;
			// s_global_material_definition *<end>$L0;
			{
				// s_global_material_definition &material;
			}
		}
	}
	todo("implement");
	_sub_1087B620(tag_instance);
}

_extern void _sub_1087CC40(s_cache_tag_instance *);
extern "C" void optimize_user_interface_map_list(s_cache_tag_instance *tag_instance) // 0x1087CC40
{
	// optimize_user_interface_map_list
	// static ...; // 0x1087CDA0
	// static ...; // 0x1087CD94
	// static ...; // 0x1087CD8C
	// s_cache_tag_instance *tag_instance;
	// s_game_options const *game_options;
	// c_static_bit_vector<65535> dependencies_to_null;
	// s_user_interface_map_list *const definition;
	{
		// c_tag_block<s_user_interface_map_image> &<range>$L0;
		// s_user_interface_map_image *<begin>$L0;
		// s_user_interface_map_image *<end>$L0;
		{
			// s_user_interface_map_image &image;
		}
	}
	todo("implement");
	_sub_1087CC40(tag_instance);
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_enum<enum e_game_engine_type,long>::operator!=(e_game_engine_type const &) const;
template bool c_enum<enum e_game_engine_type,long>::operator==(e_game_engine_type const &) const;
template bool c_enum<enum e_game_mode,long>::operator!=(e_game_mode const &) const;
template bool c_static_bit_vector<256>::test(long);
template bool c_static_bit_vector<256>::valid_bit(long);
template bool c_static_bit_vector<65535>::test(long);
template bool c_static_bit_vector<65535>::valid_bit(long);
template bool c_tag_block<s_forge_palette_item>::try_get_element(__int32, s_forge_palette_item **) const;
template bool c_tag_block<s_geometry_material>::try_get_element(__int32, s_geometry_material **) const;
template bool c_tag_block<s_tag_reference>::try_get_element(__int32, s_tag_reference **) const;
template s_forge_palette_item & c_tag_block<s_forge_palette_item>::operator[](__int32);
template s_forge_palette_item * c_tag_block<s_forge_palette_item>::get_element(__int32) const;
template s_geometry_material & c_tag_block<s_geometry_material>::operator[](__int32);
template s_geometry_material * c_tag_block<s_geometry_material>::get_element(__int32) const;
template s_global_material_definition * c_tag_block<s_global_material_definition>::begin();
template s_global_material_definition * c_tag_block<s_global_material_definition>::end();
template s_multiplayer_consumable * c_tag_block<s_multiplayer_consumable>::begin();
template s_multiplayer_consumable * c_tag_block<s_multiplayer_consumable>::end();
template s_multiplayer_equipment * c_tag_block<s_multiplayer_equipment>::begin();
template s_multiplayer_equipment * c_tag_block<s_multiplayer_equipment>::end();
template s_multiplayer_event_response_definition * c_tag_block<s_multiplayer_event_response_definition>::begin();
template s_multiplayer_event_response_definition * c_tag_block<s_multiplayer_event_response_definition>::end();
template s_multiplayer_object_set * c_tag_block<s_multiplayer_object_set>::begin();
template s_multiplayer_object_set * c_tag_block<s_multiplayer_object_set>::end();
template s_multiplayer_object_substitution * c_tag_block<s_multiplayer_object_substitution>::begin();
template s_multiplayer_object_substitution * c_tag_block<s_multiplayer_object_substitution>::end();
template s_multiplayer_runtime_globals_definition & c_tag_block<s_multiplayer_runtime_globals_definition>::operator[](__int32);
template s_multiplayer_vehicle * c_tag_block<s_multiplayer_vehicle>::begin();
template s_multiplayer_vehicle * c_tag_block<s_multiplayer_vehicle>::end();
template s_tag_reference & c_tag_block<s_tag_reference>::operator[](__int32);
template s_tag_reference * c_tag_block<s_tag_reference>::get_element(__int32) const;
template s_user_interface_map_image * c_tag_block<s_user_interface_map_image>::begin();
template s_user_interface_map_image * c_tag_block<s_user_interface_map_image>::end();
template void c_static_bit_vector<256>::clear();
template void c_static_bit_vector<256>::set(long);
template void c_static_bit_vector<65535>::clear();
template void c_static_bit_vector<65535>::set(long);
template void c_static_bit_vector<65535>::set_all();
template void c_static_bit_vector<65535>::unset(long);
