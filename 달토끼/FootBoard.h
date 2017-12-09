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
	//static bool isInitModel;

	int m_Side{ -2 }; //-2는 존재하지 않음

	CVector3D<> m_Position{ 0, -5, 0 };

	CVector3D<float, 4>			m_TextureRGBA{1.f, 1.f, 1.f};


	GLfloat m_Translate_Matrix[16] =
	{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
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
	bool IsDisappear{ false };
	
private:
	//내부함수
	void Disappear();
	void RenderModel();

public:
	CFootBoard();
	~CFootBoard();
	static void InitModel();
	static void DeleteModel();
	void InitPosition(const int& x, const int & y, const int& z);
	void InitPosition(const CVector3D<>& rhs);

	void Render();
	void Update();

	const CVector3D<> GetPos() const noexcept { return m_Position; }
	const bool GetDisappear() const { return IsDisappear; }
	const int GetSide() const noexcept { return m_Side; }

	void Init_GameScene();
};



