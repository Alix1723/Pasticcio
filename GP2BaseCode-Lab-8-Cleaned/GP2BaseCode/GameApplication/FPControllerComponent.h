#pragma once

#include "GameComponent.h"

#include <windows.h>
#define _XM_NO_INTRINSICS_
#include <xnamath.h>

class FPControllerComponent : public GameComponent
{
public:
	FPControllerComponent()
	{
		m_Translate = XMFLOAT3(0.0f,0.0f,0.0f);
		m_MouseInput = XMFLOAT2(0.0f,0.0f);
		m_AimDirection = XMFLOAT3(0.0f,0.0f,0.0f);
	};
	~FPControllerComponent(){};
	void update(); //from parent
private:
	XMFLOAT3 m_Translate;
	XMFLOAT2 m_MouseInput;
	XMFLOAT3 m_AimDirection;

	XMVECTOR m_VecTranslate;
	XMVECTOR m_VecAimDirection;
};