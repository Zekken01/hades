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

void c_rasterizer::set_DAC_LUT_curve() // 0x10F14560
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_DAC_LUT_curve@c_rasterizer@@SAXXZ");
	// procedure flags: nofpo
	// static ...; // 0x10F146B8
	// static ...; // 0x10F146AC
	// static ...; // 0x10F146A4
		// _D3DLOCKED_RECT locked_lut;
			// float *lut_buffer;
				// __int32 i;
	// function call : HRESULT (unsigned __int32, _D3DLOCKED_RECT *, tagRECT const *, unsigned long)
	// function call : HRESULT (unsigned __int32)

	if (!g_LUT_control.same_curve_as(&g_last_LUT_control))
	{
		g_last_LUT_control = g_LUT_control;
		g_LUT_control.compute_LUT(&g_d3d_gamma_ramp);
		_D3DLOCKED_RECT locked_lut;
		if (g_LUT_1D->LockRect(0, &locked_lut, nullptr, 0) >= 0)
		{
			float *lut_buffer = (float *)locked_lut.pBits;
			for (__int32 i = 0; i < 256; i++)
				lut_buffer[i] = c_rasterizer_LUT_control::sample_ramp(g_d3d_gamma_ramp.red, i / 255.0f);
			g_LUT_1D->UnlockRect(0);
			c_rasterizer_LUT_control::update_LUT_gpu();
		}
	}
}

bool c_rasterizer_LUT_control::same_curve_as(c_rasterizer_LUT_control *x) const // 0x10F142F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?same_curve_as@c_rasterizer_LUT_control@@QBE_NPAV1@@Z");
	// c_rasterizer_LUT_control *x;

	return m_buffer_type == x->m_buffer_type && m_buffer_curve == x->m_buffer_curve && m_target_curve == x->m_target_curve && m_gamma_mode == x->m_gamma_mode && m_black_level.red == x->m_black_level.red && m_black_level.green == x->m_black_level.green && m_black_level.blue == x->m_black_level.blue && m_white_level.red == x->m_white_level.red && m_white_level.green == x->m_white_level.green && m_white_level.blue == x->m_white_level.blue;
}

void c_rasterizer_LUT_control::compute_LUT(_D3DGAMMARAMP *ramp) // 0x10F13A90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?compute_LUT@c_rasterizer_LUT_control@@QAEXPAU_D3DGAMMARAMP@@@Z");
	// static ...; // 0x10F13F65
	// static ...; // 0x10F13F58
	// static ...; // 0x10F13F34
	// static ...; // 0x10F13F2C
	// c_rasterizer_LUT_control *const this;
	// _D3DGAMMARAMP *ramp;
	// float power;
	// real_rgb_color colour_scale;
	// real_rgb_color colour_bias;
		// long i;
			// real_rgb_color mapped_value;
			// float linear;

	m_gamma_mode = ((m_gamma_mode < 4 ? m_gamma_mode : 4) > 0 ? (m_gamma_mode < 4 ? m_gamma_mode : 4) : 0);
	float power = 1.0f / (m_target_curve * gamma_adjustment[m_gamma_mode]);
	real_rgb_color colour_bias = { m_black_level.red + black_level_adjustment[m_gamma_mode], m_black_level.green + black_level_adjustment[m_gamma_mode], m_black_level.blue + black_level_adjustment[m_gamma_mode] };
	real_rgb_color colour_scale = { m_white_level.red - colour_bias.red, m_white_level.green - colour_bias.green, m_white_level.blue - colour_bias.blue };
	for (long i = 0; i < 256; i++)
	{
		float linear = get_linear_buffer_value(i, 255, m_buffer_curve);
		real_rgb_color mapped_value;
		mapped_value.red = (0.0f > (1.0f < linear * colour_scale.red + colour_bias.red ? 1.0f : linear * colour_scale.red + colour_bias.red) ? 0.0f : (1.0f < linear * colour_scale.red + colour_bias.red ? 1.0f : linear * colour_scale.red + colour_bias.red));
		mapped_value.green = (0.0f > (1.0f < linear * colour_scale.green + colour_bias.green ? 1.0f : linear * colour_scale.green + colour_bias.green) ? 0.0f : (1.0f < linear * colour_scale.green + colour_bias.green ? 1.0f : linear * colour_scale.green + colour_bias.green));
		mapped_value.blue = (0.0f > (1.0f < linear * colour_scale.blue + colour_bias.blue ? 1.0f : linear * colour_scale.blue + colour_bias.blue) ? 0.0f : (1.0f < linear * colour_scale.blue + colour_bias.blue ? 1.0f : linear * colour_scale.blue + colour_bias.blue));
		mapped_value.red = powf(mapped_value.red, power);
		mapped_value.green = powf(mapped_value.green, power);
		mapped_value.blue = powf(mapped_value.blue, power);
		ramp->red[i] = (WORD)(mapped_value.red * 65535.0f);
		ramp->green[i] = (WORD)(mapped_value.green * 65535.0f);
		ramp->blue[i] = (WORD)(mapped_value.blue * 65535.0f);
	}
}

bool c_rasterizer_LUT_control::initialized() // 0x10F14230
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?initialized@c_rasterizer_LUT_control@@SA_NXZ");
	// procedure flags: nofpo

	return g_LUT_initialized;
}

bool c_rasterizer_LUT_control::initialize_LUT_textures() // 0x10F14140
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?initialize_LUT_textures@c_rasterizer_LUT_control@@SA_NXZ");
	// procedure flags: nofpo

	if (initialized())
	{
		release_textures();
	}

	if (c_d3d_resource_allocator::create_texture(256, 1, 1, 0, D3DFMT_R32F, 2, &g_LUT_1D, 0, 0, 0, "LUT_1D") >= 0
		&& c_d3d_resource_allocator::create_texture(256, 1, 1, 0, D3DFMT_R32F, 0, &g_LUT_1D_gpu, 0, 0, 0, "LUT_1D_gpu") >= 0)
	{
		g_LUT_initialized = true;
	}

	if (!initialized())
	{
		release_textures();
	}

	return initialized();
}

void c_rasterizer_LUT_control::set_LUT_texture(long sampler) // 0x10F14720
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?set_LUT_texture@c_rasterizer_LUT_control@@SAXJ@Z");
	// long sampler;
	// function call : void (*const)(long)
	// function call : void (*const)(long, IDirect3DBaseTexture9 *)
	// function call : void (*const)(long, long)

	((void(__cdecl *const)(long))0xa22a90)(sampler);
	((void(__cdecl *const)(long, IDirect3DTexture9 *))0xa23980)(sampler, g_LUT_1D_gpu);
	((void(__cdecl *const)(long, long))0xa23530)(sampler, 0);
}

void c_rasterizer_LUT_control::release_textures() // 0x10F14280
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?release_textures@c_rasterizer_LUT_control@@SAXXZ");
	// procedure flags: nofpo

	c_d3d_resource_allocator::release_texture(g_LUT_1D);
	c_d3d_resource_allocator::release_texture(g_LUT_1D_gpu);
	g_LUT_initialized = false;
}

float c_rasterizer_LUT_control::sample_ramp(unsigned short *ramp_channel, float coord) // 0x10F14470
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?sample_ramp@c_rasterizer_LUT_control@@SAMPAGM@Z");
	// float coord;
	// long i;
	// float s;
	// float indexF;

	float f = coord * 255.0f;
	long i = (long)f;
	float s = f - i;

	return ramp_channel[i] / 65535.0f * (1.0f - s) + ramp_channel[i + 1] / 65535.0f * s;
}

void c_rasterizer_LUT_control::update_LUT_gpu() // 0x10F147D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?update_LUT_gpu@c_rasterizer_LUT_control@@SAXXZ");
	// procedure flags: nofpo

	if (initialized())
	{
		c_d3d_resource_allocator::update_texture(g_LUT_1D, g_LUT_1D_gpu);
	}
}

float get_linear_buffer_value(long a1, long max_pixel_value, float a3) // 0x10F140C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_linear_buffer_value@@YAMJJM@Z");
	// float a3;

	return powf((float)a1 / (float)max_pixel_value, a3);
}

/* ---------- private code */

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { bool g_LUT_initialized; }
namespace hades_file_local { IDirect3DTexture9 *g_LUT_1D; }
namespace hades_file_local { IDirect3DTexture9 *g_LUT_1D_gpu; }
namespace hades_file_local { _D3DGAMMARAMP g_d3d_gamma_ramp; }
namespace hades_file_local { c_rasterizer_LUT_control g_last_LUT_control; }
namespace hades_file_local { float gamma_adjustment[5] = { 0.7599999904632568f, 0.8799999952316284f, 1.0f, 1.1200000047683716f, 1.2400000095367432f }; }
namespace hades_file_local { float black_level_adjustment[5]; }
