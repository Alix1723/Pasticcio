#include "CubeVisualComponent.h"
#include "../D3D10Renderer/Vertex.h"
#include "../D3D10Renderer/D3D10Renderer.h"

bool CubeVisualComponent::create(IRenderer * pRenderer)
{
	m_iNoVerts=8;
	Vertex verts[8];
	verts[0].position = XMFLOAT3(-1.0f, -1.0f, -1.0f);	//		(5)-------(7)		    y
	verts[1].position = XMFLOAT3(-1.0f,  1.0f, -1.0f);	//	    /|        /|		    ^    ´` z
	verts[2].position = XMFLOAT3( 1.0f, -1.0f, -1.0f);	//     / |       / |			|   /
	verts[3].position = XMFLOAT3( 1.0f,  1.0f, -1.0f);	//	 (1)-|-----(3) |			|  /
	verts[4].position = XMFLOAT3(-1.0f, -1.0f,  1.0f);	//    |	(4)-----|-(6)			| /
	verts[5].position = XMFLOAT3(-1.0f,  1.0f,  1.0f);	//    | /       | /				|/---------- > x  
	verts[6].position = XMFLOAT3( 1.0f, -1.0f,  1.0f);	//    |/        |/              0
	verts[7].position = XMFLOAT3( 1.0f,  1.0f,  1.0f);	//   (0)-------(2)

	verts[0].textureCoords = XMFLOAT2(0.0f, 1.0f);
	verts[1].textureCoords = XMFLOAT2(0.0f, 0.0f);
	verts[2].textureCoords = XMFLOAT2(1.0f, 1.0f);
	verts[3].textureCoords = XMFLOAT2(1.0f, 0.0f);
	verts[4].textureCoords = XMFLOAT2(0.0f, 1.0f);
	verts[5].textureCoords = XMFLOAT2(0.0f, 0.0f);
	verts[6].textureCoords = XMFLOAT2(1.0f, 1.0f);
	verts[7].textureCoords = XMFLOAT2(1.0f, 0.0f);

	// normals for the vertices: (vertex - center) or vertex it self in this case, since center is at origin.
	// normalizitation by dividing with sqrt(3)
	verts[0].normal = XMFLOAT3(-1.0f / sqrt(3.0f), -1.0f / sqrt(3.0f), -1.0f / sqrt(3.0f));
	verts[1].normal = XMFLOAT3(-1.0f / sqrt(3.0f),  1.0f / sqrt(3.0f), -1.0f / sqrt(3.0f));
	verts[2].normal = XMFLOAT3( 1.0f / sqrt(3.0f), -1.0f / sqrt(3.0f), -1.0f / sqrt(3.0f));
	verts[3].normal = XMFLOAT3( 1.0f / sqrt(3.0f),  1.0f / sqrt(3.0f), -1.0f / sqrt(3.0f));
	verts[4].normal = XMFLOAT3(-1.0f / sqrt(3.0f), -1.0f / sqrt(3.0f),  1.0f / sqrt(3.0f));
	verts[5].normal = XMFLOAT3(-1.0f / sqrt(3.0f),  1.0f / sqrt(3.0f),  1.0f / sqrt(3.0f));
	verts[6].normal = XMFLOAT3( 1.0f / sqrt(3.0f), -1.0f / sqrt(3.0f),  1.0f / sqrt(3.0f));
	verts[7].normal = XMFLOAT3( 1.0f / sqrt(3.0f),  1.0f / sqrt(3.0f),  1.0f / sqrt(3.0f));
	

	m_iNoIndices = 36;
	int indices[36] = {0, 1, 2, // front face	0
					  1, 2, 3,

					  4, 5, 6,	// back face	1
					  5, 6, 7,

					  4, 5, 0,	// left face	2
					  5, 0, 1,

					  2, 3, 6,	// right face	3
					  3, 6, 7,

					  1, 5, 3,	// top face		4
					  5, 3, 7,

					  0, 4, 2,	// bottom face	5
					  4, 2, 6};


	D3D10Renderer *pD3D10Renderer=static_cast<D3D10Renderer*>(pRenderer);

	m_pVertexBuffer=pD3D10Renderer->createVertexBuffer(m_iNoVerts,verts);
	m_pIndexBuffer=pD3D10Renderer->createIndexBuffer(m_iNoIndices,indices);
	

	return true;
}