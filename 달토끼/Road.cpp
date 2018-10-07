#include "pch.h"
#include "Collision.h"
#include "FootBoard.h"
#include "RoadState.h"
#include "RoadSubject.h"
#include "Player.h"

#include "Road.h"

const bool Road::IsOutofRange(const int & len)
{
	return (0 > len || len >= m_RoadLength);
}

Road::Road()
{
	m_RoadLength = 5;
	m_FootBoardManager.Initialize(m_RoadLength, m_ItemManager);
	StateChange_Stop();
}

Road::Road(const int & num)
{
	m_RoadLength = num;
	m_ItemManager.Initialize(num);
	m_FootBoardManager.Initialize(num, m_ItemManager);
	StateChange_Stop();
}

Road::~Road()
{

}

void Road::Render()
{
	glPushMatrix();
	m_FootBoardManager.Render();
	m_ItemManager.Render(&m_FootBoardManager);
	glPopMatrix();
}

void Road::TestRender()
{
	m_FootBoardManager.TestRender();
	m_ItemManager.TestRender();
}

void Road::Update()
{
	m_RoadState->Update(*this);
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
	m_ItemManager.Update();
}

void Road::Stop()
{
	//FootBoardManager do nothing;
	m_ItemManager.Update();
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
	m_FootBoardManager.Add_DisappearingIndex(*player);

	Side player_sideindex = player->Get_BoardSide();
	Side road_sideindex = m_FootBoardManager.Get_Side(player->Get_BoardLength());


	const bool IsCorrectSide = player_sideindex.Get_Side() == road_sideindex.Get_Side();
	if (!IsCorrectSide) {
		player->StateChange_WaitCamera();
	}

	const bool IsGameClear = (player->Get_BoardLength() + 1)== (m_RoadLength);
	if (IsGameClear && IsCorrectSide) {
#ifdef _DEBUG
		std::cout << player->Get_BoardLength() << " , " << m_RoadLength << std::endl;
#endif // !_DEBUG

		player->SetClear();
		player->StateChange_WaitCamera();
	}
}


//플레이어 위치에 해당하는 아이템에 충돌체크를 합니다.
void Road::Receive_PlayerJumping(CPlayer * player)
{
	if (IsOutofRange(player->Get_BoardLength())) return;

	Collision::Collide(*player,	m_ItemManager.Get_Item(player->Get_BoardLength()));
}

// road에 적절한 위치로 점프 시킵니다.
void Road::Receive_PlayerAutoWaiting(CPlayer * player)
{
	int playerLenght = player->Get_BoardLength() + 1;
	Side playerSide = player->Get_BoardSide();
	Side footboardSide = m_FootBoardManager.Get_IsExisted(playerLenght);

	Side futureMove = playerSide.FutureMoveSide(footboardSide);

	if (futureMove.Get_IsFront()) {
		player->StateChange_FrontJump();
	}
	else if (futureMove.Get_IsLeft()) {
		player->StateChange_LeftJump();
	}
	else if (futureMove.Get_IsRight()) {
		player->StateChange_RightJump();
	}
}

void Road::Init_GameScene()
{
	m_ItemManager.Initialize(m_RoadLength);
	m_FootBoardManager.Initialize(m_RoadLength, m_ItemManager);
	StateChange_Stop();
}
