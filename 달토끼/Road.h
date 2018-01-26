#pragma once
#include "Disappear.h"
#include "Stop.h"
#include "Observer.h"

class RoadState;
class CFootBoard;
class CMediator;
class RoadObserver;

class CRoad : public Observer
{
	const int		k_side[3] = { k_left, k_front, k_right };
	CFootBoard*		m_pFootBoard;
	int				m_boardNum{ 5 };
	int				m_PlayerBoardIndex{ 0 };
	int				m_DisappearingBoardIndex{ 0 };

	RoadState*		m_RoadState{ nullptr };
	
	Stop		StopState;
	Disappear	DisappearState;
	

	GLdouble		JumpReach{ -1 };

	CMediator*		m_pMediator{ nullptr };
	RoadObserver*	m_pRoadObserver{ nullptr };

private:
	void InitFootBoardModel();
	void InitFootBoardPos(const GLdouble& distance);

	const bool IsOutRange() const;
	void Add_DisappearingBoardIndex();

public:
	CRoad(const GLdouble& distance);
	CRoad(const GLdouble& distance, CMediator*& mediator);
	~CRoad();

	void Render();
	void TestRender();
	void Update();


	void Disappear();
	void Stop();

	/////////////////////////////////State Change
	void StateChange_Disappear();
	void StateChange_Stop();
	/////////////////////////////////State Change

	/////////////////////////////////Get
	const CVector3D<> GetLastPos() const noexcept;
	const CVector3D<> GetFirstPos() const noexcept;
	const CVector3D<> GetCenterPos() const noexcept;
	const int Get_DisappearingBoardIndex() const noexcept { return m_DisappearingBoardIndex; }
	/////////////////////////////////Get

	/////////////////////////////////Set
	//void Set_PlayerBoardIndex(const int& playerboardindex) noexcept { m_PlayerBoardIndex = playerboardindex; }
	void Set_RoadObserver(RoadObserver* notification) noexcept { m_pRoadObserver = notification; };
	/////////////////////////////////Set
	
	virtual void Init_GameScene();
	virtual void Player_JumpStart();
	virtual void Player_Jumping();
	virtual void Player_JumpFinish(int playerside);
	

};
