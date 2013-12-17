#include "ModelLoader.h"
#include "GameObject.h"
#include "Components.h"

#include "../D3D10Renderer/D3D10Renderer.h"

#include <fbxsdk.h>

GameObject * ModelLoader::loadModelFromFile(const string& filename, IRenderer *pRenderer)
{
	GameObject *pObject=NULL;

	string extension=filename.substr(filename.find('.')+1);

	if (extension.compare("fbx")==0)
		pObject=loadFbxModelFromFile(filename,pRenderer);
	return pObject;
}

GameObject * ModelLoader::loadFbxModelFromFile(const string& filename, IRenderer *pRenderer)
{
	//Null Game Object
	GameObject *pRootObject=NULL;
	int noVerts=0;
	int noIndices=0;
	int *pIndices=NULL;
	Vertex * pVerts=NULL;

	FbxManager* lSdkManager = FbxManager::Create();
	FbxIOSettings *ios = FbxIOSettings::Create(lSdkManager, IOSROOT);
	lSdkManager->SetIOSettings(ios);

	// Create an importer using our sdk manager.
	FbxImporter* lImporter = FbxImporter::Create(lSdkManager,"");
	FbxGeometryConverter converter( lSdkManager);

	// Use the first argument as the filename for the importer.
	if(!lImporter->Initialize(filename.c_str(), -1, lSdkManager->GetIOSettings())) {
		return NULL;
	}

	// Create a new scene so it can be populated by the imported file.
	FbxScene* lScene = FbxScene::Create(lSdkManager,"myScene");
	FbxAxisSystem SceneAxisSystem = lScene->GetGlobalSettings().GetAxisSystem();


	INT iUpAxisSign;
	FbxAxisSystem::EUpVector UpVector = SceneAxisSystem.GetUpVector( iUpAxisSign );

	// Import the contents of the file into the scene.
	lImporter->Import(lScene);

	// The file has been imported; we can get rid of the importer.
	lImporter->Destroy();
	FbxNode* lRootNode = lScene->GetRootNode();
	FbxMesh * pMesh=NULL;
	if(lRootNode) {
		pRootObject=new GameObject();
		pRootObject->setName(lRootNode->GetName());
		for (int i=0;i<lRootNode->GetChildCount();i++){
			FbxNode * modelNode=lRootNode->GetChild(i);
			for(int i=0;i<modelNode->GetNodeAttributeCount();i++)
			{
				FbxNodeAttribute *pAttributeNode=modelNode->GetNodeAttributeByIndex(i);
				if (pAttributeNode->GetAttributeType()==FbxNodeAttribute::eMesh)
				{
					//found mesh
					pMesh=(FbxMesh*)pAttributeNode;
					if (pMesh)
					{
						GameObject *pChildGO=new GameObject();
						pChildGO->setName(pMesh->GetName());
						//pMesh=converter.TriangulateMesh(pMesh);
						FbxVector4 * verts=pMesh->GetControlPoints();
						int noVerts=pMesh->GetControlPointsCount();

						int noIndices=pMesh->GetPolygonVertexCount();
						int *pIndices=pMesh->GetPolygonVertices();

						Vertex * pVerts=new Vertex[noVerts];
						for(int i=0;i<noVerts;i++)
						{

							pVerts[i].position.x=verts[i][0];
							pVerts[i].position.y=verts[i][1];
							pVerts[i].position.z=verts[i][2];
						}
						for (int iPolygon = 0; iPolygon < pMesh->GetPolygonCount(); iPolygon++) { 
							for (unsigned iPolygonVertex = 0; iPolygonVertex < 3; iPolygonVertex++) {        
								int fbxCornerIndex = pMesh->GetPolygonVertex(iPolygon, iPolygonVertex);
								FbxVector4 fbxVertex = verts[fbxCornerIndex];

								FbxVector4 fbxNormal;        
								pMesh->GetPolygonVertexNormal(iPolygon, iPolygonVertex, fbxNormal);        
								fbxNormal.Normalize();        
								pVerts[fbxCornerIndex].normal.x=fbxNormal[0];
								pVerts[fbxCornerIndex].normal.y=fbxNormal[1];
								pVerts[fbxCornerIndex].normal.z=fbxNormal[2];

								FbxVector2 fbxUV = FbxVector2(0.0, 0.0);        
								FbxLayerElementUV* fbxLayerUV = pMesh->GetLayer(0)->GetUVs();
								// Get texture coordinate        
								if (fbxLayerUV) {                
									int iUVIndex = 0;                
									switch (fbxLayerUV->GetMappingMode()) {        
									case FbxLayerElement::eByControlPoint:
										iUVIndex = fbxCornerIndex;                                
										break;        
									case FbxLayerElement::eByPolygonVertex:
										iUVIndex = pMesh->GetTextureUVIndex(iPolygon, iPolygonVertex, FbxLayerElement::eTextureDiffuse);        
										break;                
									}                
									fbxUV = fbxLayerUV->GetDirectArray().GetAt(iUVIndex);        
									pVerts[fbxCornerIndex].textureCoords.x=fbxUV[0];
									pVerts[fbxCornerIndex].textureCoords.y= 1.0f-fbxUV[1];
								}
							}
						}

						computeTangents(pVerts,noVerts);

						VisualComponent *pVisualComponent=new VisualComponent();
						pVisualComponent->createVertexBuffer(noVerts,pVerts,pRenderer);
						pVisualComponent->createIndexBuffer(noIndices,pIndices,pRenderer);
						pChildGO->addComponent(pVisualComponent);
						pRootObject->addChild(pChildGO);
						if (pVerts)
						{
							delete [] pVerts;
							pVerts=NULL;
						}
					}
				}
			}
		}
	}

	return pRootObject;
}

void ModelLoader::computeTangents(Vertex *pVerts,int vertexCount) 
{ 
    int triCount=vertexCount/3; 
    XMFLOAT3 * tan1=new XMFLOAT3[vertexCount]; 
    XMFLOAT3 * tan2=new XMFLOAT3[vertexCount]; 
  
    for (int i=0;i<triCount;i+=3) 
    { 
        XMFLOAT3 v1=pVerts[i].position; 
        XMFLOAT3 v2=pVerts[i+1].position; 
        XMFLOAT3 v3=pVerts[i+2].position; 
  
        XMFLOAT3 uv1=XMFLOAT3((float*)&pVerts[i].textureCoords); 
        XMFLOAT3 uv2=XMFLOAT3((float*)&pVerts[i+1].textureCoords); 
        XMFLOAT3 uv3=XMFLOAT3((float*)&pVerts[i+2].textureCoords); 
              
        float x1 = v2.x - v1.x; 
        float x2 = v3.x - v1.x; 
        float y1 = v2.y - v1.y; 
        float y2 = v3.y - v1.y; 
        float z1 = v2.z - v1.z; 
        float z2 = v3.z - v1.z; 
  
        float s1 = uv2.x - uv1.x; 
        float s2 = uv3.x - uv1.x; 
        float t1 = uv2.y - uv1.y; 
        float t2 = uv3.y - uv1.y; 
  
        float r=1.0f/(s1*t2-s2*t1); 
        XMFLOAT3 sdir = XMFLOAT3((t2 * x1 - t1 * x2) * r, (t2 * y1 - t1 * y2) * r, (t2 * z1 - t1 * z2) * r); 
        XMFLOAT3 tdir = XMFLOAT3((s1 * x2 - s2 * x1) * r, (s1 * y2 - s2 * y1) * r, (s1 * z2 - s2 * z1) * r); 
  
		tan1[i].x += sdir.x; 
		tan1[i].y += sdir.y; 
		tan1[i].z += sdir.z; 

		tan1[i+1].x += sdir.x; 
		tan1[i+1].y += sdir.y; 
		tan1[i+1].z += sdir.z;

		tan1[i+2].x += sdir.x; 
		tan1[i+2].y += sdir.y; 
		tan1[i+2].z += sdir.z;
  
		tan2[i].x += tdir.x; 
		tan2[i].y += tdir.y; 
		tan2[i].z += tdir.z; 

		tan2[i+1].x += tdir.x; 
		tan2[i+1].y += tdir.y; 
		tan2[i+1].z += tdir.z;

		tan2[i+2].x += tdir.x; 
		tan2[i+2].y += tdir.y; 
		tan2[i+2].z += tdir.z; 
    } 
    for (int i=0;i<vertexCount;i++) 
    { 
		XMFLOAT3 n=pVerts[i].normal; 
        XMFLOAT3 t=tan1[i]; 
		XMVECTOR nDotT=XMVector3Dot(XMLoadFloat3(&n), XMLoadFloat3(&t));
		XMFLOAT3 nDotT3;
		XMStoreFloat3(&nDotT3,nDotT);
		//XMFLOAT3 tmp = t - n * nDotT3); 
		XMFLOAT3 tmp = t;
		tmp.x=tmp.x-n.x*nDotT3.x;
		tmp.y=tmp.y-n.y*nDotT3.y;
		tmp.z=tmp.z-n.z*nDotT3.z;
        XMVECTOR v=XMVector3Normalize(XMLoadFloat3(&tmp)); 
		XMStoreFloat3(&pVerts[i].tangent,v);
		//pVerts[i].tangent = ; 
        //tangents[a].w = (Vector3.Dot(Vector3.Cross(n, t), tan2[a]) < 0.0f) ? -1.0f : 1.0f; 
  
    } 
    if (tan1) 
    { 
        delete [] tan1; 
        tan1=NULL; 
    } 
    if (tan2) 
    { 
        delete [] tan2; 
        tan2=NULL; 
    } 
}