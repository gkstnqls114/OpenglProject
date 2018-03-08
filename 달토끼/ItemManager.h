#pragma once
#include <vector>

class Item;

class ItemManager
{
	std::vector<Item*> m_ItemList;
	int m_ItemNumber{ 0 };

	static void initModel();
	void Add_Item(Item*&);
	
public:
	ItemManager();
	~ItemManager();

	void Render();
	void Update();
	void Add_Star();
	void Add_Shield();
	void Add_Carrat();
	
};