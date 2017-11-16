#include "pch.h"
#include "ObjModel.h"
#include "FootBoard.h"

// ? 왜 여기에다가 정의할수있는거지 잘모르겠어..
//정적멤버변수는 클래스밖에서 초기화(정확히는 아니지만)해야한다.
CObjModel* CFootBoard::m_obj = nullptr;

void CFootBoard::Disappear()
{

	
}

void CFootBoard::RenderModel()
{
	m_obj->Render();
}

CFootBoard::CFootBoard()
{
	std::cout << "FootBoard 생성자" << std::endl;
}

CFootBoard::~CFootBoard()
{
	std::cout << "FootBoard 소멸자" << std::endl;
}

void CFootBoard::InitModel()
{
	////단 한 번만 호출
	if (CFootBoard::m_obj != nullptr) return;

	std::cout << "FootBoard 모델 생성" << std::endl;

	CFootBoard::m_obj = new CObjModel;
	CFootBoard::m_obj->LoadObj("box2.obj");
}

void CFootBoard::DeleteModel()
{
	if (CFootBoard::m_obj == nullptr) return;
	std::cout << "FootBoard 모델 삭제" << std::endl;

	delete[] CFootBoard::m_obj;

}

void CFootBoard::Render()
{
	glPushMatrix();
	//glLoadMatrixf(m_Translate_Matrix);
	glLoadIdentity();
	glMultMatrixf(m_Translate_Matrix);
	glMultMatrixf(m_Rotate_Matrix);
	glMultMatrixf(m_Scale_Matrix);
	glColor3f(m_r, m_g, m_b);
	
	RenderModel();

	glPopMatrix();
}

void CFootBoard::Update()
{
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

	glPushMatrix();
	glLoadIdentity();
	glTranslatef(x, y, z);
	glMultMatrixf(m_Translate_Matrix);
	glGetFloatv(GL_MODELVIEW_MATRIX, m_Translate_Matrix);
	glPopMatrix();
}
