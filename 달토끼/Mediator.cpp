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

void CMediator::Player_JumpFinish()
{
	std::cout << "Mediator: 플레이어 점프 완료" << std::endl;
	m_pPlayer->Player_JumpFinish();
	m_pRoad->Player_JumpFinish();
	m_pCamera->Player_JumpFinish();
}

void CMediator::Player_Dead()
{
	std::cout << "Mediator: 플레이어 죽음 완료" << std::endl;
	m_pPlayer->Player_Dead();
	m_pRoad->Player_Dead();
	m_pCamera->Player_Dead();
}

void CMediator::Road_playerBoard_Disapper()
{
	std::cout << "Mediator: 플레이어 보드 사라짐 완료" << std::endl;
	m_pPlayer->Road_playerBoard_Disapper();
	m_pRoad->Road_playerBoard_Disapper();
	m_pCamera->Road_playerBoard_Disapper();
}

