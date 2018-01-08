#pragma once
#include "PlayerState.h"

class CFall :
	public CPlayerState
{
public:
	CFall();
	virtual ~CFall();

	virtual void Behave() override;
	virtual void Keyboard(const unsigned char& key) override;
};

