#include "CameraComponent.h"

void CameraComponent::Update()
{
	//Get the parent game object's transform
	Transform *pTransform = static_cast<Transform*>(m_pOwnerGameObject->getComponent("Transform"));
	//Calculate matrices from variables & transform position
	m_View = XMMatrixLookAtLH(XMLoadFloat3(&pTransform->getPosition()),XMLoadFloat3(&m_LookAt),XMLoadFloat3(&m_Up));
	m_Projection = XMMatrixPerspectiveFovLH(m_FOV,m_AspectRatio,m_NearClip,m_FarClip);
	
}