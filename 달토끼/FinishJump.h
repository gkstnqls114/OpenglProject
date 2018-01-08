#pragma once
#include "PlayerState.h"

class CFinishJump :
	public CPlayerState
{
public:
	CFinishJump();
	virtual ~CFinishJump();

	virtual void Behave() override;
	virtual void Keyboard(const unsigned char& key) override;
};

