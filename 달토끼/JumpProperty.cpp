#include "pch.h"
#include "JumpProperty.h"

int CJumpProperty::FinishJumpTime{ 0 };
GLdouble CJumpProperty::JumpReach{ 0 };
float CJumpProperty::Rotatedegree{ 0 };
float CJumpProperty::Sidedegree{ 0 };
const int CJumpProperty::k_JumpDegree{ 80 };
const int CJumpProperty::k_power{ 9 };
const float CJumpProperty::k_gravity{ 0.7f };
const double CJumpProperty::k_PI{ 3.14152 };

CJumpProperty::CJumpProperty()
{
}

CJumpProperty::~CJumpProperty()
{
}

void CJumpProperty::Initialize()
{
	float radian = k_JumpDegree * k_PI / 180;
	int temp_jumptime = 0;
	GLdouble temp_vector_z = 0;
	GLdouble temp_vector_y = 0;
	while (temp_vector_y >= 0)
	{
		temp_jumptime += 1;
		temp_vector_z += -k_power * cos(radian);
		temp_vector_y += k_power * sin(radian) - k_gravity * temp_jumptime;
	}

	FinishJumpTime = temp_jumptime;
	JumpReach = -temp_vector_z;

	Rotatedegree = atan(float(JumpReach) / float(Road_Distance_X)) * 180 / k_PI;
	Rotatedegree = 90 - Rotatedegree;
}

void CJumpProperty::Reset()
{

}
