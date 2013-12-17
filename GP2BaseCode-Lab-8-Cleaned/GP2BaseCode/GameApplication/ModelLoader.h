#pragma once

#define FBXSDK_NEW_API

#include <string>

#include "..\Renderer\Renderer.h"
#include "..\D3D10Renderer\Vertex.h"

class GameObject;

using namespace std;


class ModelLoader
{
public:
        ModelLoader(){};
        ~ModelLoader(){};

        GameObject * loadModelFromFile(const string& filename, IRenderer *pRenderer);
		void computeTangents(Vertex *pVerts,int vertexCount); 
private:
        GameObject * loadFbxModelFromFile(const string& filename, IRenderer *pRenderer);
};