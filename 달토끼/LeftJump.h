#pragma once
#include "Jump.h"

class CLeftJump :
	public CJump
{
public:
	CLeftJump();
	virtual ~CLeftJump();

	virtual void Initialize() override;
	virtual void Update(CPlayer* player) override;
	virtual void SpecialKeys(CPlayer* player, const int& key) override;

};

