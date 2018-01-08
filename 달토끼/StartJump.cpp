#include "pch.h"
#include "StartJump.h"


CStartJump::CStartJump(CPlayer * player)
{
}

CStartJump::~CStartJump()
{
}

void CStartJump::Behave()
{
	if (rand() % 3 == 0) {
		IsTumbling = true;
	}
	else {
		IsTumbling = false;
	}
	m_pPlayer->ProcessSide(jumpSide);
}

void CStartJump::Keyboard(const unsigned char & key)
{
}
