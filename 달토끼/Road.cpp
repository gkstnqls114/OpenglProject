#include "pch.h"
#include "FootBoard.h"
#include "RoadState.h"
#include "RoadSubject.h"
#include "Player.h"

#include "Road.h"

Road::Road()
{
	m_RoadLength = 100;
	m_FootBoardManager.Initialize(m_RoadLength, m_ItemManager);
}

Road::Road(const int & num)
{
	m_RoadLength = num;
	m_FootBoardManager.Initialize(num, m_ItemManager);
}

Road::~Road()
{

}

void Road::Render()
{
	m_FootBoardManager.Render();
	m_ItemManager.Render();
}

void Road::TestRender()
{
	m_FootBoardManager.TestRender();
	m_ItemManager.TestRender();
}

void Road::Update()
{

}

void Road::Reset()
{
	m_RoadState->Update(*this);
}

const CVector3D<> Road::Get_LastPos() const noexcept
{
	return m_FootBoardManager.Get_LastPos();
}

const CVector3D<> Road::Get_FirstPos() const noexcept
{
	return m_FootBoardManager.Get_FirstPos();
}

void Road::Disappear()
{
	m_FootBoardManager.Update();
}

void Road::Stop()
{
	//아무 행동도 하지 않는다.
	//doing nothing
}

void Road::StateChange_Disappear()
{
	m_RoadState = &DisappearState;
}

void Road::StateChange_Stop()
{
	m_RoadState = &StopState;
}

void Road::Receive_PlayerWaitCamera(CPlayer * player)
{
	StateChange_Stop();
}

void Road::Receive_PlayerJumpFinish(CPlayer* player)
{
	m_FootBoardManager.Add_DisappearingIndex();

	const bool IsCorrectSide = player->Get_BoardSide() == m_FootBoardManager.Get_Side(player->Get_BoardNum());
	if (!IsCorrectSide) {
		//Test를 위해 주석합니다.
		//player->StateChange_WaitCamera();
	}
}

//void Road::Player_JumpFinish(int playerside)
//{
	//플레이어 위치가 올바른 곳인지 확인
	/*bool IsWrongPos = m_pFootBoard[m_PlayerBoardIndex].GetSide() != playerside;
	if (IsWrongPos) {
		m_pMediator->Player_Dead();
		return;
	}
	bool IsGameClear = m_PlayerBoardIndex == (m_boardNum - 1);
	if (IsGameClear) {
		m_pFootBoard[m_boardNum - 1].IsNotLight();
		return;
	}

	if (m_PlayerBoardIndex - 2 < 0) {
		m_DisappearingBoardIndex = 0;
	}
	else {
		m_DisappearingBoardIndex = m_PlayerBoardIndex - 2;
	}*/
//}
