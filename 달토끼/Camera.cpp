#include "pch.h"
#include "SceneManager.h"
#include "Player.h"
#include "Camera.h"



void CCamera::Animation_GameClear()
{
	if (!isGameClear) return;

	float max_v = float(180 + Rotatedegree) * PI / 180.f;
	float max_h = 0 * PI / 180.f;

	bool verticalMove = m_vertical < max_v;
	if (verticalMove) {
		Rotate(1, 0);
	}

	bool horizontalMove = m_horizontal < max_h;
	if (horizontalMove) {
		Rotate(0, 1);
	}

	bool Far = m_distance > 50;
	if (Far) {
		zoom(0.99f);
	}

	LookAt();

	bool Finish = !Far && !verticalMove && !horizontalMove;
	if (Finish) {
		isAnimate = false;
	}
}

CCamera::CCamera()
{
	m_aspect = glutGet(GLUT_WINDOW_WIDTH) / static_cast<float>(glutGet(GLUT_WINDOW_HEIGHT));
}

void CCamera::Initialize(const CVector3D<> & at, float distance, float zNear, float zFar, float fov)
{
	m_fovy = fov;
	m_near = zNear;
	m_far = zFar;
	m_distance = distance;
	m_at = at;
	m_vertical = 0;
	m_horizontal = 0;
}


void CCamera::SetPosition(const CVector3D<> & at)
{
	m_at = at;
	LookAt();
}

void CCamera::SetPosition(CVector3D<> && at) noexcept
{
	m_at = std::move(at);
	LookAt();
}

void CCamera::Move(const CVector3D<> & at) noexcept
{
	SetPosition(m_at + at);
}

void CCamera::Move(CVector3D<> && at) noexcept
{
	SetPosition(m_at + std::move(at));
}


void CCamera::Rotate(float v, float h)
{
	m_vertical += v;
	if (-PI * 0.5f < m_horizontal + h && m_horizontal + h < PI * 0.5f)
		m_horizontal += h;
}

void CCamera::Rotate(int degree_v, int degree_h)
{
	float v = degree_v * PI / 180.f;
	float h = degree_h * PI / 180.f;
	m_vertical += v;
	if (-PI * 0.5f < m_horizontal + h && m_horizontal + h < PI * 0.5f)
		m_horizontal += h;
}


void CCamera::LookAt() const
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	CVector3D<> vEye{ eye() };

	gluPerspective(m_fovy, m_aspect, m_near, m_far);
	
	gluLookAt(
		vEye.x, vEye.y, vEye.z,
		m_at.x, m_at.y, m_at.z,
		m_up.x, m_up.y, m_up.z
	);

	glMatrixMode(GL_MODELVIEW);
}


CVector3D<> CCamera::GetLookVector() const
{
	CVector3D<> temp
	{
		cos(m_horizontal) * sin(m_vertical),
		sin(m_horizontal),
		cos(m_horizontal) * cos(m_vertical)
	};
	temp.Normalize();

	return temp;
}


CVector3D<> CCamera::eye() const
{
	return GetLookVector() * double(m_distance) + GetPosition();
}

void CCamera::Update()
{

}

void CCamera::Receive_PlayerJumping(CPlayer * player)
{
	CVector3D<> Move = player->Get_Pos();
	Move.y = 0;
	if (isMapCamera) Move.x = 0;
	SetPosition(Move);
}

void CCamera::Receive_PlayerWaitCamera(CPlayer * player)
{
	if (isMapCamera) return;
	float max_v = float(180 + Rotatedegree) * PI / 180.f;
	float max_h = 0 * PI / 180.f;

	bool verticalMove = m_vertical < max_v;
	if (verticalMove) {
		Rotate(3, 0);
	}

	bool horizontalMove = m_horizontal < max_h;
	if (horizontalMove) {
		Rotate(0, 3);
	}

	bool Far = m_distance > 150;
	if (Far) {
		zoom(0.99f);
	}

	LookAt();

	bool Finish = !Far && !verticalMove && !horizontalMove;
	if (Finish) {
		if (player->IsGameClear()) {
			CSceneManager::GetInstance()->ChangeToGameClear();
		}
		else {
			player->StateChange_Fall();
		}
	}
}

void CCamera::Init_FistPerspective()
{
	Initialize(CVector3D<>(0.f, 0.f, 0.f), 300, 0.1f, 1500.f, 60);
	Rotate(0, 20);
	LookAt();
}

void CCamera::Init_ThirdPerspective()
{
	Initialize(CVector3D<>(0.f, 0.f, 0.f), 300, 0.1f, 1500.f, 60);
	Rotate(25, 20);
	LookAt();
}

void CCamera::Init_MainScene()
{
	Initialize(CVector3D<>(0.f, 0.f, 0.f), 500, 0.1f, 1000.f, 60);
	Rotate(0, 0);
	LookAt();
}

void CCamera::Init_GameOver()
{
	Initialize(CVector3D<>(0.f, 0.f, 0.f), 100, 0.1f, 600.f, 60);
	Rotate(0, 10);
	LookAt();
}

void CCamera::Init_GameClear()
{
	Initialize(CVector3D<>(0.f, 0.f, 0.f), 300, 0.1f, 600.f, 60);
	Rotate(0, 10);
	LookAt();
}

void CCamera::Init_GameScene()
{
	Initialize(CVector3D<>(0.f, 0.f, 0.f), 300, 0.1f, 1500.f, 60);
	Rotate(25, 20);
	LookAt();
	isAnimate = false;
	isGameClear = false;
}

void CCamera::Player_Dead(const float& rotatedegree)
{
	Rotatedegree = rotatedegree;
	isAnimate = true;
}

void CCamera::Player_Clear(const float& rotatedegree)
{
	Rotatedegree = rotatedegree;
	isAnimate = true;
	isGameClear = true;
}


