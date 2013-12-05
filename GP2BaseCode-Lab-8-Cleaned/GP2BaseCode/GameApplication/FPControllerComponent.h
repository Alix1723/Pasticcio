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
		m_SpeedMultiplier = 0.005;
		m_MouseSensitivity = 0.1f;
		m_Translate = XMFLOAT3(0.0f,0.0f,0.0f);
		m_MouseDelta = XMFLOAT2(0.0f,0.0f);
		m_AimAngle = XMFLOAT3(0.0f,0.0f,0.0f);
		m_AimDirection = XMFLOAT3(0.0f,0.0f,0.0f);
		GetCursorPos(&m_CurrentCursorPos);
		m_PreviousCursorPos = m_CurrentCursorPos;
	};
	~FPControllerComponent(){};
	void update(); //from parent

private:
	float m_SpeedMultiplier;
	float m_MouseSensitivity;

	XMFLOAT3 m_Translate;
	XMFLOAT2 m_MouseDelta;
	POINT m_CurrentCursorPos;
	POINT m_PreviousCursorPos;
	XMFLOAT3 m_AimAngle;
	XMFLOAT3 m_AimDirection;

	XMVECTOR m_VecTranslate;
	XMVECTOR m_VecAimDirection;
};