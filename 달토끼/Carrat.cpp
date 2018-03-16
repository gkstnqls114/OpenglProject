#include "pch.h"
#include "ObjModel.h"
#include "Carrat.h"

CObjModel* Carrat::m_ObjModel { nullptr };

void Carrat::InitModel()
{
	if (Carrat::m_ObjModel) return;
	
	Carrat::m_ObjModel = new CObjModel;
	Carrat::m_ObjModel->LoadObj(".\\OBJModel\\item_carrat.obj");
}
 
Carrat::Carrat()
{
}

Carrat::~Carrat()
{
}

void Carrat::Update()
{

}

void Carrat::Render()
{
	Carrat::m_ObjModel->Render();
}

void Carrat::Set_Pos(const CVector3D<>& rhs)
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
