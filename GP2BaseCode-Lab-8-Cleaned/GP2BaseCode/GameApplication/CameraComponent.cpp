#include "CameraComponent.h"
#include "Transform.h"
#include "GameObject.h"

void CameraComponent::update()
{
	if(m_pOwnerGameObject)
	{
		//Taking position and rotation from parent object
		Transform t=m_pOwnerGameObject->getTransform();
		XMFLOAT3 position=t.getPosition();
		
		XMFLOAT3 lookDirection = XMFLOAT3(
			t.getPosition().x + t.getRotation().x,
			t.getPosition().y + t.getRotation().y,
			t.getPosition().z + t.getRotation().z);

		m_View=XMMatrixLookAtLH(XMLoadFloat3(&position),XMLoadFloat3(&lookDirection),XMLoadFloat3(&m_Up));
		m_Projection=XMMatrixPerspectiveFovLH(m_FOV,m_AspectRatio,m_NearClip,m_FarClip);

	}
	
}