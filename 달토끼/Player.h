#pragma once

class CObjModel;

class CPlayer
{
	CObjModel* m_rabit{ nullptr };
	float m_x{ 0 };
	float m_y{ 0 };
	float m_z{ 0 };
	float m_floor{ m_y };

	GLfloat m_Translate_Matrix[16] =
	{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		m_x, m_y, m_z, 1
	};

	GLfloat m_Scale_Matrix[16] =
	{
		0.3f, 0, 0, 0,
		0, 0.3f, 0, 0,
		0, 0, 0.3f, 0,
		0, 0, 0, 1.f
	};

	GLfloat m_Rotate_Matrix[16] =
	{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};

	//움직임
	bool IsJump{ false };
	bool IsRight{ false };
	bool IsLeft{ false };
	bool isDead{ false };

	//포물선 운동 위한..
	float m_gravitation_acceleration{ 0.98f };
	float JumpTime{ 0.f };
	float m_power{ 10.f };
	int m_jump_degree{ 70 };
	float m_vector_x{ 0 };
	float m_vector_y{ 0 };
	float m_vector_z{ 0 };
	const double k_PI{ 3.141592 };
	
	//수평도달거리
	int m_JumpReach{0};

private:
	void Jump();

public:
	CPlayer();
	~CPlayer();

	void Keyboard(const unsigned char& key, const int& x, const int& y);
	void SpecialKeys(const int& key, const int& x, const int& y);
	void Update();
	void Render();

	float Get_VectorX() const noexcept { return m_vector_x; }
	float Get_VectorY() const noexcept { return m_vector_y; }
	float Get_VectorZ() const noexcept { return m_vector_z; }

	float Get_JumpReach() const noexcept { return m_JumpReach; }
};

