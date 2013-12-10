#pragma once

#include "windows.h"

#include "XInput.h"

bool IsControllerConnected(int controllerIndex);

bool GetButtonPressed(int controllerIndex, WORD button);
short GetAxis(int controllerIndex, int axisIndex);