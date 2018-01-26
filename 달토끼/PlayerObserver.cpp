#include "pch.h"
#include "Observer.h"
#include "PlayerObserver.h"


PlayerObserver::PlayerObserver()
{
}


PlayerObserver::~PlayerObserver()
{
}

void PlayerObserver::Add_Observer(Observer * push)
{
	m_List.push_back(push);
}

void PlayerObserver::Sub_Observer(Observer * pop)
{
	//일단 공백
}

void PlayerObserver::Notify(CPlayer * player)
{
	for (auto d : m_List) {
		d->Notify(player);
	}
}
