#include "FPControllerComponent.h"
#include "GameObject.h"
#include "GamepadInput.h"
#include "MouseKeyboardInput.h"

void FPControllerComponent::update()
{
	if(m_pOwnerGameObject)
	{
		bool t = false;
		//Quick way of toggling M+K/Controller
		if(GetKeyPressed(VK_F1) & !t)
		{
			m_ControllerInput = !m_ControllerInput;
			t=true;
		}
		if(!GetKeyPressed(VK_F1) & t)
		{
			t=false;
		}

		bool u = false;
		//Quick way of toggling control on/off
		if(GetKeyPressed(VK_F2) & !u)
		{
			m_IsActivated=!m_IsActivated;
			u=true;
		}
		if(!GetKeyPressed(VK_F2) & u)
		{
			u=false;
		}
		
		if(m_IsActivated)
		{

				//DIRECTION
			//360 controller input
			if(m_ControllerInput)
			{
				m_AimAngle.x -= GetRightThumbstick(0).x*m_ControllerAimSensitivity;
				m_AimAngle.y += GetRightThumbstick(0).y*m_ControllerAimSensitivity;
			}
			//Mouse and keyboard input
			else
			{
				XMFLOAT3 delta = GetMouseDelta();
				m_AimAngle.x -= delta.y*m_MouseSensitivity;
				m_AimAngle.y -= delta.x*m_MouseSensitivity;
			}

			if(m_AimAngle.y>89.0f){m_AimAngle.y=89.0f;}		//Clamp the pitch between -89 and 89 degrees
			if(m_AimAngle.y<-89.0f){m_AimAngle.y=-89.0f;}

			float d2r = (XM_PI * 2) / 360;	//Convert Degrees to Radians

			m_AimDirection.x = cos(m_AimAngle.x * d2r) * cos(m_AimAngle.y * d2r);		//Convert degrees into vector components via trigonomentry
			m_AimDirection.z = sin(m_AimAngle.x * d2r) * cos(m_AimAngle.y * d2r);;		//Note: for this vector, XZ is horizontal rotation, Y is vertical rotation
			m_AimDirection.y = sin(m_AimAngle.y * d2r);	

			m_VecAimDirection = XMLoadFloat3(&m_AimDirection);
		
				//POSITION
			if(m_ControllerInput)
			{
				iForward =  GetLeftThumbstick(0).y;			//Joystick inputs
				iHorizontal = GetLeftThumbstick(0).x;		//Given as a value from -1 to 1 on each axis
				iUpwards = GetRightTrigger(0) - GetLeftTrigger(0);
				m_SpeedMultiplier = m_SpeedMultiplier + 0.00001f*(GetButtonPressed(0,XINPUT_GAMEPAD_RIGHT_SHOULDER)-GetButtonPressed(0,XINPUT_GAMEPAD_LEFT_SHOULDER));	//Modify how fast the player moves
					if(m_SpeedMultiplier<=0){m_SpeedMultiplier=0.0005f;}
			}
			else
			{
				iForward = (GetKeyPressed('W') ? 1 : 0) - (GetKeyPressed('S') ? 1 : 0); //Key Inputs
				iHorizontal = (GetKeyPressed('D') ? 1 : 0) - (GetKeyPressed('A') ? 1 : 0); //(Key A - Key B) will give you a 1/0/-1 input axis
				iUpwards = (GetKeyPressed(VK_SPACE) ? 1 : 0) - (GetKeyPressed(VK_CONTROL) ? 1 : 0);
				m_SpeedMultiplier = m_SpeedMultiplier + 0.00005f*((GetKeyPressed('Q') ? 1 : 0) - (GetKeyPressed('E') ? 1 : 0));	//Modify how fast the player moves
					if(m_SpeedMultiplier<=0){m_SpeedMultiplier=0.0001f;}
			}

			if(m_SmoothX < iForward){m_SmoothX+=m_Accel;} //Movement smoothing
			if(m_SmoothX > iForward){m_SmoothX-=m_Accel;}
				if(iForward==0.0f & m_SmoothX<=m_Accel & m_SmoothX>=-m_Accel){m_SmoothX=0.0f;}	//Some rounding down done to stop infinite movement
			if(m_SmoothY < iHorizontal){m_SmoothY+=m_Accel;}	
			if(m_SmoothY > iHorizontal){m_SmoothY-=m_Accel;}
				if(iHorizontal==0.0f & m_SmoothY<=m_Accel & m_SmoothY>=-m_Accel){m_SmoothY=0.0f;}
			if(m_SmoothZ < iUpwards){m_SmoothZ+=m_Accel;}
			if(m_SmoothZ > iUpwards){m_SmoothZ-=m_Accel;}
				if(iUpwards==0.0f & m_SmoothZ<=m_Accel & m_SmoothZ>=-m_Accel){m_SmoothZ=0.0f;}
		
			m_Translate = XMFLOAT3(m_SmoothX,m_SmoothY,m_SmoothZ);
																			//																	| /
			m_Right = -XMVector3Cross(XMLoadFloat3(&m_AimDirection),m_Up); //Get the vector perpendicular to Aim and Up via Cross Product		|/--->
			m_VecTranslate = (m_Translate.x * m_SpeedMultiplier * m_VecAimDirection)	//Multiply each input by each direction
				+(m_Translate.y * m_SpeedMultiplier * m_Right)
				+(m_Translate.z * m_SpeedMultiplier * m_Up);

			XMVECTOR curPos = XMLoadFloat3(&m_pOwnerGameObject->getTransform().getPosition());
			XMVECTOR newPos = curPos + m_VecTranslate;
		
			//SET TRANSFORM
			if(m_IsRestricted)
			{m_pOwnerGameObject->getTransform().setPosition(checkBoundaries(newPos));}
			else
			{m_pOwnerGameObject->getTransform().setPosition(newPos);}
			m_pOwnerGameObject->getTransform().setRotation(m_VecAimDirection);
		}
	}
}

XMVECTOR FPControllerComponent::checkBoundaries(XMVECTOR position)
{
	//Quick'n'dirty boundary checking	
	//X
	if(position.x>m_BoundingCuboid.x/2)
		position.x = m_BoundingCuboid.x/2;
	if(position.x<-m_BoundingCuboid.x/2)
		position.x = -m_BoundingCuboid.x/2;
	//Y - the floor is 0!
	if(position.y>m_BoundingCuboid.y)
		position.y = m_BoundingCuboid.y;
	if(position.y<0.5f)
		position.y = 0.5f;
	//Z
	if(position.z>m_BoundingCuboid.z/2)
		position.z = m_BoundingCuboid.z/2;
	if(position.z<-m_BoundingCuboid.z/2)
		position.z = -m_BoundingCuboid.z/2;

	return position;
}
