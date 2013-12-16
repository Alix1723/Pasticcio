#include "OrbitalMovementComponent.h"
#include "GameObject.h"



void OrbitalMovementComponent::update()
{
	//Initial Transform
	if(m_Init)
	{
		if(strcmp(m_pAxis, "x") == 0)
			m_pOwnerGameObject->getTransform().setPosition(m_RotPoint.x, m_RotPoint.y+m_Radius, m_RotPoint.z);
		else if(strcmp(m_pAxis, "y") == 0)
			m_pOwnerGameObject->getTransform().setPosition(m_RotPoint.x, m_RotPoint.y, m_RotPoint.z+m_Radius);
		else if(strcmp(m_pAxis, "z") == 0)
			m_pOwnerGameObject->getTransform().setPosition(m_RotPoint.x+m_Radius, m_RotPoint.y, m_RotPoint.z);
	m_Init = false;
	}

	m_actTime = GetTickCount();
	m_difftime = m_actTime - m_startTime;
	if(m_difftime >= m_speed)
	{
		m_startTime = GetTickCount();
		rotate();	
	}
	



	//m_pOwnerGameObject->getTransform().setRotation(m_VecAimDirection);
}

void OrbitalMovementComponent::rotate()
{
	XMVECTOR curPos = XMLoadFloat3(&m_pOwnerGameObject->getTransform().getPosition());
	XMVECTOR newPos = curPos;

	if(strcmp(m_pAxis, "x") == 0)
	{
		newPos.y = m_RotPoint.y + (curPos.y - m_RotPoint.y)*cos(m_Phi) - (curPos.z - m_RotPoint.z)*sin(m_Phi);
		newPos.z = m_RotPoint.z + (curPos.y - m_RotPoint.y)*sin(m_Phi) + (curPos.z - m_RotPoint.z)*cos(m_Phi);
	}
	else if(strcmp(m_pAxis, "y") == 0)
	{
		newPos.x = m_RotPoint.x + (curPos.x - m_RotPoint.x)*cos(m_Phi) - (curPos.z - m_RotPoint.z)*sin(m_Phi);
		newPos.z = m_RotPoint.z + (curPos.x - m_RotPoint.x)*sin(m_Phi) + (curPos.z - m_RotPoint.z)*cos(m_Phi);
	}
	else if(strcmp(m_pAxis, "z") == 0)
	{
		newPos.x = m_RotPoint.x + (curPos.x - m_RotPoint.x)*cos(m_Phi) - (curPos.y - m_RotPoint.y)*sin(m_Phi);
		newPos.y = m_RotPoint.y + (curPos.x - m_RotPoint.x)*sin(m_Phi) + (curPos.y - m_RotPoint.y)*cos(m_Phi);
	}
	
	m_pOwnerGameObject->getTransform().setPosition(newPos);
}