
struct VS_INPUT
{
	float2 position : POSITION;
};

struct PS_INPUT
{
	float4 Pos : SV_POSITION;
	float2 texCoord : TEXCOORD;
};

Texture2D rt : register(t0);
SamplerState rtLinear : register(s0);

PS_INPUT VS( VS_INPUT input )
{
	PS_INPUT output = (PS_INPUT)0;

	output.Pos = float4(input.position.x, input.position.y, 0.5f, 1.0);
	output.texCoord = float2(input.position.x, input.position.y);

	return output;
}

float4 PS( PS_INPUT input) : SV_Target
{
	float2 texCoord = input.texCoord;
	texCoord = texCoord * 0.5f + 0.5f;
	texCoord.y = 1 - texCoord.y;

	float4 color = rt.Sample(rtLinear, texCoord);
	color.rgb = ((color.rgb - 0.5f) * max(1.1f, 0)) + 0.5f;

	color.rgb *= float3(0.7f, 1.0f, 0.95f);

	return color;
}