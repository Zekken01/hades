/* ---------- headers */

#include "hades/hades.h"
#include "Forge/SelectionRenderer.hpp"
#include "Forge/ForgeMapModifier.hpp"

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
#include "Blam/camera/camera.hpp"  // hades: added for 0x10A6C960
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
#include "Forge/ForgeSkies.hpp"  // hades: added for 0x10A603E0
#include "Forge/ForgeWeather.hpp"  // hades: added for 0x10A603E0
#include "Forge/ForgeAtmosphere.hpp"  // hades: added for 0x10A603E0
#include "Forge/ForgeCameraFx.hpp"  // hades: added for 0x10A603E0
#include "Forge/ForgeMapBarriers.hpp"  // hades: added for 0x10A603E0
#include "Forge/Reforge.hpp"  // hades: added for 0x10A603E0
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
namespace Forge {} namespace Forge { namespace RotationSnap { void RotateSnapped(real_vector3d const &axis); } }
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
	bool IsValid = false; // 0x0
	bool MonitorLastTick = false; // 0x1
	bool NoclipLastTick = false; // 0x2
	long HeldObjectIndex = -1; // 0x4
	long HeldObjectRootNode = -1; // 0x8
	real_vector3d GrabOffset = {}; // 0xC
};
// static_assert(sizeof(s_monitorState) == 24, "Invalid s_monitorState size");
// Withheld: the type inventory does not describe this type, so its
// padding could not be reconstructed.

struct s_selectionState
{
	public:
	struct ChildInfo
	{
		real_vector3d displacement = {}; // 0x0
		float scale = 0.0f; // 0xC
	};
	// static_assert(sizeof(ChildInfo) == 16, "Invalid ChildInfo size");
	// Withheld: the type inventory does not describe this type, so its
	// padding could not be reconstructed.
	public:
	real_point3d initialPosition = {}; // 0x0
	float initialScale = 0.0f; // 0xC
	std::unordered_map<int,ChildInfo> children; // 0x10
	// hades: every special member implicit, so `selectionState = {}` builds an
	// aggregate temporary and move-assigns it, as the original does.
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

namespace eldorado
{
	// Functions in eldorado.exe, named as in ManagedDonkey.
	static auto const game_engine_object_is_fixed = reinterpret_cast<bool (*)(long)>(0x59A7B0);
	static auto const object_get_origin = reinterpret_cast<void (*)(long, real_point3d *)>(0xB2E5A0);
	static auto const object_get_world_matrix = reinterpret_cast<real_matrix4x3 *(*)(long, real_matrix4x3 *)>(0xB2EC60);
	static auto const object_set_velocities = reinterpret_cast<void(__cdecl *)(long, real_vector3d const *, real_vector3d const *)>(0xB34040);
	static auto const player_mapping_get_input_user = reinterpret_cast<long (*)(long)>(0x589B00);
	static auto const player_mapping_get_player_by_input_user = reinterpret_cast<unsigned long (*)(long)>(0x589C30);
	static auto const player_mapping_get_player_by_input_user_2 = reinterpret_cast<long(__cdecl *)(long)>(0x589C30);
}
#line 385

real_vector3d *vector_from_points3d(real_point3d const *a, real_point3d const *b, real_vector3d *result);  // hades: added for 0x10A6DC20
extern real_point3d *point_from_line3d(real_point3d const *origin, real_vector3d const *vector, float t, real_point3d *result);  // hades: added for 0x10A6DC20

namespace Forge { namespace Selection { extern void Update(); } }  // hades: added for 0x10A6C2E0
namespace Forge { namespace RotationSnap { extern void Update(unsigned __int32 playerIndex, unsigned __int32 objectIndex); } }  // hades: added for 0x10A6C2E0

void matrix4x3_translation(real_matrix4x3 *matrix, real_point3d const *translation);  // hades: added for 0x10A670C0

namespace Forge { extern void DeleteObject(long playerIndex, long objectIndex); }  // hades: added for 0x10A64E10

extern bool (*const game_engine_is_sandbox)();  // hades: added for 0x10A6B0A0

namespace Web { namespace Ui { namespace WebForge { extern void OnItemSpawned(unsigned int objectIndex); } } }  // hades: added for 0x10A6F800

float distance3d(real_point3d const *a, real_point3d const *b);  // hades: added for 0x10A647D0
real_vector3d operator-(real_point3d const &a, real_point3d const &b);  // hades: added for 0x10A647D0

extern void *(*const tag_get)(unsigned long, long);  // hades: added for 0x10A6C710
extern float (*const game_tick_length)();  // hades: added for 0x10A6C960
namespace Patches { namespace Camera { e_camera_mode GetForcedCameraMode(); } }  // hades: added for 0x10A6C960

namespace Forge { namespace Selection { bool Clone(); } }  // hades: added for 0x10A65280

#include "Web/Ui/ScreenLayer.hpp"  // hades: added for 0x10A6BA90
namespace Web { namespace Ui { namespace WebForge { extern std::string BuildForgePaletteJSON(); } } }  // hades: added for 0x10A6BA90

#include "Blam/interface/gui/gui_screen_manager.hpp"  // hades: added for 0x10A6C650

extern s_map_variant *(*const game_engine_get_runtime_map_variant)();  // hades: added for 0x10A6F150

namespace Forge { namespace PrematchCamera { extern void PlaceCameraObject(short team); } }  // hades: added for 0x10A66840


namespace Forge { namespace Selection { extern ::Forge::ObjectSet &GetSelection(); } }  // hades: added for 0x10A6BA00

extern bool (*const game_is_multiplayer)();  // hades: added for 0x10A6F5D0

namespace Web { namespace Ui { namespace WebForge { extern void ShowObjectCreation(); } } }  // hades: added for 0x10A6F530

s_object_data *object_get(unsigned long object_index);  // hades: added for 0X10A6F470
s_forge_globals_definition *forge_globals_get_definition();  // hades: added for 0X10A6F470

void *tag_try_and_get_and_verify_group(unsigned long group_tag, long tag_index);  // hades: added for 0X10A6ABD0

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
float __fastcall c_map_variant__get_budget_fraction_hook(s_map_variant *thisptr, void *__formal, float *budget_spent, float *budget_max);
bool __fastcall c_sandbox_engine__initialize_for_new_map_hook(c_sandbox_engine *thisptr, void *__formal);
void __fastcall c_sandbox_engine__dispose_from_old_map_hook(c_sandbox_engine *thisptr, void *__formal);
void __fastcall c_sandbox_engine__update_hook(c_sandbox_engine *thisptr, void *__formal);
void __fastcall c_sandbox_engine__rotate_object_hook(c_sandbox_engine *thisptr, void *__formal, long playerIndex, long objectIndex, float yaw, float pitch, float roll);
void __fastcall c_sandbox_engine__handle_deleted_object_hook(c_sandbox_engine *thisptr, void *__formal, long object_index);
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
void __fastcall c_map_variant__apply_multiplayer_properties_hook(s_map_variant *thisptr, void *__formal, s_map_variant_placement_properties *properties, long object_index);
void c_map_variant__setup_object_properties_hook(s_variant_datum *placement);
void __fastcall c_map_variant__initialize_from_scenario_hook(s_map_variant *thisptr, void *unused);
void __fastcall c_map_variant__recalculate_quota_hook(s_map_variant *thisptr, void *unused, __int32 budgetIndex, char arg_4);
void __fastcall c_map_variant__rebuild_quotas_from_hook(s_map_variant *thisptr, void *__formal, s_map_variant *other);
void c_map_variant__create_object_jump_hook();
long __fastcall place_object_hook(s_map_variant *thisptr, void *__formal, long tag_index, long creation_type, long map_variant_index, real_point3d const *position, real_vector3d const *forward, real_vector3d const *up, long scenario_object_index, e_object_type object_type, s_map_variant_placement_properties *properties, unsigned short flags);
bool can_place_object_at_hook(long tag_index, real_point3d *position, long player_unit_index);
float __fastcall light_intensity_function_evaluate(c_function_definition *thisptr, long light_index, float input, float range);
void __fastcall light_color_function_evaluate(c_function_definition *thisptr, long light_index, float input, float range, real_rgb_color *color);
void light_intensity_function_hook();
void light_color_function_hook();
void add_simple_light_callback_hook(long light_index, long user_index, float intensity, c_lights_view *lights_view);
void __fastcall c_map_variant__quantize_hook(s_map_variant *thisptr, void *unused);
void game_engine_update_hook();
bool game_engine_game_object_has_fallen_too_far_hook(long object_index);
bool collision_test_object_hook(long object_index, s_object_header *object_header, s_object_data *object, unsigned long test_flags, long object_type_mask, long ignore_object_index_1, long ignore_object_index_2, long ignore_object_index_3);
static void multiplayer_object_submit_boundary_hook(s_multiplayer_object_boundary_geometry_data *boundary, real_argb_color *color, long object_index);
void __fastcall c_multiplayer_candy_monitor_manager__monitor_object_hook(c_multiplayer_candy_monitor_manager *thisptr, void *__formal, long map_variant_index, long object_index);
void shield_impact_bloom_intensity_hook(long id, long count, float *data);
void game_sound_update_acoustics_hook(float dt);
void object_placement_create_active_zone_set_skies_hook(long scenario_index, unsigned long bsp_mask);
bool IgnoreRigidBodyNode(unsigned __int32 objectIndex, __int32 nodeIndex);
void __fastcall rigid_body_hack_hook(c_runtime_node_to_physics_model_rigid_body_index_mapping *thisptr, void *__formal, long object_index, bool force);
long havok_cull_objects_filter_rigid_body_hook(hkpEntity *entity);
void __fastcall c_havok_component__connect_to_havok_world_hook(c_havok_component *thisptr, void *unused);
void game_engine_garbage_collect_for_round_switch_object_delete_hook(long object_index);
s_multiplayer_object_properties *game_engine_find_available_spawn_location_objects_filter_hook(long object_index);
bool __fastcall c_havok_contact_point__is_climbable_surface_hook(c_havok_contact_point *contact_point);
void map_variant_register_object_hook(long object_index, long map_variant_index, char registration_type);
void __fastcall c_sandbox_engine__update_local_player_hook(c_sandbox_engine *thisptr, void *__formal, long player_index);
long __fastcall c_map_variant__create_object_hook(s_map_variant *thisptr, void *__formal, long object_definition_index, long creation_type, long map_variant_index, real_point3d *position, real_vector3d *forward, real_vector3d *up, long scenario_datum_index, long object_type, s_map_variant_placement_properties *variant_properties, unsigned short object_placement_flags);
void __fastcall c_map_variant__register_scenario_object_hook(s_map_variant *thisptr, void *__formal, long object_index, bool edited);
bool __fastcall c_map_variant__update_scenario_object_properties_hook(s_map_variant *thisptr, void *__formal, long object_index);
long __fastcall c_map_variant__get_scenario_placement_map_variant_index_hook(s_map_variant *thisptr, void *__formal, long object_type, long scenario_datum_index);
bool c_candy_spawner__spawn_object__new_from_scenario_object_hook(long object_type, long scenario_datum_index, void *scenario_object, s_tag_block *palette_block, char create_at_rest, char flags, s_object_placement_data *placement_data);

/* ---------- globals */

namespace Forge { namespace Volumes { extern void Update(); } }  // hades: added for 0x10A6E3C0
extern s_object_data *(*const object_try_and_get_and_verify_type)(unsigned long, c_enum<enum e_object_type,long>);  // hades: added for 0x10A673E0
namespace Web { namespace Ui { namespace WebConsole { extern void Hide(); } } }  // hades: added for 0x10A66460
namespace Web { namespace Ui { namespace WebForge { extern void ShowObjectProperties(unsigned __int32 objectIndex); } } }  // hades: added for 0x10A66460
namespace Forge { namespace Selection { extern void Clear(); } }  // hades: added for 0x10A6B960
extern s_multiplayer_object_properties *(*const object_get_multiplayer)(unsigned long);  // hades: added for 0X10A6D5B0
extern long (*const havok_entity_get_havok_component_index)(hkpEntity const *);  // hades: added for 0X10A6E6D0
namespace Forge { namespace RotationSnap { extern void RotateToScripted(unsigned __int32 objectIndex, real_quaternion const &rotation); } }  // hades: added for 0x10A66650
extern s_multiplayer_object_properties *(*const object_get_multiplayer)(unsigned long);  // hades: added for 0X10A6A8A0

/* ---------- private variables */

namespace hades_file_local
{
	namespace hades_file_local_Forge { extern real_vector3d global_zero3d; } using namespace hades_file_local_Forge; // 0x111AFB58
	extern float const HELDOBJECT_DISTANCE_MIN; // 0x111AFB88
	extern float const HELDOBJECT_DISTANCE_CHANGE_MULTIPLIER; // 0x111AFB8C
	extern float const MONITOR_MOVEMENT_SPEEDS[7]; // 0x111AFB90
	extern wchar_t const *MONITOR_MOVEMENT_SPEED_NAMES[7]; // 0x11354370
	extern s_monitorState monitorState; // 0x1135438C
	extern std::vector<void (__cdecl*)(unsigned int)> s_ItemSpawnedCallbacks; // 0x124584C0
	s_selectionState selectionState; // 0x124584D0  // hades: defined, so its dynamic initializer emits the implicit constructor
}
using namespace hades_file_local;
/* ---------- public code */

// mangled_x86(MANGLED_DEFAULT, "??0c_function_definition@@QAE@XZ"); no body to assert in

// mangled_x86(MANGLED_DEFAULT, "??0s_tag_data@@QAE@XZ"); no body to assert in

namespace Patches
{
	namespace Forge
	{

		void ApplyAll() // 0x10A60560
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAll@Forge@Patches@@YAXXZ");
			// procedure flags: nofpo

			Hook(0x1337F1, game_engine_update_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Pointer(0x165AB54).Write<unsigned int>(reinterpret_cast<unsigned int>(c_sandbox_engine__update_hook));
			Pointer(0x165AB94).Write<unsigned int>(reinterpret_cast<unsigned int>(c_sandbox_engine__handle_deleted_object_hook));
			Pointer(0x165AB04).Write<unsigned int>(reinterpret_cast<unsigned int>(c_sandbox_engine__initialize_for_new_map_hook));
			Pointer(0x165AB08).Write<unsigned int>(reinterpret_cast<unsigned int>(c_sandbox_engine__dispose_from_old_map_hook));
			Hook(0x19D482, c_sandbox_engine__update_local_player_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x19FA69, c_sandbox_engine__rotate_object_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x7350A, game_engine_sandox_apply_grab_object_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x19B14D, game_engine_sandox_apply_grab_object_hook2, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x7356F, game_engine_sandbox_stop_editing_object_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x734FC, game_engine_sandbox_delete_object_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x73527, game_engine_sandbox_update_variant_object_properties_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x734EE, game_engine_sandbox_place_object_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x7AF758, character_physics_update_input_datum_initialize_flying_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x19CAFC, update_edited_object_transform_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x19F4CA, shoot_probe_for_player_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0xAD4DD, c_map_variant__apply_multiplayer_properties_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x180E66, c_map_variant__apply_multiplayer_properties_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x181326, c_map_variant__apply_multiplayer_properties_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x1824EA, c_map_variant__apply_multiplayer_properties_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x185BBD, c_map_variant__apply_multiplayer_properties_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x186680, c_map_variant__setup_object_properties_hook).Apply();
			Hook(0x6E25A0, object_properties_user_interface_allocate_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x6E26C1, object_properties_user_interface_allocate_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x6E2729, object_creation_user_interface_allocate_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Patch(0x6EAADD, { 0xEB }).Apply();
			Patch(0x6EAA37, { 0xEB }).Apply();
			Pointer(0x59FA99).Write<float const *>(&HELDOBJECT_DISTANCE_MIN);
			Pointer(0x59FA7E).Write<float const *>(&HELDOBJECT_DISTANCE_CHANGE_MULTIPLIER);
			Patch(0x19FACC, { 0x90, 0x90 }).Apply();
			Hook(0x19E8AD, shoot_probe_for_player_test_vector_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Patch::NopFill(Pointer::Base(0x6E4796), 102);
			Hook(0x151506, c_map_variant__initialize_from_scenario_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x185DC1, c_map_variant__recalculate_quota_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x182110, c_map_variant__create_object_jump_hook).Apply();
			Hook(0x181F30, c_map_variant__create_object_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x186071, c_map_variant__create_object_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x19AEE6, place_object_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x19AEBA, can_place_object_at_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Pointer(0xA669E5).Write<unsigned int>(reinterpret_cast<unsigned int>(add_simple_light_callback_hook));
			Hook(0x79E1A9, light_intensity_function_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x79E186, light_color_function_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x181CC0, c_map_variant__rebuild_quotas_from_hook).Apply();
			Patch(0x18676E, { 0x90, 0x90 }).Apply();
			Hook(0x184CF0, c_map_variant__quantize_hook).Apply();
			Hook(0x58028E, game_engine_game_object_has_fallen_too_far_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x5D4CD5, game_engine_game_object_has_fallen_too_far_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x2D8F48, collision_test_object_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x19F0B8, multiplayer_object_submit_boundary_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x653D77, shield_impact_bloom_intensity_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Patch(0x317265, { 0xBA, 0x07, 0x00, 0x00, 0x00 }).Apply();
			Patch(0x7D8A59, { 0xEB }).Apply();
			Hook(0x1D9BBE, game_sound_update_acoustics_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x7591E4, object_placement_create_active_zone_set_skies_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x1E41CA, rigid_body_hack_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x757490, rigid_body_hack_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x1C4E3A, havok_cull_objects_filter_rigid_body_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x731E5F, c_havok_component__connect_to_havok_world_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x14F139, game_engine_garbage_collect_for_round_switch_object_delete_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x1A38A8, game_engine_find_available_spawn_location_objects_filter_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x3238EA, c_havok_contact_point__is_climbable_surface_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x183250, c_map_variant__get_budget_fraction_hook).Apply();
			Hook(0xAD4EA, map_variant_register_object_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x190DB1, c_candy_spawner__spawn_object__new_from_scenario_object_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x19004E, c_multiplayer_candy_monitor_manager__monitor_object_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Patch(0x181C90, { 0xB0, 0x01, 0xC3 }).Apply();
			Patch::NopFill(Pointer::Base(0x185655), 6);
			Patch::NopFill(Pointer::Base(0x1858E2), 6);
			Patch::NopFill(Pointer::Base(0x186C75), 2);
			Hook(0x184829, c_map_variant__register_scenario_object_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x184811, c_map_variant__update_scenario_object_properties_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x1834E0, c_map_variant__get_scenario_placement_map_variant_index_hook).Apply();
			Pointer(0x58FFFD).Write<int>(0x280F);
			Pointer(0x590638).Write<int>(0x280F);
			Pointer(0x590C87).Write<int>(0x280F);
			Pointer(0x54ECA1).Write<int>(0x280F);
			Pointer(0x59E8A4).Write<int>(0x531D);
			::Forge::SelectionRenderer::ApplyPatches();
			CForgeDeviceManager &deviceManager = CForgeDeviceManager::Instance();
			::Patches::Game::RegisterGameSystem(&deviceManager);
			CForgeUndoManager::Instance().completedEvent.Subscribe(::Forge::CForgeMapModifier::OnUndoRedoCompleted);
		}

		void ApplyAfterTagsLoaded() // 0x10A603E0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAfterTagsLoaded@Forge@Patches@@YAXXZ");
			// procedure flags: nofpo

			monitorState = {};
			selectionState = {};
			::Forge::Reforge::InitializeForNewMap();
			::Forge::CForgeMapModifier::InitializeForNewMap();
			::Forge::CForgeSkies::InitializeForNewMap();
			::Forge::CForgeWeather::InitializeForNewMap();
			::Forge::CForgeAtmosphere::InitializeForNewMap();
			::Forge::CForgeCameraFx::InitializeForNewMap();
			::Forge::CForgeMapBarriers::InitializeForNewMap();
		}

		void Tick() // 0x10A674B0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Tick@Forge@Patches@@YAXXZ");
			// procedure flags: nofpo
		}

		void OnItemSpawned(void (*callback)(unsigned __int32)) // 0x10A66A20
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OnItemSpawned@Forge@Patches@@YAXP6AXI@Z@Z");
			// void (*callback)(unsigned __int32);

			s_ItemSpawnedCallbacks.push_back(callback);
		}
	}
}

/* ---------- private code */

void AddMapVariantUndoPoint(char const *summary) // 0x10A60240
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?AddMapVariantUndoPoint@@YAXPBD@Z");
	// `anonymous-namespace'::AddMapVariantUndoPoint
	// char const *summary;
	// s_map_variant *mapVariant;
	// function call : bool (*const)()
	// function call : s_map_variant *(*const)()

	if (!((bool (__cdecl *)())0x5319C0)())
		return;
	if (!CForgeUndoManager::Instance().IsRecording())
		return;

	s_map_variant *mapVariant = game_engine_get_runtime_map_variant();
	CForgeUndoManager::Instance().AddUndo(summary, std::make_shared<CForgeUndoMapVariant>(summary, *mapVariant));
}

void ApplyGrabOffset(long player_index, long object_index) // 0x10A647D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyGrabOffset@@YAXJJ@Z");
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

	monitorState.GrabOffset = global_zero3d;
	s_player_datum *player = player_get(player_index);
	s_object_data *unit = object_try_and_get_and_verify_type(player->unit_index, 0x2003);
	if (!unit)
		return;
	s_object_data *object = object_get(object_index);
	real_point3d unitPos;
	eldorado::object_get_origin(player->unit_index, &unitPos);
	s_sandbox_globals *sandboxGlobals = get_sandbox_globals();
	real_point3d crosshairPoint = sandboxGlobals->player_cursor_position[player_index & 0xF];
	sandboxGlobals->player_cursor_distance[player_index & 0xF] = distance3d(&unitPos, &crosshairPoint);
	monitorState.GrabOffset = object->bounding_sphere_center - crosshairPoint;
}

void GrabObject(long player_index, long map_variant_index) // 0x10A656C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GrabObject@@YAXJJ@Z");
	// `anonymous-namespace'::GrabObject
	// long map_variant_index;
	// long object_index;
	// Forge::ObjectSet &selection;
	// void (*const c_map_variant__remove_object)(s_map_variant *, long, long);
	// void (*const game_engine_sandox_apply_grab_object)(long, long);
	// void (*const change_object_physics_mode)(long, long);
	// s_map_variant *map_variant;
		// long i;
			// s_variant_datum const &placement;
			// long selection_object_index;
	// function call : s_map_variant *(*const)()
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : unsigned long (*const)(long)
	// function call : void (*const)(long, long)
	// function call : void (*const)(s_map_variant *, long, long)
	// function call : void (*const)(long, long, long)
	// function call : void (*const)(long, long)
	// function call : bool (*const)(long)

	void (*const game_engine_sandox_apply_grab_object)(long, long) = reinterpret_cast<void (*)(long, long)>(0x59B080);
	void (__thiscall *const c_map_variant__remove_object)(s_map_variant *, long, long) = reinterpret_cast<void (__thiscall *)(s_map_variant *, long, long)>(0x585C00);
	void (*const change_object_physics_mode)(long, long) = reinterpret_cast<void (*)(long, long)>(0x59A620);
	s_map_variant *map_variant = game_engine_get_runtime_map_variant();
	long object_index = map_variant->objects[map_variant_index].object_index;
	if (!object_try_and_get_and_verify_type(object_index, -1))
		return;
	AddMapVariantUndoPoint("Object Grabbed");
	if (player_index == eldorado::player_mapping_get_player_by_input_user(0))
		monitorState.HeldObjectIndex = object_index;
	game_engine_sandox_apply_grab_object(player_index, map_variant_index);
	::Forge::ObjectSet &selection = ::Forge::Selection::GetSelection();
	if (selection.Contains(object_index))
	{
		for (long i = 0; i < 640; i++)
		{
			s_variant_datum const &placement = map_variant->objects[i];
			if (!placement.flags.test((e_variant_object_placement_flags)0) || placement.object_index == object_index)
				continue;
			long selection_object_index = placement.object_index;
			if (selection.Contains(selection_object_index))
			{
				c_map_variant__remove_object(map_variant, i, 2);
				((void (*const)(long, long, long))0xB2A250)(object_index, selection_object_index, 0);
				change_object_physics_mode(selection_object_index, 1);
			}
		}
	}
	if (eldorado::game_engine_object_is_fixed(object_index))
		ApplyGrabOffset(player_index, object_index);
}

void GrabSelection(long player_index) // 0x10A65950
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GrabSelection@@YAXJ@Z");
	// `anonymous-namespace'::GrabSelection
	// long player_index;
	// Forge::ObjectSet const &selection;
	// void (*const game_engine_sandox_apply_grab_object)(long, long);
	// s_map_variant const *map_variant;
		// __int32 i;
	// function call : s_map_variant *(*const)()

	void (__cdecl *const game_engine_sandox_apply_grab_object)(long, long) = (void(__cdecl *const)(long, long))0x59b080;
	s_map_variant const *map_variant = game_engine_get_runtime_map_variant();
	::Forge::ObjectSet const &selection = ::Forge::Selection::GetSelection();

	for (__int32 i = 0; i < 640; i++)
	{
		if (selection.Contains(map_variant->objects[i].object_index))
		{
			GrabObject(player_index, i);
			return;
		}
	}
}

void SubmitWorldBoundsForRendering() // 0x10A670C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SubmitWorldBoundsForRendering@@YAXXZ");
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

	if (!Utils::Singleton<Modules::ModuleForge>::Instance().VarShowWorldBoundsClient->ValueInt)
		return;
	s_forge_globals_definition *forge_globals = forge_globals_get_definition();
	if (!forge_globals)
		return;
	long shader_tag_index = forge_globals->default_boundary_method.index;
	long player_index = ((long (*)(long))0x589C30)(0);
	if (!((bool (*)(long, long, long))0x59A6F0)(player_index, 0, 0))
		return;
	s_map_variant *map_variant = game_engine_get_runtime_map_variant();
	float width = map_variant->world_bounds.x1 - map_variant->world_bounds.x0;
	float depth = map_variant->world_bounds.y1 - map_variant->world_bounds.y0;
	float height = map_variant->world_bounds.z1 - map_variant->world_bounds.z0;
	real_point3d center;
	center.x = (map_variant->world_bounds.x0 + map_variant->world_bounds.x1) * 0.5f;
	center.y = (map_variant->world_bounds.y0 + map_variant->world_bounds.y1) * 0.5f;
	center.z = (map_variant->world_bounds.z0 + map_variant->world_bounds.z1) * 0.5f;
	real_argb_color color = { 1.0f, 1.0f, 1.0f, 1.0f };
	real_matrix4x3 matrix;
	matrix4x3_translation(&matrix, &center);
	((void (*)(long, real_argb_color const *, real_matrix4x3 const *, float, float, float, float))0xA74B80)(shader_tag_index, &color, &matrix, width, depth, height * 0.5f, height * 0.5f);
}

void TryUndo() // 0x10A676D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?TryUndo@@YAXXZ");
	// `anonymous-namespace'::TryUndo
	// procedure flags: nofpo
	// static ...; // 0x10A67860
	// static ...; // 0x10A67854
	// static ...; // 0x10A6784C
	// CForgeUndoManager &undoManager;
	// std::wstring message;

	CForgeUndoManager &undoManager = Utils::Singleton<CForgeUndoManager>::Instance();
	if (!undoManager.CanUndo())
	{
		::Forge::PrintKillFeedText(0, L"Nothing to undo!", 0);
		return;
	}

	std::wstring message = Utils::String::WidenString("Undo " + undoManager.GetNextUndoSummary());
	::Forge::PrintKillFeedText(0, message.c_str(), 0);
	undoManager.RequestUndo();
}

void TryRedo() // 0x10A674D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?TryRedo@@YAXXZ");
	// `anonymous-namespace'::TryRedo
	// procedure flags: nofpo
	// static ...; // 0x10A67660
	// static ...; // 0x10A67654
	// static ...; // 0x10A6764C
	// CForgeUndoManager &undoManager;
	// std::wstring message;

	CForgeUndoManager &undoManager = Utils::Singleton<CForgeUndoManager>::Instance();
	if (!undoManager.CanRedo())
	{
		::Forge::PrintKillFeedText(0, L"Nothing to redo!", 0);
		return;
	}

	std::wstring message = Utils::String::WidenString("Redo " + undoManager.GetNextRedoSummary());
	::Forge::PrintKillFeedText(0, message.c_str(), 0);
	undoManager.RequestRedo();
}

void CanvasMap() // 0x10A64E10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CanvasMap@@YAXXZ");
	// `anonymous-namespace'::CanvasMap
	// procedure flags: nofpo
	// void (*const c_map_variant_placement__ctor)(s_variant_datum *);
	// long player_index;
	// s_map_variant *map_variant;
		// long i;
			// s_variant_datum &placement;
			// s_variant_quota &budget;
	// function call : s_map_variant *(*const)()
	// function call : unsigned long (*const)(long)
	// function call : void (*const)(s_variant_datum *)

	void (__thiscall *const c_map_variant_placement__ctor)(s_variant_datum *) = reinterpret_cast<void (__thiscall *)(s_variant_datum *)>(0x4AC1D0);
	AddMapVariantUndoPoint("Map Canvas");
	s_map_variant *map_variant = game_engine_get_runtime_map_variant();
	if (!map_variant)
		return;
	long player_index = ((long (*)(long))0x589C30)(0);
	for (long i = 0; i < 640; i++)
	{
		s_variant_datum &placement = map_variant->objects[i];
		if (!placement.flags.test((e_variant_object_placement_flags)0))
			continue;
		s_variant_quota &budget = map_variant->object_quotas[placement.quota_index];
		if (budget.definition_index == -1 || budget.cost < 0.0f)
			continue;
		if (placement.object_index != -1)
		{
			::Forge::DeleteObject(player_index, i);
		}
		else
		{
			if (i < map_variant->scenario_object_count)
				placement.flags |= 0x20;
			else
			{
				memset(&placement, 0, sizeof(s_variant_datum));
				c_map_variant_placement__ctor(&placement);
			}
			if (!--budget.placed_on_map)
			{
				budget.definition_index = -1;
				budget.cost = -1.0f;
				budget.placed_on_map = 0;
				budget.maximum_allowed = 0xFF;
				budget.minimum_count = 0xFF;
				budget.maximum_count = 0xFF;
			}
		}
	}
}

void ResetRuntime() // 0x10A66D30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ResetRuntime@@YAXXZ");
	// `anonymous-namespace'::ResetRuntime
	// procedure flags: nofpo
	// s_game_engine_globals *game_engine_globals;
		// long i;
			// c_candy_spawner *spawner;
	// function call : void (*const)(long)
	// function call : void (*const)(void *, bool)

	static void (*const object_delete)(long) = reinterpret_cast<void (*)(long)>(0xB2CD10);
	static void (__thiscall *const spawn_object)(void *, bool) = reinterpret_cast<void (__thiscall *)(void *, bool)>(0x590CE0);
	s_game_engine_globals *game_engine_globals = tls_getd().game_engine_globals;
	for (long i = 0; i < 512; i++)
	{
		c_candy_spawner *spawner = &game_engine_globals->candy_monitor_manager.m_candy_spawners[i];
		if (spawner->m_map_variant_index == -1 || spawner->m_respawn_timer == 0x7FFF)
			continue;
		if (spawner->m_spawned_object_index != -1)
		{
			object_delete(spawner->m_spawned_object_index);
			spawner->m_spawned_object_index = -1;
		}
		spawn_object(spawner, true);
	}
}

void HandlePrefabCommands() // 0x10A66510
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?HandlePrefabCommands@@YAXXZ");
	// `anonymous-namespace'::HandlePrefabCommands
	// procedure flags: nofpo
	// Modules::ModulePlayer &modulePlayer;
	// Modules::ModuleForge &moduleForge;
	// function call : unsigned long (*const)(long)

	Modules::ModuleForge &moduleForge = Modules::ModuleForge::Instance();
	Modules::ModulePlayer &modulePlayer = Modules::ModulePlayer::Instance();
	if (moduleForge.CommandState.Prefabs.LoadPrefab)
	{
		AddMapVariantUndoPoint("Load Prefab");
		if (::Forge::Prefabs::Load(moduleForge.CommandState.Prefabs.Path))
			GrabSelection(((unsigned long (__cdecl *)(long))0x589C30)(0));
		else
			::Forge::PrintKillFeedText(0, L"ERROR: Failed to load prefab.", 0);
		moduleForge.CommandState.Prefabs.LoadPrefab = false;
	}
	if (moduleForge.CommandState.Prefabs.SavePrefab)
	{
		if (!::Forge::Prefabs::Save(modulePlayer.VarPlayerName->ValueString, moduleForge.CommandState.Prefabs.Name, moduleForge.CommandState.Prefabs.Path))
			::Forge::PrintKillFeedText(0, L"ERROR: Failed to save prefab.", 0);
		moduleForge.CommandState.Prefabs.SavePrefab = false;
	}
}

void SpawnItem(long tag_index) // 0x10A66E30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SpawnItem@@YAXJ@Z");
	// `anonymous-namespace'::SpawnItem
	// static ...; // 0x10A6702F
	// static ...; // 0x10A67024
	// static ...; // 0x10A6700C
	// static ...; // 0x10A67004
	// long tag_index;
	// long player_index;
	// s_simulation_queue_sandbox_event_data event_data;
		// wchar_t buff[256];
	// function call : unsigned long (*const)(long)
	// function call : bool (*const)(long, long *, long *)
	// function call : void (*const)(s_simulation_queue_sandbox_event_data *)

	if (tag_index == -1)
		return;
	long player_index = ((long (*)(long))0x589C30)(0);
	if (player_index == -1 || !((bool (*)(long, long, long))0x59A6F0)(player_index, 0, 0))
		return;
	if (!tag_try_and_get_and_verify_group('obje', tag_index))
	{
		wchar_t buff[256];
		swprintf_s(buff, L"Tag not loaded or not a valid forge object [0x%04x]", tag_index);
		::Forge::PrintKillFeedText(0, buff, 0);
		return;
	}
	struct
	{
		long type;
		long object_definition_index;
		long map_variant_index;
		long player_index;
		float object_throw_force;
		unsigned char quota_min;
		unsigned char quota_max;
		real_point3d position;
		long game_engine_type;
		struct
		{
			c_flags<enum e_game_engine_type,unsigned short> game_engine_flags;
			c_flags<enum e_variant_placement_flags,unsigned char> placement_flags;
			char team_affiliation;
			unsigned char shared_storage;
			unsigned char respawn_time;
			char multiplayer_object_type;
			c_enum<enum e_multiplayer_object_boundary_shape,char> boundry_shape;
			float boundry_width;
			float boundry_length;
			float boundry_top;
			float boundry_bottom;
		} object_properties;
	} event_data = {};
	event_data.type = s_simulation_queue_sandbox_event_data::_event_type_place_object;
	event_data.player_index = player_index;
	event_data.object_definition_index = tag_index;
	event_data.position = get_sandbox_globals()->player_cursor_position[player_index & 0xF];
	((void (*)(void *))0x4735D0)(&event_data);
}

void DoClone(long player_index, long cursor_object_index) // 0x10A65280
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?DoClone@@YAXJJ@Z");
	// `anonymous-namespace'::DoClone
	// long cursor_object_index;
		// float cloneDepth;
		// real_vector3d const &intersectNormal;
		// Modules::ModuleForge &forgeModule;
		// float cloneMultiplier;
		// long objectIndexToClone;
			// __int32 i;

	AddMapVariantUndoPoint("Clone");
	if (cursor_object_index != -1)
	{
		Modules::ModuleForge &forgeModule = Modules::ModuleForge::Instance();
		float cloneDepth = forgeModule.VarCloneDepth->ValueFloat;
		float cloneMultiplier = forgeModule.VarCloneMultiplier->ValueInt;
		real_vector3d const &intersectNormal = get_sandbox_globals()->player_cursor_normal[player_index & 0xF];
		long objectIndexToClone = cursor_object_index;
		for (__int32 i = 0; i < cloneMultiplier; i++)
		{
			objectIndexToClone = ::Forge::CloneObject(player_index, objectIndexToClone, cloneDepth, intersectNormal);
			if (objectIndexToClone == -1)
				break;
		}
	}
	else
	{
		if (::Forge::Selection::GetSelection().Any() && ::Forge::Selection::Clone())
			GrabSelection(player_index);
	}
}

void HandleRuntimeReset() // 0x10A667D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?HandleRuntimeReset@@YAXXZ");
	// `anonymous-namespace'::HandleRuntimeReset
	// procedure flags: nofpo
	// Modules::ModuleForge &moduleForge;

	auto &moduleForge = Utils::Singleton<Modules::ModuleForge>::Instance();
	if (moduleForge.CommandState.RuntimeReset)
	{
		ResetRuntime();
		moduleForge.CommandState.RuntimeReset = false;
	}
}

void HandleMapCanvas() // 0x10A65A80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?HandleMapCanvas@@YAXXZ");
	// `anonymous-namespace'::HandleMapCanvas
	// procedure flags: nofpo
	// Modules::ModuleForge &moduleForge;

	Modules::ModuleForge *moduleForge = &Utils::Singleton<Modules::ModuleForge>::Instance();
	if (moduleForge->CommandState.MapCanvas)
	{
		ResetRuntime();
		CanvasMap();
		moduleForge->CommandState.MapCanvas = false;
	}
}

void HandleSetPrematchCamera() // 0x10A66840
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?HandleSetPrematchCamera@@YAXXZ");
	// `anonymous-namespace'::HandleSetPrematchCamera
	// procedure flags: nofpo
	// Modules::ModuleForge &moduleForge;

	Modules::ModuleForge *moduleForge = &Utils::Singleton<Modules::ModuleForge>::Instance();

	if (moduleForge->CommandState.SetPrematchCamera)
	{
		::Forge::PrematchCamera::PlaceCameraObject(moduleForge->CommandState.PrematchCameraTeamIndex);
		moduleForge->CommandState.SetPrematchCamera = false;
		moduleForge->CommandState.PrematchCameraTeamIndex = -1;
	}
}

void HandleSpawnItem() // 0x10A668C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?HandleSpawnItem@@YAXXZ");
	// `anonymous-namespace'::HandleSpawnItem
	// procedure flags: nofpo
	// Modules::ModuleForge &moduleForge;
	// long &itemTagIndex;

	Modules::ModuleForge &moduleForge = Modules::ModuleForge::Instance();
	long &itemTagIndex = moduleForge.CommandState.SpawnItem;

	if (itemTagIndex != -1)
	{
		SpawnItem(itemTagIndex);
		itemTagIndex = -1;
	}
}

void HandleOpenMapOptions() // 0x10A66460
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?HandleOpenMapOptions@@YAXXZ");
	// `anonymous-namespace'::HandleOpenMapOptions
	// procedure flags: nofpo
	// Modules::ModuleForge &moduleForge;
	// long mapModifierObjectIndex;
	// function call : void (*const)(long, wchar_t const *, e_chud_message_context)

	Modules::ModuleForge &moduleForge = Utils::Singleton<Modules::ModuleForge>::Instance();

	if (!moduleForge.CommandState.OpenMapOptions)
	{
		return;
	}

	moduleForge.CommandState.OpenMapOptions = false;

	long mapModifierObjectIndex = ::Forge::CForgeMapModifier::GetOrCreateMapModifierObject();

	if (mapModifierObjectIndex == -1)
	{
		((void(__cdecl *const)(long, wchar_t const *, e_chud_message_context))0xa95920)(0, L"Failed to spawn map modifier object. Out of objects?", (e_chud_message_context)0);
	}
	else
	{
		Web::Ui::WebConsole::Hide();
		Web::Ui::WebForge::ShowObjectProperties(mapModifierObjectIndex);
	}
}

void HandleCommands() // 0x10A65A20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?HandleCommands@@YAXXZ");
	// `anonymous-namespace'::HandleCommands
	// procedure flags: nofpo

	HandleMapCanvas();
	HandleRuntimeReset();
	HandleSpawnItem();
	HandleSetPrematchCamera();
	HandlePrefabCommands();
	HandleOpenMapOptions();
}

void HandleRotationReset() // 0x10A66650
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?HandleRotationReset@@YAXXZ");
	// `anonymous-namespace'::HandleRotationReset
	// procedure flags: nofpo
	// static ...; // 0x10A6676A
	// static ...; // 0x10A66764
	// static ...; // 0x10A6674C
	// static ...; // 0x10A66744
	// Blam::Input::ActionState *uiUpAction;
		// long heldObjectIndex;
			// real_quaternion ident;
	// function call : unsigned long (*const)(long)
	// function call : bool (*const)(long, long *, long *)

	Blam::Input::ActionState *uiUpAction = Blam::Input::GetActionState(Blam::Input::eGameActionUiUp);
	if (((uiUpAction->Flags & 1) == 0 && uiUpAction->Ticks == 1)
		|| Blam::Input::GetMouseButtonTicks(Blam::Input::eMouseButtonMiddle, Blam::Input::eInputTypeGame) == 1)
	{
		uiUpAction->Flags |= 1;

		long heldObjectIndex;
		if (((bool(__cdecl *const)(long, long *, long *))0x59a6f0)(eldorado::player_mapping_get_player_by_input_user_2(0), &heldObjectIndex, 0))
		{
			real_quaternion ident;
			ident.i = 0.0f;
			ident.j = 0.0f;
			ident.k = 0.0f;
			ident.w = 1.0f;

			::Forge::RotationSnap::RotateToScripted(heldObjectIndex, ident);
		}
	}
}

void HandleMovementSpeed() // 0x10A66150
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?HandleMovementSpeed@@YAXXZ");
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
		// long currentSpeed;
		// wchar_t buff[256];
	// function call : unsigned long (*const)(long)
	// function call : void (*const)(long, real_vector3d const *, real_vector3d const *)

	static Modules::ModuleForge &moduleForge = Utils::Singleton<Modules::ModuleForge>::Instance();
	s_player_datum *player = player_get(((long (*)(long))0x589C30)(0));
	Blam::Input::ActionState *crouchAction = Blam::Input::GetActionState((Blam::Input::GameAction)0x1D);
	crouchAction->Flags |= 1;
	Blam::Input::ActionState *movementSpeedAction = Blam::Input::GetActionState((Blam::Input::GameAction)8);
	if (!(movementSpeedAction->Flags & 1) && movementSpeedAction->Ticks == 1 || Blam::Input::GetKeyTicks((Blam::Input::KeyCode)0x30, (Blam::Input::InputType)1) == 1)
	{
		movementSpeedAction->Flags |= 1;
		long currentSpeed = moduleForge.VarMonitorSpeed->ValueInt;
		currentSpeed = (currentSpeed + 1) % 7u;
		Modules::CommandMap::Instance().SetVariable(moduleForge.VarMonitorSpeed, std::to_string(currentSpeed), true);
		((void (*)(long, real_vector3d const *, real_vector3d const *))0xB34040)(player->unit_index, &global_zero3d, &global_zero3d);
		wchar_t buff[256];
		swprintf_s(buff, L"Movement Speed: %s", MONITOR_MOVEMENT_SPEED_NAMES[currentSpeed]);
		::Forge::PrintKillFeedText(0, buff, 0);
	}
}

void HandleMonitorNoclip() // 0x10A65FB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?HandleMonitorNoclip@@YAXXZ");
	// `anonymous-namespace'::HandleMonitorNoclip
	// procedure flags: nofpo
	// s_player_datum *player;
	// s_object_data *unit;
	// long player_index;
	// Modules::ModuleForge const &moduleForge;
	// bool noclipping;
		// c_havok_component *havok_component;
	// function call : unsigned long (*const)(long)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void (*const)(long, long)

	Modules::ModuleForge const &moduleForge = Utils::Singleton<Modules::ModuleForge>::Instance();
	long player_index = ((long (*)(long))0x589C30)(0);
	if (player_index == -1)
		return;
	s_player_datum *player = player_get(player_index);
	s_object_data *unit = object_try_and_get_and_verify_type(player->unit_index, 0x2003);
	if (!unit)
		return;
	bool noclipping = moduleForge.VarMonitorNoclip->ValueInt != 0;
	if (noclipping != monitorState.NoclipLastTick)
	{
		if (!noclipping)
			((void (*)(long, long))0x5C7380)(player->unit_index, 0);
		monitorState.NoclipLastTick = noclipping;
	}
	if (noclipping)
	{
		c_havok_component *havok_component = havok_component_get(unit->havok_component_index);
		if (havok_component)
			havok_component->set_rigid_body_collision_filter_info(0, 0x13);
	}
}

void HandleMonitorInput(long playerIndex) // 0x10A65AF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?HandleMonitorInput@@YAXJ@Z");
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
		// Blam::Input::ActionState *cloneAction;
		// Blam::Input::ActionState *uiRightAction;
		// Modules::CommandMap &commandMap;
		// std::string previousValueStr;
		// unsigned long prevValue;
	// function call : bool (*const)(long, long *, long *)
	// function call : long (*const)(e_user_interface_sound, long)

	Modules::ModuleForge &moduleForge = Utils::Singleton<Modules::ModuleForge>::Instance();
	long heldObjectIndex;
	long objectIndexUnderCrosshair;
	if (!((bool (*)(long, long *, long *))0x59A6F0)(playerIndex, &heldObjectIndex, &objectIndexUnderCrosshair))
		return;
	if (heldObjectIndex == -1)
	{
		Blam::Input::ActionState *cloneAction = Blam::Input::GetActionState(Blam::Input::eGameActionUiB);
		if ((cloneAction->Flags & 1) == 0 && cloneAction->Ticks == 1)
		{
			cloneAction->Flags |= 1;
			if (Blam::Network::GetActiveSession()->IsHost())
				DoClone(playerIndex, objectIndexUnderCrosshair);
			else
			{
				::Forge::PrintKillFeedText(0, L"Must be host to clone objects", 0);
				((void (*)(long, long))0xAA5CD0)(0, -1);
			}
		}
		Blam::Input::ActionState *uiRightAction = Blam::Input::GetActionState(Blam::Input::eGameActionUiRight);
		if ((uiRightAction->Flags & 1) == 0 && uiRightAction->Ticks == 50)
		{
			::Forge::Selection::Clear();
			::Forge::PrintKillFeedText(0, L"Selection Cleared", 0);
		}
	}
	if (Blam::Input::GetKeyTicks(Blam::Input::eKeyCodeM, Blam::Input::eInputTypeGame) == 1 || (Blam::Input::GetActionState(Blam::Input::eGameActionUiDown)->Flags & 1) == 0 && Blam::Input::GetActionState(Blam::Input::eGameActionUiDown)->Ticks == 1)
	{
		unsigned long prevValue = moduleForge.VarMagnetsEnabled->ValueInt;
		std::string previousValueStr;
		Modules::CommandMap &commandMap = Utils::Singleton<Modules::CommandMap>::Instance();
		commandMap.SetVariable(moduleForge.VarMagnetsEnabled, std::to_string(prevValue ? 0 : 1), previousValueStr, true);
		if (!prevValue)
			::Forge::PrintKillFeedText(0, L"Magnets Enabled", 0);
		else
			::Forge::PrintKillFeedText(0, L"Magnets Disabled", 0);
	}
	if (Blam::Input::GetKeyTicks(Blam::Input::eKeyCodeCtrl, Blam::Input::eInputTypeGame) > 0 && Blam::Input::GetKeyTicks(Blam::Input::eKeyCodeZ, Blam::Input::eInputTypeGame) == 1)
	{
		if (Blam::Input::GetKeyTicks(Blam::Input::eKeyCodeShift, Blam::Input::eInputTypeGame) > 0)
			TryRedo();
		else
			TryUndo();
	}
	if (Blam::Input::GetKeyTicks(Blam::Input::eKeyCodeCtrl, Blam::Input::eInputTypeGame) > 0 && Blam::Input::GetKeyTicks(Blam::Input::eKeyCodeY, Blam::Input::eInputTypeGame) == 1)
		TryRedo();
	if (Blam::Input::GetActionState(Blam::Input::eGameActionUiLeftTrigger)->Ticks > 0)
	{
		if (Blam::Input::GetActionState(Blam::Input::eGameActionUiLeft)->Ticks == 1)
			TryUndo();
		else if (Blam::Input::GetActionState(Blam::Input::eGameActionUiRight)->Ticks == 1)
			TryRedo();
	}
}

long FindComplexObjectRigidBodyRootNode(long object_index) // 0x10A65410
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?FindComplexObjectRigidBodyRootNode@@YAJJ@Z");
	// `anonymous-namespace'::FindComplexObjectRigidBodyRootNode
	// long object_index;
	// s_object_definition *object_definition;
	// s_object_data *object;
	// s_physics_model_definition *physics_model;
	// s_model_definition *model;
		// long i;
			// s_physics_model_rigid_body const &rigid_body;
	// function call : void *(*const)(unsigned long, long)
	// function call : void *(*const)(unsigned long, long)
	// function call : void *(*const)(unsigned long, long)

	s_object_data *object = object_get(object_index);
	if (!object)
		return -1;
	s_object_definition *object_definition = (s_object_definition *)tag_get('obje', object->definition_index);
	if (!object_definition || object_definition->model.index == -1)
		return -1;
	s_model_definition *model = (s_model_definition *)tag_get('hlmt', object_definition->model.index);
	if (!model || model->physics_model.index == -1)
		return -1;
	s_physics_model_definition *physics_model = (s_physics_model_definition *)tag_get('phmo', model->physics_model.index);
	if (!physics_model || physics_model->rigid_bodies.count < 2)
		return -1;
	for (long i = 0; i < physics_model->rigid_bodies.count; i++)
	{
		s_physics_model_rigid_body const &rigid_body = physics_model->rigid_bodies[i];
		if (rigid_body.motion_type == 4 || rigid_body.motion_type == 5)
			return rigid_body.node;
	}
	return -1;
}

void UpdateSelectionManipulationState(__int32 rootObjectIndex) // 0x10A678D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?UpdateSelectionManipulationState@@YAXH@Z");
	// `anonymous-namespace'::UpdateSelectionManipulationState
	// static ...; // 0x10A67AC0
	// static ...; // 0x10A67AB4
	// static ...; // 0x10A67AAC
	// __int32 rootObjectIndex;
	// Forge::ObjectSet const &selection;
	// s_object_data *rootObject;
	// s_map_variant *map_variant;
		// long i;
			// s_variant_datum &placement;
			// s_selectionState::ChildInfo &childInfo;
			// float scale;
			// real_point3d pos;
	// function call : void (*const)(long, real_point3d *)
	// function call : s_map_variant *(*const)()
	// function call : void (*const)(long, real_point3d *)

	::Forge::ObjectSet const &selection = ::Forge::Selection::GetSelection();
	s_object_data *rootObject = object_get(rootObjectIndex);
	selectionState.children.clear();
	selectionState.initialScale = rootObject->scale;
	eldorado::object_get_origin(rootObjectIndex, &selectionState.initialPosition);
	if (!selection.Contains(rootObjectIndex))
		return;
	s_map_variant *map_variant = game_engine_get_runtime_map_variant();
	for (long i = 0; i < 640; i++)
	{
		s_variant_datum &placement = map_variant->objects[i];
		if (!placement.flags.test((e_variant_object_placement_flags)0) || placement.object_index == -1 || placement.object_index == rootObjectIndex)
			continue;
		if (!selection.Contains(placement.object_index))
			continue;
		float scale = 1.0f;
		if (placement.properties.boundry_width >= 0.00001f)
			scale = placement.properties.boundry_width;
		real_point3d pos;
		eldorado::object_get_origin(placement.object_index, &pos);
		s_selectionState::ChildInfo &childInfo = selectionState.children[placement.object_index];
		vector_from_points3d(&selectionState.initialPosition, &pos, &childInfo.displacement);
		childInfo.scale = scale;
	}
}

s_forge_palette_item *FindSandboxPaletteItem(long tag_index) // 0x10A655E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?FindSandboxPaletteItem@@YAPAUs_forge_palette_item@@J@Z");
	// `anonymous-namespace'::FindSandboxPaletteItem
	// long tag_index;
	// s_forge_globals_definition *forge_globals;
		// long i;

	s_forge_globals_definition *forge_globals = forge_globals_get_definition();
	if (!forge_globals)
	{
		return nullptr;
	}

	for (long i = 0; i < forge_globals->palette.count; i++)
	{
		if (forge_globals->palette[i].object.index == tag_index)
		{
			return &forge_globals->palette[i];
		}
	}

	return nullptr;
}

bool initialize_map_variant_from_scenario(s_map_variant *thisptr, s_scenario *scenario) // 0x10A6E7A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?initialize_map_variant_from_scenario@@YA_NPAUs_map_variant@@PAUs_scenario@@@Z");
	// `anonymous-namespace'::initialize_map_variant_from_scenario
	// s_scenario *scenario;
	// s_tag_block *(*const scenario_get_object_type_scenario_datums)(s_scenario *, e_object_type, long *);
	// c_tag_block<s_scenario_object_palette_entry> *(*const scenario_get_object_type_scenario_palette)(s_scenario *, e_object_type);
	// unsigned __int32 (*const crc_checksum_buffer)(unsigned __int32, unsigned char *, long);
	// long totalObjectCount;
	// long scnrPlacementOffset;
		// long type;
			// s_object_type_definition *type_definition;
			// c_tag_block<s_scenario_object_palette_entry> &palette;
				// s_tag_block *placementBlock;
				// long i;
					// s_variant_quota &budgetEntry;
					// s_scenario_object_palette_entry &paletteEntry;
					// s_forge_palette_item *sandboxPaletteItem;
	// function call : unsigned __int32 (*const)(unsigned __int32, unsigned char *, long)
	// function call : s_object_type_definition *(*const)(e_object_type)
	// function call : s_tag_block *(*const)(s_scenario *, e_object_type, long *)
	// function call : c_tag_block<s_scenario_object_palette_entry> *(*const)(s_scenario *, e_object_type)

	unsigned __int32 (*const crc_checksum_buffer)(unsigned __int32, unsigned char *, long) = reinterpret_cast<unsigned __int32 (*)(unsigned __int32, unsigned char *, long)>(0x52CD20);
	s_tag_block *(*const scenario_get_object_type_scenario_datums)(s_scenario *, e_object_type, long *) = reinterpret_cast<s_tag_block *(*)(s_scenario *, e_object_type, long *)>(0xB5A880);
	c_tag_block<s_scenario_object_palette_entry> *(*const scenario_get_object_type_scenario_palette)(s_scenario *, e_object_type) = reinterpret_cast<c_tag_block<s_scenario_object_palette_entry> *(*)(s_scenario *, e_object_type)>(0xB5A8B0);
	thisptr->cache_checksum = crc_checksum_buffer(0xFFFFFFFF, (unsigned char *)0x22AB34C, 256);
	thisptr->scenario_object_count = 0;
	thisptr->placeable_object_quota_count = 0;
	long totalObjectCount = 0;
	long scnrPlacementOffset = 0;
	for (long type = 0; type < 15; type++)
	{
		if (type == 7 || type == 11 || type == 1 || type == 2 || type == 3 || type == 13 || type == 0)
		{
			s_object_type_definition *type_definition = ((s_object_type_definition *(*)(long))0xB734F0)(type);
			if (type_definition->placement_tag_block_offset != -1 && type_definition->palette_tag_block_offset != -1)
			{
				s_tag_block *placementBlock = scenario_get_object_type_scenario_datums(scenario, (e_object_type)type, nullptr);
				thisptr->object_type_start_index[type] = scnrPlacementOffset;
				thisptr->variant_object_count += placementBlock->count;
				if (thisptr->variant_object_count > 640)
					return false;
				scnrPlacementOffset += placementBlock->count;
			}
			c_tag_block<s_scenario_object_palette_entry> &palette = *scenario_get_object_type_scenario_palette(scenario, (e_object_type)type);
			for (long i = 0; i < palette.count; i++)
			{
				s_scenario_object_palette_entry &paletteEntry = palette[i];
				if (((s_tag_reference *)paletteEntry.object)->index == -1)
					continue;
				if (thisptr->placeable_object_quota_count >= 256)
					return false;
				s_variant_quota &budgetEntry = thisptr->object_quotas[thisptr->placeable_object_quota_count];
				s_forge_palette_item *sandboxPaletteItem = FindSandboxPaletteItem(((s_tag_reference *)paletteEntry.object)->index);
				if (!sandboxPaletteItem)
					continue;
				budgetEntry.definition_index = ((s_tag_reference *)paletteEntry.object)->index;
				if (sandboxPaletteItem->max_allowed)
					budgetEntry.maximum_allowed = sandboxPaletteItem->max_allowed;
				else
					budgetEntry.maximum_allowed = -1;
				budgetEntry.placed_on_map = 0;
				budgetEntry.minimum_count = 0;
				budgetEntry.maximum_count = 0;
				budgetEntry.cost = 0.0f;
				thisptr->placeable_object_quota_count++;
			}
		}
	}
	thisptr->scenario_object_count = thisptr->variant_object_count;
	thisptr->maximum_budget = scenario->sandbox_budget;
	thisptr->spent_budget = 0.0f;
	return true;
}

long CreateOrGetBudgetForItem(s_map_variant *thisptr, long tag_index) // 0x10A65030
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CreateOrGetBudgetForItem@@YAJPAUs_map_variant@@J@Z");
	// `anonymous-namespace'::CreateOrGetBudgetForItem
	// static ...; // 0x10A651F4
	// static ...; // 0x10A651EC
	// s_map_variant *thisptr;
	// long tag_index;
	// long index;
	// long (*const c_map_variant__find_quota_index)(s_map_variant *, long);
		// __int32 i;
			// s_variant_quota const &budget;
		// s_variant_quota &budget;
		// s_forge_palette_item *sandboxPaletteItem;
		// wchar_t buff[256];
	// function call : long (*const)(s_map_variant *, long)

	long (__thiscall *const c_map_variant__find_quota_index)(s_map_variant *, long) = reinterpret_cast<long (__thiscall *)(s_map_variant *, long)>(0x5831C0);
	long index = c_map_variant__find_quota_index(thisptr, tag_index);
	if (index != -1)
		return index;
	if (thisptr->placeable_object_quota_count >= 256)
	{
		for (__int32 i = 0; i < thisptr->placeable_object_quota_count; i++)
		{
			s_variant_quota const &budget = thisptr->object_quotas[i];
			if (budget.definition_index == -1)
			{
				index = i;
				break;
			}
		}
	}
	else
	{
		index = thisptr->placeable_object_quota_count++;
	}
	if (index != -1)
	{
		s_variant_quota &budget = thisptr->object_quotas[index];
		s_forge_palette_item *sandboxPaletteItem = FindSandboxPaletteItem(tag_index);
		if (!sandboxPaletteItem)
			return -1;
		budget.definition_index = tag_index;
		if (sandboxPaletteItem->max_allowed)
			budget.maximum_allowed = (unsigned char)sandboxPaletteItem->max_allowed;
		else
			budget.maximum_allowed = 0xFF;
		budget.placed_on_map = 0;
		budget.minimum_count = 0;
		budget.maximum_count = 0;
		budget.cost = 0.0f;
	}
	if (index == -1)
	{
		wchar_t buff[256];
		_swprintf(buff, L"Unable to create budget for 0x%x", tag_index);
		::Forge::PrintKillFeedText(0, buff, 0);
	}
	return index;
}

void RecalculateMapVariantBudget() // 0x10A66B90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?RecalculateMapVariantBudget@@YAXXZ");
	// `anonymous-namespace'::RecalculateMapVariantBudget
	// procedure flags: nofpo
	// s_map_variant *map_variant;
		// long i;
			// s_variant_datum &placement;
			// s_variant_quota &budgetItem;
	// function call : s_map_variant *(*const)()

	s_map_variant *map_variant = game_engine_get_runtime_map_variant();
	for (long i = 0; i < 256; i++)
		map_variant->object_quotas[i].placed_on_map = 0;
	for (long i = 0; i < 640; i++)
	{
		s_variant_datum &placement = map_variant->objects[i];
		if (placement.flags.test((e_variant_object_placement_flags)0))
			map_variant->object_quotas[placement.quota_index].placed_on_map++;
	}
	for (long i = 0; i < 256; i++)
	{
		s_variant_quota &budgetItem = map_variant->object_quotas[i];
		if (budgetItem.minimum_count > budgetItem.placed_on_map)
			budgetItem.minimum_count = budgetItem.placed_on_map;
		if (budgetItem.maximum_count < budgetItem.placed_on_map)
			budgetItem.maximum_count = budgetItem.placed_on_map;
	}
}

void ObjectOutOfWorldBoundsError() // 0x10A669B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ObjectOutOfWorldBoundsError@@YAXXZ");
	// `anonymous-namespace'::ObjectOutOfWorldBoundsError
	// procedure flags: nofpo
	// function call : long (*const)(e_user_interface_sound, long)

	::Forge::PrintKillFeedText(0, L"ERROR: One or more objects outside of the world bounds", 0);

	((void(__cdecl *)(long, long))0xaa5cd0)(0, -1);
}

bool TestBarrierTestProjectile(long barrierObjectIndex, long projectileObjectIndex) // 0x10A673E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?TestBarrierTestProjectile@@YA_NJJ@Z");
	// `anonymous-namespace'::TestBarrierTestProjectile
	// long projectileObjectIndex;
	// s_damage_owner *damageOwner;
	// s_object_data *projectileObject;
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)

	s_object_data *projectileObject = object_try_and_get_and_verify_type(projectileObjectIndex, 0x40);

	if (!projectileObject)
	{
		return false;
	}

	s_damage_owner *damageOwner = (s_damage_owner *)offset_pointer(projectileObject, 0xC0);

	if (damageOwner->player_index == -1)
	{
		return false;
	}

	return ::Forge::Reforge::TeamBarrierTestPlayer(barrierObjectIndex, damageOwner->player_index);
}

void OnMonitorModeChange(bool isMonitor) // 0x10A66A70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?OnMonitorModeChange@@YAX_N@Z");
	// `anonymous-namespace'::OnMonitorModeChange
	// bool isMonitor;
		// s_player_datum *player;
		// long player_index;
	// function call : unsigned long (*const)(long)
	// function call : unsigned long (*const)(long)
	// function call : void (*const)(long, real_vector3d const *, real_vector3d const *)

	if (!isMonitor)
	{
		long player_index = eldorado::player_mapping_get_player_by_input_user_2(0);
		s_player_datum *player = players_get()->try_and_get(eldorado::player_mapping_get_player_by_input_user_2(0));

		if (!player || (player && player->unit_index == player->dead_unit_index))
			return;
		else if (player->unit_index == -1)
			return;

		eldorado::object_set_velocities(player->unit_index, &global_zero3d, &global_zero3d);
	}
}

float __fastcall c_map_variant__get_budget_fraction_hook(s_map_variant *thisptr, void *__formal, float *budget_spent, float *budget_max) // 0x10A6ACC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_map_variant__get_budget_fraction_hook@@YIMPAUs_map_variant@@PAXPAM2@Z");
	// `anonymous-namespace'::c_map_variant__get_budget_fraction_hook
	// float *budget_max;
	// static Forge::ForgeObjectQuota `c_map_variant__get_budget_fraction_hook'::`2'::cachedQuota; // 0x12458514
	// static unsigned long `c_map_variant__get_budget_fraction_hook'::`2'::last_time; // 0x12458510

	static ::Forge::ForgeObjectQuota cachedQuota;
	static unsigned long last_time;

	if (!cachedQuota.TotalObjectsAvailable || system_milliseconds() - last_time >= 150)
	{
		cachedQuota = ::Forge::CalculateObjectQuota();
		last_time = system_milliseconds();
	}

	if (budget_spent)
		*budget_spent = (float)cachedQuota.TotalObjectsUsed;

	if (budget_max)
		*budget_max = (float)cachedQuota.TotalObjectsAvailable;

	if (!cachedQuota.TotalObjectsAvailable)
		return 0.0f;

	return (float)cachedQuota.TotalObjectsUsed / (float)cachedQuota.TotalObjectsAvailable;
}

bool __fastcall c_sandbox_engine__initialize_for_new_map_hook(c_sandbox_engine *thisptr, void *__formal) // 0x10A6BA90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_sandbox_engine__initialize_for_new_map_hook@@YI_NPAUc_sandbox_engine@@PAX@Z");
	// `anonymous-namespace'::c_sandbox_engine__initialize_for_new_map_hook
	// void *__formal;
	// bool (*const c_sandbox_engine__initialize_for_new_map)(c_sandbox_engine *);
	// function call : bool (*const)(c_sandbox_engine *)

	bool (__thiscall *const c_sandbox_engine__initialize_for_new_map)(c_sandbox_engine *) = reinterpret_cast<bool (__thiscall *)(c_sandbox_engine *)>(0x59C0D0);
	if (!c_sandbox_engine__initialize_for_new_map(thisptr))
		return false;

	::Forge::Magnets::Initialize();
	::Forge::SelectionRenderer::Initialize();
	CForgeUndoManager::Instance().StartRecording();
	Web::Ui::ScreenLayer::Notify("forge_init", Web::Ui::WebForge::BuildForgePaletteJSON(), true);
	return true;
}

void __fastcall c_sandbox_engine__dispose_from_old_map_hook(c_sandbox_engine *thisptr, void *__formal) // 0x10A6B960
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_sandbox_engine__dispose_from_old_map_hook@@YIXPAUc_sandbox_engine@@PAX@Z");
	// `anonymous-namespace'::c_sandbox_engine__dispose_from_old_map_hook
	// void *__formal;
	// void (*const c_sandbox_engine__dispose_from_old_map)(c_sandbox_engine *);
	// function call : void (*const)(c_sandbox_engine *)

	const auto c_sandbox_engine__dispose_from_old_map = (void(__thiscall *)(c_sandbox_engine *))0x59A600;

	c_sandbox_engine__dispose_from_old_map(thisptr);

	::Forge::Magnets::Shutdown();
	::Forge::Selection::Clear();
	::Forge::SelectionRenderer::SetEnabled(false);
	::Forge::SelectionRenderer::Dispose();
	CForgeUndoManager::Instance().Clear();
}

void __fastcall c_sandbox_engine__update_hook(c_sandbox_engine *thisptr, void *__formal) // 0x10A6C2E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_sandbox_engine__update_hook@@YIXPAUc_sandbox_engine@@PAX@Z");
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
		// Modules::ModuleForge const &moduleForge;
	// function call : void (*const)(c_sandbox_engine *)
	// function call : unsigned long (*const)(long)
	// function call : bool (*const)(long, long *, long *)

	void (__thiscall *const c_sandbox_engine__update)(c_sandbox_engine *) = reinterpret_cast<void (__thiscall *)(c_sandbox_engine *)>(0x59ED70);
	c_sandbox_engine__update(thisptr);
	::Forge::SelectionRenderer::Update();
	::Forge::Magnets::Update();
	Utils::Singleton<CForgeUndoManager>::Instance().Update();
	SubmitWorldBoundsForRendering();
	HandleCommands();
	long activeScreenCount = Pointer(0x5260F34)[0](0x3C, true).Read<short>();
	if (activeScreenCount > 0)
		return;
	long player_index = ((unsigned long (*)(long))0x589C30)(0);
	if (player_index == -1)
		return;
	long editing_object_index = -1;
	long crosshair_object_index = -1;
	bool isMonitor = ((bool (*)(long, long *, long *))0x59A6F0)(player_index, &editing_object_index, &crosshair_object_index);
	if (isMonitor != monitorState.MonitorLastTick)
	{
		OnMonitorModeChange(isMonitor);
		monitorState.MonitorLastTick = isMonitor;
	}
	if (isMonitor)
	{
		Modules::ModuleForge const &moduleForge = Utils::Singleton<Modules::ModuleForge>::Instance();
		::Forge::SelectionRenderer::SetEnabled(true);
		::Forge::SelectionRenderer::SetRendererType((::Forge::SelectionRenderer::RendererImplementationType)moduleForge.VarSelectionRenderer->ValueInt);
		::Forge::Selection::Update();
		::Forge::RotationSnap::Update(player_index, editing_object_index);
		HandleMovementSpeed();
		HandleMonitorNoclip();
		HandleMonitorInput(player_index);
	}
	else
	{
		::Forge::SelectionRenderer::SetEnabled(false);
	}
}

void __fastcall c_sandbox_engine__rotate_object_hook(c_sandbox_engine *thisptr, void *__formal, long playerIndex, long objectIndex, float yaw, float pitch, float roll) // 0x10A6BC10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_sandbox_engine__rotate_object_hook@@YIXPAUc_sandbox_engine@@PAXJJMMM@Z");
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

	void (__thiscall *const c_sandbox_engine__rotate_object)(c_sandbox_engine *, long, long, float, float, float) = reinterpret_cast<void (__thiscall *)(c_sandbox_engine *, long, long, float, float, float)>(0x59DD50);
	Modules::ModuleForge const &moduleForge = Modules::ModuleForge::Instance();
	long const currentSnap = moduleForge.VarRotationSnap->ValueInt;
	float const rotationSensitivity = moduleForge.VarRotationSensitivity->ValueFloat;
	if (playerIndex != eldorado::player_mapping_get_player_by_input_user(0))
	{
		c_sandbox_engine__rotate_object(thisptr, playerIndex, objectIndex, yaw, pitch, roll);
		return;
	}
	yaw = rotationSensitivity * 0.5f * yaw;
	pitch = rotationSensitivity * 0.5f * pitch;
	roll = rotationSensitivity * 0.5f * roll;
	HandleRotationReset();
	if (currentSnap < 1)
	{
		c_sandbox_engine__rotate_object(thisptr, playerIndex, objectIndex, yaw, pitch, roll);
		return;
	}
	s_player_datum *player = player_get(playerIndex);
	if (player->unit_index == -1)
		return;
	real_matrix4x3 objectTransform;
	eldorado::object_get_world_matrix(player->unit_index, &objectTransform);
	float const xn = abs(yaw);
	float const yn = abs(pitch);
	float const zn = abs(roll);
	float const DEAD_ZONE = 0.5f * rotationSensitivity * 0.5f;
	static float xticks = 0;
	static float yticks = 0;
	static float zticks = 0;
	if (xn > DEAD_ZONE)
		xticks += 1;
	else
		xticks = 0;
	if (yn > DEAD_ZONE)
		yticks += 1;
	else
		yticks = 0;
	if (zn > DEAD_ZONE)
		zticks += 1;
	else
		zticks = 0;
	if (zn > DEAD_ZONE && zticks == 1)
	{
		::Forge::RotationSnap::RotateSnapped(::Forge::GetClosestCardianalAxix(objectTransform.forward) * (roll > 0 ? 1.0f : -1.0f));
	}
	else if (xn > yn && xticks == 1)
	{
		::Forge::RotationSnap::RotateSnapped(::Forge::GetClosestCardianalAxix(objectTransform.up) * (yaw > 0 ? -1.0f : 1.0f));
	}
	else if (yticks == 1)
	{
		::Forge::RotationSnap::RotateSnapped(::Forge::GetClosestCardianalAxix(objectTransform.left) * (pitch > 0 ? 1.0f : -1.0f));
	}
}

void __fastcall c_sandbox_engine__handle_deleted_object_hook(c_sandbox_engine *thisptr, void *__formal, long object_index) // 0x10A6BA00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_sandbox_engine__handle_deleted_object_hook@@YIXPAUc_sandbox_engine@@PAXJ@Z");
	// `anonymous-namespace'::c_sandbox_engine__handle_deleted_object_hook
	// long object_index;
	// void (*const c_sandbox_engine__handle_deleted_object)(c_sandbox_engine *, long);
	// function call : void (*const)(c_sandbox_engine *, long)

	const auto c_sandbox_engine__handle_deleted_object = (void(__thiscall *)(c_sandbox_engine *, long))0x59BC70;

	::Forge::Selection::GetSelection().Remove(object_index);
	c_sandbox_engine__handle_deleted_object(thisptr, object_index);
}

void game_engine_sandox_apply_grab_object_hook2(long player_index, long object_index) // 0x10A6E2A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_engine_sandox_apply_grab_object_hook2@@YAXJJ@Z");
	// `anonymous-namespace'::game_engine_sandox_apply_grab_object_hook2
	// long object_index;
	// void (*const havok_object_rebuild_immediate)(long);
	// void (*const game_engine_sandbox_apply_grab_object_no_fail)(long, long);
	// function call : void (*const)(long)
	// function call : unsigned long (*const)(long)
	// function call : void (*const)(long, long)

	void (__cdecl *const sub_59CF50)(long, long) = (void(__cdecl *const)(long, long))0x59cf50;
	void (__cdecl *const sub_5C7360)(long) = (void(__cdecl *const)(long))0x5c7360;

	sub_5C7360(object_index);
	if (player_index == eldorado::player_mapping_get_player_by_input_user_2(0))
	{
		monitorState.HeldObjectIndex = object_index;
		monitorState.HeldObjectRootNode = FindComplexObjectRigidBodyRootNode(object_index);
	}
	sub_59CF50(player_index, object_index);
}

void game_engine_sandox_apply_grab_object_hook(long player_index, long map_variant_index) // 0x10A6E370
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_engine_sandox_apply_grab_object_hook@@YAXJJ@Z");
	// `anonymous-namespace'::game_engine_sandox_apply_grab_object_hook
	// long map_variant_index;

	GrabObject(player_index, map_variant_index);
}

void game_engine_sandbox_stop_editing_object_hook(long map_variant_index, float force, bool activate_physics) // 0x10A6DC20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_engine_sandbox_stop_editing_object_hook@@YAXJM_N@Z");
	// `anonymous-namespace'::game_engine_sandbox_stop_editing_object_hook
	// static ...; // 0x10A6E068
	// static ...; // 0x10A6E044
	// static ...; // 0x10A6E03C
	// long map_variant_index;
	// float force;
	// bool activate_physics;
	// s_object_data *droppedObject;
	// std::stack<unsigned int> detachStack;
	// Forge::ObjectSet &selection;
	// void (*const game_engine_sandbox_stop_editing_object)(long, float, bool);
	// Forge::Magnets::MagnetPair const &magnetPair;
	// long playerIndex;
	// s_map_variant *map_variant;
	// void (*const object_set_uses_fixed_physics)(long, bool);
	// long droppedObjectIndex;
	// __int32 (*const c_map_variant__register_object)(void *, long, long);
		// long objectIndex;
			// s_object_data *object;
		// real_point3d heldObjectPosition;
		// real_vector3d displacement;
		// s_object_data *object;
	// function call : s_map_variant *(*const)()
	// function call : long (*const)(long)
	// function call : unsigned long (*const)(long)
	// function call : void (*const)(long, float, bool)
	// function call : void (*const)(long, real_point3d *)
	// function call : void (*const)(bool, long, real_point3d const *, real_vector3d const *, real_vector3d const *)
	// function call : void (*const)(long)
	// function call : __int32 (*const)(void *, long, long)
	// function call : void (*const)(long, bool)

	void (*const game_engine_sandbox_stop_editing_object)(long, float, bool) = reinterpret_cast<void (*)(long, float, bool)>(0x59B250);
	__int32 (__thiscall *const c_map_variant__register_object)(void *, long, long) = reinterpret_cast<__int32 (__thiscall *)(void *, long, long)>(0x5855E0);
	void (*const object_set_uses_fixed_physics)(long, bool) = reinterpret_cast<void (*)(long, bool)>(0xB313E0);
	s_map_variant *map_variant = game_engine_get_runtime_map_variant();
	long droppedObjectIndex = map_variant->objects[map_variant_index].object_index;
	if (droppedObjectIndex == -1)
		return;
	s_object_data *droppedObject = object_get(droppedObjectIndex);
	if (!droppedObject)
		return;
	if (!::Forge::ObjectInWorldBounds(droppedObjectIndex))
	{
		ObjectOutOfWorldBoundsError();
		return;
	}
	std::stack<unsigned int> detachStack;
	::Forge::ObjectSet &selection = ::Forge::Selection::GetSelection();
	if (selection.Contains(droppedObjectIndex))
	{
		long objectIndex = droppedObject->first_child_object_index;
		while (objectIndex != -1)
		{
			s_object_data *object = object_get(objectIndex);
			if (!object)
				continue;
			if (!::Forge::ObjectInWorldBounds(objectIndex))
			{
				ObjectOutOfWorldBoundsError();
				return;
			}
			if (selection.Contains(objectIndex))
				detachStack.push(objectIndex);
			objectIndex = object->next_object_index;
		}
	}
	long playerIndex = ((long (*)(long))0x59BB90)(droppedObjectIndex);
	if (playerIndex == ((long (*)(long))0x589C30)(0))
		monitorState.HeldObjectIndex = -1;
	game_engine_sandbox_stop_editing_object(map_variant_index, force, activate_physics);
	::Forge::Magnets::MagnetPair const &magnetPair = ::Forge::Magnets::GetMagnetPair();
	if (magnetPair.IsValid)
	{
		real_point3d heldObjectPosition;
		((void (*)(long, real_point3d *))0xB2E5A0)(droppedObjectIndex, &heldObjectPosition);
		real_vector3d displacement;
		vector_from_points3d(&magnetPair.Source->Position, &magnetPair.Dest->Position, &displacement);
		point_from_line3d(&heldObjectPosition, &displacement, 1.0f, &heldObjectPosition);
		((void (*)(long, long, real_point3d *, long, long))0x59E340)(0, droppedObjectIndex, &heldObjectPosition, 0, 0);
	}
	while (!detachStack.empty())
	{
		long objectIndex = detachStack.top();
		detachStack.pop();
		s_object_data *object = object_get(objectIndex);
		if (!object)
			continue;
		if (CreateOrGetBudgetForItem(map_variant, object->definition_index) == -1)
		{
			::Forge::PrintKillFeedText(0, L"ERROR: Budget limit reached", 0);
			break;
		}
		((void (*)(long))0xB2D180)(objectIndex);
		c_map_variant__register_object(map_variant, objectIndex, -1);
		if (!::Forge::Reforge::IsReforgeObject(objectIndex) && !::Forge::ObjectIsForgeScenery(objectIndex))
		{
			object_set_uses_fixed_physics(objectIndex, true);
			::Forge::ThrowObject(playerIndex, objectIndex, force);
		}
	}
	RecalculateMapVariantBudget();
}

void game_engine_sandbox_delete_object_hook(long map_variant_index, long player_index) // 0x10A6D850
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_engine_sandbox_delete_object_hook@@YAXJJ@Z");
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
		// s_object_data *heldObject;
		// long i;
			// s_variant_datum &placement;
	// function call : bool (*const)(long, long *, long *)
	// function call : s_map_variant *(*const)()
	// function call : void (*const)(long, long)
	// function call : void (*const)(long, long)

	void (*const game_engine_sandbox_delete_object)(long, long) = reinterpret_cast<void (*)(long, long)>(0x59A920);
	AddMapVariantUndoPoint("Object Deleted");
	long heldObjectIndex = -1;
	long crosshairObjectIndex = -1;
	((bool (*const)(long, long *, long *))0x59A6F0)(player_index, &heldObjectIndex, &crosshairObjectIndex);
	if (heldObjectIndex != -1 && crosshairObjectIndex != -1)
	{
		s_object_data *heldObject = object_get(heldObjectIndex);
		if (map_variant_index != heldObject->map_variant_index)
			map_variant_index = heldObject->map_variant_index;
	}
	s_map_variant *map_variant = game_engine_get_runtime_map_variant();
	::Forge::ObjectSet const &selection = ::Forge::Selection::GetSelection();
	long deletedObjectIndex = map_variant->objects[map_variant_index].object_index;
	if (selection.Contains(deletedObjectIndex))
	{
		for (long i = 0; i < 640; i++)
		{
			s_variant_datum const &placement = map_variant->objects[i];
			if (!placement.flags.test((e_variant_object_placement_flags)0) || placement.object_index == -1 || placement.object_index == deletedObjectIndex)
				continue;
			if (selection.Contains(placement.object_index))
				game_engine_sandbox_delete_object(i, player_index);
		}
	}
	game_engine_sandbox_delete_object(map_variant_index, player_index);
	get_sandbox_globals()->player_cursor_distance[player_index & 0xF] = *(float *)0x18A157C;
}

void game_engine_sandbox_place_object_hook(long tag_index, long player_index, real_point3d const *position) // 0x10A6DAF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_engine_sandbox_place_object_hook@@YAXJJPBUreal_point3d@@@Z");
	// `anonymous-namespace'::game_engine_sandbox_place_object_hook
	// real_point3d const *position;
	// void (*const game_engine_sandbox_place_object)(long, long, real_point3d const *);
	// function call : unsigned long (*const)(long)
	// function call : void (*const)(long, long, real_point3d const *)

	void (__cdecl *const game_engine_sandbox_place_object)(long, long, real_point3d const *) = (void(__cdecl *const)(long, long, real_point3d const *))0x59ae50;

	AddMapVariantUndoPoint("Spawn Item");
	CForgeUndoManager::Instance().StopRecording();

	if (player_index == eldorado::player_mapping_get_player_by_input_user_2(0))
	{
		monitorState.GrabOffset = { 0.0f, 0.0f, 0.0f };
	}

	game_engine_sandbox_place_object(tag_index, player_index, position);
	CForgeUndoManager::Instance().StartRecording();
}

void ApplyObjectPropertiesToSelection(long playerIndex, long rootObjectIndex, s_map_variant_placement_properties *properties) // 0x10A64A30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyObjectPropertiesToSelection@@YAXJJPAUs_map_variant_placement_properties@@@Z");
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
		// long i;
			// s_variant_datum &placement;
			// s_map_variant_placement_properties tmp;
				// std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<int const ,ChildInfo> > > > it;
					// real_point3d newPos;
					// float deltaScale;
	// function call : s_map_variant *(*const)()
	// function call : void (*const)(bool, long, real_point3d const *, real_vector3d const *, real_vector3d const *)
	// function call : void (*const)(long, long, s_map_variant_placement_properties *)

	void (*const game_engine_sandbox_update_variant_object_properties)(long, long, s_map_variant_placement_properties *) = reinterpret_cast<void (*)(long, long, s_map_variant_placement_properties *)>(0x59B5F0);
	s_map_variant *map_variant = game_engine_get_runtime_map_variant();
	::Forge::ObjectSet const &selection = ::Forge::Selection::GetSelection();
	bool isForgeScenery = ::Forge::ObjectIsForgeScenery(rootObjectIndex);
	for (long i = 0; i < 640; i++)
	{
		s_variant_datum &placement = map_variant->objects[i];
		if (!placement.flags.test((e_variant_object_placement_flags)0) || placement.object_index == -1 || placement.object_index == rootObjectIndex)
			continue;
		if (!selection.Contains(placement.object_index))
			continue;
		s_map_variant_placement_properties tmp;
		memcpy(&tmp, properties, sizeof(s_map_variant_placement_properties));
		if (isForgeScenery)
		{
			auto it = selectionState.children.find(placement.object_index);
			if (it != selectionState.children.end())
			{
				if (fabs(selectionState.initialScale) >= 0.00001f)
				{
					float deltaScale = properties->boundry_width / selectionState.initialScale;
					tmp.boundry_width = it->second.scale * deltaScale;
					real_point3d newPos;
					point_from_line3d(&selectionState.initialPosition, &it->second.displacement, deltaScale, &newPos);
					((void (*const)(bool, long, real_point3d const *, real_vector3d const *, real_vector3d const *))0x59E340)(false, placement.object_index, &newPos, nullptr, nullptr);
				}
			}
		}
		game_engine_sandbox_update_variant_object_properties(playerIndex, i, &tmp);
	}
}

void game_engine_sandbox_update_variant_object_properties_hook(long player_index, long map_variant_index, s_map_variant_placement_properties *properties) // 0x10A6E1C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_engine_sandbox_update_variant_object_properties_hook@@YAXJJPAUs_map_variant_placement_properties@@@Z");
	// `anonymous-namespace'::game_engine_sandbox_update_variant_object_properties_hook
	// s_map_variant_placement_properties *properties;
	// void (*const ame_engine_sandbox_update_variant_object_properties)(unsigned __int32, unsigned short, s_map_variant_placement_properties *);
	// s_map_variant *map_variant;
	// long changedObjectIndex;
	// function call : s_map_variant *(*const)()
	// function call : void (*const)(unsigned __int32, unsigned short, s_map_variant_placement_properties *)

	const auto game_engine_sandbox_update_variant_object_properties = (void(*)(unsigned __int32, unsigned short, s_map_variant_placement_properties *))0x59B5F0;

	s_map_variant *map_variant = game_engine_get_runtime_map_variant();
	long changedObjectIndex = map_variant->objects[map_variant_index].object_index;

	game_engine_sandbox_update_variant_object_properties(player_index, map_variant_index, properties);

	if (::Forge::Selection::GetSelection().Contains(changedObjectIndex))
	{
		ApplyObjectPropertiesToSelection(player_index, changedObjectIndex, properties);
	}
}

void character_physics_update_input_datum_initialize_flying_hook(long unit_index, s_character_physics_update_input_datum *physics_input, c_character_physics_component *physics_component, float a6, float a7) // 0x10A6C960
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?character_physics_update_input_datum_initialize_flying_hook@@YAXJPAUs_character_physics_update_input_datum@@PAUc_character_physics_component@@MM@Z");
	// `anonymous-namespace'::character_physics_update_input_datum_initialize_flying_hook
	// float a7;
	// s_player_datum *player;
	// void (*const character_physics_update_input_datum_initialize_flying)(long, s_character_physics_update_input_datum *, c_character_physics_component *, float, float);
	// long playerIndex;
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
	// function call : unsigned long (*const)(long)
	// function call : bool (*const)(long, long *, long *)
	// function call : void (*const)(long, s_character_physics_update_input_datum *, c_character_physics_component *, float, float)
	// function call : void *(*const)(unsigned long, long)
	// function call : float (*const)()
	// function call : void (*const)(long, s_character_physics_update_input_datum *, c_character_physics_component *, float, float)

	void (*const character_physics_update_input_datum_initialize_flying)(long, s_character_physics_update_input_datum *, c_character_physics_component *, float, float) = (void (*)(long, s_character_physics_update_input_datum *, c_character_physics_component *, float, float))0x7205D0;
	long playerIndex = eldorado::player_mapping_get_player_by_input_user(0);
	s_player_datum *player = player_get(playerIndex);
	if (player && player->unit_index == unit_index && ((bool (*const)(long, long *, long *))0x59A6F0)(playerIndex, nullptr, nullptr))
	{
		Modules::ModuleForge &moduleForge = Modules::ModuleForge::Instance();
		float &monitorSpeed = *(float *)offset_pointer(physics_input, 0x150);
		monitorSpeed *= MONITOR_MOVEMENT_SPEEDS[moduleForge.VarMonitorSpeed->ValueInt];
		character_physics_update_input_datum_initialize_flying(unit_index, physics_input, physics_component, a6, a7);
		long activeScreenCount = Pointer(0x5260F34)[0](0x3C, 1).Read<short>();
		if (activeScreenCount)
			return;
		s_object_data *biped = object_get(unit_index);
		if (!biped)
			return;
		s_biped_definition *biped_definition = (s_biped_definition *)tag_get('bipd', biped->definition_index);
		float maxVelocity = biped_definition->physics.flying.maximum_velocity * monitorSpeed;
		float acceleration = biped_definition->physics.flying.acceleration;
		float deceleration = biped_definition->physics.flying.deceleration;
		Blam::Input::ActionState *uiRightBumper = Blam::Input::GetActionState(Blam::Input::eGameActionUiRightBumper);
		Blam::Input::ActionState *uiLeftBumper = Blam::Input::GetActionState(Blam::Input::eGameActionUiLeftBumper);
		bool movementDisabled = tls_getd().players_globals->mostly_input_inhibit;
		if (movementDisabled || Patches::Camera::GetForcedCameraMode() == _camera_mode_flying)
			return;
		static float s_Velocity = 0;
		float direction = 0;
		if (!(uiRightBumper->Flags & 1) && uiRightBumper->Ticks > 0)
			direction = 1.0f;
		else if (!(uiLeftBumper->Flags & 1) && uiLeftBumper->Ticks > 0)
			direction = -1.0f;
		float t = game_tick_length();
		float destination = direction * maxVelocity;
		s_Velocity = (1.0f - t * acceleration) * s_Velocity + t * deceleration * destination;
		real_vector3d *velocity = (real_vector3d *)offset_pointer(physics_input, 0x134);
		if (direction != 0)
			velocity->k = s_Velocity;
	}
	else
	{
		character_physics_update_input_datum_initialize_flying(unit_index, physics_input, physics_component, a6, a7);
	}
}

void update_edited_object_transform_hook(bool apply_gravity, long object_index, real_point3d const *position, real_vector3d const *forward, real_vector3d const *up) // 0x10A70320
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?update_edited_object_transform_hook@@YAX_NJPBUreal_point3d@@PBUreal_vector3d@@2@Z");
	// `anonymous-namespace'::update_edited_object_transform_hook
	// bool apply_gravity;
	// long object_index;
	// real_point3d const *position;
	// real_vector3d const *forward;
	// real_vector3d const *up;
	// Forge::ObjectSet const &selection;
	// unsigned long playerHandle;
	// s_object_data *heldObject;
		// real_point3d newPos;
		// real_vector3d offset;
	// function call : long (*const)(long)
	// function call : bool (*const)(long)
	// function call : void (*const)(bool, long, real_point3d const *, real_vector3d const *, real_vector3d const *)
	// function call : void (*const)(bool, long, real_point3d const *, real_vector3d const *, real_vector3d const *)

	s_object_data *heldObject = object_get(object_index);
	if (!heldObject)
		return;
	unsigned long playerHandle = ((long (*)(long))0x59BB90)(object_index);
	if (playerHandle == -1)
		return;
	::Forge::ObjectSet const &selection = ::Forge::Selection::GetSelection();
	if (((bool (*)(long))0x59A7B0)(object_index))
	{
		real_vector3d offset = -(heldObject->bounding_sphere_center - heldObject->relative_position - monitorState.GrabOffset);
		real_point3d newPos = get_sandbox_globals()->player_cursor_position[playerHandle & 0xF] + offset;
		((void (*)(bool, long, real_point3d const *, real_vector3d const *, real_vector3d const *))0x59E340)(apply_gravity, object_index, &newPos, forward, up);
	}
	else
	{
		((void (*)(bool, long, real_point3d const *, real_vector3d const *, real_vector3d const *))0x59E340)(apply_gravity, object_index, position, forward, up);
	}
}

bool shoot_probe_for_player_test_vector_hook(unsigned long flags, unsigned long test_object_flags, real_point3d const *origin, real_vector3d const *vector, __int32 ignore_object_index1, __int32 ignore_object_index2, s_collision_result *results) // 0x10A70080
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?shoot_probe_for_player_test_vector_hook@@YA_NKKPBUreal_point3d@@PBUreal_vector3d@@HHPAUs_collision_result@@@Z");
	// `anonymous-namespace'::shoot_probe_for_player_test_vector_hook
	// s_collision_result *results;
	// bool (*const collision_test_vector)(unsigned long, unsigned long, real_point3d const *, real_vector3d const *, long, long, s_collision_result *);
	// function call : bool (*const)(unsigned long, unsigned long, real_point3d const *, real_vector3d const *, long, long, s_collision_result *)

	bool (__cdecl *const shoot_probe_for_player_test_vector)(unsigned long, unsigned long, real_point3d const *, real_vector3d const *, __int32, __int32, s_collision_result *) = (bool(__cdecl *const)(unsigned long, unsigned long, real_point3d const *, real_vector3d const *, __int32, __int32, s_collision_result *))0x6d7160;

	if (ignore_object_index1 != -1 && Modules::ModuleForge::Instance().VarMonitorNoclip->ValueInt)
		return false;

	return shoot_probe_for_player_test_vector(flags, test_object_flags, origin, vector, ignore_object_index1, ignore_object_index2, results);
}

void *object_properties_user_interface_allocate_hook(long size) // 0x10A6F670
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?object_properties_user_interface_allocate_hook@@YAPAXJ@Z");
	// `anonymous-namespace'::object_properties_user_interface_allocate_hook
	// static ...; // 0x10A6F78C
	// static ...; // 0x10A6F77C
	// static ...; // 0x10A6F764
	// static ...; // 0x10A6F75C
	// long size;
	// long heldObjectIndex;
	// long objectIndexUnderCrosshair;
	// long playerIndex;
		// long currentObjectIndex;
		// s_object_data *currentObject;
	// function call : unsigned long (*const)(long)
	// function call : bool (*const)(long, long *, long *)

	long playerIndex = ((long (*)(long))0x589C30)(0);
	long objectIndexUnderCrosshair;
	long heldObjectIndex;
	if (((bool (*)(long, long *, long *))0x59A6F0)(playerIndex, &heldObjectIndex, &objectIndexUnderCrosshair))
	{
		long currentObjectIndex = heldObjectIndex != -1 ? heldObjectIndex : objectIndexUnderCrosshair;
		s_object_data *currentObject = object_get(currentObjectIndex);
		if (currentObject && currentObject->map_variant_index != -1)
		{
			AddMapVariantUndoPoint("Object Properties");
			UpdateSelectionManipulationState(currentObjectIndex);
			Web::Ui::WebForge::ShowObjectProperties(currentObjectIndex);
		}
	}
	return nullptr;
}

void *object_creation_user_interface_allocate_hook(long size) // 0x10A6F530
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?object_creation_user_interface_allocate_hook@@YAPAXJ@Z");
	// `anonymous-namespace'::object_creation_user_interface_allocate_hook
	// long size;

	Web::Ui::WebForge::ShowObjectCreation();
	return nullptr;
}

bool shoot_probe_for_player_hook(long player_index, long *out_object_index) // 0x10A6FF60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?shoot_probe_for_player_hook@@YA_NJPAJ@Z");
	// `anonymous-namespace'::shoot_probe_for_player_hook
	// long *out_object_index;
	// bool (*const shoot_probe_for_player)(long, long *);
		// s_sandbox_globals *sandbox_globals;
		// long player_absolute_index;
			// bool ret;
			// float old_distance;
	// function call : unsigned long (*const)(long)
	// function call : bool (*const)(long, long *)
	// function call : bool (*const)(long, long *)

	bool (__cdecl *const shoot_probe_for_player)(long, long *) = (bool(__cdecl *const)(long, long *))0x59e720;

	if (eldorado::player_mapping_get_player_by_input_user_2(0) == player_index)
	{
		s_sandbox_globals *sandbox_globals = get_sandbox_globals();
		long player_absolute_index = player_index & 0xF;

		if (sandbox_globals->player_edited_object_index[player_absolute_index] == -1)
		{
			float old_distance = sandbox_globals->player_cursor_distance[player_absolute_index];
			sandbox_globals->player_cursor_distance[player_absolute_index] = Modules::ModuleForge::Instance().VarMaxGrabDistance->ValueFloat;
			bool ret = shoot_probe_for_player(player_index, out_object_index);
			sandbox_globals->player_cursor_distance[player_absolute_index] = old_distance;
			return ret;
		}
	}

	return shoot_probe_for_player(player_index, out_object_index);
}

void __fastcall c_map_variant__apply_multiplayer_properties_hook(s_map_variant *thisptr, void *__formal, s_map_variant_placement_properties *properties, long object_index) // 0x10A6A9B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_map_variant__apply_multiplayer_properties_hook@@YIXPAUs_map_variant@@PAXPAUs_map_variant_placement_properties@@J@Z");
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

	void (__thiscall *const c_map_variant__apply_multiplayer_properties)(s_map_variant *, s_map_variant_placement_properties *, long) = reinterpret_cast<void (__thiscall *)(s_map_variant *, s_map_variant_placement_properties *, long)>(0x580E80);
	void (*const change_object_physics_mode)(long, long) = reinterpret_cast<void (*)(long, long)>(0x59A620);
	s_object_data *object = object_get(object_index);
	if (!object)
		return;
	s_multiplayer_object_properties *mpProperties = object_get_multiplayer(object_index);
	if (!mpProperties)
		return;
	char oldZoneShape = mpProperties->boundary_shape;
	if (properties->game_engine_flags)
		mpProperties->engine_flags = (unsigned short)properties->game_engine_flags;
	c_map_variant__apply_multiplayer_properties(thisptr, properties, object_index);
	if (!(properties->boundry_shape == oldZoneShape))
	{
		if ((char)properties->boundry_shape == 4)
			::Forge::SetObjectPhysicsMode(object_index, ::Forge::Phased, true);
		else if (oldZoneShape == 4)
			::Forge::SetObjectPhysicsMode(object_index, ::Forge::Normal, true);
	}
	if (::Forge::ObjectIsForgeScenery(object_index))
		::Forge::ScaleForgeSceneryObject(object_index, properties->boundry_width);
}

void c_map_variant__setup_object_properties_hook(s_variant_datum *placement) // 0x10A6B2C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_map_variant__setup_object_properties_hook@@YAXPAUs_variant_datum@@@Z");
	// `anonymous-namespace'::c_map_variant__setup_object_properties_hook
	// s_variant_datum *placement;
	// long (*const weapon_get_rounds_inventory)(long, short, bool);
	// s_object_data *object;
	// s_multiplayer_object_properties *mpProperties;
		// s_weapon_definition *weaponDefinition;
			// long rounds;
			// s_weapon_magazine_definition &magazine;
	// function call : s_multiplayer_object_properties *(*const)(unsigned long)
	// function call : void *(*const)(unsigned long, long)
	// function call : long (*const)(long, short, bool)

	long (*const weapon_get_rounds_inventory)(long, short, bool) = reinterpret_cast<long (*)(long, short, bool)>(0xB63150);
	if (placement->object_index == -1)
		return;
	s_object_data *object = object_get(placement->object_index);
	if (!object)
		return;
	s_multiplayer_object_properties *mpProperties = object_get_multiplayer(placement->object_index);
	if (!mpProperties)
		return;
	placement->properties.game_engine_flags = (unsigned short)mpProperties->engine_flags;
	placement->properties.multiplayer_object_type = mpProperties->multiplayer_object_type;
	placement->properties.placement_flags = (unsigned char)0;
	placement->properties.team_affiliation = (short)mpProperties->team_designator & 0xFF;
	placement->properties.shared_storage = 0;
	placement->properties.boundry_shape = (char)mpProperties->boundary_shape;
	placement->properties.placement_flags.set(_variant_placement_unique_spawn_bit, mpProperties->definition_flags.test(_multiplayer_object_unknown6_bit));
	placement->properties.placement_flags.set(_variant_placement_not_initially_placed_bit, mpProperties->definition_flags.test(_multiplayer_object_unknown7_bit));
	placement->properties.placement_flags.set(_variant_placement_symmetric_bit, mpProperties->symmetry == _game_engine_symmetry_symmetric || mpProperties->symmetry == _game_engine_symmetry_disregard);
	placement->properties.placement_flags.set(_variant_placement_asymmetric_bit, mpProperties->symmetry == _game_engine_symmetry_asymmetric || mpProperties->symmetry == _game_engine_symmetry_disregard);
	if (mpProperties->spawn_time < 0 || mpProperties->spawn_time >= 255)
		placement->properties.respawn_time = 0;
	else
		placement->properties.respawn_time = mpProperties->spawn_time & 0xFF;
	if (object->object_identifier.type == _object_type_weapon)
	{
		s_weapon_definition *weaponDefinition = (s_weapon_definition *)tag_get('weap', object->definition_index);
		if (weaponDefinition->magazines.count > 0)
		{
			s_weapon_magazine_definition &magazine = weaponDefinition->magazines[0];
			long rounds = weapon_get_rounds_inventory(placement->object_index, 0, true);
			if (magazine.rounds_total_loaded_maximum)
				placement->properties.shared_storage = rounds / magazine.rounds_total_loaded_maximum;
		}
	}
	else if (mpProperties->multiplayer_object_type >= _object_multiplayer_type_teleporter_2way && mpProperties->multiplayer_object_type <= _object_multiplayer_type_teleporter_receiver)
		placement->properties.shared_storage = mpProperties->teleporter_channel;
	else
		placement->properties.shared_storage = mpProperties->spare_clips;
	memcpy(&placement->properties.boundry_width, &mpProperties->boundry_width, 16);
}

void __fastcall c_map_variant__initialize_from_scenario_hook(s_map_variant *thisptr, void *unused) // 0x10A6AE40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_map_variant__initialize_from_scenario_hook@@YIXPAUs_map_variant@@PAX@Z");
	// `anonymous-namespace'::c_map_variant__initialize_from_scenario_hook
	// void *unused;
	// s_scenario *scenario;
	// function call : void (*const)(s_map_variant *, long)
	// function call : bool (*const)()
	// function call : void (*const)(s_map_variant *, long)

	s_scenario *scenario = global_scenario_get();
	((void (__thiscall *)(s_map_variant *, long))0x581F70)(thisptr, scenario->map_id);
	if (!initialize_map_variant_from_scenario(thisptr, scenario))
	{
		if (game_is_multiplayer())
			Console::WriteLine("ERROR: Failed to initialize map variant from scenario. Too many objects!");
		((void (__thiscall *)(s_map_variant *, long))0x581F70)(thisptr, scenario->map_id);
	}
}

void __fastcall c_map_variant__recalculate_quota_hook(s_map_variant *thisptr, void *unused, __int32 budgetIndex, char arg_4) // 0x10A6B0A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_map_variant__recalculate_quota_hook@@YIXPAUs_map_variant@@PAXHD@Z");
	// `anonymous-namespace'::c_map_variant__recalculate_quota_hook
	// char arg_4;
	// s_variant_quota &budget;
	// void (*const c_map_variant_update_item_budget)(s_map_variant *, __int32, char);
		// s_object_definition *objectDef;
	// function call : void (*const)(s_map_variant *, __int32, char)
	// function call : bool (*const)()
	// function call : void *(*const)(unsigned long, long)

	void (__thiscall *const c_map_variant_update_item_budget)(s_map_variant *, __int32, char) = reinterpret_cast<void (__thiscall *)(s_map_variant *, __int32, char)>(0x584E10);
	c_map_variant_update_item_budget(thisptr, budgetIndex, arg_4);
	s_variant_quota &budget = thisptr->object_quotas[budgetIndex];
	if (game_engine_is_sandbox())
	{
		s_object_definition *objectDef = (s_object_definition *)tag_get('obje', budget.definition_index);
		if (objectDef && objectDef->multiplayer_object.count && objectDef->multiplayer_object[0].engine_flags)
			return;
	}
	if (!budget.placed_on_map)
	{
		budget.definition_index = -1;
		budget.cost = -1.0f;
		budget.placed_on_map = 0;
		budget.maximum_allowed = 0xFF;
		budget.minimum_count = 0xFF;
		budget.maximum_count = 0xFF;
	}
}

void __fastcall c_map_variant__rebuild_quotas_from_hook(s_map_variant *thisptr, void *__formal, s_map_variant *other) // 0x10A6AFC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_map_variant__rebuild_quotas_from_hook@@YIXPAUs_map_variant@@PAX0@Z");
	// `anonymous-namespace'::c_map_variant__rebuild_quotas_from_hook
	// s_map_variant *other;
		// long i;
			// s_variant_quota &budget;
				// long newBudgetIndex;

	for (long i = 0; i < other->placeable_object_quota_count; i++)
	{
		s_variant_quota *quota = &other->object_quotas[i];
		if (quota->definition_index != -1)
		{
			long budget_index = CreateOrGetBudgetForItem(thisptr, quota->definition_index);
			if (budget_index != -1)
			{
				thisptr->object_quotas[budget_index] = *quota;
			}
		}
	}
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

long __fastcall place_object_hook(s_map_variant *thisptr, void *__formal, long tag_index, long creation_type, long map_variant_index, real_point3d const *position, real_vector3d const *forward, real_vector3d const *up, long scenario_object_index, e_object_type object_type, s_map_variant_placement_properties *properties, unsigned short flags) // 0x10A6F800
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?place_object_hook@@YIJPAUs_map_variant@@PAXJJJPBUreal_point3d@@PBUreal_vector3d@@3JW4e_object_type@@PAUs_map_variant_placement_properties@@G@Z");
	// `anonymous-namespace'::place_object_hook
	// unsigned short flags;
	// long object_index;
		// std::vector<void (__cdecl*)(unsigned int)> &<range>$L0;
		// void (**<begin>$L0)(unsigned __int32);
		// void (**<end>$L0)(unsigned __int32);
			// void (*&cb)(unsigned __int32);
	// function call : long (*const)(s_map_variant *, long, long, long, real_point3d const *, real_vector3d const *, real_vector3d const *, long, long, s_map_variant_placement_properties const *, short)
	// function call : void (*)(unsigned __int32)

	if (!tag_try_and_get_and_verify_group('obje', tag_index))
		return -1;
	CreateOrGetBudgetForItem(thisptr, tag_index);
	long object_index = ((long (__thiscall *)(s_map_variant *, long, long, long, real_point3d const *, real_vector3d const *, real_vector3d const *, long, e_object_type, s_map_variant_placement_properties *, unsigned short))0x582110)(thisptr, tag_index, creation_type, map_variant_index, position, forward, up, scenario_object_index, object_type, properties, flags);
	for (auto &cb : s_ItemSpawnedCallbacks)
		cb(object_index);
	Web::Ui::WebForge::OnItemSpawned(object_index);
	return object_index;
}

bool can_place_object_at_hook(long tag_index, real_point3d *position, long player_unit_index) // 0x10A6C710
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?can_place_object_at_hook@@YA_NJPAUreal_point3d@@J@Z");
	// `anonymous-namespace'::can_place_object_at_hook
	// long player_unit_index;
	// s_object_definition *object_definition;
	// bool (*const calculate_sphere_fixed_position)(float, float, long, long, long, real_point3d const *, real_point3d const *, long, real_point3d *, bool);
	// float boundingRadius;
		// s_model_definition *hlmtDef;
			// s_model_object_data const &modelobjectData;
	// function call : void *(*const)(unsigned long, long)
	// function call : void *(*const)(unsigned long, long)
	// function call : bool (*const)(float, float, long, long, long, real_point3d const *, real_point3d const *, long, real_point3d *, bool)
	// function call : s_map_variant *(*const)()

	bool (*const calculate_sphere_fixed_position)(float, float, long, long, long, real_point3d const *, real_point3d const *, long, real_point3d *, bool) = reinterpret_cast<bool (*)(float, float, long, long, long, real_point3d const *, real_point3d const *, long, real_point3d *, bool)>(0x715E90);
	s_object_definition *object_definition = (s_object_definition *)tag_get('obje', tag_index);
	if (!object_definition)
		return false;
	float boundingRadius = object_definition->bounding_radius;
	if (object_definition->model.index != -1)
	{
		s_model_definition *hlmtDef = (s_model_definition *)tag_get('hlmt', object_definition->model.index);
		if (hlmtDef && hlmtDef->model_object_data.count > 0)
		{
			s_model_object_data const &modelobjectData = hlmtDef->model_object_data[0];
			if (modelobjectData.Radius > boundingRadius)
				boundingRadius = modelobjectData.Radius;
		}
	}
	if (boundingRadius < 0.00001f)
		boundingRadius = 1.0f;
	if (boundingRadius < 2.0f)
		calculate_sphere_fixed_position(boundingRadius, boundingRadius, 1, 4, player_unit_index, position, nullptr, -1, position, false);
	return CreateOrGetBudgetForItem(game_engine_get_runtime_map_variant(), tag_index) != -1;
}

float __fastcall light_intensity_function_evaluate(c_function_definition *thisptr, long light_index, float input, float range) // 0x10A6EDB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?light_intensity_function_evaluate@@YIMPAVc_function_definition@@JMM@Z");
	// `anonymous-namespace'::light_intensity_function_evaluate
	// c_function_definition *thisptr;
	// long light_index;
	// float input;
	// float range;
	// static light_intensity_function_evaluate::__l2::s_functionData `light_intensity_function_evaluate'::`2'::functionData; // 0x12458528
	// s_light_datum *light;
	// s_object_data *lightObject;
		// unsigned long lightFlags;
		// s_multiplayer_object_properties *mpProperties;
			// c_function_definition temp_function;
			// Forge::ForgeLightProperties const *lightProperties;
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : s_multiplayer_object_properties *(*const)(unsigned long)
	// function call : void *(*const)(unsigned long, long)

	struct s_functionData
	{
		s_function_definition_internal header;
		c_periodic_function_compact periodic;
	};
	static s_functionData functionData;
	s_light_datum *light = tls_getd().lights->try_and_get(light_index);
	s_object_data *lightObject = object_try_and_get_and_verify_type(light->object_index, -1);
	if (lightObject)
	{
		s_multiplayer_object_properties *mpProperties = object_get_multiplayer(light->object_index);
		unsigned long lightFlags = *(unsigned long *)tag_get('ligh', light->definition_index);
		if ((lightFlags & 0x80000000) && mpProperties)
		{
			::Forge::ForgeLightProperties const *lightProperties = (::Forge::ForgeLightProperties const *)&mpProperties->boundry_width;
			if (lightProperties->Function.Type == 0)
				return 1.0f;
			functionData = {};
			functionData.header.type = 3;
			functionData.header.flags = 4;
			functionData.header.clamp_range_min = lightProperties->Function.Base / 255.0f;
			functionData.header.clamp_range_max = 1.0f;
			functionData.header.data_size = 20;
			functionData.periodic.frequency = lightProperties->Function.Freq / 255.0f * 2.0f;
			functionData.periodic.phase = 0.0f;
			functionData.periodic.amplitude_min = 0.0f;
			functionData.periodic.amplitude_max = 1.0f;
			switch (lightProperties->Function.Type)
			{
			case 1:
				functionData.periodic.function = 2;
				break;
			case 2:
				functionData.periodic.frequency *= 0.2f;
				functionData.periodic.function = 8;
				break;
			}
			c_function_definition temp_function;
			temp_function.m_data.size = 52;
			temp_function.m_data.address = &functionData;
			return temp_function.evaluate_scalar(input, range);
		}
	}
	return thisptr->evaluate_scalar(input, range);
}

void __fastcall light_color_function_evaluate(c_function_definition *thisptr, long light_index, float input, float range, real_rgb_color *color) // 0x10A6EB50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?light_color_function_evaluate@@YIXPAVc_function_definition@@JMMPAUreal_rgb_color@@@Z");
	// `anonymous-namespace'::light_color_function_evaluate
	// real_rgb_color *color;
	// void (*const c_function_definition__evaluate_color)(c_function_definition *, float, float, real_rgb_color *);
	// s_light_datum *light;
	// s_object_data *lightObject;
		// unsigned long lightFlags;
		// s_multiplayer_object_properties *mpProperties;
			// Forge::ForgeLightProperties const *lightProperties;
			// float intensity;
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : s_multiplayer_object_properties *(*const)(unsigned long)
	// function call : void *(*const)(unsigned long, long)

	void (*const c_function_definition__evaluate_color)(c_function_definition *, float, float, real_rgb_color *) = reinterpret_cast<void (*)(c_function_definition *, float, float, real_rgb_color *)>(0x9498D0);
	s_light_datum *light = tls_getd().lights->try_and_get(light_index);
	s_object_data *lightObject = object_try_and_get_and_verify_type(light->object_index, -1);
	if (lightObject)
	{
		s_multiplayer_object_properties *mpProperties = object_get_multiplayer(light->object_index);
		unsigned long lightFlags = *(unsigned long *)tag_get('ligh', light->definition_index);
		if ((lightFlags & 0x80000000) && mpProperties)
		{
			::Forge::ForgeLightProperties const *lightProperties = (::Forge::ForgeLightProperties const *)&mpProperties->boundry_width;
			float intensity = lightProperties->Intensity / 255.0f * 2.0f * 300.0f;
			color->red = lightProperties->ColorR / 255.0f * intensity;
			color->green = lightProperties->ColorG / 255.0f * intensity;
			color->blue = lightProperties->ColorB / 255.0f * intensity;
			return;
		}
	}
	thisptr->evaluate_color(input, range, color);
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

// s_selectionState::s_selectionState() is implicit; 0x10A5E590

// s_selectionState::ChildInfo::ChildInfo() is implicit; 0x10A5EE30

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

// s_selectionState::~s_selectionState() is implicit; 0x10A5EFA0

// s_selectionState::operator=(s_selectionState &&) is implicit; 0x10A5F740

void add_simple_light_callback_hook(long light_index, long user_index, float intensity, c_lights_view *lights_view) // 0x10A6A160
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?add_simple_light_callback_hook@@YAXJJMPAUc_lights_view@@@Z");
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
		// s_multiplayer_object_properties *multiplayer_properties;
			// real_rgb_color color;
			// float percent_spherical;
			// float fov;
			// float angular_smoothness;
			// float distance_diffusion;
			// Forge::ForgeLightProperties const *lightProperties;
			// float maximum_distance;
	// function call : void *(*const)(unsigned long, long)
	// function call : s_multiplayer_object_properties *(*const)(unsigned long)
	// function call : void (*const)(c_lights_view *, real_point3d, real_rgb_color, float, float, real_vector3d, float, float, float)
	// function call : void (*const)(long, long, float, c_lights_view *)

	void (*const add_simple_light_callback)(long, long, float, c_lights_view *) = reinterpret_cast<void (*)(long, long, float, c_lights_view *)>(0xA667F0);
	void (__thiscall *const c_lights_view__update)(c_lights_view *, real_point3d, real_rgb_color, float, float, real_vector3d, float, float, float) = reinterpret_cast<void (__thiscall *)(c_lights_view *, real_point3d, real_rgb_color, float, float, real_vector3d, float, float, float)>(0xA66900);
	s_light_datum *light = tls_getd().lights->try_and_get(light_index);
	char *lightDef = (char *)tag_get('ligh', light->definition_index);
	unsigned long lightFlags = *(unsigned long *)lightDef;
	if (lightFlags & 0x80000000)
	{
		s_multiplayer_object_properties *multiplayer_properties = object_get_multiplayer(light->object_index);
		if (multiplayer_properties)
		{
			::Forge::ForgeLightProperties const *lightProperties = (::Forge::ForgeLightProperties const *)&multiplayer_properties->boundry_width;
			float percent_spherical = *(float *)(lightDef + 0x74);
			float angular_smoothness = lightProperties->Type == ::Forge::ForgeLightProperties::LightType_Point ? 1.0f : 0.0f;
			float fov = lightProperties->FieldOfView / 255.0f * 180.0f * 0.0174533f;
			float maximum_distance = lightProperties->Range / 65535.0f * 50.0f;
			float distance_diffusion = 6.0f;
			real_rgb_color color;
			color.red = intensity * light->color.red, color.green = intensity * light->color.green, color.blue = intensity * light->color.blue;
			c_lights_view__update(lights_view, light->position, color, distance_diffusion, maximum_distance, light->forward, fov, percent_spherical, angular_smoothness);
			return;
		}
	}
	add_simple_light_callback(light_index, user_index, intensity, lights_view);
}

void __fastcall c_map_variant__quantize_hook(s_map_variant *thisptr, void *unused) // 0x10A6AFA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_map_variant__quantize_hook@@YIXPAUs_map_variant@@PAX@Z");
	// the original is empty
	// `anonymous-namespace'::c_map_variant__quantize_hook
	// void *unused;
}

void game_engine_update_hook() // 0x10A6E3C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_engine_update_hook@@YAXXZ");
	// `anonymous-namespace'::game_engine_update_hook
	// procedure flags: nofpo
	// function call : bool (*const)()
	// function call : bool (*const)()

	if (!game_is_multiplayer())
	{
		return;
	}

	::Forge::CForgeMapModifier::Update();

	if (!((bool (*)())0x531d70)())
	{
		::Forge::Volumes::Update();
	}
}

bool game_engine_game_object_has_fallen_too_far_hook(long object_index) // 0x10A6D690
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_engine_game_object_has_fallen_too_far_hook@@YA_NJ@Z");
	// `anonymous-namespace'::game_engine_game_object_has_fallen_too_far_hook
	// long object_index;
	// bool (*const game_engine_game_object_has_fallen_too_far)(long);
	// function call : bool (*const)(long)

	const auto game_engine_game_object_has_fallen_too_far = (bool(*)(long))0x54E9B0;

	if (::Forge::CForgeMapBarriers::KillBarrierDisabled() || ::Forge::CForgeMapBarriers::PushBarrierDisabled())
	{
		return false;
	}

	return game_engine_game_object_has_fallen_too_far(object_index);
}

bool collision_test_object_hook(long object_index, s_object_header *object_header, s_object_data *object, unsigned long test_flags, long object_type_mask, long ignore_object_index_1, long ignore_object_index_2, long ignore_object_index_3) // 0x10A6D0A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?collision_test_object_hook@@YA_NJPAUs_object_header@@PAUs_object_data@@KJJJJ@Z");
	// `anonymous-namespace'::collision_test_object_hook
	// long ignore_object_index_3;
	// long playerIndex;
	// s_forge_globals_definition *forge_globals;
	// bool (*const test_object)(long, s_object_header *, s_object_data *, unsigned long, unsigned long, long, long, long);
	// s_multiplayer_object_properties *mpProperties;
		// bool allowsProjectiles;
		// Forge::ReforgeObjectProperties *reforgeProperties;
	// function call : bool (*const)(long, s_object_header *, s_object_data *, unsigned long, unsigned long, long, long, long)
	// function call : unsigned long (*const)(long)
	// function call : bool (*const)(long, long *, long *)
	// function call : s_multiplayer_object_properties *(*const)(unsigned long)
	// function call : unsigned long (*const)(long)
	// function call : bool (*const)(long, long *, long *)

	bool (*const test_object)(long, s_object_header *, s_object_data *, unsigned long, unsigned long, long, long, long) = reinterpret_cast<bool (*)(long, s_object_header *, s_object_data *, unsigned long, unsigned long, long, long, long)>(0x6D92A0);
	if (!test_object(object_index, object_header, object, test_flags, object_type_mask, ignore_object_index_1, ignore_object_index_2, ignore_object_index_3))
		return false;
	long playerIndex = eldorado::player_mapping_get_player_by_input_user(0);
	s_forge_globals_definition *forge_globals = forge_globals_get_definition();
	if (!forge_globals)
		return true;
	if ((object->definition_index == forge_globals->prematch_camera_object.index || object->definition_index == forge_globals->kill_volume_object.index || object->definition_index == forge_globals->garbage_volume_object.index) && !((bool (*const)(long, long *, long *))0x59A6F0)(playerIndex, nullptr, nullptr))
		return false;
	s_multiplayer_object_properties *mpProperties = object_get_multiplayer(object_index);
	if (mpProperties && ::Forge::Reforge::IsReforgeObject(object_index))
	{
		::Forge::ReforgeObjectProperties *reforgeProperties = (::Forge::ReforgeObjectProperties *)((unsigned char *)mpProperties + 0x14);
		bool allowsProjectiles = (reforgeProperties->Flags & ::Forge::ReforgeObjectProperties::MaterialAllowsProjectiles) != 0;
		if (allowsProjectiles && !((bool (*const)(long, long *, long *))0x59A6F0)(eldorado::player_mapping_get_player_by_input_user(0), nullptr, nullptr))
		{
			if (reforgeProperties->TeamBarrier)
				return !TestBarrierTestProjectile(object_index, ignore_object_index_3);
			else
				return false;
		}
	}
	return true;
}

static void multiplayer_object_submit_boundary_hook(s_multiplayer_object_boundary_geometry_data *boundary, real_argb_color *color, long object_index) // 0x10A6F470
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?multiplayer_object_submit_boundary_hook@@YAXPAUs_multiplayer_object_boundary_geometry_data@@PAUreal_argb_color@@J@Z");
	// `anonymous-namespace'::multiplayer_object_submit_boundary_hook
	// long object_index;
	// void (*const multiplayer_object_submit_boundary)(s_multiplayer_object_boundary_geometry_data *, real_argb_color *, long);
	// s_object_data *object;
	// s_forge_globals_definition *forge_globals;
	// function call : void (*const)(s_multiplayer_object_boundary_geometry_data *, real_argb_color *, long)

	void (__cdecl *const multiplayer_object_submit_boundary)(s_multiplayer_object_boundary_geometry_data *, real_argb_color *, long) = (void(__cdecl *const)(s_multiplayer_object_boundary_geometry_data *, real_argb_color *, long))0xba0fc0;

	s_object_data *object = object_get(object_index);
	if (!object)
	{
		return;
	}

	s_forge_globals_definition *forge_globals = forge_globals_get_definition();
	if (object->definition_index == forge_globals->garbage_volume_object.index
		|| object->definition_index == forge_globals->kill_volume_object.index)
	{
		return;
	}

	multiplayer_object_submit_boundary(boundary, color, object_index);
}

void __fastcall c_multiplayer_candy_monitor_manager__monitor_object_hook(c_multiplayer_candy_monitor_manager *thisptr, void *__formal, long map_variant_index, long object_index) // 0x10A6B8B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_multiplayer_candy_monitor_manager__monitor_object_hook@@YIXPAUc_multiplayer_candy_monitor_manager@@PAXJJ@Z");
	// `anonymous-namespace'::c_multiplayer_candy_monitor_manager__monitor_object_hook
	// long object_index;
	// void (*const c_multiplayer_candy_monitor_manager__monitor_object)(c_multiplayer_candy_monitor_manager *, long, long);
	// function call : void (*const)(c_multiplayer_candy_monitor_manager *, long, long)

	const auto c_multiplayer_candy_monitor_manager__monitor_object = (void(__thiscall *)(c_multiplayer_candy_monitor_manager *, long, long))0x590600;

	if (!::Forge::Reforge::IsReforgeObject(object_index) && !::Forge::ObjectIsForgeScenery(object_index))
	{
		c_multiplayer_candy_monitor_manager__monitor_object(thisptr, map_variant_index, object_index);
	}
}

void shield_impact_bloom_intensity_hook(long id, long count, float *data) // 0x10A6FDE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?shield_impact_bloom_intensity_hook@@YAXJJPAM@Z");
	// `anonymous-namespace'::shield_impact_bloom_intensity_hook
	// float *data;
	// void (*const rasterizer_set_pixel_shader_constant)(__int32, __int32, float *);
		// float intensity;
	// function call : void (*const)(__int32, __int32, float *)

	void (__cdecl *const rasterizer_set_pixel_shader_constant)(__int32, __int32, float *) = (void(__cdecl *const)(__int32, __int32, float *))0xa66270;

	if (::Forge::CForgeCameraFx::IsActive() && abs(::Forge::CForgeCameraFx::GetBloomIntensity()) >= 0.00001f)
	{
		float intensity = ::Forge::CForgeCameraFx::GetBloomIntensity();

		data[12] = data[12] * intensity;
		data[13] = data[13] * intensity;
		data[14] = data[14] * intensity;
		data[15] = data[15] * intensity;
	}

	rasterizer_set_pixel_shader_constant(id, count, data);
}

void game_sound_update_acoustics_hook(float dt) // 0x10A6E440
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_sound_update_acoustics_hook@@YAXM@Z");
	// `anonymous-namespace'::game_sound_update_acoustics_hook
	// float dt;
	// void (*const game_sound_update_acoustics)(float);
	// function call : void (*const)(float)

	const auto game_sound_update_acoustics = (void(*)(float))0x5DAB20;

	if (!::Forge::CForgeSkies::IsActive())
	{
		game_sound_update_acoustics(dt);
	}
}

void object_placement_create_active_zone_set_skies_hook(long scenario_index, unsigned long bsp_mask) // 0x10A6F5D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?object_placement_create_active_zone_set_skies_hook@@YAXJK@Z");
	// `anonymous-namespace'::object_placement_create_active_zone_set_skies_hook
	// unsigned long bsp_mask;
	// void (*const object_placement_create_active_zone_set_skies)(long, unsigned long);
	// function call : bool (*const)()
	// function call : void (*const)(long, unsigned long)

	const auto object_placement_create_active_zone_set_skies = (void(*)(long, unsigned long))0xB594C0;

	if (game_is_multiplayer() && ::Forge::CForgeSkies::IsActive())
	{
		return;
	}

	object_placement_create_active_zone_set_skies(scenario_index, bsp_mask);
}

bool IgnoreRigidBodyNode(unsigned __int32 objectIndex, __int32 nodeIndex) // 0x10A66940
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?IgnoreRigidBodyNode@@YA_NIH@Z");
	// `anonymous-namespace'::IgnoreRigidBodyNode
	// __int32 nodeIndex;

	return monitorState.HeldObjectIndex != -1
		&& monitorState.HeldObjectIndex == objectIndex
		&& monitorState.HeldObjectRootNode != -1
		&& nodeIndex != monitorState.HeldObjectRootNode;
}

void __fastcall rigid_body_hack_hook(c_runtime_node_to_physics_model_rigid_body_index_mapping *thisptr, void *__formal, long object_index, bool force) // 0x10A6FA00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?rigid_body_hack_hook@@YIXPAUc_runtime_node_to_physics_model_rigid_body_index_mapping@@PAXJ_N@Z");
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
		// long i;
			// long model_region_index;
			// c_runtime_node_to_physics_model_rigid_body_index_mapping::s_mapping *mapping;
			// long model_permutation_index;
			// s_physics_model_rigid_body *rigid_body;
	// function call : void *(*const)(unsigned long, long)
	// function call : void *(*const)(unsigned long, long)
	// function call : void *(*const)(unsigned long, long)
	// function call : bool (*const)(long, long, long, long, long *, long *)

	bool (*const calculate_model_region_and_permutation_from_physics_model_region_and_permutation)(long, long, long, long, long *, long *) = reinterpret_cast<bool (*)(long, long, long, long, long *, long *)>(0x715300);
	s_object_data *object = object_get(object_index);
	if (!object)
		return;
	s_object_definition *object_definition = (s_object_definition *)tag_get('obje', object->definition_index);
	if (!object_definition || object_definition->model.index == -1)
		return;
	s_model_definition *model = (s_model_definition *)tag_get('hlmt', object_definition->model.index);
	if (!model || model->physics_model.index == -1)
		return;
	s_physics_model_definition *physics_model = (s_physics_model_definition *)tag_get('phmo', model->physics_model.index);
	if (!physics_model)
		return;
	thisptr->m_node_count = physics_model->nodes.count;
	for (long i = 0; i < thisptr->m_node_count; i++)
		thisptr->m_node_to_rigid_body_mapping[i].rigid_body_count = 0;
	thisptr->m_root_rigid_body_mapping.rigid_body_count = 0;
	for (long rigid_body_index = 0; rigid_body_index < physics_model->rigid_bodies.count; rigid_body_index++)
	{
		s_physics_model_rigid_body *rigid_body = &physics_model->rigid_bodies[rigid_body_index];
		if (IgnoreRigidBodyNode(object_index, rigid_body->node))
			continue;
		c_runtime_node_to_physics_model_rigid_body_index_mapping::s_mapping *mapping;
		if (rigid_body->node == -1)
			mapping = &thisptr->m_root_rigid_body_mapping;
		else
			mapping = &thisptr->m_node_to_rigid_body_mapping[rigid_body->node];
		long model_region_index;
		long model_permutation_index;
		if (force || (calculate_model_region_and_permutation_from_physics_model_region_and_permutation(object_index, object_definition->model.index, rigid_body->region, rigid_body->permutation, &model_region_index, &model_permutation_index), model_region_index != -1) && model_permutation_index != -1)
			mapping->rigid_body_indices[mapping->rigid_body_count++] = (char)rigid_body_index;
	}
}

long havok_cull_objects_filter_rigid_body_hook(hkpEntity *entity) // 0x10A6E6D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?havok_cull_objects_filter_rigid_body_hook@@YAJPAUhkpEntity@@@Z");
	// `anonymous-namespace'::havok_cull_objects_filter_rigid_body_hook
	// hkpEntity *entity;
	// long havok_component_index;
		// c_havok_component *havok_component;
		// long object_index;
	// function call : long (*const)(hkpEntity const *)

	long havok_component_index = havok_entity_get_havok_component_index(entity);
	if (havok_component_index != -1)
	{
		c_havok_component *havok_component = havok_component_get(havok_component_index);
		long object_index = havok_component->get_object_index();

		if (::Forge::Reforge::IsReforgeObject(object_index) || ::Forge::ObjectIsForgeScenery(object_index))
		{
			havok_component_index = -1;
		}
	}

	return havok_component_index;
}

void __fastcall c_havok_component__connect_to_havok_world_hook(c_havok_component *thisptr, void *unused) // 0x10A6A770
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_havok_component__connect_to_havok_world_hook@@YIXPAVc_havok_component@@PAX@Z");
	// `anonymous-namespace'::c_havok_component__connect_to_havok_world_hook
	// void *unused;
	// void (*const c_havok_component__connect_to_havok_world)(c_havok_component *);
	// bool shouldBeFixed;
	// long object_index;
		// long rigidBodyCount;
			// __int32 i;
				// unsigned char *rigidBody;
	// function call : void (*const)(c_havok_component *)

	const auto c_havok_component__connect_to_havok_world = (void(__thiscall *)(c_havok_component *))0x5e6a50;

	long object_index = thisptr->get_object_index();
	bool shouldBeFixed = ::Forge::Reforge::IsReforgeObject(object_index) || ::Forge::ObjectIsForgeScenery(object_index);
	if (object_index != -1 && shouldBeFixed)
	{
		long rigidBodyCount = thisptr->m_rigid_bodies.m_size;

		for (__int32 i = 0; i < rigidBodyCount; i++)
		{
			unsigned char *rigidBody = (unsigned char *)thisptr->m_rigid_bodies.m_data[i].rigid_body;

			*(rigidBody + 0xA8) = 7;
		}
	}

	c_havok_component__connect_to_havok_world(thisptr);
}

void game_engine_garbage_collect_for_round_switch_object_delete_hook(long object_index) // 0x10A6D720
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_engine_garbage_collect_for_round_switch_object_delete_hook@@YAXJ@Z");
	// `anonymous-namespace'::game_engine_garbage_collect_for_round_switch_object_delete_hook
	// long object_index;
	// s_object_data *object;
	// void (*const object_delete_immediately)(unsigned __int32);
	// s_forge_globals_definition *forge_globals;
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void (*const)(unsigned __int32)

	void (*const object_delete_immediately)(unsigned __int32) = reinterpret_cast<void (*)(unsigned __int32)>(0xB2CF40);
	s_object_data *object = object_try_and_get_and_verify_type(object_index, -1);
	if (!object)
		return;
	s_forge_globals_definition *forge_globals = forge_globals_get_definition();
	if (object->definition_index == forge_globals->map_modifier_object.index || object->definition_index == forge_globals->garbage_volume_object.index || object->definition_index == forge_globals->kill_volume_object.index)
		return;
	if (::Forge::Reforge::IsReforgeObject(object_index))
		return;
	if (::Forge::ObjectIsForgeScenery(object_index))
		return;
	object_delete_immediately(object_index);
}

s_multiplayer_object_properties *game_engine_find_available_spawn_location_objects_filter_hook(long object_index) // 0x10A6D5B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?game_engine_find_available_spawn_location_objects_filter_hook@@YAPAUs_multiplayer_object_properties@@J@Z");
	// `anonymous-namespace'::game_engine_find_available_spawn_location_objects_filter_hook
	// long object_index;
	// s_object_data *object;
	// s_forge_globals_definition *forge_globals;
	// function call : s_multiplayer_object_properties *(*const)(unsigned long)

	s_forge_globals_definition *forge_globals = forge_globals_get_definition();
	s_object_data *object = object_get(object_index);

	if (object
		&& (1 << (char)object->object_identifier.type)
		&& object->definition_index != forge_globals->map_modifier_object.index
		&& object->definition_index != forge_globals->prematch_camera_object.index)
	{
		return object_get_multiplayer(object_index);
	}

	return nullptr;
}

bool __fastcall c_havok_contact_point__is_climbable_surface_hook(c_havok_contact_point *contact_point) // 0x10A6A8A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_havok_contact_point__is_climbable_surface_hook@@YI_NPAUc_havok_contact_point@@@Z");
	// `anonymous-namespace'::c_havok_contact_point__is_climbable_surface_hook
	// c_havok_contact_point *contact_point;
	// s_multiplayer_object_properties *multiplayer_properties;
	// long object_index;
	// unsigned long surface_flags;
		// Forge::ReforgeObjectProperties *reforge_properties;
	// function call : s_multiplayer_object_properties *(*const)(unsigned long)

	long object_index = *(long *)offset_pointer(contact_point, 20);
	unsigned long surface_flags = *(unsigned long *)offset_pointer(contact_point, 64);
	s_multiplayer_object_properties *multiplayer_properties = object_get_multiplayer(object_index);

	if (multiplayer_properties && ::Forge::Reforge::IsReforgeObject(object_index))
	{
		::Forge::ReforgeObjectProperties *reforge_properties = (::Forge::ReforgeObjectProperties *)&multiplayer_properties->boundry_width;

		if (reforge_properties->Flags & ::Forge::ReforgeObjectProperties::MaterialIsClimbable)
			return true;
	}

	return (surface_flags & 4) != 0;
}

void map_variant_register_object_hook(long object_index, long map_variant_index, char registration_type) // 0x10A6F150
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?map_variant_register_object_hook@@YAXJJD@Z");
	// `anonymous-namespace'::map_variant_register_object_hook
	// char registration_type;
	// void (*const map_variant_register_object)(long, long, char);
	// function call : s_map_variant *(*const)()
	// function call : void (*const)(long, long, char)

	void (*const map_variant_register_object)(long, long, char) = reinterpret_cast<void (*)(long, long, char)>(0x584790);
	CreateOrGetBudgetForItem(game_engine_get_runtime_map_variant(), object_get(object_index)->definition_index);
	map_variant_register_object(object_index, map_variant_index, registration_type);
}

void __fastcall c_sandbox_engine__update_local_player_hook(c_sandbox_engine *thisptr, void *__formal, long player_index) // 0x10A6C650
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_sandbox_engine__update_local_player_hook@@YIXPAUc_sandbox_engine@@PAXJ@Z");
	// `anonymous-namespace'::c_sandbox_engine__update_local_player_hook
	// long player_index;
	// void (*const c_sandbox_engine__update_local_player)(c_sandbox_engine *, long);
	// function call : long (*const)(long)
	// function call : void (*const)(c_sandbox_engine *, long)

	void (__thiscall *const c_sandbox_engine__update_local_player)(c_sandbox_engine *, long) = reinterpret_cast<void (__thiscall *)(c_sandbox_engine *, long)>(0x59F0E0);
	if (c_gui_screen_manager::get()->input_should_be_suppressed(eldorado::player_mapping_get_input_user(player_index)))
	{
		return;
	}

	c_sandbox_engine__update_local_player(thisptr, player_index);
}

long __fastcall c_map_variant__create_object_hook(s_map_variant *thisptr, void *__formal, long object_definition_index, long creation_type, long map_variant_index, real_point3d *position, real_vector3d *forward, real_vector3d *up, long scenario_datum_index, long object_type, s_map_variant_placement_properties *variant_properties, unsigned short object_placement_flags) // 0x10A6ABD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_map_variant__create_object_hook@@YIJPAUs_map_variant@@PAXJJJPAUreal_point3d@@PAUreal_vector3d@@3JJPAUs_map_variant_placement_properties@@G@Z");
	// `anonymous-namespace'::c_map_variant__create_object_hook
	// unsigned short object_placement_flags;
	// long (*const c_map_variant__create_object)(s_map_variant *, void *, long, long, long, real_point3d *, real_vector3d *, real_vector3d *, long, long, s_map_variant_placement_properties *, unsigned short);
	// function call : long (*const)(s_map_variant *, void *, long, long, long, real_point3d *, real_vector3d *, real_vector3d *, long, long, s_map_variant_placement_properties *, unsigned short)

	long (__fastcall *const c_map_variant__create_object)(s_map_variant *, void *, long, long, long, real_point3d *, real_vector3d *, real_vector3d *, long, long, s_map_variant_placement_properties *, unsigned short) = (long(__fastcall *const)(s_map_variant *, void *, long, long, long, real_point3d *, real_vector3d *, real_vector3d *, long, long, s_map_variant_placement_properties *, unsigned short))0x582110;

	if (!tag_try_and_get_and_verify_group(0x6F626A65, object_definition_index))
	{
		return -1;
	}

	return c_map_variant__create_object(thisptr, nullptr, object_definition_index, creation_type, map_variant_index, position, forward, up, scenario_datum_index, object_type, variant_properties, object_placement_flags);
}

void __fastcall c_map_variant__register_scenario_object_hook(s_map_variant *thisptr, void *__formal, long object_index, bool edited) // 0x10A6B220
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_map_variant__register_scenario_object_hook@@YIXPAUs_map_variant@@PAXJ_N@Z");
	// `anonymous-namespace'::c_map_variant__register_scenario_object_hook
	// bool edited;
	// void (*const c_map_variant__register_scenario_object)(s_map_variant *, long, bool);
	// long object_type;
	// function call : void (*const)(s_map_variant *, long, bool)

	long object_type = object_get_type(object_index);

	if (thisptr->object_type_start_index[object_type] == -1)
	{
		return;
	}

	const auto c_map_variant__register_scenario_object = (void(__thiscall *)(s_map_variant *, long, bool))0x585890;

	c_map_variant__register_scenario_object(thisptr, object_index, edited);
}

bool __fastcall c_map_variant__update_scenario_object_properties_hook(s_map_variant *thisptr, void *__formal, long object_index) // 0x10A6B810
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_map_variant__update_scenario_object_properties_hook@@YI_NPAUs_map_variant@@PAXJ@Z");
	// `anonymous-namespace'::c_map_variant__update_scenario_object_properties_hook
	// long object_index;
	// bool (*const c_map_variant__update_scenario_object_properties)(s_map_variant *, long);
	// long object_type;
	// function call : bool (*const)(s_map_variant *, long)

	long object_type = object_get_type(object_index);

	if (thisptr->object_type_start_index[object_type] == -1)
	{
		return false;
	}

	const auto c_map_variant__update_scenario_object_properties = (bool(__thiscall *)(s_map_variant *, long))0x586C20;

	return c_map_variant__update_scenario_object_properties(thisptr, object_index);
}

long __fastcall c_map_variant__get_scenario_placement_map_variant_index_hook(s_map_variant *thisptr, void *__formal, long object_type, long scenario_datum_index) // 0x10A6ADE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_map_variant__get_scenario_placement_map_variant_index_hook@@YIJPAUs_map_variant@@PAXJJ@Z");
	// `anonymous-namespace'::c_map_variant__get_scenario_placement_map_variant_index_hook
	// long scenario_datum_index;

	if (thisptr->object_type_start_index[object_type] != -1)
	{
		return thisptr->object_type_start_index[object_type] + scenario_datum_index;
	}

	return -1;
}

bool c_candy_spawner__spawn_object__new_from_scenario_object_hook(long object_type, long scenario_datum_index, void *scenario_object, s_tag_block *palette_block, char create_at_rest, char flags, s_object_placement_data *placement_data) // 0x10A6A6B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_candy_spawner__spawn_object__new_from_scenario_object_hook@@YA_NJJPAXPAUs_tag_block@@DDPAUs_object_placement_data@@@Z");
	// `anonymous-namespace'::c_candy_spawner__spawn_object__new_from_scenario_object_hook
	// s_object_placement_data *placement_data;
	// bool (*const object_placement_data_new_from_scenario_object)(long, long, void *, s_tag_block *, char, char, s_object_placement_data *);
	// function call : bool (*const)(long, long, void *, s_tag_block *, char, char, s_object_placement_data *)

	#line 3411 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\Forge.cpp"
		assert(scenario_object);
		#line 3419 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\Forge.cpp"
	if (!scenario_object)
	{
		return false;
	}

	bool (*const object_placement_data_new_from_scenario_object)(long, long, void *, s_tag_block *, char, char, s_object_placement_data *) = reinterpret_cast<bool (*)(long, long, void *, s_tag_block *, char, char, s_object_placement_data *)>(0xB596C0);
	return object_placement_data_new_from_scenario_object(object_type, scenario_datum_index, scenario_object, palette_block, create_at_rest, flags, placement_data);
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

/* ---------- explicit instantiations */
template short & Pointer::Read<short>() const;

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { float const HELDOBJECT_DISTANCE_MIN = 0.10000000149011612f; }
namespace hades_file_local { float const HELDOBJECT_DISTANCE_CHANGE_MULTIPLIER = 0.10000000149011612f; }
namespace hades_file_local { float const MONITOR_MOVEMENT_SPEEDS[7] = { 0.0010000000474974513f, 0.05000000074505806f, 0.25f, 1.0f, 2.0f, 4.0f, 8.0f }; }
namespace hades_file_local { std::vector<void (__cdecl*)(unsigned int)> s_ItemSpawnedCallbacks; }
namespace hades_file_local { namespace hades_file_local_Forge { real_vector3d global_zero3d; } }
namespace hades_file_local { s_monitorState monitorState; }
namespace hades_file_local { wchar_t const *MONITOR_MOVEMENT_SPEED_NAMES[7] = { L"0.001 (Z-Fight Fixer)", L"Slower", L"Slow", L"Normal", L"Fast", L"Faster", L"Fastest" }; }
