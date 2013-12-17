float4x4 matWorld:WORLD<string UIWidget="None";>;
float4x4 matView:VIEW<string UIWidget="None";>;
float4x4 matProjection:PROJECTION<string UIWidget="None";>;

float4 ambientMaterial<
	string UIName="Ambient Material";
	string UIWidget="Color";
> = float4(0.5f,0.5f,0.5f,1.0f);

float4 diffuseMaterial<
	string UIName="Diffuse Material";
	string UIWidget="Color";
	string Object="DirectionalLight";
> = float4(0.8f,0.8f,0.8f,1.0f);

float4 specularMaterial<
	string UIName="Specular Material";
	string UIWiget="Color";
> = float4(1.0f,1.0f,1.0f,1.0f);


float4 ambientLightColour<
	string UIName="Ambient Light";
	string UIWiget="Color";
> = float4(1.0f,1.0f,1.0f,1.0f);

float3 lightDirection:DIRECTION<
		string Object="DirectionalLight";
>;

float4 diffuseLightColour:DIFFUSE<
	string UIName="DirectionalLight";
> = float4(1.0f,1.0f,1.0f,0.0f);

float4 specularLightColour:SPECULAR<
	string UIName="DirectionalLight";
> = float4(1.0f,1.0f,1.0f,0.0f);

float specularPower<
	string UIName = "Specular Level";
	string UIWidget = "Slider";
	float UIMin = 0.0;
	float UIMax = 25;
	float UIStep = 1;	
> = 25.0f;
 
float4 cameraPosition;

Texture2D diffuseTexture;
Texture2D specularTexture;

SamplerState wrapSampler
{
	Filter = MIN_MAG_LINEAR_MIP_POINT;
	AddressU= Wrap;
	AddressV= Wrap;
};


struct VS_INPUT
{
	float4 pos:POSITION;	
	float2 texCoord:TEXCOORD0;
	float3 normal:NORMAL;
	
};

struct PS_INPUT
{
	float4 pos:SV_POSITION;
	float3 normal:NORMAL;
	float4 cameraDirection:VIEWDIR;
	float2 texCoord:TEXCOORD0;
};

PS_INPUT VS(VS_INPUT input)
{
        PS_INPUT output=(PS_INPUT)0;
        
        float4x4 matViewProjection=mul(matView,matProjection);
        float4x4 matWorldViewProjection=mul(matWorld,matViewProjection);
        output.pos=mul(input.pos,matWorldViewProjection);
		output.normal=normalize(mul(input.normal,matWorld));

		float4 worldPos=mul(input.pos,matWorld);
        output.cameraDirection=normalize(cameraPosition-worldPos);
                 

        output.texCoord=input.texCoord;
        return output;
}

float4 PS(PS_INPUT input):SV_TARGET
{

    float3 normal=normalize(input.normal);        
    float3 lightDir=normalize(lightDirection);
       
    float diffuse=saturate(dot(normal,lightDir));
        
    float3 halfVec=normalize(lightDir+input.cameraDirection);
    float specular=pow(saturate(dot(normal,halfVec)),specularPower);
    float4 finalTexture = diffuseTexture.Sample(wrapSampler , input.texCoord);


    return ((ambientMaterial*ambientLightColour)+
			((diffuseMaterial*finalTexture)*(diffuseLightColour*diffuse))+
			(specularMaterial*specularLightColour*specular));
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
