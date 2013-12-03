float4x4 matWorld:WORLD<string UIWidget="None";>;
float4x4 matView:VIEW<string UIWidget="None";>;
float4x4 matProjection:PROJECTION<string UIWidget="None";>;

float4 ambientMaterial
<
	string UIName="Ambient Material";
	string UIWidget="Color";
>;

float4 ambientLightColour
<
	string UIName="Ambient Light Colour";
	string UIWidget="Color";
>;


float4 objectColour
<
	string UIName="Object Colour";
	string UIWidget="Color";
> = {1,1,1,1};

float3 lightDirection:DIRECTION<
		string Object="DirectionalLight";
		string UIWidget="None";
>;

float4 diffuseMaterial:DIFFUSE<
	string UIName="Diffuse Material";
	string UIWidget="Color";
	string Object="DirectionalLight";
>;

float4 diffuseLightColour:COLOR<
	string UIName="Light Colour";
	string UIWiget="Color";
	string Object="DirectionalLight";
	string UIWidget="None";
>;


float4 specularMaterial:COLOR<
	string UIName="Specular Material";
	string UIWiget="Color";
>;

float4 specularLightColour:COLOR<
	string UIName="Specular Light Colour";
	string UIWiget="Color";
>;

float4 cameraPosition;

float specularLevel<
		string UIWidget = "slider";
		float UIMin = 0.0;
		float UIMax = 25;
		float UIStep = 1;
		string UIName = "Specular Level";
> = 0.9;;


struct VS_INPUT
{
	float4 pos:POSITION;	
	float3 normal:NORMAL;
};

struct PS_INPUT
{
	float4 pos:SV_POSITION;
	float3 normal:NORMAL;
	float4 cameraDirection:VIEWDIR;
};

PS_INPUT VS(VS_INPUT input)
{
	PS_INPUT output=(PS_INPUT)0;
	
	float4x4 matViewProjection=mul(matView,matProjection);
	float4x4 matWorldViewProjection=mul(matWorld,matViewProjection);
	
	output.pos=mul(input.pos,matWorldViewProjection);
	output.normal=mul(input.normal,matWorld);
	float4 worldPos=mul(input.pos,matWorld);
	output.cameraDirection=normalize(cameraPosition-worldPos);
	
	return output;
}

float4 PS(PS_INPUT input):SV_TARGET
{
	float3 normal=normalize(input.normal);
	float3 lightDir=normalize(lightDirection);
	float diffuseHighlight=saturate(dot(normal,lightDir));
	float3 halfVec=normalize(lightDir+input.cameraDirection);
	float specular=pow(saturate(dot(normal,halfVec)),specularLevel);

	return (ambientMaterial*ambientLightColour)+(diffuseMaterial*diffuseLightColour*diffuseHighlight)+(specularMaterial*specularLightColour*specular);	
}

RasterizerState DisableCulling
{
	CullMode = NONE;	
};

technique10 Render
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_4_0, VS()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_4_0, PS()));
		SetRasterizerState(DisableCulling);
	}
}