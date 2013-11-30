#include "CameraComponent.h"

//Default values on creation
CameraComponent::CameraComponent(){
	m_FOV = 70;
	m_LookAt = XMFLOAT3(0.0f,0.0f,0.0f);
	m_Up = XMFLOAT3(0.0f,1.0f,0.0f);
	m_NearClip = 0.01f;
	m_FarClip = 1000.0f;
};

void CameraComponent::Update()
{
	//Get the parent game object's transform
	Transform *pTransform = static_cast<Transform*>(m_pOwnerGameObject->getComponent("Transform"));
	//Calculate matrices from variables & transform position						
	if(pTransform){
		m_View = XMMatrixLookAtLH(XMLoadFloat3(&pTransform->getPosition()),
		XMLoadFloat3(&m_LookAt),
		XMLoadFloat3(&m_Up));
		m_Projection = XMMatrixPerspectiveFovLH(m_FOV,m_AspectRatio,m_NearClip,m_FarClip); 
	}
	
}