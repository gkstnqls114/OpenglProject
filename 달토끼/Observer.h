#pragma once

class CPlayer;
class CRoad;

class Observer
{

public:
	Observer();
	~Observer();

	virtual void Render() {};
	virtual void Update() {};

	virtual void Receive_PlayerJumping(CPlayer* player) { };
	virtual void Receive_PlayerWaitCamera(CPlayer* player) {};
	virtual void Receive_PlayerJumpFinish(CPlayer* player) {};


	virtual void Receive_DisappearFootBoard(CRoad* road) {};
};
