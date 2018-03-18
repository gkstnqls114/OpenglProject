#include "pch.h"
#include "RotateMatrix.h"

RotateMatrix::RotateMatrix()
{
}


RotateMatrix::~RotateMatrix()
{
}

//이 함수에 앞 뒤에 push/pop 해야합니다.
void RotateMatrix::Rotate()
{
	glMultMatrixf(m_Rotate_Matrix);
}

void RotateMatrix::Calu_Rotate(const int& Nowdegree, const int& x, const int& y, const int& z)
{
	glPushMatrix();
	////glLoadIdentity();
	glRotated(Nowdegree, x, y, z);
	glMultMatrixf(m_Rotate_Matrix);
	glGetFloatv(GL_MODELVIEW_MATRIX, m_Rotate_Matrix);
	glPopMatrix();
}

void RotateMatrix::Calu_Rotate(const float & Nowdegree, const int & x, const int & y, const int & z)
{
	glPushMatrix();
	glRotatef(Nowdegree, x, y, z);
	glMultMatrixf(m_Rotate_Matrix);
	glGetFloatv(GL_MODELVIEW_MATRIX, m_Rotate_Matrix);
	glPopMatrix();
}

void RotateMatrix::Set_Rotate(const int & Nowdegree, const int & x, const int & y, const int & z)
{
	glPushMatrix();
	ResetRotate();
	glRotated(Nowdegree, x, y, z);
	glMultMatrixf(m_Rotate_Matrix);
	glGetFloatv(GL_MODELVIEW_MATRIX, m_Rotate_Matrix);
	glPopMatrix();
}

void RotateMatrix::Set_Rotate(const float & Nowdegree, const int & x, const int & y, const int & z)
{
	glPushMatrix();
	ResetRotate();
	glRotatef(Nowdegree, x, y, z);
	glMultMatrixf(m_Rotate_Matrix);
	glGetFloatv(GL_MODELVIEW_MATRIX, m_Rotate_Matrix);
	glPopMatrix();
}

void RotateMatrix::ResetRotate()
{
	for (int index = 0; index < 16; ++index) {
		m_Rotate_Matrix[index] = 0;
	}

	m_Rotate_Matrix[0] = 1;
	m_Rotate_Matrix[5] = 1;
	m_Rotate_Matrix[10] = 1;
	m_Rotate_Matrix[15] = 1;
}
