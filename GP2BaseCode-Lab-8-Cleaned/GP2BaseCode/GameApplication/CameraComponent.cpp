#include "CameraComponent.h"

//Default values on creation
CameraComponent::CameraComponent(){
	m_FOV = XM_PI/4;
	m_LookAt = XMFLOAT3(0.0f,0.0f,0.0f);
	m_Up = XMFLOAT3(0.0f,1.0f,0.0f);
	m_NearClip = 0.1f;
	m_FarClip = 1000.0f;
};

void CameraComponent::Update()
{
	//Get the parent game object's transform
	Transform *pTransform = static_cast<Transform*>(m_pOwnerGameObject->getComponent("Transform"));
	//Calculate matrices from variables & transform position
	XMFLOAT3 tester = XMFLOAT3(0.0f,0.0f,10.0f);
	//if(&m_pOwnerGameObject->getTransfrom().getPosition()){ &m_pOwnerGameObject->getTransfrom().getPosition())
m_View = XMMatrixLookAtLH(XMLoadFloat3(&tester),
		XMLoadFloat3(&m_LookAt),
		XMLoadFloat3(&m_Up));
		m_Projection = XMMatrixPerspectiveFovLH(m_FOV,m_AspectRatio,m_NearClip,m_FarClip); 
	//}
	
}