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

short GetAxis(int controllerIndex, int axisIndex)
{
	XINPUT_STATE cState;

	memset(&cState,0,sizeof(XINPUT_STATE));
	DWORD result = XInputGetState(controllerIndex,&cState);
//	return cState.Gamepad.//cState.Gamepad.wButtons&button;d
}