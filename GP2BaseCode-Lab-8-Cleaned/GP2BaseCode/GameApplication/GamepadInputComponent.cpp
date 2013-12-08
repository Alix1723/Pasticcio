#include "GamepadInputComponent.h"

#include "XInput.h"

bool GamepadInputComponent::IsControllerConnected()
{
	XINPUT_STATE cState;
	int cNumber;
	memset(&cState,0,sizeof(XINPUT_STATE));
	DWORD result = XInputGetState(cNumber,&cState);
	return result == ERROR_DEVICE_NOT_CONNECTED ? false : true;
}

void GamepadInputComponent::update()
{
	//
}
/*XMVECTOR GamepadInputComponent::GetLeftStick()
{
	return m_LeftStick;
}*

/*void GamepadInputComponent::update()
{
	DWORD dwResult;
	for(DWORD i = 0; i < XUSER_MAX_COUNT; i++)
	{
		XINPUT_STATE state;
		ZeroMemory(&state,sizeof(XINPUT_STATE));
		dwResult = XInputGetState(i,&state);
		if(dwResult == ERROR_SUCCESS)
		{
			//Connected
			m_Controller = &state.Gamepad;
			
			m_LeftStick.x = m_Controller->sThumbLX;
			m_LeftStick.y = m_Controller->sThumbLY;
		}
		else
		{
			//Not connected
		}
	}
}*/