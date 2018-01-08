#pragma once

class CPlayer;

class CPlayerState
{

public:
	CPlayerState();
	virtual ~CPlayerState();

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Keyboard(const unsigned char& key) = 0;
};

