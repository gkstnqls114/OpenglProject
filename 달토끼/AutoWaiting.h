#pragma once
#include "PlayerState.h"

class CAutoWaiting :
	public CPlayerState
{
	bool IsUsing{ false };
	int m_JumpNum{ 0 };
	const int MaxJum{ 10 };

public:
	CAutoWaiting();
	virtual ~CAutoWaiting();

	virtual void Initialize() override;
	virtual void Update(CPlayer& player) override;
	virtual void SpecialKeys(CPlayer& player, const int& key) override;

	void Reset();
	void Add_JumpNum() { m_JumpNum += 1; std::cout << m_JumpNum << std::endl; }
	const int Get_JumpNume() const { return m_JumpNum; }
	const bool Get_IsUsing() const { return IsUsing; }
};