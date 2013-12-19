#include "QuadVisualComponent.h"
#include "../D3D10Renderer/Vertex.h"
#include "../D3D10Renderer/D3D10Renderer.h"

bool QuadVisualComponent::create(IRenderer * pRenderer)
{	
	m_iNoVerts=4;
	Vertex verts[4];
	verts[0].position = XMFLOAT3(-1.0f, -1.0f, 0.0f);	//		(0)-------(3)		    
	verts[1].position = XMFLOAT3(-1.0f,  1.0f, 0.0f);	//	    /         /		   
	verts[2].position = XMFLOAT3( 1.0f,  1.0f, 0.0f);	//     /         / 			
	verts[3].position = XMFLOAT3( 1.0f, -1.0f, 0.0f);	//	 (1)-------(2) 			
	

	verts[0].textureCoords = XMFLOAT2(0.0f, 1.0f);
	verts[1].textureCoords = XMFLOAT2(0.0f, 0.0f);
	verts[2].textureCoords = XMFLOAT2(1.0f, 0.0f);
	verts[3].textureCoords = XMFLOAT2(1.0f, 1.0f);
	

	/*verts[0].normal = XMFLOAT3(-1.0f / sqrt(3.0f), -1.0f / sqrt(3.0f), -1.0f / sqrt(3.0f));
	verts[1].normal = XMFLOAT3(-1.0f / sqrt(3.0f),  1.0f / sqrt(3.0f), -1.0f / sqrt(3.0f));
	verts[2].normal = XMFLOAT3( 1.0f / sqrt(3.0f), -1.0f / sqrt(3.0f), -1.0f / sqrt(3.0f));
	verts[3].normal = XMFLOAT3( 1.0f / sqrt(3.0f),  1.0f / sqrt(3.0f), -1.0f / sqrt(3.0f));*/
	
	m_iNoIndices = 6;
	int indices[6] = {0, 1, 2, 
						2, 3, 0};

	D3D10Renderer *pD3D10Renderer=static_cast<D3D10Renderer*>(pRenderer);

	m_pVertexBuffer=pD3D10Renderer->createVertexBuffer(m_iNoVerts,verts);
	m_pIndexBuffer=pD3D10Renderer->createIndexBuffer(m_iNoIndices,indices);
	

	return true;
}