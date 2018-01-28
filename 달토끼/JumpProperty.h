#pragma once

class CJumpProperty
{
public:
	int m_FinishJumpTime{ 0 };
	int m_JumpTime{ 0 };

	GLdouble m_JumpReach{ 0 };

	float Rotatedegree{ 0 };
	float Sidedegree{ 0 };

public:
	const int m_JumpDegree{ 80 };
	const int m_power{ 9 };
	const float k_gravity{ 0.6f };
	const double k_PI{ 3.14 };

public:
	CJumpProperty();
	~CJumpProperty();

	void Initialize();
	void Reset();
	
	const GLdouble Get_JumpReach() const noexcept { return m_JumpReach; }
};
