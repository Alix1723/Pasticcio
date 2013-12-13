#include "GamepadInput.h"
#include "XInput.h"

bool IsControllerConnected(int controllerIndex)
{
        XINPUT_STATE cState;
 
        memset(&cState,0,sizeof(XINPUT_STATE));
        DWORD result = XInputGetState(controllerIndex,&cState);
        return result == ERROR_DEVICE_NOT_CONNECTED ? false : true;
}
 
bool GetButtonPressed(int controllerIndex, WORD button)
{
        XINPUT_STATE cState;
 
        memset(&cState,0,sizeof(XINPUT_STATE));
        DWORD result = XInputGetState(controllerIndex,&cState);
        return cState.Gamepad.wButtons&button;
}
 
XMFLOAT3 GetLeftThumbstick(int controllerIndex)
{
		float deadZone = 0.3f; //DZ as percentage of stick movement

        XINPUT_STATE cState;
        memset(&cState,0,sizeof(XINPUT_STATE));
        DWORD result = XInputGetState(controllerIndex,&cState);
       
        float x = (float)cState.Gamepad.sThumbLX / 32767.0f;
        float y = (float)cState.Gamepad.sThumbLY / 32767.0f;
		float magnitude  = sqrt((x*x)+(y*y));
		if(magnitude>deadZone)
			return XMFLOAT3(x,y,0);
		else
			return XMFLOAT3(0,0,0);
}

XMFLOAT3 GetRightThumbstick(int controllerIndex)
{
		float deadZone = 0.3f; //DZ as percentage of stick movement

        XINPUT_STATE cState;
        memset(&cState,0,sizeof(XINPUT_STATE));
        DWORD result = XInputGetState(controllerIndex,&cState);
       
        float x = (float)cState.Gamepad.sThumbRX / 32767.0f;
        float y = (float)cState.Gamepad.sThumbRY / 32767.0f;
		float magnitude  = sqrt((x*x)+(y*y));
		if(magnitude>deadZone)
			return XMFLOAT3(x,y,0);
		else
			return XMFLOAT3(0,0,0);
}

float GetLeftTrigger(int controllerIndex)
{
		float deadZone = 0.1f; //DZ as percentage of trigger range
		XINPUT_STATE cState;
		memset(&cState,0,sizeof(XINPUT_STATE));
		DWORD result = XInputGetState(controllerIndex,&cState);

		float t = (float)cState.Gamepad.bLeftTrigger / 255;
	
		if(t>deadZone)
			return t;
		else
			return 0.0f;
}

float GetRightTrigger(int controllerIndex)
{
		float deadZone = 0.1f; //DZ as percentage of trigger range
		XINPUT_STATE cState;
		memset(&cState,0,sizeof(XINPUT_STATE));
		DWORD result = XInputGetState(controllerIndex,&cState);

		float t = (float)cState.Gamepad.bRightTrigger / 255;
	
		if(t>deadZone)
			return t;
		else
			return 0.0f;
}
