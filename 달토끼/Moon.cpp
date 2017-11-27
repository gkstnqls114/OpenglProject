#include "pch.h"
#include "ObjModel.h"
#include "Matrix.h"
#include "Moon.h"

CObjModel* CMoon::m_Moon = nullptr;

void CMoon::InitModel()
{
	if (m_Moon != nullptr) return;
	m_Moon = new CObjModel;
	m_Moon->LoadObj("sample_moon.obj");
}

void CMoon::DeleteModel()
{
	if (m_Moon == nullptr) return;

	delete m_Moon;
	m_Moon = nullptr;
}

CMoon::CMoon(const CVector3D& Pos)
{
	InitModel();

	m_Matrix = new CMatrix;
	m_Matrix->Calu_Tranlate(Pos);
	m_Matrix->Calu_Scale(0.7);
}


CMoon::~CMoon()
{
	DeleteModel();
	delete m_Matrix;
}

void CMoon::Update()
{
	m_Moon->Rotate(1, 0, 1, 0);
}

void CMoon::Render()
{
	if (m_Moon == nullptr) return;

	glPushMatrix();
	m_Matrix->MultiMatrix();
	m_Moon->Render();
	glPopMatrix();
}
