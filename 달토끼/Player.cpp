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

	//�÷��̾� �������ްŸ�
	// �Ǽ��� ��Ȯ�� ��� ����Ƿ� ���⼭ �ѹ� ����Ѵ�.
	Find_JumpProperty();

	m_Matrix = new CMatrix();
	m_Matrix->Calu_Rotate(180, 0, 1, 0);
	m_Matrix->Calu_Scale(0.3);

	m_Mediator = mediator;
}

CPlayer::~CPlayer()
{
	//���߿� ����
	//���� ���� �ʿ䰡 ������ �ͱ⵵ �ϰ�..
	CPlayer::DeleteModel();
}

void CPlayer::InitModel()
{
	////�� �� ���� ȣ��
	//���߿� �Լ�ȭ�ϱ�
	if (CPlayer::m_Rabit_Body == nullptr) {
		CPlayer::m_Rabit_Body = new CObjModel;
		CPlayer::m_Rabit_Body->LoadObj("Rabit_Body.obj");
		m_Rabit_Body->MovePivot(CVector3D(0, -10, 20));
	}

	if (CPlayer::m_Rabit_Ear == nullptr) {
		CPlayer::m_Rabit_Ear = new CObjModel;
		CPlayer::m_Rabit_Ear->LoadObj("Rabit_Ear.obj");
		m_Rabit_Ear->MovePivot(CVector3D(0, -37, -20));
	}

	if (CPlayer::m_Rabit_LeftFoot == nullptr) {
		CPlayer::m_Rabit_LeftFoot = new CObjModel;
		CPlayer::m_Rabit_LeftFoot->LoadObj("Rabit_LeftFoot.obj");
		m_Rabit_LeftFoot->MovePivot(CVector3D(0, -10, 10));
	}

	if (CPlayer::m_Rabit_RightFoot == nullptr) {
		CPlayer::m_Rabit_RightFoot = new CObjModel;
		CPlayer::m_Rabit_RightFoot->LoadObj("Rabit_RightFoot.obj");
		m_Rabit_RightFoot->MovePivot(CVector3D(0, -10, 10));
	}

	if (CPlayer::m_Rabits_Helmet == nullptr) {
		CPlayer::m_Rabits_Helmet = new CObjModel;
		CPlayer::m_Rabits_Helmet->LoadObj("Rabits_Helmet_low.obj");
	}

	std::cout << "Player �� ���� �Ϸ�" << std::endl;
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
	//�� ���� ���߿� �����ҷ� ��0��;;
	//Ȧ���� ���� ���� ������ ������� �ʴ´�.
	if (m_FinishJumpTime % 2 == 1 && m_JumpTime == (m_FinishJumpTime / 2 + 1)) return;

	float TimeSection = float(m_FinishJumpTime) / 4.f;
	int FrameSection = m_FinishJumpTime / 4;

	// �ڽ��� �����̴� TimeSection
	float Body_degree =					45.f	/ float(m_FinishJumpTime);
	float Boby_flat_percent =			0.5f	/ float(m_FinishJumpTime);
	float Ear_degree =					-35.f	/ float(FrameSection * 2);
	float Foot_top_degree =				40.f	/ float(FrameSection * 2);
	float Foot_befor_reach_degree =		-90.f	/ float(FrameSection);
	float Foot_reach_degree =			50.f	/ float(FrameSection);

	bool Untill_Top = m_JumpTime <= TimeSection * 2;
	if (Untill_Top) {
		std::cout << m_JumpTime << " : ���� �ö󰡴� ��" << std::endl;
		m_Rabit_LeftFoot->Rotate(Foot_top_degree, 1, 0, 0);
		m_Rabit_RightFoot->Rotate(Foot_top_degree, 1, 0, 0);
		m_Rabit_Body->Rotate(Body_degree, 1, 0, 0);
		m_Rabit_Body->Scale(1.f, 1.f - Boby_flat_percent, 1.f);
		m_Rabit_Ear->Rotate(Ear_degree, 1, 0, 0);
	}
	else {
		m_Rabit_Body->Rotate(-Body_degree, 1, 0, 0);
		m_Rabit_Body->Scale(1.f, 1.f + Boby_flat_percent, 1.f);
		m_Rabit_Ear->Rotate(-Ear_degree, 1, 0, 0);
	}

	if (m_FinishJumpTime % 2 == 1 &&
		m_JumpTime == (m_FinishJumpTime / 2 + m_JumpTime / 4 + 2)) return;

	bool Unitll_Before_Reach = m_JumpTime >= TimeSection * 2;
	bool Unitll_Reach = m_JumpTime >= TimeSection * 3;
	bool Unitll_Last = m_JumpTime == m_FinishJumpTime;
	if (Unitll_Last) {
		//�Ƹ𸣰ڴ�!! �� ȸ�� ����
		m_Rabit_LeftFoot->Reset_Rotate();
		m_Rabit_RightFoot->Reset_Rotate();
	}
	else if (Unitll_Reach) {
		//������ ���� ���ư�
		m_Rabit_LeftFoot->Rotate(Foot_reach_degree, 1, 0, 0);
		m_Rabit_RightFoot->Rotate(Foot_reach_degree, 1, 0, 0);
	}
	else if (Unitll_Before_Reach) {
		m_Rabit_LeftFoot->Rotate(Foot_befor_reach_degree, 1, 0, 0);
		m_Rabit_RightFoot->Rotate(Foot_befor_reach_degree, 1, 0, 0);
	}
}

void CPlayer::Player_JumpFinish()
{

}

void CPlayer::Player_Dead()
{
	if (IsJump) {
		std::cout << "�̻���!" << std::endl;
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

	std::cout << "�����Ϸ�ð�: " << m_FinishJumpTime << std::endl;
	std::cout << "�����Ÿ�: " << m_JumpReach << std::endl;
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
