#include "pch.h"
#include "Colleague.h"
#include "PlayerNotification.h"


CPlayerNotification::CPlayerNotification()
{
}


CPlayerNotification::~CPlayerNotification()
{
}

void CPlayerNotification::Push(CColleague * push)
{
	m_List.push_back(push);
}

void CPlayerNotification::Pop(CColleague * pop)
{
	//일단 공백
}

void CPlayerNotification::Notify(CPlayer * player)
{
	for (auto d : m_List) {
		d->Notify(player);
	}
}
