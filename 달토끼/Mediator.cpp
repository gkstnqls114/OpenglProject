#include "pch.h"
#include "Player.h"
#include "Road.h"
#include "Camera.h"
#include "Mediator.h"


CMediator::CMediator()
{
}

CMediator::CMediator(CPlayer *& p, CRoad *& r, CCamera *& m)
{
	m_pPlayer = p;
	m_pRoad = r;
	m_pCamera = m;
}

CMediator::~CMediator()
{

}

void CMediator::Set_Colleague(CPlayer *& p, CRoad *& r, CCamera *& m)
{
	m_pPlayer = p;
	m_pRoad = r;
	m_pCamera = m;
}


void CMediator::Player_JumpStart()
{
	m_pPlayer->Player_JumpStart();
	m_pCamera->Player_JumpStart();
	m_pRoad->Player_JumpStart();
}

void CMediator::Player_Jumping()
{
	m_pPlayer->Player_Jumping();

	CVector3D jumpmove
		(
		m_pPlayer->Get_VectorX(),
		0,
		m_pPlayer->Get_VectorZ()
		);

	m_pCamera->Player_Jumping(jumpmove);

	m_pRoad->Player_Jumping();
}

void CMediator::Player_JumpFinish()
{
	std::cout << "Mediator: 플레이어 점프 완료" << std::endl;
	m_pPlayer->Player_JumpFinish();
	m_pRoad->Player_JumpFinish(m_pPlayer->Get_Side());
	m_pCamera->Player_JumpFinish();
}

void CMediator::Player_Dead()
{
	std::cout << "Mediator: 플레이어 죽음 완료" << std::endl;
	m_pPlayer->Player_Dead();
	m_pRoad->Player_Dead();
	m_pCamera->Player_Dead();
}


