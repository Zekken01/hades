#include "rml_common.hlsli"

sampler2D s_texture : register(s0);

// Both the vertex colour and the texture are premultiplied, so a plain modulate is right.
float4 main(VS_OUT i) : COLOR
{
	return i.col * tex2D(s_texture, i.uv);
}
