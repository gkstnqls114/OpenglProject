#include "pch.h"
#include "ObjModel.h"
#include "Carrat.h"
CObjModel* Carrat::m_Carrat = nullptr;

void Carrat::InitModel()
{
	if (Carrat::m_Carrat) return;
	
	Carrat::m_Carrat = new CObjModel;
	Carrat::m_Carrat->LoadObj(".\\OBJModel\\item_carrot.obj");
	//텍스쳐 추가
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
	Carrat::m_Carrat->Render();
}
