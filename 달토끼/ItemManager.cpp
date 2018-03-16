#include "pch.h"

#include "NullItem.h"
#include "Star.h"
#include "Shield.h"
#include "Carrat.h"

#include "ItemManager.h"

ItemManager::ItemManager(const int & num)
{
	m_ItemNumber = num;
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

	m_ItemList = new Item*[m_ItemNumber];
	for (int index = 0; index < m_ItemNumber; ++index) 
	{
		m_ItemList[index] = new Star;
	}
}

void ItemManager::InitItemModel()
{
}

const bool ItemManager::IsOutRange() const noexcept
{

	return false;
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
	for (int index = 0; index < m_ItemNumber; ++index) {
		m_ItemList[index]->Render();
	}
}

void ItemManager::Update()
{ 
	for (int index = 0; index < m_ItemNumber; ++index) {
		m_ItemList[index]->Update();
	}
}

void ItemManager::Set_Pos(const int & boardnum, const CVector3D<> pos)
{
	m_ItemList[boardnum]->Set_Pos(pos);
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

