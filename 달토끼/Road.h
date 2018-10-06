#pragma once
#include "Disappear.h"
#include "Stop.h"
#include "ItemManager.h"
#include "FootBoardManager.h"

#include "PlayerObserver.h"

class RoadState;
class CFootBoard;
class CMediator;
class RoadSubject;

////////////////////////////////////////////////////
// Road는 FootBoard와 Item을 관리하고 생성합니다.
////////////////////////////////////////////////////

class Road 
	: public PlayerObserver
{
	const float m_Scale{ 0.3f };

	int				m_RoadLength{ 0 };
	FootBoardManager m_FootBoardManager;
	ItemManager		m_ItemManager;

	RoadState*		m_RoadState{ nullptr };
	
	Stop			StopState;
	Disappear		DisappearState;
	
	GLdouble		JumpReach{ -1 };

	RoadSubject*	m_pRoadSubject{ nullptr };

private:
	const bool IsOutofRange(const int& len);

public:
	Road();
	Road(const int& num);
	~Road();

	void Render();
	void TestRender();
	void Update();
	void Reset();

	///////////////////////////////// State
	void Disappear();
	void Stop();

	void StateChange_Disappear();
	void StateChange_Stop();
	///////////////////////////////// State

	///////////////////////////////// Get
	const CVector3D<> Get_LastPos() const noexcept;
	const CVector3D<> Get_FirstPos() const noexcept;
	const int Get_DisappearingBoardIndex() const noexcept { return m_FootBoardManager.Get_DisappearingBoardIndex(); };
	FootBoardManager& Get_FootBoardManager() noexcept { return m_FootBoardManager; }
	///////////////////////////////// Get

	///////////////////////////////// Set
	//void Set_PlayerBoardIndex(const int& playerboardindex) noexcept { m_PlayerBoardIndex = playerboardindex; }
	void Set_RoadObserver(RoadSubject* subject) noexcept { m_pRoadSubject = subject; };
	///////////////////////////////// Set
	
	///////////////////////////////// Receive
	virtual void Receive_PlayerWaitCamera(CPlayer* player) override;
	virtual void Receive_PlayerJumpFinish(CPlayer* player) override;
	virtual void Receive_PlayerJumping(CPlayer* player)	override;
	virtual void Receive_PlayerAutoWaiting(CPlayer* player) override;
	///////////////////////////////// Receive

	///////////////////////////////// Etc

	///////////////////////////////// Etc
};
