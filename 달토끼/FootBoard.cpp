#include "pch.h"
#include "ObjModel.h"
#include "FootBoard.h"

// ? �� ���⿡�ٰ� �����Ҽ��ִ°��� �߸𸣰ھ�..
//������������� Ŭ�����ۿ��� �ʱ�ȭ(��Ȯ���� �ƴ�����)�ؾ��Ѵ�.
CObjModel* CFootBoard::m_obj = nullptr;

void CFootBoard::Disappear()
{
	if (m_a <= 0) {
		IsDisappear = true;
		return;
	}

	m_a -= 0.03f;
}

void CFootBoard::RenderModel()
{
	if (IsDisappear) return;

	m_obj->Render();
}

CFootBoard::CFootBoard()
{
	std::cout << "FootBoard ������" << std::endl;
}

CFootBoard::~CFootBoard()
{
	std::cout << "FootBoard �Ҹ���" << std::endl;
}

void CFootBoard::InitModel()
{
	////�� �� ���� ȣ��
	if (CFootBoard::m_obj != nullptr) return;

	std::cout << "FootBoard �� ����" << std::endl;

	CFootBoard::m_obj = new CObjModel;
	CFootBoard::m_obj->LoadObj("FootBoard.obj");
	CFootBoard::m_obj->LoadTexture("FootBoard.bmp");
}

void CFootBoard::DeleteModel()
{
	if (CFootBoard::m_obj == nullptr) return;
	std::cout << "FootBoard �� ����" << std::endl;

	delete[] CFootBoard::m_obj;

}

void CFootBoard::Render()
{
	glEnable(GL_BLEND);
	glPushMatrix();
	//glLoadMatrixf(m_Translate_Matrix);
	glLoadIdentity();
	glMultMatrixf(m_Translate_Matrix);
	glMultMatrixf(m_Rotate_Matrix);
	glMultMatrixf(m_Scale_Matrix);
	glColor4f(m_r, m_g, m_b, m_a);
	
	RenderModel();

	glPopMatrix();
}

void CFootBoard::Update()
{
	if (isDisappear) return;
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
