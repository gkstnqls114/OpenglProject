#pragma once
#include "PlayerState.h"

class CFalling :
	public CPlayerState
{
public:
	CFalling();
	virtual ~CFalling();

	virtual void Initialize() override;
	virtual void Update(CPlayer& player) override;
	virtual void SpecialKeys(CPlayer& player, const int& key) override;
};

