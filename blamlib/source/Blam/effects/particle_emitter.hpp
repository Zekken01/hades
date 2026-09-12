#ifndef __BLAM_EFFECTS_PARTICLE_EMITTER_HPP__
#define __BLAM_EFFECTS_PARTICLE_EMITTER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/effects/particle_system.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/data.hpp"

/* ---------- forward declarations */

struct c_particle_emitter;
struct c_particle_emitter_gpu;
struct c_particle_system;
struct real_matrix4x3;
struct real_vector3d;
struct s_datum;

/* ---------- constants */

/* ---------- definitions */

struct c_particle_emitter :
	public s_datum
{
	short field_02; // 0x2
	long flags; // 0x4
	long particle_datum; // 0x8
	long field_0C; // 0xC
	long particle_emitter_gpu_datum; // 0x10
	long particle_location_datum; // 0x14
	long emitter_definition_index; // 0x18
	real_point3d translational_offset; // 0x1C
	real_vector3d direction; // 0x28
	float emission_radius; // 0x34
	float emission_angle; // 0x38
	float particle_starting_count; // 0x3C
	float particle_lifespan; // 0x40
	float particle_velocity; // 0x44
	float particle_mass; // 0x48
	float emission_per_distance; // 0x4C
	float max_count; // 0x50
	float emission_rate; // 0x54
	float render_time; // 0x58
	real_matrix4x3 projection; // 0x5C
	static c_particle_emitter *(*get)(unsigned long);
};
static_assert(sizeof(c_particle_emitter) == 144, "Invalid c_particle_emitter size");

struct c_particle_emitter_gpu :
	public s_datum
{
	public:
	struct s_row :
		public s_datum
	{
		short field_02; // 0x2
		long previous_row; // 0x4
		long next_row; // 0x8
		short row_datum; // 0xC
		char m_used_count; // 0xE
		float field_10; // 0x10
	};
	static_assert(sizeof(s_row) == 20, "Invalid s_row size");
	static_assert(offsetof(s_row, field_10) == 0x10, "s_row::field_10 moved when its reconstructed padding was removed");
	struct s_gpu_storage
	{
		void *_vftable; // 0x0
		__int32 field_04; // 0x4
		__int32 field_08; // 0x8
		__int32 field_0C; // 0xC
		__int32 field_10; // 0x10
		__int32 field_14; // 0x14
		__int32 field_18; // 0x18
		__int32 field_1C; // 0x1C
		__int32 field_20; // 0x20
		__int32 field_24; // 0x24
	};
	static_assert(sizeof(s_gpu_storage) == 40, "Invalid s_gpu_storage size");
	struct s_cpu_buffer
	{
		void *_vftable; // 0x0
		__int32 field_04; // 0x4
		__int32 field_08; // 0x8
		__int32 field_0C; // 0xC
		__int32 field_10; // 0x10
		__int32 field_14; // 0x14
		__int32 field_18; // 0x18
		__int32 field_1C; // 0x1C
		__int32 field_20; // 0x20
		__int32 field_24; // 0x24
		__int32 field_28; // 0x28
		__int32 field_2C; // 0x2C
	};
	static_assert(sizeof(s_cpu_buffer) == 48, "Invalid s_cpu_buffer size");
	struct s_layout
	{
		void *field_00; // 0x0
		void *_vftable_04; // 0x4
		void *_vftable_08; // 0x8
		void *_vftable_0C; // 0xC
		void *_vftable_10; // 0x10
		void *_vftable_14; // 0x14
		void *_vftable_18; // 0x18
		void *_vftable_1C; // 0x1C
		void *_vftable_20; // 0x20
		void *_vftable_24; // 0x24
		void *_vftable_28; // 0x28
		void *_vftable_2C; // 0x2C
		__int32 field_30; // 0x30
		__int32 field_34; // 0x34
		__int32 field_38; // 0x38
		__int32 field_3C; // 0x3C
		__int32 field_40; // 0x40
		__int32 field_44; // 0x44
		__int32 field_48; // 0x48
		__int32 field_4C; // 0x4C
		__int32 field_50; // 0x50
		__int32 field_54; // 0x54
		__int32 field_58; // 0x58
		__int32 field_5C; // 0x5C
		__int32 field_60; // 0x60
		__int32 field_64; // 0x64
		__int32 field_68; // 0x68
		__int32 field_6C; // 0x6C
		__int32 field_70; // 0x70
		__int32 field_74; // 0x74
		__int32 field_78; // 0x78
		__int32 field_7C; // 0x7C
		__int32 field_80; // 0x80
		__int32 field_84; // 0x84
		__int32 field_88; // 0x88
		__int32 field_8C; // 0x8C
		__int32 field_90; // 0x90
		__int32 field_94; // 0x94
		__int32 field_98; // 0x98
		__int32 field_9C; // 0x9C
		__int32 field_A0; // 0xA0
		__int32 field_A4; // 0xA4
		__int32 field_A8; // 0xA8
		__int32 field_AC; // 0xAC
		__int32 field_B0; // 0xB0
		__int32 field_B4; // 0xB4
		__int32 field_B8; // 0xB8
		__int32 field_BC; // 0xBC
		__int32 field_C0; // 0xC0
		__int32 field_C4; // 0xC4
		__int32 field_C8; // 0xC8
		__int32 field_CC; // 0xCC
		__int32 field_D0; // 0xD0
		__int32 field_D4; // 0xD4
		__int32 field_D8; // 0xD8
		__int32 field_DC; // 0xDC
		__int32 field_E0; // 0xE0
		__int32 field_E4; // 0xE4
		__int32 field_E8; // 0xE8
		__int32 field_EC; // 0xEC
		__int32 field_F0; // 0xF0
		__int32 field_F4; // 0xF4
		__int32 field_F8; // 0xF8
		__int32 field_FC; // 0xFC
		__int32 field_100; // 0x100
		__int32 field_104; // 0x104
		__int32 field_108; // 0x108
		__int32 field_10C; // 0x10C
		__int32 field_110; // 0x110
		__int32 field_114; // 0x114
		__int32 field_118; // 0x118
		__int32 field_11C; // 0x11C
		__int32 field_120; // 0x120
		__int32 field_124; // 0x124
		__int32 field_128; // 0x128
		__int32 field_12C; // 0x12C
		__int32 field_130; // 0x130
		__int32 field_134; // 0x134
		__int32 field_138; // 0x138
		__int32 field_13C; // 0x13C
		__int32 field_140; // 0x140
		__int32 field_144; // 0x144
		__int32 field_148; // 0x148
		__int32 field_14C; // 0x14C
		__int32 field_150; // 0x150
		__int32 field_154; // 0x154
		__int32 field_158; // 0x158
		__int32 field_15C; // 0x15C
		__int32 field_160; // 0x160
		__int32 field_164; // 0x164
		__int32 field_168; // 0x168
		__int32 field_16C; // 0x16C
		__int32 field_170; // 0x170
		__int32 field_174; // 0x174
		__int32 field_178; // 0x178
		__int32 field_17C; // 0x17C
		__int32 field_180; // 0x180
		__int32 field_184; // 0x184
		__int32 field_188; // 0x188
		__int32 field_18C; // 0x18C
		s_gpu_storage m_position_storage; // 0x190
		s_gpu_storage m_velocity_storage; // 0x1B8
		s_gpu_storage m_rnd_storage; // 0x1E0
		s_gpu_storage m_rnd2_storage; // 0x208
		s_gpu_storage m_rotation_storage; // 0x230
		s_gpu_storage m_time_storage; // 0x258
		s_gpu_storage m_anm_storage; // 0x280
		s_gpu_storage m_anm2_storage; // 0x2A8
		s_gpu_storage m_axis_storage; // 0x2D0
		s_gpu_storage m_col_storage; // 0x2F8
		s_gpu_storage m_col2_storage; // 0x320
		__int32 field_348; // 0x348
		__int32 field_34C; // 0x34C
	};
	static_assert(sizeof(s_layout) == 848, "Invalid s_layout size");
	struct s_queued_buffer_system_layout
	{
		s_layout layout; // 0x0
		void *field_350; // 0x350
		void *_vftable_354; // 0x354
		__int32 field_358; // 0x358
		__int32 field_35C; // 0x35C
		__int32 field_360; // 0x360
		__int32 field_364; // 0x364
		__int32 field_368; // 0x368
		__int32 field_36C; // 0x36C
		__int32 field_370; // 0x370
		__int32 field_374; // 0x374
		__int32 field_378; // 0x378
		__int32 field_37C; // 0x37C
		s_gpu_storage storage_380; // 0x380
		__int32 field_3A8; // 0x3A8
		__int32 field_3AC; // 0x3AC
		s_cpu_buffer cpu_storage_3B0; // 0x3B0
		s_cpu_buffer cpu_storage_3E0; // 0x3E0
		__int32 queued_count; // 0x410
		__int32 field_414; // 0x414
		__int32 field_418; // 0x418
		__int32 field_41C; // 0x41C
	};
	static_assert(sizeof(s_queued_buffer_system_layout) == 1056, "Invalid s_queued_buffer_system_layout size");
	struct s_queued_buffer_system
	{
		s_queued_buffer_system_layout *layouts[2]; // 0x0
	};
	static_assert(sizeof(s_queued_buffer_system) == 8, "Invalid s_queued_buffer_system size");
	public:
	short field_02; // 0x2
	unsigned long particle_system_index; // 0x4
	long emitter_definition_index; // 0x8
	unsigned long particle_emitter_index; // 0xC
	long first_gpu_row_index; // 0x10
	short used_row_count; // 0x14
	static c_particle_emitter_gpu *(*get)(unsigned long);
	static void (*set_shader_render_state)(c_particle_emitter_gpu *, void *, long);
	static s_queued_buffer_system *x_queued_buffer_system;
	static c_particle_system *get_particle_system(c_particle_emitter_gpu *);
};
static_assert(sizeof(c_particle_emitter_gpu) == 24, "Invalid c_particle_emitter_gpu size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_EFFECTS_PARTICLE_EMITTER_HPP__
