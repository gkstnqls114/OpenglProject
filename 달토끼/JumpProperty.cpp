#include "pch.h"
#include "JumpProperty.h"

bool	JumpProperty::IsInitialized{ false };
int JumpProperty::FinishJumpTime{ 0 };
int JumpProperty::JumpTime{ 0 };
GLdouble JumpProperty::JumpReach{ 0 };
float JumpProperty::Rotatedegree{ 0 };
float JumpProperty::Sidedegree{ 0 };
const int JumpProperty::k_JumpDegree{ 70 };
const int JumpProperty::k_power{ 15 };
const float JumpProperty::k_gravity{ 0.9f };
const double JumpProperty::k_PI{ 3.14152 };
const int JumpProperty::Road_Distance_X{ 50 };

JumpProperty::JumpProperty()
{
}

JumpProperty::~JumpProperty()
{
}

void JumpProperty::Initialize()
{
	if (IsInitialized) return;

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

	IsInitialized = true;
}

void JumpProperty::Reset()
{
	JumpTime = 0;
}
