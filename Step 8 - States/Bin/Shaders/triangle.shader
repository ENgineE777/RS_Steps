
cbuffer vs_params : register( b0 )
{
    matrix trans;
};

cbuffer ps_params : register( b0 )
{
	float4 color;
};

struct VS_INPUT
{
    float3 position : POSITION;
    float2 texCoord : TEXCOORD;
};

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float2 texCoord : TEXCOORD;
};

Texture2D diffuseMap : register(t0);
SamplerState samLinear : register(s0);

PS_INPUT VS( VS_INPUT input )
{
	PS_INPUT output = (PS_INPUT)0;

	output.Pos = mul(float4(input.position, 1.0f), trans);
    output.texCoord = input.texCoord;

	return output;
}

float4 PS( PS_INPUT input) : SV_Target
{
	return diffuseMap.Sample(samLinear, input.texCoord) * color;
}