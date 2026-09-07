/* ---------- headers */

#include "Blam/rasterizer/rasterizer_LUT_control.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/math/color_definitions.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/rasterizer/rasterizer.hpp"
#include "Blam/rasterizer/rasterizer_d3d_allocations.hpp"
#include "Blam/rasterizer/rasterizer_samplers.hpp"
#include "Blam/rasterizer/rasterizers_textures_cache.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Player/PlayerEmblemGenerator.hpp"

#include <Windows.h>

/* ---------- forward declarations */

class c_rasterizer_LUT_control;
struct _D3DGAMMARAMP;
struct _D3DLOCKED_RECT;
struct c_rasterizer;
struct real_rgb_color;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern float get_linear_buffer_value(long a1, long max_pixel_value, float a3);

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern bool g_LUT_initialized; // 0x1256B9F8
	extern IDirect3DTexture9 *g_LUT_1D; // 0x1256B9FC
	extern IDirect3DTexture9 *g_LUT_1D_gpu; // 0x1256BA00
	extern _D3DGAMMARAMP g_d3d_gamma_ramp; // 0x1256BA18
	extern c_rasterizer_LUT_control g_LUT_control; // 0x11359F10
	extern c_rasterizer_LUT_control g_last_LUT_control; // 0x1256C018
	extern float gamma_adjustment[5]; // 0x11359F38
	extern float black_level_adjustment[5]; // 0x1256BA04
}
using namespace hades_file_local;
/* ---------- public code */

_extern void _sub_10F14560();
void c_rasterizer::set_DAC_LUT_curve() // 0x10F14560
{
	mangled_x86(MANGLED_TODO, "?set_DAC_LUT_curve@c_rasterizer@@SAXXZ");
	// procedure flags: nofpo
	// static ...; // 0x10F146B8
	// static ...; // 0x10F146AC
	// static ...; // 0x10F146A4
	{
		// _D3DLOCKED_RECT locked_lut;
		{
			// float *lut_buffer;
			{
				// __int32 i;
			}
		}
	}
	// function call : HRESULT (unsigned __int32, _D3DLOCKED_RECT *, tagRECT const *, unsigned long)
	// function call : HRESULT (unsigned __int32)
	todo("implement");
	_sub_10F14560();
}

_extern bool _sub_10F142F0(c_rasterizer_LUT_control const *const, c_rasterizer_LUT_control *);
bool c_rasterizer_LUT_control::same_curve_as(c_rasterizer_LUT_control *x) const // 0x10F142F0
{
	mangled_x86(MANGLED_TODO, "?same_curve_as@c_rasterizer_LUT_control@@QBE_NPAV1@@Z");
	// c_rasterizer_LUT_control *x;
	todo("implement");
	bool __result = _sub_10F142F0((c_rasterizer_LUT_control const *)this, x);
	return __result;
}

_extern void _sub_10F13A90(c_rasterizer_LUT_control *const, _D3DGAMMARAMP *);
void c_rasterizer_LUT_control::compute_LUT(_D3DGAMMARAMP *ramp) // 0x10F13A90
{
	mangled_x86(MANGLED_TODO, "?compute_LUT@c_rasterizer_LUT_control@@QAEXPAU_D3DGAMMARAMP@@@Z");
	// static ...; // 0x10F13F65
	// static ...; // 0x10F13F58
	// static ...; // 0x10F13F34
	// static ...; // 0x10F13F2C
	// c_rasterizer_LUT_control *const this;
	// _D3DGAMMARAMP *ramp;
	// float power;
	// real_rgb_color colour_scale;
	// real_rgb_color colour_bias;
	{
		// long i;
		{
			// real_rgb_color mapped_value;
			// float linear;
		}
	}
	todo("implement");
	_sub_10F13A90(this, ramp);
}

_extern bool _sub_10F14230();
bool c_rasterizer_LUT_control::initialized() // 0x10F14230
{
	mangled_x86(MANGLED_TODO, "?initialized@c_rasterizer_LUT_control@@SA_NXZ");
	// procedure flags: nofpo
	todo("implement");
	bool __result = _sub_10F14230();
	return __result;
}

_extern bool _sub_10F14140();
bool c_rasterizer_LUT_control::initialize_LUT_textures() // 0x10F14140
{
	mangled_x86(MANGLED_TODO, "?initialize_LUT_textures@c_rasterizer_LUT_control@@SA_NXZ");
	// procedure flags: nofpo
	todo("implement");
	bool __result = _sub_10F14140();
	return __result;
}

_extern void _sub_10F14720(long);
void c_rasterizer_LUT_control::set_LUT_texture(long sampler) // 0x10F14720
{
	mangled_x86(MANGLED_TODO, "?set_LUT_texture@c_rasterizer_LUT_control@@SAXJ@Z");
	// long sampler;
	// function call : void (*const)(long)
	// function call : void (*const)(long, IDirect3DBaseTexture9 *)
	// function call : void (*const)(long, long)
	todo("implement");
	_sub_10F14720(sampler);
}

_extern void _sub_10F14280();
void c_rasterizer_LUT_control::release_textures() // 0x10F14280
{
	mangled_x86(MANGLED_TODO, "?release_textures@c_rasterizer_LUT_control@@SAXXZ");
	// procedure flags: nofpo
	todo("implement");
	_sub_10F14280();
}

_extern float _sub_10F14470(unsigned short *, float);
float c_rasterizer_LUT_control::sample_ramp(unsigned short *ramp_channel, float coord) // 0x10F14470
{
	mangled_x86(MANGLED_TODO, "?sample_ramp@c_rasterizer_LUT_control@@SAMPAGM@Z");
	// float coord;
	// long i;
	// float s;
	// float indexF;
	todo("implement");
	float __result = _sub_10F14470(ramp_channel, coord);
	return __result;
}

_extern void _sub_10F147D0();
void c_rasterizer_LUT_control::update_LUT_gpu() // 0x10F147D0
{
	mangled_x86(MANGLED_TODO, "?update_LUT_gpu@c_rasterizer_LUT_control@@SAXXZ");
	// procedure flags: nofpo
	todo("implement");
	_sub_10F147D0();
}

_extern float _sub_10F140C0(long, long, float);
float get_linear_buffer_value(long a1, long max_pixel_value, float a3) // 0x10F140C0
{
	mangled_x86(MANGLED_TODO, "?get_linear_buffer_value@@YAMJJM@Z");
	// float a3;
	todo("implement");
	float __result = _sub_10F140C0(a1, max_pixel_value, a3);
	return __result;
}

/* ---------- private code */
