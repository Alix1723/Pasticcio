#pragma once 

#include "LightComponent.h"

class DirectionalLightComponent:public LightComponent
{
public:
	DirectionalLightComponent()
	{
		m_Name="DirectionalLight";
		m_Direction=XMFLOAT3(0.0f,0.0f,-1.0f);
	};

	virtual ~DirectionalLightComponent()
	{
	};

	void setDirection(float x, float y, float z)
	{
		m_Direction=XMFLOAT3(x,y,z);
	};

	XMFLOAT3& getDirection(){return m_Direction;};
private:
	XMFLOAT3 m_Direction;
};