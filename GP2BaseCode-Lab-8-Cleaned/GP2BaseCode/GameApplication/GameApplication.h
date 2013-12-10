//header guard, so this file is only compiled once
#pragma once

#include <string>
#include <vector>

#include "Components.h"
#include "GameObject.h"
#include "ModelLoader.h"

using namespace std;

//Forward decleration of our Window Interface
class IWindow;
class IRenderer;

//Structure for holding GameOptions, this will be loaded from config files
struct GameOptionsDesc
{
	wstring gameName;
	int width;
	int height;
	bool fullscreen;
};

//we have this here so we don't need to prefix all
//standard library types with std::
using namespace std;

//Our Game Application class
class CGameApplication
{
public:
	CGameApplication(void);
	//virtual deconstructor, so this class can be overriden
	virtual ~CGameApplication(void);
	//virtual function, can be overriden
	virtual bool init();
	void run();
	//virtual function, can be overriden
	virtual void render();
	//virtual function, can be overriden
	virtual void update();

	virtual bool initGame();

	void clearObjectList();

	void setMainCamera(CameraComponent* sCamera)
	{
		m_pMainCamera = sCamera;
	};
private:
	bool parseConfigFile();
	bool initInput();
	
	bool initGraphics();
	bool initPhysics();

	bool initWindow();
protected:
	typedef vector<GameObject*> GameObjectList;
	typedef vector<GameObject*>::iterator GameObjectIter;
	IWindow * m_pWindow;
	IRenderer * m_pRenderer;
	GameOptionsDesc m_GameOptionDesc;
	wstring m_ConfigFileName;
	GameObjectList m_GameObjectList;
	CameraComponent* m_pMainCamera; //Pointer to the current viewable camera
	ModelLoader m_ModelLoader;		// Modelloader
	
};