#include "pch.h"
#include "Mediator.h"
#include "FootBoard.h"
#include "Road.h"


void CRoad::InitFootBoardModel()
{
	CFootBoard::InitModel();
	m_pFootBoard = new CFootBoard[m_boardNum];
}

void CRoad::InitFootBoardPos(const GLdouble& distance)
{
	int prev_Side = 0;
	m_pFootBoard[0].InitPosition(CVector3D<>(0, -5, 0));

	//�� ù��°�� �̵����� �����Ƿ� 1���� ����
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
		float tranlateZ = -x * distance;
		m_pFootBoard[x].InitPosition(CVector3D<>(tranlateX, -5, tranlateZ));

		prev_Side = nowSide;
	}
	//�������� �ݵ�� ���
	float tranlateX = 0;
	float tranlateZ = -(m_boardNum - 1) * distance;
	m_pFootBoard[m_boardNum - 1].InitPosition(CVector3D<>(tranlateX, -5, tranlateZ));

}

CRoad::CRoad(const GLdouble& distance, CMediator*& mediator)
{
	//m_boardNum = 100;
	m_boardNum = 10;

	InitFootBoardModel();
	InitFootBoardPos(distance);

	m_pMediator = mediator;
}


CRoad::~CRoad()
{
	CFootBoard::DeleteModel();
	delete[] m_pFootBoard;
}

void CRoad::Render()
{
	if (isPlayerDead) return;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	int MaxNum = min(m_boardNum, m_PlayerPosNum + 5);
	for (int x = m_DisappearBoardNum; x < MaxNum; ++x) {
		m_pFootBoard[x].Render();
	}
	glDisable(GL_BLEND);
}

void CRoad::Update()
{
	if (isGameClear) return;
	if (isPlayerDead) return;

	m_pFootBoard[m_DisappearBoardNum].Update();

	if (m_pFootBoard[m_PlayerPosNum].GetDisappear()) {
		m_pMediator->Player_Dead();
	}

	//�� if���� ���� �߿�!
	if (m_pFootBoard[m_DisappearBoardNum].GetDisappear()) {
		m_DisappearBoardNum += 1;
	}
}

const CVector3D<> CRoad::GetLastPos() const noexcept
{
	return m_pFootBoard[m_boardNum - 1].GetPos();
}

const CVector3D<> CRoad::GetFirstPos() const noexcept
{
	return m_pFootBoard[0].GetPos();
}

const CVector3D<> CRoad::GetCenterPos() const noexcept
{
	CVector3D<> Center;
	if (m_boardNum % 2 == 0) {
		int center_num_1 = m_boardNum / 2;
		int center_num_2 = center_num_1 + 1;
		CVector3D<> Prev = m_pFootBoard[center_num_1].GetPos();
		CVector3D<> Next = m_pFootBoard[center_num_2].GetPos();

		Center = CVector3D<>(
			(Prev[0] + Next[0]) / 2
			, (Prev[1] + Next[1]) / 2
			, (Prev[2] + Next[2]) / 2
			);
	}
	else {
		int center_num = float(m_boardNum) / 2.f + 0.5;
		Center = m_pFootBoard[center_num].GetPos();
	}
	return Center;
}

void CRoad::Init_GameScene()
{
	for (int index = 0; index < m_boardNum; ++index) {
		m_pFootBoard[index].Init_GameScene();
	}
	m_PlayerPosNum = 0;
	m_DisappearBoardNum = 0;
	isPlayerDead = false;
	isGameClear = false;
}

void CRoad::Player_JumpStart()
{
	m_PlayerPosNum += 1;
}

void CRoad::Player_Jumping()
{

}

void CRoad::Player_JumpFinish(int playerside)
{
	//�÷��̾� ��ġ�� �ùٸ� ������ Ȯ��
	bool IsWrongPos = m_pFootBoard[m_PlayerPosNum].GetSide() != playerside;
	if (IsWrongPos) {
		m_pMediator->Player_Dead();
		return;
	}
	bool IsGameClear = m_PlayerPosNum == (m_boardNum - 1);
	if (IsGameClear) {
		m_pMediator->Player_Clear();
		return;
	}

	if (m_PlayerPosNum - 2 < 0) {
		m_DisappearBoardNum = 0;
	}
	else {
		m_DisappearBoardNum = m_PlayerPosNum - 2;
	}
}

void CRoad::Player_Dead()
{
	isPlayerDead = true;
}

void CRoad::Player_Fall()
{
}

void CRoad::Player_Clear()
{
	isGameClear = true;
}
