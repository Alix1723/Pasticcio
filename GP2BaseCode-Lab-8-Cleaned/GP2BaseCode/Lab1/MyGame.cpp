#include "MyGame.h"
#include "../D3D10Renderer/D3D10Renderer.h"

bool MyGame::initGame()
{


	LightComponent *pLightComponent=new LightComponent();
	pLightComponent->setSpecular(0.5f,0.5,1.0f,1.0f);	//Light Blue
	
	GameObject *pLight=new GameObject();
	pLight->setName("TestObject");
	pLight->addComponent(pLightComponent);

	pLight->getTransform().setPosition(2.0f,1.0f,1.0f);
	
	D3D10Renderer *pD3D10Renderer=static_cast<D3D10Renderer*>(m_pRenderer);
	pD3D10Renderer->setMainLight(pLight);
	
	m_GameObjectList.push_back(pLight);
	//Set Light
	
	
	CubeVisualComponent *pCube=new CubeVisualComponent();
	pCube->create(m_pRenderer);

	Material *pMaterial=new Material();
	pMaterial->loadEffect("Effects/DirectionalLight.fx",m_pRenderer);
	pMaterial->loadDiffuseTexture("textures/armoredrecon_diffuse.png", m_pRenderer);

	GameObject *pTestObj=new GameObject();
	pTestObj->setName("TestObject1");
	pTestObj->addComponent(pCube);
	pTestObj->addComponent(pMaterial);
	
	pCube->createVertexLayout(m_pRenderer);

	pTestObj->getTransform().setPosition(4.0f,1.0f,0.0f);

	m_GameObjectList.push_back(pTestObj);


	// Initialize a camera
	CameraComponent *pCam=new CameraComponent();
	pCam->setFOV(m_GameOptionDesc.width/m_GameOptionDesc.height);

	//Add it to a camera gameobject;
	GameObject *pCameraObj=new GameObject();
	pCameraObj->setName("MainCamera");
	pCameraObj->addComponent(pCam);
	setMainCamera(pCam);
	
	pCameraObj->getTransform().setPosition(0.0f,0.0f,-10.0f);
	pCameraObj->getTransform().setRotation(0.0f,0.0f,1.0f);	//Magnitude must not = 0!
	FPControllerComponent *pFPControl = new FPControllerComponent();
	pCameraObj->addComponent(pFPControl);

	m_GameObjectList.push_back(pCameraObj);

	return true;
}