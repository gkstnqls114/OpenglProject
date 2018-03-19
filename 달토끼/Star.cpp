#include "pch.h"
#include "ItemEffectManager.h"
#include "ObjModel.h"
#include "Star.h"

CObjModel* Star::m_ObjModel { nullptr };

void Star::ItemEffect()
{
	if (m_pItemEffectManager) {
		m_pItemEffectManager->ItemEffect_Star();
	}
}

void Star::Render_Model()
{
	Star::m_ObjModel->Render();
	Render_Sphere();
}

Star::Star()
{
}

Star::~Star()
{
}

void Star::InitModel()
{
	if (Star::m_ObjModel) return;

	Star::m_ObjModel = new CObjModel;
	Star::m_ObjModel->LoadObj(".\\OBJModel\\item_star.obj");
	Star::m_ObjModel->LoadTexture(".\\Texture\\GoalLight.bmp");
}
