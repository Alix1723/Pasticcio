#pragma once

#include "GameComponent.h"
#define _XM_NO_INSTRINSICS_
#include <xnamath.h>

class LightComponent:public GameComponent
{
public:
	LightComponent()
	{
		m_Name="Light";
		m_Diffuse=XMFLOAT4(0.8f,0.8f,0.8f,1.0f);
        m_Specular=XMFLOAT4(1.0f,1.0f,1.0f,1.0f);
	};
	virtual ~LightComponent()
	{
	};

	void setDiffuse(float r, float g, float b, float a)
	{
		m_Diffuse=XMFLOAT4(r,g,b,a);
	};
	void setSpecular(float r, float g, float b, float a)
	{
		m_Specular=XMFLOAT4(r,g,b,a);
	};

	XMFLOAT4& getDiffuse(){return m_Diffuse;};
	XMFLOAT4& getSpecular(){return m_Specular;};

private:
	XMFLOAT4 m_Diffuse;
	XMFLOAT4 m_Specular;

};