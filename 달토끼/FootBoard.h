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
	//c++�� static storage duration ���� ��ü��
	//0�� �����մϴ�.
	//ǥ���� ����, ���������� 0���� �ʱ�ȭ���� ����մϴ�.
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

	//������
	float DisappearTime{ 0.f };
	bool isDisappear{ false };
	
private:
	//�����Լ�
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



