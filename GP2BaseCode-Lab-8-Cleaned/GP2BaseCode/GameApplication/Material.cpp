#include "Material.h"

#include "../D3D10Renderer/D3D10Renderer.h"

bool Material::loadEffect(const string& filename,IRenderer * pRenderer)
{
	D3D10Renderer *pD3D10Renderer=static_cast<D3D10Renderer*>(pRenderer);

	m_pEffect=pD3D10Renderer->loadEffectFromFile(filename.c_str());
	if (!m_pEffect)
	{
		return false;
	}
	m_pCurrentTechnique=m_pEffect->GetTechniqueByIndex(0);
	return true;
}

bool Material::loadDiffuseTexture(const string& filename,IRenderer * pRenderer)
{
	D3D10Renderer *pD3D10Renderer=static_cast<D3D10Renderer*>(pRenderer);

	m_pDiffuseTexture=pD3D10Renderer->loadTexture(filename.c_str());
	if (!m_pDiffuseTexture)
	{
		return false;
	}
	return true;
}

bool Material::loadSpecularTexture(const string& filename,IRenderer * pRenderer)
{
	D3D10Renderer *pD3D10Renderer=static_cast<D3D10Renderer*>(pRenderer);

	m_pSpecularTexture=pD3D10Renderer->loadTexture(filename.c_str());
	if (!m_pSpecularTexture)
	{
		return false;
	}
	return true;
}

bool Material::loadDecalView(const string& filename,IRenderer * pRenderer)
{
	D3D10Renderer *pD3D10Renderer=static_cast<D3D10Renderer*>(pRenderer);

	m_pDecalView=pD3D10Renderer->loadTexture(filename.c_str());
	if (!m_pDecalView)
	{
		return false;
	}
	return true;
}

bool Material::loadNormalMap(const string& filename,IRenderer * pRenderer)
{
	D3D10Renderer *pD3D10Renderer=static_cast<D3D10Renderer*>(pRenderer);

	m_pNormalMap=pD3D10Renderer->loadTexture(filename.c_str());
	if (!m_pNormalMap)
	{
		return false;
	}
	return true;
}

bool Material::loadHeightMap(const string& filename,IRenderer * pRenderer)
{
	D3D10Renderer *pD3D10Renderer=static_cast<D3D10Renderer*>(pRenderer);

	m_pHeightMap=pD3D10Renderer->loadTexture(filename.c_str());
	if (!m_pHeightMap)
	{
		return false;
	}
	return true;
}
void Material::switchTechnique(const string& name)
{
	if (m_pEffect)
	{
		m_pCurrentTechnique=m_pEffect->GetTechniqueByName(name.c_str());
	}
}

bool Material::loadRenderViewAsDiffuse(IRenderer * pRenderer)
{
	D3D10Renderer *pD3D10Renderer=static_cast<D3D10Renderer*>(pRenderer);

	m_pDiffuseTexture=pD3D10Renderer->getRenderTexture();
	if (!m_pDiffuseTexture)
	{
		return false;
	}
	return true;
}