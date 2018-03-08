#pragma once
#include "Disappear.h"
#include "Stop.h"
#include "ItemManager.h"

#include "PlayerObserver.h"

class RoadState;
class CFootBoard;
class CMediator;
class RoadSubject;

////////////////////////////////////////////////////
// Road는 FootBoard와 Item을 관리하고 생성합니다.
////////////////////////////////////////////////////

class CRoad 
	: public PlayerObserver
{
	const int		k_side[3] = { k_left, k_front, k_right };
	
	////////////////////// 나중에 묶기
	CFootBoard*		m_pFootBoard{ nullptr };
	int				m_DisappearingBoardIndex{ 0 };
	int				m_boardNum{ 5 };
	//////////////////////

	ItemManager		m_ItemManager;

	RoadState*		m_RoadState{ nullptr };
	
	Stop			StopState;
	Disappear		DisappearState;
	

	GLdouble		JumpReach{ -1 };

	RoadSubject*	m_pRoadSubject{ nullptr };

private:
	void InitFootBoardModel();
	void InitFootBoardPos(const GLdouble& distance);

	const bool IsOutRange() const;
	void Add_DisappearingBoardIndex();

public:
	CRoad(const GLdouble& distance);
	~CRoad();

	void Render();
	void TestRender();
	void Update();

	/////////////////////////////////State
	void Disappear();
	void Stop();

	void StateChange_Disappear();
	void StateChange_Stop();
	/////////////////////////////////State

	/////////////////////////////////Get
	const CVector3D<> GetLastPos() const noexcept;
	const CVector3D<> GetFirstPos() const noexcept;
	const CVector3D<> GetCenterPos() const noexcept;
	const int Get_DisappearingBoardIndex() const noexcept { return m_DisappearingBoardIndex; }
	/////////////////////////////////Get

	/////////////////////////////////Set
	//void Set_PlayerBoardIndex(const int& playerboardindex) noexcept { m_PlayerBoardIndex = playerboardindex; }
	void Set_RoadObserver(RoadSubject* subject) noexcept { m_pRoadSubject = subject; };
	/////////////////////////////////Set
	
	/////////////////////////////////Receive
	virtual void Receive_PlayerWaitCamera(CPlayer* player) override;
	virtual void Receive_PlayerJumpFinish(CPlayer* player) override;
	virtual void Receive_PlayerJumping(CPlayer* player)	override {};
	/////////////////////////////////Receive

	virtual void Init_GameScene();
	virtual void Player_JumpFinish(int playerside);
	

};
