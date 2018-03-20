#pragma once
#include "PlayerState.h"

//���� ������ �ִϸ��̼�: ���� ������ ��Ÿ���ϴ�.
class Appear
	: public CPlayerState
{

public:
	Appear();
	virtual ~Appear();

	virtual void Initialize() override;
	virtual void Update(CPlayer& player) override;
	virtual void SpecialKeys(CPlayer& player, const int& key) override;
};
