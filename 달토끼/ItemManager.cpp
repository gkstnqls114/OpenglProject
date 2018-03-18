#include "pch.h"
#include"Collision.h"

#include "NullItem.h"
#include "Star.h"
#include "Shield.h"
#include "Carrat.h"

#include "ItemManager.h"

ItemManager::ItemManager()
{
	ItemManager::initModel();
}

ItemManager::ItemManager(const int & num)
{
	ItemManager::initModel();
	m_ItemLength = num;
	Initialize(num);
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

void ItemManager::Initialize(const int& num)
{
	if (m_ItemList) 
	{
		for (int index = 0; index < num; ++index)
		{
			delete[] m_ItemList[index];
		}
		delete[] m_ItemList;
	}

	m_ItemLength = num;
	m_ItemList = new Item*[num];
	for (int index = 0; index < num; ++index)
	{
		m_ItemList[index] = new Star;
	}
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

void ItemManager::Set_Pos(const int & boardnum, const CVector3D<>& rhs)
{
	if (IsOutRange(boardnum)) return;

	m_ItemList[boardnum][0].Set_Pos(rhs);
}

Item & ItemManager::Get_Item(const int & num) const
{ 
	return m_ItemList[num][0];
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

void ItemManager::TestPosPrint(const int & num) const
{
	CVector3D<> pos = m_ItemList[num][0].Get_Pos();
	std::cout << pos.x << " , " << pos.y << " , " << pos.z << std::endl;
}

