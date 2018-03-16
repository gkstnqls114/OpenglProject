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
 
void Carrat::ModelRender()
{
	Carrat::m_ObjModel->Render();
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

