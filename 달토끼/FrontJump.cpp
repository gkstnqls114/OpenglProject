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

void CFrontJump::Update(CPlayer * player)
{
	player->RotateZ(1);
}

void CFrontJump::SpecialKeys(CPlayer * player, const int & key)
{
	if (key == GLUT_KEY_DOWN) {
		player->Wait();
	}
}
