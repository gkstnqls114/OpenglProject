#pragma once
#include "PlayerState.h"

class WaitCamera :
	public CPlayerState
{
public:
	WaitCamera();
	virtual ~WaitCamera();

	virtual void Initialize() override;
	virtual void Update(CPlayer* player) override;
	virtual void SpecialKeys(CPlayer* player, const int& key) override;
};

