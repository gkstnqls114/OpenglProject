#include "pch.h"
#include "ObjModel.h"
#include "FootBoard.h"

// ? 왜 여기에다가 정의할수있는거지 잘모르겠어..
//정적멤버변수는 클래스밖에서 초기화(정확히는 아니지만)해야한다.
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

	glColor4f(LIGHTRGB.x, LIGHTRGB.y, LIGHTRGB.z, m_TextureAlpha);
	m_obj->Render();

	if (IsLast) {
		glColor4f(LIGHTRGB.x, LIGHTRGB.y, LIGHTRGB.z, m_LightAlpha);
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
	////단 한 번만 호출
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
	if (IsDisappear) return;

	glPushMatrix();
	glTranslatef(m_Position.x, m_Position.y, m_Position.z);
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

}

void CFootBoard::InitPosition(const CVector3D<> & rhs)
{
	if (rhs.x < 0) {
		m_Side = -1;
	}
	else if (rhs.x > 0) {
		m_Side = 1;
	}
	else {
		m_Side = 0;
	}

	m_Position.x  = rhs.x;
	m_Position.y  = rhs.y;
	m_Position.z  = rhs.z;

}

void CFootBoard::InitPosition(CVector3D<>&& rhs)
{

	if (rhs.x < 0) {
		m_Side = -1;
	}
	else if (rhs.x > 0) {
		m_Side = 1;
	}
	else {
		m_Side = 0;
	}

	m_Position.x = rhs.x;
	m_Position.y = rhs.y;
	m_Position.z = rhs.z;

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
