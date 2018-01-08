#pragma once
#include "PlayerState.h"

class CPlayer;

class CWaiting :
	public CPlayerState
{
	CPlayer* m_pPlayer{ nullptr };

public:
	CWaiting(CPlayer* player);
	virtual ~CWaiting();

	virtual void Behave() override;
	virtual void Keyboard(const unsigned char& key) override;
};

