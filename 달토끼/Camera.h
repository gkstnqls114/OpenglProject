#pragma once
#include "Vector.h"

class CCamera
{
	CVector m_at{ 0.f, 0.f, 0.f };
	CVector m_up{ 0.f, 1.f, 0.f };

	float m_distance{ 0 };

	float m_vertical{ 0 };
	float m_horizontal{ 0 };

	float m_aspect{ 0 };
	float m_near{ 0.f };
	float m_far{ 1.f };
	float m_fovy{ 0 };

	const float PI = 3.14;

public:
	CCamera()
		// 카메라 생성 시 최초 1회는 aspect를 자동으로 설정한다.
		: m_aspect{ glutGet(GLUT_WINDOW_WIDTH) / static_cast<float>(glutGet(GLUT_WINDOW_HEIGHT)) }
	{
	}

	~CCamera() = default;

	void Initialize(const CVector & pos, float distance, float zNear, float zFar, float fov)
	{
		m_fovy = fov;
		m_near = zNear;
		m_far = zFar;
		m_distance = distance;
		m_at = pos;
	}

	void SetAspect(float aspect) { m_aspect = aspect; }
	CVector GetPosition()	const { return m_at; }

	void SetPosition(const CVector& pos) { m_at = pos; LookAt(); }
	void SetPosition(CVector&& pos)	noexcept { m_at = std::move(pos); LookAt(); }
	void Move(const CVector& pos)	noexcept { SetPosition(m_at + pos); }
	void Move(CVector&& pos)		noexcept { SetPosition(m_at + std::move(pos)); }

	void SetDistance(const float& d) { m_distance = fmax(d, m_near); }
	float GetDistance() const { return m_distance; }

	void zoom(float per) { m_distance = m_distance * per; }

	void Rotate(float v, float h)
	{
		m_vertical += v;
		if (-PI * 0.5f < m_horizontal + h && m_horizontal + h < PI * 0.5f)
			m_horizontal += h;
	}

	void LookAt() const
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

		std::cout << "EYE: " << vEye.x << " , " << vEye.y << " , " << vEye.z << std::endl;

		std::cout << "AT: " << m_at.x << " , " << m_at.y << " , " << m_at.z << std::endl;

		std::cout << "UP: " << m_up.x << " , " << m_up.y << " , " << m_up.z << std::endl;

	
		glMatrixMode(GL_MODELVIEW);
	}

	CVector GetLookVector() const
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

	CVector eye() const
	{
		CVector temp = GetLookVector();
		std::cout << "EYE TEMP: " << temp.x << " , " << temp.y << " , " << temp.z << std::endl;
		
		temp = temp * m_distance;
		std::cout << "EYE TEMP: " << temp.x << " , " << temp.y << " , " << temp.z << std::endl;

		temp = temp + GetPosition();
		std::cout << "EYE TEMP: " << temp.x << " , " << temp.y << " , " << temp.z << std::endl;

		//return GetLookVector() * m_distance + GetPosition();
		return temp;
	}

};
