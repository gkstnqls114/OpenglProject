#include "pch.h"
#include "Mediator.h"
#include "Camera.h"


void CCamera::Animation_PlayerDead()
{
	if (!isPlayerDead) return;

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
		vEye.x, vEye.y, vEye.z,
		m_at.x, m_at.y, m_at.z,
		m_up.x, m_up.y, m_up.z
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
}

void CCamera::Player_JumpFinish()
{
	std::cout << "Camera: 플레이어 점프 확인" << std::endl;
}

void CCamera::Player_Dead()
{
	std::cout << "Camera: 플레이어 죽음 확인" << std::endl;
}

void CCamera::Road_playerBoard_Disapper()
{
	std::cout << "Camera: 플레이어 보드 사라짐 확인" << std::endl;
}


