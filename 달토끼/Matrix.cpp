#include "pch.h"
#include "Vector3D.h"
#include "Matrix.h"


CMatrix::CMatrix()
{
}


CMatrix::~CMatrix()
{
}

void CMatrix::MultiMatrix()
{
	//이 함수에 앞 뒤에 push/pop 해야합니다.
	//glLoadIdentity();
	glMultMatrixf(m_Translate_Matrix);
	glMultMatrixf(m_Rotate_Matrix);
	glMultMatrixf(m_Scale_Matrix);
}

void CMatrix::Calu_Tranlate(const CVector3D<> & rhs)
{
	glPushMatrix();
	//glLoadIdentity();
	glTranslated(rhs[0], rhs[1], rhs[2]);
	glMultMatrixf(m_Translate_Matrix);
	glGetFloatv(GL_MODELVIEW_MATRIX, m_Translate_Matrix);
	glPopMatrix();
}

void CMatrix::Calu_Tranlate(CVector3D<> && rhs)
{
	glPushMatrix();
	//glLoadIdentity();
	glTranslated(rhs[0], rhs[1], rhs[2]);
	glMultMatrixf(m_Translate_Matrix);
	glGetFloatv(GL_MODELVIEW_MATRIX, m_Translate_Matrix);
	glPopMatrix();
}

void CMatrix::Calu_Rotate(const int& degree, const int& x, const int& y, const int& z)
{
	glPushMatrix();
	////glLoadIdentity();
	glRotated(degree, x, y, z);
	glMultMatrixf(m_Rotate_Matrix);
	glGetFloatv(GL_MODELVIEW_MATRIX, m_Rotate_Matrix);
	glPopMatrix();
}

void CMatrix::Calu_Rotate(const float & degree, const int & x, const int & y, const int & z)
{
	glPushMatrix();
	//glLoadIdentity();
	glRotatef(degree, x, y, z);
	glMultMatrixf(m_Rotate_Matrix);
	glGetFloatv(GL_MODELVIEW_MATRIX, m_Rotate_Matrix);
	glPopMatrix();
}

void CMatrix::Reset_Rotate()
{
	for (int index = 0; index < 16; ++index) {
		m_Rotate_Matrix[index] = 0;
	}

	m_Rotate_Matrix[0] = 1;
	m_Rotate_Matrix[5] = 1;
	m_Rotate_Matrix[10] = 1;
	m_Rotate_Matrix[15] = 1;
}

void CMatrix::Calu_Scale(const float & size)
{
	glPushMatrix();
	//glLoadIdentity();
	glScaled(size, size, size);
	glMultMatrixf(m_Scale_Matrix);
	glGetFloatv(GL_MODELVIEW_MATRIX, m_Scale_Matrix);
	glPopMatrix();
}

void CMatrix::Calu_Scale(const float & x, const float & y, const float & z)
{

	glPushMatrix();
	//glLoadIdentity();
	glScaled(x, y, z);
	glMultMatrixf(m_Scale_Matrix);
	glGetFloatv(GL_MODELVIEW_MATRIX, m_Scale_Matrix);
	glPopMatrix();
}

void CMatrix::Set_Scale(const float & size)
{
	m_Scale_Matrix[0] = size;
	m_Scale_Matrix[5] = size;
	m_Scale_Matrix[10] = size;
}

void CMatrix::Set_Scale(const float & x, const float & y, const float & z)
{
	m_Scale_Matrix[0] = x;
	m_Scale_Matrix[5] = y;
	m_Scale_Matrix[10] = z;
}
