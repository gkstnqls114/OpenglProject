#include "pch.h"
#include "Player.h"
#include "RightJump.h"


CRightJump::CRightJump()
{
}


CRightJump::~CRightJump()
{
}

void CRightJump::Initialize()
{
}

void CRightJump::Update(CPlayer & player)
{
	player.RightJump();
}

void CRightJump::SpecialKeys(CPlayer & player, const int & key)
{
}
