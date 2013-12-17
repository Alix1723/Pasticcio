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
	
	OrbitalMovementComponent *pOrbMove = new OrbitalMovementComponent(2.0f, 0.0f, 0.0f, 0.0f, "z", 10, 0.0f, 0.0f, 0.0f);

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
	

	
	// Initialize a camera
	CameraComponent *pCam=new CameraComponent();
	pCam->setFOV(m_GameOptionDesc.width/m_GameOptionDesc.height);

	//Add it to a camera gameobject;
	GameObject *pCameraObj=new GameObject();
	pCameraObj->setName("MainCamera");
	pCameraObj->addComponent(pCam);
	setMainCamera(pCam);
	
	pCameraObj->getTransform().setPosition(5.0f,0.0f,-10.0f);
	pCameraObj->getTransform().setRotation(0.0f,0.0f,1.0f);	//Magnitude must not = 0!
	FPControllerComponent *pFPControl = new FPControllerComponent();
	pCameraObj->addComponent(pFPControl);
	m_GameObjectList.push_back(pCameraObj);
	
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
		//iter->second->getTransform().setPosition(4.0f, 0.0f, 0.0f);
	}
	
	m_GameObjectList.push_back(pParaCar);
	
	//space station
	GameObject *pCorridor=m_ModelLoader.loadModelFromFile("Models/Corridor.fbx",m_pRenderer);
	for(GameObject::ChildrenGameObjectsIter iter=pCorridor->getFirstChild();iter!=pCorridor->getLastChild();iter++)
	{
		pMaterial=new Material();
		pMaterial->loadEffect("Effects/DirectionalLight.fx",m_pRenderer);
		//pMaterial->loadDiffuseTexture("Textures/planet_earth.bmp",m_pRenderer);
		iter->second->addComponent(pMaterial);
		VisualComponent *pVisual=static_cast<VisualComponent*>(iter->second->getComponent("Visual"));
		pVisual->createVertexLayout(m_pRenderer);
		iter->second->getTransform().setScale(0.6f, 0.6f, 0.6f);
		iter->second->getTransform().setPosition(0.0f, 0.0f, 0.0f);
		iter->second->getTransform().setRotation(-3.9f, 0.0f, 0.0f);
	}

	m_GameObjectList.push_back(pCorridor);
	
	// planet
	GameObject *pEarth=m_ModelLoader.loadModelFromFile("Models/planet_earth.fbx",m_pRenderer);
	for(GameObject::ChildrenGameObjectsIter iter=pEarth->getFirstChild();iter!=pEarth->getLastChild();iter++)
	{
		pMaterial=new Material();
		pMaterial->loadEffect("Effects/DirectionalLight.fx",m_pRenderer);
		pMaterial->loadDiffuseTexture("Textures/planet_earth.bmp",m_pRenderer);
		iter->second->addComponent(pMaterial);
		VisualComponent *pVisual=static_cast<VisualComponent*>(iter->second->getComponent("Visual"));
		pVisual->createVertexLayout(m_pRenderer);
		iter->second->getTransform().setScale(0.2f, 0.2f, 0.2f);
		iter->second->getTransform().setPosition(0.0f, 5.0f, 0.0f);
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
	
	//Spaceship
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