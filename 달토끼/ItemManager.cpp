#include "pch.h"
#include "Star.h"
#include "Shield.h"
#include "Carrat.h"

#include "ItemManager.h"

ItemManager::ItemManager()
{
	ItemManager::initModel();
	//�ϴ� �⺻���� ��
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
	m_ItemList.push_back(item);
	m_ItemNumber += 1;
}

void ItemManager::Render()
{
	for (const auto& item : m_ItemList) {
		item->Render();
	}
}

void ItemManager::Update()
{
	for (const auto& item : m_ItemList) {
		item->Update();
	}
}
