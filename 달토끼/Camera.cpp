#include "pch.h"
#include "Mediator.h"
#include "Camera.h"


void CCamera::Animation_PlayerDead()
{
	if (!isPlayerDead) return;

	float max_v = 180 * PI / 180.f;
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

CCamera::CCamera(CMediator *& mediator)
{
	m_aspect = glutGet(GLUT_WINDOW_WIDTH) / static_cast<float>(glutGet(GLUT_WINDOW_HEIGHT));
	m_Mediator = mediator;
}

void CCamera::Initialize(const CVector3D & at, float distance, float zNear, float zFar, float fov)
{
	m_fovy = fov;
	m_near = zNear;
	m_far = zFar;
	m_distance = distance;
	m_at = at;
}

void CCamera::SetPosition(const CVector3D & at)
{
	m_at = at;
	LookAt();
}

void CCamera::SetPosition(CVector3D && at) noexcept
{
	m_at = std::move(at);
	LookAt();
}

void CCamera::Move(const CVector3D & at) noexcept
{
	SetPosition(m_at + at);
}

void CCamera::Move(CVector3D && at) noexcept
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

	CVector3D vEye{ eye() };

	gluPerspective(m_fovy, m_aspect, m_near, m_far);
	
	gluLookAt(
		vEye[0], vEye[1], vEye[2],
		m_at[0], m_at[1], m_at[2],
		m_up[0], m_up[1], m_up[2]
	);

	glMatrixMode(GL_MODELVIEW);
}


CVector3D CCamera::GetLookVector() const
{
	CVector3D temp
	{
		cos(m_horizontal) * sin(m_vertical),
		sin(m_horizontal),
		cos(m_horizontal) * cos(m_vertical)
	};
	temp.Normalize();

	return temp;
}


CVector3D CCamera::eye() const
{
	return GetLookVector() * m_distance + GetPosition();
}

void CCamera::Update()
{
	if (!isAnimate) return;

	Animation_PlayerDead();
}

void CCamera::Player_JumpStart()
{
}

void CCamera::Player_Jumping(const CVector3D& move)
{
	Move(move);
}

void CCamera::Player_JumpFinish()
{

}

void CCamera::Player_Dead()
{
	isPlayerDead = true;
	isAnimate = true;
}


