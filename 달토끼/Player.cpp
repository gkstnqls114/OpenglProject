#include "pch.h"
#include "Vector3D.h"
#include "ObjModel.h"
#include "Mediator.h"
#include "Matrix.h"
#include "Player.h"


CPlayer::CPlayer(CMediator*& mediator)
{
	std::cout << "�÷��̾� ����" << std::endl;
	m_RabitBody = new CObjModel;
	m_RabitBody->LoadObj("body.obj");

	m_RabitFoot = new CObjModel;
	m_RabitFoot->LoadObj("foot_up.obj");

	//�÷��̾� �������ްŸ�
	// �Ǽ��� ��Ȯ�� ��� ����Ƿ� ���⼭ �ѹ� ����Ѵ�.
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

		m_BoardNum += 1;
		IsJump = true;
	}
	else if (key == GLUT_KEY_RIGHT) {
		m_BoardNum += 1;
		IsJump = true;
		IsRight = true;
	}
	else if (key == GLUT_KEY_LEFT) {
		m_BoardNum += 1;
		IsJump = true;
		IsLeft = true;
	}		
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

void CPlayer::Player_JumpFinish()
{
	std::cout << "Player: �÷��̾� ���� Ȯ��" << std::endl;
}

void CPlayer::Player_Dead()
{
	std::cout << "Player: �÷��̾� ���� Ȯ��" << std::endl;
	isDead = true;
}

void CPlayer::Road_playerBoard_Disapper()
{
	std::cout << "Player: �÷��̾� ���� ����� Ȯ��" << std::endl;
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

	std::cout << "�����Ϸ�ð�: " << m_FinishJumpTime << std::endl;
	std::cout << "�����Ÿ�: " << m_JumpReach << std::endl;
}

void CPlayer::Jump()
{
	if (!IsJump) {
		//ī�޶� ������ ���������� x = 0..
		m_vector_x = 0;
		m_vector_y = 0;
		m_vector_z = 0;
		return;
	}

	Calculate_JumpVector();
	m_Matrix->Calu_Tranlate(CVector3D(m_vector_x, m_vector_y, m_vector_z));
	
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

	//���� �Ϸ��� �����ڿ��� ����.
	m_Mediator->Player_JumpFinish();
}

void CPlayer::Finish_Jump()
{
	if (m_Matrix->Get_Tranlate_13() >= 0) return;

	m_Matrix->Set_Translate_13(0);

	if (IsRight) {
		m_MySide += 1;
	}
	else if (IsLeft) {
		m_MySide -= 1;
	}


	Reset_JumpProperty();
}
