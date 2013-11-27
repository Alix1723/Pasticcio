#include "CubeVisualComponent.h"
#include "../D3D10Renderer/Vertex.h"
#include "../D3D10Renderer/D3D10Renderer.h"

bool CubeVisualComponent::create(IRenderer * pRenderer)
{
	/*
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
	*/

	m_iNoVerts=8;
	Vertex verts[8];
	verts[0].position = XMFLOAT3(-1.0f, -1.0f,  1.0f);
	verts[1].position = XMFLOAT3(-1.0f,  1.0f,  1.0f);
	verts[2].position = XMFLOAT3( 1.0f, -1.0f,  1.0f);
	verts[3].position = XMFLOAT3( 1.0f,  1.0f,  1.0f);
	verts[4].position = XMFLOAT3(-1.0f, -1.0f, -1.0f);
	verts[5].position = XMFLOAT3(-1.0f,  1.0f, -1.0f);
	verts[6].position = XMFLOAT3( 1.0f, -1.0f, -1.0f);
	verts[7].position = XMFLOAT3( 1.0f,  1.0f, -1.0f);

	m_iNoIndices = 36;
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

	// Calculate the normals
	int ii = 0;
	for(int i = 0; i < m_iNoVerts; ++i)
	{
		XMFLOAT3 result;	// cross product of vec1 and vec2
		XMFLOAT3 vec1;		// vec1 = B - A		example first calc: B = verts[1] and A = verts[0]
		XMFLOAT3 vec2;		// vec2 = C - B

		vec1.x = verts[indices[ii+1]].position.x - verts[indices[ii]].position.x;
		vec1.y = verts[indices[ii+1]].position.y - verts[indices[ii]].position.y;
		vec1.z = verts[indices[ii+1]].position.z - verts[indices[ii]].position.z;

		vec2.x = verts[indices[ii+2]].position.x - verts[indices[ii+1]].position.x;
		vec2.y = verts[indices[ii+2]].position.y - verts[indices[ii+1]].position.y;
		vec2.z = verts[indices[ii+2]].position.z - verts[indices[ii+1]].position.z;

		// calculate the cross product
		result.x = (vec1.y * vec2.z) - (vec1.z * vec2.y);
		result.y = (vec1.z * vec2.x) - (vec1.x * vec2.z);
		result.z = (vec1.x * vec2.y) - (vec1.y * vec2.x);

		verts[i].normal = result;

		ii += 6;		// increasing the counter for the indices to jump to the next face / vertex
	}

	D3D10Renderer *pD3D10Renderer=static_cast<D3D10Renderer*>(pRenderer);

	m_pVertexBuffer=pD3D10Renderer->createVertexBuffer(m_iNoVerts,verts);
	m_pIndexBuffer=pD3D10Renderer->createIndexBuffer(m_iNoIndices,indices);
	

	return true;
}