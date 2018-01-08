#pragma once
#include "PlayerState.h"

class CDead :
	public CPlayerState
{
public:
	CDead();
	virtual ~CDead();

	virtual void Behave() override;
	virtual void Keyboard(const unsigned char& key) override;
};
