#pragma once
#include <vector>

class Item;

class ItemManager
{
	Item** m_ItemList{ nullptr };
	int m_ItemLength{ 0 };

	
private:
	static void initModel();
	void Add_Item(Item*&);
	const bool IsOutRange(const int& num) const noexcept;

public:
	ItemManager();
	ItemManager(const int& num);
	~ItemManager();

	void Initialize(const int& num);
	void Render();
	void TestRender();
	void Update();
	void Set_Pos(const int& boardnum, const CVector3D<> pos);
	
	void Change_Star(const int& boardnum);
	void Change_Shield(const int& boardnum);
	void Change_Carrat(const int& boardnum);
	
};