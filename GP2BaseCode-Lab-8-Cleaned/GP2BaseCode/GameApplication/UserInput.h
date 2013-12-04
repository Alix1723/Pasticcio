#pragma once
#include <iostream>
#include <Windows.h>
#include "GameComponent.h"

class UserInput:public GameComponent
{
public:
	UserInput()
	{
		if(GetAsyncKeyState(VK_UP) || GetAsyncKeyState(0x57))
		{
		}

		if(GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState(0x53))
		{
		}

		if(GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(0x41))
		{
		}

		if(GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState(0x44))
		{
		}

	}
};
	
