#pragma once
#include "PlayerState.h"

class CDead :
	public CPlayerState
{

public:
	CDead();
	virtual ~CDead();

	virtual void Initialize() override;
	virtual void Update(CPlayer* player) override;
	virtual void SpecialKeys(CPlayer* player, const int& key) override;
};
