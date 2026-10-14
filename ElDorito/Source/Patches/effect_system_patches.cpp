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

float real_random_local();  // hades: added for 0x10913610

real_vector3d *cross_product3d(real_vector3d const *a, real_vector3d const *b, real_vector3d *result);  // hades: added for 0x109137D0
float magnitude3d(real_vector3d const *v);  // hades: added for 0x109137D0

extern void *(*const datum_try_and_get)(s_data_array const *, unsigned long);  // hades: added for 0x10913E60
void *tag_try_and_get_and_verify_group(unsigned long group_tag, long tag_index);  // hades: added for 0x10913E60

#include "Modules/ModuleDebug.hpp"  // hades: added for 0x10910B40
char const *tag_get_name(long tag_index);  // hades: added for 0x10910B40

void *csmemmove(void *dest, const void *src, unsigned long size);  // hades: added for 0X10913080

extern void effect_system_patches_apply();
extern void effect_system_patches_tick();

void __fastcall c_contrail_gpu__render_hook(s_contrail_gpu_datum *gpu_datum, void *unused, s_contrail_states *states);
void gpu_vertex_stream_submit(c_rasterizer_vertex_buffer *vertex_buffer, s_gpu_vertex_stream *stream);
void beam_gpu_vertex_stream_submit_hook();
void contrail_gpu_vertex_stream_submit_hook();
void light_volume_gpu_vertex_stream_submit_hook();
void particle_emitter_gpu_vertex_stream_submit_hook();
void event_add_particle_system_location_hook(s_effect_message *message);
void render_visible_decals_hook(long pass);
void __fastcall c_effect_messaging_queue__post_message_hook(void *queue, void *unused, s_effect_message const *message);
void set_effect_message_filter(e_effect_message_type type, bool filtered);
void s_gpu_storage_2x16un__pack_call_hook(char *buffer_dblptr, real_vector4d *data);
void s_gpu_storage_2x16un__unpack_call_hook(char *buffer_dblptr, real_vector4d *data);
bool lens_flare_is_constant(s_effect_event const *event_definition);
void effect_render(unsigned long effect_index, long output_user_index);
real_point3d *matrix4x3_transform_point(real_matrix4x3 const *matrix, real_point3d const *point, real_point3d *result);  // hades: added for 0x109116A0
real_vector3d *matrix4x3_transform_vector(real_matrix4x3 const *matrix, real_vector3d const *vector, real_vector3d *result);  // hades: added for 0x109116A0
void c_particle_emitter_definition__initialize_particle_initial(s_particle_system_emitter *_this, void *state_list, c_particle *particle, c_particle_emitter *emitter, c_particle_system *system);
_inline void initialize_particle_cube(s_particle_system_emitter *_this, void *state_list, c_particle *particle, c_particle_emitter *emitter, c_particle_system *system);
_inline void initialize_particle_cylinder(s_particle_system_emitter *_this, void *state_list, c_particle *particle, c_particle_emitter *emitter, c_particle_system *system);
_inline void initialize_particle_unweighted_line(s_particle_system_emitter *_this, void *state_list, c_particle *particle, c_particle_emitter *emitter, c_particle_system *system);
_inline void initialize_particle_planar_orbit(s_particle_system_emitter *_this, void *state_list, c_particle *particle, c_particle_emitter *emitter, c_particle_system *system);
_inline void initialize_particle_sphere_orbit(s_particle_system_emitter *_this, void *state_list, c_particle *particle, c_particle_emitter *emitter, c_particle_system *system);
void __fastcall c_particle_emitter_definition__initialize_particle_call_hook(s_particle_system_emitter *_this, void *_, void *particle_state_list, c_particle *particle, c_particle_emitter *emitter, c_particle_system *system, void *particle_movement_definition);

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern c_flags<enum e_effect_message_type,unsigned long> g_effect_message_filter; // 0x1240936C
	extern real_vector3d global_zero3d; // 0x111978AC
}
using namespace hades_file_local;
/* ---------- public code */

void effect_system_patches_apply() // 0x10911EE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?effect_system_patches_apply@@YAXXZ");
	// procedure flags: nofpo

	Hook(0x357367, c_contrail_gpu__render_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x1BBE36, beam_gpu_vertex_stream_submit_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x1BBE3B, contrail_gpu_vertex_stream_submit_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x1BBE40, light_volume_gpu_vertex_stream_submit_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x1BBE45, particle_emitter_gpu_vertex_stream_submit_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Patch(0x1B6ED0, { 0xEB }).Apply();
	Hook(0x1C117B, event_add_particle_system_location_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x2947FE, render_visible_decals_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0x1B91CC, c_effect_messaging_queue__post_message_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0xA0DAE8, s_gpu_storage_2x16un__pack_call_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Hook(0xA0CD06, s_gpu_storage_2x16un__unpack_call_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
	Patch::NopFill(0xA4D5A1, 82);
	Hook(0x1B63E0, effect_render).Apply();
	Hook(0x5F0463, c_particle_emitter_definition__initialize_particle_call_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
}

void effect_system_patches_tick() // 0x10912BB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?effect_system_patches_tick@@YAXXZ");
	// procedure flags: nofpo
	// Modules::ModuleGraphics &graphics_module;

	auto &graphics_module = Utils::Singleton<Modules::ModuleGraphics>::Instance();

	set_effect_message_filter(_effect_message_type_create_contrail_system, graphics_module.VarContrailsEnabled->ValueInt == 0);
	set_effect_message_filter(_effect_message_type_create_decal_system, graphics_module.VarDecalsEnabled->ValueInt == 0);
	set_effect_message_filter(_effect_message_type_create_particle_system, graphics_module.VarParticlesEnabled->ValueInt == 0);
}

/* ---------- private code */

void __fastcall c_contrail_gpu__render_hook(s_contrail_gpu_datum *gpu_datum, void *unused, s_contrail_states *states) // 0x10910260
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_contrail_gpu__render_hook@@YIXPAUs_contrail_gpu_datum@@PAXPAUs_contrail_states@@@Z");
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
		// __int32 v7;
		// s_contrail_gpu_row *i;
		// short field_c;
		// long offset;
			// long offset;
				// __int32 v15;
				// __int32 v16;
					// __int32 v17;
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

	if (!*(bool *)0x18F3A8C)
		return;
	((void (*const)())0x5BBE10)();
	if (!*(bool *)0x18F3A8F)
		return;
	if (!*(bool *)0x1917322 || gpu_datum->gpu_row_datum_index == -1 || gpu_datum->field_C <= 1)
		return;
	s_contrail_instance *contrail = ((s_contrail_instance *(*const)(long))0x7563D0)(gpu_datum->parent_contrail_index);
	s_contrail_system_definition *system = ((s_contrail_system_definition *(__thiscall *const)(s_contrail_instance *))0x756460)(contrail);
	((bool (*const)(c_rasterizer_vertex_buffer *))0xA5DB60)((c_rasterizer_vertex_buffer *)0x510FD30);
	((void (*const)(long, long, void *))0xA66410)(0x20, 1, (void *)0x191C9AC);
	__int32 v4 = 1;
	if (system->field_12E)
	{
		if (system->field_12E == 1)
			v4 = 2;
		else
			v4 = system->field_12F;
	}
	_D3DCULL previous_cull_mode = (_D3DCULL)1;
	if ((system->render_flags >> 7) & 1)
		((void (*const)())0xA3B5A0)();
	if ((system->render_flags >> 1) & 1)
	{
		previous_cull_mode = ((_D3DCULL (*const)())0xA22BA0)();
		((void (*const)(_D3DCULL))0xA232D0)((_D3DCULL)1);
	}
	if (!*(long *)0x191746C)
	{
		*(c_render_method **)0x191746C = &system->render_method;
		__int32 v7 = ((__int32 (__thiscall *const)(c_render_method **))0xA57300)((c_render_method **)0x191746C);
		((__int32 (__thiscall *const)(void *, __int32))0xA56BC0)((void *)0x1917470, v7);
	}
	((void (__thiscall *const)(s_contrail_gpu_datum *, void *, s_contrail_states *))0xA54940)(gpu_datum, (void *)0x1917470, states);
	((void (__thiscall *const)(s_contrail_gpu_datum *, void *))0xA55040)(gpu_datum, (void *)0x1917470);
	((bool (*const)(bool))0xA3D260)(true);
	s_contrail_location *parent_location = ((s_contrail_location *(__thiscall *const)(s_contrail_instance *))0x756560)(contrail);
	s_contrail_system *parent_system = ((s_contrail_system *(__thiscall *const)(s_contrail_location *))0x756590)(parent_location);
	if (!((bool (*const)(long, c_render_method *, long, unsigned long, long, bool))0xA3CA60)(parent_system->definition_index, &system->render_method, 11, 0, 0, false))
		return;
	__int32 index = 0;
	__int32 row_index = -1;
	long row_indices[8];
	for (s_contrail_gpu_row *i = ((s_contrail_gpu_row *(*const)(long))0xA58710)(gpu_datum->gpu_row_datum_index); i; i = ((s_contrail_gpu_row *(*const)(long))0xA58710)(i->next_row_datum_index))
	{
		if (index >= 8)
			break;
		row_index = i->next_row_datum_index;
		row_indices[index] = i->index;
		index++;
	}
	c_rasterizer_vertex_buffer *contrail_vertex_buffer = (c_rasterizer_vertex_buffer *)0x191736C;
	void *contrail_index_buffer = (void *)0x510FD20;
	IDirect3DDevice9 *device = *(IDirect3DDevice9 **)0x50DADDC;
	device->SetStreamSourceFreq(1, 0x80000001);
	if (gpu_datum->field_C)
	{
		short field_c = gpu_datum->field_C;
		if (index > 0)
		{
			do
			{
				long offset = row_indices[index - 1] * 16 * contrail_vertex_buffer->get_vertex_stride() + *(long *)0x510FD54;
				if (offset >= 0)
				{
					((void (*const)(c_rasterizer_vertex_buffer *, long))0xA5DB90)(contrail_vertex_buffer, offset);
					__int32 v15 = 16;
					if (field_c < 16)
						v15 = field_c;
					__int32 v16 = v15 - *(long *)0x191749C;
					if (v16 < 0)
						v16 = 0;
					if (v16 > 0)
					{
						__int32 v17 = v16 | 0x40000000;
						device->SetStreamSourceFreq(0, v17);
						device->SetStreamSourceFreq(2, v17);
						((void (*const)(void *, long, long, long, long))0xA28270)(contrail_index_buffer, 0, 4 * v4, 0, 6 * v4);
					}
				}
				field_c -= 16;
			} while (--index);
		}
		long offset = contrail_vertex_buffer->get_vertex_stride() * (row_indices[0] * 16 + gpu_datum->field_C % 16 - 2) + *(long *)0x510FD54;
		if (offset >= 0)
		{
			((bool (*const)(c_rasterizer_vertex_buffer *))0xA5DB60)((c_rasterizer_vertex_buffer *)0x510FD3C);
			((void (*const)(c_rasterizer_vertex_buffer *, long))0xA5DB90)(contrail_vertex_buffer, offset);
			device->SetStreamSourceFreq(0, 0x40000001);
			device->SetStreamSourceFreq(2, 0x40000001);
			((void (*const)(void *, long, long, long, long))0xA28270)(contrail_index_buffer, 0, 4 * v4, 0, 6 * v4);
		}
	}
	device->SetStreamSourceFreq(0, 1);
	device->SetStreamSourceFreq(1, 1);
	device->SetStreamSourceFreq(2, 1);
	if ((system->render_flags >> 1) & 1)
		((void (*const)(_D3DCULL))0xA232D0)(previous_cull_mode);
	((bool (*const)(bool))0xA3D260)(false);
}

void gpu_vertex_stream_submit(c_rasterizer_vertex_buffer *vertex_buffer, s_gpu_vertex_stream *stream) // 0x10913080
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?gpu_vertex_stream_submit@@YAXPAVc_rasterizer_vertex_buffer@@PAUs_gpu_vertex_stream@hades_file_local@@@Z");
	// `anonymous-namespace'::gpu_vertex_stream_submit
	// s_gpu_vertex_stream *stream;
	// void *data;
	// long vertex_data_size;
	// function call : void *(*const)(c_rasterizer_vertex_buffer *, long, long, bool)
	// function call : bool (*const)(c_rasterizer_vertex_buffer *)

	unsigned int vertex_data_size;
	void *data;

	if (stream->vertex_count < 1)
	{
		return;
	}

	vertex_data_size = stream->vertex_count * vertex_buffer->get_vertex_stride();
	stream->offset = 0;
	data = ((void *(__thiscall *)(c_rasterizer_vertex_buffer *, int, unsigned int, int))0xa5dd60)(vertex_buffer, 0, vertex_data_size, 1);
	if (data)
	{
		csmemmove(data, stream->vertex_data, vertex_data_size);
		stream->previous_offset = stream->offset;
		stream->offset += vertex_data_size;
		stream->vertex_count = 0;
	}
	else
	{
		stream->previous_offset = 0;
		stream->vertex_count = 0;
	}
	((void (__thiscall *)(c_rasterizer_vertex_buffer *))0xa5de30)(vertex_buffer);
}

void beam_gpu_vertex_stream_submit_hook() // 0x10910210
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?beam_gpu_vertex_stream_submit_hook@@YAXXZ");
	// `anonymous-namespace'::beam_gpu_vertex_stream_submit_hook
	// procedure flags: nofpo

	gpu_vertex_stream_submit((c_rasterizer_vertex_buffer *)0x1916754, (s_gpu_vertex_stream *)0x510F99C);
}

void contrail_gpu_vertex_stream_submit_hook() // 0x10911650
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?contrail_gpu_vertex_stream_submit_hook@@YAXXZ");
	// `anonymous-namespace'::contrail_gpu_vertex_stream_submit_hook
	// procedure flags: nofpo

	gpu_vertex_stream_submit((c_rasterizer_vertex_buffer *)0x191736C, (s_gpu_vertex_stream *)0x510FD48);
}

void light_volume_gpu_vertex_stream_submit_hook() // 0x10913D40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?light_volume_gpu_vertex_stream_submit_hook@@YAXXZ");
	// `anonymous-namespace'::light_volume_gpu_vertex_stream_submit_hook
	// procedure flags: nofpo

	gpu_vertex_stream_submit((c_rasterizer_vertex_buffer *)0x19177AC, (s_gpu_vertex_stream *)0x5115A90);
}

void particle_emitter_gpu_vertex_stream_submit_hook() // 0x10913D90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?particle_emitter_gpu_vertex_stream_submit_hook@@YAXXZ");
	// `anonymous-namespace'::particle_emitter_gpu_vertex_stream_submit_hook
	// procedure flags: nofpo

	gpu_vertex_stream_submit((c_rasterizer_vertex_buffer *)0x1916194, (s_gpu_vertex_stream *)0x510ED80);
}

void event_add_particle_system_location_hook(s_effect_message *message) // 0x10912CB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?event_add_particle_system_location_hook@@YAXPAUs_effect_message@@@Z");
	// `anonymous-namespace'::event_add_particle_system_location_hook
	// s_effect_message *message;
	// constexpr void (*const `event_add_particle_system_location_hook'::`2'::event_add_particle_system_location)(s_effect_message *); // constant == 6019520
	// s_effect_datum *effect;
	// constexpr real_vector3d *(*const `event_add_particle_system_location_hook'::`2'::sub_A4BD70)(real_point3d *, long); // constant == 10796400
		// c_particle *particle;
	// function call : real_vector3d *(*const)(real_point3d *, long)
	// function call : void (*const)(s_effect_message *)

	s_effect_datum *effect = effects_get()->try_and_get(message->effect_index);
	if ((effect && message->field_14 == 1) || (effect && effect->particle_index != -1 && effect->object_index == -1))
	{
		c_particle *particle = particles_get()->try_and_get(effect->particle_index);
		if (particle && particle->m_start_vertex != -1)
		{
			((real_vector3d *(*)(real_point3d *, long))0xa4bd70)(&message->transform.position, particle->m_start_vertex);
		}
	}
	((void (*)(s_effect_message *))0x5bd9c0)(message);
}

void render_visible_decals_hook(long pass) // 0x10913E60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_visible_decals_hook@@YAXJ@Z");
	// `anonymous-namespace'::render_visible_decals_hook
	// long pass;
	// void (*const c_decal__render)(render_visible_decals_hook::__l2::c_decal *, long);
	// long g_render_decal_count;
	// render_visible_decals_hook::__l2::s_render_decal_unknown *g_render_decals;
		// long i;
			// render_visible_decals_hook::__l2::s_render_decal_unknown *render_decal;
				// render_visible_decals_hook::__l2::c_decal *head;
				// long definition_index;
				// s_tag_block *system_block;
				// s_data_array *decal_system_data;
				// char *block_element;
				// char *decal_system;
				// void *definition;
	// function call : void *(*const)(s_data_array const *, unsigned long)
	// function call : void (*const)(render_visible_decals_hook::__l2::c_decal *, long)

	struct c_decal
	{
		short identifier;
		long parent_system_block_index;
		long parent_system_index;
		long next_index;
	};
	struct s_render_decal_unknown
	{
		c_decal *decals[600];
		long decal_count;
		unsigned char __pad[16];
	};
	void (__thiscall *const c_decal__render)(c_decal *, long) = reinterpret_cast<void (__thiscall *)(c_decal *, long)>(0x694430);
	long g_render_decal_count = *(long *)0x46DE700;
	s_render_decal_unknown *g_render_decals = (s_render_decal_unknown *)0x46DE718;
	for (long i = 0; i < g_render_decal_count; i++)
	{
		s_render_decal_unknown *render_decal = &g_render_decals[i];
		if (render_decal->decal_count > 0)
		{
			c_decal *head = render_decal->decals[0];
			if (!head)
				continue;
			s_data_array *decal_system_data = *(s_data_array **)tls_get(0x354);
			if (!decal_system_data)
				continue;
			char *decal_system = (char *)datum_try_and_get(decal_system_data, head->parent_system_index);
			if (!decal_system)
				continue;
			long definition_index = *(long *)(decal_system + 4);
			if (definition_index <= 0)
				continue;
			void *definition = tag_try_and_get_and_verify_group('decs', definition_index);
			if (!definition)
				continue;
			s_tag_block *system_block = (s_tag_block *)((char *)definition + 0x14);
			if (head->parent_system_block_index < 0 || head->parent_system_block_index >= system_block->count)
				continue;
			char *block_element = head->parent_system_block_index * 0x74 + (char *)system_block->address;
			if (*(long *)(block_element + 0x68) != pass)
				continue;
			c_decal__render(head, i);
		}
	}
}

void __fastcall c_effect_messaging_queue__post_message_hook(void *queue, void *unused, s_effect_message const *message) // 0x10910B40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_effect_messaging_queue__post_message_hook@@YIXPAX0PBUs_effect_message@@@Z");
	// `anonymous-namespace'::c_effect_messaging_queue__post_message_hook
	// s_effect_message const *message;
		// std::string const &particle_filter;
	// function call : void (*)(void *, s_effect_message const *)

	if (g_effect_message_filter & (1 << (unsigned char)message->type))
		return;
	if (message->type == _effect_message_type_create_particle_system)
	{
		std::string const &particle_filter = Utils::Singleton<Modules::ModuleDebug>::Instance().VarParticleFilter->ValueString;
		if (!particle_filter.empty() && !strstr(tag_get_name(message->definition_index), particle_filter.c_str()))
			return;
	}
	((void (__thiscall *)(void *, s_effect_message const *))0x5B4780)(queue, message);
}

void set_effect_message_filter(e_effect_message_type type, bool filtered) // 0x10914170
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_effect_message_filter@@YAXW4e_effect_message_type@@_N@Z");
	// `anonymous-namespace'::set_effect_message_filter
	// bool filtered;

	if (filtered)
	{
		g_effect_message_filter |= 1 << type;
	}
	else
	{
		g_effect_message_filter &= ~(1 << type);
	}
}

void s_gpu_storage_2x16un__pack_call_hook(char *buffer_dblptr, real_vector4d *data) // 0x10914050
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?s_gpu_storage_2x16un__pack_call_hook@@YAXPADPAUreal_vector4d@@@Z");
	// `anonymous-namespace'::s_gpu_storage_2x16un__pack_call_hook
	// real_vector4d *data;
	// short *buffer;

	short *buffer = *(short **)buffer_dblptr;
	*buffer = (short)(data->i * 65535.0f - 32767.0f);
	*(buffer + 1) = (short)(data->j * 65535.0f - 32767.0f);
	*buffer_dblptr += 4;
}

void s_gpu_storage_2x16un__unpack_call_hook(char *buffer_dblptr, real_vector4d *data) // 0x109140E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?s_gpu_storage_2x16un__unpack_call_hook@@YAXPADPAUreal_vector4d@@@Z");
	// `anonymous-namespace'::s_gpu_storage_2x16un__unpack_call_hook
	// real_vector4d *data;
	// short *buffer;

	short *buffer = *(short **)buffer_dblptr;
	data->i = (*buffer + 32767.0f) / 65535.0f;
	data->j = (*(buffer + 1) + 32767.0f) / 65535.0f;
	*buffer_dblptr += 4;
}

bool lens_flare_is_constant(s_effect_event const *event_definition) // 0x10913CD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?lens_flare_is_constant@@YA_NPBUs_effect_event@@@Z");
	// `anonymous-namespace'::lens_flare_is_constant
	// s_effect_event const *event_definition;

	return event_definition->duration_bounds_min == 0.033333335f && event_definition->duration_bounds_max == 0.033333335f;
}

void effect_render(unsigned long effect_index, long output_user_index) // 0x109116A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?effect_render@@YAXKJ@Z");
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
		// s_effect_event_datum *effect_event;
			// s_effect_event const *const effect_event_definition;
				// bool lens_flare_always_zero;
					// __int32 i;
						// s_effect_event_part const *const part;
							// short primary_location;
								// char camera_mode;
								// __int32 location_count;
								// __int32 runtime_location_index;
									// real_vector3d forward;
									// real_vector3d unknown_vector;
									// s_effect_location_datum *effect_location;
									// float effect_scale;
									// real_point3d position;
									// long effect_location_index;
									// real_vector3d up;
										// real_matrix4x3 out_nodes;
										// float time;
										// float duration;
										// bool node_unknown;
											// s_lens_flare_definition *const lens;
											// float transition;
	// function call : void *(*const)(unsigned long, long)
	// function call : long (*const)(s_effect_datum *, __int32, char)
	// function call : void (*const)(s_effect_datum *, short, real_matrix4x3 *)
	// function call : void *(*const)(unsigned long, long)
	// function call : float (*const)(short, float)
	// function call : void (*const)(__int32, __int32, __int32, __int32, real_point3d *, real_vector3d *, real_vector3d *, float, float, float, char, __int32)

	float (*const transition_function_evaluate)(short, float) = (float (*)(short, float))0x601950;
	void (*const effect_get_node_matrix)(s_effect_datum *, short, real_matrix4x3 *) = (void (*)(s_effect_datum *, short, real_matrix4x3 *))0x5B6B40;
	void (*const lens_flares_create)(__int32, __int32, __int32, __int32, real_point3d *, real_vector3d *, real_vector3d *, float, float, float, char, __int32) = (void (*)(__int32, __int32, __int32, __int32, real_point3d *, real_vector3d *, real_vector3d *, float, float, float, char, __int32))0xA5A250;
	tls_data &tls_data = tls_getd();
	s_effect_datum *effect = tls_data.effect->get_absolute((short)effect_index);
	s_effect const *effect_definition = (s_effect const *)tag_get('effe', effect->definition_index);
	unsigned long effect_event_datum_index = effect->event_index;
	while (effect_event_datum_index != -1)
	{
		s_effect_event_datum *effect_event = tls_data.effect_event->get_absolute((short)effect_event_datum_index);
		if (!(effect_event->flags & 2) && (effect_event->flags & 1))
		{
			s_effect_event const *const effect_event_definition = &effect_definition->events[effect_event->event_index];
			if (effect_event_definition->parts.count > 0)
			{
				bool lens_flare_always_zero = lens_flare_is_constant(effect_event_definition);
				for (__int32 i = 0; i < effect_event_definition->parts.count; i++)
				{
					s_effect_event_part const *const part = &effect_event_definition->parts[i];
					if (part->runtime_base_group_tag == 'lens' && part->type.index != -1)
					{
						short primary_location = part->primary_location;
						if (primary_location >= 0 && primary_location < effect_definition->locations.count)
						{
							char camera_mode = part->camera_mode;
							__int32 runtime_location_index = effect->locations[primary_location];
							__int32 location_count = 0;
							while (true)
							{
								long effect_location_index = ((long (*const)(s_effect_datum *, long, unsigned char))0x5B7890)(effect, runtime_location_index, camera_mode);
								if (effect_location_index == -1)
									break;
								s_effect_location_datum *effect_location = tls_data.effect_location->get_absolute((short)effect_location_index);
								runtime_location_index = effect_location->next_location_index;
								real_point3d position = effect_location->world_location.position;
								real_vector3d forward = effect_location->world_location.forward;
								real_vector3d up = effect_location->world_location.up;
								real_vector3d unknown_vector = *(real_vector3d *)0x189CD58;
								float effect_scale = 1.0f;
								if ((long)part->a_scales_values & 0x20)
									effect_scale = effect->primary_scale;
								if ((long)part->b_scales_values & 0x20)
									effect_scale = effect->secondary_scale * effect_scale;
								if (effect_location->node_index != 0xFFFF)
								{
									real_matrix4x3 out_nodes;
									effect_get_node_matrix(effect, effect_location->node_index, &out_nodes);
									matrix4x3_transform_point(&out_nodes, &position, &position);
									matrix4x3_transform_vector(&out_nodes, &forward, &forward);
									matrix4x3_transform_vector(&out_nodes, &up, &up);
								}
								if (part->runtime_base_group_tag == 'lens')
								{
									float duration = effect_event->duration;
									float time = lens_flare_always_zero ? 0.0f : effect_event->time;
									if (duration != 0.0f)
									{
										time /= duration;
										s_lens_flare_definition *const lens = (s_lens_flare_definition *)tag_get('lens', part->type.index);
										float transition = transition_function_evaluate(lens->falloff_function, time);
										effect_scale = (1.0f - transition) * effect_scale;
									}
									bool node_unknown = effect_location->node_index != -1 && (effect_location->node_index & 0x8000);
									lens_flares_create(part->type.index, 0, effect_index, location_count + 8 * (i + 32 * effect_event->event_index), &position, &forward, &unknown_vector, time, effect_scale, 1.0f, node_unknown, output_user_index);
								}
								location_count++;
							}
						}
					}
				}
			}
		}
		effect_event_datum_index = effect_event->next_event;
	}
}

void c_particle_emitter_definition__initialize_particle_initial(s_particle_system_emitter *_this, void *state_list, c_particle *particle, c_particle_emitter *emitter, c_particle_system *system) // 0x10911520
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_particle_emitter_definition__initialize_particle_initial@@YAXPAUs_particle_system_emitter@@PAXPAUc_particle@@PAUc_particle_emitter@@PAUc_particle_system@@@Z");
	// `anonymous-namespace'::c_particle_emitter_definition__initialize_particle_initial
	// c_particle_system *system;
	// float (*const c_editable_property__c_particle_state_list__evaluate)(c_editable_property *, void *);
	// function call : float (*const)(c_editable_property *, void *)
	// function call : float (*const)(c_editable_property *, void *)
	// function call : float (*const)(c_editable_property *, void *)

	float (__thiscall *const c_editable_property__c_particle_state_list__evaluate)(c_editable_property *, void *) = (float(__thiscall *const)(c_editable_property *, void *))0x9ecc00;

	emitter->particle_lifespan = c_editable_property__c_particle_state_list__evaluate(&_this->particle_lifespan, state_list);
	if (emitter->particle_lifespan <= 0.001f)
	{
		emitter->particle_lifespan = 0.001f;
	}
	particle->m_inverse_lifespan = 1.0f / emitter->particle_lifespan;
	particle->field_48 = 0;
	system->initialize_particle(state_list, particle);
	emitter->emission_angle = c_editable_property__c_particle_state_list__evaluate(&_this->emission_angle, state_list);
	emitter->emission_radius = c_editable_property__c_particle_state_list__evaluate(&_this->emission_radius, state_list);
}

_inline void initialize_particle_cube(s_particle_system_emitter *_this, void *state_list, c_particle *particle, c_particle_emitter *emitter, c_particle_system *system) // 0x10913210
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?initialize_particle_cube@@YAXPAUs_particle_system_emitter@@PAXPAUc_particle@@PAUc_particle_emitter@@PAUc_particle_system@@@Z");
	// `anonymous-namespace'::initialize_particle_cube
	// c_particle_system *system;
	// float x;
	// float y;
	// float emission_radius;
	// float z;

	c_particle_emitter_definition__initialize_particle_initial(_this, state_list, particle, emitter, system);
	float emission_radius = emitter->emission_radius;
	float z = real_random_local() * 2.0f * emission_radius - emission_radius;
	float y = real_random_local() * 2.0f * emission_radius - emission_radius;
	float x = real_random_local() * 2.0f * emission_radius - emission_radius;
	particle->m_position = real_point3d{ x, y, z };
	particle->m_velocity = real_vector3d{ x, y, z };
}

_inline void initialize_particle_cylinder(s_particle_system_emitter *_this, void *state_list, c_particle *particle, c_particle_emitter *emitter, c_particle_system *system) // 0x109133F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?initialize_particle_cylinder@@YAXPAUs_particle_system_emitter@@PAXPAUc_particle@@PAUc_particle_emitter@@PAUc_particle_system@@@Z");
	// `anonymous-namespace'::initialize_particle_cylinder
	// c_particle_system *system;
	// float x;
	// float random_circular;
	// float y;
	// float randomized_radius;
	// float z;

	c_particle_emitter_definition__initialize_particle_initial(_this, state_list, particle, emitter, system);
	float x = real_random_local() * 2.0f - 1.0f;
	float random_circular = real_random_local() * 6.2831855f;
	float randomized_radius = real_random_local() * emitter->emission_radius;
	float y = sinf(random_circular) * randomized_radius;
	float z = cosf(random_circular) * randomized_radius;
	particle->m_position = real_point3d{ x, y, z };
	particle->m_velocity = real_vector3d{ x, y, z };
}

_inline void initialize_particle_unweighted_line(s_particle_system_emitter *_this, void *state_list, c_particle *particle, c_particle_emitter *emitter, c_particle_system *system) // 0x109139B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?initialize_particle_unweighted_line@@YAXPAUs_particle_system_emitter@@PAXPAUc_particle@@PAUc_particle_emitter@@PAUc_particle_system@@@Z");
	// `anonymous-namespace'::initialize_particle_unweighted_line
	// c_particle_system *system;
	// float random_angle;
	// float random_circular;
	// float y;

	c_particle_emitter_definition__initialize_particle_initial(_this, state_list, particle, emitter, system);
	float random_circular = system->real_internal_random_range(0.0f, 6.2831855f);
	float random_angle = system->real_internal_random_range(0.0f, emitter->emission_angle * 0.017453292f);
	float y = emitter->emission_radius * 2.0f * real_random_local() - emitter->emission_radius;
	particle->m_position = real_point3d{ 0.0f, y, 0.0f };
	particle->m_velocity = real_vector3d{ cosf(random_angle), sinf(random_circular) * sinf(random_angle), cosf(random_circular) * sinf(random_angle) };
}

_inline void initialize_particle_planar_orbit(s_particle_system_emitter *_this, void *state_list, c_particle *particle, c_particle_emitter *emitter, c_particle_system *system) // 0x10913610
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?initialize_particle_planar_orbit@@YAXPAUs_particle_system_emitter@@PAXPAUc_particle@@PAUc_particle_emitter@@PAUc_particle_system@@@Z");
	// `anonymous-namespace'::initialize_particle_planar_orbit
	// c_particle_system *system;
	// float random_circular;
	// float emission_radius;

	c_particle_emitter_definition__initialize_particle_initial(_this, state_list, particle, emitter, system);
	float random_circular = real_random_local() * 6.2831855f;
	float emission_radius = emitter->emission_radius;
	particle->m_position = real_point3d{ 0.0f, sinf(random_circular) * emission_radius, cosf(random_circular) * emission_radius };
	particle->m_velocity = real_vector3d{ 0.0f, particle->m_position.z, -particle->m_position.y };
}

_inline void initialize_particle_sphere_orbit(s_particle_system_emitter *_this, void *state_list, c_particle *particle, c_particle_emitter *emitter, c_particle_system *system) // 0x109137D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?initialize_particle_sphere_orbit@@YAXPAUs_particle_system_emitter@@PAXPAUc_particle@@PAUc_particle_emitter@@PAUc_particle_system@@@Z");
	// `anonymous-namespace'::initialize_particle_sphere_orbit
	// s_particle_system_emitter *_this;
	// void *state_list;
	// c_particle *particle;
	// c_particle_emitter *emitter;
	// c_particle_system *system;
	// float velocity_magnitude;
	// real_vector3d original_velocity;
	// real_vector3d random_direction;

	float velocity_magnitude;
	real_vector3d random_direction;
	c_particle_emitter_definition__initialize_particle_initial(_this, state_list, particle, emitter, system);
	system->internal_random_direction3d(&particle->m_velocity);
	particle->m_position.x = particle->m_velocity.i * emitter->emission_radius;
	particle->m_position.y = particle->m_velocity.j * emitter->emission_radius;
	particle->m_position.z = particle->m_velocity.k * emitter->emission_radius;
	real_vector3d original_velocity = particle->m_velocity;
	do
	{
		system->internal_random_direction3d(&random_direction);
		cross_product3d(&original_velocity, &random_direction, &particle->m_velocity);
		velocity_magnitude = magnitude3d(&particle->m_velocity);
	}
	while (velocity_magnitude < 0.0001f);
	particle->m_velocity *= velocity_magnitude;
}

void __fastcall c_particle_emitter_definition__initialize_particle_call_hook(s_particle_system_emitter *_this, void *_, void *particle_state_list, c_particle *particle, c_particle_emitter *emitter, c_particle_system *system, void *particle_movement_definition) // 0x10910CA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?c_particle_emitter_definition__initialize_particle_call_hook@@YIXPAUs_particle_system_emitter@@PAX1PAUc_particle@@PAUc_particle_emitter@@PAUc_particle_system@@1@Z");
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
		// float random_circular;
		// float starting_count_direction_scale;
		// real_vector3d new_direction;
	// function call : void (*const)(s_particle_system_emitter *, void *, c_particle *, c_particle_emitter *, c_particle_system *, void *)
	// function call : float (*const)(c_editable_property *, void *)
	// function call : float (*const)(c_editable_property *, void *)
	// function call : float (*const)(c_editable_property *, void *)

	void (__thiscall *const c_particle_emitter_definition__initialize_particle)(s_particle_system_emitter *, void *, c_particle *, c_particle_emitter *, c_particle_system *, void *) = (void (__thiscall *)(s_particle_system_emitter *, void *, c_particle *, c_particle_emitter *, c_particle_system *, void *))0x9ECF80;
	float (__thiscall *const c_editable_property__c_particle_state_list__evaluate)(c_editable_property *, void *) = (float (__thiscall *)(c_editable_property *, void *))0x9ECC00;
	switch ((char)_this->emission_shape)
	{
	case _emission_shape_cube:
		initialize_particle_cube(_this, particle_state_list, particle, emitter, system);
		break;
	case _emission_shape_cylinder:
		initialize_particle_cylinder(_this, particle_state_list, particle, emitter, system);
		break;
	case _emission_shape_unweighted_line:
		initialize_particle_unweighted_line(_this, particle_state_list, particle, emitter, system);
		break;
	case _emission_shape_plane:
		c_particle_emitter_definition__initialize_particle_initial(_this, particle_state_list, particle, emitter, system);
		particle->m_position.x = (real_random_local() * 2.0f - 1.0f) * emitter->emission_radius;
		particle->m_position.y = (real_random_local() * 2.0f - 1.0f) * emitter->emission_radius;
		particle->m_position.z = (real_random_local() * 2.0f - 1.0f) * emitter->emission_radius;
		particle->m_velocity.i = 1.0f;
		particle->m_velocity.j = 0.0f;
		particle->m_velocity.k = 0.0f;
		break;
	case _emission_shape_planar_orbit:
		initialize_particle_planar_orbit(_this, particle_state_list, particle, emitter, system);
		break;
	case _emission_shape_sphere_orbit:
		initialize_particle_sphere_orbit(_this, particle_state_list, particle, emitter, system);
		break;
	default:
		c_particle_emitter_definition__initialize_particle(_this, particle_state_list, particle, emitter, system, particle_movement_definition);
		return;
	}
	long particle_definition = (long)system->get_particle_definition();
	long appearance_flags = *(long *)(particle_definition + 0x10);
	if ((appearance_flags & 0x8000) == 1)
	{
		float random_circular = system->real_internal_random_range(0.0f, emitter->particle_starting_count * 0.017453292f);
		float starting_count_direction_scale = system->real_internal_random_range(0.0f, 6.2831855f);
		real_vector3d new_direction;
		switch ((char)_this->model_axis)
		{
		case _particle_emitter_model_constant:
			particle->direction.i = 1.0f;
			particle->direction.j = 0.0f;
			particle->direction.k = 0.0f;
			break;
		case _particle_emitter_model_cone:
			emitter->particle_starting_count = c_editable_property__c_particle_state_list__evaluate(&_this->particle_starting_count, particle_state_list);
			particle->direction.i = cosf(random_circular);
			particle->direction.j = sinf(starting_count_direction_scale) * sinf(random_circular);
			particle->direction.k = cosf(starting_count_direction_scale) * sinf(random_circular);
			break;
		case _particle_emitter_model_disc:
			particle->direction.i = 0.0f;
			particle->direction.j = sinf(starting_count_direction_scale);
			particle->direction.k = cosf(starting_count_direction_scale);
			break;
		case _particle_emitter_model_globe:
			system->internal_random_direction3d(&particle->direction);
			break;
		}
		switch ((char)_this->reference_axis)
		{
		case _particle_emitter_reference_axis_x:
			break;
		case _particle_emitter_reference_axis_y:
			new_direction = { particle->direction.k, particle->direction.i, particle->direction.j };
			particle->direction = new_direction;
			break;
		case _particle_emitter_reference_axis_z:
			new_direction = { particle->direction.j, particle->direction.k, particle->direction.i };
			particle->direction = new_direction;
			break;
		}
	}
	float magnitude = magnitude3d(&particle->m_velocity);
	if (fabsf(magnitude) >= 0.00001f)
		particle->m_velocity *= 1.0f / magnitude;
	emitter->particle_velocity = c_editable_property__c_particle_state_list__evaluate(&_this->particle_velocity, particle_state_list);
	emitter->particle_mass = c_editable_property__c_particle_state_list__evaluate(&_this->particle_mass, particle_state_list);
	unsigned short billboard_style = *(unsigned short *)(particle_definition + 0x14);
	if ((billboard_style == 9 || billboard_style == 2 || billboard_style == 3) && emitter->particle_velocity == 0.0f)
		emitter->particle_velocity = 0.001f;
	particle->m_velocity *= emitter->particle_velocity;
	particle->m_mass = emitter->particle_mass;
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

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { c_flags<enum e_effect_message_type,unsigned long> g_effect_message_filter; }
