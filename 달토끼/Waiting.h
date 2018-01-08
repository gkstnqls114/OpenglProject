#pragma once
#include "PlayerState.h"

class CWaiting :
	public CPlayerState
{
	CPlayer* m_pPlayer{ nullptr };

public:
	CWaiting(CPlayer* player);
	virtual ~CWaiting();

	virtual void Update() override;
	virtual void Keyboard(const unsigned char& key) override;
};

