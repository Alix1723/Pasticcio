#pragma once

//http://www.gamedev.net/topic/506017-quick-question-about-id3d10inputlayout/
//The header file for the renderer interface
#include "../Renderer/Renderer.h"

#include <Windows.h>

#include <D3D10.h>
#include <D3DX10.h>

#define _XM_NO_INTRINSICS_
#include <xnamath.h>
#include <queue>
#include <string>

#include "Vertex.h"

using namespace std;

//D3D10Renderer implements the Renderer interface
class D3D10Renderer:public IRenderer
{
public:
	D3D10Renderer();
	~D3D10Renderer();
	//notice these have the same signature as the pure methods
	//in the interface
	bool init(void *pWindowHandle,bool fullScreen);
	void clear(float r,float g,float b,float a);
	void present();
	void render();
	void setRenderTarget(int target);

	ID3D10Effect * loadEffectFromMemory(const char *pMem);
	ID3D10Effect * loadEffectFromFile(const char *pFilename);

	ID3D10Buffer * createVertexBuffer(int size,Vertex *pVerts);
	ID3D10Buffer * createIndexBuffer(int size,int *pIndices);
	ID3D10InputLayout * createVertexLayout(ID3D10Effect * pEffect);
	ID3D10ShaderResourceView * loadTexture(const string& fileName);

	ID3D10ShaderResourceView * getRenderTexture();

	void setAmbientLightColour(float r, float g , float b, float a)
	{
		m_pAmbientLightColour = XMFLOAT4(r,g,b,a);
	};

	void addToRenderQueue(GameObject *pObject);

	//Setting Matrices
	void setViewMatrix(XMMATRIX& sView)
	{
		m_pViewMatrix = sView;//
	};

	void setProjectionMatrix(XMMATRIX& sProj)
	{
		m_pProjectionMatrix = sProj;
	};

	//Set main light
	void setMainLight(GameObject *light)
	{
		m_pMainLight = light;
	};

	void setMainCamera(GameObject *camera)
	{
		m_pMainCamera = camera;
	};

private:
	bool createDevice(HWND pWindowHandle,int windowWidth, int windowHeight,
						bool fullScreen);
	bool createInitialRenderTarget(int windowWidth, int windowHeight);
	bool createPostFXRenderTarget(int windowWidth, int windowHeight);
	void render(GameObject *pCurrentObject);

private:
	typedef std::queue<GameObject*> RenderQueue;
	//D3D10 stuff
	ID3D10Device * m_pD3D10Device;
	IDXGISwapChain * m_pSwapChain;
	ID3D10RenderTargetView * m_pRenderTargetView;
	ID3D10DepthStencilView * m_pDepthStencelView;
	ID3D10Texture2D *m_pDepthStencilTexture;

	ID3D10Texture2D *m_pPostFXRenderTexture;
	ID3D10RenderTargetView *m_pPostFXRenderView;
	ID3D10ShaderResourceView *m_pPostFXShaderResView;

	//Camera matrices
	XMMATRIX m_pViewMatrix;
	XMMATRIX m_pProjectionMatrix;

	//Vertex Layout
	ID3D10InputLayout*      m_pDefaultVertexLayout;
	//this will be used if we have no Effect
	ID3D10Effect * m_pDefaultEffect;
	ID3D10EffectTechnique * m_pDefaultTechnique;

	//Ambient Colour
	XMFLOAT4  m_pAmbientLightColour;

	GameObject * m_pMainLight;
	GameObject * m_pMainCamera;

	RenderQueue m_RenderQueue;
};