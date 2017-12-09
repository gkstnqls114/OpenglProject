#include "pch.h"
#include "ObjModel.h"
#include "Mediator.h"
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

CEarth::CEarth(CMediator*& mediator)
{
	InitModel();
	m_pMediator = mediator;
	m_Matrix = new CMatrix;

	Init_MainScene();
}

CEarth::~CEarth()
{
	DeleteModel();
	delete m_Matrix;
}

void CEarth::SetPos(const CVector3D<>& rhs)
{
	m_Matrix->Set_Translate(rhs);
}

void CEarth::Update()
{
	if (IsGameStart) {
		m_Matrix->Calu_Rotate(6, 0, 1, 0);
		m_Matrix->Calu_Tranlate(CVector3D<>(0, 5, 0));

		if (m_Matrix->Get_Tranlate_Y() > 400) {
			m_pMediator->GameScene();
		}

		return;
	}
	Float();
	m_Earth->Rotate(1, 0, 1, 0);
}

void CEarth::Render()
{
	if (m_Earth == nullptr)return;

	glColor3f(LIGHTRGB[0], LIGHTRGB[2], LIGHTRGB[3]);
	glPushMatrix();
	m_Matrix->MultiMatrix();
	m_Earth->Render();
	glPopMatrix();
}

void CEarth::Float()
{
	m_Time += 0.01f;
	if (m_Time >= 1.f) {
		m_Time = 0.f;
		m_BeginY = m_EndY;
		m_EndY = -m_EndY;
	}

	GLdouble MoveY = Interpolation(m_BeginY, m_EndY, m_Time);
	m_Matrix->Calu_Tranlate(CVector3D<>(0, MoveY, 0));
}

void CEarth::Init_MainScene()
{
	SetPos(CVector3D<>(-100, 0, 0));
	m_Matrix->ResetRotate();
	IsGameStart = false;
}

void CEarth::GameStart()
{
	IsGameStart = true;
}
