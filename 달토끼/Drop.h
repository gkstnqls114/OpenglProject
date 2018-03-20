#pragma once
#include "PlayerState.h"

//���� ������ �ִϸ��̼�: ���� ������ ��Ÿ���ϴ�.
class Drop
	: public CPlayerState
{

public:
	Drop();
	virtual ~Drop();

	virtual void Initialize() override;
	virtual void Update(CPlayer& player) override;
	virtual void SpecialKeys(CPlayer& player, const int& key) override;
};
