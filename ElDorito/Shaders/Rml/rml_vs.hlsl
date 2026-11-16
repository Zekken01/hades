#include "rml_common.hlsli"

// Rml::Matrix4f is column-major; the default HLSL packing puts column k in c[k], so the
// matrix is uploaded as-is and multiplied as M * v.
float4x4 g_transform : register(c0);
float4   g_translate : register(c4); // xy = Rml translation, zw unused

VS_OUT main(VS_IN i)
{
	VS_OUT o;
	o.pos = mul(g_transform, float4(i.pos + g_translate.xy, 0.0f, 1.0f));
	o.col = i.col;
	o.uv = i.uv;
	return o;
}
