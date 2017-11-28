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
	std::cout << distance << ": �Ÿ�" << std::endl;

	int prev_Side = 0;
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
		m_pFootBoard[x].InitPosition(CVector3D(tranlateX, 0, tranlateZ));

		prev_Side = nowSide;
	}
	//�������� �ݵ�� ���
	float tranlateX = 0;
	float tranlateZ = -(m_boardNum - 1) * distance;
	m_pFootBoard[m_boardNum - 1].InitPosition(CVector3D(tranlateX, 0, tranlateZ));

}

CRoad::CRoad(const GLdouble& distance, CMediator*& mediator)
{
	std::cout << "Road ������" << std::endl;
	
	InitFootBoardModel();
	InitFootBoardPos(distance);

	m_Mediator = mediator;
}


CRoad::~CRoad()
{
	std::cout << "Road �Ҹ���" << std::endl;
	
	CFootBoard::DeleteModel();
	delete[] m_pFootBoard;
}

void CRoad::Render()
{
	if (isPlayerDead) return;

	for (int x = m_DisappearBoardNum; x < m_PlayerPosNum + 5; ++x) {
		m_pFootBoard[x].Render();
	}
}

void CRoad::Update()
{
	if (isPlayerDead) return;

	m_pFootBoard[m_DisappearBoardNum].Update();

	if (m_pFootBoard[m_PlayerPosNum].GetDisappear()) {
		m_Mediator->Player_Dead();
	}

	//�� if���� ���� �߿�!
	if (m_pFootBoard[m_DisappearBoardNum].GetDisappear()) {
		m_DisappearBoardNum += 1;
	}
}

const CVector3D CRoad::GetLastPos() const noexcept
{
	return m_pFootBoard[m_boardNum - 1].GetPos();
}

const CVector3D CRoad::GetFirstPos() const noexcept
{
	return m_pFootBoard[0].GetPos();
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
		m_Mediator->Player_Dead();
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
