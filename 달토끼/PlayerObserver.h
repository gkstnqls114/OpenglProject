#pragma once

class CPlayer;
class Observer;

class PlayerObserver
{
	std::list<Observer*> m_List;

public:
	PlayerObserver();
	~PlayerObserver();

	void Add_Observer(Observer* push);
	void Sub_Observer(Observer* pop);

	void Notify_PlayerJumping(CPlayer* player);
	void Notify_PlayerWaitCamera(CPlayer* player);
	void Notify_PlayerJumpFinish(CPlayer* player);
};