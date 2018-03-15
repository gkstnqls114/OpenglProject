#include "pch.h"
#include "ObjModel.h"
#include "Star.h"

CObjModel* Star::m_ObjModel { nullptr };

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
}

void Star::Update()
{

}

void Star::Render()
{
	Star::m_ObjModel->Render();
}
