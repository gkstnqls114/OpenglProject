#pragma once

class CPlayer;

class PlayerObserver
{
	
public:
	PlayerObserver();
	~PlayerObserver();

	virtual void Receive_PlayerWaitCamera(CPlayer* player) = 0;
	virtual void Receive_PlayerJumpFinish(CPlayer* player) = 0;
	virtual void Receive_PlayerJumping(CPlayer* player) = 0;

};