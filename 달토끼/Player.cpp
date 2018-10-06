#include "pch.h"
#include "ObjModel.h"
#include "RotateMatrix.h"

#include "SceneManager.h"
#include "PlayerObserver.h"
#include "PlayerSubject.h"
#include "PlayerState.h"

#include "Road.h"

#include "Player.h"

CObjModel* CPlayer::m_Rabit_Body{ nullptr };
CObjModel* CPlayer::m_Rabit_Ear{ nullptr };
CObjModel* CPlayer::m_Rabit_LeftFoot{ nullptr };
CObjModel* CPlayer::m_Rabit_RightFoot{ nullptr };

CPlayer::CPlayer()
{
	CPlayer::InitModel();
	m_Matrix = new RotateMatrix();
	m_JumpProperty.Initialize();

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

	if (m_PlayerState) m_PlayerState->SpecialKeys(*this, key);
}

void CPlayer::Update()
{
	if (m_PlayerState) m_PlayerState->Update(*this);
}

void CPlayer::Render()
{
	glColor3f(LIGHTRGB.x, LIGHTRGB.y, LIGHTRGB.z);
	glPushMatrix();
		glTranslated(m_Pos.x, m_Pos.y, m_Pos.z);
	glPushMatrix();
		m_Matrix->Rotate();
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

void CPlayer::Reset_ModelRotate()
{
	m_Rabit_LeftFoot->Reset();
	m_Rabit_RightFoot->Reset();
	m_Rabit_Body->Reset();
	m_Rabit_Ear->Reset();
}

const bool CPlayer::IsAutoWaiting() const noexcept
{
	return AutoWaitingState.Get_IsUsing();
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
	Reset_ModelRotate();

	m_Matrix->Set_Rotate(180, 0, 1, 0);
	m_Pos = CVector3D<>(0.f, 0.f, 0.f);

	m_PlayerState = &WaitingState;

	m_MyBoardLength = 0;
	m_prevKeySide.IsFront();
	m_MyKeySide.IsFront();
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

void CPlayer::Receive_DisappearFootBoard(Road * road)
{
	const bool IsOnFallBoard = m_MyBoardLength <= road->Get_DisappearingBoardIndex();
	if (!IsOnFallBoard) return;
}

void CPlayer::Notify_PlayerJumping()
{
	if (m_pPlayerSubject) m_pPlayerSubject->Notify_PlayerJumping(this);
}

void CPlayer::Notify_PlayerWaitCamera()
{
	if (m_pPlayerSubject) m_pPlayerSubject->Notify_PlayerWaitCamera(this);
}

void CPlayer::Notify_PlayerJumpFinish()
{
	if (m_pPlayerSubject) m_pPlayerSubject->Notify_PlayerJumpFinish(this);
}

void CPlayer::Nofity_PlayerAutoJumping()
{
	if (m_pPlayerSubject) m_pPlayerSubject->Nofity_PlayerAutoJumping(this);
}

float CPlayer::BodyRotateDegree()
{
	int prevKeySide = m_prevKeySide.Get_Side() - 1;
	int currKeySide = m_MyKeySide.Get_Side() - 1;
	int Rotate = abs(prevKeySide - currKeySide);

	bool Rotate_degree_0 = Rotate == 0;
	if (Rotate_degree_0) return 0;

	bool IsRotate_degree45 = Rotate == 1;
	bool IsRotate_degree90 = Rotate == 2;
	float frame_degree = 0;
	float Nowdegree = 0;

	if (IsRotate_degree45) {
		Nowdegree = m_JumpProperty.Get_Rotatedegree();
		frame_degree = Nowdegree / float(m_JumpProperty.Get_FinishJumpTime());
	}
	else if (IsRotate_degree90) {
		Nowdegree = m_JumpProperty.Get_Rotatedegree() * 2;
		frame_degree = Nowdegree / float(m_JumpProperty.Get_FinishJumpTime());
	}

	return frame_degree;
}

void CPlayer::FrontJump()
{
	Calculate_FrontJump();
	//만약 오토점프중이라면 다시 한번 더 호출한다.
	if (AutoWaitingState.Get_IsUsing()) {
		Calculate_FrontJump();
	}

	Notify_PlayerJumping();
}

void CPlayer::RightJump()
{
	Calculate_RightJump();
	//만약 오토점프중이라면 다시 한번 더 호출한다.
	if (AutoWaitingState.Get_IsUsing()) {
		Calculate_RightJump();
	}

	Notify_PlayerJumping();
}

void CPlayer::LeftJump()
{
	Calculate_LeftJump();
	//만약 오토점프중이라면 다시 한번 더 호출한다.
	if (AutoWaitingState.Get_IsUsing()) {
		Calculate_LeftJump();
	}

	Notify_PlayerJumping();
}

void CPlayer::Fall()
{
	m_Matrix->Calu_Rotate(10, 0, 1, 0);
	m_Pos.y -= 3;

	if (m_Pos.y <= -200) {
		CSceneManager::GetInstance()->ChangeToGameOver();
		StateChange_Dead();
	}
}

void CPlayer::Dead()
{
	
}

void CPlayer::Protected()
{
}

void CPlayer::WaitCamera()
{
	Notify_PlayerWaitCamera();
}

void CPlayer::AutoWaiting()
{
	if(AutoWaitingState.IsPossibleUpdate()) {
		Nofity_PlayerAutoJumping();
	}
}

void CPlayer::StateChange_FrontJump()
{
	m_MyBoardLength += 1;
	m_prevKeySide = m_MyKeySide;
	m_MyKeySide.IsFront();
	m_PlayerState = &FrontJumpState;
}

void CPlayer::StateChange_RightJump()
{
	m_MyBoardLength += 1;
	m_prevKeySide = m_MyKeySide;
	m_MyKeySide.IsRight();
	m_MyBoardSide.MoveRight();
	m_PlayerState = &RightJumpState;
}

void CPlayer::StateChange_LeftJump()
{
	m_MyBoardLength += 1;
	m_prevKeySide = m_MyKeySide;
	m_MyKeySide.IsLeft();
	m_MyBoardSide.MoveLeft();
	m_PlayerState = &LeftJumpState;
}

//WaitCamera인지 AutoJump인지, 혹은 정상적으로 점프가 완료했는지 확인한다.
void CPlayer::StateChange_Wait()
{
	if (m_PlayerState != &AutoWaitingState) {
		// 현재 상태에 따라 rotate각도를 고정한다.
		// -z 가 현재 토끼가 바라보는 방향이므로 전부 +180도를 한다.
		m_Matrix->ResetRotate();
		if (m_PlayerState == &LeftJumpState) {
			std::cout << "Left Jump" << std::endl;
			m_Matrix->Set_Rotate(m_JumpProperty.Get_Rotatedegree() + 180, 0, 1, 0);
		}
		else if (m_PlayerState == &RightJumpState) {
			std::cout << "Right Jump" << std::endl;
			m_Matrix->Set_Rotate(-m_JumpProperty.Get_Rotatedegree() + 180, 0, 1, 0);
		}
		else if (m_PlayerState == &FrontJumpState) {
			std::cout << "Front Jump" << std::endl;
			m_Matrix->Set_Rotate(180, 0, 1, 0);
		}

		m_Rabit_Body->Set_Scale(1.f, 1.f, 1.f);
		m_Rabit_Body->ResetRotate();
		m_Rabit_LeftFoot->ResetRotate();
		m_Rabit_RightFoot->ResetRotate();
		m_JumpProperty.Reset();

		m_Pos.y = 0;
		m_Pos.x = (m_MyBoardSide.Get_Side() - 1) * m_JumpProperty.Get_RoadDistanceX();
		m_Pos.z = -m_MyBoardLength * m_JumpProperty.Get_JumpReach();
	}

	if (IsGetOutRoad()) {
		StateChange_WaitCamera();
	}
	else if (IsAutoWaiting()) {
#ifdef _DEBUG
		std::cout << "오토 중" << std::endl;
#endif
		m_PlayerState = &AutoWaitingState;
	}
	else {
		m_PlayerState = &WaitingState;
	}

	Notify_PlayerJumpFinish();
}

void CPlayer::StateChange_WaitCamera()
{
	m_PlayerState = &WaitCameraState;
}

void CPlayer::StateChange_Fall()
{
	m_PlayerState = &FallingState;
}

void CPlayer::StateChange_Dead()
{
	Init_GameOver();
	m_PlayerState = &DeadState;
}

void CPlayer::StateChange_AutoWaiting()
{
#ifdef _DEBUG
	std::cout << "오토 점프 실행" << std::endl;
#endif
	AutoWaitingState.Initialize();
}

void CPlayer::StateChange_Protected()
{

}

void CPlayer::Calculate_JumpVector()
{
	m_JumpProperty.Add_JumpTime();

	float radian = m_JumpProperty.k_JumpDegree * m_JumpProperty.k_PI / 180;
	
	CVector3D<> tempVector;
	tempVector.z = - m_JumpProperty.k_power * cos(radian);
	tempVector.y = m_JumpProperty.k_power * sin(radian)
		- m_JumpProperty.k_gravity * m_JumpProperty.Get_JumpTime();
	
	m_Pos.x += tempVector.x;
	m_Pos.y += tempVector.y;
	m_Pos.z += tempVector.z;
}

const bool CPlayer::IsGetOutRoad() const noexcept
{
	return m_MyBoardSide.IsOutofRange();
}

void CPlayer::JumpRotate()
{
	if (m_JumpProperty.Get_FinishJumpTime() % 2 == 1 && m_JumpProperty.Get_JumpTime()
		== (m_JumpProperty.Get_FinishJumpTime() / 2 + 1)) return;

	float TimeSection = float(m_JumpProperty.Get_FinishJumpTime()) / 4.f;
	int FrameSection = m_JumpProperty.Get_FinishJumpTime() / 4;

	// 자신의 움직이는 TimeSection
	float Body_degree = 45.f / float(m_JumpProperty.Get_FinishJumpTime());
	float Boby_flat_percent = 0.5f / float(m_JumpProperty.Get_FinishJumpTime());
	float Ear_degree = -35.f / float(FrameSection * 2);
	float Foot_top_degree = 40.f / float(FrameSection * 2);
	float Foot_befor_reach_degree = -90.f / float(FrameSection);
	float Foot_reach_degree = 50.f / float(FrameSection);

	bool Untill_Top = m_JumpProperty.Get_JumpTime() <= TimeSection * 2;
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

	if (m_JumpProperty.Get_FinishJumpTime() % 2 == 1 &&
		m_JumpProperty.Get_JumpTime() == (m_JumpProperty.Get_FinishJumpTime() / 2 + m_JumpProperty.Get_JumpTime() / 4 + 2)) return;

	bool Unitll_Before_Reach = m_JumpProperty.Get_JumpTime() >= TimeSection * 2;
	bool Unitll_Reach = m_JumpProperty.Get_JumpTime() >= TimeSection * 3;
	bool Unitll_Last = m_JumpProperty.Get_JumpTime() == m_JumpProperty.Get_FinishJumpTime();

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

void CPlayer::Render_TestRadius()
{

	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glColor4f(1.f, 1.f, 1.f, 0.5f);
	
	glPushMatrix();
	glTranslated(m_Pos.x, m_Pos.y + m_CollideY, m_Pos.z);
	glutSolidSphere(m_playerRadius, 10, 10);
	glPopMatrix();

	glDisable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
}

void CPlayer::Calculate_FrontJump()
{
	Calculate_JumpVector();
	float rotatedegree = BodyRotateDegree();
	if (m_prevKeySide.Get_IsRight()) {
		m_Matrix->Calu_Rotate(rotatedegree, 0, 1, 0);
	}
	else if (m_prevKeySide.Get_IsLeft()) {
		m_Matrix->Calu_Rotate(-rotatedegree, 0, 1, 0);
	}

	JumpRotate();
}

void CPlayer::Calculate_RightJump()
{
	Calculate_JumpVector();
	float rotatedegree = BodyRotateDegree();
	m_Matrix->Calu_Rotate(-rotatedegree, 0, 1, 0);
	float tmp_vector_x = float(JumpProperty::k_RoadDistance_X) / m_JumpProperty.Get_FinishJumpTime();
	m_Pos.x += tmp_vector_x;

	JumpRotate();
}

void CPlayer::Calculate_LeftJump()
{
	Calculate_JumpVector();
	float rotatedegree = BodyRotateDegree();
	m_Matrix->Calu_Rotate(rotatedegree, 0, 1, 0);

	float tmp_vector_x = -float(JumpProperty::k_RoadDistance_X) / m_JumpProperty.Get_FinishJumpTime();
	m_Pos.x += tmp_vector_x;

	JumpRotate();
}

void CPlayer::InitBody()
{
	if (CPlayer::m_Rabit_Body != nullptr) return;

	CPlayer::m_Rabit_Body = new CObjModel;
	CPlayer::m_Rabit_Body->LoadObj(".\\OBJModel\\Rabit_Body.obj");
	CPlayer::m_Rabit_Body->LoadTexture(".\\Texture\\Rabit_Body.bmp");
	CPlayer::m_Rabit_Body->LoadTexture(".\\Texture\\Rabit_Body_Dead.bmp");
	CPlayer::m_Rabit_Body->LoadTexture(".\\Texture\\Rabit_Body_Fall.bmp");
	m_Rabit_Body->MovePivot(CVector3D<>(0, -20, 10));
}

void CPlayer::InitEar()
{
	if (CPlayer::m_Rabit_Ear != nullptr) return;

	CPlayer::m_Rabit_Ear = new CObjModel;
	CPlayer::m_Rabit_Ear->LoadObj(".\\OBJModel\\Rabit_Ear.obj");
	CPlayer::m_Rabit_Ear->LoadTexture(".\\Texture\\Rabit_Ear.bmp");
	m_Rabit_Ear->MovePivot(CVector3D<>(0, -37, -20));
}

void CPlayer::InitLeftFoot()
{
	if (CPlayer::m_Rabit_LeftFoot != nullptr) return;

	CPlayer::m_Rabit_LeftFoot = new CObjModel;
	CPlayer::m_Rabit_LeftFoot->LoadObj(".\\OBJModel\\Rabit_LeftFoot.obj");
	CPlayer::m_Rabit_LeftFoot->LoadTexture(".\\Texture\\Rabit_LeftFoot.bmp");
	m_Rabit_LeftFoot->MovePivot(CVector3D<>(0, -10, 10));
}

void CPlayer::InitRightFoot()
{
	if (CPlayer::m_Rabit_RightFoot != nullptr) return;

	CPlayer::m_Rabit_RightFoot = new CObjModel;
	CPlayer::m_Rabit_RightFoot->LoadObj(".\\OBJModel\\Rabit_RightFoot.obj");
	CPlayer::m_Rabit_RightFoot->LoadTexture(".\\Texture\\Rabit_RightFoot.bmp");
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
