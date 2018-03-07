#pragma once
#include "PlayerState.h"

class CFrontJump :
	public CPlayerState
{
public:
	CFrontJump();
	virtual ~CFrontJump();

	virtual void Initialize() override;
	virtual void Update(CPlayer& player) override;
	virtual void SpecialKeys(CPlayer& player, const int& key) override;
};

