#pragma once
class CColleague
{

public:
	CColleague();
	~CColleague();

	virtual void Player_JumpStart() {};
	virtual void Player_Jumping() {};
	virtual void Player_JumpFinish() {};
	virtual void Player_Dead() {};
};
