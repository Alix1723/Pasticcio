#include "CubeVisualComponent.h"
#include "../D3D10Renderer/Vertex.h"
#include "../D3D10Renderer/D3D10Renderer.h"

bool CubeVisualComponent::create(IRenderer * pRenderer)
{
	m_iNoVerts=8;
	Vertex verts[8] = {														// cube			
	//	  pos		x, 	    y,     z 		tex coord  x   y			normals:  x		 y		z
		{XMFLOAT3(-1.0f, -1.0f,  1.0f),		XMFLOAT2(0.0f, 0.0f),		XMFLOAT3(0.0f,  0.5f,  0.5f)},	// front face 
		{XMFLOAT3(-1.0f,  1.0f,  1.0f),		XMFLOAT2(0.0f, 0.0f),		XMFLOAT3(0.0f,  0.5f,  0.5f)},	// 
		{XMFLOAT3( 1.0f, -1.0f,  1.0f),		XMFLOAT2(0.0f, 0.0f),		XMFLOAT3(0.0f, -0.5f,  0.5f)},	// 
		{XMFLOAT3( 1.0f,  1.0f,  1.0f),		XMFLOAT2(0.0f, 0.0f),		XMFLOAT3(0.0f, -0.5f,  0.5f)},	//

		{XMFLOAT3(-1.0f, -1.0f, -1.0f),		XMFLOAT2(0.0f, 0.0f),		XMFLOAT3(0.0f,  0.5f, -0.5f)},	// back face
		{XMFLOAT3(-1.0f,  1.0f, -1.0f),		XMFLOAT2(0.0f, 0.0f),		XMFLOAT3(0.0f,  0.5f, -0.5f)},	// 
		{XMFLOAT3( 1.0f, -1.0f, -1.0f),		XMFLOAT2(0.0f, 0.0f),		XMFLOAT3(0.0f, -0.5f, -0.5f)},	// 
		{XMFLOAT3( 1.0f,  1.0f, -1.0f),		XMFLOAT2(0.0f, 0.0f),		XMFLOAT3(0.0f, -0.5f, -0.5f)}	// 
	};

	int indices[36] = {0, 1, 2, // front face
					  1, 2, 3,

					  4, 5, 6,	// back face
					  5, 6, 7,

					  4, 5, 0,	// left face
					  5, 0, 1,

					  2, 3, 6,	// right face
					  3, 6, 7,

					  1, 5, 3,	// top face
					  5, 3, 7,

					  0, 4, 2,	// bottom face
					  4, 2, 6};
	m_iNoIndices = 36;

	D3D10Renderer *pD3D10Renderer=static_cast<D3D10Renderer*>(pRenderer);

	m_pVertexBuffer=pD3D10Renderer->createVertexBuffer(m_iNoVerts,verts);
	m_pIndexBuffer=pD3D10Renderer->createIndexBuffer(m_iNoIndices,indices);
	

	return true;
}