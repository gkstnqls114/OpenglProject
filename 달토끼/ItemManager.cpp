#include "pch.h"

#include "NullItem.h"
#include "Star.h"
#include "Shield.h"
#include "Carrat.h"

#include "ItemManager.h"

ItemManager::ItemManager()
{

}

ItemManager::ItemManager(const int & num)
{
	m_ItemLength = num;
	ItemManager::initModel();
	Initialize();
}

ItemManager::~ItemManager()
{

}

void ItemManager::initModel()
{
	Star::InitModel();
	Shield::InitModel();
	Carrat::InitModel();
}

void ItemManager::Add_Item(Item* & item)
{

}

void ItemManager::Initialize()
{
	if (m_ItemList) return;

	m_ItemList = new Item*[m_ItemLength];
	for (int index = 0; index < m_ItemLength; ++index) 
	{
		m_ItemList[index] = new Star;
	}
}

void ItemManager::InitItemModel()
{
}

const bool ItemManager::IsOutRange(const int& num) const noexcept
{
	if (num < 0 || num >= m_ItemLength) return true;
	else return false;
}

void ItemManager::Render()
{
	//for (const auto& item : m_ItemList) {
	//	item->Render();
	//}
}

void ItemManager::TestRender()
{
	//all Render
	for (int index = 0; index < m_ItemLength; ++index) {
		m_ItemList[index][0].Render();
	}
}

void ItemManager::Update()
{ 
	for (int index = 0; index < m_ItemLength; ++index) {
		m_ItemList[index][0].Update();
	}
}

void ItemManager::Set_Pos(const int & boardnum, const CVector3D<> pos)
{
	m_ItemList[boardnum][0].Set_Pos(pos);
}


void ItemManager::Change_Star(const int & boardnum)
{
	
}

void ItemManager::Change_Shield(const int & boardnum)
{
}

void ItemManager::Change_Carrat(const int & boardnum)
{
}

