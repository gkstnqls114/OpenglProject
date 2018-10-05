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
	b_IsUsing = true;
	m_JumpNum = 0;
	m_WaitTime = 0;
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
	b_IsUsing = false;
	m_JumpNum = 0;
}

const bool CAutoWaiting::IsPossibleUpdate()
{
	if (m_WaitTime == m_MAXWaitTime) {
		m_WaitTime = 0;
		return true;
	}
	else {
		m_WaitTime += 1;
		return false;
	}
}
