#pragma once
#include "Item.h"
class Spacestar
{
	CVector3D<float> m_RGB;
	CVector3D<float> m_StartRGB;
	CVector3D<float> m_EndRGB;

	CVector3D<> m_Pos;

	float m_Time{ 0.f };

public:
	Spacestar();
	~Spacestar();
	void Initialize();
	void RandomPosZ(const int& z);

	void Render();
	void Update();
};
