#pragma once
#include "Jump.h"

class CFrontJump :
	public CJump
{
public:
	CFrontJump();
	virtual ~CFrontJump();

	virtual void Initialize() override;
	virtual void Update(CPlayer* player) override;
	virtual void SpecialKeys(CPlayer* player, const int& key) override;
};

