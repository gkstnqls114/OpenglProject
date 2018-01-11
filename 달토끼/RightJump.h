#pragma once
#include "Jumping.h"
class CRightJump :
	public CJumping
{
public:
	CRightJump();
	virtual ~CRightJump();

	virtual void Update() override;
	virtual void SpecialKeys(const unsigned char& key) override;

};

