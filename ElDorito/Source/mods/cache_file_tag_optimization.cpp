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

void optimize_render_model(long runtime_tag_index, s_cache_tag_instance *tag_instance) // 0x1087C8B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?optimize_render_model@@YAXJPAUs_cache_tag_instance@@@Z");

	c_static_bit_vector<65535> dependencies_to_null;
	dependencies_to_null.clear();
	if (!g_reforge_render_models.test(runtime_tag_index))
		return;
	g_reforge_material_tags.clear();
	s_render_model *const definition = (s_render_model *)((char *)tag_instance + tag_instance->definition_offset);
	for (unsigned char material_index = 0; material_index < definition->materials.count; material_index++)
	{
		long render_method_index = definition->materials[material_index].render_method.index;
		if (render_method_index == -1)
			continue;
		if (g_reforge_material_indices.test(material_index))
			g_reforge_material_tags.set(render_method_index);
	}
	for (unsigned char material_index = 0; material_index < definition->materials.count; material_index++)
	{
		long render_method_index = definition->materials[material_index].render_method.index;
		if (!g_reforge_material_tags.test(render_method_index))
			dependencies_to_null.set(render_method_index);
	}
	null_tag_dependencies(tag_instance, &dependencies_to_null);
}

void cache_file_tags_optimize(long runtime_tag_index, s_cache_tag_instance *tag_instance) // 0x1087AA80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?cache_file_tags_optimize@@YAXJPAUs_cache_tag_instance@@@Z");

	switch (tag_instance->group.tags[0])
	{
	case 'scnr':
		optimize_scenario(tag_instance);
		return;
	case 'forg':
		optimize_forge_globals(tag_instance);
		return;
	case 'mulg':
		optimize_multiplayer_globals(tag_instance);
		return;
	case 'matg':
		optimize_globals(tag_instance);
		return;
	case 'wigl':
		optimize_user_interface_shared_globals(tag_instance);
		return;
	case 'mlst':
		optimize_user_interface_map_list(tag_instance);
		return;
	case 'hlmt':
		optimize_model(runtime_tag_index, tag_instance);
		return;
	case 'mode':
		optimize_render_model(runtime_tag_index, tag_instance);
		return;
	}
	if (tag_instance->group.tags[0] == 'obje' || tag_instance->group.tags[1] == 'obje' || tag_instance->group.tags[2] == 'obje')
		optimize_object(runtime_tag_index, tag_instance);
}

/* ---------- private code */

extern "C" s_game_options *get_intermediate_game_options() // 0x1087B0F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_get_intermediate_game_options");

	return (s_game_options *)0x2391800;
}

extern "C" void null_tag_dependencies(s_cache_tag_instance *tag_instance, c_static_bit_vector<65535> *dependencies_to_null) // 0x1087B110
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_null_tag_dependencies");

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

extern "C" void optimize_reforge_objects(s_forge_globals_definition *definition) // 0x1087C750
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_optimize_reforge_objects");

	s_game_options const *game_options = get_intermediate_game_options();
	s_map_variant const *map_variant = &game_options->map_variant;
	for (__int32 i = 0; i < definition->reforge_objects.count; i++)
	{
		long object_tag_index = definition->reforge_objects[i].index;
		g_reforge_objects.set(object_tag_index);
	}
	for (__int32 placement_index = 0; placement_index < 640; placement_index++)
	{
		long palette_index = map_variant->objects[placement_index].quota_index;
		if (palette_index < 0 || palette_index >= 256)
			continue;
		s_variant_quota const *palette_entry = &map_variant->object_quotas[palette_index];
		if (map_variant->objects[placement_index].properties.multiplayer_object_type)
			continue;
		g_reforge_material_indices.set(map_variant->objects[placement_index].properties.shared_storage);
	}
}

extern "C" void optimize_forge_globals(s_cache_tag_instance *tag_instance) // 0x1087B1D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_optimize_forge_globals");

	c_static_bit_vector<65535> dependencies_to_null;
	dependencies_to_null.clear();
	g_reforge_models.clear();
	g_reforge_objects.clear();
	g_reforge_render_models.clear();
	g_reforge_material_indices.clear();
	s_game_options const *game_options = get_intermediate_game_options();
	if (game_options->game_variant.game_engine_type == (e_game_engine_type)5)
		return;
	if (game_options->game_mode != (e_game_mode)2)
	{
		dependencies_to_null.set_all();
	}
	else
	{
		s_forge_globals_definition *definition = (s_forge_globals_definition *)((char *)tag_instance + tag_instance->definition_offset);
		optimize_reforge_objects(definition);
		c_tag_block<s_forge_palette_item> &palette = definition->palette;
		for (long i = 0; i < palette.count; i++)
		{
			s_forge_palette_item &item = palette[i];
			if (item.object.index != -1)
				dependencies_to_null.set(item.object.index);
		}
		for (long i = 0; i < 256; i++)
		{
			long definition_index = game_options->map_variant.object_quotas[i].definition_index;
			if (definition_index > 0 && definition_index < 0xFFFF)
				dependencies_to_null.unset(definition_index);
		}
	}
	null_tag_dependencies(tag_instance, &dependencies_to_null);
}

extern "C" void optimize_game_engine_event_response_tag_block(s_cache_tag_instance *tag_instance, c_tag_block<s_multiplayer_event_response_definition> *tag_block, e_game_engine_type game_engine_type, c_static_bit_vector<65535> *dependencies_to_null) // 0x1087B580
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_optimize_game_engine_event_response_tag_block");

	for (s_multiplayer_event_response_definition &response : *tag_block)
	{
		optimize_game_engine_event_response(&response, game_engine_type, dependencies_to_null);
	}
}

extern "C" void optimize_multiplayer_runtime_globals_for_engine_type(s_cache_tag_instance *tag_instance, s_multiplayer_runtime_globals_definition *runtime, e_game_engine_type game_engine_type, c_static_bit_vector<65535> *dependencies_to_null) // 0x1087C070
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_optimize_multiplayer_runtime_globals_for_engine_type");

	s_game_options const *game_options = get_intermediate_game_options();
	if (game_engine_type != _game_engine_type_sandbox)
	{
		if (runtime->sandbox_editor_object.index != -1)
			dependencies_to_null->set(runtime->sandbox_editor_object.index);
		if (runtime->sandbox_editor_unit.index != -1)
			dependencies_to_null->set(runtime->sandbox_editor_unit.index);
		if (runtime->sandbox_intro_ui.index != -1)
			dependencies_to_null->set(runtime->sandbox_intro_ui.index);
	}
	if (game_engine_type != _game_engine_type_slayer)
	{
		optimize_game_engine_event_response_tag_block(tag_instance, &runtime->slayer_event_responses, game_engine_type, dependencies_to_null);
		if (runtime->slayer_intro_ui.index != -1)
			dependencies_to_null->set(runtime->slayer_intro_ui.index);
	}
	if (game_engine_type != _game_engine_type_ctf)
	{
		optimize_game_engine_event_response_tag_block(tag_instance, &runtime->ctf_event_responses, game_engine_type, dependencies_to_null);
		if (runtime->ctf_intro_ui.index != -1)
			dependencies_to_null->set(runtime->ctf_intro_ui.index);
	}
	if (game_engine_type != _game_engine_type_oddball)
	{
		optimize_game_engine_event_response_tag_block(tag_instance, &runtime->oddball_event_responses, game_engine_type, dependencies_to_null);
		if (runtime->oddball_intro_ui.index != -1)
			dependencies_to_null->set(runtime->oddball_intro_ui.index);
	}
	if (game_engine_type != _game_engine_type_koth)
	{
		optimize_game_engine_event_response_tag_block(tag_instance, &runtime->koth_event_responses, game_engine_type, dependencies_to_null);
		if (runtime->king_of_the_hill_intro_ui.index != -1)
			dependencies_to_null->set(runtime->king_of_the_hill_intro_ui.index);
	}
	if (game_engine_type != _game_engine_type_vip)
	{
		optimize_game_engine_event_response_tag_block(tag_instance, &runtime->vip_event_responses, game_engine_type, dependencies_to_null);
		if (runtime->vip_intro_ui.index != -1)
			dependencies_to_null->set(runtime->vip_intro_ui.index);
		if (runtime->vip_zone.index != -1)
			dependencies_to_null->set(runtime->vip_zone.index);
	}
	if (game_engine_type != _game_engine_type_juggernaut)
	{
		optimize_game_engine_event_response_tag_block(tag_instance, &runtime->juggernaut_event_responses, game_engine_type, dependencies_to_null);
		if (runtime->juggernaut_intro_ui.index != -1)
			dependencies_to_null->set(runtime->juggernaut_intro_ui.index);
	}
	if (game_engine_type != _game_engine_type_territories)
	{
		optimize_game_engine_event_response_tag_block(tag_instance, &runtime->territories_event_responses, game_engine_type, dependencies_to_null);
		if (runtime->territories_intro_ui.index != -1)
			dependencies_to_null->set(runtime->territories_intro_ui.index);
	}
	if (game_engine_type != _game_engine_type_assault)
	{
		optimize_game_engine_event_response_tag_block(tag_instance, &runtime->assault_event_responses, game_engine_type, dependencies_to_null);
		if (runtime->assault_intro_ui.index != -1)
			dependencies_to_null->set(runtime->assault_intro_ui.index);
	}
	if (game_engine_type != _game_engine_type_infection)
	{
		optimize_game_engine_event_response_tag_block(tag_instance, &runtime->infection_event_responses, game_engine_type, dependencies_to_null);
		if (runtime->infection_intro_ui.index != -1)
			dependencies_to_null->set(runtime->infection_intro_ui.index);
	}
	if (game_engine_type == _game_engine_type_none)
	{
		optimize_game_engine_event_response_tag_block(tag_instance, &runtime->general_event_responses, game_engine_type, dependencies_to_null);
		optimize_game_engine_event_response_tag_block(tag_instance, &runtime->flavor_event_responses, game_engine_type, dependencies_to_null);
	}
	if (game_options->game_mode != _game_mode_multiplayer)
	{
		s_tag_block &multiplayer_constants_block = runtime->multiplayer_constants;
		s_tag_block &weapons_block = *(s_tag_block *)((char *)multiplayer_constants_block.address + 0x68);
		s_tag_block &vehicles_block = *(s_tag_block *)((char *)multiplayer_constants_block.address + 0x74);
		s_tag_block &projectiles_block = *(s_tag_block *)((char *)multiplayer_constants_block.address + 0x80);
		s_tag_block &equipment_block = *(s_tag_block *)((char *)multiplayer_constants_block.address + 0x80);
		for (long i = 0; i < weapons_block.count; i++)
		{
			s_tag_reference *weapon = (s_tag_reference *)((char *)weapons_block.address + i * 32);
			if (weapon->index != -1)
				dependencies_to_null->set(weapon->index);
		}
		for (long i = 0; i < vehicles_block.count; i++)
		{
			s_tag_reference *vehicle = (s_tag_reference *)((char *)vehicles_block.address + i * 32);
			if (vehicle->index != -1)
				dependencies_to_null->set(vehicle->index);
		}
		for (long i = 0; i < projectiles_block.count; i++)
		{
			s_tag_reference *projectile = (s_tag_reference *)((char *)projectiles_block.address + i * 28);
			if (projectile->index != -1)
				dependencies_to_null->set(projectile->index);
		}
		for (long i = 0; i < equipment_block.count; i++)
		{
			s_tag_reference *equipment = (s_tag_reference *)((char *)equipment_block.address + i * 28);
			if (equipment->index != -1)
				dependencies_to_null->set(equipment->index);
		}
	}
}

extern "C" void optimize_multiplayer_globals(s_cache_tag_instance *tag_instance) // 0x1087BA00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_optimize_multiplayer_globals");

	c_static_bit_vector<65535> dependencies_to_null;
	dependencies_to_null.clear();
	s_multiplayer_globals_definition *const definition = (s_multiplayer_globals_definition *)((char *)tag_instance + tag_instance->definition_offset);
	c_tag_block<s_multiplayer_universal_globals_definition> &universal_block = definition->universal;
	c_tag_block<s_multiplayer_runtime_globals_definition> &runtime_block = definition->runtime;
	s_game_options const *game_options = get_intermediate_game_options();
	if (universal_block->sandbox_strings.index != -1)
		dependencies_to_null.set(universal_block->sandbox_strings.index);
	if (universal_block->sandbox_text_value_pairs.index != -1)
		dependencies_to_null.set(universal_block->sandbox_text_value_pairs.index);
	c_tag_block<s_multiplayer_consumable> &consumables_block = universal_block->consumables;
	for (s_multiplayer_consumable &consumable : consumables_block)
	{
		if (consumable.object.index != -1)
			dependencies_to_null.set(consumable.object.index);
	}
	c_tag_block<s_multiplayer_equipment> &equipment_block = universal_block->equipment;
	for (s_multiplayer_equipment &equipment : equipment_block)
	{
		if (((s_tag_reference *)equipment.object)->index != -1)
			dependencies_to_null.set(((s_tag_reference *)equipment.object)->index);
	}
	c_tag_block<s_multiplayer_vehicle> &vehicles_block = universal_block->vehicles;
	c_tag_block<s_multiplayer_object_set> &vehicle_sets_list = universal_block->vehicle_sets;
	for (s_multiplayer_vehicle &vehicle : vehicles_block)
	{
		bool null_this = true;
		if (vehicle.object.index != -1)
		{
			for (s_multiplayer_object_set &set : vehicle_sets_list)
			{
				for (s_multiplayer_object_substitution &sub : set.substitutions)
				{
					if (sub.substituted_object_name == vehicle.name)
						null_this = false;
				}
			}
			if (null_this)
				dependencies_to_null.set(vehicle.object.index);
		}
	}
	if (game_options->game_variant.game_engine_type != _game_engine_type_sandbox)
	{
		if (runtime_block->sandbox_editor_unit.index != -1)
			dependencies_to_null.set(runtime_block->sandbox_editor_unit.index);
		if (runtime_block->sandbox_editor_object.index != -1)
			dependencies_to_null.set(runtime_block->sandbox_editor_object.index);
	}
	optimize_multiplayer_runtime_globals_for_engine_type(tag_instance, &runtime_block[0], game_options->game_variant.game_engine_type, &dependencies_to_null);
	if (game_options->game_mode != _game_mode_mainmenu && universal_block->game_engine_settings.index != -1)
		dependencies_to_null.set(universal_block->game_engine_settings.index);
	null_tag_dependencies(tag_instance, &dependencies_to_null);
}

extern "C" void optimize_user_interface_shared_globals(s_cache_tag_instance *tag_instance) // 0x1087CE20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_optimize_user_interface_shared_globals");

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

extern "C" void optimize_globals(s_cache_tag_instance *tag_instance) // 0x1087B620
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_optimize_globals");

	c_static_bit_vector<65535> dependencies_to_null;
	dependencies_to_null.clear();
	s_game_options const *game_options = get_intermediate_game_options();
	s_game_globals *const definition = (s_game_globals *)((char *)tag_instance + tag_instance->definition_offset);
	if (game_options->game_mode == _game_mode_mainmenu)
	{
		c_tag_block<s_global_material_definition> &materials_block = definition->Materials;
		for (s_global_material_definition &material : materials_block)
		{
			if (material.MaterialEffects.index != -1)
				dependencies_to_null.set(material.MaterialEffects.index);
		}
		materials_block.count = 0;
		materials_block.address = nullptr;
	}
	null_tag_dependencies(tag_instance, &dependencies_to_null);
}

extern "C" void optimize_user_interface_map_list(s_cache_tag_instance *tag_instance) // 0x1087CC40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "_optimize_user_interface_map_list");

	c_static_bit_vector<65535> dependencies_to_null;
	dependencies_to_null.clear();
	s_user_interface_map_list *const definition = (s_user_interface_map_list *)((char *)tag_instance + tag_instance->definition_offset);
	s_game_options const *game_options = get_intermediate_game_options();
	if (game_options->game_mode != _game_mode_mainmenu)
	{
		for (s_user_interface_map_image &image : definition->map_images)
		{
			if (image.map_id != game_options->map_id)
				dependencies_to_null.set(image.bitmap.index);
		}
	}
	null_tag_dependencies(tag_instance, &dependencies_to_null);
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

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
extern "C" { c_static_bit_vector<65535> g_reforge_objects; }
extern "C" { c_static_bit_vector<65535> g_reforge_models; }
extern "C" { c_static_bit_vector<65535> g_reforge_render_models; }
extern "C" { c_static_bit_vector<256> g_reforge_material_indices; }
extern "C" { c_static_bit_vector<65535> g_reforge_material_tags; }
