#include "pch.h"
#include "JumpProperty.h"


CJumpProperty::CJumpProperty()
{
}

CJumpProperty::~CJumpProperty()
{
}

void CJumpProperty::Initialize()
{
	float radian = m_JumpDegree * k_PI / 180;
	int temp_jumptime = 0;
	GLdouble temp_vector_z = 0;
	GLdouble temp_vector_y = 0;
	while (temp_vector_y >= 0)
	{
		temp_jumptime += 1;
		temp_vector_z += -m_power * cos(radian);
		temp_vector_y += m_power * sin(radian) - k_gravity * temp_jumptime;
	}

	m_FinishJumpTime = temp_jumptime;
	m_JumpReach = -temp_vector_z;

	Rotatedegree = atan(float(m_JumpReach) / float(Road_Distance_X)) * 180 / k_PI;
	Rotatedegree = 90 - Rotatedegree;
}
