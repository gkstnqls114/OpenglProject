#pragma once
#include "Colleague.h"
#include "Vector3D.h"

class CMediator;

class CCamera : public CColleague
{
	CVector3D m_at{ 0.f, 0.f, 0.f };
	CVector3D m_up{ 0.f, 1.f,0.f };

	float m_distance{ 0 };

	//각도
	float m_vertical{ 0 };
	float m_horizontal{ 0 };

	float m_aspect{ 0 };
	float m_near{ 0.f };
	float m_far{ 1.f };
	float m_fovy{ 0 };

	const double PI{ 3.141592 };
	
	CMediator* m_Mediator{ nullptr };

	//Camera Animation
	bool isPlayerDead{ false };

private:
	void Animation_PlayerDead();

public:
	CCamera(CMediator*& mediator);
		// 카메라 생성 시 최초 1회는 aspect를 자동으로 설정한다.

	~CCamera() = default;

	void Initialize(const CVector3D & pos, float distance, float zNear, float zFar, float fov);

	void SetAspect(float aspect) { m_aspect = aspect; }
	CVector3D GetPosition()	const { return m_at; }

	void SetPosition(const CVector3D& at) { m_at = at; LookAt(); }
	void SetPosition(CVector3D&& at)	noexcept { m_at = std::move(at); LookAt(); }
	void Move(const CVector3D& at)	noexcept { SetPosition(m_at + at); }
	void Move(CVector3D&& at)		noexcept { SetPosition(m_at + std::move(at)); }

	void SetDistance(const float& d) { m_distance = fmax(d, m_near); }
	float GetDistance() const { return m_distance; }
	
	void zoom(float per) { m_distance = m_distance * per; }

	void Rotate(float v, float h);
	void Rotate(int degree_v, int degree_h);

	void LookAt() const;

	CVector3D GetLookVector() const;

	CVector3D eye() const;


	//Mediator
	void Update();

	virtual void Player_JumpStart();
	virtual void Player_Jumping(const CVector3D& move);
	virtual void Player_JumpFinish();
	virtual void Player_Dead();
};
