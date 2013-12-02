#include "MyGame.h"

bool MyGame::initGame()
{
	CubeVisualComponent *pCube=new CubeVisualComponent();
	pCube->create(m_pRenderer);
	
	Material *pMaterial=new Material();
	pMaterial->loadEffect("Effects/Transform.fx",m_pRenderer);

	GameObject *pTestObj=new GameObject();
	pTestObj->setName("TestObject");
	pTestObj->addComponent(pCube);
	pTestObj->addComponent(pMaterial);

	LightComponent *pLightComponent=new LightComponent();

	GameObject *pDirectionalLight=new GameObject();
	pDirectionalLight->setName("DirectionalLight");
	pDirectionalLight->addComponent(pLightComponent);

	pCube->createVertexLayout(m_pRenderer);
	
	pTestObj->getTransfrom().setPosition(0.5f,1.0f,1.0f);
	m_pRenderer->setAmbientLightColour(0.0f,0.0f,0.0f,0.0f);

	m_GameObjectList.push_back(pTestObj);

	return true;
}