#pragma once

#include "GameComponent.h"

#include <windows.h>
#define _XM_NO_INTRINSICS_
#include <xnamath.h>
//*

class CameraComponent : public GameComponent
{
public:
	//Constructor/destructor
	CameraComponent()
	{
		m_Name="Camera";
	m_FOV = XM_PI/4;
	m_LookAt = XMFLOAT3(0.0f,0.0f,0.0f);
	m_Up = XMFLOAT3(0.0f,1.0f,0.0f);
	m_NearClip = 0.1f;
	m_FarClip = 1000.0f;
	m_View = XMMatrixIdentity();
	m_Projection = XMMatrixIdentity();
	m_AspectRatio = 800.0f/640.0f;
	};

	~CameraComponent(){}; //Overrides from parent
	void Update(); 
	//Member variables
private:
	XMFLOAT3 m_LookAt;		//Point the camera is looking at (focus)
	XMFLOAT3 m_Up;			//Up direction of the camera
	float m_FOV;			//Field of View
	float m_AspectRatio;	//Aspect ratio of the displayed image
	float m_NearClip;		//Near clipping distance
	float m_FarClip;		//Far clipping distance
	XMMATRIX m_Projection;	//Projection matrix
	XMMATRIX m_View;		//View matrix

	//Methods
public:
	//Setters
	void setLook(float x, float y, float z)
	{
		m_LookAt = XMFLOAT3(x,y,z);
	};

	void setUp(float x, float y, float z)
	{
		m_Up = XMFLOAT3(x,y,z);		
	};

	void setFOV(float fov)
	{
		m_FOV = fov;
	};
	
	void setAspectRatio(float ratio)
	{
		m_AspectRatio = ratio;
	};
	
	void setNearClip(float nc)
	{
		m_NearClip = nc;
	};

	void setFarClip(float fc)
	{
		m_FarClip = fc;
	};

	//Getters
	XMFLOAT3& getLook()
	{
		return m_LookAt;
	};

	XMFLOAT3& getUp() //standUp()
	{
		return m_Up;
	}; 

	float getFOV()
	{
		return m_FOV;
	};

	float getAspectRatio()
	{
		return m_AspectRatio;
	};

	float getNearClip()
	{
		return m_NearClip;		
	};
	
	float getFarClip()
	{
		return m_FarClip;		
	};
	
	XMMATRIX& getView()
	{
		return m_View;
	};
	
	XMMATRIX& getProjection()
	{
		return m_Projection;		
	};
};
