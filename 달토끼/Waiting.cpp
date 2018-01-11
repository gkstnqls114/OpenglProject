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
	player->RotateY(1);
}

void CWaiting::SpecialKeys(CPlayer * player, const int & key)
{
	if (key == GLUT_KEY_DOWN) {
		player->Jump();
	}
}
