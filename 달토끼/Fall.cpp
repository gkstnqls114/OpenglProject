#include "pch.h"
#include "Player.h"
#include "Fall.h"


CFalling::CFalling()
{
}


CFalling::~CFalling()
{
}

void CFalling::Initialize()
{
}

void CFalling::Update(CPlayer * player)
{
	player->Fall();
}

void CFalling::SpecialKeys(CPlayer * player, const int & key)
{
}
