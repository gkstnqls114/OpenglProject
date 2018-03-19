#pragma once

class CObjModel;
class RotateMatrix;

class CFootBoard
{
	CVector3D<> m_Pos			{ 0, -5, 0 };
	
	//c++�� static storage duration ���� ��ü��
	//0�� �����մϴ�.
	//ǥ���� ����, ���������� 0���� �ʱ�ȭ���� ����մϴ�.
	//static bool isInitModel;
	static CObjModel* m_obj;
	static CObjModel* m_Light_obj;

	bool IsLast						{ false };
	bool IsLightDisappear			{ false };

	float		m_TextureAlpha		{1.f};
	const float m_DropAlphaUnit		{ 0.3f };
	//float		m_LightAlpha{ 0.5f };

	RotateMatrix* m_Matrix{ nullptr };

	//������
	float DisappearTime{ 0.f };
	bool IsDisappear{ false };
	
	bool m_IsExisted{ false }; /* false��� �׸����� �ʰ� ������Ʈ�� �����ʽ��ϴ�. */

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

	///////////////////////////////// Get
	const CVector3D<> Get_Pos() const noexcept { return m_Pos; }
	const bool GetDisappear() const { return IsDisappear; }
	const bool Get_IsExisted() const noexcept{ return m_IsExisted; }
	///////////////////////////////// Get

	void Disappear_True() { IsDisappear = true; }
	void IsExisted() { m_IsExisted = true; }
};



