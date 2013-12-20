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
		m_IsActivated = false;
		m_IsRestricted = true;
		m_SpeedMultiplier = 0.01;				
		m_Accel = 0.01f;						
		m_MouseSensitivity = 0.2f;				
		m_ControllerAimSensitivity = 0.1f;		
		m_ControllerInput=false;				
			
		m_Translate = XMFLOAT3(0.0f,0.0f,0.0f);		
		m_AimAngle = XMFLOAT3(0.0f,0.0f,0.0f);		
		m_AimDirection = XMFLOAT3(0.0f,0.0f,0.0f);	
		XMFLOAT3 up = XMFLOAT3(0.0f,1.0f,0.0f);		
		m_Up = XMLoadFloat3(&up);					
		m_SmoothX = 0.0f;							
		m_SmoothY = 0.0f; 
		m_SmoothZ = 0.0f;
		m_BoundingCuboid = XMFLOAT3(10.0f, 9.0f, 140.0f);	
	};
	~FPControllerComponent(){};
	void update(); //from parent
	
	void setActivated(bool active) //Change if this in use or not
	{
		m_IsActivated = active;
	}							 
	void setRestricted(bool restrict) //Change restriction
	{
		m_IsRestricted = restrict;
	} 
	XMVECTOR checkBoundaries(XMVECTOR position);	//Checking rectangular boundary

private:
	bool m_IsActivated;						//Is the FP controller currently being used?
	bool m_IsRestricted;					//Is the movement bound by the boundary cuboid?
	bool m_ControllerInput;					//Toggling between Mouse+Keyboard and Controller inputs

	float m_SpeedMultiplier;				//How fast to move the camera around
	float m_MouseSensitivity;				//How fast the mouse rotates the camera
	float m_ControllerAimSensitivity;		//How fast the right analogue stick rotates the camera
	float m_Accel;							//How quickly to reach maximum speed
	float m_SmoothX;						
	float m_SmoothY;						//Smoothing out movement
	float m_SmoothZ;

	float iForward;							//Input variables for each direction, ranging from -1 to 1
	float iHorizontal;
	float iUpwards;

	XMFLOAT3 m_Translate;					//What amount to move the camera by
	XMFLOAT3 m_AimAngle;					//What angle to aim at, in degrees
	XMFLOAT3 m_BoundingCuboid;				//Boundaries the camera cannot move out of
	
	XMFLOAT3 m_AimDirection;				//The angle to aim at converted to a normalized vector
	XMVECTOR m_Right;						//Vector perpendicular to both the aim direction and up direction
	XMVECTOR m_Up;							//Unit vector pointing straight upwards

	XMVECTOR m_VecAimDirection;				//XMVECTORs for aim and movement, for addition/multiplication purposes
	XMVECTOR m_VecTranslate;				
};