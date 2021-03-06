#include "pch.h"
#include "Spacestar.h"

#define MAXPOS 200

Spacestar::Spacestar()
{
	CVector3D<float> RandStart(
		float(rand() % 156 + 100) / 255.f,
		float(rand() % 156 + 100) / 255.f,
		float(rand() % 156 + 100) / 255.f
	);

	m_StartRGB = RandStart;
		
	CVector3D<float> RandEnd(
		float(rand() % 156 + 100) / 255.f,
		float(rand() % 156 + 100) / 255.f,
		float(rand() % 156 + 100) / 255.f
	);
	m_EndRGB = RandEnd;
		
	m_RGB = m_StartRGB;

	m_Pos = CVector3D<>(
		rand() % (MAXPOS * 2) - MAXPOS, // -MAXPOS ~ MAXPOS 
		rand() % (MAXPOS * 2) - MAXPOS, 
		rand() % (MAXPOS * 2) - MAXPOS
		);
}


Spacestar::~Spacestar()
{
}

void Spacestar::Initialize()
{
}

void Spacestar::RandomPosZ(const int & z)
{
	m_Pos.z = -(rand() % (abs(z) + 400) - 200);
}

void Spacestar::Render()
{
	glColor3f(m_RGB.x, m_RGB.y, m_RGB.z);
	glPushMatrix();
	glTranslated(m_Pos.x, m_Pos.y, m_Pos.z);
	glutSolidSphere(1, 3, 3);
	glPopMatrix();
}

void Spacestar::Update()
{
	m_Time += 0.01f;
	if (m_Time >= 1.f) {
		m_Time = 0.f;
		m_StartRGB = m_EndRGB;
		CVector3D<float> RandEnd(
			float(rand() % 156 + 100) / 255.f,
			float(rand() % 156 + 100) / 255.f,
			float(rand() % 156 + 100) / 255.f
		);
		
		m_EndRGB = RandEnd;
	}

	m_RGB.x = Interpolation(m_StartRGB.x, m_EndRGB.x, m_Time);
	m_RGB.y = Interpolation(m_StartRGB.y, m_EndRGB.y, m_Time);
	m_RGB.z = Interpolation(m_StartRGB.z, m_EndRGB.z, m_Time);
}

