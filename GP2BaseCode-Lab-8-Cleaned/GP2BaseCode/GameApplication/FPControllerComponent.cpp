#include "FPControllerComponent.h"
//#include "Transform.h"
#include "GameObject.h"

void FPControllerComponent::update()
{
	if(m_pOwnerGameObject)
	{
		//POSITION
		//Componentwise addition for now, will change to vector addition/multiplication when possible
		int Forward = (GetAsyncKeyState(VK_UP) ? 1 : 0) - (GetAsyncKeyState(VK_DOWN) ? 1 : 0);
		int Horizontal = (GetAsyncKeyState(VK_RIGHT) ? 1 : 0) - (GetAsyncKeyState(VK_LEFT) ? 1 : 0);; //GetAsyncKeyState(VK_RIGHT) - GetAsyncKeyState(VK_LEFT);
		int Upwards = (GetAsyncKeyState(VK_SPACE) ? 1 : 0) - (GetAsyncKeyState(VK_CONTROL) ? 1 : 0);
	
		m_Translate = XMFLOAT3(Horizontal, Upwards, Forward);

		XMFLOAT3 curPos = m_pOwnerGameObject->getTransform().getPosition();
		float denominator = 50;

		float newX = curPos.x + Horizontal/denominator;
		float newY = curPos.y + Upwards/denominator;
		float newZ = curPos.z + Forward/denominator;

		m_pOwnerGameObject->getTransform().setPosition(newX,newY,newZ);
	}
}
