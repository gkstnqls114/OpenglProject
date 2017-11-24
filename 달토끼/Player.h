#pragma once

class CObjModel;
class CMatrix;
class CVector3D;
class CMessageSender;
class CMediator;
class CRoad;
class CCamera;

class CPlayer
{
	CObjModel* m_RabitBody{ nullptr };
	CObjModel* m_RabitFoot{ nullptr };

	CMatrix* m_Matrix{nullptr};

	CMediator* m_Mediator{nullptr};

	//점프변수들
	//jump property
	const float k_gravity{ 0.7f };
	const double k_PI{ 3.14152 };
	const int m_JumpDegree{ 70 };
	const float m_power{ 5.f };
	int m_FinishJumpTime{ 0 };
	GLdouble m_JumpReach{0};

	bool IsJump{ false };
	bool IsRight{ false };
	bool IsLeft{ false };
	int m_JumpTime{ 0 };
	GLdouble m_vector_x{ 0 };
	GLdouble m_vector_y{ 0 };
	GLdouble m_vector_z{ 0 };
	
	bool isDead{ false };

	//현재 발판 넘버
	int m_BoardNum{ 0 };
	int m_MySide{ 0 };

	

private:
	void Find_JumpProperty();
	void Jump();
	void Calculate_JumpVector();
	void Reset_JumpProperty();
	void Finish_Jump();

public:
	CPlayer(CMediator*& mediator);
	~CPlayer();

	void Keyboard(const unsigned char& key, const int& x, const int& y);
	void SpecialKeys(const int& key, const int& x, const int& y);
	void Update();
	void Render();

	float Get_VectorX() const noexcept { return m_vector_x; }
	float Get_VectorY() const noexcept { return m_vector_y; }
	float Get_VectorZ() const noexcept { return m_vector_z; }

	const float Get_JumpReach() const noexcept { return m_JumpReach; }
	const int Get_BoardNum() const noexcept { return m_BoardNum; }
	const int Get_Side() const noexcept { return m_MySide; }

	//Mediator
	virtual void Player_JumpStart();
	virtual void Player_Jumping();
	virtual void Player_JumpFinish();
	virtual void Player_Dead();
};

