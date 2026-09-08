/* ---------- headers */

#include "hades/hades.h"

#include "Blam/ai/actor.hpp"
#include "Blam/BlamInput.hpp"
#include "Blam/BlamNetwork.hpp"
#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/effects/screen_effect.hpp"
#include "Blam/fmod/fmod_functions.inl"
#include "Blam/forge/forge_globals.hpp"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/engine/game_engine_sandbox.hpp"
#include "Blam/game/game_engine_candy_monitor.hpp"
#include "Blam/game/game_engine_globals.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/interface/chud/chud_messaging.hpp"
#include "Blam/interface/user_interface_sound.hpp"
#include "Blam/items/equipment_definitions.hpp"
#include "Blam/items/weapon_definitions.hpp"
#include "Blam/math/color_definitions.hpp"
#include "Blam/math/function_definitions.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/math/sound_math.hpp"
#include "Blam/memory/bitstream.hpp"
#include "Blam/memory/data_array.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/models/model_definitions.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/objects/lights.hpp"
#include "Blam/objects/multiplayer_game_objects.hpp"
#include "Blam/objects/object_definitions.hpp"
#include "Blam/objects/object_types.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/physics/collision_test.hpp"
#include "Blam/physics/havok_component.hpp"
#include "Blam/physics/havok_types.hpp"
#include "Blam/physics/havok_utilities.hpp"
#include "Blam/physics/physics_model.hpp"
#include "Blam/rasterizer/rasterizer_game_states.hpp"
#include "Blam/rasterizer/rasterizer_geometry.hpp"
#include "Blam/render/views/render_lights_view.hpp"
#include "Blam/saved_games/scenario_map_variant.hpp"
#include "Blam/scenario/scenario.hpp"
#include "Blam/scenario/scenario_definitions.hpp"
#include "Blam/simulation/simulation_queue_global_events.hpp"
#include "Blam/sounds/sound_memory.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "Blam/units/biped_definitions.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "CommandMap.hpp"
#include "CommandScript.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Console/Console.hpp"
#include "ElDorito.hpp"
#include "Forge/ForgeDevice.hpp"
#include "Forge/ForgeObjectProperties.hpp"
#include "Forge/ForgeUndo.hpp"
#include "Forge/ForgeUndoMapVariant.hpp"
#include "Forge/ForgeUtil.hpp"
#include "Forge/Geoemetry.hpp"
#include "Forge/Magnets.hpp"
#include "Forge/ObjectSet.hpp"
#include "mods/map_variant_loader.hpp"
#include "Modules/ModuleForge.hpp"
#include "Modules/ModulePlayer.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Patches/GamePatches.hpp"
#include "Patches/Ui.hpp"
#include "Pointer.hpp"
#include "ThirdParty/rapidjson/allocators.h"
#include "ThirdParty/rapidjson/encodedstream.h"
#include "ThirdParty/rapidjson/error/error.h"
#include "ThirdParty/rapidjson/internal/biginteger.h"
#include "ThirdParty/rapidjson/internal/diyfp.h"
#include "ThirdParty/rapidjson/internal/ieee754.h"
#include "ThirdParty/rapidjson/internal/pow10.h"
#include "ThirdParty/rapidjson/internal/strtod.h"
#include "ThirdParty/rapidjson/memorystream.h"
#include "ThirdParty/rapidjson/reader.h"
#include "Utils/EventSink.hpp"
#include "Utils/Macros.hpp"
#include "Utils/NameValueTable.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/StlUtil.hpp"
#include "Utils/String.hpp"
#include "Web/Bridge/WebRendererQueryHandler.hpp"
#include "Web/Ui/Screen.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <atomic>
#include <bitset>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <deque>
#include <exception>
#include <functional>
#include <initializer_list>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <memory>
#include <ostream>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <system_error>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <unordered_map>
#include <utility>
#include <vector>

/* ---------- forward declarations */

class CForgeDeviceManager;
class CForgeUndoManager;
class c_function_definition;
class c_havok_component;
struct begin;
struct c_candy_spawner;
struct c_character_physics_component;
struct c_havok_contact_point;
struct c_lights_view;
struct c_multiplayer_candy_monitor_manager;
struct c_periodic_function_compact;
struct c_runtime_node_to_physics_model_rigid_body_index_mapping;
struct c_sandbox_engine;
struct end;
struct hkpEntity;
struct real_argb_color;
struct real_matrix4x3;
struct real_point3d;
struct real_quaternion;
struct real_rgb_color;
struct real_vector3d;
struct s_biped_definition;
struct s_character_physics_update_input_datum;
struct s_collision_result;
struct s_damage_owner;
struct s_forge_globals_definition;
struct s_forge_palette_item;
struct s_function_definition_internal;
struct s_game_engine_globals;
struct s_light_datum;
struct s_map_variant;
struct s_map_variant_placement_properties;
struct s_model_definition;
struct s_model_object_data;
struct s_monitorState;
struct s_multiplayer_object_boundary_geometry_data;
struct s_multiplayer_object_properties;
struct s_object_data;
struct s_object_definition;
struct s_object_header;
struct s_object_placement_data;
struct s_object_type_definition;
struct s_physics_model_definition;
struct s_physics_model_rigid_body;
struct s_player_datum;
struct s_sandbox_globals;
struct s_scenario;
struct s_scenario_object_palette_entry;
struct s_selectionState;
struct s_simulation_queue_sandbox_event_data;
struct s_tag_block;
struct s_tag_data;
struct s_variant_datum;
struct s_variant_quota;
struct s_weapon_definition;
struct s_weapon_magazine_definition;
namespace Blam
{
	namespace Input
	{
		struct ActionState;
	}
}
namespace Forge
{
	class ObjectSet;
	struct ForgeLightProperties;
	struct ForgeObjectQuota;
	struct ReforgeObjectProperties;
}
namespace Forge
{
	namespace Magnets
	{
		struct MagnetPair;
	}
}
namespace Modules
{
	class CommandMap;
	class ModuleForge;
	class ModulePlayer;
}

namespace Utils {}
using namespace ::Utils;
namespace Utils
{
	namespace AntiCheat {}
	using namespace Utils::AntiCheat;
}

namespace Modules {}
using namespace ::Modules;
namespace Forge {}
using namespace ::Forge;
namespace Forge
{
	namespace Magnets {}
	using namespace Forge::Magnets;
	namespace Selection {}
	using namespace Forge::Selection;
	namespace Prefabs {}
	using namespace Forge::Prefabs;
	namespace Volumes {}
	using namespace Forge::Volumes;
	namespace SelectionRenderer {}
	using namespace Forge::SelectionRenderer;
	namespace Reforge {}
	using namespace Forge::Reforge;
}

namespace base
{
	namespace internal {}
	using namespace base::internal;
}

namespace Web {}
using namespace ::Web;
namespace Web
{
	namespace Ui {}
	using namespace Web::Ui;
}

namespace Web
{
	namespace Ui
	{
		namespace ScreenLayer {}
		using namespace Web::Ui::ScreenLayer;
		namespace WebForge {}
		using namespace Web::Ui::WebForge;
		namespace WebConsole {}
		using namespace Web::Ui::WebConsole;
	}
}

namespace Web
{
	namespace Browser {}
	using namespace Web::Browser;
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge {}
		using namespace Web::Browser::Bridge;
	}
}

namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Camera {}
	using namespace Patches::Camera;
	namespace Game {}
	using namespace Patches::Game;
}

namespace Console {}
using namespace ::Console;
namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Input {}
	using namespace Blam::Input;
}

/* ---------- constants */

/* ---------- definitions */

struct s_monitorState
{
	bool IsValid; // 0x0
	bool MonitorLastTick; // 0x1
	bool NoclipLastTick; // 0x2
	long HeldObjectIndex; // 0x4
	long HeldObjectRootNode; // 0x8
	real_vector3d GrabOffset; // 0xC
	s_monitorState(); /* compiler_generated() */
};
// static_assert(sizeof(s_monitorState) == 24, "Invalid s_monitorState size");
// Withheld: the type inventory does not describe this type, so its
// padding could not be reconstructed.

struct s_selectionState
{
	public:
	struct ChildInfo
	{
		real_vector3d displacement; // 0x0
		float scale; // 0xC
		ChildInfo(); /* compiler_generated() */
	};
	// static_assert(sizeof(ChildInfo) == 16, "Invalid ChildInfo size");
	// Withheld: the type inventory does not describe this type, so its
	// padding could not be reconstructed.
	public:
	real_point3d initialPosition; // 0x0
	float initialScale; // 0xC
	std::unordered_map<int,ChildInfo,std::hash<int>,std::equal_to<int>,std::allocator<std::pair<int const ,ChildInfo> > > children; // 0x10
	s_selectionState(s_selectionState &); /* compiler_generated() */
	s_selectionState(s_selectionState const &); /* compiler_generated() */
	s_selectionState(); /* compiler_generated() */
	~s_selectionState(); /* compiler_generated() */
	s_selectionState &operator=(s_selectionState &); /* compiler_generated() */
	s_selectionState &operator=(s_selectionState const &); /* compiler_generated() */
};
// static_assert(sizeof(s_selectionState) == 56, "Invalid s_selectionState size");
// Withheld: the type inventory does not describe this type, so its
// padding could not be reconstructed.

namespace hades_file_local
{

}
using namespace hades_file_local;
//struct light_intensity_function_evaluate::__l2::s_functionData
//{
//	s_function_definition_internal header; // 0x0
//	c_periodic_function_compact periodic; // 0x20
//};
//static_assert(sizeof(light_intensity_function_evaluate::__l2::s_functionData) == 52, "Invalid light_intensity_function_evaluate::__l2::s_functionData size");

namespace Patches
{
	namespace Forge
	{
		typedef void (*ItemSpawnedCallback)(unsigned __int32);
	}
}

/* ---------- prototypes */

namespace Patches
{
	namespace Forge
	{
		extern void ApplyAll();
		extern void ApplyAfterTagsLoaded();
		extern void Tick();
		extern void OnItemSpawned(void (*callback)(unsigned __int32));
	}
}

void AddMapVariantUndoPoint(char const *summary);
void ApplyGrabOffset(long player_index, long object_index);
void GrabObject(long player_index, long map_variant_index);
void GrabSelection(long player_index);
void SubmitWorldBoundsForRendering();
void TryUndo();
void TryRedo();
void CanvasMap();
void ResetRuntime();
void HandlePrefabCommands();
void SpawnItem(long tag_index);
void DoClone(long player_index, long cursor_object_index);
void HandleRuntimeReset();
void HandleMapCanvas();
void HandleSetPrematchCamera();
void HandleSpawnItem();
void HandleOpenMapOptions();
void HandleCommands();
void HandleRotationReset();
void HandleMovementSpeed();
void HandleMonitorNoclip();
void HandleMonitorInput(long playerIndex);
long FindComplexObjectRigidBodyRootNode(long object_index);
void UpdateSelectionManipulationState(__int32 rootObjectIndex);
s_forge_palette_item *FindSandboxPaletteItem(long tag_index);
bool initialize_map_variant_from_scenario(s_map_variant *thisptr, s_scenario *scenario);
long CreateOrGetBudgetForItem(s_map_variant *thisptr, long tag_index);
void RecalculateMapVariantBudget();
void ObjectOutOfWorldBoundsError();
bool TestBarrierTestProjectile(long barrierObjectIndex, long projectileObjectIndex);
void OnMonitorModeChange(bool isMonitor);
float c_map_variant__get_budget_fraction_hook(s_map_variant *thisptr, void *__formal, float *budget_spent, float *budget_max);
bool c_sandbox_engine__initialize_for_new_map_hook(c_sandbox_engine *thisptr, void *__formal);
void c_sandbox_engine__dispose_from_old_map_hook(c_sandbox_engine *thisptr, void *__formal);
void c_sandbox_engine__update_hook(c_sandbox_engine *thisptr, void *__formal);
void c_sandbox_engine__rotate_object_hook(c_sandbox_engine *thisptr, void *__formal, long playerIndex, long objectIndex, float yaw, float pitch, float roll);
void c_sandbox_engine__handle_deleted_object_hook(c_sandbox_engine *thisptr, void *__formal, long object_index);
void game_engine_sandox_apply_grab_object_hook2(long player_index, long object_index);
void game_engine_sandox_apply_grab_object_hook(long player_index, long map_variant_index);
void game_engine_sandbox_stop_editing_object_hook(long map_variant_index, float force, bool activate_physics);
void game_engine_sandbox_delete_object_hook(long map_variant_index, long player_index);
void game_engine_sandbox_place_object_hook(long tag_index, long player_index, real_point3d const *position);
void ApplyObjectPropertiesToSelection(long playerIndex, long rootObjectIndex, s_map_variant_placement_properties *properties);
void game_engine_sandbox_update_variant_object_properties_hook(long player_index, long map_variant_index, s_map_variant_placement_properties *properties);
void character_physics_update_input_datum_initialize_flying_hook(long unit_index, s_character_physics_update_input_datum *physics_input, c_character_physics_component *physics_component, float a6, float a7);
void update_edited_object_transform_hook(bool apply_gravity, long object_index, real_point3d const *position, real_vector3d const *forward, real_vector3d const *up);
bool shoot_probe_for_player_test_vector_hook(unsigned long flags, unsigned long test_object_flags, real_point3d const *origin, real_vector3d const *vector, __int32 ignore_object_index1, __int32 ignore_object_index2, s_collision_result *results);
void *object_properties_user_interface_allocate_hook(long size);
void *object_creation_user_interface_allocate_hook(long size);
bool shoot_probe_for_player_hook(long player_index, long *out_object_index);
void c_map_variant__apply_multiplayer_properties_hook(s_map_variant *thisptr, void *__formal, s_map_variant_placement_properties *properties, long object_index);
void c_map_variant__setup_object_properties_hook(s_variant_datum *placement);
void c_map_variant__initialize_from_scenario_hook(s_map_variant *thisptr, void *unused);
void c_map_variant__recalculate_quota_hook(s_map_variant *thisptr, void *unused, __int32 budgetIndex, char arg_4);
void c_map_variant__rebuild_quotas_from_hook(s_map_variant *thisptr, void *__formal, s_map_variant *other);
void c_map_variant__create_object_jump_hook();
long place_object_hook(s_map_variant *thisptr, void *__formal, long tag_index, long creation_type, long map_variant_index, real_point3d const *position, real_vector3d const *forward, real_vector3d const *up, long scenario_object_index, e_object_type object_type, s_map_variant_placement_properties *properties, unsigned short flags);
bool can_place_object_at_hook(long tag_index, real_point3d *position, long player_unit_index);
float light_intensity_function_evaluate(c_function_definition *thisptr, long light_index, float input, float range);
void light_color_function_evaluate(c_function_definition *thisptr, long light_index, float input, float range, real_rgb_color *color);
void light_intensity_function_hook();
void light_color_function_hook();
void add_simple_light_callback_hook(long light_index, long user_index, float intensity, c_lights_view *lights_view);
void c_map_variant__quantize_hook(s_map_variant *thisptr, void *unused);
void game_engine_update_hook();
bool game_engine_game_object_has_fallen_too_far_hook(long object_index);
bool collision_test_object_hook(long object_index, s_object_header *object_header, s_object_data *object, unsigned long test_flags, long object_type_mask, long ignore_object_index_1, long ignore_object_index_2, long ignore_object_index_3);
void multiplayer_object_submit_boundary_hook(s_multiplayer_object_boundary_geometry_data *boundary, real_argb_color *color, long object_index);
void c_multiplayer_candy_monitor_manager__monitor_object_hook(c_multiplayer_candy_monitor_manager *thisptr, void *__formal, long map_variant_index, long object_index);
void shield_impact_bloom_intensity_hook(long id, long count, float *data);
void game_sound_update_acoustics_hook(float dt);
void object_placement_create_active_zone_set_skies_hook(long scenario_index, unsigned long bsp_mask);
bool IgnoreRigidBodyNode(unsigned __int32 objectIndex, __int32 nodeIndex);
void rigid_body_hack_hook(c_runtime_node_to_physics_model_rigid_body_index_mapping *thisptr, void *__formal, long object_index, bool force);
long havok_cull_objects_filter_rigid_body_hook(hkpEntity *entity);
void c_havok_component__connect_to_havok_world_hook(c_havok_component *thisptr, void *unused);
void game_engine_garbage_collect_for_round_switch_object_delete_hook(long object_index);
s_multiplayer_object_properties *game_engine_find_available_spawn_location_objects_filter_hook(long object_index);
bool c_havok_contact_point__is_climbable_surface_hook(c_havok_contact_point *contact_point);
void map_variant_register_object_hook(long object_index, long map_variant_index, char registration_type);
void c_sandbox_engine__update_local_player_hook(c_sandbox_engine *thisptr, void *__formal, long player_index);
long c_map_variant__create_object_hook(s_map_variant *thisptr, void *__formal, long object_definition_index, long creation_type, long map_variant_index, real_point3d *position, real_vector3d *forward, real_vector3d *up, long scenario_datum_index, long object_type, s_map_variant_placement_properties *variant_properties, unsigned short object_placement_flags);
void c_map_variant__register_scenario_object_hook(s_map_variant *thisptr, void *__formal, long object_index, bool edited);
bool c_map_variant__update_scenario_object_properties_hook(s_map_variant *thisptr, void *__formal, long object_index);
long c_map_variant__get_scenario_placement_map_variant_index_hook(s_map_variant *thisptr, void *__formal, long object_type, long scenario_datum_index);
bool c_candy_spawner__spawn_object__new_from_scenario_object_hook(long object_type, long scenario_datum_index, void *scenario_object, s_tag_block *palette_block, char create_at_rest, char flags, s_object_placement_data *placement_data);

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern float const HELDOBJECT_DISTANCE_MIN; // 0x111AFB88
	extern float const HELDOBJECT_DISTANCE_CHANGE_MULTIPLIER; // 0x111AFB8C
	extern float const MONITOR_MOVEMENT_SPEEDS[7]; // 0x111AFB90
	extern wchar_t const *MONITOR_MOVEMENT_SPEED_NAMES[7]; // 0x11354370
	extern std::vector<void (__cdecl*)(unsigned int),std::allocator<void (__cdecl*)(unsigned int)> > s_ItemSpawnedCallbacks; // 0x124584C0
	extern real_vector3d global_zero3d; // 0x111AFB58
}
using namespace hades_file_local;
/* ---------- public code */

extern c_function_definition* _sub_10A5EEF0(c_function_definition *const);
_inline c_function_definition::c_function_definition() // 0x10A5EEF0
{
	mangled_x86(MANGLED_TODO, "??0c_function_definition@@QAE@XZ");
	// c_function_definition *const this;
	compiler_generated();
	todo("implement");
	_sub_10A5EEF0(this);
}

extern s_tag_data* _sub_10A5EF40(s_tag_data *const);
_inline s_tag_data::s_tag_data() // 0x10A5EF40
{
	mangled_x86(MANGLED_TODO, "??0s_tag_data@@QAE@XZ");
	// s_tag_data *const this;
	compiler_generated();
	todo("implement");
	_sub_10A5EF40(this);
}

namespace Patches
{
	namespace Forge
	{
		_extern void _sub_10A60560();
		void ApplyAll() // 0x10A60560
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@Forge@Patches@@YAXXZ");
			// procedure flags: nofpo
			// CForgeDeviceManager *forgeDeviceManager;
			todo("implement");
			_sub_10A60560();
		}

		_extern void _sub_10A603E0();
		void ApplyAfterTagsLoaded() // 0x10A603E0
		{
			mangled_x86(MANGLED_TODO, "?ApplyAfterTagsLoaded@Forge@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10A603E0();
		}

		void Tick() // 0x10A674B0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Tick@Forge@Patches@@YAXXZ");
			// procedure flags: nofpo
		}

		_extern void _sub_10A66A20(void (*)(unsigned __int32));
		void OnItemSpawned(void (*callback)(unsigned __int32)) // 0x10A66A20
		{
			mangled_x86(MANGLED_TODO, "?OnItemSpawned@Forge@Patches@@YAXP6AXI@Z@Z");
			// void (*callback)(unsigned __int32);
			todo("implement");
			_sub_10A66A20(callback);
		}
	}
}

/* ---------- private code */

_extern void _sub_10A60240(char const *);
void AddMapVariantUndoPoint(char const *summary) // 0x10A60240
{
	// `anonymous-namespace'::AddMapVariantUndoPoint
	// char const *summary;
	// s_map_variant *mapVariant;
	// function call : bool (*const)()
	// function call : s_map_variant *(*const)()
	todo("implement");
	_sub_10A60240(summary);
}

_extern void _sub_10A647D0(long, long);
void ApplyGrabOffset(long player_index, long object_index) // 0x10A647D0
{
	// `anonymous-namespace'::ApplyGrabOffset
	// static ...; // 0x10A64994
	// static ...; // 0x10A6497C
	// static ...; // 0x10A64974
	// long player_index;
	// long object_index;
	// s_player_datum *player;
	// s_object_data *unit;
	// s_object_data *object;
	// real_point3d crosshairPoint;
	// real_point3d unitPos;
	// s_sandbox_globals *sandboxGlobals;
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void (*const)(long, real_point3d *)
	todo("implement");
	_sub_10A647D0(player_index, object_index);
}

_extern void _sub_10A656C0(long, long);
void GrabObject(long player_index, long map_variant_index) // 0x10A656C0
{
	// `anonymous-namespace'::GrabObject
	// long map_variant_index;
	// long object_index;
	// Forge::ObjectSet &selection;
	// void (*const c_map_variant__remove_object)(s_map_variant *, long, long);
	// void (*const game_engine_sandox_apply_grab_object)(long, long);
	// void (*const change_object_physics_mode)(long, long);
	// s_map_variant *map_variant;
	{
		// long i;
		{
			// s_variant_datum const &placement;
			// long selection_object_index;
		}
	}
	// function call : s_map_variant *(*const)()
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : unsigned long (*const)(long)
	// function call : void (*const)(long, long)
	// function call : void (*const)(s_map_variant *, long, long)
	// function call : void (*const)(long, long, long)
	// function call : void (*const)(long, long)
	// function call : bool (*const)(long)
	todo("implement");
	_sub_10A656C0(player_index, map_variant_index);
}

_extern void _sub_10A65950(long);
void GrabSelection(long player_index) // 0x10A65950
{
	// `anonymous-namespace'::GrabSelection
	// long player_index;
	// Forge::ObjectSet const &selection;
	// void (*const game_engine_sandox_apply_grab_object)(long, long);
	// s_map_variant const *map_variant;
	{
		// __int32 i;
	}
	// function call : s_map_variant *(*const)()
	todo("implement");
	_sub_10A65950(player_index);
}

_extern void _sub_10A670C0();
void SubmitWorldBoundsForRendering() // 0x10A670C0
{
	// `anonymous-namespace'::SubmitWorldBoundsForRendering
	// procedure flags: nofpo
	// static ...; // 0x10A67331
	// static ...; // 0x10A6732B
	// static ...; // 0x10A67324
	// static ...; // 0x10A67300
	// static ...; // 0x10A672F8
	// real_argb_color color;
	// long player_index;
	// float depth;
	// long shader_tag_index;
	// s_map_variant *map_variant;
	// real_matrix4x3 matrix;
	// real_point3d center;
	// s_forge_globals_definition *forge_globals;
	// float width;
	// float height;
	// function call : unsigned long (*const)(long)
	// function call : bool (*const)(long, long *, long *)
	// function call : s_map_variant *(*const)()
	// function call : void (*const)(long, real_argb_color const *, real_matrix4x3 const *, float, float, float, float)
	todo("implement");
	_sub_10A670C0();
}

_extern void _sub_10A676D0();
void TryUndo() // 0x10A676D0
{
	// `anonymous-namespace'::TryUndo
	// procedure flags: nofpo
	// static ...; // 0x10A67860
	// static ...; // 0x10A67854
	// static ...; // 0x10A6784C
	// CForgeUndoManager &undoManager;
	// std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t> > message;
	todo("implement");
	_sub_10A676D0();
}

_extern void _sub_10A674D0();
void TryRedo() // 0x10A674D0
{
	// `anonymous-namespace'::TryRedo
	// procedure flags: nofpo
	// static ...; // 0x10A67660
	// static ...; // 0x10A67654
	// static ...; // 0x10A6764C
	// CForgeUndoManager &undoManager;
	// std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t> > message;
	todo("implement");
	_sub_10A674D0();
}

_extern void _sub_10A64E10();
void CanvasMap() // 0x10A64E10
{
	// `anonymous-namespace'::CanvasMap
	// procedure flags: nofpo
	// void (*const c_map_variant_placement__ctor)(s_variant_datum *);
	// long player_index;
	// s_map_variant *map_variant;
	{
		// long i;
		{
			// s_variant_datum &placement;
			// s_variant_quota &budget;
		}
	}
	// function call : s_map_variant *(*const)()
	// function call : unsigned long (*const)(long)
	// function call : void (*const)(s_variant_datum *)
	todo("implement");
	_sub_10A64E10();
}

_extern void _sub_10A66D30();
void ResetRuntime() // 0x10A66D30
{
	// `anonymous-namespace'::ResetRuntime
	// procedure flags: nofpo
	// s_game_engine_globals *game_engine_globals;
	{
		// long i;
		{
			// c_candy_spawner *spawner;
		}
	}
	// function call : void (*const)(long)
	// function call : void (*const)(void *, bool)
	todo("implement");
	_sub_10A66D30();
}

_extern void _sub_10A66510();
void HandlePrefabCommands() // 0x10A66510
{
	// `anonymous-namespace'::HandlePrefabCommands
	// procedure flags: nofpo
	// Modules::ModulePlayer &modulePlayer;
	// Modules::ModuleForge &moduleForge;
	// function call : unsigned long (*const)(long)
	todo("implement");
	_sub_10A66510();
}

_extern void _sub_10A66E30(long);
void SpawnItem(long tag_index) // 0x10A66E30
{
	// `anonymous-namespace'::SpawnItem
	// static ...; // 0x10A6702F
	// static ...; // 0x10A67024
	// static ...; // 0x10A6700C
	// static ...; // 0x10A67004
	// long tag_index;
	// long player_index;
	// s_simulation_queue_sandbox_event_data event_data;
	{
		// wchar_t buff[256];
	}
	// function call : unsigned long (*const)(long)
	// function call : bool (*const)(long, long *, long *)
	// function call : void (*const)(s_simulation_queue_sandbox_event_data *)
	todo("implement");
	_sub_10A66E30(tag_index);
}

_extern void _sub_10A65280(long, long);
void DoClone(long player_index, long cursor_object_index) // 0x10A65280
{
	// `anonymous-namespace'::DoClone
	// long cursor_object_index;
	{
		// float cloneDepth;
		// real_vector3d const &intersectNormal;
		// Modules::ModuleForge &forgeModule;
		// float cloneMultiplier;
		// long objectIndexToClone;
		{
			// __int32 i;
		}
	}
	todo("implement");
	_sub_10A65280(player_index, cursor_object_index);
}

_extern void _sub_10A667D0();
void HandleRuntimeReset() // 0x10A667D0
{
	// `anonymous-namespace'::HandleRuntimeReset
	// procedure flags: nofpo
	// Modules::ModuleForge &moduleForge;
	todo("implement");
	_sub_10A667D0();
}

_extern void _sub_10A65A80();
void HandleMapCanvas() // 0x10A65A80
{
	// `anonymous-namespace'::HandleMapCanvas
	// procedure flags: nofpo
	// Modules::ModuleForge &moduleForge;
	todo("implement");
	_sub_10A65A80();
}

_extern void _sub_10A66840();
void HandleSetPrematchCamera() // 0x10A66840
{
	// `anonymous-namespace'::HandleSetPrematchCamera
	// procedure flags: nofpo
	// Modules::ModuleForge &moduleForge;
	todo("implement");
	_sub_10A66840();
}

_extern void _sub_10A668C0();
void HandleSpawnItem() // 0x10A668C0
{
	// `anonymous-namespace'::HandleSpawnItem
	// procedure flags: nofpo
	// Modules::ModuleForge &moduleForge;
	// long &itemTagIndex;
	todo("implement");
	_sub_10A668C0();
}

_extern void _sub_10A66460();
void HandleOpenMapOptions() // 0x10A66460
{
	// `anonymous-namespace'::HandleOpenMapOptions
	// procedure flags: nofpo
	// Modules::ModuleForge &moduleForge;
	// long mapModifierObjectIndex;
	// function call : void (*const)(long, wchar_t const *, e_chud_message_context)
	todo("implement");
	_sub_10A66460();
}

_extern void _sub_10A65A20();
void HandleCommands() // 0x10A65A20
{
	// `anonymous-namespace'::HandleCommands
	// procedure flags: nofpo
	todo("implement");
	_sub_10A65A20();
}

_extern void _sub_10A66650();
void HandleRotationReset() // 0x10A66650
{
	// `anonymous-namespace'::HandleRotationReset
	// procedure flags: nofpo
	// static ...; // 0x10A6676A
	// static ...; // 0x10A66764
	// static ...; // 0x10A6674C
	// static ...; // 0x10A66744
	// Blam::Input::ActionState *uiUpAction;
	{
		// long heldObjectIndex;
		{
			// real_quaternion ident;
		}
	}
	// function call : unsigned long (*const)(long)
	// function call : bool (*const)(long, long *, long *)
	todo("implement");
	_sub_10A66650();
}

_extern void _sub_10A66150();
void HandleMovementSpeed() // 0x10A66150
{
	// `anonymous-namespace'::HandleMovementSpeed
	// procedure flags: nofpo
	// static ...; // 0x10A663B8
	// static ...; // 0x10A663AC
	// static ...; // 0x10A663A4
	// s_player_datum *player;
	// Blam::Input::ActionState *crouchAction;
	// static Modules::ModuleForge &`HandleMovementSpeed'::`2'::moduleForge; // 0x12458508
	// Blam::Input::ActionState *movementSpeedAction;
	// static __int32 `HandleMovementSpeed'::`2'::$TSS0; // 0x1245850C
	{
		// long currentSpeed;
		// wchar_t buff[256];
	}
	// function call : unsigned long (*const)(long)
	// function call : void (*const)(long, real_vector3d const *, real_vector3d const *)
	todo("implement");
	_sub_10A66150();
}

_extern void _sub_10A65FB0();
void HandleMonitorNoclip() // 0x10A65FB0
{
	// `anonymous-namespace'::HandleMonitorNoclip
	// procedure flags: nofpo
	// s_player_datum *player;
	// s_object_data *unit;
	// long player_index;
	// Modules::ModuleForge const &moduleForge;
	// bool noclipping;
	{
		// c_havok_component *havok_component;
	}
	// function call : unsigned long (*const)(long)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void (*const)(long, long)
	todo("implement");
	_sub_10A65FB0();
}

_extern void _sub_10A65AF0(long);
void HandleMonitorInput(long playerIndex) // 0x10A65AF0
{
	// `anonymous-namespace'::HandleMonitorInput
	// static ...; // 0x10A65EA3
	// static ...; // 0x10A65E89
	// static ...; // 0x10A65E78
	// static ...; // 0x10A65E54
	// static ...; // 0x10A65E4C
	// long playerIndex;
	// long heldObjectIndex;
	// Modules::ModuleForge &moduleForge;
	// long objectIndexUnderCrosshair;
	{
		// Blam::Input::ActionState *cloneAction;
		// Blam::Input::ActionState *uiRightAction;
	}
	{
		// Modules::CommandMap &commandMap;
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > previousValueStr;
		// unsigned long prevValue;
	}
	// function call : bool (*const)(long, long *, long *)
	// function call : long (*const)(e_user_interface_sound, long)
	todo("implement");
	_sub_10A65AF0(playerIndex);
}

_extern long _sub_10A65410(long);
long FindComplexObjectRigidBodyRootNode(long object_index) // 0x10A65410
{
	// `anonymous-namespace'::FindComplexObjectRigidBodyRootNode
	// long object_index;
	// s_object_definition *object_definition;
	// s_object_data *object;
	// s_physics_model_definition *physics_model;
	// s_model_definition *model;
	{
		// long i;
		{
			// s_physics_model_rigid_body const &rigid_body;
		}
	}
	// function call : void *(*const)(unsigned long, long)
	// function call : void *(*const)(unsigned long, long)
	// function call : void *(*const)(unsigned long, long)
	todo("implement");
	long __result = _sub_10A65410(object_index);
	return __result;
}

_extern void _sub_10A678D0(__int32);
void UpdateSelectionManipulationState(__int32 rootObjectIndex) // 0x10A678D0
{
	// `anonymous-namespace'::UpdateSelectionManipulationState
	// static ...; // 0x10A67AC0
	// static ...; // 0x10A67AB4
	// static ...; // 0x10A67AAC
	// __int32 rootObjectIndex;
	// Forge::ObjectSet const &selection;
	// s_object_data *rootObject;
	// s_map_variant *map_variant;
	{
		// long i;
		{
			// s_variant_datum &placement;
			// s_selectionState::ChildInfo &childInfo;
			// float scale;
			// real_point3d pos;
		}
	}
	// function call : void (*const)(long, real_point3d *)
	// function call : s_map_variant *(*const)()
	// function call : void (*const)(long, real_point3d *)
	todo("implement");
	_sub_10A678D0(rootObjectIndex);
}

extern s_forge_palette_item *_sub_10A655E0(long);
s_forge_palette_item *FindSandboxPaletteItem(long tag_index) // 0x10A655E0
{
	// `anonymous-namespace'::FindSandboxPaletteItem
	// long tag_index;
	// s_forge_globals_definition *forge_globals;
	{
		// long i;
	}
	todo("implement");
	s_forge_palette_item * __result = _sub_10A655E0(tag_index);
	return __result;
}

_extern bool _sub_10A6E7A0(s_map_variant *, s_scenario *);
bool initialize_map_variant_from_scenario(s_map_variant *thisptr, s_scenario *scenario) // 0x10A6E7A0
{
	// `anonymous-namespace'::initialize_map_variant_from_scenario
	// s_scenario *scenario;
	// s_tag_block *(*const scenario_get_object_type_scenario_datums)(s_scenario *, e_object_type, long *);
	// c_tag_block<s_scenario_object_palette_entry> *(*const scenario_get_object_type_scenario_palette)(s_scenario *, e_object_type);
	// unsigned __int32 (*const crc_checksum_buffer)(unsigned __int32, unsigned char *, long);
	// long totalObjectCount;
	// long scnrPlacementOffset;
	{
		// long type;
		{
			// s_object_type_definition *type_definition;
			// c_tag_block<s_scenario_object_palette_entry> &palette;
			{
				// s_tag_block *placementBlock;
			}
			{
				// long i;
				{
					// s_variant_quota &budgetEntry;
					// s_scenario_object_palette_entry &paletteEntry;
					// s_forge_palette_item *sandboxPaletteItem;
				}
			}
		}
	}
	// function call : unsigned __int32 (*const)(unsigned __int32, unsigned char *, long)
	// function call : s_object_type_definition *(*const)(e_object_type)
	// function call : s_tag_block *(*const)(s_scenario *, e_object_type, long *)
	// function call : c_tag_block<s_scenario_object_palette_entry> *(*const)(s_scenario *, e_object_type)
	todo("implement");
	bool __result = _sub_10A6E7A0(thisptr, scenario);
	return __result;
}

_extern long _sub_10A65030(s_map_variant *, long);
long CreateOrGetBudgetForItem(s_map_variant *thisptr, long tag_index) // 0x10A65030
{
	// `anonymous-namespace'::CreateOrGetBudgetForItem
	// static ...; // 0x10A651F4
	// static ...; // 0x10A651EC
	// s_map_variant *thisptr;
	// long tag_index;
	// long index;
	// long (*const c_map_variant__find_quota_index)(s_map_variant *, long);
	{
		// __int32 i;
		{
			// s_variant_quota const &budget;
		}
	}
	{
		// s_variant_quota &budget;
		// s_forge_palette_item *sandboxPaletteItem;
	}
	{
		// wchar_t buff[256];
	}
	// function call : long (*const)(s_map_variant *, long)
	todo("implement");
	long __result = _sub_10A65030(thisptr, tag_index);
	return __result;
}

_extern void _sub_10A66B90();
void RecalculateMapVariantBudget() // 0x10A66B90
{
	// `anonymous-namespace'::RecalculateMapVariantBudget
	// procedure flags: nofpo
	// s_map_variant *map_variant;
	{
		// long i;
	}
	{
		{
			// s_variant_datum &placement;
		}
	}
	{
		{
			// s_variant_quota &budgetItem;
		}
	}
	// function call : s_map_variant *(*const)()
	todo("implement");
	_sub_10A66B90();
}

_extern void _sub_10A669B0();
void ObjectOutOfWorldBoundsError() // 0x10A669B0
{
	// `anonymous-namespace'::ObjectOutOfWorldBoundsError
	// procedure flags: nofpo
	// function call : long (*const)(e_user_interface_sound, long)
	todo("implement");
	_sub_10A669B0();
}

_extern bool _sub_10A673E0(long, long);
bool TestBarrierTestProjectile(long barrierObjectIndex, long projectileObjectIndex) // 0x10A673E0
{
	// `anonymous-namespace'::TestBarrierTestProjectile
	// long projectileObjectIndex;
	// s_damage_owner *damageOwner;
	// s_object_data *projectileObject;
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	todo("implement");
	bool __result = _sub_10A673E0(barrierObjectIndex, projectileObjectIndex);
	return __result;
}

_extern void _sub_10A66A70(bool);
void OnMonitorModeChange(bool isMonitor) // 0x10A66A70
{
	// `anonymous-namespace'::OnMonitorModeChange
	// bool isMonitor;
	{
		// s_player_datum *player;
		// long player_index;
	}
	// function call : unsigned long (*const)(long)
	// function call : unsigned long (*const)(long)
	// function call : void (*const)(long, real_vector3d const *, real_vector3d const *)
	todo("implement");
	_sub_10A66A70(isMonitor);
}

_extern float _sub_10A6ACC0(s_map_variant *, void *, float *, float *);
float c_map_variant__get_budget_fraction_hook(s_map_variant *thisptr, void *__formal, float *budget_spent, float *budget_max) // 0x10A6ACC0
{
	// `anonymous-namespace'::c_map_variant__get_budget_fraction_hook
	// float *budget_max;
	// static Forge::ForgeObjectQuota `c_map_variant__get_budget_fraction_hook'::`2'::cachedQuota; // 0x12458514
	// static unsigned long `c_map_variant__get_budget_fraction_hook'::`2'::last_time; // 0x12458510
	todo("implement");
	float __result = _sub_10A6ACC0(thisptr, __formal, budget_spent, budget_max);
	return __result;
}

_extern bool _sub_10A6BA90(c_sandbox_engine *, void *);
bool c_sandbox_engine__initialize_for_new_map_hook(c_sandbox_engine *thisptr, void *__formal) // 0x10A6BA90
{
	// `anonymous-namespace'::c_sandbox_engine__initialize_for_new_map_hook
	// void *__formal;
	// bool (*const c_sandbox_engine__initialize_for_new_map)(c_sandbox_engine *);
	// function call : bool (*const)(c_sandbox_engine *)
	todo("implement");
	bool __result = _sub_10A6BA90(thisptr, __formal);
	return __result;
}

_extern void _sub_10A6B960(c_sandbox_engine *, void *);
void c_sandbox_engine__dispose_from_old_map_hook(c_sandbox_engine *thisptr, void *__formal) // 0x10A6B960
{
	// `anonymous-namespace'::c_sandbox_engine__dispose_from_old_map_hook
	// void *__formal;
	// void (*const c_sandbox_engine__dispose_from_old_map)(c_sandbox_engine *);
	// function call : void (*const)(c_sandbox_engine *)
	todo("implement");
	_sub_10A6B960(thisptr, __formal);
}

_extern void _sub_10A6C2E0(c_sandbox_engine *, void *);
void c_sandbox_engine__update_hook(c_sandbox_engine *thisptr, void *__formal) // 0x10A6C2E0
{
	// `anonymous-namespace'::c_sandbox_engine__update_hook
	// static ...; // 0x10A6C56C
	// static ...; // 0x10A6C554
	// static ...; // 0x10A6C54C
	// c_sandbox_engine *thisptr;
	// void *__formal;
	// long crosshair_object_index;
	// long player_index;
	// bool isMonitor;
	// long editing_object_index;
	// void (*const c_sandbox_engine__update)(c_sandbox_engine *);
	// long activeScreenCount;
	{
		// Modules::ModuleForge const &moduleForge;
	}
	// function call : void (*const)(c_sandbox_engine *)
	// function call : unsigned long (*const)(long)
	// function call : bool (*const)(long, long *, long *)
	todo("implement");
	_sub_10A6C2E0(thisptr, __formal);
}

_extern void _sub_10A6BC10(c_sandbox_engine *, void *, long, long, float, float, float);
void c_sandbox_engine__rotate_object_hook(c_sandbox_engine *thisptr, void *__formal, long playerIndex, long objectIndex, float yaw, float pitch, float roll) // 0x10A6BC10
{
	// `anonymous-namespace'::c_sandbox_engine__rotate_object_hook
	// long objectIndex;
	// float yaw;
	// float pitch;
	// float roll;
	// s_player_datum *player;
	// float const xn;
	// float const DEAD_ZONE;
	// float const zn;
	// static float `c_sandbox_engine__rotate_object_hook'::`2'::zticks; // 0x12458520
	// long const currentSnap;
	// float const yn;
	// Modules::ModuleForge const &moduleForge;
	// static float `c_sandbox_engine__rotate_object_hook'::`2'::xticks; // 0x12458518
	// static float `c_sandbox_engine__rotate_object_hook'::`2'::yticks; // 0x1245851C
	// real_matrix4x3 objectTransform;
	// float const rotationSensitivity;
	// void (*const c_sandbox_engine__rotate_object)(c_sandbox_engine *, long, long, float, float, float);
	// function call : unsigned long (*const)(long)
	// function call : void (*const)(c_sandbox_engine *, long, long, float, float, float)
	// function call : void (*const)(c_sandbox_engine *, long, long, float, float, float)
	// function call : real_matrix4x3 *(*const)(long, real_matrix4x3 *)
	todo("implement");
	_sub_10A6BC10(thisptr, __formal, playerIndex, objectIndex, yaw, pitch, roll);
}

_extern void _sub_10A6BA00(c_sandbox_engine *, void *, long);
void c_sandbox_engine__handle_deleted_object_hook(c_sandbox_engine *thisptr, void *__formal, long object_index) // 0x10A6BA00
{
	// `anonymous-namespace'::c_sandbox_engine__handle_deleted_object_hook
	// long object_index;
	// void (*const c_sandbox_engine__handle_deleted_object)(c_sandbox_engine *, long);
	// function call : void (*const)(c_sandbox_engine *, long)
	todo("implement");
	_sub_10A6BA00(thisptr, __formal, object_index);
}

_extern void _sub_10A6E2A0(long, long);
void game_engine_sandox_apply_grab_object_hook2(long player_index, long object_index) // 0x10A6E2A0
{
	// `anonymous-namespace'::game_engine_sandox_apply_grab_object_hook2
	// long object_index;
	// void (*const havok_object_rebuild_immediate)(long);
	// void (*const game_engine_sandbox_apply_grab_object_no_fail)(long, long);
	// function call : void (*const)(long)
	// function call : unsigned long (*const)(long)
	// function call : void (*const)(long, long)
	todo("implement");
	_sub_10A6E2A0(player_index, object_index);
}

_extern void _sub_10A6E370(long, long);
void game_engine_sandox_apply_grab_object_hook(long player_index, long map_variant_index) // 0x10A6E370
{
	// `anonymous-namespace'::game_engine_sandox_apply_grab_object_hook
	// long map_variant_index;
	todo("implement");
	_sub_10A6E370(player_index, map_variant_index);
}

_extern void _sub_10A6DC20(long, float, bool);
void game_engine_sandbox_stop_editing_object_hook(long map_variant_index, float force, bool activate_physics) // 0x10A6DC20
{
	// `anonymous-namespace'::game_engine_sandbox_stop_editing_object_hook
	// static ...; // 0x10A6E068
	// static ...; // 0x10A6E044
	// static ...; // 0x10A6E03C
	// long map_variant_index;
	// float force;
	// bool activate_physics;
	// s_object_data *droppedObject;
	// std::stack<unsigned int,std::deque<unsigned int,std::allocator<unsigned int> > > detachStack;
	// Forge::ObjectSet &selection;
	// void (*const game_engine_sandbox_stop_editing_object)(long, float, bool);
	// Forge::Magnets::MagnetPair const &magnetPair;
	// long playerIndex;
	// s_map_variant *map_variant;
	// void (*const object_set_uses_fixed_physics)(long, bool);
	// long droppedObjectIndex;
	// __int32 (*const c_map_variant__register_object)(void *, long, long);
	{
		// long objectIndex;
		{
			// s_object_data *object;
		}
	}
	{
		// real_point3d heldObjectPosition;
		// real_vector3d displacement;
	}
	{
		// s_object_data *object;
	}
	// function call : s_map_variant *(*const)()
	// function call : long (*const)(long)
	// function call : unsigned long (*const)(long)
	// function call : void (*const)(long, float, bool)
	// function call : void (*const)(long, real_point3d *)
	// function call : void (*const)(bool, long, real_point3d const *, real_vector3d const *, real_vector3d const *)
	// function call : void (*const)(long)
	// function call : __int32 (*const)(void *, long, long)
	// function call : void (*const)(long, bool)
	todo("implement");
	_sub_10A6DC20(map_variant_index, force, activate_physics);
}

_extern void _sub_10A6D850(long, long);
void game_engine_sandbox_delete_object_hook(long map_variant_index, long player_index) // 0x10A6D850
{
	// `anonymous-namespace'::game_engine_sandbox_delete_object_hook
	// static ...; // 0x10A6DA40
	// static ...; // 0x10A6DA28
	// static ...; // 0x10A6DA20
	// long map_variant_index;
	// long player_index;
	// void (*const game_engine_sandbox_delete_object)(long, long);
	// long heldObjectIndex;
	// Forge::ObjectSet const &selection;
	// long deletedObjectIndex;
	// long crosshairObjectIndex;
	// s_map_variant *map_variant;
	{
		// s_object_data *heldObject;
	}
	{
		// long i;
		{
			// s_variant_datum &placement;
		}
	}
	// function call : bool (*const)(long, long *, long *)
	// function call : s_map_variant *(*const)()
	// function call : void (*const)(long, long)
	// function call : void (*const)(long, long)
	todo("implement");
	_sub_10A6D850(map_variant_index, player_index);
}

_extern void _sub_10A6DAF0(long, long, real_point3d const *);
void game_engine_sandbox_place_object_hook(long tag_index, long player_index, real_point3d const *position) // 0x10A6DAF0
{
	// `anonymous-namespace'::game_engine_sandbox_place_object_hook
	// real_point3d const *position;
	// void (*const game_engine_sandbox_place_object)(long, long, real_point3d const *);
	// function call : unsigned long (*const)(long)
	// function call : void (*const)(long, long, real_point3d const *)
	todo("implement");
	_sub_10A6DAF0(tag_index, player_index, position);
}

_extern void _sub_10A64A30(long, long, s_map_variant_placement_properties *);
void ApplyObjectPropertiesToSelection(long playerIndex, long rootObjectIndex, s_map_variant_placement_properties *properties) // 0x10A64A30
{
	// `anonymous-namespace'::ApplyObjectPropertiesToSelection
	// static ...; // 0x10A64D34
	// static ...; // 0x10A64D10
	// static ...; // 0x10A64D08
	// long playerIndex;
	// long rootObjectIndex;
	// s_map_variant_placement_properties *properties;
	// void (*const game_engine_sandbox_update_variant_object_properties)(long, long, s_map_variant_placement_properties *);
	// Forge::ObjectSet const &selection;
	// bool isForgeScenery;
	// s_map_variant *map_variant;
	{
		// long i;
		{
			// s_variant_datum &placement;
			// s_map_variant_placement_properties tmp;
			{
				// std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<int const ,ChildInfo> > > > it;
				{
					// real_point3d newPos;
					// float deltaScale;
				}
			}
		}
	}
	// function call : s_map_variant *(*const)()
	// function call : void (*const)(bool, long, real_point3d const *, real_vector3d const *, real_vector3d const *)
	// function call : void (*const)(long, long, s_map_variant_placement_properties *)
	todo("implement");
	_sub_10A64A30(playerIndex, rootObjectIndex, properties);
}

_extern void _sub_10A6E1C0(long, long, s_map_variant_placement_properties *);
void game_engine_sandbox_update_variant_object_properties_hook(long player_index, long map_variant_index, s_map_variant_placement_properties *properties) // 0x10A6E1C0
{
	// `anonymous-namespace'::game_engine_sandbox_update_variant_object_properties_hook
	// s_map_variant_placement_properties *properties;
	// void (*const ame_engine_sandbox_update_variant_object_properties)(unsigned __int32, unsigned short, s_map_variant_placement_properties *);
	// s_map_variant *map_variant;
	// long changedObjectIndex;
	// function call : s_map_variant *(*const)()
	// function call : void (*const)(unsigned __int32, unsigned short, s_map_variant_placement_properties *)
	todo("implement");
	_sub_10A6E1C0(player_index, map_variant_index, properties);
}

_extern void _sub_10A6C960(long, s_character_physics_update_input_datum *, c_character_physics_component *, float, float);
void character_physics_update_input_datum_initialize_flying_hook(long unit_index, s_character_physics_update_input_datum *physics_input, c_character_physics_component *physics_component, float a6, float a7) // 0x10A6C960
{
	// `anonymous-namespace'::character_physics_update_input_datum_initialize_flying_hook
	// float a7;
	// s_player_datum *player;
	// void (*const character_physics_update_input_datum_initialize_flying)(long, s_character_physics_update_input_datum *, c_character_physics_component *, float, float);
	// long playerIndex;
	{
		// s_object_data *biped;
		// float t;
		// Modules::ModuleForge &moduleForge;
		// float destination;
		// real_vector3d *velocity;
		// float direction;
		// float maxVelocity;
		// float &monitorSpeed;
		// float acceleration;
		// Blam::Input::ActionState *uiLeftBumper;
		// static float `character_physics_update_input_datum_initialize_flying_hook'::`5'::s_Velocity; // 0x12458524
		// float deceleration;
		// Blam::Input::ActionState *uiRightBumper;
		// bool movementDisabled;
		// long activeScreenCount;
		// s_biped_definition *biped_definition;
	}
	// function call : unsigned long (*const)(long)
	// function call : bool (*const)(long, long *, long *)
	// function call : void (*const)(long, s_character_physics_update_input_datum *, c_character_physics_component *, float, float)
	// function call : void *(*const)(unsigned long, long)
	// function call : float (*const)()
	// function call : void (*const)(long, s_character_physics_update_input_datum *, c_character_physics_component *, float, float)
	todo("implement");
	_sub_10A6C960(unit_index, physics_input, physics_component, a6, a7);
}

_extern void _sub_10A70320(bool, long, real_point3d const *, real_vector3d const *, real_vector3d const *);
void update_edited_object_transform_hook(bool apply_gravity, long object_index, real_point3d const *position, real_vector3d const *forward, real_vector3d const *up) // 0x10A70320
{
	// `anonymous-namespace'::update_edited_object_transform_hook
	// bool apply_gravity;
	// long object_index;
	// real_point3d const *position;
	// real_vector3d const *forward;
	// real_vector3d const *up;
	// Forge::ObjectSet const &selection;
	// unsigned long playerHandle;
	// s_object_data *heldObject;
	{
		// real_point3d newPos;
		// real_vector3d offset;
	}
	// function call : long (*const)(long)
	// function call : bool (*const)(long)
	// function call : void (*const)(bool, long, real_point3d const *, real_vector3d const *, real_vector3d const *)
	// function call : void (*const)(bool, long, real_point3d const *, real_vector3d const *, real_vector3d const *)
	todo("implement");
	_sub_10A70320(apply_gravity, object_index, position, forward, up);
}

_extern bool _sub_10A70080(unsigned long, unsigned long, real_point3d const *, real_vector3d const *, __int32, __int32, s_collision_result *);
bool shoot_probe_for_player_test_vector_hook(unsigned long flags, unsigned long test_object_flags, real_point3d const *origin, real_vector3d const *vector, __int32 ignore_object_index1, __int32 ignore_object_index2, s_collision_result *results) // 0x10A70080
{
	// `anonymous-namespace'::shoot_probe_for_player_test_vector_hook
	// s_collision_result *results;
	// bool (*const collision_test_vector)(unsigned long, unsigned long, real_point3d const *, real_vector3d const *, long, long, s_collision_result *);
	// function call : bool (*const)(unsigned long, unsigned long, real_point3d const *, real_vector3d const *, long, long, s_collision_result *)
	todo("implement");
	bool __result = _sub_10A70080(flags, test_object_flags, origin, vector, ignore_object_index1, ignore_object_index2, results);
	return __result;
}

_extern void *_sub_10A6F670(long);
void *object_properties_user_interface_allocate_hook(long size) // 0x10A6F670
{
	// `anonymous-namespace'::object_properties_user_interface_allocate_hook
	// static ...; // 0x10A6F78C
	// static ...; // 0x10A6F77C
	// static ...; // 0x10A6F764
	// static ...; // 0x10A6F75C
	// long size;
	// long heldObjectIndex;
	// long objectIndexUnderCrosshair;
	// long playerIndex;
	{
		// long currentObjectIndex;
		// s_object_data *currentObject;
	}
	// function call : unsigned long (*const)(long)
	// function call : bool (*const)(long, long *, long *)
	todo("implement");
	void * __result = _sub_10A6F670(size);
	return __result;
}

_extern void *_sub_10A6F530(long);
void *object_creation_user_interface_allocate_hook(long size) // 0x10A6F530
{
	// `anonymous-namespace'::object_creation_user_interface_allocate_hook
	// long size;
	todo("implement");
	void * __result = _sub_10A6F530(size);
	return __result;
}

_extern bool _sub_10A6FF60(long, long *);
bool shoot_probe_for_player_hook(long player_index, long *out_object_index) // 0x10A6FF60
{
	// `anonymous-namespace'::shoot_probe_for_player_hook
	// long *out_object_index;
	// bool (*const shoot_probe_for_player)(long, long *);
	{
		// s_sandbox_globals *sandbox_globals;
		// long player_absolute_index;
		{
			// bool ret;
			// float old_distance;
		}
	}
	// function call : unsigned long (*const)(long)
	// function call : bool (*const)(long, long *)
	// function call : bool (*const)(long, long *)
	todo("implement");
	bool __result = _sub_10A6FF60(player_index, out_object_index);
	return __result;
}

_extern void _sub_10A6A9B0(s_map_variant *, void *, s_map_variant_placement_properties *, long);
void c_map_variant__apply_multiplayer_properties_hook(s_map_variant *thisptr, void *__formal, s_map_variant_placement_properties *properties, long object_index) // 0x10A6A9B0
{
	// `anonymous-namespace'::c_map_variant__apply_multiplayer_properties_hook
	// s_map_variant *thisptr;
	// void *__formal;
	// s_map_variant_placement_properties *properties;
	// long object_index;
	// s_object_data *object;
	// void (*const change_object_physics_mode)(long, long);
	// char oldZoneShape;
	// void (*const c_map_variant__apply_multiplayer_properties)(s_map_variant *, s_map_variant_placement_properties *, long);
	// s_multiplayer_object_properties *mpProperties;
	// function call : s_multiplayer_object_properties *(*const)(unsigned long)
	// function call : void (*const)(s_map_variant *, s_map_variant_placement_properties *, long)
	todo("implement");
	_sub_10A6A9B0(thisptr, __formal, properties, object_index);
}

_extern void _sub_10A6B2C0(s_variant_datum *);
void c_map_variant__setup_object_properties_hook(s_variant_datum *placement) // 0x10A6B2C0
{
	// `anonymous-namespace'::c_map_variant__setup_object_properties_hook
	// s_variant_datum *placement;
	// long (*const weapon_get_rounds_inventory)(long, short, bool);
	// s_object_data *object;
	// s_multiplayer_object_properties *mpProperties;
	{
		// s_weapon_definition *weaponDefinition;
		{
			// long rounds;
			// s_weapon_magazine_definition &magazine;
		}
	}
	// function call : s_multiplayer_object_properties *(*const)(unsigned long)
	// function call : void *(*const)(unsigned long, long)
	// function call : long (*const)(long, short, bool)
	todo("implement");
	_sub_10A6B2C0(placement);
}

_extern void _sub_10A6AE40(s_map_variant *, void *);
void c_map_variant__initialize_from_scenario_hook(s_map_variant *thisptr, void *unused) // 0x10A6AE40
{
	// `anonymous-namespace'::c_map_variant__initialize_from_scenario_hook
	// void *unused;
	// s_scenario *scenario;
	// function call : void (*const)(s_map_variant *, long)
	// function call : bool (*const)()
	// function call : void (*const)(s_map_variant *, long)
	todo("implement");
	_sub_10A6AE40(thisptr, unused);
}

_extern void _sub_10A6B0A0(s_map_variant *, void *, __int32, char);
void c_map_variant__recalculate_quota_hook(s_map_variant *thisptr, void *unused, __int32 budgetIndex, char arg_4) // 0x10A6B0A0
{
	// `anonymous-namespace'::c_map_variant__recalculate_quota_hook
	// char arg_4;
	// s_variant_quota &budget;
	// void (*const c_map_variant_update_item_budget)(s_map_variant *, __int32, char);
	{
		// s_object_definition *objectDef;
	}
	// function call : void (*const)(s_map_variant *, __int32, char)
	// function call : bool (*const)()
	// function call : void *(*const)(unsigned long, long)
	todo("implement");
	_sub_10A6B0A0(thisptr, unused, budgetIndex, arg_4);
}

_extern void _sub_10A6AFC0(s_map_variant *, void *, s_map_variant *);
void c_map_variant__rebuild_quotas_from_hook(s_map_variant *thisptr, void *__formal, s_map_variant *other) // 0x10A6AFC0
{
	// `anonymous-namespace'::c_map_variant__rebuild_quotas_from_hook
	// s_map_variant *other;
	{
		// long i;
		{
			// s_variant_quota &budget;
			{
				// long newBudgetIndex;
			}
		}
	}
	todo("implement");
	_sub_10A6AFC0(thisptr, __formal, other);
}

__declspec(naked) void c_map_variant__create_object_jump_hook() // 0x10A6AC90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_map_variant__create_object_jump_hook@@YAXXZ");
	// `anonymous-namespace'::c_map_variant__create_object_jump_hook
	// procedure flags: nofpo

	__asm
	{
		push ebp
		mov ebp, esp
		sub esp, 194h
		pushad
		push dword ptr [ebp + 8]
		push ecx
		call CreateOrGetBudgetForItem
		add esp, 8
		popad
		mov eax, 0582119h
		jmp eax
	}
}

_extern long _sub_10A6F800(s_map_variant *, void *, long, long, long, real_point3d const *, real_vector3d const *, real_vector3d const *, long, e_object_type, s_map_variant_placement_properties *, unsigned short);
long place_object_hook(s_map_variant *thisptr, void *__formal, long tag_index, long creation_type, long map_variant_index, real_point3d const *position, real_vector3d const *forward, real_vector3d const *up, long scenario_object_index, e_object_type object_type, s_map_variant_placement_properties *properties, unsigned short flags) // 0x10A6F800
{
	// `anonymous-namespace'::place_object_hook
	// unsigned short flags;
	// long object_index;
	{
		// std::vector<void (__cdecl*)(unsigned int),std::allocator<void (__cdecl*)(unsigned int)> > &<range>$L0;
		// void (**<begin>$L0)(unsigned __int32);
		// void (**<end>$L0)(unsigned __int32);
		{
			// void (*&cb)(unsigned __int32);
		}
	}
	// function call : long (*const)(s_map_variant *, long, long, long, real_point3d const *, real_vector3d const *, real_vector3d const *, long, long, s_map_variant_placement_properties const *, short)
	// function call : void (*)(unsigned __int32)
	todo("implement");
	long __result = _sub_10A6F800(thisptr, __formal, tag_index, creation_type, map_variant_index, position, forward, up, scenario_object_index, object_type, properties, flags);
	return __result;
}

_extern bool _sub_10A6C710(long, real_point3d *, long);
bool can_place_object_at_hook(long tag_index, real_point3d *position, long player_unit_index) // 0x10A6C710
{
	// `anonymous-namespace'::can_place_object_at_hook
	// long player_unit_index;
	// s_object_definition *object_definition;
	// bool (*const calculate_sphere_fixed_position)(float, float, long, long, long, real_point3d const *, real_point3d const *, long, real_point3d *, bool);
	// float boundingRadius;
	{
		// s_model_definition *hlmtDef;
		{
			// s_model_object_data const &modelobjectData;
		}
	}
	// function call : void *(*const)(unsigned long, long)
	// function call : void *(*const)(unsigned long, long)
	// function call : bool (*const)(float, float, long, long, long, real_point3d const *, real_point3d const *, long, real_point3d *, bool)
	// function call : s_map_variant *(*const)()
	todo("implement");
	bool __result = _sub_10A6C710(tag_index, position, player_unit_index);
	return __result;
}

_extern float _sub_10A6EDB0(c_function_definition *, long, float, float);
float light_intensity_function_evaluate(c_function_definition *thisptr, long light_index, float input, float range) // 0x10A6EDB0
{
	// `anonymous-namespace'::light_intensity_function_evaluate
	// c_function_definition *thisptr;
	// long light_index;
	// float input;
	// float range;
	// static light_intensity_function_evaluate::__l2::s_functionData `light_intensity_function_evaluate'::`2'::functionData; // 0x12458528
	// s_light_datum *light;
	// s_object_data *lightObject;
	{
		// unsigned long lightFlags;
		// s_multiplayer_object_properties *mpProperties;
		{
			// c_function_definition temp_function;
			// Forge::ForgeLightProperties const *lightProperties;
		}
	}
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : s_multiplayer_object_properties *(*const)(unsigned long)
	// function call : void *(*const)(unsigned long, long)
	todo("implement");
	float __result = _sub_10A6EDB0(thisptr, light_index, input, range);
	return __result;
}

_extern void _sub_10A6EB50(c_function_definition *, long, float, float, real_rgb_color *);
void light_color_function_evaluate(c_function_definition *thisptr, long light_index, float input, float range, real_rgb_color *color) // 0x10A6EB50
{
	// `anonymous-namespace'::light_color_function_evaluate
	// real_rgb_color *color;
	// void (*const c_function_definition__evaluate_color)(c_function_definition *, float, float, real_rgb_color *);
	// s_light_datum *light;
	// s_object_data *lightObject;
	{
		// unsigned long lightFlags;
		// s_multiplayer_object_properties *mpProperties;
		{
			// Forge::ForgeLightProperties const *lightProperties;
			// float intensity;
		}
	}
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : s_multiplayer_object_properties *(*const)(unsigned long)
	// function call : void *(*const)(unsigned long, long)
	todo("implement");
	_sub_10A6EB50(thisptr, light_index, input, range, color);
}

__declspec(naked) void light_intensity_function_hook() // 0x10A6F140
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?light_intensity_function_hook@@YAXXZ");
	// procedure flags: nofpo

	__asm
	{
		mov edx, [ebp + 8]
		jmp light_intensity_function_evaluate
	}
}

extern s_selectionState* _sub_10A5E590(s_selectionState *const);
_inline s_selectionState::s_selectionState() // 0x10A5E590
{
	// `anonymous-namespace'::<unnamed-type-selectionState>::<unnamed-type-selectionState>
	// s_selectionState *const this;
	compiler_generated();
	todo("implement");
	_sub_10A5E590(this);
}

extern s_selectionState::ChildInfo* _sub_10A5EE30(s_selectionState::ChildInfo *const);
_inline s_selectionState::ChildInfo::ChildInfo() // 0x10A5EE30
{
	// `anonymous-namespace'::<unnamed-type-selectionState>::ChildInfo::ChildInfo
	// s_selectionState::ChildInfo *const this;
	compiler_generated();
	todo("implement");
	_sub_10A5EE30(this);
}

__declspec(naked) void light_color_function_hook() // 0x10A6EDA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?light_color_function_hook@@YAXXZ");
	// procedure flags: nofpo

	__asm
	{
		mov edx, [ebp + 8]
		jmp light_color_function_evaluate
	}
}

_extern void _sub_10A5EFA0(s_selectionState *const);
_inline s_selectionState::~s_selectionState() // 0x10A5EFA0
{
	// `anonymous-namespace'::<unnamed-type-selectionState>::~<unnamed-type-selectionState>
	// s_selectionState *const this;
	compiler_generated();
	todo("implement");
	_sub_10A5EFA0(this);
}

extern s_selectionState &_sub_10A5F740(s_selectionState *const, s_selectionState &);
_inline s_selectionState &s_selectionState::operator=(s_selectionState &__that) // 0x10A5F740
{
	// `anonymous-namespace'::<unnamed-type-selectionState>::operator=
	// s_selectionState &__that;
	compiler_generated();
	todo("implement");
	s_selectionState & __result = _sub_10A5F740(this, __that);
	return __result;
}

_extern void _sub_10A6A160(long, long, float, c_lights_view *);
void add_simple_light_callback_hook(long light_index, long user_index, float intensity, c_lights_view *lights_view) // 0x10A6A160
{
	// `anonymous-namespace'::add_simple_light_callback_hook
	// long light_index;
	// long user_index;
	// float intensity;
	// c_lights_view *lights_view;
	// char *lightDef;
	// void (*const add_simple_light_callback)(long, long, float, c_lights_view *);
	// void (*const c_lights_view__update)(c_lights_view *, real_point3d, real_rgb_color, float, float, real_vector3d, float, float, float);
	// unsigned long lightFlags;
	// s_light_datum *light;
	{
		// s_multiplayer_object_properties *multiplayer_properties;
		{
			// real_rgb_color color;
			// float percent_spherical;
			// float fov;
			// float angular_smoothness;
			// float distance_diffusion;
			// Forge::ForgeLightProperties const *lightProperties;
			// float maximum_distance;
		}
	}
	// function call : void *(*const)(unsigned long, long)
	// function call : s_multiplayer_object_properties *(*const)(unsigned long)
	// function call : void (*const)(c_lights_view *, real_point3d, real_rgb_color, float, float, real_vector3d, float, float, float)
	// function call : void (*const)(long, long, float, c_lights_view *)
	todo("implement");
	_sub_10A6A160(light_index, user_index, intensity, lights_view);
}

_extern void _sub_10A6AFA0(s_map_variant *, void *);
void c_map_variant__quantize_hook(s_map_variant *thisptr, void *unused) // 0x10A6AFA0
{
	// `anonymous-namespace'::c_map_variant__quantize_hook
	// void *unused;
	todo("implement");
	_sub_10A6AFA0(thisptr, unused);
}

_extern void _sub_10A6E3C0();
void game_engine_update_hook() // 0x10A6E3C0
{
	// `anonymous-namespace'::game_engine_update_hook
	// procedure flags: nofpo
	// function call : bool (*const)()
	// function call : bool (*const)()
	todo("implement");
	_sub_10A6E3C0();
}

_extern bool _sub_10A6D690(long);
bool game_engine_game_object_has_fallen_too_far_hook(long object_index) // 0x10A6D690
{
	// `anonymous-namespace'::game_engine_game_object_has_fallen_too_far_hook
	// long object_index;
	// bool (*const game_engine_game_object_has_fallen_too_far)(long);
	// function call : bool (*const)(long)
	todo("implement");
	bool __result = _sub_10A6D690(object_index);
	return __result;
}

_extern bool _sub_10A6D0A0(long, s_object_header *, s_object_data *, unsigned long, long, long, long, long);
bool collision_test_object_hook(long object_index, s_object_header *object_header, s_object_data *object, unsigned long test_flags, long object_type_mask, long ignore_object_index_1, long ignore_object_index_2, long ignore_object_index_3) // 0x10A6D0A0
{
	// `anonymous-namespace'::collision_test_object_hook
	// long ignore_object_index_3;
	// long playerIndex;
	// s_forge_globals_definition *forge_globals;
	// bool (*const test_object)(long, s_object_header *, s_object_data *, unsigned long, unsigned long, long, long, long);
	// s_multiplayer_object_properties *mpProperties;
	{
		// bool allowsProjectiles;
		// Forge::ReforgeObjectProperties *reforgeProperties;
	}
	// function call : bool (*const)(long, s_object_header *, s_object_data *, unsigned long, unsigned long, long, long, long)
	// function call : unsigned long (*const)(long)
	// function call : bool (*const)(long, long *, long *)
	// function call : s_multiplayer_object_properties *(*const)(unsigned long)
	// function call : unsigned long (*const)(long)
	// function call : bool (*const)(long, long *, long *)
	todo("implement");
	bool __result = _sub_10A6D0A0(object_index, object_header, object, test_flags, object_type_mask, ignore_object_index_1, ignore_object_index_2, ignore_object_index_3);
	return __result;
}

_extern void _sub_10A6F470(s_multiplayer_object_boundary_geometry_data *, real_argb_color *, long);
void multiplayer_object_submit_boundary_hook(s_multiplayer_object_boundary_geometry_data *boundary, real_argb_color *color, long object_index) // 0x10A6F470
{
	// `anonymous-namespace'::multiplayer_object_submit_boundary_hook
	// long object_index;
	// void (*const multiplayer_object_submit_boundary)(s_multiplayer_object_boundary_geometry_data *, real_argb_color *, long);
	// s_object_data *object;
	// s_forge_globals_definition *forge_globals;
	// function call : void (*const)(s_multiplayer_object_boundary_geometry_data *, real_argb_color *, long)
	todo("implement");
	_sub_10A6F470(boundary, color, object_index);
}

_extern void _sub_10A6B8B0(c_multiplayer_candy_monitor_manager *, void *, long, long);
void c_multiplayer_candy_monitor_manager__monitor_object_hook(c_multiplayer_candy_monitor_manager *thisptr, void *__formal, long map_variant_index, long object_index) // 0x10A6B8B0
{
	// `anonymous-namespace'::c_multiplayer_candy_monitor_manager__monitor_object_hook
	// long object_index;
	// void (*const c_multiplayer_candy_monitor_manager__monitor_object)(c_multiplayer_candy_monitor_manager *, long, long);
	// function call : void (*const)(c_multiplayer_candy_monitor_manager *, long, long)
	todo("implement");
	_sub_10A6B8B0(thisptr, __formal, map_variant_index, object_index);
}

_extern void _sub_10A6FDE0(long, long, float *);
void shield_impact_bloom_intensity_hook(long id, long count, float *data) // 0x10A6FDE0
{
	// `anonymous-namespace'::shield_impact_bloom_intensity_hook
	// float *data;
	// void (*const rasterizer_set_pixel_shader_constant)(__int32, __int32, float *);
	{
		// float intensity;
	}
	// function call : void (*const)(__int32, __int32, float *)
	todo("implement");
	_sub_10A6FDE0(id, count, data);
}

_extern void _sub_10A6E440(float);
void game_sound_update_acoustics_hook(float dt) // 0x10A6E440
{
	// `anonymous-namespace'::game_sound_update_acoustics_hook
	// float dt;
	// void (*const game_sound_update_acoustics)(float);
	// function call : void (*const)(float)
	todo("implement");
	_sub_10A6E440(dt);
}

_extern void _sub_10A6F5D0(long, unsigned long);
void object_placement_create_active_zone_set_skies_hook(long scenario_index, unsigned long bsp_mask) // 0x10A6F5D0
{
	// `anonymous-namespace'::object_placement_create_active_zone_set_skies_hook
	// unsigned long bsp_mask;
	// void (*const object_placement_create_active_zone_set_skies)(long, unsigned long);
	// function call : bool (*const)()
	// function call : void (*const)(long, unsigned long)
	todo("implement");
	_sub_10A6F5D0(scenario_index, bsp_mask);
}

_extern bool _sub_10A66940(unsigned __int32, __int32);
bool IgnoreRigidBodyNode(unsigned __int32 objectIndex, __int32 nodeIndex) // 0x10A66940
{
	// `anonymous-namespace'::IgnoreRigidBodyNode
	// __int32 nodeIndex;
	todo("implement");
	bool __result = _sub_10A66940(objectIndex, nodeIndex);
	return __result;
}

_extern void _sub_10A6FA00(c_runtime_node_to_physics_model_rigid_body_index_mapping *, void *, long, bool);
void rigid_body_hack_hook(c_runtime_node_to_physics_model_rigid_body_index_mapping *thisptr, void *__formal, long object_index, bool force) // 0x10A6FA00
{
	// `anonymous-namespace'::rigid_body_hack_hook
	// static ...; // 0x10A6FC6C
	// c_runtime_node_to_physics_model_rigid_body_index_mapping *thisptr;
	// void *__formal;
	// long object_index;
	// bool force;
	// s_object_definition *object_definition;
	// s_object_data *object;
	// s_physics_model_definition *physics_model;
	// bool (*const calculate_model_region_and_permutation_from_physics_model_region_and_permutation)(long, long, long, long, long *, long *);
	// s_model_definition *model;
	{
		// long i;
	}
	{
		{
			// long model_region_index;
			// c_runtime_node_to_physics_model_rigid_body_index_mapping::s_mapping *mapping;
			// long model_permutation_index;
			// s_physics_model_rigid_body *rigid_body;
		}
	}
	// function call : void *(*const)(unsigned long, long)
	// function call : void *(*const)(unsigned long, long)
	// function call : void *(*const)(unsigned long, long)
	// function call : bool (*const)(long, long, long, long, long *, long *)
	todo("implement");
	_sub_10A6FA00(thisptr, __formal, object_index, force);
}

_extern long _sub_10A6E6D0(hkpEntity *);
long havok_cull_objects_filter_rigid_body_hook(hkpEntity *entity) // 0x10A6E6D0
{
	// `anonymous-namespace'::havok_cull_objects_filter_rigid_body_hook
	// hkpEntity *entity;
	// long havok_component_index;
	{
		// c_havok_component *havok_component;
		// long object_index;
	}
	// function call : long (*const)(hkpEntity const *)
	todo("implement");
	long __result = _sub_10A6E6D0(entity);
	return __result;
}

_extern void _sub_10A6A770(c_havok_component *, void *);
void c_havok_component__connect_to_havok_world_hook(c_havok_component *thisptr, void *unused) // 0x10A6A770
{
	// `anonymous-namespace'::c_havok_component__connect_to_havok_world_hook
	// void *unused;
	// void (*const c_havok_component__connect_to_havok_world)(c_havok_component *);
	// bool shouldBeFixed;
	// long object_index;
	{
		// long rigidBodyCount;
		{
			// __int32 i;
			{
				// unsigned char *rigidBody;
			}
		}
	}
	// function call : void (*const)(c_havok_component *)
	todo("implement");
	_sub_10A6A770(thisptr, unused);
}

_extern void _sub_10A6D720(long);
void game_engine_garbage_collect_for_round_switch_object_delete_hook(long object_index) // 0x10A6D720
{
	// `anonymous-namespace'::game_engine_garbage_collect_for_round_switch_object_delete_hook
	// long object_index;
	// s_object_data *object;
	// void (*const object_delete_immediately)(unsigned __int32);
	// s_forge_globals_definition *forge_globals;
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void (*const)(unsigned __int32)
	todo("implement");
	_sub_10A6D720(object_index);
}

extern s_multiplayer_object_properties *_sub_10A6D5B0(long);
s_multiplayer_object_properties *game_engine_find_available_spawn_location_objects_filter_hook(long object_index) // 0x10A6D5B0
{
	// `anonymous-namespace'::game_engine_find_available_spawn_location_objects_filter_hook
	// long object_index;
	// s_object_data *object;
	// s_forge_globals_definition *forge_globals;
	// function call : s_multiplayer_object_properties *(*const)(unsigned long)
	todo("implement");
	s_multiplayer_object_properties * __result = _sub_10A6D5B0(object_index);
	return __result;
}

_extern bool _sub_10A6A8A0(c_havok_contact_point *);
bool c_havok_contact_point__is_climbable_surface_hook(c_havok_contact_point *contact_point) // 0x10A6A8A0
{
	// `anonymous-namespace'::c_havok_contact_point__is_climbable_surface_hook
	// c_havok_contact_point *contact_point;
	// s_multiplayer_object_properties *multiplayer_properties;
	// long object_index;
	// unsigned long surface_flags;
	{
		// Forge::ReforgeObjectProperties *reforge_properties;
	}
	// function call : s_multiplayer_object_properties *(*const)(unsigned long)
	todo("implement");
	bool __result = _sub_10A6A8A0(contact_point);
	return __result;
}

_extern void _sub_10A6F150(long, long, char);
void map_variant_register_object_hook(long object_index, long map_variant_index, char registration_type) // 0x10A6F150
{
	// `anonymous-namespace'::map_variant_register_object_hook
	// char registration_type;
	// void (*const map_variant_register_object)(long, long, char);
	// function call : s_map_variant *(*const)()
	// function call : void (*const)(long, long, char)
	todo("implement");
	_sub_10A6F150(object_index, map_variant_index, registration_type);
}

_extern void _sub_10A6C650(c_sandbox_engine *, void *, long);
void c_sandbox_engine__update_local_player_hook(c_sandbox_engine *thisptr, void *__formal, long player_index) // 0x10A6C650
{
	// `anonymous-namespace'::c_sandbox_engine__update_local_player_hook
	// long player_index;
	// void (*const c_sandbox_engine__update_local_player)(c_sandbox_engine *, long);
	// function call : long (*const)(long)
	// function call : void (*const)(c_sandbox_engine *, long)
	todo("implement");
	_sub_10A6C650(thisptr, __formal, player_index);
}

_extern long _sub_10A6ABD0(s_map_variant *, void *, long, long, long, real_point3d *, real_vector3d *, real_vector3d *, long, long, s_map_variant_placement_properties *, unsigned short);
long c_map_variant__create_object_hook(s_map_variant *thisptr, void *__formal, long object_definition_index, long creation_type, long map_variant_index, real_point3d *position, real_vector3d *forward, real_vector3d *up, long scenario_datum_index, long object_type, s_map_variant_placement_properties *variant_properties, unsigned short object_placement_flags) // 0x10A6ABD0
{
	// `anonymous-namespace'::c_map_variant__create_object_hook
	// unsigned short object_placement_flags;
	// long (*const c_map_variant__create_object)(s_map_variant *, void *, long, long, long, real_point3d *, real_vector3d *, real_vector3d *, long, long, s_map_variant_placement_properties *, unsigned short);
	// function call : long (*const)(s_map_variant *, void *, long, long, long, real_point3d *, real_vector3d *, real_vector3d *, long, long, s_map_variant_placement_properties *, unsigned short)
	todo("implement");
	long __result = _sub_10A6ABD0(thisptr, __formal, object_definition_index, creation_type, map_variant_index, position, forward, up, scenario_datum_index, object_type, variant_properties, object_placement_flags);
	return __result;
}

_extern void _sub_10A6B220(s_map_variant *, void *, long, bool);
void c_map_variant__register_scenario_object_hook(s_map_variant *thisptr, void *__formal, long object_index, bool edited) // 0x10A6B220
{
	// `anonymous-namespace'::c_map_variant__register_scenario_object_hook
	// bool edited;
	// void (*const c_map_variant__register_scenario_object)(s_map_variant *, long, bool);
	// long object_type;
	// function call : void (*const)(s_map_variant *, long, bool)
	todo("implement");
	_sub_10A6B220(thisptr, __formal, object_index, edited);
}

_extern bool _sub_10A6B810(s_map_variant *, void *, long);
bool c_map_variant__update_scenario_object_properties_hook(s_map_variant *thisptr, void *__formal, long object_index) // 0x10A6B810
{
	// `anonymous-namespace'::c_map_variant__update_scenario_object_properties_hook
	// long object_index;
	// bool (*const c_map_variant__update_scenario_object_properties)(s_map_variant *, long);
	// long object_type;
	// function call : bool (*const)(s_map_variant *, long)
	todo("implement");
	bool __result = _sub_10A6B810(thisptr, __formal, object_index);
	return __result;
}

_extern long _sub_10A6ADE0(s_map_variant *, void *, long, long);
long c_map_variant__get_scenario_placement_map_variant_index_hook(s_map_variant *thisptr, void *__formal, long object_type, long scenario_datum_index) // 0x10A6ADE0
{
	// `anonymous-namespace'::c_map_variant__get_scenario_placement_map_variant_index_hook
	// long scenario_datum_index;
	todo("implement");
	long __result = _sub_10A6ADE0(thisptr, __formal, object_type, scenario_datum_index);
	return __result;
}

_extern bool _sub_10A6A6B0(long, long, void *, s_tag_block *, char, char, s_object_placement_data *);
bool c_candy_spawner__spawn_object__new_from_scenario_object_hook(long object_type, long scenario_datum_index, void *scenario_object, s_tag_block *palette_block, char create_at_rest, char flags, s_object_placement_data *placement_data) // 0x10A6A6B0
{
	// `anonymous-namespace'::c_candy_spawner__spawn_object__new_from_scenario_object_hook
	// s_object_placement_data *placement_data;
	// bool (*const object_placement_data_new_from_scenario_object)(long, long, void *, s_tag_block *, char, char, s_object_placement_data *);
	// function call : bool (*const)(long, long, void *, s_tag_block *, char, char, s_object_placement_data *)
	todo("implement");
	bool __result = _sub_10A6A6B0(object_type, scenario_datum_index, scenario_object, palette_block, create_at_rest, flags, placement_data);
	return __result;
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_enum<enum e_game_engine_symmetric_placement,char>::operator==(e_game_engine_symmetric_placement const &) const;
template bool c_enum<enum e_multiplayer_object_boundary_shape,char>::operator==(char const &) const;
template bool c_enum<enum e_multiplayer_object_type,char>::operator<=(e_multiplayer_object_type const &) const;
template bool c_enum<enum e_multiplayer_object_type,char>::operator>=(e_multiplayer_object_type const &) const;
template bool c_flags<enum e_multiplayer_object_flags,unsigned char>::test(e_multiplayer_object_flags) const;
template bool c_tag_block<s_model_object_data>::try_get_element(__int32, s_model_object_data **) const;
template bool c_tag_block<s_scenario_object_palette_entry>::try_get_element(__int32, s_scenario_object_palette_entry **) const;
template bool c_tag_block<s_weapon_magazine_definition>::try_get_element(__int32, s_weapon_magazine_definition **) const;
template c_enum<enum e_multiplayer_object_type,char>::operator char() const;
template c_flags<enum e_game_engine_flags,unsigned short>::operator bool() const;
template c_flags<enum e_game_engine_type,unsigned short>::operator bool() const;
template c_flags<enum e_game_engine_type,unsigned short>::operator unsigned short() const;
template c_flags<enum e_tag_data_flags,long>::c_flags();
template c_flags<enum e_variant_object_placement_flags,unsigned short> & c_flags<enum e_variant_object_placement_flags,unsigned short>::operator|=(__int32 const);
template c_flags<enum e_variant_placement_flags,unsigned char> & c_flags<enum e_variant_placement_flags,unsigned char>::operator=(unsigned char const &);
template s_light_datum * c_data_array<s_light_datum>::try_and_get(unsigned long);
template s_model_object_data & c_tag_block<s_model_object_data>::operator[](__int32);
template s_model_object_data * c_tag_block<s_model_object_data>::get_element(__int32) const;
template s_multiplayer_object_definition & c_tag_block<s_multiplayer_object_definition>::operator[](__int32);
template s_scenario_object_palette_entry & c_tag_block<s_scenario_object_palette_entry>::operator[](__int32);
template s_scenario_object_palette_entry * c_tag_block<s_scenario_object_palette_entry>::get_element(__int32) const;
template s_weapon_magazine_definition & c_tag_block<s_weapon_magazine_definition>::operator[](__int32);
template s_weapon_magazine_definition * c_tag_block<s_weapon_magazine_definition>::get_element(__int32) const;
template void Pointer::Write<float const *>(float const *const) const;
template void c_flags<enum e_variant_placement_flags,unsigned char>::set(e_variant_placement_flags, bool);
