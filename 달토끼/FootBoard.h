#pragma once

class CObjModel;


namespace {
	CObjModel* m_obj;
}
//��.. ���� ; _;
//static���� ��� �ֽŹ���̷�..
//�ٵ� ������ �ϴ� �о�..

class CFootBoard
{
	static CObjModel* m_obj;
	static CObjModel* m_Light_obj;
	//c++�� static storage duration ���� ��ü��
	//0�� �����մϴ�.
	//ǥ���� ����, ���������� 0���� �ʱ�ȭ���� ����մϴ�.
	//static bool isInitModel;

	int m_Side{ -2 }; //-2�� �������� ����

	CVector3D<> m_Position{ 0, -5, 0 };
	bool IsLast{ false };
	bool IsLightDisappear{ false };

	float		m_TextureAlpha {1.f};
	float		m_LightAlpha{ 0.5f };

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

	//������
	float DisappearTime{ 0.f };
	bool IsDisappear{ false };
	
private:
	//�����Լ�
	void Disappear();
	void RenderModel();

public:
	CFootBoard();
	~CFootBoard();
	static void InitModel();
	static void DeleteModel();
	void InitPosition(const int& x, const int & y, const int& z);
	void InitPosition(const CVector3D<>& rhs);
	void InitPosition(CVector3D<>&& rhs);
	void IsLight();
	void IsNotLight();
	void LightDisappear();

	void Render();
	void Update();

	const CVector3D<> GetPos() const noexcept { return m_Position; }
	const bool GetDisappear() const { return IsDisappear; }
	const int GetSide() const noexcept { return m_Side; }

	void Init_GameScene();

};



