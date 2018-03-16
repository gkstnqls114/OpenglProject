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
	Star::m_ObjModel->LoadTexture(".\\Texture\\GoalLight.bmp");
}

void Star::Update()
{

}

void Star::Render()
{
	Star::m_ObjModel->Render();
}

void Star::Set_Pos(const CVector3D<>& rhs)
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

