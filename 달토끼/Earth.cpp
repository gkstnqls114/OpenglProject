#include "pch.h"
#include "ObjModel.h"
#include "Matrix.h"
#include "Earth.h"

CObjModel* CEarth::m_Earth = nullptr;

void CEarth::InitModel()
{
	if (m_Earth != nullptr) return;
	m_Earth = new CObjModel;
	m_Earth->LoadObj("sample_earth.obj");
}

void CEarth::DeleteModel()
{
	if (m_Earth == nullptr) return;

	delete m_Earth;
	m_Earth = nullptr;
}

CEarth::CEarth(const CVector3D& Pos)
{
	InitModel();

	m_Matrix = new CMatrix;
	m_Matrix->Calu_Tranlate(Pos);
	m_Matrix->Calu_Scale(0.7);
}


CEarth::~CEarth()
{
	DeleteModel();
	delete m_Matrix;
}

void CEarth::Update()
{
	m_Earth->Rotate(1, 0, 1, 0);
}

void CEarth::Render()
{
	if (m_Earth == nullptr)return;

	glPushMatrix();
	m_Matrix->MultiMatrix();
	m_Earth->Render();
	glPopMatrix();
}
