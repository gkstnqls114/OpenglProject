#pragma once

class CPlayer;
class Item;
class FootBoardManager;

class ItemEffectManager
{
	int m_StarPlusLenght{ 5 };
	FootBoardManager* m_pFootboardManager{ nullptr };

	CPlayer * m_pPlayer{ nullptr };

public:
	ItemEffectManager() {}
	ItemEffectManager(FootBoardManager& road, CPlayer& player) : m_pFootboardManager(&road), m_pPlayer(&player) {};
	~ItemEffectManager() {}

	void Set_pRoad(FootBoardManager* road) { m_pFootboardManager = road; }
	void Set_pPlayer(CPlayer* player) { m_pPlayer = player; }

	void ItemEffect_Star();
	void ItemEffect_Carrat();
	void ItemEffect_Shield();

};