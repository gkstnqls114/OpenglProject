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
	void Notify(CPlayer* player);
};