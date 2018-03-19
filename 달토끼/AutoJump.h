#pragma once
#include "PlayerState.h"

class CAutoJump :
	public CPlayerState
{
public:
	CAutoJump();
	virtual ~CAutoJump();

	virtual void Initialize() override;
	virtual void Update(CPlayer& player) override;
	virtual void SpecialKeys(CPlayer& player, const int& key) override;

};