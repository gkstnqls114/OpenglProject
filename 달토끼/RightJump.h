#pragma once
#include "PlayerState.h"

class CRightJump :
	public CPlayerState
{
public:
	CRightJump();
	virtual ~CRightJump();

	virtual void Initialize() override;
	virtual void Update(CPlayer& player) override;
	virtual void SpecialKeys(CPlayer& player, const int& key) override;
};