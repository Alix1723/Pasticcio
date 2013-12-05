#include "MyGame.h"

bool MyGame::initGame()
{
	CubeVisualComponent *pCube=new CubeVisualComponent();
	pCube->create(m_pRenderer);
	
	Material *pMaterial=new Material();
	pMaterial->loadEffect("Effects/DirectionalLight.fx",m_pRenderer);
	LightComponent *pLightComponent=new LightComponent();
	
	GameObject *pTestObj=new GameObject();
	pTestObj->setName("TestObject");
	pTestObj->addComponent(pCube);
	pTestObj->addComponent(pMaterial);
	pTestObj->addComponent(pLightComponent);
	
		
	pCube->createVertexLayout(m_pRenderer);
	
	pTestObj->getTransfrom().setPosition(0.5f,1.0f,1.0f);
	

	m_GameObjectList.push_back(pTestObj);

	return true;
}