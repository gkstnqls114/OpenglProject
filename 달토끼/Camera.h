#pragma once
#include "Vector.h"

class CCamera
{
	CVector m_at{ 0.f, 0.f, 0.f };
	CVector m_up{ 0.f, 1.f, 0.f };

	float m_distance{ 0 };

	//각도
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

	void Initialize(const CVector & pos, float distance, float zNear, float zFar, float fov);

	void SetAspect(float aspect) { m_aspect = aspect; }
	CVector GetPosition()	const { return m_at; }

	void SetPosition(const CVector& at) { m_at = at; LookAt(); }
	void SetPosition(CVector&& at)	noexcept { m_at = std::move(at); LookAt(); }
	void Move(const CVector& at)	noexcept { SetPosition(m_at + at); }
	void Move(CVector&& at)		noexcept { SetPosition(m_at + std::move(at)); }

	void SetDistance(const float& d) { m_distance = fmax(d, m_near); }
	float GetDistance() const { return m_distance; }
	
	void zoom(float per) { m_distance = m_distance * per; }

	void Rotate(float v, float h);

	void LookAt() const;

	CVector GetLookVector() const;

	CVector eye() const;
};
