float4x4 matProjection:PROJECTION;

Texture2D renderedView;

struct VS_INPUT
{
	float4 pos:POSITION;
	float2 texCoord;
};

struct PS_INPUT
{
	float4 pos:SV_POSITION;
	float4 col:COLOR;
};

PS_INPUT VS(VS_INPUT input)
{
	PS_INPUT output=(PS_INPUT)0;
	output.pos=mul(input.pos,matProjection);
	return output;
}

SamplerState sceneSampler
{
    Filter = MIN_MAG_LINEAR_MIP_POINT;
    AddressU = Clamp;
    AddressV = Clamp;
};

float4 PS(PS_INPUT input):SV_TARGET
{
	return renderedView.Sample(sceneSampler,input.texCoord);     
}

RasterizerState DisableCulling
{
    CullMode = NONE;
};

technique10 Render
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_4_0, VS() ) );
		SetGeometryShader( NULL );
		SetPixelShader( CompileShader( ps_4_0,  PS() ) );
		SetRasterizerState(DisableCulling); 
	}
}