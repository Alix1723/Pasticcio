#pragma once
 
#include "windows.h"
 
#include <windows.h>
#define _XM_NO_INTRINSICS_
#include <xnamath.h>
 
#include "XInput.h"
 
bool IsControllerConnected(int controllerIndex);
 
bool GetButtonPressed(int controllerIndex, WORD button);
XMFLOAT3 GetLeftThumbstick(int controllerIndex);
XMFLOAT3 GetRightThumbstick(int controllerIndex);
float GetLeftTrigger(int controllerIndex);
float GetRightTrigger(int controllerIndex);