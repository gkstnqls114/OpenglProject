#pragma once

class CObjModel;
class RotateMatrix;

class CFootBoard
{
	static CObjModel* m_obj;
	static CObjModel* m_Light_obj;

	//c++�� static storage duration ���� ��ü��
	//0�� �����մϴ�.
	//ǥ���� ����, ���������� 0���� �ʱ�ȭ���� ����մϴ�.
	//static bool isInitModel;

	int m_Side{ -2 }; //-2�� �������� ����

	CVector3D<> m_Pos			{ 0, -5, 0 };
	bool IsLast						{ false };
	bool IsLightDisappear			{ false };

	float		m_TextureAlpha		{1.f};
	const float m_DropAlphaUnit		{ 0.3f };
	//float		m_LightAlpha{ 0.5f };

	RotateMatrix* m_Matrix{ nullptr };

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
	void HasLight();
	void IsNotLight();
	void LightDisappear();

	void Render();
	void Update();

	const CVector3D<> Get_Pos() const noexcept { return m_Pos; }
	const bool GetDisappear() const { return IsDisappear; }
	void Disappear_True() { IsDisappear = true; }
	const int GetSide() const noexcept { return m_Side; }

};



