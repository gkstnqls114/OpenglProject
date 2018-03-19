#include "pch.h"
#include "ItemEffectManager.h"
#include "ObjModel.h"
#include "Shield.h"

CObjModel* Shield::m_ObjModel{ nullptr };

void Shield::ItemEffect()
{
	if (m_pItemEffectManager) {
		m_pItemEffectManager->ItemEffect_Shield();
	}
}

void Shield::Render_Model()
{
	Shield::m_ObjModel->Render();
	Render_Sphere();
}

Shield::Shield()
{
}


Shield::~Shield()
{
}

void Shield::InitModel()
{
	if (m_ObjModel) return;

	Shield::m_ObjModel = new CObjModel;
	Shield::m_ObjModel->LoadObj(".\\OBJModel\\item_shield.obj");
}


