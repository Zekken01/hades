/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/forge/forge_globals.hpp"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_globals.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/multiplayer_definitions.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/geometry/geometry_definitions.hpp"
#include "Blam/geometry/geometry_sampler.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/color_definitions.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/data_array.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/models/model_definitions.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/objects/multiplayer_game_objects.hpp"
#include "Blam/objects/object_definitions.hpp"
#include "Blam/objects/object_types.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/physics/havok_types.hpp"
#include "Blam/rasterizer/rasterizer_geometry.hpp"
#include "Blam/rasterizer/rasterizer_globals.hpp"
#include "Blam/rasterizer/rasterizer_samplers.hpp"
#include "Blam/rasterizer/rasterizer_states.hpp"
#include "Blam/rasterizer/rasterizers_textures_cache.hpp"
#include "Blam/render/render_globals.hpp"
#include "Blam/render/render_model.hpp"
#include "Blam/render/render_object.hpp"
#include "Blam/render/render_object_globals.hpp"
#include "Blam/render/render_structure.hpp"
#include "Blam/scenario/scenario.hpp"
#include "Blam/shaders/render_method_submit.hpp"
#include "Blam/shaders/render_methods_definitions.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "Blam/visibility/visibility_items.hpp"
#include "Blam/visibility/visibility_object_render_info.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Forge/ForgeObjectProperties.hpp"
#include "Forge/Geoemetry.hpp"
#include "Forge/Reforge.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
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

class c_render_method;
struct real_matrix4x3;
struct real_point3d;
struct real_rgb_color;
struct real_vector3d;
struct s_compression_info;
struct s_forge_globals_definition;
struct s_game_globals;
struct s_geometry_material;
struct s_geometry_sample;
struct s_mesh;
struct s_model_definition;
struct s_multiplayer_globals_definition;
struct s_multiplayer_object_properties;
struct s_object_cached_render_state_datum;
struct s_object_data;
struct s_object_definition;
struct s_object_region_information;
struct s_part;
struct s_render_first_person_model;
struct s_render_geometry;
struct s_render_lighting;
struct s_render_model;
struct s_render_model_permutation;
struct s_render_model_region;
struct s_render_object;
struct s_render_object_info;
struct s_render_object_mesh_part;
struct s_shader_extern_info;
struct s_visible_items;
struct s_visible_object;
struct s_visible_object_hierarchy;
namespace Forge
{
	struct ForgeKillVolumeProperties;
	struct ReforgeObjectProperties;
}
namespace Forge
{
	namespace Reforge
	{
		struct SRenderMaterialParameters;
	}
}

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;
namespace Forge {}
using namespace ::Forge;
namespace Forge
{
	namespace Reforge {}
	using namespace Forge::Reforge;
}

namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace RenderObject {}
	using namespace Patches::RenderObject;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Patches
{
	namespace RenderObject
	{
		extern void ApplyAll();
		extern bool GetPRTDisabled();
	}
}

void render_object_set_shield_impact(long element_index, void *definition);
bool object_should_render(long object_index);
void render_object_add_mesh_parts_hook(s_render_object *render_object, s_visible_object *render_info, long object_entry_point_flags, bool a4, bool has_shield_impact, bool isFpShit, bool camo);
void render_reforge_object_mesh_part(s_render_object_mesh_part *element, long entry_point, long entry_point_flags, bool a4, long material_index, ::Forge::Reforge::SRenderMaterialParameters const &parameters);
long object_get_prt_disabled(long object_index);
void render_object_mesh_part_hook(s_render_object_mesh_part *element, long entry_point, long entry_point_flags, bool a4);
bool object_sh_lightmap_sampling_disabled(long object_index);
long object_lighting_geometry_sample_hook(real_point3d *origin, real_vector3d *direction, __int32 a3, long object_index, char a5, char a6, s_geometry_sample *sample);
s_game_globals *try_and_get_game_globals();
real_rgb_color *network_get_team_color(real_rgb_color *color, long team);
bool object_always_updates_change_colors(long object_index);
void render_object_update_change_colors_hook(long object_index, bool force);
void render_visibility_add_first_person_object_to_items_hook(long output_user_index, long object_index, bool a3, bool a4);

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern bool g_prt_disabled; // 0x124083AC
}
using namespace hades_file_local;
/* ---------- public code */

namespace Patches
{
	namespace RenderObject
	{
		_extern void _sub_108DE300();
		void ApplyAll() // 0x108DE300
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@RenderObject@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_108DE300();
		}
	}
}

_inline s_compression_info::s_compression_info(s_compression_info const &__that) // 0x108DDBA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0s_compression_info@@QAE@ABU0@@Z");
	// s_compression_info const &__that;

	compiler_generated();
}

namespace Patches
{
	namespace RenderObject
	{
		_extern bool _sub_108DEC70();
		bool GetPRTDisabled() // 0x108DEC70
		{
			mangled_x86(MANGLED_TODO, "?GetPRTDisabled@RenderObject@Patches@@YA_NXZ");
			// procedure flags: nofpo
			todo("implement");
			bool __result = _sub_108DEC70();
			return __result;
		}
	}
}

/* ---------- private code */

_extern void _sub_108E06E0(long, void *);
void render_object_set_shield_impact(long element_index, void *definition) // 0x108E06E0
{
	// `anonymous-namespace'::render_object_set_shield_impact
	// void *definition;
	todo("implement");
	_sub_108E06E0(element_index, definition);
}

_extern bool _sub_108DF6D0(long);
bool object_should_render(long object_index) // 0x108DF6D0
{
	// `anonymous-namespace'::object_should_render
	// long object_index;
	// s_object_data *object;
	// bool is_invisible_material;
	// s_forge_globals_definition *forge_globals;
	{
		// s_multiplayer_object_properties *multiplayer_properties;
		// Forge::ForgeKillVolumeProperties *kill_volume_properties;
	}
	{
		// long player_index;
		// bool show_invisibles;
	}
	// function call : bool (*const)()
	// function call : bool (*const)()
	// function call : s_multiplayer_object_properties *(*const)(unsigned long)
	// function call : unsigned long (*const)(long)
	// function call : bool (*const)(long, long *, long *)
	todo("implement");
	bool __result = _sub_108DF6D0(object_index);
	return __result;
}

_extern void _sub_108DF930(s_render_object *, s_visible_object *, long, bool, bool, bool, bool);
void render_object_add_mesh_parts_hook(s_render_object *render_object, s_visible_object *render_info, long object_entry_point_flags, bool a4, bool has_shield_impact, bool isFpShit, bool camo) // 0x108DF930
{
	// `anonymous-namespace'::render_object_add_mesh_parts_hook
	// long object_entry_point_flags;
	// bool a4;
	// bool has_shield_impact;
	// bool isFpShit;
	// bool camo;
	// bool uses_fixed_oreder_transparency;
	// s_geometry_material *materials;
	// s_object_data *object;
	// bool ridiculous_transparency_sort_bias_bit;
	// s_render_model *render_model;
	{
		// __int32 region_index;
		{
			// short sort_index;
			// unsigned char mesh_index;
			// s_mesh *mesh;
			{
				// __int32 part_index;
				{
					// long reforge_material_index;
					// bool uses_z_pre_pass;
					// bool is_decal;
					// bool unknown_transparency_flag;
					// long element_index;
					// s_part *part;
					// bool uses_alpha_blending;
					// c_render_method *render_method;
					// long entry_point_flags;
					// long render_method_index;
					// short material_index;
					{
						// real_point3d sorting_position;
					}
					{
						{
							// void *callback;
							// unsigned char sorting_layer;
							// bool uses_distortion;
						}
						{
							// void *shield_impact;
						}
					}
				}
			}
		}
	}
	// function call : void *(*const)(unsigned long, long)
	// function call : bool (*const)(long)
	// function call : bool (*const)(long)
	// function call : long (*const)(s_render_object *, s_render_object_info *, unsigned long *, short, short, short, short, __int32)
	// function call : long (*const)(void *, void *, long)
	// function call : bool (*const)(long)
	// function call : void (*const)(s_render_geometry *, s_mesh *, s_part *, long, long, void *, __int32, real_point3d *, char, long, long, void *)
	// function call : bool (*const)(long)
	// function call : void (*const)(s_render_geometry *, s_mesh *, s_part *, long, long, void *, __int32, real_point3d *, char, long, long, void *)
	// function call : void (*const)(bool)
	// function call : void (*const)(bool)
	// function call : void (*const)(s_render_geometry *, s_mesh *, s_part *, long, long, void *, __int32, real_point3d *, char, long, long, void *)
	// function call : s_shield_parameters *(*const)(s_object_data *, bool)
	// function call : void (*const)()
	todo("implement");
	_sub_108DF930(render_object, render_info, object_entry_point_flags, a4, has_shield_impact, isFpShit, camo);
}

_extern void _sub_108E0D80(s_render_object_mesh_part *, long, long, bool, long, ::Forge::Reforge::SRenderMaterialParameters const &);
void render_reforge_object_mesh_part(s_render_object_mesh_part *element, long entry_point, long entry_point_flags, bool a4, long material_index, ::Forge::Reforge::SRenderMaterialParameters const &parameters) // 0x108E0D80
{
	// `anonymous-namespace'::render_reforge_object_mesh_part
	// long entry_point_flags;
	// bool a4;
	// long material_index;
	// Forge::Reforge::SRenderMaterialParameters const &parameters;
	// long old_material_index;
	// s_compression_info custom_compression_info;
	// s_part *part;
	// void *old_compression_info_adress;
	// s_mesh *mesh;
	// s_render_model *render_model;
	// function call : void *(*const)(unsigned long, long)
	// function call : void (*const)(s_render_object_mesh_part *, long, long, bool)
	todo("implement");
	_sub_108E0D80(element, entry_point, entry_point_flags, a4, material_index, parameters);
}

_extern long _sub_108DF440(long);
long object_get_prt_disabled(long object_index) // 0x108DF440
{
	// `anonymous-namespace'::object_get_prt_disabled
	// static ...; // 0x108DF520
	// static ...; // 0x108DF514
	// static ...; // 0x108DF50C
	// long object_index;
	// float const k_spartan_scale_threshold;
	// s_object_data *object;
	{
		// c_enum<enum e_object_type,char> object_type;
	}
	// function call : long (*const)(long)
	todo("implement");
	long __result = _sub_108DF440(object_index);
	return __result;
}

_extern void _sub_108E0540(s_render_object_mesh_part *, long, long, bool);
void render_object_mesh_part_hook(s_render_object_mesh_part *element, long entry_point, long entry_point_flags, bool a4) // 0x108E0540
{
	// `anonymous-namespace'::render_object_mesh_part_hook
	// s_render_object_mesh_part *element;
	// long entry_point;
	// long entry_point_flags;
	// bool a4;
	// short reforge_material_index;
	// Forge::Reforge::SRenderMaterialParameters reforgeParameters;
	// function call : void (*const)(s_render_object_mesh_part *, long, long, bool)
	todo("implement");
	_sub_108E0540(element, entry_point, entry_point_flags, a4);
}

_extern bool _sub_108DF640(long);
bool object_sh_lightmap_sampling_disabled(long object_index) // 0x108DF640
{
	// `anonymous-namespace'::object_sh_lightmap_sampling_disabled
	// long object_index;
	todo("implement");
	bool __result = _sub_108DF640(object_index);
	return __result;
}

_extern long _sub_108DF570(real_point3d *, real_vector3d *, __int32, long, char, char, s_geometry_sample *);
long object_lighting_geometry_sample_hook(real_point3d *origin, real_vector3d *direction, __int32 a3, long object_index, char a5, char a6, s_geometry_sample *sample) // 0x108DF570
{
	// `anonymous-namespace'::object_lighting_geometry_sample_hook
	// s_geometry_sample *sample;
	// static __int32 (*`object_lighting_geometry_sample_hook'::`2'::object_sh_lighting)(real_point3d *, real_vector3d *, __int32, long, char, char, void *); // 0x11352E8C
	// function call : __int32 (*)(real_point3d *, real_vector3d *, __int32, long, char, char, void *)
	todo("implement");
	long __result = _sub_108DF570(origin, direction, a3, object_index, a5, a6, sample);
	return __result;
}

extern s_game_globals *_sub_108E1E10();
s_game_globals *try_and_get_game_globals() // 0x108E1E10
{
	// `anonymous-namespace'::try_and_get_game_globals
	// procedure flags: nofpo
	// function call : long (*const)(unsigned long)
	// function call : void *(*const)(unsigned long, long)
	todo("implement");
	s_game_globals * __result = _sub_108E1E10();
	return __result;
}

extern real_rgb_color *_sub_108DF2B0(real_rgb_color *, long);
real_rgb_color *network_get_team_color(real_rgb_color *color, long team) // 0x108DF2B0
{
	// `anonymous-namespace'::network_get_team_color
	// long team;
	// s_game_globals *matg;
	{
		// s_multiplayer_globals_definition *mulg;
	}
	// function call : void *(*const)(unsigned long, long)
	todo("implement");
	real_rgb_color * __result = _sub_108DF2B0(color, team);
	return __result;
}

_extern bool _sub_108DF3C0(long);
bool object_always_updates_change_colors(long object_index) // 0x108DF3C0
{
	// `anonymous-namespace'::object_always_updates_change_colors
	// long object_index;
	// s_multiplayer_object_properties *multiplayer;
	// function call : s_multiplayer_object_properties *(*const)(unsigned long)
	todo("implement");
	bool __result = _sub_108DF3C0(object_index);
	return __result;
}

_extern void _sub_108E0730(long, bool);
void render_object_update_change_colors_hook(long object_index, bool force) // 0x108E0730
{
	// `anonymous-namespace'::render_object_update_change_colors_hook
	// static ...; // 0x108E0C20
	// static ...; // 0x108E0C18
	// long object_index;
	// bool force;
	// s_object_data *object;
	// bool (*const restricted_region_locked_for_current_thread)(long);
	// void (*const object_queue_render_thread_message)(long, long, long);
	// void *(*const object_get_render_data)(long);
	// bool (*const object_get_change_color)(long, long, real_rgb_color *);
	// s_object_definition *object_def;
	// long cached_state_index;
	{
		// c_data_array<s_object_cached_render_state_datum> *cached_states;
		// s_object_cached_render_state_datum *cached_state;
		{
			// __int32 i;
			{
				// real_rgb_color color;
				{
					// s_multiplayer_object_properties *multiplayer;
					// long target_object_index;
					{
						// bool isReforgeObject;
						{
							// Forge::ReforgeObjectProperties *const reforge;
						}
						{
							// unsigned char *custom_change_colors;
						}
					}
				}
			}
		}
	}
	// function call : bool (*const)(long)
	// function call : void (*const)(long, long, long)
	// function call : void *(*const)(unsigned long, long)
	// function call : void *(*const)(long)
	// function call : bool (*const)(long, long, real_rgb_color *)
	// function call : long (*const)(long)
	// function call : s_multiplayer_object_properties *(*const)(unsigned long)
	// function call : s_multiplayer_object_properties *(*const)(unsigned long)
	// function call : unsigned long (*const)(real_rgb_color *)
	todo("implement");
	_sub_108E0730(object_index, force);
}

_extern void _sub_108E1010(long, long, bool, bool);
void render_visibility_add_first_person_object_to_items_hook(long output_user_index, long object_index, bool a3, bool a4) // 0x108E1010
{
	// `anonymous-namespace'::render_visibility_add_first_person_object_to_items_hook
	// static ...; // 0x108E1A3C
	// long output_user_index;
	// long object_index;
	// bool a3;
	// bool a4;
	// bool (*const render_object_first_person_globals_valid)();
	// void *(*const c_render_frame_memory__get)(long);
	// long (*const render_model_get_skinning_matrix_count)(long, long, unsigned char const *);
	// long old_objects_count;
	// long old_hierarchy_count;
	// long new_hierarchy_index;
	// long (*const c_object_renderer_submit_object_attachments)(long, long);
	// s_render_lighting *(*const object_update_cached_render_lighting)(long, float);
	// void (*const render_object_get_object_values)(long, s_render_object_info *);
	// long (*const c_render_frame_memory__allocate)(long, __int32, long);
	// void (*const render_model_build_skinning)(long, long, real_matrix4x3 *, unsigned char *, long, char, __int32, void *);
	// s_render_lighting *lighting;
	// void (*const object_get_region_information)(long, long *, char **, char **, s_object_region_information **);
	// long (*const render_model_compute_skinning_size_in_bytes)(long);
	// bool added_successfully;
	// void (*const object_visibility_new)(s_visible_object *);
	// s_visible_items &visible_items;
	{
		// s_visible_object_hierarchy &new_hierarchy;
		// __int32 count;
		{
			// __int32 i;
			{
				// s_object_data *object;
				// long new_render_visibility_index;
				// long unit_region_count;
				// s_render_first_person_model &first_person_model;
				// s_object_definition *object_def;
				// char *unit_region_permutation_indices;
				// bool v29;
				// s_render_model *render_model;
				// s_visible_object &new_render_visibility;
				// long skinning_size;
				{
					// __int32 j;
					{
						// s_render_model_region &region;
					}
				}
				{
					// s_model_definition *tp_model;
					// s_object_data *tp_object;
					// s_render_model *tp_render_model;
					// s_object_definition *tp_object_def;
					{
						// __int32 j;
						{
							// s_render_model_permutation &permutation;
							// char permutation_index;
							// s_render_model_region &region;
							{
								// __int32 k;
								{
									// s_render_model_region &target_region;
									{
										// __int32 l;
										{
											// s_render_model_permutation &target_permutation;
										}
									}
								}
							}
						}
					}
				}
				{
					// void *skinning;
				}
			}
		}
	}
	// function call : bool (*const)()
	// function call : s_render_lighting *(*const)(long, float)
	// function call : void *(*const)(unsigned long, long)
	// function call : long (*const)(long, long)
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void *(*const)(unsigned long, long)
	// function call : void *(*const)(unsigned long, long)
	// function call : void (*const)(s_visible_object *)
	// function call : void (*const)(long, long *, char **, char **, s_object_region_information **)
	// function call : void *(*const)(unsigned long, long)
	// function call : void *(*const)(unsigned long, long)
	// function call : void *(*const)(unsigned long, long)
	// function call : long (*const)(long, long, unsigned char const *)
	// function call : long (*const)(long)
	// function call : long (*const)(long, __int32, long)
	// function call : void *(*const)(long)
	// function call : void (*const)(long, long, real_matrix4x3 *, unsigned char *, long, char, __int32, void *)
	// function call : s_shader_extern_info *(*const)(long)
	// function call : void (*const)(long, s_render_object_info *)
	todo("implement");
	_sub_108E1010(output_user_index, object_index, a3, a4);
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_enum<enum e_alpha_blend_mode,int>::operator!=(__int32 const &) const;
template bool c_enum<enum e_alpha_blend_mode,int>::operator==(__int32 const &) const;
template bool c_enum<enum e_multiplayer_object_type,char>::operator==(e_multiplayer_object_type const &) const;
template bool c_enum<enum e_part_type,char>::operator==(e_part_type const &) const;
template bool c_enum<enum e_vertex_type,char>::operator==(e_vertex_type const &) const;
template bool c_flags<enum e_mesh_flags,unsigned char>::test(e_mesh_flags) const;
template bool c_flags<enum e_multiplayer_team_designator,short>::operator<(e_multiplayer_team_designator const &) const;
template bool c_flags<enum e_multiplayer_team_designator,short>::operator>=(e_multiplayer_team_designator const &) const;
template bool c_flags<enum e_render_method_flags,short>::test(e_render_method_flags) const;
template bool c_tag_block<s_compression_info>::try_get_element(__int32, s_compression_info **) const;
template bool c_tag_block<s_multiplayer_team_color>::try_get_element(__int32, s_multiplayer_team_color **) const;
template bool c_tag_block<s_part>::try_get_element(__int32, s_part **) const;
template bool c_tag_block<s_render_method_postprocess_definition>::try_get_element(__int32, s_render_method_postprocess_definition **) const;
template bool c_tag_block<s_render_model_permutation>::try_get_element(__int32, s_render_model_permutation **) const;
template bool c_tag_block<s_render_model_region>::try_get_element(__int32, s_render_model_region **) const;
template bool c_tag_block<s_sorting_position>::try_get_element(__int32, s_sorting_position **) const;
template c_enum<enum e_object_definition_runtime_flags,long> c_enum<enum e_object_definition_runtime_flags,long>::operator&(__int32 const) const;
template c_enum<enum e_object_definition_runtime_flags,long>::c_enum(long const &);
template c_enum<enum e_object_definition_runtime_flags,long>::operator bool() const;
template c_enum<enum e_object_type,char>::c_enum(c_enum<enum e_object_type,char> const &);
template c_enum<enum e_object_type,char>::c_enum(char const &);
template c_enum<enum e_sorting_layer,char>::operator char() const;
template c_flags<enum e_compression_info_flags,unsigned short>::c_flags(c_flags<enum e_compression_info_flags,unsigned short> const &);
template c_flags<enum e_compression_info_flags,unsigned short>::c_flags(unsigned short const &);
template long s_simple_list<s_visible_object,1792>::add();
template long s_simple_list<s_visible_object_hierarchy,1536>::add();
template s_compression_info & c_tag_block<s_compression_info>::operator[](__int32);
template s_compression_info * c_tag_block<s_compression_info>::get_element(__int32) const;
template s_multiplayer_team_color & c_tag_block<s_multiplayer_team_color>::operator[](__int32);
template s_multiplayer_team_color * c_tag_block<s_multiplayer_team_color>::get_element(__int32) const;
template s_object_cached_render_state_datum * c_data_array<s_object_cached_render_state_datum>::try_and_get(unsigned long);
template s_part & c_tag_block<s_part>::operator[](__int32);
template s_part * c_tag_block<s_part>::get_element(__int32) const;
template s_render_method_postprocess_definition * c_tag_block<s_render_method_postprocess_definition>::get_element(__int32) const;
template s_render_method_postprocess_definition * c_tag_block<s_render_method_postprocess_definition>::operator->();
template s_render_model_permutation & c_tag_block<s_render_model_permutation>::operator[](__int32);
template s_render_model_permutation * c_tag_block<s_render_model_permutation>::get_element(__int32) const;
template s_render_model_permutation * c_tag_block<s_render_model_permutation>::operator->();
template s_render_model_region & c_tag_block<s_render_model_region>::operator[](__int32);
template s_render_model_region * c_tag_block<s_render_model_region>::get_element(__int32) const;
template s_sorting_position & c_tag_block<s_sorting_position>::operator[](__int32);
template s_sorting_position * c_tag_block<s_sorting_position>::get_element(__int32) const;
