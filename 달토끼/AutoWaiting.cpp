#include "pch.h"
#include "Player.h"
#include "AutoWaiting.h"

CAutoWaiting::CAutoWaiting()
{
}

CAutoWaiting::~CAutoWaiting()
{
}

void CAutoWaiting::Initialize()
{
	IsUsing = true;
	m_JumpNum = 0;
}

void CAutoWaiting::Update(CPlayer & player)
{
	if (m_JumpNum > MaxJum) {
		Reset();
		player.StateChange_Wait();
		return;
	}

	player.AutoWaiting();
	Add_JumpNum();
}

void CAutoWaiting::SpecialKeys(CPlayer & player, const int & key)
{
	//Do nothing
}

void CAutoWaiting::Reset()
{
	IsUsing = false;
	m_JumpNum = 0;
}
