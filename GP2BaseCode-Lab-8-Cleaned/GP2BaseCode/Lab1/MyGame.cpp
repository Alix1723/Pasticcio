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

	pCube->createVertexLayout(m_pRenderer);
	
	//pTestObj->getTransfrom().setPosition(0.5f,1.0f,1.0f);

	m_GameObjectList.push_back(pTestObj);
	
	// Initialize a camera
	CameraComponent *pCam=new CameraComponent();
	pCam->setLook(0.0f,0.0f,0.0f);
	pCam->setFOV(m_GameOptionDesc.width/m_GameOptionDesc.height);

	//Add it to a camera gameobject;
	GameObject *pCameraObj=new GameObject();
	pCameraObj->setName("MainCamera");
	pCameraObj->addComponent(pCam);
	setMainCamera(pCam);

	pCameraObj->getTransfrom().setPosition(-1.5f,0.0f,-2.0f);
	pCam->Update();

	m_GameObjectList.push_back(pCameraObj);

	return true;
}