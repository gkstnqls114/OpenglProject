#include "pch.h"
#include "Player.h"
#include "Road.h"
#include "Camera.h"
#include "Moon.h"
#include "Earth.h"
#include "PLAY_word.h"
#include "EXIT_word.h"
#include "SceneManager.h"
#include "Mediator.h"

CMediator::CMediator(CSceneManager *& manager)
{
	m_pSceneManager = manager;
}

CMediator::~CMediator()
{

}

void CMediator::GameOver()
{
	m_pSceneManager->ChangeToGameOver();
	Init_GameOver();
}

void CMediator::GameClear()
{
	m_pSceneManager->ChangeToGameClear();
	Init_GameClear();
}

void CMediator::MainScene()
{
	m_pSceneManager->ChangeToMain();
	Init_MainScene();
}

void CMediator::GameScene()
{
	m_pSceneManager->ChangeToGame();
	Init_GameScene();
}

void CMediator::TestScene()
{
}

void CMediator::Init_MainScene()
{
	if(m_pEarth)	m_pEarth->Init_MainScene();
	if(m_pCamera)	m_pCamera->Init_MainScene();
	if(m_pMoon)		m_pMoon->Init_MainScene();
	if (m_pPLAY)	m_pPLAY->Init_MainScene();
	if (m_pEXIT)	m_pEXIT->Init_MainScene();
}

void CMediator::Cursor_PLAY()
{
	if (m_pPLAY)	m_pPLAY->Cursor_PLAY();
	if (m_pEXIT)	m_pEXIT->Cursor_PLAY();
}

void CMediator::Cursor_EXIT()
{
	if (m_pPLAY)	m_pPLAY->Cursor_EXIT();
	if (m_pEXIT)	m_pEXIT->Cursor_EXIT();
}

void CMediator::GameStart()
{
	if (m_pEarth)	m_pEarth->GameStart();
	if (m_pMoon)	m_pMoon->GameStart();
	if (m_pPLAY)	m_pPLAY->GameStart();
	if (m_pEXIT)	m_pEXIT->GameStart();
}


void CMediator::Init_GameScene()
{
	if (m_pPlayer)	m_pPlayer->Init_GameScene();
	if (m_pCamera)	m_pCamera->Init_GameScene();
	if (m_pRoad)	m_pRoad->Init_GameScene();
}

void CMediator::Player_JumpStart()
{
	if (m_pPlayer)	m_pPlayer->Player_JumpStart();
	if (m_pCamera)	m_pCamera->Player_JumpStart();
	if (m_pRoad)	m_pRoad->Player_JumpStart();
}

void CMediator::Player_Jumping()
{
	if (m_pPlayer)	m_pPlayer->Player_Jumping();

	CVector3D<> jumpmove
		(
		m_pPlayer->Get_VectorX(),
		0,
		m_pPlayer->Get_VectorZ()
		);

	if (m_pCamera) m_pCamera->Player_Jumping(jumpmove);
	if (m_pRoad) m_pRoad->Player_Jumping();
}

void CMediator::Player_JumpFinish()
{
	if (m_pPlayer)	m_pPlayer->Player_JumpFinish();
	if (m_pCamera)	m_pRoad->Player_JumpFinish(m_pPlayer->Get_Side());
	if (m_pRoad)	m_pCamera->Player_JumpFinish();
}

void CMediator::Player_Dead()
{
	std::cout << "Mediator: 플레이어 죽음 완료" << std::endl;
	if (m_pPlayer)	m_pPlayer->Player_Dead();
	if (m_pCamera)	m_pRoad->Player_Dead();
	if (m_pRoad)	m_pCamera->Player_Dead();
}

void CMediator::Init_GameOver()
{
}

void CMediator::Init_GameClear()
{
}


