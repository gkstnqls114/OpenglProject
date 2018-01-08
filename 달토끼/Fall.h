#pragma once
#include "PlayerState.h"

class CFall :
	public CPlayerState
{
	CPlayer* m_pPlayer{ nullptr };

public:
	CFall();
	virtual ~CFall();

	virtual void Update() override;
	virtual void Keyboard(const unsigned char& key) override;
};

