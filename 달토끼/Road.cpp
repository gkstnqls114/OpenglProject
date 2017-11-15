#include "pch.h"
#include "FootBoard.h"
#include "Road.h"


CRoad::CRoad()
{
	std::cout << "Road 持失切" << std::endl;

	CFootBoard::InitModel();
	p = new CFootBoard[m_boardNum];

	for (int x = 0; x < m_boardNum; ++x) {
		p[x].Translate(0, 0, - x * 100);
	}
}


CRoad::~CRoad()
{
	std::cout << "Road 社瑚切" << std::endl;

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
