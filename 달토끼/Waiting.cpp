#include "pch.h"
#include "Player.h"
#include "Waiting.h"



CWaiting::CWaiting(CPlayer * player)
{
	m_pPlayer = player;
}

CWaiting::~CWaiting()
{
}

void CWaiting::Initialize()
{

}

void CWaiting::Update()
{
	m_pPlayer->RotateY(1);
}

void CWaiting::SpecialKeys(const unsigned char & key)
{
}
