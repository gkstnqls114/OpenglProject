#pragma once
#include "PlayerState.h"

class CStartJump :
	public CPlayerState
{
	CPlayer* m_pPlayer{ nullptr };

public:
	CStartJump(CPlayer* player);
	virtual ~CStartJump();

	virtual void Update() override;
	virtual void SpecialKeys(const unsigned char& key) override;

};

