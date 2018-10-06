#include "pch.h"
#include "ObjModel.h"
#include "RotateMatrix.h"
#include "Earth.h"

CObjModel* CEarth::m_Earth = nullptr;

void CEarth::InitModel()
{
	if (m_Earth != nullptr) return;
	m_Earth = new CObjModel;
	m_Earth->LoadObj(".\\OBJModel\\Earth.obj");
	m_Earth->LoadTexture(".\\Texture\\Earth.bmp");
}

void CEarth::DeleteModel()
{
	if (m_Earth == nullptr) return;

	delete m_Earth;
	m_Earth = nullptr;
}

CEarth::CEarth()
{
	InitModel();

	m_Matrix = new RotateMatrix;
}

CEarth::~CEarth()
{
	DeleteModel();
	delete m_Matrix;
}

void CEarth::SetPos(const CVector3D<>& rhs)
{
	m_Position = rhs;
}

void CEarth::SetPos(CVector3D<>&& rhs)
{
	m_Position = rhs;
}

void CEarth::Update()
{
	if (IsGameStart) {
		m_Matrix->Calu_Rotate(6, 0, 1, 0);
		//m_Matrix->Calu_Tranlate(CVector3D<>(0, 5, 0));
		m_Position.y += 5;

		//if (m_Matrix->Get_Tranlate_Y() > 400) {
			//m_pMediator->GameScene();
		//}

		return;
	}
	Float();
	m_Earth->Rotate(1, 0, 1, 0);
}

void CEarth::Render()
{
	if (m_Earth == nullptr)return;

	glColor3f(LIGHTRGB.x, LIGHTRGB.y, LIGHTRGB.z);
	glPushMatrix();
	glTranslatef(m_Position.x, m_Position.y, m_Position.z);
	m_Matrix->Rotate();
	glScalef(m_Scale, m_Scale, m_Scale);
	m_Earth->Render();
	glPopMatrix();
}

void CEarth::Float()
{
	if (!IsFloat) return;

	m_Time += 0.01f;
	if (m_Time >= 1.f) {
		m_Time = 0.f;
		m_BeginY = m_EndY;
		m_EndY = -m_EndY;
	}

	GLdouble MoveY = Interpolation(m_BeginY, m_EndY, m_Time);
	m_Position.y += MoveY;
}

void CEarth::Init_MainScene()
{
	SetPos(CVector3D<>(-100, 0, 0));
	m_Matrix->ResetRotate();
	IsGameStart = false;
	IsFloat = true;
}

void CEarth::GameStart()
{
	IsGameStart = true;
}
