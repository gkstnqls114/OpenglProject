#pragma once

class CObjModel;
class RotateMatrix;

class CFootBoard
{
	CVector3D<> m_Pos			{ 0, -5, 0 };
	
	//c++은 static storage duration 가진 객체는
	//0을 보장합니다.
	//표준은 전역, 정적변수는 0으로 초기화함을 명시합니다.
	//static bool isInitModel;
	static CObjModel* m_obj;
	static CObjModel* m_Light_obj;

	bool IsLast						{ false };
	bool IsLightDisappear			{ false };

	float		m_TextureAlpha		{1.f};
	const float m_DropAlphaUnit		{ 0.3f };
	//float		m_LightAlpha{ 0.5f };

	RotateMatrix* m_Matrix{ nullptr };

	//움직임
	float DisappearTime{ 0.f };
	bool IsDisappear{ false };
	
	bool m_IsExisted{ false }; /* false라면 그리지도 않고 업데이트도 하지않습니다. */

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



