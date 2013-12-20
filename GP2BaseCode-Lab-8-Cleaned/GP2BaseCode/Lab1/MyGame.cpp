#include "MyGame.h"
#include "../D3D10Renderer/D3D10Renderer.h"

bool MyGame::initGame()
{
	DirectionalLightComponent *pLightComponent=new DirectionalLightComponent();
	//pLightComponent->setSpecular(0.5f,0.5,1.0f,1.0f);	//Light Blue
	
	GameObject *pLight=new GameObject();
	pLight->setName("TestObject");
	pLight->addComponent(pLightComponent);

	pLight->getTransform().setPosition(0.0f,100.0f,-100.0f);
	
	D3D10Renderer *pD3D10Renderer=static_cast<D3D10Renderer*>(m_pRenderer);
	pD3D10Renderer->setMainLight(pLight);
	
	m_GameObjectList.push_back(pLight);
	//Set Light
	CubeVisualComponent *pCube=new CubeVisualComponent();
	pCube->create(m_pRenderer);
	


	Material *pMaterial=new Material();

	pMaterial->loadEffect("Effects/DirectionalLight.fx",m_pRenderer);
	pMaterial->loadDiffuseTexture("Textures/cube1.png", m_pRenderer);
	
	OrbitalMovementComponent *pOrbMove = new OrbitalMovementComponent(1.0f, 0.0f, 2.0f, -2.0f, "z", 10, 0.0f, 0.0f, 0.0f);

	GameObject *pTestObj=new GameObject();
	pTestObj->setName("TestObject");
	pTestObj->addComponent(pCube);
	pTestObj->addComponent(pMaterial);
	pTestObj->addComponent(pOrbMove);

    pCube->createVertexLayout(m_pRenderer);

	pTestObj->getTransform().setPosition(1.0f,1.0f,0.0f);

	m_GameObjectList.push_back(pTestObj);

	/*
	Material *pParaMaterial=new Material();

	pParaMaterial->loadEffect("Effects/Parallax.fx",m_pRenderer);
	pParaMaterial->loadDecalView("Textures/brick.dds", m_pRenderer);
	pParaMaterial->loadNormalMap("Textures/normalMap.dds", m_pRenderer);
	pParaMaterial->loadHeightMap("Textures/heightMap.dds", m_pRenderer);

	GameObject *pParaCube = new GameObject();
	pParaCube->setName("Parallax Cube");
	pParaCube->addComponent(pCube);
	pParaCube->addComponent(pParaMaterial);

	pParaCube->getTransform().setPosition(4.0f,0.0f,-2.0f);

	m_GameObjectList.push_back(pParaCube);
	*/
	
	//1: Normal camera
	CameraComponent *pCam=new CameraComponent();
	pCam->setFOV(m_GameOptionDesc.width/m_GameOptionDesc.height);

	//Add it to a camera gameobject;
	GameObject *pCameraObj=new GameObject();
	pCameraObj->setName("MainCamera");
	pCameraObj->addComponent(pCam);
	setMainCamera(pCam);
	pCameraObj->getTransform().setPosition(0.0f,0.0f,-10.0f);
	pCameraObj->getTransform().setRotation(1.0f,0.0f,0.0f);	//Magnitude must not = 0!
	FPControllerComponent *pFPControl = new FPControllerComponent();
	pFPControl->setActivated(true); //Activate this controller to use as default
	pFPControl->setRestricted(true);
	pCameraObj->addComponent(pFPControl);

	m_GameObjectList.push_back(pCameraObj);

	//2: DEBUG camera, with unrestricted movement
	//CURRENTLY UNRELIABLE, USE WITH CAUTION
	CameraComponent *pDebugCam=new CameraComponent();
	pCam->setFOV(m_GameOptionDesc.width/m_GameOptionDesc.height);

	//Add it to a camera gameobject;
	GameObject *pDebugCameraObj=new GameObject();
	pDebugCameraObj->setName("DebugCamera");
	pDebugCameraObj->addComponent(pDebugCam);
	setDebugCamera(pDebugCam);
	pDebugCameraObj->getTransform().setPosition(0.0f,0.0f,-10.0f);
	pDebugCameraObj->getTransform().setRotation(1.0f,0.0f,0.0f);	//Magnitude must not = 0!
	FPControllerComponent *pDebugFPControl = new FPControllerComponent();
	pDebugFPControl->setActivated(false);
	pDebugFPControl->setRestricted(false);
	pDebugCameraObj->addComponent(pDebugFPControl);

	m_GameObjectList.push_back(pDebugCameraObj);
	
	/*// car
	GameObject *pCar=m_ModelLoader.loadModelFromFile("Models/armoredrecon.fbx",m_pRenderer);
	for(GameObject::ChildrenGameObjectsIter iter=pCar->getFirstChild();iter!=pCar->getLastChild();iter++)
	{
		pMaterial=new Material();
		pMaterial->loadEffect("Effects/DirectionalLight.fx",m_pRenderer);
		pMaterial->loadDiffuseTexture("Textures/armoredrecon_diffuse.png",m_pRenderer);
		iter->second->addComponent(pMaterial);
		VisualComponent *pVisual=static_cast<VisualComponent*>(iter->second->getComponent("Visual"));
		pVisual->createVertexLayout(m_pRenderer);
	}
	m_GameObjectList.push_back(pCar);
	*/
	// Paracar
	GameObject *pParaCar=m_ModelLoader.loadModelFromFile("Models/armoredrecon.fbx",m_pRenderer);
	for(GameObject::ChildrenGameObjectsIter iter=pParaCar->getFirstChild();iter!=pParaCar->getLastChild();iter++)
	{
		pMaterial=new Material();
		pMaterial->loadEffect("Effects/Parallax.fx",m_pRenderer);
		pMaterial->loadDecalView("Textures/armoredrecon_diffuse.png", m_pRenderer);
		pMaterial->loadNormalMap("Textures/armoredrecon_N.png", m_pRenderer);
		pMaterial->loadHeightMap("Textures/armoredrecon_Height.png", m_pRenderer);
		iter->second->addComponent(pMaterial);
		VisualComponent *pVisual=static_cast<VisualComponent*>(iter->second->getComponent("Visual"));
		pVisual->createVertexLayout(m_pRenderer);
		iter->second->getTransform().setScale(2.0f,2.0f,2.0f);
		iter->second->getTransform().setPosition(0.0f, -1.5f, 40.0f);
	}
	
	m_GameObjectList.push_back(pParaCar);
	
	//space station
	GameObject *pCorridor=m_ModelLoader.loadModelFromFile("Models/Corridor.fbx",m_pRenderer);
	for(GameObject::ChildrenGameObjectsIter iter=pCorridor->getFirstChild();iter!=pCorridor->getLastChild();iter++)
	{
		pMaterial=new Material();
		pMaterial->loadEffect("Effects/Parallax.fx",m_pRenderer);
		pMaterial->loadDecalView("Textures/MetalBase.jpg", m_pRenderer);
		pMaterial->loadNormalMap("Textures/MetalBase_Normal.pg", m_pRenderer);
		iter->second->addComponent(pMaterial);
		VisualComponent *pVisual=static_cast<VisualComponent*>(iter->second->getComponent("Visual"));
		pVisual->createVertexLayout(m_pRenderer);
		iter->second->getTransform().setScale(0.6f, 0.6f, 0.6f);
		iter->second->getTransform().setPosition(0.0f, 0.0f, 0.0f);
		iter->second->getTransform().setRotation(-3.925f, 0.0f, 0.0f);
	}

	m_GameObjectList.push_back(pCorridor);


	GameObject *pPipe=m_ModelLoader.loadModelFromFile("Models/Pipe.fbx",m_pRenderer);
	for(GameObject::ChildrenGameObjectsIter iter=pPipe->getFirstChild();iter!=pPipe->getLastChild();iter++)
	{
		pMaterial=new Material();
		pMaterial->loadEffect("Effects/DirectionalLight.fx",m_pRenderer);
		pMaterial->loadDiffuseTexture("Textures/MetalBase.jpg",m_pRenderer);
		iter->second->addComponent(pMaterial);
		VisualComponent *pVisual=static_cast<VisualComponent*>(iter->second->getComponent("Visual"));
		pVisual->createVertexLayout(m_pRenderer);
		iter->second->getTransform().setScale(0.315f, 0.315f, 0.315f);
		iter->second->getTransform().setPosition(-6.25f, 0.75f, 38.0f);
		iter->second->getTransform().setRotation(0.0f, 0.0f, 1.25f);
	}

	m_GameObjectList.push_back(pPipe);

	GameObject *pLights=m_ModelLoader.loadModelFromFile("Models/Lights.fbx",m_pRenderer);
	for(GameObject::ChildrenGameObjectsIter iter=pLights->getFirstChild();iter!=pLights->getLastChild();iter++)
	{
		pMaterial=new Material();
		pMaterial->loadEffect("Effects/DirectionalLight.fx",m_pRenderer);
		pMaterial->loadDiffuseTexture("Textures/planet_earth.bmp",m_pRenderer);
		iter->second->addComponent(pMaterial);
		VisualComponent *pVisual=static_cast<VisualComponent*>(iter->second->getComponent("Visual"));
		pVisual->createVertexLayout(m_pRenderer);
		iter->second->getTransform().setScale(0.5f, 0.5f, 0.5f);
		iter->second->getTransform().setPosition(0.0f, 14.5f, 0.0f);
		iter->second->getTransform().setRotation(-2.355f, 0.0f, 0.0f);
	}

	m_GameObjectList.push_back(pLights);

GameObject *pDoor=m_ModelLoader.loadModelFromFile("Models/Door.fbx",m_pRenderer);
	for(GameObject::ChildrenGameObjectsIter iter=pDoor->getFirstChild();iter!=pDoor->getLastChild();iter++)
	{
		pMaterial=new Material();
		pMaterial->loadEffect("Effects/Parallax.fx",m_pRenderer);
		pMaterial->loadDecalView("Textures/ma_door_01.jpg",m_pRenderer);
		iter->second->addComponent(pMaterial);
		VisualComponent *pVisual=static_cast<VisualComponent*>(iter->second->getComponent("Visual"));
		pVisual->createVertexLayout(m_pRenderer);
		iter->second->getTransform().setScale(0.4f, 0.4f, 0.4f);
		iter->second->getTransform().setPosition(0.0f, 5.8f, -55.0f);
		iter->second->getTransform().setRotation(-0.8f, 0.0f, 0.0f);
	}

	m_GameObjectList.push_back(pDoor);
	
	
	GameObject *pEarth=m_ModelLoader.loadModelFromFile("Models/planet_earth.fbx",m_pRenderer);
	for(GameObject::ChildrenGameObjectsIter iter=pEarth->getFirstChild();iter!=pEarth->getLastChild();iter++)
	{
		pMaterial=new Material();
		pMaterial->loadEffect("Effects/Parallax.fx",m_pRenderer);
		pMaterial->loadDecalView("Textures/mars_color.jpg", m_pRenderer);
		pMaterial->loadNormalMap("Textures/mars_normal.jpg", m_pRenderer);
		//pMaterial->loadHeightMap("Textures/mars_Height.jpg", m_pRenderer);
		iter->second->addComponent(pMaterial);
		VisualComponent *pVisual=static_cast<VisualComponent*>(iter->second->getComponent("Visual"));
		pVisual->createVertexLayout(m_pRenderer);
		iter->second->getTransform().setScale(1.6f, 1.6f, 1.6f);
		iter->second->getTransform().setPosition(0.0f, 5.0f, -120.0f);
		iter->second->getTransform().setRotation(0.0f,1.0f,4.0f);
	}
	
	m_GameObjectList.push_back(pEarth);
	
	

	//Skydome
	GameObject *pSpace=m_ModelLoader.loadModelFromFile("Models/skSphere.fbx",m_pRenderer);
	for(GameObject::ChildrenGameObjectsIter iter=pSpace->getFirstChild();iter!=pSpace->getLastChild();iter++)
	{
		pMaterial=new Material();
		pMaterial->loadEffect("Effects/Texture.fx",m_pRenderer);
		pMaterial->loadDiffuseTexture("Textures/s_2048.png",m_pRenderer);
		iter->second->addComponent(pMaterial);
		VisualComponent *pVisual=static_cast<VisualComponent*>(iter->second->getComponent("Visual"));
		pVisual->createVertexLayout(m_pRenderer);
		iter->second->getTransform().setScale(5.0f,5.0f,5.0f);
		iter->second->getTransform().setRotation(1.0f,0.0f,0.0f);
		iter->second->getTransform().setPosition(0.0f, 0.0f, 0.0f);
	}
	m_GameObjectList.push_back(pSpace);
	
	
	OrbitalMovementComponent *pOrbMoveSpaceShip = new OrbitalMovementComponent(20.0f, 0.0f, 0.0f, 0.0f, "z", 10, 0.0f, 5.0, 0.0f);
	GameObject *pSpaceShip=m_ModelLoader.loadModelFromFile("Models/spaceship01.fbx",m_pRenderer);
	for(GameObject::ChildrenGameObjectsIter iter=pSpaceShip->getFirstChild();iter!=pSpaceShip->getLastChild();iter++)
	{
		pMaterial=new Material();
		pMaterial->loadEffect("Effects/Texture.fx",m_pRenderer);
		pMaterial->loadDiffuseTexture("Textures/mat_ship.bmp",m_pRenderer);
		iter->second->addComponent(pMaterial);
		iter->second->addComponent(pOrbMoveSpaceShip);
		VisualComponent *pVisual=static_cast<VisualComponent*>(iter->second->getComponent("Visual"));
		pVisual->createVertexLayout(m_pRenderer);
		iter->second->getTransform().setScale(0.2f,0.2f,0.2f);
		iter->second->getTransform().setRotation(0.0f,0.0f,0.0f);
		//iter->second->getTransform().setPosition(0.0f, 0.0f, 0.0f);
	}
	m_GameObjectList.push_back(pSpaceShip);
	
	
	


	return true;
}