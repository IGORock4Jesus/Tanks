struct Input
{
	float4 position : SV_POSITION;
	float2 texel : TEXCOORD;
};

Texture2D texture1;
SamplerState state;

float4 main(Input input) : SV_TARGET
{
	return texture1.Sample(state, input.texel);
}