#pragma once

class CColleague
{

public:
	CColleague();
	~CColleague();

	virtual void Render() {};
	virtual void Update() {};

	//����ȭ��
	virtual void Init_MainScene() {};
	virtual void Cursor_PLAY() {};
	virtual void Cursor_EXIT() {};

	//����ȭ��
	virtual void Init_GameScene() {};
	virtual void Player_JumpStart() {};
	virtual void Player_Jumping() {};
	virtual void Player_JumpFinish() {};
	virtual void Player_Dead() {};
};
