#include "pch.h"
#include "Player.h"
#include "Waiting.h"



CWaiting::CWaiting()
{

}

CWaiting::~CWaiting()
{
}

void CWaiting::Initialize()
{
}

void CWaiting::Update(CPlayer * player)
{
	//아무것도 하지 않는다.
}

void CWaiting::SpecialKeys(CPlayer * player, const int & key)
{
	if (key == GLUT_KEY_UP) {
		player->StateChange_FrontJump();
	}
	else if (key == GLUT_KEY_RIGHT) {
		player->StateChange_RightJump();
	}
	else if (key == GLUT_KEY_LEFT) {
		player->StateChange_LeftJump();
	}
}
