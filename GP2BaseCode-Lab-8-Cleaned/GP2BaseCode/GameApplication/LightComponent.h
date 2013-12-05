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
		m_Diffuse=XMCOLOR(0.8f,0.8f,0.8f,1.0f);
        m_Specular=XMCOLOR(1.0f,1.0f,1.0f,1.0f);
	};
	virtual ~LightComponent()
	{
	};

	void setDiffuse(float r, float g, float b, float a)
	{
		m_Diffuse=XMCOLOR(r,g,b,a);
	};
	void setSpecular(float r, float g, float b, float a)
	{
		m_Specular=XMCOLOR(r,g,b,a);
	};

	XMCOLOR& getDiffuse(){return m_Diffuse;};
	XMCOLOR& getSpecular(){return m_Specular;};

private:
	XMCOLOR m_Diffuse;
	XMCOLOR m_Specular;

};