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
	glLoadIdentity();
	glMultMatrixf(m_Translate_Matrix);
	glMultMatrixf(m_Rotate_Matrix);
	glMultMatrixf(m_Scale_Matrix);
}

void CMatrix::Calu_Tranlate(const CVector3D & rhs)
{
	glPushMatrix();
	glLoadIdentity();
	glTranslated(rhs.x, rhs.y, rhs.z);
	glMultMatrixf(m_Translate_Matrix);
	glGetFloatv(GL_MODELVIEW_MATRIX, m_Translate_Matrix);
	glPopMatrix();
}

void CMatrix::Calu_Tranlate(CVector3D && rhs)
{
	glPushMatrix();
	glLoadIdentity();
	glTranslated(rhs.x, rhs.y, rhs.z);
	glMultMatrixf(m_Translate_Matrix);
	glGetFloatv(GL_MODELVIEW_MATRIX, m_Translate_Matrix);
	glPopMatrix();
}

void CMatrix::Calu_Rotate(const int& degree, const int& x, const int& y, const int& z)
{

	glPushMatrix();
	glLoadIdentity();
	glRotated(degree, x, y, z);
	glMultMatrixf(m_Rotate_Matrix);
	glGetFloatv(GL_MODELVIEW_MATRIX, m_Rotate_Matrix);
	glPopMatrix();
}
