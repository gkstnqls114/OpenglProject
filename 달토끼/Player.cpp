#include "pch.h"
#include "ObjModel.h"
#include "Player.h"


CPlayer::CPlayer()
{
	std::cout << "플레이어 생성" << std::endl;
	m_rabit = new CObjModel;
	m_rabit->Initialize("rabbit.obj");
	
	glPushMatrix();
		glLoadIdentity();
		glRotated(180, 0, 1, 0);
		glMultMatrixf(m_Rotate_Matrix);
		glGetFloatv(GL_MODELVIEW_MATRIX, m_Rotate_Matrix);
	glPopMatrix();
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

	
}

void CPlayer::SpecialKeys(const int & key, const int & x, const int & y)
{
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
	if (!IsJump) {
		m_vector_x = 0;
		m_vector_y = 0;
		m_vector_z = 0;
		return;
	}

	JumpTime += 1.f;


	float radian = m_jump_degree * 3.14 / 180;
	m_vector_z = -m_power * cos(radian) * JumpTime;
	m_vector_y = m_power * sin(radian) * JumpTime
		- m_gravitation_acceleration * JumpTime * JumpTime / 2;
	float lenght = sqrt(m_vector_x * m_vector_x + m_vector_y * m_vector_y + m_vector_z * m_vector_z);

	if (lenght != 0) {
		m_vector_x /= lenght;
		m_vector_y /= lenght;
		m_vector_z /= lenght;


		m_vector_x *= m_power;
		m_vector_y *= m_power;
		m_vector_z *= m_power;
	}

	glPushMatrix();
		glLoadIdentity();
		glTranslated(m_vector_x, m_vector_y, m_vector_z);
		glMultMatrixf(m_Translate_Matrix);
		glGetFloatv(GL_MODELVIEW_MATRIX, m_Translate_Matrix);
	glPopMatrix();

	if(m_Translate_Matrix[13] <= m_floor){
		//std::cout << "m_Translate_Matrix[13] : " << m_Translate_Matrix[13] << std::endl;

		m_vector_y -= (m_Translate_Matrix[13] - m_floor);

		m_Translate_Matrix[13] = m_floor;

		JumpTime = 0.f;
		IsJump = false;
		
	}

	std::cout << "y이동량: " << m_vector_y << std::endl;
	std::cout << "tranlateY: " << m_Translate_Matrix[13] << std::endl;
	std::cout << "바닥: " << m_floor << std::endl;
	std::cout << std::endl << std::endl;

}
