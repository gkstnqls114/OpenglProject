#include "pch.h"
#include "ObjModel.h"
#include "Shield.h"

CObjModel* Shield::m_ObjModel{ nullptr };

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

void Shield::Update()
{
}

void Shield::Render()
{
	Shield::m_ObjModel->Render();
}
