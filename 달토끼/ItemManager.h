#pragma once

class Item;
class ItemEffectManager;
class FootBoardManager;

class ItemManager
{
	Item** m_ItemList{ nullptr };
	ItemEffectManager* m_pItemEffectManager;
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
	void Set_ItemEffectManager(ItemEffectManager& manager) { m_pItemEffectManager = &manager; };
	void Render(FootBoardManager* footboardManager);
	void TestRender();
	void Update();

	void Set_Pos(const int& boardnum, const CVector3D<>& pos);
	
	Item& Get_Item(const int& num) const;

	void Change_Star(const int& boardnum);
	void Change_Shield(const int& boardnum);
	void Change_Carrot(const int& boardnum);
	

	void TestPosPrint(const int& num) const;
};