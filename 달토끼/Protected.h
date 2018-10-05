#pragma once
#include "PlayerState.h"

class Protected
	: public CPlayerState
{
	bool b_IsUsing{ false };

public:
	Protected();
	virtual ~Protected();

	virtual void Initialize() override;
	virtual void Update(CPlayer& player) override;
	virtual void SpecialKeys(CPlayer& player, const int& key) override;

	void Reset();
	const bool Get_IsUsing() const { return b_IsUsing;  }
};