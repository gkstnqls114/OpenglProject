#pragma once
#include "PlayerState.h"
#include "RoadState.h"

class CWaiting :
	public CPlayerState
{

public:
	CWaiting();
	virtual ~CWaiting();

	virtual void Initialize() override;
	virtual void Update(CPlayer* player) override;
	virtual void SpecialKeys(CPlayer* player, const int& key) override;
};

class Waiting :
	public RoadState
{
public:
	Waiting();
	virtual ~Waiting();
};

