#include "pch.h"
#include "Star.h"


CStar::CStar()
{
	CVector3D<float, 3> RandStart(
		float(rand() % 156 + 100) / 255.f,
		float(rand() % 156 + 100) / 255.f,
		float(rand() % 156 + 100) / 255.f
	);

	m_StartRGB = RandStart;
		
	CVector3D<float, 3> RandEnd(
		float(rand() % 156 + 100) / 255.f,
		float(rand() % 156 + 100) / 255.f,
		float(rand() % 156 + 100) / 255.f
	);
	m_EndRGB = RandEnd;
		
	m_RGB = m_StartRGB;

	m_Pos = CVector3D<>(
		rand() % 300 - 150,
		rand() % 300 - 150,
		rand() % 300 - 150
		);
}


CStar::~CStar()
{
}

void CStar::Initialize()
{
}

void CStar::RandomPosZ(const int & z)
{
	m_Pos[2] = -(rand() % (abs(z) + 400) - 200);
}

void CStar::Render()
{
	glColor3f(m_RGB[0], m_RGB[1], m_RGB[2]);
	glPushMatrix();
	glTranslated(m_Pos[0], m_Pos[1], m_Pos[2]);
	glutSolidSphere(1, 5, 5);
	glPopMatrix();
}

void CStar::Update()
{
	m_Time += 0.01f;
	if (m_Time >= 1.f) {
		m_Time = 0.f;
		m_StartRGB = m_EndRGB;
		CVector3D<float, 3> RandEnd(
			float(rand() % 156 + 100) / 255.f,
			float(rand() % 156 + 100) / 255.f,
			float(rand() % 156 + 100) / 255.f
		);
		
		m_EndRGB = RandEnd;
	}

	m_RGB[0] = Interpolation(m_StartRGB[0], m_EndRGB[0], m_Time);
	m_RGB[1] = Interpolation(m_StartRGB[1], m_EndRGB[1], m_Time);
	m_RGB[2] = Interpolation(m_StartRGB[2], m_EndRGB[2], m_Time);
}
