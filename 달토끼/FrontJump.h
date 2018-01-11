#pragma once
#include "Jumping.h"
class CFrontJump :
	public CJumping
{
public:
	CFrontJump();
	virtual ~CFrontJump();

	virtual void Update() override;
	virtual void SpecialKeys(const unsigned char& key) override;
};

