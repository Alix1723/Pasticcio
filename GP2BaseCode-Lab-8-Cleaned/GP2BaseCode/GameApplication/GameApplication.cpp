#include "GameApplication.h"

//should really check to see if we are on a windows platform
#include "../Window/Win32Window.h"
#include "../D3D10Renderer/D3D10Renderer.h"
#include "GameObject.h"
#include "MouseKeyboardInput.h"

//boost header for program options
//#include <boost/program_options.hpp>
#include <fstream> 
using namespace std;
//namespace po = boost::program_options;

//Constructor
CGameApplication::CGameApplication(void)
{
	//Set to NULL
	m_pWindow=NULL;
	//Set to NULL
	m_pRenderer=NULL;
	//Set the Window name to GP2
	m_GameOptionDesc.gameName=TEXT("GP2");
	//Window Height and Width
	m_GameOptionDesc.width=1280;
	m_GameOptionDesc.height=960;
	//Full screen
	m_GameOptionDesc.fullscreen=false;
	//Config options
	m_ConfigFileName=TEXT("game.cfg");
	m_pMainCamera = NULL;
	m_pDebugCamera = NULL;
	cameraToggle = false;
}

//Desconstructor
CGameApplication::~CGameApplication(void)
{
	clearObjectList();
	//Delete things in reverse order
	if (m_pRenderer)
	{
		delete m_pRenderer;
		m_pRenderer=NULL;
	}
	if (m_pWindow)
	{
		delete m_pWindow;
		m_pWindow=NULL;
	}
}

//Init
//This initialises all subsystems
bool CGameApplication::init()
{
	if(!parseConfigFile())
		return false;
	if (!initWindow())
		return false;
	if (!initGraphics())
		return false;
	if (!initInput())
		return false;
	if (!initGame())
		return false;
	return true;
}

//called to parse the config file
bool CGameApplication::parseConfigFile()
{

	return true;
}

//initInput - Initialises the input
bool CGameApplication::initInput()
{
	return true;
}

//initPhysics - Initialises the physics system
bool CGameApplication::initPhysics()
{
	return true;
}

//initGraphics - initialise the graphics subsystem
bool CGameApplication::initGraphics()
{
	//check our settings first, to see what graphics mode we are in
	m_pRenderer=new D3D10Renderer();
	if (!m_pRenderer->init(m_pWindow->getHandleToWindow(),m_GameOptionDesc.fullscreen))
		return false;
	return true;
}

//initWindow - initialise the window
bool CGameApplication::initWindow()
{
	//Create a Win32 Window
	m_pWindow=new CWin32Window();
	m_pWindow->init(m_GameOptionDesc.gameName,m_GameOptionDesc.width,m_GameOptionDesc.height,m_GameOptionDesc.fullscreen);
	return true;
}

//called to init the game
bool CGameApplication::initGame()
{

	return true;
}

//Called to put the game in a loop(aka game loop)
void CGameApplication::run()
{
	//while the window is not closed
	while(m_pWindow->running())
	{
		//check for all windows messages
		m_pWindow->checkForWindowMessages();
		//update
		update();
		//render
		render();
	}
}

//Render, called to draw one frame of the game
void CGameApplication::render()
{
	D3D10Renderer *pRenderer = static_cast<D3D10Renderer*>(m_pRenderer);
	if(m_pMainCamera){
		if(cameraToggle)
		{
			pRenderer->setProjectionMatrix(m_pDebugCamera->getProjection());
			pRenderer->setViewMatrix(m_pDebugCamera->getView());
		}
		else
		{
			pRenderer->setProjectionMatrix(m_pMainCamera->getProjection());
			pRenderer->setViewMatrix(m_pMainCamera->getView());
		}
		
	}

	for(GameObjectIter iter=m_GameObjectList.begin();iter!=m_GameObjectList.end();++iter)
	{
		m_pRenderer->addToRenderQueue((*iter));
	}

	m_pRenderer->clear(1.0f,0.0f,0.0f,1.0f);

	//Render to texture
	/*pRenderer->setRenderTarget(1);
	m_pRenderer->render();

	//Use this object to display the rendered texture
	GameObject *pView=new GameObject();
		CubeVisualComponent *pCube = new CubeVisualComponent();
		Material *pViewMaterial = new Material();
		pViewMaterial->loadRenderViewAsDiffuse(m_pRenderer);
		pViewMaterial->loadEffect("Effects/Post.fx",m_pRenderer);
		pView->setName("View");
		pView->addComponent(pCube);
		pView->addComponent(pViewMaterial);
		pView->getTransform().setPosition(0.0f,0.0f,40.0f);
	
	m_pRenderer->addToRenderQueue(pView);

	//Render to backbuffer*/
	pRenderer->setRenderTarget(0);
	m_pRenderer->render();
	m_pRenderer->present();

	//Clear and unbind the texture
}

//Update, called to update the game
void CGameApplication::update()
{			
		static bool u;//Probably a bad idea to do it here, but I'm running out of options
		if(GetKeyPressed(VK_F2) & !u)
		{
			cameraToggle = !cameraToggle;
			u=true;
		}
		if(!GetKeyPressed(VK_F2) & u)
		{
			u=false;
		}

	for(GameObjectIter iter=m_GameObjectList.begin();iter!=m_GameObjectList.end();iter++)
	{
		(*iter)->update();
	}
	
}

void CGameApplication::clearObjectList()
{
	//m_GameObjectList
	GameObjectIter iter=m_GameObjectList.begin();
	while(iter!=m_GameObjectList.end())
	{
		if (*iter)
		{
			delete (*iter);
			iter=m_GameObjectList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}