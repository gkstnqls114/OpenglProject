#include "pch.h"
#include "FootBoard.h"
#include "JumpProperty.h"
#include "FootBoardManager.h"

FootBoardManger::FootBoardManger()
{
	//Test
	m_boardNum = 100;
	//Test
	InitFootBoardModel();
	m_pFootBoard = new CFootBoard[m_boardNum];
	Initialize();
}

FootBoardManger::~FootBoardManger()
{
	delete[] m_pFootBoard;
}

void FootBoardManger::Initialize()
{
	if (!m_pFootBoard) return;

	JumpProperty::Initialize();
	
	m_pFootBoard[0].InitPosition(CVector3D<>(0, -5, 0));

	//�� ù��°�� �̵����� �����Ƿ� 1���� ����
	srand(time(NULL));
	int prev_Side = 0;
	for (int x = 1; x < m_boardNum - 1; ++x) {
		int nowSide = k_side[rand() % 3];

		//���ʹ��� �������� ������ ������ �����Ǵ� ���
		bool Is_Left_to_Right = (prev_Side == k_left) && (nowSide == k_right);
		if (Is_Left_to_Right) {
			nowSide = k_front;
		}

		//�����ʹ��� �������� ���� ������ �����Ǵ� ���
		bool Is_Right_to_Left = (prev_Side == k_right) && (nowSide == k_left);
		if (Is_Right_to_Left) {
			nowSide = k_front;
		}

		float tranlateX = Road_Distance_X * nowSide;
		float tranlateZ = -x * JumpProperty::Get_JumpReach();
		m_pFootBoard[x].InitPosition(CVector3D<>(tranlateX, -5, tranlateZ));
		
		prev_Side = nowSide;
	}
	//�������� �ݵ�� ���
	float tranlateX = 0;
	float tranlateZ = -(m_boardNum - 1) * JumpProperty::Get_JumpReach();
	m_pFootBoard[m_boardNum - 1].InitPosition(CVector3D<>(tranlateX, -5, tranlateZ));
	m_pFootBoard[m_boardNum - 1].IsLight();
}

void FootBoardManger::InitFootBoardModel()
{
	CFootBoard::InitModel();
}

//���� �����մϴ�.
void FootBoardManger::TestRender()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (int x = 0; x < m_boardNum; ++x) {
		m_pFootBoard[x].Render();
	}

	glDisable(GL_BLEND);
}

void FootBoardManger::Render()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//�÷��̾� ��ġ �������� �ټ������� �����Ѵ�.
	//int MaxNum = min(m_boardNum - 1, m_PlayerBoardIndex + 5);
	for (int x = m_DisappearingBoardIndex; x < m_DisappearingBoardIndex + 7; ++x) {
		m_pFootBoard[x].Render();
	}
	m_pFootBoard[m_boardNum - 1].Render();
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
	return m_pFootBoard[m_boardNum - 1].Get_Pos();
}

const CVector3D<> FootBoardManger::Get_FirstPos() const noexcept
{
	return m_pFootBoard[0].Get_Pos();
}

const bool FootBoardManger::IsOutRange_Disappearing() const
{
	return (m_DisappearingBoardIndex < 0 || m_DisappearingBoardIndex >= m_boardNum);
}

const bool FootBoardManger::IsOutRange(const int & boardnum) const
{
	return boardnum < 0 || boardnum >= m_boardNum;
}

const int FootBoardManger::Get_Side(const int & boardnum) const noexcept
{
	if (IsOutRange(boardnum)) return 0;
	else return m_pFootBoard[boardnum].GetSide(); 
}

const int FootBoardManger::Get_Disappear(const int & boardnum) const noexcept
{
	if (IsOutRange(boardnum)) return 0;
	else return m_pFootBoard[boardnum].GetDisappear();
}
