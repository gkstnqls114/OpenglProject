#include "pch.h"
#include "ObjModel.h"
#include "Mediator.h"
#include "Matrix.h"

#include "PlayerNotification.h"
#include "PlayerState.h"

#include "Player.h"

CObjModel* CPlayer::m_Rabit_Body = nullptr;
CObjModel* CPlayer::m_Rabit_Ear = nullptr;
CObjModel* CPlayer::m_Rabit_LeftFoot = nullptr;
CObjModel* CPlayer::m_Rabit_RightFoot = nullptr;

CPlayer::CPlayer()
{
	CPlayer::InitModel();
	m_Matrix = new CMatrix();

	Init_GameScene();
}

CPlayer::~CPlayer()
{
	//나중에 수정
	//굳이 지울 필요가 있을까 싶기도 하고..
	CPlayer::DeleteModel();
	delete m_Matrix;
}

void CPlayer::InitModel()
{
	InitBody();
	InitEar();
	InitLeftFoot();
	InitRightFoot();
}

void CPlayer::DeleteModel()
{
	DeleteBody();
	DeleteEar();
	DeleteLeftFoot();
	DeleteRightFoot();
}

void CPlayer::Initialize()
{
}


void CPlayer::Keyboard(const unsigned char & key, const int & x, const int & y)
{
	
}

void CPlayer::SpecialKeys(const int & key, const int & x, const int & y)
{
	if (key != GLUT_KEY_UP && key != GLUT_KEY_LEFT && key != GLUT_KEY_RIGHT) return;

	if (m_PlayerState) {
		m_PlayerState->SpecialKeys(this, key);
	}
}

void CPlayer::Update()
{
	if (m_PlayerState) m_PlayerState->Update(this);
}

void CPlayer::Render()
{
	glColor3f(LIGHTRGB.x, LIGHTRGB.y, LIGHTRGB.z);
	glPushMatrix();
		glTranslated(m_Pos.x, m_Pos.y, m_Pos.z);
	glPushMatrix();
		m_Matrix->MultiMatrix();
	glPushMatrix();
		//glRotated(Tumblingdegree, 1, 0, 0);
		m_Rabit_Body->Render();
		m_Rabit_Ear->Render();
		m_Rabit_LeftFoot->Render();
		m_Rabit_RightFoot->Render();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}

void CPlayer::RotateX(int degree)
{
	m_Matrix->Calu_Rotate(degree, 1, 0, 0);
}

void CPlayer::RotateY(int degree)
{
	m_Matrix->Calu_Rotate(degree, 0, 1, 0);
}

void CPlayer::RotateZ(int degree)
{
	m_Matrix->Calu_Rotate(degree, 0, 0, 1);
}

void CPlayer::Init_GameScene()
{
	//초기화
	m_Rabit_Body->SetTextuerIDindex(0);
	m_JumpProperty.Initialize();
	m_Rabit_LeftFoot->Reset();
	m_Rabit_RightFoot->Reset();
	m_Rabit_Body->Reset();
	m_Rabit_Ear->Reset();

	m_PlayerState = &WaitingState;
	
	m_Matrix->Set_Rotate(180, 0, 1, 0);
	m_Matrix->Set_Scale(0.3);
	m_Matrix->ResetTranslate();

	m_prevSide = 0;
	m_BoardNum = 0;
	m_MySide = 0;
}

void CPlayer::Init_GameOver()
{
	m_Rabit_Body->SetTextuerIDindex(1);
	m_Rabit_LeftFoot->Reset();
	m_Rabit_RightFoot->Reset();
	m_Rabit_Body->Reset();
	m_Rabit_Ear->Reset();

	m_Rabit_LeftFoot->Translate(CVector3D<>(0, -7, 30));
	m_Rabit_LeftFoot->Rotate(-90, 1, 0, 0);

	m_Rabit_RightFoot->Translate(CVector3D<>(0, -7, 30));
	m_Rabit_RightFoot->Rotate(-90, 1, 0, 0);
	
	m_Rabit_Body->Rotate(15, 1, 0, 0);

	m_Rabit_Ear->Translate(CVector3D<>(0, -10, -10));
	m_Rabit_Ear->Rotate(70, 1, 0, 0);
}

void CPlayer::CheckDead()
{
	bool InRange = m_MySide <= 1 && m_MySide >= -1;
	if (InRange) return;

	stateChange_Dead();
}

float CPlayer::BodyRotateDegree()
{
	int Rotate = abs(m_prevSide - m_MySide);

	bool Rotate_degree_0 = Rotate == 0;
	if (Rotate_degree_0) return 0;

	bool Rotate_degree_45 = Rotate == 1;
	bool Rotate_degree_90 = Rotate == 2;
	float frame_degree = 0;
	float Nowdegree = 0;

	if (Rotate_degree_45) {
		Nowdegree = m_JumpProperty.Rotatedegree;
		frame_degree = Nowdegree / float(m_JumpProperty.m_FinishJumpTime);
	}
	else if (Rotate_degree_90) {
		Nowdegree = m_JumpProperty.Rotatedegree * 2;
		frame_degree = Nowdegree / float(m_JumpProperty.m_FinishJumpTime);
	}

	return frame_degree;
}

void CPlayer::FrontJump()
{
	Calculate_JumpVector();
	float rotatedegree = BodyRotateDegree();
	if (m_prevSide == k_right) {
		m_Matrix->Calu_Rotate(rotatedegree, 0, 1, 0);
	}
	else if (m_prevSide == k_left) {
		m_Matrix->Calu_Rotate(-rotatedegree, 0, 1, 0);
	}

	JumpRotate();

	if(m_pPlayerNotification) m_pPlayerNotification->Notify(this);
}

void CPlayer::RightJump()
{
	Calculate_JumpVector();
	float rotatedegree = BodyRotateDegree();
	m_Matrix->Calu_Rotate(-rotatedegree, 0, 1, 0);

	JumpRotate();

	if (m_pPlayerNotification) m_pPlayerNotification->Notify(this);
}

void CPlayer::LeftJump()
{
	Calculate_JumpVector();
	float rotatedegree = BodyRotateDegree();
	m_Matrix->Calu_Rotate(rotatedegree, 0, 1, 0);

	JumpRotate();

	if (m_pPlayerNotification) m_pPlayerNotification->Notify(this);
}

void CPlayer::StateChange_FrontJump()
{
	m_BoardNum += 1;
	m_prevSide = m_MySide;
	m_MySide = k_front;
	m_PlayerState = &FrontJumpState;
}

void CPlayer::StateChange_RightJump()
{
	m_BoardNum += 1;
	m_prevSide = m_MySide;
	m_MySide = k_right;
	m_PlayerState = &RightJumpState;
}

void CPlayer::StateChange_LeftJump()
{
	m_BoardNum += 1;
	m_prevSide = m_MySide;
	m_MySide = k_left;
	m_PlayerState = &LeftJumpState;
}

void CPlayer::StateChange_Wait()
{
	//모든 회전을 리셋시킨다.
	m_Rabit_LeftFoot->ResetRotate();
	m_Rabit_RightFoot->ResetRotate();
	m_JumpProperty.Reset();
	m_Pos.y = 0;

	m_PlayerState = &WaitingState;
	
	CheckDead();
}

void CPlayer::StateChange_Fall()
{
	m_PlayerState = &FallingState;
}

void CPlayer::stateChange_Dead()
{
	m_PlayerState = &DeadState;
}

void CPlayer::Calculate_JumpVector()
{
	m_JumpProperty.m_JumpTime += 1;

	float radian = m_JumpProperty.m_JumpDegree * m_JumpProperty.k_PI / 180;
	
	CVector3D<> tempVector;
	tempVector.z = - m_JumpProperty.m_power * cos(radian);
	tempVector.y = m_JumpProperty.m_power * sin(radian)
		- m_JumpProperty.k_gravity * m_JumpProperty.m_JumpTime;
	//if (IsRight) {
	//	m_vector_x = 20.f / m_FinishJumpTime;
	//}
	//else if (IsLeft) {
	//	m_vector_x = -20.f / m_FinishJumpTime;
	//}

	m_Pos.x += tempVector.x;
	m_Pos.y += tempVector.y;
	m_Pos.z += tempVector.z;
}

void CPlayer::JumpRotate()
{
	if (m_JumpProperty.m_FinishJumpTime % 2 == 1 && m_JumpProperty.m_JumpTime
		== (m_JumpProperty.m_FinishJumpTime / 2 + 1)) return;

	float TimeSection = float(m_JumpProperty.m_FinishJumpTime) / 4.f;
	int FrameSection = m_JumpProperty.m_FinishJumpTime / 4;

	// 자신의 움직이는 TimeSection
	float Body_degree = 45.f / float(m_JumpProperty.m_FinishJumpTime);
	float Boby_flat_percent = 0.5f / float(m_JumpProperty.m_FinishJumpTime);
	float Ear_degree = -35.f / float(FrameSection * 2);
	float Foot_top_degree = 40.f / float(FrameSection * 2);
	float Foot_befor_reach_degree = -90.f / float(FrameSection);
	float Foot_reach_degree = 50.f / float(FrameSection);

	//if (IsTumbling) {
	//	float tumblig = (360.f / float(m_FinishJumpTime));
	//	Tumblingdegree += tumblig;
	//}

	bool Untill_Top = m_JumpProperty.m_JumpTime <= TimeSection * 2;
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

	if (m_JumpProperty.m_FinishJumpTime % 2 == 1 &&
		m_JumpProperty.m_JumpTime == (m_JumpProperty.m_FinishJumpTime / 2 + m_JumpProperty.m_JumpTime / 4 + 2)) return;

	bool Unitll_Before_Reach = m_JumpProperty.m_JumpTime >= TimeSection * 2;
	bool Unitll_Reach = m_JumpProperty.m_JumpTime >= TimeSection * 3;
	bool Unitll_Last = m_JumpProperty.m_JumpTime == m_JumpProperty.m_FinishJumpTime;

	if (Unitll_Reach) {
		//앞으로 발이 나아감
		m_Rabit_LeftFoot->Rotate(Foot_reach_degree, 1, 0, 0);
		m_Rabit_RightFoot->Rotate(Foot_reach_degree, 1, 0, 0);
	}
	else if (Unitll_Before_Reach) {
		m_Rabit_LeftFoot->Rotate(Foot_befor_reach_degree, 1, 0, 0);
		m_Rabit_RightFoot->Rotate(Foot_befor_reach_degree, 1, 0, 0);
	}
	if (Unitll_Last) {
		StateChange_Wait();
	}
}


void CPlayer::InitBody()
{
	if (CPlayer::m_Rabit_Body != nullptr) return;

	CPlayer::m_Rabit_Body = new CObjModel;
	CPlayer::m_Rabit_Body->LoadObj("Rabit_Body.obj");
	CPlayer::m_Rabit_Body->LoadTexture("Rabit_Body.bmp");
	CPlayer::m_Rabit_Body->LoadTexture("Rabit_Body_Dead.bmp");
	CPlayer::m_Rabit_Body->LoadTexture("Rabit_Body_Fall.bmp");
	m_Rabit_Body->MovePivot(CVector3D<>(0, -20, 10));

}

void CPlayer::InitEar()
{
	if (CPlayer::m_Rabit_Ear != nullptr) return;

	CPlayer::m_Rabit_Ear = new CObjModel;
	CPlayer::m_Rabit_Ear->LoadObj("Rabit_Ear.obj");
	CPlayer::m_Rabit_Ear->LoadTexture("Rabit_Ear.bmp");
	m_Rabit_Ear->MovePivot(CVector3D<>(0, -37, -20));
}

void CPlayer::InitLeftFoot()
{
	if (CPlayer::m_Rabit_LeftFoot != nullptr) return;

	CPlayer::m_Rabit_LeftFoot = new CObjModel;
	CPlayer::m_Rabit_LeftFoot->LoadObj("Rabit_LeftFoot.obj");
	CPlayer::m_Rabit_LeftFoot->LoadTexture("Rabit_LeftFoot.bmp");
	m_Rabit_LeftFoot->MovePivot(CVector3D<>(0, -10, 10));
}

void CPlayer::InitRightFoot()
{
	if (CPlayer::m_Rabit_RightFoot != nullptr) return;

	CPlayer::m_Rabit_RightFoot = new CObjModel;
	CPlayer::m_Rabit_RightFoot->LoadObj("Rabit_RightFoot.obj");
	CPlayer::m_Rabit_RightFoot->LoadTexture("Rabit_RightFoot.bmp");
	m_Rabit_RightFoot->MovePivot(CVector3D<>(0, -10, 10));
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
