#pragma once
#include "PlayerState.h"

class CJumping :
	public CPlayerState
{
public:
	CJumping();
	virtual ~CJumping();

	virtual void Behave() override;
	virtual void Keyboard(const unsigned char& key) override;
};

