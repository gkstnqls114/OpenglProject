#pragma once
#include "PlayerState.h"

class CFinishJump :
	public CPlayerState
{
	CPlayer* m_pPlayer{ nullptr };
	
public:
	CFinishJump();
	virtual ~CFinishJump();

	virtual void Update() override;
	virtual void SpecialKeys(const unsigned char& key) override;

};

