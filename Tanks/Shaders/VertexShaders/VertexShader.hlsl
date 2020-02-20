struct Input
{
	float4 position : POSITION;
	float2 texel : TEXCOORD;
};

struct Output
{
	float4 position : SV_POSITION;
	float2 texel : TEXCOORD;
};


Output main(Input input)
{
	Output output;
	output.texel = input.texel;
	output.position = input.position;
	return output;
}