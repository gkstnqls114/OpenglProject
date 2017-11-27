#include "pch.h"
#include "Vector3D.h"
#include "ObjModel.h"
#include "Mediator.h"
#include "Matrix.h"
#include "Player.h"

CObjModel* CPlayer::m_Rabit_Body = nullptr;
CObjModel* CPlayer::m_Rabit_Ear = nullptr;
CObjModel* CPlayer::m_Rabit_LeftFoot = nullptr;
CObjModel* CPlayer::m_Rabit_RightFoot = nullptr;
CObjModel* CPlayer::m_Rabits_Helmet = nullptr;

CPlayer::CPlayer(CMediator*& mediator)
{
	CPlayer::InitModel();

	//플레이어 점프도달거리
	// 실수라서 정확한 계산 힘드므로 여기서 한번 계산한다.
	Find_JumpProperty();

	m_Matrix = new CMatrix();
	m_Matrix->Calu_Rotate(180, 0, 1, 0);
	m_Matrix->Calu_Scale(0.3);

	m_Mediator = mediator;
}

CPlayer::~CPlayer()
{
	//나중에 수정
	//굳이 지울 필요가 있을까 싶기도 하고..
	CPlayer::DeleteModel();
}

void CPlayer::InitModel()
{
	////단 한 번만 호출
	//나중에 함수화하기
	if (CPlayer::m_Rabit_Body == nullptr) {
		CPlayer::m_Rabit_Body = new CObjModel;
		CPlayer::m_Rabit_Body->LoadObj("Rabit_Body.obj");
	}

	if (CPlayer::m_Rabit_Ear == nullptr) {
		CPlayer::m_Rabit_Ear = new CObjModel;
		CPlayer::m_Rabit_Ear->LoadObj("Rabit_Ear.obj");
	}

	if (CPlayer::m_Rabit_LeftFoot == nullptr) {
		CPlayer::m_Rabit_LeftFoot = new CObjModel;
		CPlayer::m_Rabit_LeftFoot->LoadObj("Rabit_LeftFoot.obj");
	}

	if (CPlayer::m_Rabit_RightFoot == nullptr) {
		CPlayer::m_Rabit_RightFoot = new CObjModel;
		CPlayer::m_Rabit_RightFoot->LoadObj("Rabit_RightFoot.obj");
	}

	if (CPlayer::m_Rabits_Helmet == nullptr) {
		CPlayer::m_Rabits_Helmet = new CObjModel;
		CPlayer::m_Rabits_Helmet->LoadObj("Rabits_Helmet_low.obj");
	}

	std::cout << "Player 모델 생성 완료" << std::endl;
}

void CPlayer::DeleteModel()
{
	if (CPlayer::m_Rabit_Body != nullptr) {
		delete m_Rabit_Body;
		m_Rabit_Body = nullptr;
	}

	if (CPlayer::m_Rabit_Ear != nullptr) {
		delete m_Rabit_Ear;
		m_Rabit_Ear = nullptr;
	}

	if (CPlayer::m_Rabit_LeftFoot != nullptr) {
		delete m_Rabit_LeftFoot;
		m_Rabit_LeftFoot = nullptr;
	}

	if (CPlayer::m_Rabit_RightFoot != nullptr) {
		delete m_Rabit_RightFoot;
		m_Rabit_RightFoot = nullptr;
	}

	if (CPlayer::m_Rabits_Helmet != nullptr) {
		delete m_Rabits_Helmet;
		m_Rabits_Helmet = nullptr;
	}
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
		m_Rabit_Body->Render();
		m_Rabit_Ear->Render();
		m_Rabit_LeftFoot->Render();
		m_Rabit_RightFoot->Render();
		m_Rabits_Helmet->Render();
	glPopMatrix();
}

void CPlayer::Player_JumpStart()
{
}

void CPlayer::Player_Jumping()
{
	//홀수라서 어쩔수없이..
	if (m_FinishJumpTime % 2 == 1 && m_JumpTime == m_FinishJumpTime) return;

	float degree = 180 / m_FinishJumpTime;
	if (m_JumpTime <= m_FinishJumpTime / 2) {
		m_Rabit_LeftFoot->Rotate(degree, 1, 0, 0);
		m_Rabit_RightFoot->Rotate(degree, 1, 0, 0);
	}
	else {
		m_Rabit_LeftFoot->Rotate(-degree, 1, 0, 0);
		m_Rabit_RightFoot->Rotate(-degree, 1, 0, 0);
	}
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
