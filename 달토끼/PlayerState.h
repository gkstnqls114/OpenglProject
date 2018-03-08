#pragma once

class CPlayer;

class CPlayerState
{

public:
	CPlayerState();
	virtual ~CPlayerState();

	virtual void Initialize() = 0;
	virtual void Update(CPlayer& player) = 0;
	virtual void SpecialKeys(CPlayer& player, const int& key) = 0;
};

