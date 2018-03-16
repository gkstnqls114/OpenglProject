#pragma once

class JumpProperty
{
	static bool		IsInitialized;
	static int		FinishJumpTime ;
	static int		JumpTime;
	static float	Rotatedegree ;
	static float	Sidedegree ;
	static GLdouble JumpReach ;

public:
	static const int Road_Distance_X;
	static const int	k_JumpDegree ;
	static const int	k_power ;
	static const float	k_gravity ;
	static const double k_PI ;

private:

public:
	JumpProperty();
	~JumpProperty();

	static void Initialize();
	static void Reset();
	
	////////////////////////////Get
	static const GLdouble Get_JumpReach() noexcept { return JumpReach; }
	static const int	   Get_FinishJumpTime() noexcept { return FinishJumpTime; }
	static const int	  Get_JumpTime() noexcept { return JumpTime; }
	static const float    Get_Rotatedegree() noexcept { return Rotatedegree; }
	static const float    Get_Sidedegree() noexcept { return Sidedegree; }
	////////////////////////////Get
	void Add_JumpTime() { JumpTime += 1; }

};
