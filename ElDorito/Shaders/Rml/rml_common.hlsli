// Shared declarations for the RmlUi D3D9 render backend shaders (vs_3_0 / ps_3_0).
// Compiled by build_shaders.py into ElDorito/Source/Web/Rml/Shaders/*.h.

struct VS_IN
{
	float2 pos : POSITION;
	float4 col : COLOR0;    // premultiplied RGBA, D3DDECLTYPE_UBYTE4N
	float2 uv  : TEXCOORD0;
};

struct VS_OUT
{
	float4 pos : POSITION;
	float4 col : COLOR0;
	float2 uv  : TEXCOORD0;
};
