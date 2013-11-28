#pragma once

#include "GameComponent.h"
#include "Transform.h"
#include "GameObject.h"

#include <windows.h>
#define _XM_NO_INTRINSICS_
#include <xnamath.h>
//*

class CameraComponent : public GameComponent
{
public:
	//Constructor/destructor
	CameraComponent(){};
	virtual ~CameraComponent(){}; //Overrides from parent

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

	XMFLOAT3& getUp()
	{
		return m_Up;
	}; //standUp()

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

	//Update
	virtual void Update(); //Overriding from parent
};
