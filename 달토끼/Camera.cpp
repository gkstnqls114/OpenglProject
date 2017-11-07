#include "pch.h"
#include "Camera.h"

void CCamera::Initialize(const CVector & at, float distance, float zNear, float zFar, float fov)
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

void CCamera::LookAt() const
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	CVector vEye{ eye() };

	gluPerspective(m_fovy, m_aspect, m_near, m_far);

	gluLookAt(
		vEye.x, vEye.y, vEye.z,
		m_at.x, m_at.y, m_at.z,
		m_up.x, m_up.y, m_up.z
	);

	glMatrixMode(GL_MODELVIEW);
}

CVector CCamera::GetLookVector() const
{

	CVector temp
	{
		cos(m_horizontal) * sin(m_vertical),
		sin(m_horizontal),
		cos(m_horizontal) * cos(m_vertical)
	};
	temp.Normalize();

	return temp;
}

CVector CCamera::eye() const
{
	CVector temp = GetLookVector();
	
	temp = temp * m_distance;
	
	temp = temp + GetPosition();
	
	//return GetLookVector() * m_distance + GetPosition();
	return temp;
}
