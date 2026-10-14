/* ---------- headers */

#include "hades/hades.h"

#include "Blam/BlamInput.hpp"
#include "Blam/cache/cache_files.hpp"
#include "Blam/camera/observer.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_globals.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/geometry/geometry_definitions.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/items/equipment_definitions.hpp"
#include "Blam/math/color_definitions.hpp"
#include "Blam/math/integer_math_definitions.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/models/model_definitions.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/objects/object_definitions.hpp"
#include "Blam/objects/object_types.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/physics/collision_bsp.hpp"
#include "Blam/physics/collision_model.hpp"
#include "Blam/physics/collision_test.hpp"
#include "Blam/physics/havok_types.hpp"
#include "Blam/physics/havok_utilities.hpp"
#include "Blam/physics/physics_model.hpp"
#include "Blam/rasterizer/draw_string.hpp"
#include "Blam/rasterizer/rasterizer_d3d_allocations.hpp"
#include "Blam/rasterizer/rasterizer_geometry.hpp"
#include "Blam/render/camera_fx_settings.hpp"
#include "Blam/render/render_model.hpp"
#include "Blam/render/views/render_player_view.hpp"
#include "Blam/scenario/scenario.hpp"
#include "Blam/scenario/scenario_definitions.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/structures/structure_bsp_definitions.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_block_index.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "Blam/units/units.hpp"
#include "Blam/visibility/visibility.hpp"
#include "Blam/visibility/visibility_items.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Console/Console.hpp"
#include "Debug/DebugDraw.hpp"
#include "Forge/Magnets.hpp"
#include "Modules/ModuleDebug.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Patches/Core.hpp"
#include "Pointer.hpp"
#include "ThirdParty/rapidjson/document.h"
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
#include <memory>
#include <mutex>
#include <ostream>
#include <ratio>
#include <sstream>
#include <stdexcept>
#include <stop_token>
#include <streambuf>
#include <string>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>
#include "Objects/ObjectMessaging.hpp"

#include "Blam/Cache/StringIdCache.hpp"  // hades: added for 0x108CD2F0

/* ---------- forward declarations */

class CDebugDraw;
struct begin;
struct c_font_cache_mt_safe;
struct c_player_view;
struct c_rasterizer_draw_string;
struct collision_bsp;
struct collision_edge;
struct collision_model_definition;
struct collision_model_instance;
struct end;
struct hkpCapsuleShape;
struct hkpShape;
struct model_definition;
struct real_argb_color;
struct real_euler_angles3d;
struct real_matrix4x3;
struct real_point3d;
struct real_rectangle3d;
struct real_vector3d;
struct s_cluster_reference;
struct s_collision_model_bsp_iterator;
struct s_collision_result;
struct s_damage_data;
struct s_damage_effect_definition;
struct s_geometry_material;
struct s_global_material_definition;
struct s_large_collision_bsp;
struct s_large_collision_edge;
struct s_model_definition;
struct s_model_permutation;
struct s_model_region;
struct s_object_data;
struct s_object_definition;
struct s_object_marker;
struct s_observer_result;
struct s_physics_model_instance;
struct s_physics_model_permutation;
struct s_physics_model_region;
struct s_physics_model_rigid_body;
struct s_render_model;
struct s_render_model_marker_group;
struct s_scenario;
struct s_scenario_structure_bsp;
struct s_scenario_trigger_volume;
struct s_structure_bsp_resources;
struct s_structure_collision_material;
struct s_structure_instanced_geometry_definition;
struct s_structure_instanced_geometry_instance;
struct s_unit_data;
struct s_visible_items;
struct s_visible_object_hierarchy;
struct short_rectangle2d;
namespace Modules
{
	class ModuleDebug;
}
namespace hades_file_local
{
	class CRenderDebugCollisionTest;
}
using namespace hades_file_local;

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;
namespace Objects {}
using namespace ::Objects;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace HavokMemory {}
	using namespace Patches::HavokMemory;
	namespace Core {}
	using namespace Patches::Core;
	namespace Debug {}
	using namespace Patches::Debug;
}

namespace Console {}
using namespace ::Console;
namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Cache {}
	using namespace Blam::Cache;
}

/* ---------- constants */

/* ---------- definitions */

namespace hades_file_local
{
	class CRenderDebugCollisionTest
	{
	public:
		static void Update();
		static void UpdateInternal();
		static void Render();
		static std::string GetHitDescription(s_collision_result const &);
		static std::string GetFriendlyTagName(long);
		static void ResetForNewMap();
	private:
		static bool m_collisionResultValid;
		static s_collision_result m_collisionResult;
		static std::mutex m_mutex;
	};
	static_assert(sizeof(CRenderDebugCollisionTest) == 1, "Invalid CRenderDebugCollisionTest size");
}
using namespace hades_file_local;
typedef long long long64;

/* ---------- prototypes */

extern void render_debug_physics_shape(hkpShape const *shape, real_matrix4x3 const *matrix, real_argb_color const *color);  // hades: added for 0x108CCC50

extern s_object_data *(*const object_try_and_get_and_verify_type)(unsigned long, c_enum<e_object_type, long>);  // hades: added for 0x108C95C0

extern void *(*const tag_get)(unsigned long, long);  // hades: added for 0x108CB5A0

extern real_point3d *point_from_line3d(real_point3d const *origin, real_vector3d const *vector, float t, real_point3d *result);  // hades: added for 0x108C9A50

extern float distance_squared3d(real_point3d const *p1, real_point3d const *p2);  // hades: added for 0x108CC120

extern s_scenario_structure_bsp *(*const global_structure_bsp_get)(long);  // hades: added for 0x108C7C00
extern real_euler_angles3d *euler_angles3d_from_vectors3d(real_euler_angles3d *angles, real_vector3d const *forward, real_vector3d const *up);  // hades: added for 0x108C7FA0
extern float point3d_distance(real_point3d const *pA, real_point3d const *pB);  // hades: added for 0x108C7FA0

#include "Debug/DebugTrace.hpp"  // hades: added for 0x108CBEB0
namespace Patches { namespace HavokMemory { extern void RenderDebug(); } }  // hades: added for 0x108CBEB0

extern void render_debug_visibility();  // hades: added for 0x108C9370

namespace Patches
{
	namespace Debug
	{
		extern void OnMapLoaded(char const *mapPath);
		extern void ApplyAll();
		extern void Tick();
		extern void RenderPlayerView();
	}
}

void DisplayClusters();
void render_d3d_resource_tracker();
void render_debug_physics_model(s_physics_model_instance const *instance, real_argb_color const *color);
void render_debug_collision_edge(collision_bsp const *bsp, long index, real_matrix4x3 const *matrix, long color);
void render_debug_large_collision_edge(s_large_collision_bsp const *bsp, long index, real_matrix4x3 const *matrix, long color);
void render_debug_collision_bsp(collision_bsp const *bsp, real_matrix4x3 const *matrix, unsigned long color);
void render_debug_large_collision_bsp(s_large_collision_bsp const *bsp, real_matrix4x3 const *matrix, unsigned long color);
void render_debug_collision_model(collision_model_instance const *instance);
void render_debug_object_markers(long object_index);
void render_debug_object(long object_index);
void render_debug_objects();
void render_debug_frame_render();
void render_debug_damage_submit(s_damage_data const *data, float radius);
short area_of_effect_cause_damage_objects_in_sphere_hook(long flags, long object_mask, s_cluster_reference *cluster, real_point3d const *center, float radius, long *objects, short max_objects);
void render_debug_trigger_volume(s_scenario_trigger_volume *volume, long color);
void render_debug_trigger_volumes();
void render_debug_structure_bsp(long bsp_index);
void render_debug_structure();
void draw_assassination_capsule(char const *key, hkpCapsuleShape const *shape, real_matrix4x3 const *transform, long color);
bool havok_world_shape_collides_hook_initiator(hkpShape const *shape, long unknown, real_matrix4x3 const *transform, long havok_group);
bool havok_world_shape_collides_hook_target(hkpShape const *shape, long unknown, real_matrix4x3 const *transform, long havok_group);
bool assassination_sync_action_point_on_slope_or_falls_hook(long object_index, float height_standing, float physics_radius, real_point3d const *action_point, bool allow_success, float *out_slope_offset);

/* ---------- globals */

extern long (*const global_structure_bsp_first_active_index_get)(); // 0x11248ACC
extern long (*const global_structure_bsp_next_active_index_get)(long); // 0x11248AD0
real_point3d *matrix4x3_transform_point(real_matrix4x3 const *matrix, real_point3d const *point, real_point3d *result);  // hades: added for 0x108CB2E0
char const *tag_get_name(long tag_index);  // hades: added for 0x108C7E20
char const *tag_to_string(unsigned long tag, char *dest, long dest_length);  // hades: added for 0x108C7E20

/* ---------- private variables */

bool CRenderDebugCollisionTest::m_collisionResultValid; // 0x124082B4
s_collision_result CRenderDebugCollisionTest::m_collisionResult; // 0x124082B8
std::mutex CRenderDebugCollisionTest::m_mutex; // 0x12408280
namespace hades_file_local
{
	extern long assassination_capsule_counter; // 0x12408314
}
using namespace hades_file_local;
/* ---------- public code */

namespace Patches
{
	namespace Debug
	{
		void OnMapLoaded(char const *mapPath) // 0x108C8D00
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OnMapLoaded@Debug@Patches@@YAXPBD@Z");
			// char const *mapPath;

			CRenderDebugCollisionTest::ResetForNewMap();
			Modules::ModuleDebug::Instance().VarCollisionTest->ValueInt = 0;
			Modules::ModuleDebug::Instance().VarCollisionTest->ValueString = '0';
			Modules::ModuleDebug::Instance().VarCollisionModels->ValueInt = 0;
			Modules::ModuleDebug::Instance().VarCollisionModels->ValueString = '0';
			Modules::ModuleDebug::Instance().VarPhysicsModels->ValueInt = 0;
			Modules::ModuleDebug::Instance().VarPhysicsModels->ValueString = '0';
			Modules::ModuleDebug::Instance().VarStructureCollision->ValueInt = 0;
			Modules::ModuleDebug::Instance().VarStructureCollision->ValueString = '0';
			Modules::ModuleDebug::Instance().VarClusters->ValueInt = 0;
			Modules::ModuleDebug::Instance().VarClusters->ValueString = '0';
			Modules::ModuleDebug::Instance().VarMarkerGroups->ValueInt = 0;
			Modules::ModuleDebug::Instance().VarMarkerGroups->ValueString = '0';
			Modules::ModuleDebug::Instance().VarDamageAoe->ValueInt = 0;
			Modules::ModuleDebug::Instance().VarDamageAoe->ValueString = '0';
			Modules::ModuleDebug::Instance().VarTriggerVolumes->ValueInt = 0;
			Modules::ModuleDebug::Instance().VarTriggerVolumes->ValueString = '0';
			Modules::ModuleDebug::Instance().VarVisibility->ValueInt = 0;
			Modules::ModuleDebug::Instance().VarVisibility->ValueString = '0';
			Modules::ModuleDebug::Instance().VarAcrophobia->ValueInt = 0;
			Modules::ModuleDebug::Instance().VarAcrophobia->ValueString = '0';
			Modules::ModuleDebug::Instance().VarPlayerDamageDisabled->ValueInt = 0;
			Modules::ModuleDebug::Instance().VarPlayerDamageDisabled->ValueString = '0';
			Modules::ModuleDebug::Instance().VarMapBarriersDisabled->ValueInt = 0;
			Modules::ModuleDebug::Instance().VarMapBarriersDisabled->ValueString = '0';
			Modules::ModuleDebug::Instance().VarSoundDebug->ValueInt = 0;
			Modules::ModuleDebug::Instance().VarSoundDebug->ValueString = '0';
			Modules::ModuleDebug::Instance().VarLoopingSoundDebug->ValueInt = 0;
			Modules::ModuleDebug::Instance().VarLoopingSoundDebug->ValueString = '0';
			Modules::ModuleDebug::Instance().VarHideForgeObjects->ValueInt = 0;
			Modules::ModuleDebug::Instance().VarHideForgeObjects->ValueString = '0';
		}

		void ApplyAll() // 0x108C76E0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAll@Debug@Patches@@YAXXZ");
			// procedure flags: nofpo

			Hook(0x2047E6, render_debug_frame_render, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x74E2D9, area_of_effect_cause_damage_objects_in_sphere_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x7A9381, havok_world_shape_collides_hook_initiator, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x7A9399, havok_world_shape_collides_hook_target, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x7A93D0, assassination_sync_action_point_on_slope_or_falls_hook).Apply();
			Patches::Core::OnMapLoaded(::Patches::Debug::OnMapLoaded);
		}

		void Tick() // 0x108C9470
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Tick@Debug@Patches@@YAXXZ");
			// procedure flags: nofpo
			// function call : bool (*const)()

			if (((bool(*const)())0x5314b0)())
			{
				CRenderDebugCollisionTest::Update();
			}
		}

		void RenderPlayerView() // 0x108C9370
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?RenderPlayerView@Debug@Patches@@YAXXZ");
			// procedure flags: nofpo

			DisplayClusters();
			render_debug_objects();
			render_debug_trigger_volumes();
			render_debug_visibility();
			render_debug_structure();
		}
	}
}

/* ---------- private code */

_inline void CRenderDebugCollisionTest::Update() // 0x108C94D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Update@CRenderDebugCollisionTest@hades_file_local@@SAXXZ");
	// `anonymous-namespace'::CRenderDebugCollisionTest::Update
	// procedure flags: nofpo

	if (!Modules::ModuleDebug::Instance().VarCollisionTest->ValueInt)
	{
		m_collisionResultValid = false;
	}
	else
	{
		Objects::CObjectMessaging::EnqueueAction(UpdateInternal);
	}
}

_inline void CRenderDebugCollisionTest::UpdateInternal() // 0x108C95C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?UpdateInternal@CRenderDebugCollisionTest@hades_file_local@@SAXXZ");
	// `anonymous-namespace'::CRenderDebugCollisionTest::UpdateInternal
	// procedure flags: nofpo
	// static ...; // 0x108C98B3
	// static ...; // 0x108C98AC
	// static ...; // 0x108C98A5
	// static ...; // 0x108C98A0
	// static ...; // 0x108C9870
	// static ...; // 0x108C9868
	// s_unit_data *unit;
	// real_point3d cameraPos;
	// real_vector3d vector;
	// s_collision_result result;
	// long unitIndex;
		// std::scoped_lock<std::mutex> lock;
	// function call : unsigned long (*const)(long)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void (*const)(long, real_point3d *)
	// function call : bool (*const)(unsigned long, unsigned long, real_point3d const &, real_vector3d const &, long, long, s_collision_result *)

	static unsigned long (*const player_mapping_get_unit_by_output_user)(long) = reinterpret_cast<unsigned long (*)(long)>(0x589CC0);
	static void (*const unit_get_camera_position)(long, real_point3d *) = reinterpret_cast<void (*)(long, real_point3d *)>(0xB439D0);
	static bool (*const collision_test_vector)(unsigned long, unsigned long, real_point3d const &, real_vector3d const &, long, long, s_collision_result *) = reinterpret_cast<bool (*)(unsigned long, unsigned long, real_point3d const &, real_vector3d const &, long, long, s_collision_result *)>(0x6D7160);
	long unitIndex = player_mapping_get_unit_by_output_user(0);
	s_unit_data *unit = (s_unit_data *)object_try_and_get_and_verify_type(unitIndex, 1);
	if (!unit)
		return;
	real_point3d cameraPos;
	unit_get_camera_position(unitIndex, &cameraPos);
	real_vector3d vector = 2000.0f * unit->aiming_vector;
	s_collision_result result = {};
	m_collisionResultValid = collision_test_vector(0x100009, 0xFFFFFFFF, cameraPos, vector, unitIndex, -1, &result);
	{
		std::scoped_lock<std::mutex> lock(m_mutex);
		m_collisionResult = result;
	}
	if (m_collisionResultValid && Blam::Input::GetKeyTicks(Blam::Input::eKeyCodeInsert, Blam::Input::eInputTypeGame) == 1)
	{
		Console::WriteLine("======================== Collision Info ========================");
		Console::WriteLine(GetHitDescription(m_collisionResult));
		Console::WriteLine("================================================================");
	}
}

_inline void CRenderDebugCollisionTest::Render() // 0x108C9010
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Render@CRenderDebugCollisionTest@hades_file_local@@SAXXZ");
	// `anonymous-namespace'::CRenderDebugCollisionTest::Render
	// procedure flags: nofpo
	// static ...; // 0x108C92B6
	// static ...; // 0x108C92B1
	// static ...; // 0x108C92A5
	// static ...; // 0x108C929E
	// static ...; // 0x108C9298
	// static ...; // 0x108C9290
	// static ...; // 0x108C9248
	// static ...; // 0x108C9240
	// std::string description;
	// short_rectangle2d bounds;
	// c_rasterizer_draw_string drawstr;
	// c_font_cache_mt_safe cache;
	// s_collision_result result;
		// std::scoped_lock<std::mutex> lock;
	// function call : void (*const)(short_rectangle2d *, short_rectangle2d *, short_rectangle2d *, short_rectangle2d *)

	static void (*const interface_get_current_display_settings)(short_rectangle2d *, short_rectangle2d *, short_rectangle2d *, short_rectangle2d *) = reinterpret_cast<void (*)(short_rectangle2d *, short_rectangle2d *, short_rectangle2d *, short_rectangle2d *)>(0xA9FAA0);
	s_collision_result result;
	{
		std::scoped_lock<std::mutex> lock(m_mutex);
		if (!m_collisionResultValid)
			return;
		result = m_collisionResult;
	}
	std::string description = GetHitDescription(result);
	short_rectangle2d bounds;
	interface_get_current_display_settings(nullptr, nullptr, nullptr, &bounds);
	c_font_cache_mt_safe cache;
	c_rasterizer_draw_string drawstr;
	drawstr.set_font(0);
	drawstr.set_justification(0);
	drawstr.set_color({ 0.8f, 0.87f, 1.0f, 1.0f });
	drawstr.set_shadow_color({ 1.0f, 0.0f, 0.0f, 0.0f });
	bounds.y0 += 100;
	drawstr.set_bounds(bounds);
	drawstr.draw(&cache, description.c_str());
}

_inline std::string CRenderDebugCollisionTest::GetHitDescription(s_collision_result const &hit) // 0x108C7FA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetHitDescription@CRenderDebugCollisionTest@hades_file_local@@SA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@ABUs_collision_result@@@Z");
	// `anonymous-namespace'::CRenderDebugCollisionTest::GetHitDescription
	// static ...; // 0x108C8A44
	// static ...; // 0x108C8A39
	// static ...; // 0x108C8A2E
	// static ...; // 0x108C8A20
	// static ...; // 0x108C8A18
	// static ...; // 0x108C8A15
	// static ...; // 0x108C8A0D
	// static ...; // 0x108C89F7
	// static ...; // 0x108C89E4
	// static ...; // 0x108C89DA
	// static ...; // 0x108C89C5
	// static ...; // 0x108C89C0
	// static ...; // 0x108C8930
	// static ...; // 0x108C8928
	// s_collision_result const &hit;
	// real_euler_angles3d object_angles;
	// std::string sbspName;
	// real_point3d cameraPos;
	// long scnrIndex;
	// long renderMaterialIndex;
	// std::string collisionMaterialName;
	// char info[8224];
	// std::string renderMaterialName;
	// long (*const find_render_method_index_from_collision)(long, __int32, long, long);
	// std::string objectName;
	// std::string hitType;
	// s_scenario *scenario;
	// char bspIndex;
	// long mapvPlacementIndex;
	// float distance;
	// long unitIndex;
	// std::string global_material_name;
	// s_global_material_definition *(*const global_get_material)(short);
	// real_point3d object_pos;
		// s_object_data *object;
			// real_vector3d forward;
			// real_vector3d up;
		// s_structure_collision_material *collisionMaterial;
			// s_geometry_material *renderMaterial;
		// s_global_material_definition *global_material;
			// char *material_name;
	// function call : void (*const)(long, real_point3d *)
	// function call : void (*const)(long, real_vector3d *, real_vector3d *)
	// function call : unsigned long (*const)(long)
	// function call : void (*const)(long, real_point3d *)
	// function call : s_scenario_structure_bsp *(*const)(long)
	// function call : long (*const)(long, __int32, long, long)
	// function call : s_scenario_structure_bsp *(*const)(long)
	// function call : s_global_material_definition *(*const)(short)

	long (*const find_render_method_index_from_collision)(long, __int32, long, long) = reinterpret_cast<long (*)(long, __int32, long, long)>(0x750810);
	s_global_material_definition * (*const global_get_material)(short) = reinterpret_cast<s_global_material_definition * (*)(short)>(0x5CA640);
	std::string sbspName = "none";
	std::string objectName = "none";
	long scnrIndex = -1;
	long mapvPlacementIndex = -1;
	real_point3d object_pos = {};
	real_euler_angles3d object_angles = {};
	s_scenario *scenario = global_scenario_get();
	char bspIndex = hit.bsp_index;
	if (bspIndex >= 0 && bspIndex < scenario->structure_bsps.count)
		sbspName = GetFriendlyTagName(((s_tag_reference *)scenario->structure_bsps[bspIndex].structure_bsp)->index);
	if (hit.object_index != -1)
	{
		s_object_data *object = object_get(hit.object_index);
		if (object)
		{
			scnrIndex = object->scenario_datum_index;
			mapvPlacementIndex = object->map_variant_index;
			objectName = GetFriendlyTagName(object->definition_index);
			((void (*const)(long, real_point3d *))0xB2E5A0)(hit.object_index, &object_pos);
			real_vector3d forward;
			real_vector3d up;
			((void (*const)(long, real_vector3d *, real_vector3d *))0xB2E490)(hit.object_index, &forward, &up);
			euler_angles3d_from_vectors3d(&object_angles, &forward, &up);
			object_angles.yaw = object_angles.yaw / 3.1415927f * 180.0f;
			object_angles.pitch = object_angles.pitch / 3.1415927f * 180.0f;
			object_angles.roll = object_angles.roll / 3.1415927f * 180.0f;
		}
	}
	std::string hitType = "unknown";
	switch (hit.type)
	{
	case 1:
		hitType = "cluster";
		break;
	case 3:
		hitType = "instanced geometry";
		break;
	case 4:
		hitType = "object";
		break;
	}
	std::string collisionMaterialName = "unknown";
	std::string renderMaterialName = "unknown";
	long renderMaterialIndex = -1;
	real_point3d cameraPos = { 0.0f, 0.0f, 0.0f };
	long unitIndex = ((unsigned long (*const)(long))0x589CC0)(0);
	if (unitIndex != -1)
		((void (*const)(long, real_point3d *))0xB439D0)(unitIndex, &cameraPos);
	float distance = point3d_distance(&cameraPos, &hit.intersection_point);
	if ((hit.type == 1 || hit.type == 3) && bspIndex >= 0 && bspIndex < scenario->structure_bsps.count)
	{
		s_structure_collision_material *collisionMaterial = global_structure_bsp_get(bspIndex)->collision_materials.get_element(hit.material_index);
		if (collisionMaterial && collisionMaterial->render_method.index != -1)
			collisionMaterialName = GetFriendlyTagName(collisionMaterial->render_method.index);
		renderMaterialIndex = find_render_method_index_from_collision(bspIndex, -1, hit.instance_geometry_index, hit.surface_index);
		if (renderMaterialIndex != -1)
		{
			s_geometry_material *renderMaterial = global_structure_bsp_get(bspIndex)->materials.get_element(renderMaterialIndex);
			if (renderMaterial)
				renderMaterialName = GetFriendlyTagName(renderMaterial->render_method.index);
		}
	}
	std::string global_material_name = "unknown";
	s_global_material_definition *global_material = global_get_material(hit.global_material_type);
	if (global_material)
	{
		char *material_name = Blam::Cache::StringIDCache::GetCurrent()->GetString(global_material->Name);
		if (material_name)
			global_material_name.assign(material_name);
	}
	char info[8224];
	sprintf_s(info, "hit type: %s\r\nstructure bsp (%d): %s\r\ncluster: %d\r\ninstanced geometry instance: %d\r\nobject: %s\r\nobject scnr block index: %d\r\nobject map variant index: %d\r\nobject pos: %.3f %.3f %.3f / %.3f %.3f %.3f\r\nsurface_index: %d, flags: 0x%x\r\ncollision material (%d): %s\r\nrender material (%d): %s\r\nglobal material type (%d): %s\r\ncollision region: %d, node: %d\r\nhit point: (%.2f, %.2f, %.2f)\r\ndistance: (%.5lf)\r\n", hitType.c_str(), bspIndex, sbspName.c_str(), hit.cluster_reference.cluster_index == 0xFF ? -1 : hit.cluster_reference.cluster_index, hit.instance_geometry_index, objectName.c_str(), scnrIndex, mapvPlacementIndex, object_pos.x, object_pos.y, object_pos.z, object_angles.yaw, object_angles.pitch, object_angles.roll, hit.surface_index, hit.surface_flags, hit.material_index, collisionMaterialName.c_str(), renderMaterialIndex, renderMaterialName.c_str(), hit.global_material_type, global_material_name.c_str(), hit.region_index, hit.node_index, hit.intersection_point.x, hit.intersection_point.y, hit.intersection_point.z, distance);
	return info;
}

_inline std::string CRenderDebugCollisionTest::GetFriendlyTagName(long tagindex) // 0x108C7E20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetFriendlyTagName@CRenderDebugCollisionTest@hades_file_local@@SA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@J@Z");
	// `anonymous-namespace'::CRenderDebugCollisionTest::GetFriendlyTagName
	// static ...; // 0x108C7F3D
	// static ...; // 0x108C7F38
	// static ...; // 0x108C7F20
	// static ...; // 0x108C7F18
	// long tagindex;
	// char groupAscii[5];
	// char buff[256];
	// unsigned long group;
	// char const *name;

	if (tagindex == -1)
	{
		return "none";
	}

	char const *name = tag_get_name(tagindex);
	unsigned long group = tag_get_group_tag(tagindex);
	char groupAscii[5];
	tag_to_string(group, groupAscii, 5);
	char buff[256];
	sprintf_s(buff, "%s.%s", name, groupAscii);
	return buff;
}

_inline void CRenderDebugCollisionTest::ResetForNewMap() // 0x108C93D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ResetForNewMap@CRenderDebugCollisionTest@hades_file_local@@SAXXZ");
	// `anonymous-namespace'::CRenderDebugCollisionTest::ResetForNewMap
	// procedure flags: nofpo
	// static ...; // 0x108C9440
	// static ...; // 0x108C9434
	// static ...; // 0x108C942C
	// std::scoped_lock<std::mutex> lock;

	std::scoped_lock<std::mutex> lock(m_mutex);

	m_collisionResultValid = false;
}

void DisplayClusters() // 0x108C7C00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?DisplayClusters@@YAXXZ");
	// `anonymous-namespace'::DisplayClusters
	// procedure flags: nofpo
	// static ...; // 0x108C7DA0
	// static ...; // 0x108C7D94
	// static ...; // 0x108C7D8C
	// s_observer_result *camera;
	// s_cluster_reference cluster;
	// void (*const scenario_location_from_point)(s_cluster_reference *, real_point3d *);
		// s_scenario_structure_bsp *sbsp;
			// __int32 i;
	// function call : s_observer_result *(*const)(long)
	// function call : void (*const)(s_cluster_reference *, real_point3d *)
	// function call : s_scenario_structure_bsp *(*const)(long)

	if (!Utils::Singleton<Modules::ModuleDebug>::Instance().VarClusters->ValueInt)
		return;
	s_observer_result *camera = ((s_observer_result *(*)(long))0x613960)(0);
	if (!camera)
		return;
	void (*const scenario_location_from_point)(s_cluster_reference *, real_point3d *) = reinterpret_cast<void (*)(s_cluster_reference *, real_point3d *)>(0x4EA940);
	s_cluster_reference cluster;
	scenario_location_from_point(&cluster, &camera->position);
	CDebugDrawBackend::DrawString2d(real_point2d{ 100.0f, 200.0f }, -1, 0, 1.0f, "Structure Bsp: %d, Cluster: %d", cluster.bsp_index, cluster.cluster_index);
	if (cluster.bsp_index != -1)
	{
		s_scenario_structure_bsp *sbsp = global_structure_bsp_get(cluster.bsp_index);
		for (__int32 i = 0; i < sbsp->clusters.count; i++)
			CDebugDrawBackend::DrawBox(sbsp->clusters[i].bounds, i == cluster.cluster_index ? 0xFF00FF00 : 0xFF0000FF);
	}
}

void render_d3d_resource_tracker() // 0x108CAE30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_d3d_resource_tracker@@YAXXZ");
	// `anonymous-namespace'::render_d3d_resource_tracker
	// procedure flags: nofpo
	// static ...; // 0x108CB170
	// static ...; // 0x108CB161
	// static ...; // 0x108CB152
	// static ...; // 0x108CB144
	// static ...; // 0x108CB13B
	// static ...; // 0x108CB132
	// static ...; // 0x108CB11E
	// static ...; // 0x108CB119
	// static ...; // 0x108CB112
	// static ...; // 0x108CB10C
	// static ...; // 0x108CB104
	// static ...; // 0x108CB080
	// static ...; // 0x108CB078
		// long vertex_buffers;
		// long pixel_shaders;
		// long vertex_shaders;
		// long vertex_declarations;
		// char buff[256];
		// short_rectangle2d bounds;
		// c_rasterizer_draw_string drawstr;
		// long released_index_buffers;
		// c_font_cache_mt_safe cache;
		// long surfaces;
		// long index_buffers;
		// long textures;
		// long index_buffer_ptr;
	// function call : void (*const)(short_rectangle2d *, short_rectangle2d *, short_rectangle2d *, short_rectangle2d *)

	static void (*const interface_get_current_display_settings)(short_rectangle2d *, short_rectangle2d *, short_rectangle2d *, short_rectangle2d *) = reinterpret_cast<void (*)(short_rectangle2d *, short_rectangle2d *, short_rectangle2d *, short_rectangle2d *)>(0xA9FAA0);
	if (Utils::Singleton<Modules::ModuleDebug>::Instance().VarD3DResources->ValueInt)
	{
		long pixel_shaders;
		long vertex_shaders;
		long vertex_buffers;
		long index_buffers;
		long surfaces;
		long textures;
		long vertex_declarations;
		c_d3d_resource_tracker::get_allocated_resource_counts(&pixel_shaders, &vertex_shaders, &vertex_buffers, &index_buffers, &surfaces, &textures, &vertex_declarations);
		long index_buffer_ptr = c_d3d_resource_tracker::get_index_buffer_ptr();
		long released_index_buffers = c_d3d_resource_allocator::m_released_index_buffers;
		char buff[256];
		sprintf_s(buff, "D3D resource allocations:\r\npixel_shaders: %d\r\nvertex_shaders: %d\r\nindex_buffers: %d\r\nvertex_buffers: %d\r\nsurfaces: %d\r\ntextures: %d\r\nvertex_declarations: %d\r\nsample index buffer: 0x%x\r\nreleased index buffers: %d", pixel_shaders, vertex_shaders, vertex_buffers, index_buffers, surfaces, textures, vertex_declarations, index_buffer_ptr, released_index_buffers);
		short_rectangle2d bounds;
		interface_get_current_display_settings(nullptr, nullptr, nullptr, &bounds);
		c_font_cache_mt_safe cache;
		c_rasterizer_draw_string drawstr;
		drawstr.set_font(0);
		drawstr.set_justification(0);
		drawstr.set_color({ 0.8f, 0.87f, 1.0f, 1.0f });
		drawstr.set_shadow_color({ 1.0f, 0.0f, 0.0f, 0.0f });
		bounds.y0 += 100;
		drawstr.set_bounds(bounds);
		drawstr.draw(&cache, buff);
	}
}

void render_debug_physics_model(s_physics_model_instance const *instance, real_argb_color const *color) // 0x108CCC50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_debug_physics_model@@YAXPBUs_physics_model_instance@@PBUreal_argb_color@@@Z");
	// `anonymous-namespace'::render_debug_physics_model
	// static ...; // 0x108CCF18
	// static ...; // 0x108CCF10
	// s_physics_model_instance const *instance;
	// real_argb_color const *color;
	// s_object_data *object;
	// s_object_definition *object_def;
		// long runtime_region_index;
			// char runtime_permutation_index;
			// s_model_permutation *runtime_permutation;
			// s_model_region *runtime_region;
			// s_physics_model_permutation *physics_model_permutation;
			// s_physics_model_region *physics_model_region;
				// c_tag_block<short> &<range>$L0;
				// short *<begin>$L0;
				// short *<end>$L0;
					// long rigid_body_index;
						// real_matrix4x3 const *node_matrix;
						// real_point3d center_of_mass;
						// s_physics_model_rigid_body *rigid_body;
	// function call : void *(*const)(unsigned long, long)

	s_object_data *object = object_get(instance->object_index);
	s_object_definition *object_def = (s_object_definition *)tag_get('obje', object->definition_index);
	for (long runtime_region_index = 0; runtime_region_index < instance->model->runtime_regions.count; runtime_region_index++)
	{
		s_model_region *runtime_region = &instance->model->runtime_regions[runtime_region_index];
		char runtime_permutation_index = instance->region_permutation_indices[runtime_region_index];
		if (runtime_region->physics_region_index == -1 || runtime_permutation_index == -1)
			continue;
		s_model_permutation *runtime_permutation = &runtime_region->permutations[runtime_permutation_index];
		if (runtime_permutation->physics_permutation_index == -1)
			continue;
		if (!instance->physics_model->regions.count)
			continue;
		s_physics_model_region *physics_model_region = &instance->physics_model->regions[runtime_region->physics_region_index];
		s_physics_model_permutation *physics_model_permutation = &physics_model_region->permutations[runtime_permutation->physics_permutation_index];
		for (long rigid_body_index : physics_model_permutation->rigid_body_indices)
		{
			s_physics_model_rigid_body *rigid_body = &instance->physics_model->rigid_bodies[rigid_body_index];
			real_matrix4x3 const *node_matrix = rigid_body->node == -1 ? &instance->matrix : &instance->node_matrices[rigid_body->node];
			real_point3d center_of_mass;
			center_of_mass.x = rigid_body->center_of_mass.x;
			center_of_mass.y = rigid_body->center_of_mass.y;
			center_of_mass.z = rigid_body->center_of_mass.z;
			matrix4x3_transform_point(node_matrix, &center_of_mass, &center_of_mass);
			render_debug_physics_shape(rigid_body->shape.runtime_shape, node_matrix, color);
		}
	}
}

void render_debug_collision_edge(collision_bsp const *bsp, long index, real_matrix4x3 const *matrix, long color) // 0x108CB2E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_debug_collision_edge@@YAXPBUcollision_bsp@@JPBUreal_matrix4x3@@J@Z");
	// `anonymous-namespace'::render_debug_collision_edge
	// static ...; // 0x108CB3F4
	// collision_bsp const *bsp;
	// long index;
	// real_matrix4x3 const *matrix;
	// long color;
	// real_point3d p2;
	// real_point3d p1;
	// collision_edge const &edge;

	collision_edge const &edge = bsp->edges[index];
	real_point3d p1 = bsp->vertices[edge.start_vertex].position;
	real_point3d p2 = bsp->vertices[edge.end_vertex].position;

	if (matrix)
	{
		matrix4x3_transform_point(matrix, &p1, &p1);
		matrix4x3_transform_point(matrix, &p2, &p2);
	}

	CDebugDrawBackend::DrawLine(p1, p2, color);
}

void render_debug_large_collision_edge(s_large_collision_bsp const *bsp, long index, real_matrix4x3 const *matrix, long color) // 0x108CBF90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_debug_large_collision_edge@@YAXPBUs_large_collision_bsp@@JPBUreal_matrix4x3@@J@Z");
	// `anonymous-namespace'::render_debug_large_collision_edge
	// static ...; // 0x108CC0A4
	// s_large_collision_bsp const *bsp;
	// long index;
	// real_matrix4x3 const *matrix;
	// long color;
	// real_point3d p2;
	// real_point3d p1;
	// s_large_collision_edge const &edge;

	s_large_collision_edge const &edge = bsp->edges[index];
	real_point3d p1 = bsp->vertices[edge.start_vertex].position;
	real_point3d p2 = bsp->vertices[edge.end_vertex].position;

	if (matrix)
	{
		matrix4x3_transform_point(matrix, &p1, &p1);
		matrix4x3_transform_point(matrix, &p2, &p2);
	}

	CDebugDrawBackend::DrawLine(p1, p2, color);
}

void render_debug_collision_bsp(collision_bsp const *bsp, real_matrix4x3 const *matrix, unsigned long color) // 0x108CB260
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_debug_collision_bsp@@YAXPBUcollision_bsp@@PBUreal_matrix4x3@@K@Z");
	// `anonymous-namespace'::render_debug_collision_bsp
	// unsigned long color;
		// long i;

	long i;

	for (i = 0; i < bsp->edges.count; i++)
	{
		render_debug_collision_edge(bsp, i, matrix, color);
	}
}

void render_debug_large_collision_bsp(s_large_collision_bsp const *bsp, real_matrix4x3 const *matrix, unsigned long color) // 0x108CBF10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_debug_large_collision_bsp@@YAXPBUs_large_collision_bsp@@PBUreal_matrix4x3@@K@Z");
	// `anonymous-namespace'::render_debug_large_collision_bsp
	// unsigned long color;
		// long i;

	long i;

	for (i = 0; i < bsp->edges.count; i++)
	{
		render_debug_large_collision_edge(bsp, i, matrix, color);
	}
}

void render_debug_collision_model(collision_model_instance const *instance) // 0x108CB470
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_debug_collision_model@@YAXPBUcollision_model_instance@@@Z");
	// `anonymous-namespace'::render_debug_collision_model
	// static ...; // 0x108CB550
	// static ...; // 0x108CB544
	// static ...; // 0x108CB53C
	// collision_model_instance const *instance;
	// s_collision_model_bsp_iterator iterator;
		// unsigned char node_index;
	// function call : void (*const)(s_collision_model_bsp_iterator *, model_definition const *, collision_model_definition const *, unsigned char const *)
	// function call : bool (*const)(s_collision_model_bsp_iterator *)

	s_collision_model_bsp_iterator iterator;
	((void (*const)(s_collision_model_bsp_iterator *, model_definition *, collision_model_definition *, unsigned char *))0x980AF0)(&iterator, instance->model, instance->collision_model, instance->permutations);
	while (((bool (*const)(s_collision_model_bsp_iterator *))0x980BC0)(&iterator))
	{
		unsigned char node_index = iterator.m_bsp3d_reference & 0xFF;
		render_debug_collision_bsp(iterator.m_bsp.bsp, &instance->nodes[node_index], 0xFF00FF00);
	}
}

void render_debug_object_markers(long object_index) // 0x108CC380
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_debug_object_markers@@YAXJ@Z");
	// `anonymous-namespace'::render_debug_object_markers
	// static ...; // 0x108CC9C0
	// static ...; // 0x108CC9B4
	// static ...; // 0x108CC9AC
	// long object_index;
	// s_object_data *object;
	// std::string const &groupFilter;
	// s_object_marker markers[64];
	// s_object_definition *object_def;
	// s_model_definition *model;
	// s_render_model *render_model;
		// long i;
			// unsigned long color;
			// float r;
			// float g;
			// s_render_model_marker_group &marker_group;
			// float b;
			// char *group_name;
			// short marker_count;
			// float theta;
				// __int32 j;
	// function call : void *(*const)(unsigned long, long)
	// function call : void *(*const)(unsigned long, long)
	// function call : void *(*const)(unsigned long, long)
	// function call : unsigned long (*const)(real_argb_color const &)
	// function call : short (*const)(long, unsigned long, s_object_marker *, short)

	s_object_data *object = object_get(object_index);
	if (!object)
		return;
	s_object_definition *object_def = (s_object_definition *)tag_get('obje', object->definition_index);
	s_model_definition *model = (s_model_definition *)tag_get('hlmt', object_def->model.index);
	if (model->render_model.index == -1)
		return;
	s_render_model *render_model = (s_render_model *)tag_get('mode', model->render_model.index);
	srand(object_index);
	std::string const &groupFilter = Modules::ModuleDebug::Instance().VarMarkerGroupFilter->ValueString;
	s_object_marker markers[64];
	for (long i = 0; i < render_model->marker_groups.count; i++)
	{
		s_render_model_marker_group &marker_group = render_model->marker_groups[i];
		char *group_name = Blam::Cache::StringIDCache::GetCurrent()->GetString(marker_group.name);
		if (!group_name)
			continue;
		if (!groupFilter.empty() && !strstr(group_name, groupFilter.c_str()))
			continue;
		float theta = rand() / 1738.34326171875f;
		float r = sin(theta + 0.0f) * 0.5f + 0.5f;
		float g = sin(theta + 2.0f) * 0.5f + 0.5f;
		float b = sin(theta + 4.0f) * 0.5f + 0.5f;
		unsigned long color = ((unsigned long (*const)(real_argb_color const &))0x521810)({ 1.0f, r, g, b });
		short marker_count = ((short (*const)(long, unsigned long, s_object_marker *, short))0xB2E3C0)(object_index, marker_group.name, markers, 64);
		for (__int32 j = 0; j < marker_count; j++)
		{
				CDebugDrawBackend::DrawLine(markers[j].world_matrix.position, markers[j].world_matrix.position + 0.07f * markers[j].world_matrix.forward, 0xFF0000FF);
				CDebugDrawBackend::DrawLine(markers[j].world_matrix.position, markers[j].world_matrix.position + 0.07f * markers[j].world_matrix.up, 0xFF00FF00);
				CDebugDrawBackend::DrawLine(markers[j].world_matrix.position, markers[j].world_matrix.position + 0.07f * markers[j].world_matrix.left, 0xFFFF0000);
			CDebugDrawBackend::DrawString3d(markers[j].world_matrix.position, color, 0, 1.0f, "%d - %s", j, group_name);
		}
	}
}

void render_debug_object(long object_index) // 0x108CC120
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_debug_object@@YAXJ@Z");
	// `anonymous-namespace'::render_debug_object
	// static ...; // 0x108CC2F4
	// static ...; // 0x108CC2EB
	// static ...; // 0x108CC2E2
	// static ...; // 0x108CC2DC
	// static ...; // 0x108CC2AC
	// static ...; // 0x108CC2A4
	// long object_index;
	// real_point3d position;
	// Modules::ModuleDebug const &moduleDebug;
	// c_player_view *view;
		// collision_model_instance instance;
		// s_physics_model_instance instance;
			// real_argb_color color;
	// function call : void (*const)(long, real_point3d *)
	// function call : bool (*const)(collision_model_instance *, long)
	// function call : bool (*const)(s_physics_model_instance *, long)

	static void (*const object_get_origin)(long, real_point3d *) = reinterpret_cast<void (*)(long, real_point3d *)>(0xB2E5A0);
	static bool (*const collision_model_instance_new)(collision_model_instance *, long) = reinterpret_cast<bool (*)(collision_model_instance *, long)>(0x980E40);
	static bool (*const physics_model_instance_new)(s_physics_model_instance *, long) = reinterpret_cast<bool (*)(s_physics_model_instance *, long)>(0x786430);
	real_point3d position;
	object_get_origin(object_index, &position);
	c_player_view *view = c_player_view::get_current();
	if (distance_squared3d(&view->render_camera.position, &position) > 100.0f)
		return;
	Modules::ModuleDebug const &moduleDebug = Utils::Singleton<Modules::ModuleDebug>::Instance();
	if (moduleDebug.VarCollisionModels->ValueInt)
	{
		collision_model_instance instance;
		if (collision_model_instance_new(&instance, object_index))
			render_debug_collision_model(&instance);
	}
	if (moduleDebug.VarPhysicsModels->ValueInt)
	{
		s_physics_model_instance instance;
		if (physics_model_instance_new(&instance, object_index))
		{
			real_argb_color color = { 1.0f, 1.0f, 0.0f, 0.0f };
			render_debug_physics_model(&instance, &color);
		}
	}
	if (moduleDebug.VarMarkerGroups->ValueInt)
		render_debug_object_markers(object_index);
}

void render_debug_objects() // 0x108CCB60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_debug_objects@@YAXXZ");
	// `anonymous-namespace'::render_debug_objects
	// procedure flags: nofpo
	// short starting_index;
	// s_visible_items *visible_items;
		// __int32 i;
			// s_visible_object_hierarchy &object_hierarchy;
				// __int32 j;

	s_visible_items &visible_items = c_visible_items::get_global_items();
	short marker = *(short *)&c_visible_items::get_current_markers();

	for (long i = 0; i < visible_items.object_hierarchies.count; i++)
	{
		auto &hierarchy = visible_items.object_hierarchies.elements[i];
		if (hierarchy.first_index == -1)
			continue;

		for (long j = 0; j < hierarchy.count; j++)
		{
			render_debug_object(visible_items.objects.elements[hierarchy.first_index + j].object_index);
		}
	}
}

void render_debug_frame_render() // 0x108CBEB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_debug_frame_render@@YAXXZ");
	// `anonymous-namespace'::render_debug_frame_render
	// procedure flags: nofpo

	CRenderDebugCollisionTest::Render();
	render_d3d_resource_tracker();
	Patches::HavokMemory::RenderDebug();
	CDebugTrace::Render();
	CDebugDrawBackend::Render();
}

void render_debug_damage_submit(s_damage_data const *data, float radius) // 0x108CB5A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_debug_damage_submit@@YAXPBUs_damage_data@@M@Z");
	// `anonymous-namespace'::render_debug_damage_submit
	// static ...; // 0x108CBCD0
	// static ...; // 0x108CBCC8
	// s_damage_data const *data;
	// float radius;
	// __int32 const color_emp_radius;
	// float line_height;
	// CDebugDraw dd;
	// __int32 const color_aoe_radius;
	// float x;
	// s_damage_effect_definition *damage_effect;
	// __int32 const color_effect_radius_lower;
	// float y;
	// __int32 const color_direction_vector;
	// __int32 const color_core_radius;
	// __int32 const color_spike_radius;
	// __int32 const color_effect_radius_upper;
	// __int32 const color_shake_radius;
	// function call : void *(*const)(unsigned long, long)

	__int32 const color_aoe_radius = 0xFFFFFF00;
	__int32 const color_direction_vector = 0xFFFF0000;
	__int32 const color_effect_radius_lower = 0xFF330000;
	__int32 const color_effect_radius_upper = 0xFFFF0000;
	__int32 const color_core_radius = 0xFF953553;
	__int32 const color_shake_radius = 0xFFFFA500;
	__int32 const color_spike_radius = 0xFFFF00FF;
	__int32 const color_emp_radius = 0xFF008B8B;
	s_damage_effect_definition *damage_effect = (s_damage_effect_definition *)tag_get('jpt!', data->damage_effect_index);
	#line 576 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\DebugPatches.cpp"
		CDebugDraw dd(std::source_location::
	#line 576 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\DebugPatches.cpp"
	            current());
	#line 1104 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\DebugPatches.cpp"
	dd.SetLifetime(Utils::Singleton<Modules::ModuleDebug>::Instance().VarDamageAoeDisplayTime->ValueFloat * 20.0f);
	dd.SetFont(0);
	dd.SetTextScale(1.5f);
	float line_height = dd.GetLineHeight(0) * 1.5f;
	dd.DrawSphereOutline({ "aoe-radius", 0xFFFFFFFF }, data->epicenter, radius, color_aoe_radius);
	dd.DrawVector({ "direction", 0xFFFFFFFF }, data->epicenter, data->direction, color_direction_vector);
	dd.DrawSphereOutline({ "effect-radius-lower", 0xFFFFFFFF }, data->epicenter, damage_effect->radius.lower, color_effect_radius_lower);
	dd.DrawSphereOutline({ "effect-radius-upper", 0xFFFFFFFF }, data->epicenter, damage_effect->radius.upper, color_effect_radius_upper);
	dd.DrawSphereOutline({ "aoe-core-radius", 0xFFFFFFFF }, data->epicenter, damage_effect->area_of_effect_core_radius, color_core_radius);
	dd.DrawSphereOutline({ "shake-radius", 0xFFFFFFFF }, data->epicenter, damage_effect->shake_radius, color_shake_radius);
	dd.DrawSphereOutline({ "emp-radius", 0xFFFFFFFF }, data->epicenter, damage_effect->emp_radius, color_emp_radius);
	dd.DrawSphereOutline({ "aoe-spike-radius", 0xFFFFFFFF }, data->epicenter, damage_effect->aoe_spike_radius, color_spike_radius);
	float x = 18.0f;
	float y = 1.0f;
	dd.DrawString2d({ "radius-lower-label", 0xFFFFFFFF }, { x, y++ * line_height }, color_effect_radius_lower, "radius lower");
	dd.DrawString2d({ "radius-upper-label", 0xFFFFFFFF }, { x, y++ * line_height }, color_effect_radius_upper, "radius upper");
	dd.DrawString2d({ "core-radius-label", 0xFFFFFFFF }, { x, y++ * line_height }, color_core_radius, "core radius");
	dd.DrawString2d({ "shake-radius-label", 0xFFFFFFFF }, { x, y++ * line_height }, color_shake_radius, "shake radius");
	dd.DrawString2d({ "aoe-radius-label", 0xFFFFFFFF }, { x, y++ * line_height }, color_aoe_radius, "aoe radius");
	dd.DrawString2d({ "emp-radius-label", 0xFFFFFFFF }, { x, y++ * line_height }, color_emp_radius, "emp radius");
	dd.DrawString2d({ "spike-radius-label", 0xFFFFFFFF }, { x, y++ * line_height }, color_spike_radius, "spike radius");
}

short area_of_effect_cause_damage_objects_in_sphere_hook(long flags, long object_mask, s_cluster_reference *cluster, real_point3d const *center, float radius, long *objects, short max_objects) // 0x108C9980
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?area_of_effect_cause_damage_objects_in_sphere_hook@@YAFJJPAUs_cluster_reference@@PBUreal_point3d@@MPAJF@Z");
	// `anonymous-namespace'::area_of_effect_cause_damage_objects_in_sphere_hook
	// short max_objects;
	// short num_objects;
		// s_damage_data *damage_data;
	// function call : short (*const)(long, long, s_cluster_reference const *, real_point3d const *, float, long *, short)

	short num_objects = ((short (*const)(long, long, s_cluster_reference const *, real_point3d const *, float, long *, unsigned short))0xb35b60)(flags, object_mask, cluster, center, radius, objects, max_objects);
	if (Modules::ModuleDebug::Instance().VarDamageAoe->ValueInt)
	{
		s_damage_data *damage_data = (s_damage_data *)offset_pointer(cluster, -32);
		render_debug_damage_submit(damage_data, radius);
	}
	return num_objects;
}

void render_debug_trigger_volume(s_scenario_trigger_volume *volume, long color) // 0x108CD2F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_debug_trigger_volume@@YAXPAUs_scenario_trigger_volume@@J@Z");
	// `anonymous-namespace'::render_debug_trigger_volume
	// static ...; // 0x108CD607
	// static ...; // 0x108CD600
	// static ...; // 0x108CD5DC
	// static ...; // 0x108CD5D4
	// s_scenario_trigger_volume *volume;
	// long color;
	// bool (*const visibility_test_sphere)(real_point3d *, float);
	// real_rectangle3d bounds;
	// void (*const trigger_volume_get_matrix)(s_scenario_trigger_volume *, real_matrix4x3 *);
	// float enclosing_radius;
	// real_matrix4x3 matrix;
	// real_point3d center;
	// char const *name;
	// function call : void (*const)(s_scenario_trigger_volume *, real_matrix4x3 *)
	// function call : bool (*const)(real_point3d *, float)

	void (*const trigger_volume_get_matrix)(s_scenario_trigger_volume *, real_matrix4x3 *) = reinterpret_cast<void (*)(s_scenario_trigger_volume *, real_matrix4x3 *)>(0x5FACC0);
	bool (*const visibility_test_sphere)(real_point3d *, float) = reinterpret_cast<bool (*)(real_point3d *, float)>(0xA7BDA0);
	real_matrix4x3 matrix;
	trigger_volume_get_matrix(volume, &matrix);
	real_point3d center;
	center.x = volume->extents.x * 0.5;
	center.y = volume->extents.y * 0.5;
	center.z = volume->extents.z * 0.5;
	matrix4x3_transform_point(&matrix, &center, &center);
	float enclosing_radius = volume->c;
	if (volume->extents.x * 0.5f > enclosing_radius)
		enclosing_radius = volume->extents.x * 0.5f;
	if (volume->extents.y * 0.5f > enclosing_radius)
		enclosing_radius = volume->extents.y * 0.5f;
	if (volume->extents.z * 0.5f > enclosing_radius)
		enclosing_radius = volume->extents.z * 0.5f;
	if (!visibility_test_sphere(&center, enclosing_radius))
		return;
	real_rectangle3d bounds = { 0.0f, volume->extents.x, 0.0f, volume->extents.y, 0.0f, volume->extents.z };
	char const *name = Blam::Cache::StringIDCache::GetCurrent()->GetString(volume->name);
	CDebugDrawBackend::DrawBoxOriented(bounds, matrix, color);
	CDebugDrawBackend::DrawString3d(center, color, 0, 1.0f, "%s", name ? name : "<unknown>");
}

void render_debug_trigger_volumes() // 0x108CD6E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_debug_trigger_volumes@@YAXXZ");
	// `anonymous-namespace'::render_debug_trigger_volumes
	// procedure flags: nofpo
	// static ...; // 0x108CDAB4
	// static ...; // 0x108CDAAE
	// static ...; // 0x108CDAA8
	// static ...; // 0x108CDAA2
	// static ...; // 0x108CDAA0
	// static ...; // 0x108CDA64
	// static ...; // 0x108CDA5C
	// std::vector<short> usedIndices;
	// s_scenario *scenario;
		// long i;
			// short index;

	if (!Utils::Singleton<Modules::ModuleDebug>::Instance().VarTriggerVolumes->ValueInt)
		return;
	s_scenario *scenario = global_scenario_get();
	std::vector<short> usedIndices;
	for (long i = 0; i < scenario->zone_set_switch_trigger_volumes.count; i++)
	{
		short index = scenario->zone_set_switch_trigger_volumes[i].trigger_volume;
		if (index >= 0 && index < scenario->trigger_volumes.count)
		{
			render_debug_trigger_volume(&scenario->trigger_volumes[index], 0xFFFFFF00);
			usedIndices.push_back(index);
		}
	}
	for (long i = 0; i < scenario->scenario_kill_triggers.count; i++)
	{
		short index = scenario->scenario_kill_triggers[i];
		if (index >= 0 && index < scenario->trigger_volumes.count)
		{
			render_debug_trigger_volume(&scenario->trigger_volumes[index], 0xFFFF0000);
			usedIndices.push_back(index);
		}
	}
	for (long i = 0; i < scenario->scenario_safe_triggers.count; i++)
	{
		short index = scenario->scenario_safe_triggers[i];
		if (index >= 0 && index < scenario->trigger_volumes.count)
		{
			render_debug_trigger_volume(&scenario->trigger_volumes[index], 0xFF00FF00);
			usedIndices.push_back(index);
		}
	}
	for (long i = 0; i < scenario->trigger_volumes.count; i++)
	{
		if (std::find(usedIndices.begin(), usedIndices.end(), i) == usedIndices.end())
			render_debug_trigger_volume(&scenario->trigger_volumes[i], 0xFF0000FF);
	}
}

void render_debug_structure_bsp(long bsp_index) // 0x108CD090
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_debug_structure_bsp@@YAXJ@Z");
	// `anonymous-namespace'::render_debug_structure_bsp
	// long bsp_index;
	// s_scenario_structure_bsp *structure_bsp;
	// s_structure_bsp_resources *bsp_resources;
		// c_tag_block<collision_bsp> &<range>$L0;
		// collision_bsp *<begin>$L0;
		// collision_bsp *<end>$L0;
			// collision_bsp const &bsp;
		// s_large_collision_bsp *<end>$L1;
		// s_large_collision_bsp *<begin>$L1;
		// c_tag_block<s_large_collision_bsp> &<range>$L1;
			// s_large_collision_bsp const &bsp;
		// long i;
			// s_structure_instanced_geometry_instance *const instance;
			// s_structure_instanced_geometry_definition *const definition;
	// function call : s_scenario_structure_bsp *(*const)(long)
	// function call : void *(*const)(void *)

	s_scenario_structure_bsp *structure_bsp = global_structure_bsp_get(bsp_index);
	s_structure_bsp_resources *bsp_resources = ((s_structure_bsp_resources *(*)(void *))0x563E10)(&structure_bsp->collision_bsp_resource);
	if (!bsp_resources)
		return;
	if (Utils::Singleton<Modules::ModuleDebug>::Instance().VarStructureCollision->ValueInt)
	{
		for (collision_bsp const &bsp : bsp_resources->collision_bsps)
			render_debug_collision_bsp(&bsp, nullptr, 0xFF00FF00);
		for (s_large_collision_bsp const &bsp : bsp_resources->large_collision_bsps)
			render_debug_large_collision_bsp(&bsp, nullptr, 0xFF00FF00);
		for (long i = 0; i < structure_bsp->instanced_geometry_instances.count; i++)
		{
			s_structure_instanced_geometry_instance *const instance = &structure_bsp->instanced_geometry_instances[i];
			if (instance->mesh_index < 0 || instance->mesh_index >= bsp_resources->instanced_geometry.count)
				continue;
			s_structure_instanced_geometry_definition *const definition = &bsp_resources->instanced_geometry[instance->mesh_index];
			render_debug_collision_bsp(&definition->collision_bsp, &instance->rigid_matrix, 0xFFFF00FF);
		}
	}
}

void render_debug_structure() // 0x108CCFF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_debug_structure@@YAXXZ");
	// `anonymous-namespace'::render_debug_structure
	// procedure flags: nofpo
	// long bsp_index;
	// function call : long (*const)()
	// function call : long (*const)(long)

	long bsp_index = global_structure_bsp_first_active_index_get();
	while (bsp_index != -1)
	{
		render_debug_structure_bsp(bsp_index);
		bsp_index = global_structure_bsp_next_active_index_get(bsp_index);
	}
}

void draw_assassination_capsule(char const *key, hkpCapsuleShape const *shape, real_matrix4x3 const *transform, long color) // 0x108C9EF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?draw_assassination_capsule@@YAXPBDPBUhkpCapsuleShape@@PBUreal_matrix4x3@@J@Z");
	// `anonymous-namespace'::draw_assassination_capsule
	// static ...; // 0x108CA09C
	// static ...; // 0x108CA06C
	// static ...; // 0x108CA064
	// char const *key;
	// hkpCapsuleShape const *shape;
	// real_matrix4x3 const *transform;
	// long color;
	// CDebugDraw draw;
	// real_point3d vertex_b;
	// real_point3d vertex_a;
	// float radius;
	// real_matrix4x3 matrix_copy;

	#line 745 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\DebugPatches.cpp"
		CDebugDraw draw(std::source_location::
	#line 745 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\DebugPatches.cpp"
	            current());
	#line 1325 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\DebugPatches.cpp"
	real_point3d vertex_a;
	vertex_a.x = shape->m_vertexA.x;
	vertex_a.y = shape->m_vertexA.y;
	vertex_a.z = shape->m_vertexA.z;
	real_point3d vertex_b;
	vertex_b.x = shape->m_vertexB.x;
	vertex_b.y = shape->m_vertexB.y;
	vertex_b.z = shape->m_vertexB.z;
	float radius = shape->m_radius;
	real_matrix4x3 matrix_copy = *transform;
	draw.SetLifetime(Utils::Singleton<Modules::ModuleDebug>::Instance().VarAnimationPhoneboothDrawTime->ValueFloat);
	draw.DrawPhysicsShapeCapsule({ key, 0xFFFFFFFF }, vertex_a, vertex_b, radius, matrix_copy, color);
}

bool havok_world_shape_collides_hook_initiator(hkpShape const *shape, long unknown, real_matrix4x3 const *transform, long havok_group) // 0x108CAC70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?havok_world_shape_collides_hook_initiator@@YA_NPBUhkpShape@@JPBUreal_matrix4x3@@J@Z");
	// `anonymous-namespace'::havok_world_shape_collides_hook_initiator
	// long havok_group;
	// bool (*havok_world_shape_collides)(hkpShape const *, long, real_matrix4x3 const *, long);
	// function call : bool (*)(hkpShape const *, long, real_matrix4x3 const *, long)

	bool (*havok_world_shape_collides)(hkpShape const *, long, real_matrix4x3 const *, long) = (bool (*)(hkpShape const *, long, real_matrix4x3 const *, long))0x5c8010;
	if (Modules::ModuleDebug::Instance().VarAnimationPhoneboothTestDraw->ValueInt >= 1 && shape->m_type == 7)
	{
		draw_assassination_capsule(assassination_capsule_counter + "assassination-initiator-shape-", (hkpCapsuleShape const *)shape, transform, 0xFFFF0000);
		assassination_capsule_counter++;
	}
	return havok_world_shape_collides(shape, unknown, transform, havok_group);
}

bool havok_world_shape_collides_hook_target(hkpShape const *shape, long unknown, real_matrix4x3 const *transform, long havok_group) // 0x108CAD50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?havok_world_shape_collides_hook_target@@YA_NPBUhkpShape@@JPBUreal_matrix4x3@@J@Z");
	// `anonymous-namespace'::havok_world_shape_collides_hook_target
	// long havok_group;
	// bool (*havok_world_shape_collides)(hkpShape const *, long, real_matrix4x3 const *, long);
	// function call : bool (*)(hkpShape const *, long, real_matrix4x3 const *, long)

	bool (*havok_world_shape_collides)(hkpShape const *, long, real_matrix4x3 const *, long) = (bool (*)(hkpShape const *, long, real_matrix4x3 const *, long))0x5c8010;
	if (Modules::ModuleDebug::Instance().VarAnimationPhoneboothTestDraw->ValueInt >= 1 && shape->m_type == 7)
	{
		draw_assassination_capsule(assassination_capsule_counter + "assassination-target-shape-", (hkpCapsuleShape const *)shape, transform, 0xFF00FF00);
		assassination_capsule_counter++;
	}
	return havok_world_shape_collides(shape, unknown, transform, havok_group);
}

bool assassination_sync_action_point_on_slope_or_falls_hook(long object_index, float height_standing, float physics_radius, real_point3d const *action_point, bool allow_success, float *out_slope_offset) // 0x108C9A50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?assassination_sync_action_point_on_slope_or_falls_hook@@YA_NJMMPBUreal_point3d@@_NPAM@Z");
	// `anonymous-namespace'::assassination_sync_action_point_on_slope_or_falls_hook
	// static ...; // 0x108C9D08
	// static ...; // 0x108C9D00
	// long object_index;
	// float height_standing;
	// float physics_radius;
	// real_point3d const *action_point;
	// bool allow_success;
	// float *out_slope_offset;
	// real_point3d top_point;
	// float end_point_offset;
	// bool (*collision_test_line)(long long, bool, real_point3d *, real_point3d *, __int32, __int32, __int32, s_collision_result *);
	// s_collision_result collision_result;
	// float v30;
	// real_point3d end_point;
	// static long `assassination_sync_action_point_on_slope_or_falls_hook'::`2'::assassination_point_counter; // 0x12408318
		// real_point3d world_collision_point;
		// CDebugDraw draw;
	// function call : bool (*)(long long, bool, real_point3d *, real_point3d *, __int32, __int32, __int32, s_collision_result *)

	static long assassination_point_counter = 0;
	bool (*collision_test_line)(long long, bool, real_point3d *, real_point3d *, __int32, __int32, __int32, s_collision_result *) = reinterpret_cast<bool (*)(long long, bool, real_point3d *, real_point3d *, __int32, __int32, __int32, s_collision_result *)>(0x6D67E0);
	real_point3d top_point;
	real_point3d end_point;
	float end_point_offset = height_standing - physics_radius + 0.15f;
	float v30 = 1.0f - 0.15f / end_point_offset;
	point_from_line3d(action_point, &global_up3d, height_standing - physics_radius, &top_point);
	point_from_line3d(&top_point, &global_up3d, -end_point_offset, &end_point);
	if (Utils::Singleton<Modules::ModuleDebug>::Instance().VarAnimationPhoneboothTestDraw->ValueInt >= 1)
	{
	#line 804 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\DebugPatches.cpp"
			CDebugDraw draw(std::source_location::
	#line 804 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\DebugPatches.cpp"
	             current());
	#line 1411 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\DebugPatches.cpp"
		draw.SetLifetime(Utils::Singleton<Modules::ModuleDebug>::Instance().VarAnimationPhoneboothDrawTime->ValueFloat);
		real_point3d world_collision_point;
		point_from_line3d(&top_point, &global_up3d, -(height_standing - physics_radius), &world_collision_point);
		draw.DrawLine("assassination-point-on-slope1-" + assassination_point_counter, top_point, world_collision_point, 0xFFFFFF00);
		draw.DrawLine("assassination-point-on-slope2-" + assassination_point_counter, world_collision_point, end_point, 0xFFFF7F00);
		assassination_point_counter++;
	}
	s_collision_result collision_result;
	collision_result.collision_bsp_reference.bsp = nullptr;
	collision_result.collision_bsp_reference.large_bsp = nullptr;
	collision_result.global_material_type = -1;
	if (collision_test_line(0x130500000809, false, &top_point, &end_point, object_index, -1, -1, &collision_result))
	{
		if (collision_result.t >= v30)
		{
			*out_slope_offset = 0.0f;
			return false;
		}
		else
		{
			*out_slope_offset = (v30 - collision_result.t) * end_point_offset;
			return false;
		}
	}
	else
	{
		*out_slope_offset = 0.0f;
		return allow_success;
	}
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_tag_block<collision_edge>::try_get_element(__int32, collision_edge **) const;
template bool c_tag_block<collision_vertex>::try_get_element(__int32, collision_vertex **) const;
template bool c_tag_block<s_large_collision_edge>::try_get_element(__int32, s_large_collision_edge **) const;
template bool c_tag_block<s_large_collision_vertex>::try_get_element(__int32, s_large_collision_vertex **) const;
template bool c_tag_block<s_model_permutation>::try_get_element(__int32, s_model_permutation **) const;
template bool c_tag_block<s_model_region>::try_get_element(__int32, s_model_region **) const;
template bool c_tag_block<s_physics_model_permutation>::try_get_element(__int32, s_physics_model_permutation **) const;
template bool c_tag_block<s_physics_model_region>::try_get_element(__int32, s_physics_model_region **) const;
template bool c_tag_block<s_physics_model_rigid_body>::try_get_element(__int32, s_physics_model_rigid_body **) const;
template bool c_tag_block<s_render_model_marker_group>::try_get_element(__int32, s_render_model_marker_group **) const;
template bool c_tag_block<s_scenario_trigger_volume>::try_get_element(__int32, s_scenario_trigger_volume **) const;
template bool c_tag_block<s_scenario_zone_set_switch_trigger_volume>::try_get_element(__int32, s_scenario_zone_set_switch_trigger_volume **) const;
template bool c_tag_block<s_structure_collision_material>::try_get_element(__int32, s_structure_collision_material **) const;
template bool c_tag_block<s_structure_instanced_geometry_definition>::try_get_element(__int32, s_structure_instanced_geometry_definition **) const;
template bool c_tag_block<short>::try_get_element(__int32, short **) const;
template c_tag_block_index<s_scenario_trigger_volume,short>::operator short() const;
template collision_bsp * c_tag_block<collision_bsp>::begin();
template collision_bsp * c_tag_block<collision_bsp>::end();
template collision_edge * c_tag_block<collision_edge>::get_element(__int32) const;
template collision_edge const & c_tag_block<collision_edge>::operator[](__int32) const;
template collision_vertex * c_tag_block<collision_vertex>::get_element(__int32) const;
template collision_vertex const & c_tag_block<collision_vertex>::operator[](__int32) const;
template s_large_collision_bsp * c_tag_block<s_large_collision_bsp>::begin();
template s_large_collision_bsp * c_tag_block<s_large_collision_bsp>::end();
template s_large_collision_edge * c_tag_block<s_large_collision_edge>::get_element(__int32) const;
template s_large_collision_edge const & c_tag_block<s_large_collision_edge>::operator[](__int32) const;
template s_large_collision_vertex * c_tag_block<s_large_collision_vertex>::get_element(__int32) const;
template s_large_collision_vertex const & c_tag_block<s_large_collision_vertex>::operator[](__int32) const;
template s_model_permutation & c_tag_block<s_model_permutation>::operator[](__int32);
template s_model_permutation * c_tag_block<s_model_permutation>::get_element(__int32) const;
template s_model_region & c_tag_block<s_model_region>::operator[](__int32);
template s_model_region * c_tag_block<s_model_region>::get_element(__int32) const;
template s_physics_model_permutation & c_tag_block<s_physics_model_permutation>::operator[](__int32);
template s_physics_model_permutation * c_tag_block<s_physics_model_permutation>::get_element(__int32) const;
template s_physics_model_region & c_tag_block<s_physics_model_region>::operator[](__int32);
template s_physics_model_region * c_tag_block<s_physics_model_region>::get_element(__int32) const;
template s_physics_model_rigid_body & c_tag_block<s_physics_model_rigid_body>::operator[](__int32);
template s_physics_model_rigid_body * c_tag_block<s_physics_model_rigid_body>::get_element(__int32) const;
template s_render_model_marker_group & c_tag_block<s_render_model_marker_group>::operator[](__int32);
template s_render_model_marker_group * c_tag_block<s_render_model_marker_group>::get_element(__int32) const;
template s_scenario_trigger_volume & c_tag_block<s_scenario_trigger_volume>::operator[](__int32);
template s_scenario_trigger_volume * c_tag_block<s_scenario_trigger_volume>::get_element(__int32) const;
template s_scenario_zone_set_switch_trigger_volume & c_tag_block<s_scenario_zone_set_switch_trigger_volume>::operator[](__int32);
template s_scenario_zone_set_switch_trigger_volume * c_tag_block<s_scenario_zone_set_switch_trigger_volume>::get_element(__int32) const;
template s_structure_collision_material * c_tag_block<s_structure_collision_material>::get_element(__int32) const;
template s_structure_instanced_geometry_definition & c_tag_block<s_structure_instanced_geometry_definition>::operator[](__int32);
template s_structure_instanced_geometry_definition * c_tag_block<s_structure_instanced_geometry_definition>::get_element(__int32) const;
template short & c_tag_block<short>::operator[](__int32);
template short * c_tag_block<short>::begin();
template short * c_tag_block<short>::end();
template short * c_tag_block<short>::get_element(__int32) const;

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { long assassination_capsule_counter; }
