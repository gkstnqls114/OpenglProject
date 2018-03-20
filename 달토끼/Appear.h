#pragma once
#include "PlayerState.h"

//쉴드 아이템 애니메이션: 발판 위에서 나타납니다.
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
