#pragma once

class CPlayer;
class CColleague;

class CPlayerNotification
{
	std::list<CColleague*> m_List;

public:
	CPlayerNotification();
	~CPlayerNotification();

	void Push(CColleague* push);
	void Pop(CColleague* pop);
	void Notify(CPlayer* player);
};

