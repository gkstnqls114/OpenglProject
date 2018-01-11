#pragma once
#include "Jump.h"

class CRightJump :
	public CJump
{
public:
	CRightJump();
	virtual ~CRightJump();

	virtual void Initialize() override;
	virtual void Update(CPlayer* player) override;
	virtual void SpecialKeys(CPlayer* player, const int& key) override;
};