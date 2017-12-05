#pragma once
class CLighting
{
	GLfloat m_AmbientLight[4]{ 1.f, 1.f, 1.f, 1.f };
	GLfloat m_DiffuseLight[4]{};
	GLfloat m_SpecularLight[4]{};
	GLfloat m_specref[4]{1.f, 1.f, 1.f, 1.f};

	CVector3D m_LightPos;

public:
	CLighting();
	~CLighting();
};

