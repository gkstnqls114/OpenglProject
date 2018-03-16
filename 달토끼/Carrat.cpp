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

Carrat::Carrat(const int & boardnum)
{
	m_BoardPosNum = boardnum;
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
