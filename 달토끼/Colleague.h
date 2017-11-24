#pragma once
class CColleague
{

public:
	CColleague();
	~CColleague();
	
	virtual void Player_JumpFinish() {};
	virtual void Player_Dead() {};
	virtual void Road_playerBoard_Disapper() {};
};

