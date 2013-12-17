#include "MouseKeyboardInput.h"

bool GetKeyPressed(int vKey)
{
	return GetAsyncKeyState(vKey);
}

XMFLOAT3 GetMouseDelta()
{		static bool toggle;
		static bool kdown;

		if(GetKeyPressed('C') & !kdown)
		{
			toggle = !toggle;
			kdown = true;
			ShowCursor(!toggle);
		}
		if(!GetKeyPressed('C'))
		{
			kdown = false;
		}

		if(toggle)
		{	
			POINT pCurrentCursorPos;
			GetCursorPos(&pCurrentCursorPos); //Retrieve the current mouse pos
				float yaw = (pCurrentCursorPos.x - 100);
				float pitch = (pCurrentCursorPos.y - 100);
			SetCursorPos(100,100);
			return XMFLOAT3(pitch,yaw,0.0f);
		}
		else
		{
			return XMFLOAT3(0.0f,0.0f,0.0f);
		}
}