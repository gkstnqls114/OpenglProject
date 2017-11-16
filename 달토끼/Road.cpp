#include "pch.h"
#include "FootBoard.h"
#include "Road.h"


void CRoad::InitFootBoard(const int& distance)
{
	std::cout << distance << ": �Ÿ�" << std::endl;

	const int k_left = -1;
	const int k_right = 1;
	const int k_front = 0;
	int prvSide = 0;
	//�� ù��°�� �̵����� �����Ƿ� 1���� ����
	for (int x = 1; x < m_boardNum; ++x) {
		int nowSide = k_side[rand() % 3];

		//���ʹ��� �������� ������ ������ �����Ǵ� ���
		bool isLefttoRight = (prvSide == k_left) && (nowSide == k_right);
		if (isLefttoRight) {
			nowSide = k_front;
		}

		//�����ʹ��� �������� ���� ������ �����Ǵ� ���
		bool isRighttoLeft = (prvSide == k_right) && (nowSide == k_left);
		if (isRighttoLeft) {
			nowSide = k_front;
		}

		float tranlateX = 20 * nowSide;
		float tranlateZ = -x * distance;
		p[x].InitPosition(tranlateX, 0, tranlateZ);

		prvSide = nowSide;
	}
}

CRoad::CRoad(const int& distance)
{
	std::cout << "Road ������" << std::endl;

	CFootBoard::InitModel();
	p = new CFootBoard[m_boardNum];
	InitFootBoard(distance);
}


CRoad::~CRoad()
{
	std::cout << "Road �Ҹ���" << std::endl;

	delete[] p;
}

void CRoad::Render()
{
	for (int x = 0; x < m_boardNum; ++x) {
		p[x].Render();
	}
}

void CRoad::Update()
{

}
