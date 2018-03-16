#include "pch.h"
#include "ObjModel.h"
#include "FootBoard.h"

// ? �� ���⿡�ٰ� �����Ҽ��ִ°��� �߸𸣰ھ�..
//������������� Ŭ�����ۿ��� �ʱ�ȭ(��Ȯ���� �ƴ�����)�ؾ��Ѵ�.
CObjModel* CFootBoard::m_obj = nullptr;
CObjModel* CFootBoard::m_Light_obj = nullptr;

void CFootBoard::Disappear()
{
	if (m_TextureAlpha <= 0) {
		IsDisappear = true;
		return;
	}

	m_TextureAlpha -= 0.01f;
}

void CFootBoard::RenderModel()
{
	glColor4f(LIGHTRGB.x, LIGHTRGB.y, LIGHTRGB.z, m_TextureAlpha);
	m_obj->Render();

	if (IsLast) {
		///////////////////////////Test
		//glColor4f(LIGHTRGB.x, LIGHTRGB.y, LIGHTRGB.z, m_LightAlpha);
		//m_Light_obj->Render();
		///////////////////////////Test
	}
}

CFootBoard::CFootBoard()
{
	m_TextureAlpha = 1.f;
	DisappearTime = 0.f;
	IsDisappear = false;
}

CFootBoard::~CFootBoard()
{

}

void CFootBoard::InitModel()
{
	////�� �� ���� ȣ��
	if (CFootBoard::m_obj != nullptr) return;

	CFootBoard::m_obj = new CObjModel;
	CFootBoard::m_obj->LoadObj(".\\OBJModel\\FootBoard.obj");
	CFootBoard::m_obj->LoadTexture(".\\Texture\\FootBoard.bmp");
	//CFootBoard::m_obj->LoadTexture("Goal.bmp");

	CFootBoard::m_Light_obj = new CObjModel;
	CFootBoard::m_Light_obj->LoadObj("GoalLight.obj");
	CFootBoard::m_Light_obj->LoadTexture("GoalLight.bmp");
}

void CFootBoard::DeleteModel()
{
	if (CFootBoard::m_obj == nullptr) return;

	delete[] CFootBoard::m_obj;
}

void CFootBoard::Render()
{
	if (IsDisappear) return;

	glPushMatrix();
	glTranslatef(m_Pos.x, m_Pos.y, m_Pos.z);
	glMultMatrixf(m_Rotate_Matrix);
	glMultMatrixf(m_Scale_Matrix);
	
	RenderModel();

	glPopMatrix();
}

void CFootBoard::Update()
{
	if (IsDisappear) return;
	Disappear();
}

void CFootBoard::InitPosition(const int & x, const int & y, const int & z)
{
	if (x < 0) {
		m_Side = -1;
	}
	else if (x > 0) {
		m_Side = 1;
	}
	else {
		m_Side = 0;
	}

}

void CFootBoard::InitPosition(const CVector3D<> & rhs)
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

void CFootBoard::InitPosition(CVector3D<>&& rhs)
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

void CFootBoard::HasLight()
{
	IsLast = true;
	IsLightDisappear = false;
}

void CFootBoard::IsNotLight()
{
	IsLightDisappear = true;
}

void CFootBoard::LightDisappear()
{
	if (IsLightDisappear) {
		//m_LightAlpha -= 0.01f;
	}
}
