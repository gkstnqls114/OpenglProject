#pragma once
#include "Jumping.h"
class CLeftJump :
	public CJumping
{
public:
	CLeftJump();
	virtual ~CLeftJump();

	virtual void Update() override;
	virtual void SpecialKeys(const unsigned char& key) override;

};

