#include "CameraComponent.h"
#include "Transform.h"
#include "GameObject.h"

void CameraComponent::Update()
{
	if(m_pOwnerGameObject)
	{
	//XMFLOAT3 tester = XMFLOAT3(0.0f,0.0f,10.0f);
		Transform parentGOTransform = m_pOwnerGameObject->getTransfrom();
		m_View = XMMatrixLookAtLH(XMLoadFloat3(&parentGOTransform.getPosition()),
		XMLoadFloat3(&m_LookAt),
		XMLoadFloat3(&m_Up));
		m_Projection = XMMatrixPerspectiveFovLH(m_FOV,m_AspectRatio,m_NearClip,m_FarClip); 
	}
	
}