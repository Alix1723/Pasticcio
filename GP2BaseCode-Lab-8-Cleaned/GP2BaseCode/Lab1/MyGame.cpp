#include "MyGame.h"

bool MyGame::initGame()
{
	CubeVisualComponent *pCube=new CubeVisualComponent();
	pCube->create(m_pRenderer);
	
	Material *pMaterial=new Material();
	pMaterial->loadEffect("Effects/Texture.fx",m_pRenderer);
	pMaterial->loadDiffuseTexture("textures/armoredrecon_diffuse.png", m_pRenderer);

	GameObject *pTestObj=new GameObject();
	pTestObj->setName("TestObject");
	pTestObj->addComponent(pCube);
	pTestObj->addComponent(pMaterial);

	LightComponent *pLightComponent=new LightComponent();

	GameObject *pDirectionalLight=new GameObject();
	pDirectionalLight->setName("DirectionalLight");
	pDirectionalLight->addComponent(pLightComponent);

	pCube->createVertexLayout(m_pRenderer);
	
<<<<<<< HEAD
	pTestObj->getTransfrom().setPosition(0.5f,1.0f,1.0f);
	m_pRenderer->setAmbientLightColour(0.0f,0.0f,0.0f,0.0f);
=======
	pTestObj->getTransfrom().setPosition(3.0f,0.0f,5.0f);
>>>>>>> origin/Cwork-Lab8-Pascal

	m_GameObjectList.push_back(pTestObj);

	return true;
}