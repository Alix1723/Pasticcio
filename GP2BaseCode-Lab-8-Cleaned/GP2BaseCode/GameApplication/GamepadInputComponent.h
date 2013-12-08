#pragma once

#include "windows.h"
#include "GameComponent.h"
#include "XInput.h"

#define _XM_NO_INTRINSICS_
#include <xnamath.h>

class GamepadInputComponent : public GameComponent
{
public:
	GamepadInputComponent(){};
	~GamepadInputComponent(){};

	void update();
	
	bool IsControllerConnected();
	//XMVECTOR GetLeftStick();
	//XMVECTOR GetRightStick();
private:
	//XMVECTOR m_LeftStick;
	//XMVECTOR m_RightStick;
	//XINPUT_GAMEPAD* m_Controller;
};