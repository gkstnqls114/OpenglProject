#pragma once

class CJumpProperty
{
public:
	static int		FinishJumpTime ;
	static int		JumpTime ;

	static GLdouble m_JumpReach ;

	static float	Rotatedegree ;
	static float	Sidedegree ;

public:
	static const int	k_JumpDegree ;
	static const int	k_power ;
	static const float	k_gravity ;
	static const double k_PI ;

public:
	CJumpProperty();
	~CJumpProperty();

	void Initialize();
	void Reset();
	
	const GLdouble Get_JumpReach() const noexcept { return m_JumpReach; }
};
