#pragma once
#include "PlayerState.h"

class CStartJump :
	public CPlayerState
{
public:
	CStartJump(CPlayer* player);
	virtual ~CStartJump();

	virtual void Behave() override;
	virtual void Keyboard(const unsigned char& key) override;
};

