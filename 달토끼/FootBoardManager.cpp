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

	m_pFootBoard = new CFootBoard*[m_Length];
	for (int index = 0; index < m_Length; ++index)
	{
		m_pFootBoard[index] = new CFootBoard[m_Width];
	}

	JumpProperty::Initialize();

	GLdouble footboardY = -20;
	GLdouble itemY = 20;

	m_pFootBoard[0][k_FrontIndex].InitPosition(CVector3D<>(0, footboardY, 0));
	m_pFootBoard[0][k_FrontIndex].IsExisted();
	itemmanager.Set_Pos(0, CVector3D<> (0, itemY, 0));

	//맨 첫번째는 이동하지 않으므로 1부터 시작
	srand(time(NULL));
	int prev_Side = 0;
	for (int x = 1; x < m_Length - 1; ++x) {
		int nowSide = Side::Get_randSide();

		//왼쪽발판 다음에서 오른쪽 발판이 생성되는 경우
		bool Is_Left_to_Right = (prev_Side == k_LeftIndex) && (nowSide == k_RightIndex);
		if (Is_Left_to_Right) {
			nowSide = k_FrontIndex;
		}
		//오른쪽발판 다음에서 왼쪽 발판이 생성되는 경우
		bool Is_Right_to_Left = (prev_Side == k_RightIndex) && (nowSide == k_LeftIndex);
		if (Is_Right_to_Left) {
			nowSide = k_FrontIndex;
		}

		// nowSide - 1 : 양수일 경우 right, 음수일경우 left 위치
		float tranlateX = JumpProperty::k_RoadDistance_X * (nowSide - 1);
		float tranlateZ = -x * JumpProperty::Get_JumpReach();

		CVector3D<> pos(tranlateX, footboardY, tranlateZ);
		m_pFootBoard[x][nowSide].InitPosition(pos);
		m_pFootBoard[x][nowSide].IsExisted();
		pos.y = itemY;
		itemmanager.Set_Pos(x, pos);
		
		prev_Side = nowSide;
	}
	//마지막은 반드시 가운데
	float tranlateX = 0;
	float tranlateZ = -(m_Length - 1) * JumpProperty::Get_JumpReach();
	m_pFootBoard[m_Length - 1][k_FrontIndex].InitPosition(CVector3D<>(tranlateX, footboardY, tranlateZ));
	m_pFootBoard[m_Length - 1][k_FrontIndex].HasLight();
	m_pFootBoard[m_Length - 1][k_FrontIndex].IsExisted();
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

	for (int len = 0; len < m_Length; ++len) {
		for (int index = 0; index < m_Width; ++index) {
			m_pFootBoard[len][index].Render();
		}
	}

	glDisable(GL_BLEND);
}

void FootBoardManger::Render()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//플레이어 위치 기준으로 다섯개까지 렌더한다.
	int MaxIndex = min(m_DisappearingBoardIndex + 7, m_Length);
	for (int len = m_DisappearingBoardIndex; len < MaxIndex; ++len) {
		for (int index = 0; index < m_Width; ++index) {
			m_pFootBoard[len][index].Render();
		}
	}
	m_pFootBoard[m_Length - 1][k_FrontIndex].Render();

	glDisable(GL_BLEND);
}

void FootBoardManger::Update()
{
	for (int index = 0; index < m_Width; ++index) {
		m_pFootBoard[m_DisappearingBoardIndex][index].Update();
	}

	if (Get_DisappearLength(m_DisappearingBoardIndex)) {
		m_DisappearingBoardIndex += 1;
	}
}

const CVector3D<> FootBoardManger::Get_LastPos() const noexcept
{
	return m_pFootBoard[m_Length - 1][k_FrontIndex].Get_Pos();
}

const CVector3D<> FootBoardManger::Get_FirstPos() const noexcept
{
	return m_pFootBoard[0][k_FrontIndex].Get_Pos();
}

const Side FootBoardManger::Get_Side(const int & len, const int & index) const noexcept
{
	//반드시 수정
	if (IsOutRange_Length(len)) return Side();
	if (IsOutRange_Width(index)) return Side();

	Side val;
	if (index == k_FrontIndex) {
		val.IsFront();
		return val;
	}
	else if (index == k_LeftIndex) {
		val.IsLeft();
		return val;
	}
	else if (index == k_RightIndex) {
		val.IsRight();
		return val;
	}
	
	return val;
}

const bool FootBoardManger::IsOutRange_DisappearingIndex() const
{
	return (m_DisappearingBoardIndex < 0 || m_DisappearingBoardIndex >= m_Length);
}

const bool FootBoardManger::IsOutRange_Length(const int & len) const
{
	return len < 0 || len >= m_Length;
}

const bool FootBoardManger::IsOutRange_Width(const int & index) const
{
	return index < 0 || index >= m_Width;
}

void FootBoardManger::Add_DisappearingIndex(const CPlayer & player)
{
	m_DisappearingBoardIndex = max(m_DisappearingBoardIndex, player.Get_BoardLength() - 1);
	
	if (IsOutRange_DisappearingIndex()) {
		m_DisappearingBoardIndex = m_Length;
	}
}

// len : 앞으로 나아간 정도 (0부터 시작)
// index : 오른쪽, 왼쪽, 앞
const CVector3D<> FootBoardManger::Get_Pos(const int & len, const int & index) const noexcept
{
	if (IsOutRange_Length(len)) return CVector3D<>();
	if (IsOutRange_Width(index)) return CVector3D<>();
	
	return m_pFootBoard[len][index].Get_Pos();
}

const bool FootBoardManger::Get_Disappear(const int & len, const int & index) const noexcept
{
	if (IsOutRange_Length(len)) return false;
	if (IsOutRange_Width(index)) return false;

	return m_pFootBoard[len][index].GetDisappear();
}

const bool FootBoardManger::Get_DisappearLength(const int & len) const noexcept
{
	if (IsOutRange_Length(len)) return false;

	for (int index = 0; index < m_Width; ++index) {
		if (m_pFootBoard[len][index].GetDisappear()) {
			return true;
		}
	}
	return false;
}

const bool FootBoardManger::Get_IsExisted(const int & len, const int & index) const noexcept
{
	if (IsOutRange_Length(len)) return false;
	if (IsOutRange_Width(index)) return false;

	return m_pFootBoard[len][index].Get_IsExisted();
}
