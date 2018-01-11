#pragma once
#include "PlayerState.h"

class CJumping :
	public CPlayerState
{
	CPlayer* m_pPlayer{ nullptr };

public:
	CJumping();
	virtual ~CJumping();

	virtual void Update() override;
	virtual void SpecialKeys(const unsigned char& key) override;
};

