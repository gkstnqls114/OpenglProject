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

void CMatrix::Calu_Rotate(const int& Nowdegree, const int& x, const int& y, const int& z)
{
	glPushMatrix();
	////glLoadIdentity();
	glRotated(Nowdegree, x, y, z);
	glMultMatrixf(m_Rotate_Matrix);
	glGetFloatv(GL_MODELVIEW_MATRIX, m_Rotate_Matrix);
	glPopMatrix();
}

void CMatrix::Calu_Rotate(const float & Nowdegree, const int & x, const int & y, const int & z)
{
	glPushMatrix();
	glRotatef(Nowdegree, x, y, z);
	glMultMatrixf(m_Rotate_Matrix);
	glGetFloatv(GL_MODELVIEW_MATRIX, m_Rotate_Matrix);
	glPopMatrix();
}

void CMatrix::Set_Rotate(const int & Nowdegree, const int & x, const int & y, const int & z)
{
	glPushMatrix();
	
	glRotated(Nowdegree, x, y, z);
	glMultMatrixf(m_Rotate_Matrix);
	glGetFloatv(GL_MODELVIEW_MATRIX, m_Rotate_Matrix);
	glPopMatrix();
}

void CMatrix::Set_Rotate(const float & Nowdegree, const int & x, const int & y, const int & z)
{
	glPushMatrix();
	ResetRotate();
	glRotatef(Nowdegree, x, y, z);
	glMultMatrixf(m_Rotate_Matrix);
	glGetFloatv(GL_MODELVIEW_MATRIX, m_Rotate_Matrix);
	glPopMatrix();
}

void CMatrix::ResetTranslate()
{
	for (int index = 0; index < 16; ++index) {
		m_Translate_Matrix[index] = 0;
	}

	m_Translate_Matrix[0] = 1;
	m_Translate_Matrix[5] = 1;
	m_Translate_Matrix[10] = 1;
	m_Translate_Matrix[15] = 1;
}

void CMatrix::ResetRotate()
{
	for (int index = 0; index < 16; ++index) {
		m_Rotate_Matrix[index] = 0;
	}

	m_Rotate_Matrix[0] = 1;
	m_Rotate_Matrix[5] = 1;
	m_Rotate_Matrix[10] = 1;
	m_Rotate_Matrix[15] = 1;
}

void CMatrix::ResetScale()
{
	for (int index = 0; index < 16; ++index) {
		m_Scale_Matrix[index] = 0;
	}

	m_Scale_Matrix[0] = 1;
	m_Scale_Matrix[5] = 1;
	m_Scale_Matrix[10] = 1;
	m_Scale_Matrix[15] = 1;
}

void CMatrix::Calu_Scale(const float & NowSize)
{
	glPushMatrix();

	glLoadIdentity();
	glMultMatrixf(m_Scale_Matrix);

	//ResetRotate();

	glScaled(NowSize, NowSize, NowSize);
	glMultMatrixf(m_Scale_Matrix);
	glGetFloatv(GL_MODELVIEW_MATRIX, m_Scale_Matrix);
	glPopMatrix();
}

void CMatrix::Calu_Scale(const float & x, const float & y, const float & z)
{

	glPushMatrix();
	glScaled(x, y, z);
	glMultMatrixf(m_Scale_Matrix);
	glGetFloatv(GL_MODELVIEW_MATRIX, m_Scale_Matrix);
	glPopMatrix();
}

void CMatrix::Set_Scale(const float & NowSize)
{
	m_Scale_Matrix[0] = NowSize;
	m_Scale_Matrix[5] = NowSize;
	m_Scale_Matrix[10] = NowSize;
}

void CMatrix::Set_Scale(const float & x, const float & y, const float & z)
{
	m_Scale_Matrix[0] = x;
	m_Scale_Matrix[5] = y;
	m_Scale_Matrix[10] = z;
}
