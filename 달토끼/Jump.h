#pragma once
#include "PlayerState.h"
class CJump :
	public CPlayerState
{

public:
	CJump();
	virtual ~CJump();

	virtual void Initialize() = 0;
	virtual void Update(CPlayer* player) = 0;
	virtual void SpecialKeys(CPlayer* player, const int& key) = 0;
};

