#pragma once

class CObjModel;

class CPlayer
{
	CObjModel* m_rabit{ nullptr };
	int m_x{ 0 };
	int m_y{ 0 };
	int m_z{ 0 };

	GLfloat m_Translate_Matrix[16] =
	{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		300, 300, 0, 1,
	};

	GLfloat m_Scale_Matrix[16] =
	{
		3, 0, 0, 0,
		0, 3, 0, 0,
		0, 0, 3, 0,
		0, 0, 0, 1,
	};

	GLfloat m_Rotate_Matrix[16] =
	{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1,
	};

	int JumpTime = 0;
	bool IsJump{ false };
	bool IsRight{ false };
	bool IsLeft{ false };


public:
	CPlayer();
	~CPlayer();

	void Keyboard(const unsigned char& key, const int& x, const int& y);
	void Update();
	void Render();

	void Jump();
};

