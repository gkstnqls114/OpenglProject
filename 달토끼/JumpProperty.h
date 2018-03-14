#pragma once

class CJumpProperty
{
	static int		FinishJumpTime ;
	static float	Rotatedegree ;
	static float	Sidedegree ;
	static GLdouble JumpReach ;

public:
	static const int	k_JumpDegree ;
	static const int	k_power ;
	static const float	k_gravity ;
	static const double k_PI ;

public:
	CJumpProperty();
	~CJumpProperty();

	static void Initialize();
	static void Reset();
	
	const GLdouble Get_JumpReach() const noexcept { return JumpReach; }
	const int	   Get_FinishJumpTime() const noexcept { return FinishJumpTime; }
	const float    Get_Rotatedegree() const noexcept { return Rotatedegree; }
	const float    Get_Sidedegree() const noexcept { return Sidedegree; }
};
