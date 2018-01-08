#pragma once
#include "Colleague.h"

class CFootBoard;
class CMediator;

class CRoad : public CColleague
{
	const int k_side[3] = { k_left, k_front, k_right };
	CFootBoard* m_pFootBoard;
	int m_boardNum{ 5 };
	int m_PlayerPosNum{ 0 };
	int m_DisappearBoardNum{ 0 };

	GLdouble JumpReach{ -1 };

	CMediator* m_pMediator{ nullptr };

	bool isPlayerDead{ false };
	bool isGameClear{ false };

private:
	void InitFootBoardModel();
	void InitFootBoardPos(const GLdouble& distance);

public:
	CRoad(const GLdouble& distance, CMediator*& mediator);
	~CRoad();

	void Render();
	void AllRender();
	void Update();

	const CVector3D<> GetLastPos() const noexcept;
	const CVector3D<> GetFirstPos() const noexcept;
	const CVector3D<> GetCenterPos() const noexcept;
	
	//Mediator
	virtual void Init_GameScene();
	virtual void Player_JumpStart();
	virtual void Player_Jumping();
	virtual void Player_JumpFinish(int playerside);
	virtual void Player_Dead();
	virtual void Player_Fall();

	virtual void Player_Clear();

};
