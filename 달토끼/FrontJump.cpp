#include "pch.h"
#include "Player.h"
#include "FrontJump.h"


CFrontJump::CFrontJump()
{
}


CFrontJump::~CFrontJump()
{
}

void CFrontJump::Initialize()
{
}

void CFrontJump::Update(CPlayer & player)
{
	player.FrontJump();
}

void CFrontJump::SpecialKeys(CPlayer & player, const int & key)
{
}

