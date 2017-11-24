#include "pch.h"
#include "Vector3D.h"
#include "ObjModel.h"
#include "Mediator.h"
#include "Matrix.h"
#include "Player.h"


CPlayer::CPlayer(CMediator*& mediator)
{
	std::cout << "플레이어 생성" << std::endl;
	m_RabitBody = new CObjModel;
	m_RabitBody->LoadObj("body.obj");

	m_RabitFoot = new CObjModel;
	m_RabitFoot->LoadObj("foot_up.obj");

	//플레이어 점프도달거리
	// 실수라서 정확한 계산 힘드므로 여기서 한번 계산한다.
	Find_JumpProperty();

	m_Matrix = new CMatrix();
	m_Matrix->Calu_Rotate(180, 0, 1, 0);

	m_Mediator = mediator;
}


CPlayer::~CPlayer()
{
	delete m_RabitBody;
	delete m_RabitFoot;
}


void CPlayer::Keyboard(const unsigned char & key, const int & x, const int & y)
{
	return;
	int degree = 10;

	if (key == 'a') {
		m_Matrix->Calu_Rotate(degree, 0, 1, 0);
	}

	if (key == 'd') {
		m_Matrix->Calu_Rotate(-degree, 0, -1, 0);
	}

	if (key == 'w') {
		m_Matrix->Calu_Rotate(degree, 1, 0, 0);
	}

	if (key == 's') {
		m_Matrix->Calu_Rotate(-degree, 1, 0, 0);
	}

}

void CPlayer::SpecialKeys(const int & key, const int & x, const int & y)
{
	//JUMP
	if (IsJump) return;
	if (isDead) return;

	if (key == GLUT_KEY_UP) {
		IsJump = true;
	}
	else if (key == GLUT_KEY_RIGHT) {
		IsJump = true;
		IsRight = true;
	}
	else if (key == GLUT_KEY_LEFT) {
		IsJump = true;
		IsLeft = true;
	}		

	if (IsRight) {
		m_MySide += 1;
	}
	else if (IsLeft) {
		m_MySide -= 1;
	}

	m_BoardNum += 1;

	m_Mediator->Player_JumpStart();
}

void CPlayer::Update()
{
	if (isDead) return;

	Jump();
}

void CPlayer::Render()
{
	glColor3f(0.f, 0.f, 0.f);
	glPushMatrix();
		m_Matrix->MultiMatrix();
		m_RabitBody->Render();
		m_RabitFoot->Render();
	glPopMatrix();
}

void CPlayer::Player_JumpStart()
{
}

void CPlayer::Player_Jumping()
{
}

void CPlayer::Player_JumpFinish()
{

}

void CPlayer::Player_Dead()
{
	if (IsJump) {
		std::cout << "이상해!" << std::endl;
		return;
	}

	isDead = true;
}

void CPlayer::Find_JumpProperty()
{
	float radian = m_JumpDegree * k_PI / 180;
	int temp_jumptime = 0;
	GLdouble temp_vector_z = 0;
	GLdouble temp_vector_y = 0;
	while (temp_vector_y >= 0)
	{
		temp_jumptime += 1;
		temp_vector_z += -m_power * cos(radian);
		temp_vector_y += m_power * sin(radian) - k_gravity * temp_jumptime;
	}
	
	m_FinishJumpTime = temp_jumptime;
	m_JumpReach = -temp_vector_z;

	std::cout << "점프완료시간: " << m_FinishJumpTime << std::endl;
	std::cout << "점프거리: " << m_JumpReach << std::endl;
}

void CPlayer::Jump()
{
	if (!IsJump) return;

	Calculate_JumpVector();
	m_Matrix->Calu_Tranlate(CVector3D(m_vector_x, m_vector_y, m_vector_z));
	
	m_Mediator->Player_Jumping();

	Finish_Jump();
}

void CPlayer::Calculate_JumpVector()
{
	m_JumpTime += 1;

	float radian = m_JumpDegree * k_PI / 180;
	m_vector_z = -m_power * cos(radian);
	m_vector_y = m_power * sin(radian) - k_gravity * m_JumpTime;
	if (IsRight) {
		m_vector_x = 20.f / m_FinishJumpTime;
	}
	else if (IsLeft) {
		m_vector_x = -20.f / m_FinishJumpTime;
	}
}



void CPlayer::Reset_JumpProperty()
{
	IsJump = false;
	IsRight = false;
	IsLeft = false;
	m_JumpTime = 0;
	m_vector_x = 0;
	m_vector_y = 0;
	m_vector_z = 0;
}

void CPlayer::Finish_Jump()
{
	if (!IsJump) return;
	if (m_Matrix->Get_Tranlate_13() >= 0) return;

	m_Matrix->Set_Translate_13(0);

	Reset_JumpProperty();

	bool InRange = m_MySide <= 1 && m_MySide >= -1;
	if (InRange) {
		m_Mediator->Player_JumpFinish();
	}
	else {
		m_Mediator->Player_Dead();
	}
}
