#pragma once

class CPlayerState
{

public:
	CPlayerState();
	virtual ~CPlayerState();

	virtual void Behave() = 0;
	virtual void Keyboard(const unsigned char& key) = 0;
};

