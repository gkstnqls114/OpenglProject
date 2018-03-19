#include "pch.h"
#include "ItemEffectManager.h"
#include "ObjModel.h"
#include "Carrot.h"

CObjModel* Carrot::m_ObjModel { nullptr };

void Carrot::InitModel()
{
	if (Carrot::m_ObjModel) return;
	
	Carrot::m_ObjModel = new CObjModel;
	Carrot::m_ObjModel->LoadObj(".\\OBJModel\\item_carrot.obj");
}
 
void Carrot::ItemEffect()
{
	if (m_pItemEffectManager) {
		m_pItemEffectManager->ItemEffect_Carrat();
	}
}

void Carrot::Render_Model()
{
	Carrot::m_ObjModel->Render();
	Render_Sphere();
}

Carrot::Carrot()
{
}

Carrot::~Carrot()
{
}

