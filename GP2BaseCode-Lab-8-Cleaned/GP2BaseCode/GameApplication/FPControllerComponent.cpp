#include "FPControllerComponent.h"
#include "GameObject.h"
#include "GamepadInput.h"

void FPControllerComponent::update()
{
	if(m_pOwnerGameObject)
	{
		//DIRECTION
		GetCursorPos(&m_CurrentCursorPos);	//Retrieve the current mouse pos

		m_MouseDelta.x = m_CurrentCursorPos.x - m_PreviousCursorPos.x;	//Find the difference between the previous and the current position
		m_MouseDelta.y = m_CurrentCursorPos.y - m_PreviousCursorPos.y;	

		m_AimAngle.x = m_AimAngle.x + m_MouseDelta.x*-m_MouseSensitivity;	//Add to a Euler angle representing the direction the player is aiming in
		m_AimAngle.y = m_AimAngle.y + m_MouseDelta.y*-m_MouseSensitivity;
		if(m_AimAngle.y>90.0f){m_AimAngle.y=90.0f;}		//Clamp the pitch between -90 and 90 degrees
		if(m_AimAngle.y<-90.0f){m_AimAngle.y=-90.0f;}

		float d2r = (XM_PI * 2) / 360;	//Convert Degrees to Radians
		
		m_AimDirection.x = cos(m_AimAngle.x * d2r);	//Convert degrees into vector components via trigonomentry
		m_AimDirection.z = sin(m_AimAngle.x * d2r); //Note: for this vector, XZ is horizontal rotation, Y is vertical rotation
		m_AimDirection.y = sin(m_AimAngle.y * d2r);	
		
		m_VecAimDirection = XMLoadFloat3(&m_AimDirection);
		
		//POSITION
		int Forward = GetButtonPressed(0,XINPUT_GAMEPAD_DPAD_UP) ;//(GetAsyncKeyState('W') ? 1 : 0) - (GetAsyncKeyState('S') ? 1 : 0); //Key Inputs
		int Horizontal = (GetAsyncKeyState('D') ? 1 : 0) - (GetAsyncKeyState('A') ? 1 : 0); //(Key A - Key B) will give you a 1/0/-1 input axis
		int Upwards = (GetAsyncKeyState(VK_SPACE) ? 1 : 0) - (GetAsyncKeyState(VK_CONTROL) ? 1 : 0);

		if(m_SmoothX < Forward){m_SmoothX+=m_Accel;} //Movement smoothing
		if(m_SmoothX > Forward){m_SmoothX-=m_Accel;}
			if(Forward==0.0f & m_SmoothX<=m_Accel & m_SmoothX>=-m_Accel){m_SmoothX=0.0f;}	//Some rounding down done to stop infinite movement
		if(m_SmoothY < Horizontal){m_SmoothY+=m_Accel;}	
		if(m_SmoothY > Horizontal){m_SmoothY-=m_Accel;}
			if(Horizontal==0.0f & m_SmoothY<=m_Accel & m_SmoothY>=-m_Accel){m_SmoothY=0.0f;}
		if(m_SmoothZ < Upwards){m_SmoothZ+=m_Accel;}
		if(m_SmoothZ > Upwards){m_SmoothZ-=m_Accel;}
			if(Upwards==0.0f & m_SmoothZ<=m_Accel & m_SmoothZ>=-m_Accel){m_SmoothZ=0.0f;}
		
		m_Translate = XMFLOAT3(m_SmoothX,m_SmoothY,m_SmoothZ);

		m_SpeedMultiplier = m_SpeedMultiplier + 0.00001f*((GetAsyncKeyState('Q') ? 1 : 0) - (GetAsyncKeyState('E') ? 1 : 0));	//Modify how fast the player moves
		if(m_SpeedMultiplier<=0){m_SpeedMultiplier=0.0001f;}
			
		m_Right = -XMVector3Cross(XMLoadFloat3(&m_AimDirection),m_Up); //Get the vector perpendicular to Aim and Up via Cross Product

		m_VecTranslate = (m_Translate.x * m_SpeedMultiplier * m_VecAimDirection)
			+(m_Translate.y * m_SpeedMultiplier * m_Right)
			+(m_Translate.z * m_SpeedMultiplier * m_Up);

		XMVECTOR curPos = XMLoadFloat3(&m_pOwnerGameObject->getTransform().getPosition());
		XMVECTOR newPos = curPos + m_VecTranslate;
		
		//SET TRANSFORM
		m_pOwnerGameObject->getTransform().setPosition(newPos);
		m_pOwnerGameObject->getTransform().setRotation(m_VecAimDirection);

		GetCursorPos(&m_PreviousCursorPos);
	}
}