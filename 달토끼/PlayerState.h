#pragma once

class CPlayer;

class CPlayerState
{

public:
	CPlayerState();
	virtual ~CPlayerState();

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void SpecialKeys(const unsigned char& key) = 0;
};

