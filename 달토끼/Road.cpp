#include "pch.h"
#include "FootBoard.h"
#include "RoadState.h"
#include "RoadSubject.h"
#include "Player.h"

#include "Road.h"


void CRoad::InitFootBoardModel()
{
	CFootBoard::InitModel();
	m_pFootBoard = new CFootBoard[m_boardNum];
}

void CRoad::InitFootBoardPos(const GLdouble& distance)
{
	if (distance <= 0) return;
	JumpReach = distance;

	int prev_Side = 0;
	m_pFootBoard[0].InitPosition(CVector3D<>(0, -5, 0));

	//�� ù��°�� �̵����� �����Ƿ� 1���� ����
	srand(time(NULL));
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
	m_pFootBoard[m_boardNum - 1].IsLight();
}

const bool CRoad::IsOutRange() const
{
	return (m_DisappearingBoardIndex < 0 || m_DisappearingBoardIndex >= m_boardNum);
}

void CRoad::Add_DisappearingBoardIndex()
{
	if (IsOutRange()) return;

	m_DisappearingBoardIndex += 1;
}

CRoad::CRoad(const GLdouble & distance)
{
	m_boardNum = 100;

	InitFootBoardModel();
	InitFootBoardPos(distance);
	

	StateChange_Disappear();
}

CRoad::~CRoad()
{
	CFootBoard::DeleteModel();
	delete[] m_pFootBoard;
}

void CRoad::Render()
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

void CRoad::TestRender()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	for (int x = m_DisappearingBoardIndex; x < m_boardNum; ++x) {
		m_pFootBoard[x].Render();
	}

	glDisable(GL_BLEND);
}

void CRoad::Update()
{
	if (m_RoadState) m_RoadState->Update(*this);
}

const CVector3D<> CRoad::GetLastPos() const noexcept
{
	return m_pFootBoard[m_boardNum - 1].Get_Pos();
}

const CVector3D<> CRoad::GetFirstPos() const noexcept
{
	return m_pFootBoard[0].Get_Pos();
}

const CVector3D<> CRoad::GetCenterPos() const noexcept
{
	CVector3D<> Center;
	if (m_boardNum % 2 == 0) {
		int center_num_1 = m_boardNum / 2;
		int center_num_2 = center_num_1 + 1;
		CVector3D<> Prev = m_pFootBoard[center_num_1].Get_Pos();
		CVector3D<> Next = m_pFootBoard[center_num_2].Get_Pos();

		Center = CVector3D<>(
			  (Prev.x + Next.x) / 2
			, (Prev.y + Next.y) / 2
			, (Prev.z + Next.z) / 2
			);
	}
	else {
		int center_num = float(m_boardNum) / 2.f + 0.5;
		Center = m_pFootBoard[center_num].Get_Pos();
	}
	return Center;
}

void CRoad::Disappear()
{
	m_pFootBoard[m_DisappearingBoardIndex].Update();
	
	//if (m_pFootBoard[m_PlayerBoardIndex].GetDisappear()) {
	//	m_pMediator->Player_Dead();
	//}

	//�� if���� ���� �߿�!
	if (m_pFootBoard[m_DisappearingBoardIndex].GetDisappear()) {
		m_pRoadSubject->Notify_DisappearFootBoard(this);
		m_DisappearingBoardIndex += 1;
	}
}

void CRoad::Stop()
{
	//�ƹ� �ൿ�� ���� �ʴ´�.
	//doing nothing
}

void CRoad::StateChange_Disappear()
{
	m_RoadState = &DisappearState;
}

void CRoad::StateChange_Stop()
{
	m_RoadState = &StopState;
}

void CRoad::Receive_PlayerWaitCamera(CPlayer * player)
{
	StateChange_Stop();
}

void CRoad::Receive_PlayerJumpFinish(CPlayer* player)
{
	Add_DisappearingBoardIndex();

	//Test��
	int playerboardside = player->Get_BoardSide();
	std::cout << "�÷��̾� ���� �ѹ�:" ;
	switch (playerboardside)
	{
	case 1:
		std::cout << "������" << std::endl;
		break;
	case 0:
		std::cout << "���" << std::endl;
		break;
	case -1:
		std::cout << "����" << std::endl;
		break;
	}
	
	int boardside = m_pFootBoard[player->Get_BoardNum()].GetSide();
	std::cout << "������ ����ѹ� :";
	switch (boardside)
	{
	case 1:
		std::cout << "������" << std::endl;
		break;
	case 0:
		std::cout << "���" << std::endl;
		break;
	case -1:
		std::cout << "����" << std::endl;
		break;
	}
	std::cout << std::endl;
	//Test��

	const bool IsCorrectSide = player->Get_BoardSide() == m_pFootBoard[player->Get_BoardNum()].GetSide();
	if (!IsCorrectSide) {
		//Test�� ���� �ּ��մϴ�.
		//player->StateChange_WaitCamera();
	}
}

void CRoad::Init_GameScene()
{
	for (int index = 0; index < m_boardNum; ++index) {
		//m_pFootBoard[index].Init_GameScene();
	}
	m_pFootBoard[m_boardNum - 1].IsLight();
	InitFootBoardPos(JumpReach);
	
	m_DisappearingBoardIndex = 0;
}

void CRoad::Player_JumpFinish(int playerside)
{
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
}
