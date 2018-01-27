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

	virtual void Notify_PlayerJumping(CPlayer* player) {};
	virtual void Notify_DisappearFootBoard(CRoad* road) {};
};
