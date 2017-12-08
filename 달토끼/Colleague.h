#pragma once

class CColleague
{

public:
	CColleague();
	~CColleague();

	virtual void Render() {};
	virtual void Update() {};

	//메인화면
	virtual void Init_MainScene() {};
	virtual void Cursor_PLAY() {};
	virtual void Cursor_EXIT() {};

	//게임화면
	virtual void Init_GameScene() {};
	virtual void Player_JumpStart() {};
	virtual void Player_Jumping() {};
	virtual void Player_JumpFinish() {};
	virtual void Player_Dead() {};
};
