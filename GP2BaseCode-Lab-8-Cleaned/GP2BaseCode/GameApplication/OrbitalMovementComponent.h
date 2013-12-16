#pragma once

#include "GameComponent.h"
#include "OrbitalMovementComponent.h"
#include <string.h>
#include <time.h>
#include <windows.h>
#define _XM_NO_INTRINSICS_
#include <xnamath.h>

//Moving Objects around a RotPoint in a radius and an axis
//Constructor input: radius, koordinats of the rotation point, rotation axis, speed (lower = faster, 1 -> fastest)

class OrbitalMovementComponent : public GameComponent
{
public:
	OrbitalMovementComponent(float r, float x, float y, float z, char* axis, int speed)
	{
		m_Radius = r;
		m_RotPoint.x = x;
		m_RotPoint.y = y;
		m_RotPoint.z = z;
		m_pAxis = axis;
		m_Init = true;
		m_Phi = 0.01f;
		m_startTime = GetTickCount();
		m_speed = speed;
		
	};
	~OrbitalMovementComponent(){};
	void update(); //from parent

private:
	void rotate();

private:
	float m_Radius;
	float m_Phi;
	XMFLOAT3 m_RotPoint;
	char* m_pAxis;
	bool m_Init;
	DWORD m_difftime;
	DWORD m_startTime;
	DWORD m_actTime;
	int m_speed;



	
};