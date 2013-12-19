#pragma once

#include "GameComponent.h"

#include <windows.h>
#define _XM_NO_INTRINSICS_
#include <xnamath.h>

#include "D3D10.h"
#include "../Renderer/Renderer.h"

#include <string>

using namespace std;

class Material:public GameComponent
{
public:
	Material()
	{
		m_Name="Material";
		m_pEffect=NULL;
		m_pCurrentTechnique=NULL;
		m_Ambient=XMFLOAT4(0.3f,0.3f,0.3f,1.0f);
		m_Diffuse=XMFLOAT4(0.5f,0.5f,0.5f,1.0f);
		m_Specular=XMFLOAT4(1.0f,1.0f,1.0f,1.0f);
		m_pDiffuseTexture = NULL;
		m_pSpecularTexture = NULL;
		m_pNormalMap = NULL;
		m_pHeightMap = NULL;
	};

	~Material()
	{
		if (m_pEffect)
		{
			m_pEffect->Release();
			m_pEffect=NULL;
		}
		if (m_pDiffuseTexture)
		{
			m_pDiffuseTexture->Release();
			m_pDiffuseTexture=NULL;
		}
		if (m_pSpecularTexture)
		{
			m_pSpecularTexture->Release();
			m_pSpecularTexture=NULL;
		}
		if (m_pNormalMap)
		{
			m_pNormalMap->Release();
			m_pNormalMap=NULL;
		}
		if (m_pHeightMap)
		{
			m_pHeightMap->Release();
			m_pHeightMap=NULL;
		}
	};

	void setAmbient(float r,float g,float b,float a)
	{
		m_Ambient=XMFLOAT4(r,g,b,a);
	};

	XMFLOAT4& getAmbient()
	{
		return m_Ambient;
	};

	void setDiffuse(float r,float g,float b,float a)
	{
		m_Diffuse=XMFLOAT4(r,g,b,a);
	};

	XMFLOAT4& getDiffuse()
	{
		return m_Diffuse;
	};
	
	void setSpecular(float r,float g,float b,float a)
	{
		m_Specular=XMFLOAT4(r,g,b,a);
	};

	XMFLOAT4& getSpecular()
	{
		return m_Specular;
	};

	bool loadEffect(const string& filename,IRenderer * pRenderer);
	bool loadDiffuseTexture(const string& filename,IRenderer * pRenderer);
	bool loadSpecularTexture(const string& filename,IRenderer * pRenderer);

	bool loadDecalView(const string& filename,IRenderer * pRenderer);
	bool loadNormalMap(const string& filename,IRenderer * pRenderer);
	bool loadHeightMap(const string& filename,IRenderer * pRenderer);
	
	bool loadRenderViewAsDiffuse(IRenderer * pRenderer);

	void switchTechnique(const string& name);


	ID3D10Effect * getEffect()
	{
		return m_pEffect;
	};

	ID3D10EffectTechnique * getCurrentTechnique()
	{
		return m_pCurrentTechnique;
	};

	ID3D10ShaderResourceView * getDiffuseTexture()
	{
		return m_pDiffuseTexture;
	};

	ID3D10ShaderResourceView * getSpecularTexture()
	{
		return m_pSpecularTexture;
	};

	ID3D10ShaderResourceView * getDecalView()
	{
		return m_pDecalView;
	};

	ID3D10ShaderResourceView * getNormalMap()
	{
		return m_pNormalMap;
	};

	ID3D10ShaderResourceView * getHeightMap()
	{
		return m_pHeightMap;
	};
private:
	XMFLOAT4 m_Ambient;
	XMFLOAT4 m_Diffuse;
	XMFLOAT4 m_Specular;
	ID3D10Effect *m_pEffect;
	ID3D10EffectTechnique *m_pCurrentTechnique;
	ID3D10ShaderResourceView *m_pDiffuseTexture;
	ID3D10ShaderResourceView *m_pSpecularTexture;
	ID3D10ShaderResourceView *m_pDecalView;
	ID3D10ShaderResourceView *m_pNormalMap;
	ID3D10ShaderResourceView *m_pHeightMap;
};