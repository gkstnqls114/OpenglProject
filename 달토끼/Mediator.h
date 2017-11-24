#pragma once

class CPlayer;
class CRoad;
class CCamera;

class CMediator
{
	CPlayer* m_pPlayer{ nullptr };
	CRoad* m_pRoad{ nullptr };
	CCamera* m_pCamera{ nullptr };

public:
	CMediator();
	CMediator(CPlayer*& p, CRoad*& r, CCamera*& m);
	~CMediator();
	void Set_Colleague(CPlayer*& p, CRoad*& r, CCamera*& m);

	void Player_JumpStart();
	void Player_Jumping();
	void Player_JumpFinish();
	void Player_Dead();
};