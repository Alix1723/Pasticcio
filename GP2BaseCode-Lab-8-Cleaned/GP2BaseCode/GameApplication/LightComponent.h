#pragma once

#include "GameComponent.h"
#define XM_NO_INSTRINSICS
#include <xnamath.h>

class LightComponent:public GameComponent
{
public:
	LightComponent()
	{
		m_Name="Light";
		m_DiffuseColour=XMCOLOR(0.0f,0.0f,0.0f,1.0f);
		m_SpecularColour=XMCOLOR(0.0f,0.0f,0.0f,1.0f);
	};
	~LightComponent()
	{
	};

	void setDiffuse(float r, float g, float b, float a)
	{
		m_DiffuseColour=XMCOLOR(r,g,b,a);
	};
	void setSpecular(float r, float g, float b, float a);
	XMCOLOR& getDiffuse(){return m_DiffuseColour;};
	XMCOLOR& getSpecular(){return m_SpecularColour;};

private:
	XMCOLOR m_DiffuseColour;
	XMCOLOR m_SpecularColour;

}