#include "pch.h"
#include "FootBoard.h"
#include "RoadState.h"
#include "RoadSubject.h"
#include "Player.h"

#include "Road.h"

void Road::Add_DisappearingBoardIndex()
{
	//if (IsOutRange_Disappearing()) return;

	//m_DisappearingBoardIndex += 1;
}

Road::Road()
{

	StateChange_Disappear();
}

Road::~Road()
{
	CFootBoard::DeleteModel();
}

void Road::Render()
{
	m_FootBoardManager.Render();
}

void Road::TestRender()
{
	m_FootBoardManager.TestRender();
}

void Road::Update()
{
	m_FootBoardManager.Update();
}

void Road::Reset()
{

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

	//if (m_pFootBoard[m_PlayerBoardIndex].GetDisappear()) {
	//	m_pMediator->Player_Dead();
	//}

	////�� if���� ���� �߿�!
	//if (m_pFootBoard[m_DisappearingBoardIndex].GetDisappear()) {
	//	m_pRoadSubject->Notify_DisappearFootBoard(this);
	//	m_DisappearingBoardIndex += 1;
	//}
}

void Road::Stop()
{
	//�ƹ� �ൿ�� ���� �ʴ´�.
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
	Add_DisappearingBoardIndex();

	const bool IsCorrectSide = player->Get_BoardSide() == m_FootBoardManager.Get_Side(player->Get_BoardNum());
	if (!IsCorrectSide) {
		//Test�� ���� �ּ��մϴ�.
		//player->StateChange_WaitCamera();
	}
}

//void Road::Player_JumpFinish(int playerside)
//{
	//�÷��̾� ��ġ�� �ùٸ� ������ Ȯ��
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
