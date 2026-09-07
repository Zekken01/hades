/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/effects/contrails.hpp"
#include "Blam/effects/effect_definitions.hpp"
#include "Blam/effects/effects.hpp"
#include "Blam/effects/particle.hpp"
#include "Blam/effects/particle_emitter.hpp"
#include "Blam/effects/particle_emitter_definitions.hpp"
#include "Blam/effects/particle_states.hpp"
#include "Blam/effects/particle_system.hpp"
#include "Blam/effects/screen_effect.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/data.hpp"
#include "Blam/memory/data_array.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/rasterizer/rasterizer.hpp"
#include "Blam/rasterizer/rasterizer_geometry.hpp"
#include "Blam/rasterizer/rasterizer_samplers.hpp"
#include "Blam/rasterizer/rasterizer_shaders.hpp"
#include "Blam/rasterizer/rasterizer_states.hpp"
#include "Blam/rasterizer/rasterizers_textures_cache.hpp"
#include "Blam/render/render_lens_flares.hpp"
#include "Blam/shaders/render_method_submit.hpp"
#include "Blam/shaders/render_methods_definitions.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "mods/mod_package_updater.hpp"
#include "Modules/ModuleGraphics.hpp"
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
#include <string>
#include <system_error>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

class c_rasterizer_vertex_buffer;
class c_render_method;
struct c_editable_property;
struct c_particle;
struct c_particle_emitter;
struct c_particle_system;
struct real_matrix4x3;
struct real_point3d;
struct real_vector3d;
struct real_vector4d;
struct s_contrail_gpu_datum;
struct s_contrail_gpu_row;
struct s_contrail_instance;
struct s_contrail_location;
struct s_contrail_states;
struct s_contrail_system;
struct s_contrail_system_definition;
struct s_data_array;
struct s_effect;
struct s_effect_datum;
struct s_effect_event;
struct s_effect_event_datum;
struct s_effect_event_part;
struct s_effect_location_datum;
struct s_effect_message;
struct s_lens_flare_definition;
struct s_particle_system_emitter;
struct s_tag_block;
struct tls_data;
namespace Modules
{
	class ModuleGraphics;
}
namespace hades_file_local
{
	struct s_gpu_vertex_stream;
}
using namespace hades_file_local;

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;

/* ---------- constants */

/* ---------- definitions */

namespace hades_file_local
{
	struct s_gpu_vertex_stream
	{
		void *vertex_data; // 0x0
		unsigned char __pad0[4]; // 0x4
		long offset; // 0x8
		long previous_offset; // 0xC
		long vertex_count; // 0x10
	};
	static_assert(sizeof(s_gpu_vertex_stream) == 20, "Invalid s_gpu_vertex_stream size");
}
using namespace hades_file_local;
//struct render_visible_decals_hook::__l2::c_decal
//{
//	short identifier; // 0x0
//	long parent_system_block_index; // 0x4
//	long parent_system_index; // 0x8
//	long next_index; // 0xC
//};
//static_assert(sizeof(render_visible_decals_hook::__l2::c_decal) == 16, "Invalid render_visible_decals_hook::__l2::c_decal size");

//struct render_visible_decals_hook::__l2::s_render_decal_unknown
//{
//	render_visible_decals_hook::__l2::c_decal *decals[600]; // 0x0
//	long decal_count; // 0x960
//};
//static_assert(sizeof(render_visible_decals_hook::__l2::s_render_decal_unknown) == 2420, "Invalid render_visible_decals_hook::__l2::s_render_decal_unknown size");

/* ---------- prototypes */

extern void effect_system_patches_apply();
extern void effect_system_patches_tick();

void c_contrail_gpu__render_hook(s_contrail_gpu_datum *gpu_datum, void *unused, s_contrail_states *states);
void gpu_vertex_stream_submit(c_rasterizer_vertex_buffer *vertex_buffer, s_gpu_vertex_stream *stream);
void beam_gpu_vertex_stream_submit_hook();
void contrail_gpu_vertex_stream_submit_hook();
void light_volume_gpu_vertex_stream_submit_hook();
void particle_emitter_gpu_vertex_stream_submit_hook();
void event_add_particle_system_location_hook(s_effect_message *message);
void render_visible_decals_hook(long pass);
void c_effect_messaging_queue__post_message_hook(void *queue, void *unused, s_effect_message const *message);
void set_effect_message_filter(e_effect_message_type type, bool filtered);
void s_gpu_storage_2x16un__pack_call_hook(char *buffer_dblptr, real_vector4d *data);
void s_gpu_storage_2x16un__unpack_call_hook(char *buffer_dblptr, real_vector4d *data);
bool lens_flare_is_constant(s_effect_event const *event_definition);
void effect_render(unsigned long effect_index, long output_user_index);
void c_particle_emitter_definition__initialize_particle_initial(s_particle_system_emitter *_this, void *state_list, c_particle *particle, c_particle_emitter *emitter, c_particle_system *system);
_inline void initialize_particle_cube(s_particle_system_emitter *_this, void *state_list, c_particle *particle, c_particle_emitter *emitter, c_particle_system *system);
_inline void initialize_particle_cylinder(s_particle_system_emitter *_this, void *state_list, c_particle *particle, c_particle_emitter *emitter, c_particle_system *system);
_inline void initialize_particle_unweighted_line(s_particle_system_emitter *_this, void *state_list, c_particle *particle, c_particle_emitter *emitter, c_particle_system *system);
_inline void initialize_particle_planar_orbit(s_particle_system_emitter *_this, void *state_list, c_particle *particle, c_particle_emitter *emitter, c_particle_system *system);
_inline void initialize_particle_sphere_orbit(s_particle_system_emitter *_this, void *state_list, c_particle *particle, c_particle_emitter *emitter, c_particle_system *system);
void c_particle_emitter_definition__initialize_particle_call_hook(s_particle_system_emitter *_this, void *_, void *particle_state_list, c_particle *particle, c_particle_emitter *emitter, c_particle_system *system, void *particle_movement_definition);

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern c_flags<enum e_effect_message_type,unsigned long> g_effect_message_filter; // 0x1240936C
	extern real_vector3d global_zero3d; // 0x111978AC
}
using namespace hades_file_local;
/* ---------- public code */

_extern void _sub_10911EE0();
void effect_system_patches_apply() // 0x10911EE0
{
	mangled_x86(MANGLED_TODO, "?effect_system_patches_apply@@YAXXZ");
	// procedure flags: nofpo
	todo("implement");
	_sub_10911EE0();
}

_extern void _sub_10912BB0();
void effect_system_patches_tick() // 0x10912BB0
{
	mangled_x86(MANGLED_TODO, "?effect_system_patches_tick@@YAXXZ");
	// procedure flags: nofpo
	// Modules::ModuleGraphics &graphics_module;
	todo("implement");
	_sub_10912BB0();
}

/* ---------- private code */

_extern void _sub_10910260(s_contrail_gpu_datum *, void *, s_contrail_states *);
void c_contrail_gpu__render_hook(s_contrail_gpu_datum *gpu_datum, void *unused, s_contrail_states *states) // 0x10910260
{
	// `anonymous-namespace'::c_contrail_gpu__render_hook
	// static ...; // 0x10910954
	// s_contrail_gpu_datum *gpu_datum;
	// void *unused;
	// s_contrail_states *states;
	// __int32 row_index;
	// __int32 v4;
	// IDirect3DDevice9 *device;
	// __int32 index;
	// long row_indices[8];
	// s_contrail_instance *contrail;
	// c_rasterizer_vertex_buffer *contrail_vertex_buffer;
	// s_contrail_system_definition *system;
	// _D3DCULL previous_cull_mode;
	// s_contrail_system *parent_system;
	// s_contrail_location *parent_location;
	// void *contrail_index_buffer;
	{
		// __int32 v7;
	}
	{
		// s_contrail_gpu_row *i;
	}
	{
		// short field_c;
		// long offset;
		{
			// long offset;
			{
				// __int32 v15;
				// __int32 v16;
				{
					// __int32 v17;
				}
			}
		}
	}
	// function call : void (*const)()
	// function call : s_contrail_instance *(*const)(long)
	// function call : s_contrail_system_definition *(*const)(s_contrail_instance *)
	// function call : bool (*const)(c_rasterizer_vertex_buffer *)
	// function call : void (*const)(long, long, void *)
	// function call : void (*const)()
	// function call : _D3DCULL (*const)()
	// function call : void (*const)(_D3DCULL)
	// function call : __int32 (*const)(c_render_method **)
	// function call : __int32 (*const)(void *, __int32)
	// function call : void (*const)(s_contrail_gpu_datum *, void *, s_contrail_states *)
	// function call : void (*const)(s_contrail_gpu_datum *, void *)
	// function call : bool (*const)(bool)
	// function call : s_contrail_location *(*const)(s_contrail_instance *)
	// function call : s_contrail_system *(*const)(s_contrail_location *)
	// function call : bool (*const)(long, c_render_method *, long, unsigned long, long, bool)
	// function call : s_contrail_gpu_row *(*const)(long)
	// function call : s_contrail_gpu_row *(*const)(long)
	// function call : HRESULT (unsigned __int32, unsigned __int32)
	// function call : void (*const)(c_rasterizer_vertex_buffer *, long)
	// function call : HRESULT (unsigned __int32, unsigned __int32)
	// function call : HRESULT (unsigned __int32, unsigned __int32)
	// function call : __int32 (*const)(void *, long, long, long, long)
	// function call : bool (*const)(c_rasterizer_vertex_buffer *)
	// function call : void (*const)(c_rasterizer_vertex_buffer *, long)
	// function call : HRESULT (unsigned __int32, unsigned __int32)
	// function call : HRESULT (unsigned __int32, unsigned __int32)
	// function call : __int32 (*const)(void *, long, long, long, long)
	// function call : HRESULT (unsigned __int32, unsigned __int32)
	// function call : HRESULT (unsigned __int32, unsigned __int32)
	// function call : HRESULT (unsigned __int32, unsigned __int32)
	// function call : void (*const)(_D3DCULL)
	// function call : bool (*const)(bool)
	todo("implement");
	_sub_10910260(gpu_datum, unused, states);
}

_extern void _sub_10913080(c_rasterizer_vertex_buffer *, s_gpu_vertex_stream *);
void gpu_vertex_stream_submit(c_rasterizer_vertex_buffer *vertex_buffer, s_gpu_vertex_stream *stream) // 0x10913080
{
	// `anonymous-namespace'::gpu_vertex_stream_submit
	// s_gpu_vertex_stream *stream;
	// void *data;
	// long vertex_data_size;
	// function call : void *(*const)(c_rasterizer_vertex_buffer *, long, long, bool)
	// function call : bool (*const)(c_rasterizer_vertex_buffer *)
	todo("implement");
	_sub_10913080(vertex_buffer, stream);
}

_extern void _sub_10910210();
void beam_gpu_vertex_stream_submit_hook() // 0x10910210
{
	// `anonymous-namespace'::beam_gpu_vertex_stream_submit_hook
	// procedure flags: nofpo
	todo("implement");
	_sub_10910210();
}

_extern void _sub_10911650();
void contrail_gpu_vertex_stream_submit_hook() // 0x10911650
{
	// `anonymous-namespace'::contrail_gpu_vertex_stream_submit_hook
	// procedure flags: nofpo
	todo("implement");
	_sub_10911650();
}

_extern void _sub_10913D40();
void light_volume_gpu_vertex_stream_submit_hook() // 0x10913D40
{
	// `anonymous-namespace'::light_volume_gpu_vertex_stream_submit_hook
	// procedure flags: nofpo
	todo("implement");
	_sub_10913D40();
}

_extern void _sub_10913D90();
void particle_emitter_gpu_vertex_stream_submit_hook() // 0x10913D90
{
	// `anonymous-namespace'::particle_emitter_gpu_vertex_stream_submit_hook
	// procedure flags: nofpo
	todo("implement");
	_sub_10913D90();
}

_extern void _sub_10912CB0(s_effect_message *);
void event_add_particle_system_location_hook(s_effect_message *message) // 0x10912CB0
{
	// `anonymous-namespace'::event_add_particle_system_location_hook
	// s_effect_message *message;
	// constexpr void (*const `event_add_particle_system_location_hook'::`2'::event_add_particle_system_location)(s_effect_message *); // constant == 6019520
	// s_effect_datum *effect;
	// constexpr real_vector3d *(*const `event_add_particle_system_location_hook'::`2'::sub_A4BD70)(real_point3d *, long); // constant == 10796400
	{
		// c_particle *particle;
	}
	// function call : real_vector3d *(*const)(real_point3d *, long)
	// function call : void (*const)(s_effect_message *)
	todo("implement");
	_sub_10912CB0(message);
}

_extern void _sub_10913E60(long);
void render_visible_decals_hook(long pass) // 0x10913E60
{
	// `anonymous-namespace'::render_visible_decals_hook
	// long pass;
	// void (*const c_decal__render)(render_visible_decals_hook::__l2::c_decal *, long);
	// long g_render_decal_count;
	// render_visible_decals_hook::__l2::s_render_decal_unknown *g_render_decals;
	{
		// long i;
		{
			// render_visible_decals_hook::__l2::s_render_decal_unknown *render_decal;
			{
				// render_visible_decals_hook::__l2::c_decal *head;
				// long definition_index;
				// s_tag_block *system_block;
				// s_data_array *decal_system_data;
				// char *block_element;
				// char *decal_system;
				// void *definition;
			}
		}
	}
	// function call : void *(*const)(s_data_array const *, unsigned long)
	// function call : void (*const)(render_visible_decals_hook::__l2::c_decal *, long)
	todo("implement");
	_sub_10913E60(pass);
}

_extern void _sub_10910B40(void *, void *, s_effect_message const *);
void c_effect_messaging_queue__post_message_hook(void *queue, void *unused, s_effect_message const *message) // 0x10910B40
{
	// `anonymous-namespace'::c_effect_messaging_queue__post_message_hook
	// s_effect_message const *message;
	{
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &particle_filter;
	}
	// function call : void (*)(void *, s_effect_message const *)
	todo("implement");
	_sub_10910B40(queue, unused, message);
}

_extern void _sub_10914170(e_effect_message_type, bool);
void set_effect_message_filter(e_effect_message_type type, bool filtered) // 0x10914170
{
	// `anonymous-namespace'::set_effect_message_filter
	// bool filtered;
	todo("implement");
	_sub_10914170(type, filtered);
}

_extern void _sub_10914050(char *, real_vector4d *);
void s_gpu_storage_2x16un__pack_call_hook(char *buffer_dblptr, real_vector4d *data) // 0x10914050
{
	// `anonymous-namespace'::s_gpu_storage_2x16un__pack_call_hook
	// real_vector4d *data;
	// short *buffer;
	todo("implement");
	_sub_10914050(buffer_dblptr, data);
}

_extern void _sub_109140E0(char *, real_vector4d *);
void s_gpu_storage_2x16un__unpack_call_hook(char *buffer_dblptr, real_vector4d *data) // 0x109140E0
{
	// `anonymous-namespace'::s_gpu_storage_2x16un__unpack_call_hook
	// real_vector4d *data;
	// short *buffer;
	todo("implement");
	_sub_109140E0(buffer_dblptr, data);
}

_extern bool _sub_10913CD0(s_effect_event const *);
bool lens_flare_is_constant(s_effect_event const *event_definition) // 0x10913CD0
{
	// `anonymous-namespace'::lens_flare_is_constant
	// s_effect_event const *event_definition;
	todo("implement");
	bool __result = _sub_10913CD0(event_definition);
	return __result;
}

_extern void _sub_109116A0(unsigned long, long);
void effect_render(unsigned long effect_index, long output_user_index) // 0x109116A0
{
	// `anonymous-namespace'::effect_render
	// static ...; // 0x10911D28
	// static ...; // 0x10911D25
	// static ...; // 0x10911D16
	// static ...; // 0x10911D0C
	// static ...; // 0x10911CD0
	// static ...; // 0x10911CC8
	// unsigned long effect_index;
	// long output_user_index;
	// tls_data &tls_data;
	// void (*const lens_flares_create)(__int32, __int32, __int32, __int32, real_point3d *, real_vector3d *, real_vector3d *, float, float, float, char, __int32);
	// s_effect_datum *effect;
	// void (*const effect_get_node_matrix)(s_effect_datum *, short, real_matrix4x3 *);
	// float (*const transition_function_evaluate)(short, float);
	// unsigned long effect_event_datum_index;
	// s_effect const *effect_definition;
	{
		// s_effect_event_datum *effect_event;
		{
			// s_effect_event const *const effect_event_definition;
			{
				// bool lens_flare_always_zero;
				{
					// __int32 i;
					{
						// s_effect_event_part const *const part;
						{
							// short primary_location;
							{
								// char camera_mode;
								// __int32 location_count;
								// __int32 runtime_location_index;
								{
									// real_vector3d forward;
									// real_vector3d unknown_vector;
									// s_effect_location_datum *effect_location;
									// float effect_scale;
									// real_point3d position;
									// long effect_location_index;
									// real_vector3d up;
									{
										// real_matrix4x3 out_nodes;
									}
									{
										// float time;
										// float duration;
										// bool node_unknown;
										{
											// s_lens_flare_definition *const lens;
											// float transition;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	// function call : void *(*const)(unsigned long, long)
	// function call : long (*const)(s_effect_datum *, __int32, char)
	// function call : void (*const)(s_effect_datum *, short, real_matrix4x3 *)
	// function call : void *(*const)(unsigned long, long)
	// function call : float (*const)(short, float)
	// function call : void (*const)(__int32, __int32, __int32, __int32, real_point3d *, real_vector3d *, real_vector3d *, float, float, float, char, __int32)
	todo("implement");
	_sub_109116A0(effect_index, output_user_index);
}

_extern void _sub_10911520(s_particle_system_emitter *, void *, c_particle *, c_particle_emitter *, c_particle_system *);
void c_particle_emitter_definition__initialize_particle_initial(s_particle_system_emitter *_this, void *state_list, c_particle *particle, c_particle_emitter *emitter, c_particle_system *system) // 0x10911520
{
	// `anonymous-namespace'::c_particle_emitter_definition__initialize_particle_initial
	// c_particle_system *system;
	// float (*const c_editable_property__c_particle_state_list__evaluate)(c_editable_property *, void *);
	// function call : float (*const)(c_editable_property *, void *)
	// function call : float (*const)(c_editable_property *, void *)
	// function call : float (*const)(c_editable_property *, void *)
	todo("implement");
	_sub_10911520(_this, state_list, particle, emitter, system);
}

_extern void _sub_10913210(s_particle_system_emitter *, void *, c_particle *, c_particle_emitter *, c_particle_system *);
_inline void initialize_particle_cube(s_particle_system_emitter *_this, void *state_list, c_particle *particle, c_particle_emitter *emitter, c_particle_system *system) // 0x10913210
{
	// `anonymous-namespace'::initialize_particle_cube
	// c_particle_system *system;
	// float x;
	// float y;
	// float emission_radius;
	// float z;
	todo("implement");
	_sub_10913210(_this, state_list, particle, emitter, system);
}

_extern void _sub_109133F0(s_particle_system_emitter *, void *, c_particle *, c_particle_emitter *, c_particle_system *);
_inline void initialize_particle_cylinder(s_particle_system_emitter *_this, void *state_list, c_particle *particle, c_particle_emitter *emitter, c_particle_system *system) // 0x109133F0
{
	// `anonymous-namespace'::initialize_particle_cylinder
	// c_particle_system *system;
	// float x;
	// float random_circular;
	// float y;
	// float randomized_radius;
	// float z;
	todo("implement");
	_sub_109133F0(_this, state_list, particle, emitter, system);
}

_extern void _sub_109139B0(s_particle_system_emitter *, void *, c_particle *, c_particle_emitter *, c_particle_system *);
_inline void initialize_particle_unweighted_line(s_particle_system_emitter *_this, void *state_list, c_particle *particle, c_particle_emitter *emitter, c_particle_system *system) // 0x109139B0
{
	// `anonymous-namespace'::initialize_particle_unweighted_line
	// c_particle_system *system;
	// float random_angle;
	// float random_circular;
	// float y;
	todo("implement");
	_sub_109139B0(_this, state_list, particle, emitter, system);
}

_extern void _sub_10913610(s_particle_system_emitter *, void *, c_particle *, c_particle_emitter *, c_particle_system *);
_inline void initialize_particle_planar_orbit(s_particle_system_emitter *_this, void *state_list, c_particle *particle, c_particle_emitter *emitter, c_particle_system *system) // 0x10913610
{
	// `anonymous-namespace'::initialize_particle_planar_orbit
	// c_particle_system *system;
	// float random_circular;
	// float emission_radius;
	todo("implement");
	_sub_10913610(_this, state_list, particle, emitter, system);
}

_extern void _sub_109137D0(s_particle_system_emitter *, void *, c_particle *, c_particle_emitter *, c_particle_system *);
_inline void initialize_particle_sphere_orbit(s_particle_system_emitter *_this, void *state_list, c_particle *particle, c_particle_emitter *emitter, c_particle_system *system) // 0x109137D0
{
	// `anonymous-namespace'::initialize_particle_sphere_orbit
	// s_particle_system_emitter *_this;
	// void *state_list;
	// c_particle *particle;
	// c_particle_emitter *emitter;
	// c_particle_system *system;
	// float velocity_magnitude;
	// real_vector3d original_velocity;
	// real_vector3d random_direction;
	todo("implement");
	_sub_109137D0(_this, state_list, particle, emitter, system);
}

_extern void _sub_10910CA0(s_particle_system_emitter *, void *, void *, c_particle *, c_particle_emitter *, c_particle_system *, void *);
void c_particle_emitter_definition__initialize_particle_call_hook(s_particle_system_emitter *_this, void *_, void *particle_state_list, c_particle *particle, c_particle_emitter *emitter, c_particle_system *system, void *particle_movement_definition) // 0x10910CA0
{
	// `anonymous-namespace'::c_particle_emitter_definition__initialize_particle_call_hook
// $LN18:
// $LN17:
// $LN16:
// $LN13:
// $LN12:
// $LN11:
// $LN10:
// $LN9:
// $LN8:
	// s_particle_system_emitter *_this;
	// void *_;
	// void *particle_state_list;
	// c_particle *particle;
	// c_particle_emitter *emitter;
	// c_particle_system *system;
	// void *particle_movement_definition;
	// void (*const c_particle_emitter_definition__initialize_particle)(s_particle_system_emitter *, void *, c_particle *, c_particle_emitter *, c_particle_system *, void *);
	// long particle_definition;
	// float (*const c_editable_property__c_particle_state_list__evaluate)(c_editable_property *, void *);
	// unsigned short billboard_style;
	// long appearance_flags;
	// float magnitude;
	{
		// float random_circular;
		// float starting_count_direction_scale;
		// real_vector3d new_direction;
	}
	// function call : void (*const)(s_particle_system_emitter *, void *, c_particle *, c_particle_emitter *, c_particle_system *, void *)
	// function call : float (*const)(c_editable_property *, void *)
	// function call : float (*const)(c_editable_property *, void *)
	// function call : float (*const)(c_editable_property *, void *)
	todo("implement");
	_sub_10910CA0(_this, _, particle_state_list, particle, emitter, system, particle_movement_definition);
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_flags<enum e_effect_message_type,unsigned char>::operator==(e_effect_message_type const &) const;
template bool c_tag_block<s_effect_event>::try_get_element(__int32, s_effect_event **) const;
template bool c_tag_block<s_effect_event_part>::try_get_element(__int32, s_effect_event_part **) const;
template c_enum<enum e_effect_camera_mode,char>::operator char() const;
template c_enum<enum e_effect_event_part_scales,long>::operator long() const;
template c_enum<enum e_particle_emitter_emission_shape,char>::operator char() const;
template c_enum<enum e_particle_emitter_model_axis,char>::operator char() const;
template c_enum<enum e_particle_emitter_reference_axis,char>::operator char() const;
template c_flags<enum e_effect_message_type,unsigned char>::operator unsigned char() const;
template c_flags<enum e_effect_message_type,unsigned long> & c_flags<enum e_effect_message_type,unsigned long>::operator&=(__int32 const);
template c_flags<enum e_effect_message_type,unsigned long> & c_flags<enum e_effect_message_type,unsigned long>::operator|=(__int32 const);
template c_flags<enum e_effect_message_type,unsigned long> c_flags<enum e_effect_message_type,unsigned long>::operator&(__int32 const) const;
template c_flags<enum e_effect_message_type,unsigned long>::c_flags();
template c_flags<enum e_effect_message_type,unsigned long>::c_flags(unsigned long const &);
template c_flags<enum e_effect_message_type,unsigned long>::operator bool() const;
template c_particle * c_data_array<c_particle>::try_and_get(unsigned long);
template s_effect_datum * c_data_array<s_effect_datum>::get_absolute(long);
template s_effect_datum * c_data_array<s_effect_datum>::try_and_get(unsigned long);
template s_effect_event * c_tag_block<s_effect_event>::get_element(__int32) const;
template s_effect_event const & c_tag_block<s_effect_event>::operator[](__int32) const;
template s_effect_event_datum * c_data_array<s_effect_event_datum>::get_absolute(long);
template s_effect_event_part * c_tag_block<s_effect_event_part>::get_element(__int32) const;
template s_effect_event_part const & c_tag_block<s_effect_event_part>::operator[](__int32) const;
template s_effect_location_datum * c_data_array<s_effect_location_datum>::get_absolute(long);
