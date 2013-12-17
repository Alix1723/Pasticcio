/*
   Parallax Bump Mapping - Direct3D 10
   Game Graphics Programming
   Created by Allen Sherrod
*/


float4 lightPos;
float4 eyePos;


Texture2D decal;
Texture2D normalMap;
Texture2D heightMap;

SamplerState DecalSampler
{
   Filter = MIN_MAG_MIP_LINEAR;
   AddressU = Wrap;
   AddressV = Wrap;
};

SamplerState NormalMapSampler
{
   Filter = MIN_MAG_MIP_POINT;
   AddressU = Clamp;
   AddressV = Clamp;
};


DepthStencilState DepthStencilInfo
{
   DepthEnable = true;
   DepthWriteMask = ALL;
   DepthFunc = Less;
};


cbuffer cbChangesEveryFrame
{
   matrix World;
   matrix View;
};

cbuffer cbChangeOnResize
{
   matrix Projection;
};


struct VS_INPUT
{
   float4 Pos : POSITION;
   float2 Tex : TEXCOORD;
   float3 Norm : NORMAL;
   float3 STan : TANGENT;
};

struct PS_INPUT
{
   float4 Pos : SV_POSITION;
   float2 Tex : TEXCOORD0;
   float3 LightVec : TEXCOORD1;
   float3 ViewVec : TEXCOORD2;
};


PS_INPUT VS(VS_INPUT input)
{
   PS_INPUT output = (PS_INPUT)0;

   float4 Pos = mul(input.Pos, World);
   Pos = mul(Pos, View);
   output.Pos = mul(Pos, Projection);

   output.Tex = input.Tex;

   float3 normal = mul(input.Norm, World);
   normal = mul(normal, View);

   float3 bTangent = cross(input.STan, normal);

   float3x3 tbnMatrix = float3x3(input.STan, bTangent, normal);

   output.LightVec = lightPos.xyz - Pos.xyz;
   output.ViewVec = eyePos.xyz - Pos.xyz;
   
   output.LightVec = mul(output.LightVec, tbnMatrix);
   output.ViewVec = mul(output.ViewVec, tbnMatrix);
   
   return output;
}


float4 PS(PS_INPUT input) : SV_Target
{
   float3 lightVec = normalize(input.LightVec);
   float3 viewVec = normalize(input.ViewVec);

   float scale = 0.03;
   float bias = 0.01;

   float heightVal = heightMap.Sample(DecalSampler, input.Tex);
   float height = scale * heightVal - bias;
   float2 newTexCoord = height * viewVec.xy + input.Tex;
   
   float3 normal = normalMap.Sample(NormalMapSampler, newTexCoord);
   normal = (normal - 0.5) * 2;
   normal = normalize(normal);

   float diffuse = saturate(dot(normal, lightVec));

   return decal.Sample(DecalSampler, newTexCoord) * diffuse;
}


technique10 ParallaxMapping
{
   pass P0
   {
      SetDepthStencilState(DepthStencilInfo, 0);

      SetVertexShader(CompileShader(vs_4_0, VS()));
      SetGeometryShader(NULL);
      SetPixelShader(CompileShader(ps_4_0, PS()));
   }
}
