#include "pch.h"
#include "Player.h"
#include "LeftJump.h"


CLeftJump::CLeftJump()
{
}


CLeftJump::~CLeftJump()
{
}

void CLeftJump::Initialize()
{
}

void CLeftJump::Update(CPlayer & player)
{
	player.LeftJump();
}

void CLeftJump::SpecialKeys(CPlayer & player, const int & key)
{
}
