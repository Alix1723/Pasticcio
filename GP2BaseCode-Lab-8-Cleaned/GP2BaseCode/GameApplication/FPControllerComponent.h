#pragma once

#include "GameComponent.h"

#include <windows.h>
#define _XM_NO_INTRINSICS_
#include <xnamath.h>
//First person (Quake-style) controller
class FPControllerComponent : public GameComponent
{
public:
	FPControllerComponent()
	{
		m_SpeedMultiplier = 0.005;
		m_Accel = 0.01f;
		m_MouseSensitivity = 0.2f;
		m_ControllerAimSensitivity = 0.05f;
		m_ControllerInput=false;

		m_Translate = XMFLOAT3(0.0f,0.0f,0.0f);
		m_AimAngle = XMFLOAT3(0.0f,0.0f,0.0f);
		m_AimDirection = XMFLOAT3(0.0f,0.0f,0.0f);
		XMFLOAT3 up = XMFLOAT3(0.0f,1.0f,0.0f);
		m_Up = XMLoadFloat3(&up);
		m_SmoothX = 0.0f;
		m_SmoothY = 0.0f; 
		m_SmoothZ = 0.0f;
	};
	~FPControllerComponent(){};
	void update(); //from parent

private:
	bool m_ControllerInput;

	float m_SpeedMultiplier;
	float m_MouseSensitivity;
	float m_ControllerAimSensitivity;
	float m_Accel;
	float m_SmoothX;
	float m_SmoothY;
	float m_SmoothZ;

	float iForward;
	float iHorizontal;
	float iUpwards;

	XMFLOAT3 m_Translate;
	XMFLOAT3 m_AimAngle;
	
	XMFLOAT3 m_AimDirection;
	XMVECTOR m_Right;
	XMVECTOR m_Up;

	XMVECTOR m_VecAimDirection;
	XMVECTOR m_VecTranslate;
};