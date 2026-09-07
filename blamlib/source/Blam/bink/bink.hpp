#ifndef __BLAM_BINK_BINK_HPP__
#define __BLAM_BINK_BINK_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/math/integer_math_definitions.hpp"
#include "Player/PlayerEmblemGenerator.hpp"

/* ---------- forward declarations */

struct BINKFRAMEBUFFERS;
struct BINKFRAMEPLANESET;
struct BINKPLANE;
struct s_bink_gamestate;
struct s_bink_globals;
struct short_rectangle2d;

/* ---------- constants */

/* ---------- definitions */

struct s_bink_gamestate
{
	__int32 runtime_frame_texture_index; // 0x0
	__int32 runtime_frame_num; // 0x4
};
static_assert(sizeof(s_bink_gamestate) == 8, "Invalid s_bink_gamestate size");

struct BINKPLANE
{
	__int32 Allocate; // 0x0
	void *Buffer; // 0x4
	unsigned __int32 BufferPitch; // 0x8
};
static_assert(sizeof(BINKPLANE) == 12, "Invalid BINKPLANE size");

struct BINKFRAMEPLANESET
{
	BINKPLANE YPlane; // 0x0
	BINKPLANE cRPlane; // 0xC
	BINKPLANE cBPlane; // 0x18
	BINKPLANE APlane; // 0x24
};
static_assert(sizeof(BINKFRAMEPLANESET) == 48, "Invalid BINKFRAMEPLANESET size");

struct BINKFRAMEBUFFERS
{
	__int32 TotalFrames; // 0x0
	unsigned __int32 YABufferWidth; // 0x4
	unsigned __int32 YABufferHeight; // 0x8
	unsigned __int32 cRcBBufferWidth; // 0xC
	unsigned __int32 cRcBBufferHeight; // 0x10
	unsigned __int32 FrameNum; // 0x14
	BINKFRAMEPLANESET Frames[2]; // 0x18
};
static_assert(sizeof(BINKFRAMEBUFFERS) == 120, "Invalid BINKFRAMEBUFFERS size");

struct s_bink_globals
{
	public:
#pragma pack(push, 4)
	struct s_bink_prediction_message
	{
		public:
		union u_bink_location
		{
			char bink_path[256]; // 0x0
			void *bink_resource; // 0x0
		};
		static_assert(sizeof(u_bink_location) == 256, "Invalid u_bink_location size");
		public:
		void *bink_header; // 0x0
		u_bink_location bink_location; // 0x4
		__int32 bink_tag_index; // 0x104
		__int32 queued_state; // 0x108
		void *unknown_ptr; // 0x10C
		__int32 flags; // 0x110
	};
#pragma pack(pop)
	static_assert(sizeof(s_bink_prediction_message) == 276, "Invalid s_bink_prediction_message size");
	struct s_bink_runtime
	{
		public:
		struct s_bink_video_frame
		{
			public:
			struct s_bink_frame_texture
			{
				IDirect3DTexture9 *y_plane; // 0x0
				IDirect3DTexture9 *cr_plane; // 0x4
				IDirect3DTexture9 *cb_plane; // 0x8
				IDirect3DTexture9 *a_plane; // 0xC
				__int32 field_10; // 0x10
				char displayed; // 0x14
				unsigned char __pad0[3]; // 0x15
			};
			static_assert(sizeof(s_bink_frame_texture) == 24, "Invalid s_bink_frame_texture size");
			public:
			char texture_available[2]; // 0x0
			unsigned char __pad0[2]; // 0x2
			s_bink_frame_texture textures[2]; // 0x4
			BINKFRAMEBUFFERS framebuffers; // 0x34
			__int32 textures_unknown[2]; // 0xAC
			__int32 field_B4; // 0xB4
			__int32 field_B8; // 0xB8
			__int32 field_BC; // 0xBC
			__int32 field_C0; // 0xC0
			__int32 field_C4; // 0xC4
			__int32 frame_width; // 0xC8
			__int32 frame_height; // 0xCC
		};
		static_assert(sizeof(s_bink_video_frame) == 208, "Invalid s_bink_video_frame size");
		public:
		bool field_00; // 0x0
		bool field_01; // 0x1
		unsigned short field_02; // 0x2
		__int32 field_04; // 0x4
		float fade; // 0x8
		__int32 field_0C; // 0xC
		__int32 field_10; // 0x10
		__int32 field_14; // 0x14
		__int32 field_18; // 0x18
		__int32 field_1C; // 0x1C
		__int32 field_20; // 0x20
		__int32 field_24; // 0x24
		__int32 field_28; // 0x28
		void *bink_h; // 0x2C
		s_bink_video_frame frame; // 0x30
		__int32 volatile unused_texture_index; // 0x100
		s_bink_prediction_message prediction_message; // 0x104
	};
	static_assert(sizeof(s_bink_runtime) == 536, "Invalid s_bink_runtime size");
	public:
	char playing; // 0x0
	char initialized; // 0x1
	char field_02; // 0x2
	char field_03; // 0x3
	char main_loading; // 0x4
	char field_05; // 0x5
	char field_06; // 0x6
	char field_07; // 0x7
	unsigned __int32 start_time; // 0x8
	__int32 bink_tag_index; // 0xC
	void *bink_tag_resource; // 0x10
	unsigned __int32 flags; // 0x14
	s_bink_prediction_message pending_prediction_message; // 0x18
	__int32 field_12C; // 0x12C
	s_bink_runtime bink_runtime; // 0x130
	char data1[20]; // 0x348
	s_bink_prediction_message unknown; // 0x35C
	char data2[1336]; // 0x470
	static s_bink_globals *get();
};
static_assert(sizeof(s_bink_globals) == 2472, "Invalid s_bink_globals size");

/* ---------- prototypes */

extern void bink_display_frame(short_rectangle2d *rect);
extern bool bink_prediction_queued_and_not_active();

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __BLAM_BINK_BINK_HPP__
