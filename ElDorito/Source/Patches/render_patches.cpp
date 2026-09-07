/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/effects/screen_effect.hpp"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/data_array.inl"
#include "Blam/memory/static_array.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/networking/session/network_session_membership.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/physics/havok_types.hpp"
#include "Blam/rasterizer/rasterizer.hpp"
#include "Blam/rasterizer/rasterizer_geometry.hpp"
#include "Blam/rasterizer/rasterizer_globals.hpp"
#include "Blam/rasterizer/rasterizer_samplers.hpp"
#include "Blam/rasterizer/rasterizer_shaders.hpp"
#include "Blam/rasterizer/rasterizer_states.hpp"
#include "Blam/rasterizer/rasterizers_textures_cache.hpp"
#include "Blam/render/camera_fx_settings.hpp"
#include "Blam/render/render_globals.hpp"
#include "Blam/render/render_structure.hpp"
#include "Blam/render/screen_postprocess.hpp"
#include "Blam/render/view.hpp"
#include "Blam/render/views/render_player_view.hpp"
#include "Blam/scenario/scenario.hpp"
#include "Blam/shaders/render_method_extern.hpp"
#include "Blam/shaders/render_method_submit.hpp"
#include "Blam/shaders/render_method_template_definitions.hpp"
#include "Blam/shaders/render_methods_definitions.hpp"
#include "Blam/sky_atm/atmosphere.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "Blam/visibility/visibility_items.hpp"
#include "Blam/widgets/muffin_definitions.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Forge/ForgeVisionRenderer.hpp"
#include "Forge/Geoemetry.hpp"
#include "Modules/ModuleSettings.hpp"
#include "Patch.hpp"
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
#include <memory>
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

class c_rasterizer_globals;
struct c_player_view;
struct c_rasterizer;
struct c_rasterizer_texture_ref;
struct c_render_method_data;
struct c_screen_postprocess;
struct real_point3d;
struct s_decorator_set;
struct s_extern_description;
struct s_muffin_definition;
struct s_rasterizer_globals;
struct s_weighted_atmosphere_parameters;
struct s_wind_definition;
struct s_wind_values;
namespace Modules
{
	class ModuleSettings;
}

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;
namespace Player {}
using namespace ::Player;
namespace Forge {}
using namespace ::Forge;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Debug {}
	using namespace Patches::Debug;
	namespace RenderObject {}
	using namespace Patches::RenderObject;
}

namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Cache {}
	using namespace Blam::Cache;
}

/* ---------- constants */

/* ---------- definitions */

typedef float order_2_sh[9];
typedef float order_1_sh[4];
typedef float order_5_sh[36];
typedef __int32 S32;
typedef unsigned __int32 U32;

/* ---------- prototypes */

extern void render_patches_apply();
extern void render_patches_set_customization_biped(std::vector<int,std::allocator<int> > characterBipeds);
extern void render_patches_tick();

/* ---------- globals */

float c_player_view::render_debug_depth_render_alpha; // 0x11352F68
void (*s_wind_definition::update)(s_wind_definition *, s_wind_values *); // 0x11352F74
s_wind_definition *(*s_wind_definition::get_wind_definition)(real_point3d *); // 0x11352F78
s_decorator_set *(*s_decorator_set::get)(long); // 0x11352F7C
long (*s_decorator_set::get_explicit_shader_index)(s_decorator_set *); // 0x11352F80
unsigned long *c_render_method_data::m_change_colors; // 0x11352F34
void (*c_rasterizer_globals::get_default_texture_rasterizer_texture_ref)(s_rasterizer_globals *, c_rasterizer_texture_ref *, c_enum<enum e_rasterizer_default_bitmap,long>); // 0x11352F3C
long *c_rasterizer::g_color_surfaces; // 0x11352F48
s_muffin_definition *(*s_muffin_definition::get)(long); // 0x11352F6C

/* ---------- private variables */

namespace
{
	extern float &k_camera_field_of_view_default; // 0x11352ED4
	extern s_extern_description const g_new_extern_descriptions[55]; // 0x11195C80
	extern s_wind_values &g_wind_values; // 0x11352EDC
	extern bool &g_invalidate_render_cache; // 0x11352ED8
	extern __int32 *g_bink_frame_width; // 0x11352EE0
	extern __int32 *g_bink_frame_height; // 0x11352EE4
	extern std::vector<int,std::allocator<int> > customization_biped_index_array; // 0x124083B0
	extern float g_lod_distance_scale; // 0x11352EE8
	extern float g_decorator_distance_scale; // 0x11352EEC
	extern bool &render_static_lighting_enabled; // 0x11352EF0
	extern bool &byte_191C922; // 0x11352EF4
	extern float &c_camera_fx_values__g_HDR_target_stops; // 0x11352EF8
	extern c_screen_postprocess::s_settings &c_screen_postprocess__x_settings; // 0x11352EFC
	extern long &c_surface__g_current_splitscreen_res; // 0x11352F00
	extern s_weighted_atmosphere_parameters &g_atmosphere_parameters; // 0x11352F04
	extern float &g_particle_hack_near_fade_scale; // 0x11352F08
	extern long &render_debug_depth_render; // 0x11352F0C
	extern bool &render_dynamic_shadow_enabled; // 0x11352F10
	extern bool &render_water_interaction_enabled; // 0x11352F14
	extern bool &render_water_wireframe_enabled; // 0x11352F18
}
/* ---------- public code */

_extern void _sub_108F1E10();
void render_patches_apply() // 0x108F1E10
{
	mangled_x86(MANGLED_TODO, "?render_patches_apply@@YAXXZ");
	// procedure flags: nofpo
	todo("implement");
	_sub_108F1E10();
}

_extern void _sub_108F5A80(std::vector<int,std::allocator<int> >);
void render_patches_set_customization_biped(std::vector<int,std::allocator<int> > characterBipeds) // 0x108F5A80
{
	mangled_x86(MANGLED_TODO, "?render_patches_set_customization_biped@@YAXV?$vector@HV?$allocator@H@std@@@std@@@Z");
	// std::vector<int,std::allocator<int> > characterBipeds;
	todo("implement");
	_sub_108F5A80(characterBipeds);
}

_extern void _sub_108F5B20();
void render_patches_tick() // 0x108F5B20
{
	mangled_x86(MANGLED_TODO, "?render_patches_tick@@YAXXZ");
	// procedure flags: nofpo
	// Modules::ModuleSettings const &settingsModule;
	todo("implement");
	_sub_108F5B20();
}

/* ---------- private code */
