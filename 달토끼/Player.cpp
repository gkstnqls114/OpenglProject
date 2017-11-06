#include "pch.h"
#include "ObjModel.h"
#include "Player.h"


CPlayer::CPlayer()
{
	std::cout << "플레이어 생성" << std::endl;
	m_rabit = new CObjModel;
	m_rabit->Initialize("TestObject.obj");
}


CPlayer::~CPlayer()
{
	if (m_rabit != nullptr) {
		delete m_rabit;
	}
}

void CPlayer::Keyboard(const unsigned char & key, const int & x, const int & y)
{
	int degree = 10;

	if (key == 'a') {
		glPushMatrix();
			glLoadIdentity();
			glRotated(degree, 0, 1, 0);
			glMultMatrixf(m_Rotate_Matrix);
			glGetFloatv(GL_MODELVIEW_MATRIX, m_Rotate_Matrix);
		glPopMatrix();
	}

	if (key == 'd') {
		glPushMatrix();
			glLoadIdentity();
			glRotated(-degree, 0, 1, 0);
			glMultMatrixf(m_Rotate_Matrix);
			glGetFloatv(GL_MODELVIEW_MATRIX, m_Rotate_Matrix);
		glPopMatrix();
	}

	if (key == 'w') {
		glPushMatrix();
		glLoadIdentity();
		glRotated(degree, 1, 0, 0);
		glMultMatrixf(m_Rotate_Matrix);
		glGetFloatv(GL_MODELVIEW_MATRIX, m_Rotate_Matrix);
		glPopMatrix();
	}

	if (key == 's') {
		glPushMatrix();
		glLoadIdentity();
		glRotated(-degree, 1, 0, 0);
		glMultMatrixf(m_Rotate_Matrix);
		glGetFloatv(GL_MODELVIEW_MATRIX, m_Rotate_Matrix);
		glPopMatrix();

	}

	//JUMP
	if (key == GLUT_KEY_UP) {
		IsJump = true;
	}
}

void CPlayer::Update()
{
	Jump();

}

void CPlayer::Render()
{
	glPushMatrix();
		//glLoadMatrixf(m_Translate_Matrix);
		glLoadIdentity();
		glMultMatrixf(m_Translate_Matrix);
		glMultMatrixf(m_Scale_Matrix);
		glMultMatrixf(m_Rotate_Matrix);
		glColor3f(0.f, 0.f, 0.f);

	if (m_rabit != nullptr) {
		m_rabit->Render();
	}
	glPopMatrix();

}

void CPlayer::Jump()
{
	if (!IsJump) return;

	JumpTime += 1;

}
