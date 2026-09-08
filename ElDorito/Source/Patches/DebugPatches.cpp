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
		_extern void _sub_108C8D00(char const *);
		void OnMapLoaded(char const *mapPath) // 0x108C8D00
		{
			mangled_x86(MANGLED_TODO, "?OnMapLoaded@Debug@Patches@@YAXPBD@Z");
			// char const *mapPath;
			todo("implement");
			_sub_108C8D00(mapPath);
		}

		_extern void _sub_108C76E0();
		void ApplyAll() // 0x108C76E0
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@Debug@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_108C76E0();
		}

		_extern void _sub_108C9470();
		void Tick() // 0x108C9470
		{
			mangled_x86(MANGLED_TODO, "?Tick@Debug@Patches@@YAXXZ");
			// procedure flags: nofpo
			// function call : bool (*const)()
			todo("implement");
			_sub_108C9470();
		}

		_extern void _sub_108C9370();
		void RenderPlayerView() // 0x108C9370
		{
			mangled_x86(MANGLED_TODO, "?RenderPlayerView@Debug@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_108C9370();
		}
	}
}

/* ---------- private code */

_extern void _sub_108C94D0();
_inline void CRenderDebugCollisionTest::Update() // 0x108C94D0
{
	// `anonymous-namespace'::CRenderDebugCollisionTest::Update
	// procedure flags: nofpo
	todo("implement");
	_sub_108C94D0();
}

_extern void _sub_108C95C0();
_inline void CRenderDebugCollisionTest::UpdateInternal() // 0x108C95C0
{
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
	{
		// std::scoped_lock<std::mutex> lock;
	}
	// function call : unsigned long (*const)(long)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void (*const)(long, real_point3d *)
	// function call : bool (*const)(unsigned long, unsigned long, real_point3d const &, real_vector3d const &, long, long, s_collision_result *)
	todo("implement");
	_sub_108C95C0();
}

_extern void _sub_108C9010();
_inline void CRenderDebugCollisionTest::Render() // 0x108C9010
{
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
	{
		// std::scoped_lock<std::mutex> lock;
	}
	// function call : void (*const)(short_rectangle2d *, short_rectangle2d *, short_rectangle2d *, short_rectangle2d *)
	todo("implement");
	_sub_108C9010();
}

extern std::string _sub_108C7FA0(s_collision_result const &);
_inline std::string CRenderDebugCollisionTest::GetHitDescription(s_collision_result const &hit) // 0x108C7FA0
{
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
	{
		// s_object_data *object;
		{
			// real_vector3d forward;
			// real_vector3d up;
		}
	}
	{
		// s_structure_collision_material *collisionMaterial;
		{
			// s_geometry_material *renderMaterial;
		}
	}
	{
		// s_global_material_definition *global_material;
		{
			// char *material_name;
		}
	}
	// function call : void (*const)(long, real_point3d *)
	// function call : void (*const)(long, real_vector3d *, real_vector3d *)
	// function call : unsigned long (*const)(long)
	// function call : void (*const)(long, real_point3d *)
	// function call : s_scenario_structure_bsp *(*const)(long)
	// function call : long (*const)(long, __int32, long, long)
	// function call : s_scenario_structure_bsp *(*const)(long)
	// function call : s_global_material_definition *(*const)(short)
	todo("implement");
	std::string __result = _sub_108C7FA0(hit);
	return __result;
}

extern std::string _sub_108C7E20(long);
_inline std::string CRenderDebugCollisionTest::GetFriendlyTagName(long tagindex) // 0x108C7E20
{
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
	todo("implement");
	std::string __result = _sub_108C7E20(tagindex);
	return __result;
}

_extern void _sub_108C93D0();
_inline void CRenderDebugCollisionTest::ResetForNewMap() // 0x108C93D0
{
	// `anonymous-namespace'::CRenderDebugCollisionTest::ResetForNewMap
	// procedure flags: nofpo
	// static ...; // 0x108C9440
	// static ...; // 0x108C9434
	// static ...; // 0x108C942C
	// std::scoped_lock<std::mutex> lock;
	todo("implement");
	_sub_108C93D0();
}

_extern void _sub_108C7C00();
void DisplayClusters() // 0x108C7C00
{
	// `anonymous-namespace'::DisplayClusters
	// procedure flags: nofpo
	// static ...; // 0x108C7DA0
	// static ...; // 0x108C7D94
	// static ...; // 0x108C7D8C
	// s_observer_result *camera;
	// s_cluster_reference cluster;
	// void (*const scenario_location_from_point)(s_cluster_reference *, real_point3d *);
	{
		// s_scenario_structure_bsp *sbsp;
		{
			// __int32 i;
		}
	}
	// function call : s_observer_result *(*const)(long)
	// function call : void (*const)(s_cluster_reference *, real_point3d *)
	// function call : s_scenario_structure_bsp *(*const)(long)
	todo("implement");
	_sub_108C7C00();
}

_extern void _sub_108CAE30();
void render_d3d_resource_tracker() // 0x108CAE30
{
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
	{
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
	}
	// function call : void (*const)(short_rectangle2d *, short_rectangle2d *, short_rectangle2d *, short_rectangle2d *)
	todo("implement");
	_sub_108CAE30();
}

_extern void _sub_108CCC50(s_physics_model_instance const *, real_argb_color const *);
void render_debug_physics_model(s_physics_model_instance const *instance, real_argb_color const *color) // 0x108CCC50
{
	// `anonymous-namespace'::render_debug_physics_model
	// static ...; // 0x108CCF18
	// static ...; // 0x108CCF10
	// s_physics_model_instance const *instance;
	// real_argb_color const *color;
	// s_object_data *object;
	// s_object_definition *object_def;
	{
		// long runtime_region_index;
		{
			// char runtime_permutation_index;
			// s_model_permutation *runtime_permutation;
			// s_model_region *runtime_region;
			// s_physics_model_permutation *physics_model_permutation;
			// s_physics_model_region *physics_model_region;
			{
				// c_tag_block<short> &<range>$L0;
				// short *<begin>$L0;
				// short *<end>$L0;
				{
					// long rigid_body_index;
					{
						// real_matrix4x3 const *node_matrix;
						// real_point3d center_of_mass;
						// s_physics_model_rigid_body *rigid_body;
					}
				}
			}
		}
	}
	// function call : void *(*const)(unsigned long, long)
	todo("implement");
	_sub_108CCC50(instance, color);
}

_extern void _sub_108CB2E0(collision_bsp const *, long, real_matrix4x3 const *, long);
void render_debug_collision_edge(collision_bsp const *bsp, long index, real_matrix4x3 const *matrix, long color) // 0x108CB2E0
{
	// `anonymous-namespace'::render_debug_collision_edge
	// static ...; // 0x108CB3F4
	// collision_bsp const *bsp;
	// long index;
	// real_matrix4x3 const *matrix;
	// long color;
	// real_point3d p2;
	// real_point3d p1;
	// collision_edge const &edge;
	todo("implement");
	_sub_108CB2E0(bsp, index, matrix, color);
}

_extern void _sub_108CBF90(s_large_collision_bsp const *, long, real_matrix4x3 const *, long);
void render_debug_large_collision_edge(s_large_collision_bsp const *bsp, long index, real_matrix4x3 const *matrix, long color) // 0x108CBF90
{
	// `anonymous-namespace'::render_debug_large_collision_edge
	// static ...; // 0x108CC0A4
	// s_large_collision_bsp const *bsp;
	// long index;
	// real_matrix4x3 const *matrix;
	// long color;
	// real_point3d p2;
	// real_point3d p1;
	// s_large_collision_edge const &edge;
	todo("implement");
	_sub_108CBF90(bsp, index, matrix, color);
}

_extern void _sub_108CB260(collision_bsp const *, real_matrix4x3 const *, unsigned long);
void render_debug_collision_bsp(collision_bsp const *bsp, real_matrix4x3 const *matrix, unsigned long color) // 0x108CB260
{
	// `anonymous-namespace'::render_debug_collision_bsp
	// unsigned long color;
	{
		// long i;
	}
	todo("implement");
	_sub_108CB260(bsp, matrix, color);
}

_extern void _sub_108CBF10(s_large_collision_bsp const *, real_matrix4x3 const *, unsigned long);
void render_debug_large_collision_bsp(s_large_collision_bsp const *bsp, real_matrix4x3 const *matrix, unsigned long color) // 0x108CBF10
{
	// `anonymous-namespace'::render_debug_large_collision_bsp
	// unsigned long color;
	{
		// long i;
	}
	todo("implement");
	_sub_108CBF10(bsp, matrix, color);
}

_extern void _sub_108CB470(collision_model_instance const *);
void render_debug_collision_model(collision_model_instance const *instance) // 0x108CB470
{
	// `anonymous-namespace'::render_debug_collision_model
	// static ...; // 0x108CB550
	// static ...; // 0x108CB544
	// static ...; // 0x108CB53C
	// collision_model_instance const *instance;
	// s_collision_model_bsp_iterator iterator;
	{
		// unsigned char node_index;
	}
	// function call : void (*const)(s_collision_model_bsp_iterator *, model_definition const *, collision_model_definition const *, unsigned char const *)
	// function call : bool (*const)(s_collision_model_bsp_iterator *)
	todo("implement");
	_sub_108CB470(instance);
}

_extern void _sub_108CC380(long);
void render_debug_object_markers(long object_index) // 0x108CC380
{
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
	{
		// long i;
		{
			// unsigned long color;
			// float r;
			// float g;
			// s_render_model_marker_group &marker_group;
			// float b;
			// char *group_name;
			// short marker_count;
			// float theta;
			{
				// __int32 j;
			}
		}
	}
	// function call : void *(*const)(unsigned long, long)
	// function call : void *(*const)(unsigned long, long)
	// function call : void *(*const)(unsigned long, long)
	// function call : unsigned long (*const)(real_argb_color const &)
	// function call : short (*const)(long, unsigned long, s_object_marker *, short)
	todo("implement");
	_sub_108CC380(object_index);
}

_extern void _sub_108CC120(long);
void render_debug_object(long object_index) // 0x108CC120
{
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
	{
		// collision_model_instance instance;
	}
	{
		// s_physics_model_instance instance;
		{
			// real_argb_color color;
		}
	}
	// function call : void (*const)(long, real_point3d *)
	// function call : bool (*const)(collision_model_instance *, long)
	// function call : bool (*const)(s_physics_model_instance *, long)
	todo("implement");
	_sub_108CC120(object_index);
}

_extern void _sub_108CCB60();
void render_debug_objects() // 0x108CCB60
{
	// `anonymous-namespace'::render_debug_objects
	// procedure flags: nofpo
	// short starting_index;
	// s_visible_items *visible_items;
	{
		// __int32 i;
		{
			// s_visible_object_hierarchy &object_hierarchy;
			{
				// __int32 j;
			}
		}
	}
	todo("implement");
	_sub_108CCB60();
}

_extern void _sub_108CBEB0();
void render_debug_frame_render() // 0x108CBEB0
{
	// `anonymous-namespace'::render_debug_frame_render
	// procedure flags: nofpo
	todo("implement");
	_sub_108CBEB0();
}

_extern void _sub_108CB5A0(s_damage_data const *, float);
void render_debug_damage_submit(s_damage_data const *data, float radius) // 0x108CB5A0
{
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
	todo("implement");
	_sub_108CB5A0(data, radius);
}

_extern short _sub_108C9980(long, long, s_cluster_reference *, real_point3d const *, float, long *, short);
short area_of_effect_cause_damage_objects_in_sphere_hook(long flags, long object_mask, s_cluster_reference *cluster, real_point3d const *center, float radius, long *objects, short max_objects) // 0x108C9980
{
	// `anonymous-namespace'::area_of_effect_cause_damage_objects_in_sphere_hook
	// short max_objects;
	// short num_objects;
	{
		// s_damage_data *damage_data;
	}
	// function call : short (*const)(long, long, s_cluster_reference const *, real_point3d const *, float, long *, short)
	todo("implement");
	short __result = _sub_108C9980(flags, object_mask, cluster, center, radius, objects, max_objects);
	return __result;
}

_extern void _sub_108CD2F0(s_scenario_trigger_volume *, long);
void render_debug_trigger_volume(s_scenario_trigger_volume *volume, long color) // 0x108CD2F0
{
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
	todo("implement");
	_sub_108CD2F0(volume, color);
}

_extern void _sub_108CD6E0();
void render_debug_trigger_volumes() // 0x108CD6E0
{
	// `anonymous-namespace'::render_debug_trigger_volumes
	// procedure flags: nofpo
	// static ...; // 0x108CDAB4
	// static ...; // 0x108CDAAE
	// static ...; // 0x108CDAA8
	// static ...; // 0x108CDAA2
	// static ...; // 0x108CDAA0
	// static ...; // 0x108CDA64
	// static ...; // 0x108CDA5C
	// std::vector<short,std::allocator<short> > usedIndices;
	// s_scenario *scenario;
	{
		// long i;
		{
			// short index;
		}
	}
	{
		{
		}
	}
	{
		{
		}
	}
	{
	}
	todo("implement");
	_sub_108CD6E0();
}

_extern void _sub_108CD090(long);
void render_debug_structure_bsp(long bsp_index) // 0x108CD090
{
	// `anonymous-namespace'::render_debug_structure_bsp
	// long bsp_index;
	// s_scenario_structure_bsp *structure_bsp;
	// s_structure_bsp_resources *bsp_resources;
	{
		// c_tag_block<collision_bsp> &<range>$L0;
		// collision_bsp *<begin>$L0;
		// collision_bsp *<end>$L0;
		{
			// collision_bsp const &bsp;
		}
	}
	{
		// s_large_collision_bsp *<end>$L1;
		// s_large_collision_bsp *<begin>$L1;
		// c_tag_block<s_large_collision_bsp> &<range>$L1;
		{
			// s_large_collision_bsp const &bsp;
		}
	}
	{
		// long i;
		{
			// s_structure_instanced_geometry_instance *const instance;
			// s_structure_instanced_geometry_definition *const definition;
		}
	}
	// function call : s_scenario_structure_bsp *(*const)(long)
	// function call : void *(*const)(void *)
	todo("implement");
	_sub_108CD090(bsp_index);
}

_extern void _sub_108CCFF0();
void render_debug_structure() // 0x108CCFF0
{
	// `anonymous-namespace'::render_debug_structure
	// procedure flags: nofpo
	// long bsp_index;
	// function call : long (*const)()
	// function call : long (*const)(long)
	todo("implement");
	_sub_108CCFF0();
}

_extern void _sub_108C9EF0(char const *, hkpCapsuleShape const *, real_matrix4x3 const *, long);
void draw_assassination_capsule(char const *key, hkpCapsuleShape const *shape, real_matrix4x3 const *transform, long color) // 0x108C9EF0
{
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
	todo("implement");
	_sub_108C9EF0(key, shape, transform, color);
}

_extern bool _sub_108CAC70(hkpShape const *, long, real_matrix4x3 const *, long);
bool havok_world_shape_collides_hook_initiator(hkpShape const *shape, long unknown, real_matrix4x3 const *transform, long havok_group) // 0x108CAC70
{
	// `anonymous-namespace'::havok_world_shape_collides_hook_initiator
	// long havok_group;
	// bool (*havok_world_shape_collides)(hkpShape const *, long, real_matrix4x3 const *, long);
	// function call : bool (*)(hkpShape const *, long, real_matrix4x3 const *, long)
	todo("implement");
	bool __result = _sub_108CAC70(shape, unknown, transform, havok_group);
	return __result;
}

_extern bool _sub_108CAD50(hkpShape const *, long, real_matrix4x3 const *, long);
bool havok_world_shape_collides_hook_target(hkpShape const *shape, long unknown, real_matrix4x3 const *transform, long havok_group) // 0x108CAD50
{
	// `anonymous-namespace'::havok_world_shape_collides_hook_target
	// long havok_group;
	// bool (*havok_world_shape_collides)(hkpShape const *, long, real_matrix4x3 const *, long);
	// function call : bool (*)(hkpShape const *, long, real_matrix4x3 const *, long)
	todo("implement");
	bool __result = _sub_108CAD50(shape, unknown, transform, havok_group);
	return __result;
}

_extern bool _sub_108C9A50(long, float, float, real_point3d const *, bool, float *);
bool assassination_sync_action_point_on_slope_or_falls_hook(long object_index, float height_standing, float physics_radius, real_point3d const *action_point, bool allow_success, float *out_slope_offset) // 0x108C9A50
{
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
	{
		// real_point3d world_collision_point;
		// CDebugDraw draw;
	}
	// function call : bool (*)(long long, bool, real_point3d *, real_point3d *, __int32, __int32, __int32, s_collision_result *)
	todo("implement");
	bool __result = _sub_108C9A50(object_index, height_standing, physics_radius, action_point, allow_success, out_slope_offset);
	return __result;
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
