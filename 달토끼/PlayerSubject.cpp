#include "pch.h"
#include "PlayerObserver.h"
#include "PlayerSubject.h"


PlayerSubject::PlayerSubject()
{
}


PlayerSubject::~PlayerSubject()
{
}

void PlayerSubject::Add_Observer(PlayerObserver * push)
{
	m_PlayerObserverList.push_back(push);
}

void PlayerSubject::Sub_Observer(PlayerObserver * pop)
{
}

void PlayerSubject::Notify_PlayerJumping(CPlayer * player)
{
	for (auto d : m_PlayerObserverList) {
		d->Receive_PlayerJumping(player);
	}
}

void PlayerSubject::Notify_PlayerWaitCamera(CPlayer * player)
{
	for (auto d : m_PlayerObserverList) {
		d->Receive_PlayerWaitCamera(player);
	}
}

void PlayerSubject::Notify_PlayerJumpFinish(CPlayer * player)
{
	for (auto d : m_PlayerObserverList) {
		d->Receive_PlayerJumpFinish(player);
	}
}

void PlayerSubject::Nofity_PlayerAutoJumping(CPlayer * player)
{
	for (auto d : m_PlayerObserverList) {
		d->Receive_PlayerAutoWaiting(player);
	}
}
