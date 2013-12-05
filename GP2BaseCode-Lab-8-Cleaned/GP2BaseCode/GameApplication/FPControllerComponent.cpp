#include "FPControllerComponent.h"
//#include "Transform.h"
#include "GameObject.h"

void FPControllerComponent::update()
{
	if(m_pOwnerGameObject)
	{
		//DIRECTION
		GetCursorPos(&m_CurrentCursorPos);	//Retrieve the current mouse pos

		m_MouseDelta.x = m_CurrentCursorPos.x - m_PreviousCursorPos.x;	
		m_MouseDelta.y = m_CurrentCursorPos.y - m_PreviousCursorPos.y;	

		m_AimAngle.x = m_AimAngle.x + m_MouseDelta.x*-m_MouseSensitivity;
		m_AimAngle.y = m_AimAngle.y + m_MouseDelta.y*-m_MouseSensitivity;
		if(m_AimAngle.y>90.0f){m_AimAngle.y=90.0f;}
		if(m_AimAngle.y<-90.0f){m_AimAngle.y=-90.0f;}

		float d2r = (XM_PI * 2) / 360;
		//Note: for the aim vector, XZ is horizontal rotation, Y is vertical rotation
		m_AimDirection.x = cos(m_AimAngle.x * d2r);
		m_AimDirection.z = sin(m_AimAngle.x * d2r);
		m_AimDirection.y = sin(m_AimAngle.y * d2r);	

		m_VecAimDirection = XMLoadFloat3(&m_AimDirection);
		
		//POSITION - currently NOT RELATIVE TO AIM DIRECTION
		int Forward = (GetAsyncKeyState('W') ? 1 : 0) - (GetAsyncKeyState('S') ? 1 : 0);
		int Horizontal = (GetAsyncKeyState('D') ? 1 : 0) - (GetAsyncKeyState('A') ? 1 : 0); 
		int Upwards = (GetAsyncKeyState(VK_SPACE) ? 1 : 0) - (GetAsyncKeyState(VK_CONTROL) ? 1 : 0);
			
		m_SpeedMultiplier = m_SpeedMultiplier + 0.00001f*((GetAsyncKeyState(VK_ADD) ? 1 : 0) - (GetAsyncKeyState(VK_SUBTRACT) ? 1 : 0));
		if(m_SpeedMultiplier<=0){m_SpeedMultiplier=0.0001f;}
		
		m_Translate = XMFLOAT3(Horizontal*m_SpeedMultiplier, Upwards*m_SpeedMultiplier, Forward*m_SpeedMultiplier);
		m_VecTranslate = XMLoadFloat3(&m_Translate);

		XMVECTOR curPos = XMLoadFloat3(&m_pOwnerGameObject->getTransform().getPosition());
		XMVECTOR newPos = curPos + m_VecTranslate;
		
		//SET TRANSFORM
		m_pOwnerGameObject->getTransform().setPosition(newPos);
		m_pOwnerGameObject->getTransform().setRotation(m_VecAimDirection);

		GetCursorPos(&m_PreviousCursorPos);
	}
}
