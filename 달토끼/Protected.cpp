#include "pch.h"
#include "Protected.h"

Protected::Protected()
{
}

Protected::~Protected()
{
}

void Protected::Initialize()
{
	b_IsUsing = true;
}

void Protected::Update(CPlayer & player)
{
	//player.Protected();
}

void Protected::SpecialKeys(CPlayer & player, const int & key)
{
	// do nothing
}

void Protected::Reset()
{
	b_IsUsing = false;
}
