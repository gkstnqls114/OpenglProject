#pragma once

class Road;
class CPlayer;
class Item;

class ItemEffectManager
{
	Road* m_pRoad{ nullptr };
	CPlayer * m_pPlayer{ nullptr };

public:
	ItemEffectManager() {}
	ItemEffectManager(const Road&, const CPlayer&);
	~ItemEffectManager() {}

	void ItemEffect_Star(const Item& item);
	void ItemEffect_Carrat(const Item& item);
	void ItemEffect_Shield(const Item& item);

};