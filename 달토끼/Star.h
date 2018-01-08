#pragma once
class CStar
{
	CVector3D<float> m_RGB;
	CVector3D<float> m_StartRGB;
	CVector3D<float> m_EndRGB;

	CVector3D<> m_Pos;

	float m_Time{ 0.f };

public:
	CStar();
	~CStar();
	void Initialize();
	void RandomPosZ(const int& z);

	void Render();
	void Update();
};

