#pragma once

class CObjModel;


namespace {
	CObjModel* m_obj;
}
//음.. 으음 ; _;
//static보다 요게 최신방법이래..
//근데 졸려서 일단 패쓰..

class CFootBoard
{
	static CObjModel* m_obj;
	//c++은 static storage duration 가진 객체는
	//0을 보장합니다.
	//표준은 전역, 정적변수는 0으로 초기화함을 명시합니다.
	static bool isInitModel;

	float m_x{ 0 };
	float m_y{ 0 };
	float m_z{ 0 };
	float m_floor{ m_y };

	float m_r{ 0.f };
	float m_g{ 0.f };
	float m_b{ 0.f };

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
	float DisappearTime{ 0.f };
	bool isDisappear{ false };
	
private:
	//내부함수
	void Disappear();
	void RenderModel();


public:
	CFootBoard();
	~CFootBoard();
	static void InitModel();
	static void DeleteModel();

	void Render();
	void Update();

	void Translate(const float& x, const float & y, const float& z);
};



