#pragma once
#include "Colleague.h"

class CFootBoard;
class CMediator;

class CRoad : public CColleague
{
	const int k_side[3] = { k_left, k_front, k_right };
	CFootBoard* m_pFootBoard;
	int m_boardNum{ 20 };
	int m_PlayerPosNum{ 0 };
	int m_DisappearBoardNum{ 0 };

	CMediator* m_pMediator{ nullptr };

	bool isPlayerDead{ false };

private:
	void InitFootBoardModel();
	void InitFootBoardPos(const GLdouble& distance);

public:
	CRoad(const GLdouble& distance, CMediator*& mediator);
	~CRoad();

	void Render();
	void Update();

	const CVector3D<> GetLastPos() const noexcept;
	const CVector3D<> GetFirstPos() const noexcept;

	//Mediator
	virtual void Init_GameScene();
	virtual void Player_JumpStart();
	virtual void Player_Jumping();
	virtual void Player_JumpFinish(int playerside);
	virtual void Player_Dead();
	virtual void Player_Fall();

	virtual void Player_Clear();

};
