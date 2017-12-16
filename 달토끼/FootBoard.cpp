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

	m_TextureAlpha -= 0.03f;
}

void CFootBoard::RenderModel()
{
	if (IsDisappear) return;

	glColor4f(LIGHTRGB[0], LIGHTRGB[1], LIGHTRGB[2], m_TextureAlpha);
	m_obj->Render();

	if (IsLast) {
		glColor4f(LIGHTRGB[0], LIGHTRGB[1], LIGHTRGB[2], m_LightAlpha);
		m_Light_obj->Render();
	}
}

CFootBoard::CFootBoard()
{


}

CFootBoard::~CFootBoard()
{

}

void CFootBoard::InitModel()
{
	////�� �� ���� ȣ��
	if (CFootBoard::m_obj != nullptr) return;

	CFootBoard::m_obj = new CObjModel;
	CFootBoard::m_obj->LoadObj("FootBoard.obj");
	CFootBoard::m_obj->LoadTexture("FootBoard.bmp");
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
	glPushMatrix();
	glMultMatrixf(m_Translate_Matrix);
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

void CFootBoard::Init_GameScene()
{
	m_TextureAlpha = 1.f;
	DisappearTime = 0.f;
	IsDisappear = false;
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

	glPushMatrix();
	glLoadIdentity();
	glTranslatef(x, y, z);
	glMultMatrixf(m_Translate_Matrix);
	glGetFloatv(GL_MODELVIEW_MATRIX, m_Translate_Matrix);
	glPopMatrix();
}

void CFootBoard::InitPosition(const CVector3D<> & rhs)
{
	if (rhs[0] < 0) {
		m_Side = -1;
	}
	else if (rhs[0] > 0) {
		m_Side = 1;
	}
	else {
		m_Side = 0;
	}

	m_Position[0] = rhs[0];
	m_Position[1] = rhs[1];
	m_Position[2] = rhs[2];
	m_Position[3] = rhs[3];

	glPushMatrix();
	glLoadIdentity();
	glTranslatef(m_Position[0], m_Position[1], m_Position[2]);
	glMultMatrixf(m_Translate_Matrix);
	glGetFloatv(GL_MODELVIEW_MATRIX, m_Translate_Matrix);
	glPopMatrix();
}

void CFootBoard::InitPosition(CVector3D<>&& rhs)
{

	if (rhs[0] < 0) {
		m_Side = -1;
	}
	else if (rhs[0] > 0) {
		m_Side = 1;
	}
	else {
		m_Side = 0;
	}

	m_Position[0] = rhs[0];
	m_Position[1] = rhs[1];
	m_Position[2] = rhs[2];
	m_Position[3] = rhs[3];

	glPushMatrix();
	glLoadIdentity();
	glTranslatef(m_Position[0], m_Position[1], m_Position[2]);
	glMultMatrixf(m_Translate_Matrix);
	glGetFloatv(GL_MODELVIEW_MATRIX, m_Translate_Matrix);
	glPopMatrix();
}

void CFootBoard::IsLight()
{
	IsLast = true;
	m_LightAlpha = 0.5f;
	IsLightDisappear = false;
}

void CFootBoard::IsNotLight()
{
	IsLightDisappear = true;
}

void CFootBoard::LightDisappear()
{
	if (IsLightDisappear) {
		m_LightAlpha -= 0.01f;
	}
}
