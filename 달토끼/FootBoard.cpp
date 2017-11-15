#include "pch.h"
#include "ObjModel.h"
#include "FootBoard.h"

// ? �� ���⿡�ٰ� �����Ҽ��ִ°��� �߸𸣰ھ�..
//������������� Ŭ�����ۿ��� �ʱ�ȭ(��Ȯ���� �ƴ�����)�ؾ��Ѵ�.
bool CFootBoard::isInitModel = false;
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
	std::cout << "FootBoard ������" << std::endl;
}

CFootBoard::~CFootBoard()
{
	std::cout << "FootBoard �Ҹ���" << std::endl;
}

void CFootBoard::InitModel()
{
	////�� �� ���� ȣ��
	if (CFootBoard::isInitModel) return;

	std::cout << "FootBoard �� ����" << std::endl;

	CFootBoard::isInitModel = true;
	CFootBoard::m_obj = new CObjModel;
	CFootBoard::m_obj->LoadObj("box2.obj");
}

void CFootBoard::DeleteModel()
{
	if (CFootBoard::isInitModel) {

		std::cout << "FootBoard �� ����" << std::endl;

		delete[] CFootBoard::m_obj;
	}
}

void CFootBoard::Render()
{
	glPushMatrix();
	//glLoadMatrixf(m_Translate_Matrix);
	glLoadIdentity();
	glMultMatrixf(m_Translate_Matrix);
	glMultMatrixf(m_Scale_Matrix);
	glMultMatrixf(m_Rotate_Matrix);
	glColor3f(m_r, m_g, m_b);
	
	RenderModel();

	glPopMatrix();
}

void CFootBoard::Update()
{
	Disappear();
}

void CFootBoard::Translate(const float & x, const float & y, const float & z)
{
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(x, y, z);
	glMultMatrixf(m_Translate_Matrix);
	glGetFloatv(GL_MODELVIEW_MATRIX, m_Translate_Matrix);
	glPopMatrix();
}
