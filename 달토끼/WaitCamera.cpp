#include "pch.h"
#include "Player.h"
#include "WaitCamera.h"


WaitCamera::WaitCamera()
{
}


WaitCamera::~WaitCamera()
{

}

void WaitCamera::Initialize()
{
}

void WaitCamera::Update(CPlayer & player)
{
	player.WaitCamera();
}

void WaitCamera::SpecialKeys(CPlayer & player, const int & key)
{
	//DO NOTHING
}

