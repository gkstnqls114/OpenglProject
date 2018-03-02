#pragma once

class PlayerObserver;
class CPlayer;

class PlayerSubject
{
public:
	PlayerSubject();
	~PlayerSubject();

	void Add_Observer(PlayerObserver* push);
	void Sub_Observer(PlayerObserver* pop);

	void Notify_PlayerJumping(CPlayer* player);
	void Notify_PlayerWaitCamera(CPlayer* player);
	void Notify_PlayerJumpFinish(CPlayer* player);

private:
	std::list<PlayerObserver*> m_PlayerObserverList;

};

