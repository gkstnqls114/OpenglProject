#include "pch.h"
#include "ItemManager.h"
#include "FootBoard.h"
#include "JumpProperty.h"
#include "Player.h"
#include "FootBoardManager.h"

FootBoardManger::FootBoardManger()
{
	InitFootBoardModel();
}

FootBoardManger::FootBoardManger(const int & num, ItemManager& itemManager)
{
	InitFootBoardModel();
	Initialize(num, itemManager);
}

FootBoardManger::~FootBoardManger()
{
	delete[] m_pFootBoard;
}

void FootBoardManger::Set_FootBoardPos(ItemManager & itemmanager)
{
	if (m_pFootBoard) return;

	m_pFootBoard = new CFootBoard[m_Length];

	JumpProperty::Initialize();

	GLdouble footboardY = -20;
	GLdouble itemY = 30;

	m_pFootBoard[0].InitPosition(CVector3D<>(0, footboardY, 0));
	itemmanager.Set_Pos(0, CVector3D<> (0, itemY, 0));

	//맨 첫번째는 이동하지 않으므로 1부터 시작
	srand(time(NULL));
	int prev_Side = 0;
	for (int x = 1; x < m_Length - 1; ++x) {
		int nowSide = k_side[rand() % 3];

		//왼쪽발판 다음에서 오른쪽 발판이 생성되는 경우
		bool Is_Left_to_Right = (prev_Side == k_left) && (nowSide == k_right);
		if (Is_Left_to_Right) {
			nowSide = k_front;
		}
		//오른쪽발판 다음에서 왼쪽 발판이 생성되는 경우
		bool Is_Right_to_Left = (prev_Side == k_right) && (nowSide == k_left);
		if (Is_Right_to_Left) {
			nowSide = k_front;
		}

		float tranlateX = JumpProperty::k_RoadDistance_X * nowSide;
		float tranlateZ = -x * JumpProperty::Get_JumpReach();

		CVector3D<> pos(tranlateX, footboardY, tranlateZ);
		m_pFootBoard[x].InitPosition(pos);
		pos.y = itemY;
		itemmanager.Set_Pos(x, pos);
		
		prev_Side = nowSide;
	}
	//마지막은 반드시 가운데
	float tranlateX = 0;
	float tranlateZ = -(m_Length - 1) * JumpProperty::Get_JumpReach();
	m_pFootBoard[m_Length - 1].InitPosition(CVector3D<>(tranlateX, footboardY, tranlateZ));
	m_pFootBoard[m_Length - 1].HasLight();
	itemmanager.Set_Pos(m_Length - 1, CVector3D<>(tranlateX, itemY, tranlateZ));
}

void FootBoardManger::InitFootBoardModel()
{
	CFootBoard::InitModel();
}

void FootBoardManger::Initialize(const int & num, ItemManager & itemManager)
{
	m_Length = num;
	Set_FootBoardPos(itemManager);
}

//전부 렌더합니다.
void FootBoardManger::TestRender()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (int x = 0; x < m_Length; ++x) {
		m_pFootBoard[x].Render();
	}

	glDisable(GL_BLEND);
}

void FootBoardManger::Render()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//플레이어 위치 기준으로 다섯개까지 렌더한다.
	int MaxIndex = min(m_DisappearingBoardIndex + 7, m_Length);
	for (int x = m_DisappearingBoardIndex; x < MaxIndex; ++x) {
		m_pFootBoard[x].Render();
	}
	m_pFootBoard[m_Length - 1].Render();

	glDisable(GL_BLEND);
}

void FootBoardManger::Update()
{
	m_pFootBoard[m_DisappearingBoardIndex].Update();

	if (Get_Disappear(m_DisappearingBoardIndex)) {
		m_DisappearingBoardIndex += 1;
	}
}

const CVector3D<> FootBoardManger::Get_LastPos() const noexcept
{
	return m_pFootBoard[m_Length - 1].Get_Pos();
}

const CVector3D<> FootBoardManger::Get_FirstPos() const noexcept
{
	return m_pFootBoard[0].Get_Pos();
}

const bool FootBoardManger::IsOutRange_DisappearingIndex() const
{
	return (m_DisappearingBoardIndex < 0 || m_DisappearingBoardIndex >= m_Length);
}

const bool FootBoardManger::IsOutRange(const int & boardnum) const
{
	return boardnum < 0 || boardnum >= m_Length;
}

void FootBoardManger::Add_DisappearingIndex(const CPlayer & player)
{
	m_DisappearingBoardIndex = max(m_DisappearingBoardIndex, player.Get_BoardIndex() - 1);
	
	if (IsOutRange_DisappearingIndex()) {
		m_DisappearingBoardIndex = m_Length;
	}
}

const int FootBoardManger::Get_Side(const int & boardnum) const noexcept
{
	if (IsOutRange(boardnum)) return 0;
	else return m_pFootBoard[boardnum].GetSide(); 
}

const CVector3D<> FootBoardManger::Get_Pos(const int & boardnum) const noexcept
{
	if (IsOutRange(boardnum)) return CVector3D<>();
	else return m_pFootBoard[boardnum].Get_Pos();
}

const int FootBoardManger::Get_Disappear(const int & boardnum) const noexcept
{
	if (IsOutRange(boardnum)) return 0;
	else return m_pFootBoard[boardnum].GetDisappear();
}
