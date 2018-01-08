#pragma once
#include "PlayerState.h"

class CDead :
	public CPlayerState
{
	CPlayer* m_pPlayer{ nullptr };

public:
	CDead();
	virtual ~CDead();

	virtual void Update() override;
	virtual void Keyboard(const unsigned char& key) override;
};
