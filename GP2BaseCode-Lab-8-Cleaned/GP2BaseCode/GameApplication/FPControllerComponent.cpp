#include "FPControllerComponent.h"
//#include "Transform.h"
#include "GameObject.h"

void FPControllerComponent::update()
{
	if(m_pOwnerGameObject)
	{
		//POSITION
		int Forward = (GetAsyncKeyState(VK_UP) ? 1 : 0) - (GetAsyncKeyState(VK_DOWN) ? 1 : 0);
		int Horizontal = (GetAsyncKeyState(VK_RIGHT) ? 1 : 0) - (GetAsyncKeyState(VK_LEFT) ? 1 : 0);; //GetAsyncKeyState(VK_RIGHT) - GetAsyncKeyState(VK_LEFT);
		int Upwards = (GetAsyncKeyState(VK_SPACE) ? 1 : 0) - (GetAsyncKeyState(VK_CONTROL) ? 1 : 0);
		float denominator = 50;
		m_Translate = XMFLOAT3(Horizontal/denominator, Upwards/denominator, Forward/denominator);
		m_VecTranslate = XMLoadFloat3(&m_Translate);
		
		XMVECTOR curPos = XMLoadFloat3(&m_pOwnerGameObject->getTransform().getPosition());
		XMVECTOR newPos = curPos + m_VecTranslate;
		
		m_pOwnerGameObject->getTransform().setPosition(newPos);
	}
}
