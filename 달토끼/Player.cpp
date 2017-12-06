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
	InitBody();
	InitEar();
	InitLeftFoot();
	InitHelmet();

	std::cout << "Player 모델 생성 완료" << std::endl;
}

void CPlayer::DeleteModel()
{
	DeleteBody();
	DeleteEar();
	DeleteLeftFoot();
	DeleteRightFoot();
	DeleteHelmet();

	std::cout << "Player 모델 삭제 완료" << std::endl;
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
	Process_Side(jumpSide);
}

void CPlayer::Player_Jumping()
{
	Jump_BodyRotate();

	//아 점프 나중에 수정할래 ㅡ0ㅡ;;
	//홀수는 제일 높은 지점을 계산하지 않는다.
	if (m_FinishJumpTime % 2 == 1 && m_JumpTime == (m_FinishJumpTime / 2 + 1)) return;

	float TimeSection = float(m_FinishJumpTime) / 4.f;
	int FrameSection = m_FinishJumpTime / 4;

	// 자신의 움직이는 TimeSection
	float Body_degree =					45.f	/ float(m_FinishJumpTime);
	float Boby_flat_percent =			0.5f	/ float(m_FinishJumpTime);
	float Ear_degree =					-35.f	/ float(FrameSection * 2);
	float Foot_top_degree =				40.f	/ float(FrameSection * 2);
	float Foot_befor_reach_degree =		-90.f	/ float(FrameSection);
	float Foot_reach_degree =			50.f	/ float(FrameSection);

	bool Untill_Top = m_JumpTime <= TimeSection * 2;
	if (Untill_Top) {
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
		//아모르겠다!! 걍 회전 리셋
		m_Rabit_LeftFoot->Reset_Rotate();
		m_Rabit_RightFoot->Reset_Rotate();
	}
	else if (Unitll_Reach) {
		//앞으로 발이 나아감
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
		std::cout << "이상해!" << std::endl;
		return;
	}

	isDead = true;
}

void CPlayer::Process_Side(int & lhs)
{
	if (IsRight) {
		lhs = k_right;
	}
	else if (IsLeft) {
		lhs = k_left;
	}
	else {
		lhs = k_front;
	}
}

void CPlayer::Jump_BodyRotate()
{
	int Rotate = abs(prevSide - jumpSide);
	float frame_degree = 0;

	bool Rotate_degree_0 = Rotate == 0;
	if (Rotate_degree_0) return;
	
	bool Rotate_degree_45 = Rotate == 1;
	bool Rotate_degree_90 = Rotate == 2;
	float degree = atan(float(m_JumpReach) / float(Road_Distance_X)) * 180 / k_PI;
	degree = 90 - degree;
	if (Rotate_degree_45) {
		frame_degree = degree / float(m_FinishJumpTime);
	}
	else if (Rotate_degree_90) {
		degree = degree * 2;
		frame_degree = degree / float(m_FinishJumpTime);
	}

	//나중에 수정
	// 굳이 4개면 안에 이프문 만들 필요가 없지..
	if (IsRight) {
		m_Matrix->Calu_Rotate(-frame_degree, 0, 1, 0);
	}
	else if (IsLeft) {
		m_Matrix->Calu_Rotate(frame_degree, 0, 1, 0);
	}
	else {
		//앞으로 향함
		if (prevSide == k_right) {
			m_Matrix->Calu_Rotate(frame_degree, 0, 1, 0);
		}
		else if (prevSide == k_left) {
			m_Matrix->Calu_Rotate(-frame_degree, 0, 1, 0);
		}
	}
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
	if (m_Matrix->Get_Tranlate_Y() >= 0) return;

	m_Matrix->Set_Translate_13(0);

	Process_Side(prevSide);

	Reset_JumpProperty();

	bool InRange = m_MySide <= 1 && m_MySide >= -1;
	if (InRange) {
		m_Mediator->Player_JumpFinish();
	}
	else {
		m_Mediator->Player_Dead();
	}
}

void CPlayer::InitBody()
{
	if (CPlayer::m_Rabit_Body != nullptr) return;

	CPlayer::m_Rabit_Body = new CObjModel;
	CPlayer::m_Rabit_Body->LoadObj("Rabit_Body.obj");
	CPlayer::m_Rabit_Body->LoadTexture("Rabit_Body(24bmp).bmp");
	m_Rabit_Body->MovePivot(CVector3D(0, -20, 10));

}

void CPlayer::InitEar()
{
	if (CPlayer::m_Rabit_Ear != nullptr) return;

	CPlayer::m_Rabit_Ear = new CObjModel;
	CPlayer::m_Rabit_Ear->LoadObj("Rabit_Ear.obj");
	m_Rabit_Ear->MovePivot(CVector3D(0, -37, -20));
}

void CPlayer::InitLeftFoot()
{
	if (CPlayer::m_Rabit_LeftFoot != nullptr) return;

	CPlayer::m_Rabit_LeftFoot = new CObjModel;
	CPlayer::m_Rabit_LeftFoot->LoadObj("Rabit_LeftFoot.obj");
	m_Rabit_LeftFoot->MovePivot(CVector3D(0, -10, 10));
}

void CPlayer::InitRightFoot()
{
	if (CPlayer::m_Rabit_RightFoot != nullptr) return;

	CPlayer::m_Rabit_RightFoot = new CObjModel;
	CPlayer::m_Rabit_RightFoot->LoadObj("Rabit_RightFoot.obj");
	m_Rabit_RightFoot->MovePivot(CVector3D(0, -10, 10));
}

void CPlayer::InitHelmet()
{
	if (CPlayer::m_Rabits_Helmet != nullptr) return;

	CPlayer::m_Rabits_Helmet = new CObjModel;
	CPlayer::m_Rabits_Helmet->LoadObj("Rabits_Helmet_low.obj");
}

void CPlayer::DeleteBody()
{
	if (CPlayer::m_Rabit_Body == nullptr) return;

	delete m_Rabit_Body;
	m_Rabit_Body = nullptr;
}

void CPlayer::DeleteEar()
{
	if (CPlayer::m_Rabit_Ear == nullptr) return;

	delete m_Rabit_Ear;
	m_Rabit_Ear = nullptr;
}

void CPlayer::DeleteLeftFoot()
{
	if (CPlayer::m_Rabit_LeftFoot == nullptr) return;

	delete m_Rabit_LeftFoot;
	m_Rabit_LeftFoot = nullptr;
}

void CPlayer::DeleteRightFoot()
{
	if (CPlayer::m_Rabit_RightFoot == nullptr) return;

	delete m_Rabit_RightFoot;
	m_Rabit_RightFoot = nullptr;
}

void CPlayer::DeleteHelmet()
{
	if (CPlayer::m_Rabits_Helmet == nullptr) return;

	delete m_Rabits_Helmet;
	m_Rabits_Helmet = nullptr;
}
