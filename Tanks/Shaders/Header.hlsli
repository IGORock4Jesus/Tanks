struct VSInput
{
	float4 position : POSITION;
	float2 texel : TEXCOORD;
};

struct VSOutput
{
	float4 position : SV_POSITION;
	float2 texel : TEXCOORD;
};