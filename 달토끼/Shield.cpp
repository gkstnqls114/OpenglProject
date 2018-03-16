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
}

void Shield::Set_Pos(const CVector3D<>& rhs)
{
	if (rhs.x < 0) {
		m_Side = k_left;
	}
	else if (rhs.x > 0) {
		m_Side = k_right;
	}
	else {
		m_Side = k_front;
	}

	m_Pos = rhs;
}
