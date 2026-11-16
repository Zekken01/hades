#include "rml_common.hlsli"

// Port of RmlUi's DX11 gradient shader to ps_3_0.  ps_3_0 cannot index constant arrays
// dynamically, so the stop loop is unrolled over MAX_NUM_STOPS and masked by the stop
// count, and the first/last stop positions needed for repeating gradients come in c0.zw.
// Constant layout: c0 params, c1 p, c2 v, c3..c18 stop colours, c19..c34 stop positions.
#define MAX_NUM_STOPS 16
#define LINEAR 0
#define RADIAL 1
#define CONIC 2
#define REPEATING_LINEAR 3
#define REPEATING_RADIAL 4
#define REPEATING_CONIC 5
#define PI 3.14159265

float4 g_params : register(c0); // x = func, y = num_stops, z = first stop position, w = last stop position
float4 g_p : register(c1);      // xy: linear: starting point, radial: center, conic: center
float4 g_v : register(c2);      // xy: linear: vector to ending point, radial: inverse radius, conic: angled unit vector
float4 g_stop_colors[MAX_NUM_STOPS] : register(c3);
float4 g_stop_positions[MAX_NUM_STOPS] : register(c19); // x = normalized position 0..1 (one register per stop: ps_3_0 has no bitwise ops for packing)

#define GET_STOP_POS(i) (g_stop_positions[(i)].x)

float glsl_mod(float x, float y)
{
	return x - y * floor(x / y);
}

float4 main(VS_OUT i) : COLOR
{
	int func = (int)g_params.x;
	int num_stops = (int)g_params.y;
	float t = 0.0f;

	if (func == LINEAR || func == REPEATING_LINEAR)
	{
		float2 V = i.uv - g_p.xy;
		t = dot(g_v.xy, V) / dot(g_v.xy, g_v.xy);
	}
	else if (func == RADIAL || func == REPEATING_RADIAL)
	{
		float2 V = i.uv - g_p.xy;
		t = length(g_v.xy * V);
	}
	else
	{
		float2x2 R = float2x2(g_v.x, -g_v.y, g_v.y, g_v.x);
		float2 V = mul(i.uv - g_p.xy, R);
		t = 0.5f + atan2(-V.x, V.y) / (2.0f * PI);
	}

	if (func >= REPEATING_LINEAR)
	{
		float t0 = g_params.z;
		float t1 = g_params.w;
		t = t0 + glsl_mod(t - t0, t1 - t0);
	}

	float4 color = g_stop_colors[0];
	[unroll]
	for (int s = 1; s < MAX_NUM_STOPS; s++)
	{
		if (s < num_stops)
		{
			float p0 = GET_STOP_POS(s - 1);
			float p1 = max(GET_STOP_POS(s), p0 + 1e-5f);
			color = lerp(color, g_stop_colors[s], smoothstep(p0, p1, t));
		}
	}
	return i.col * color;
}
