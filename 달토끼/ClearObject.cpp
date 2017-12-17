#include "pch.h"
#include "ObjModel.h"
#include "ClearObject.h"


CClearObject::CClearObject()
{
	m_ClearMoon = new CObjModel;
	m_ClearMoon->LoadObj("ClearMoon.obj");
	m_ClearMoon->LoadTexture("ClearMoon.bmp");

	m_ClearRabbit = new CObjModel;
	m_ClearRabbit->LoadObj("ClearRabit.obj");
	m_ClearRabbit->LoadTexture("ClearRabit.bmp");

	m_ClearRabbitEar = new CObjModel;
	m_ClearRabbitEar->LoadObj("ClearRabitEar.obj");
	m_ClearRabbitEar->LoadTexture("ClearRabitEar.bmp");

	m_ClearSunglass = new CObjModel;
	m_ClearSunglass->LoadObj("ClearSunglass.obj");
	m_ClearSunglass->LoadTexture("ClearSunglass.bmp");

	m_ClearMartini = new CObjModel;
	m_ClearMartini->LoadObj("ClearMartini.obj");
	m_ClearMartini->LoadTexture("ClearMartini.bmp");
}


CClearObject::~CClearObject()
{
}

void CClearObject::Render()
{
	glPushMatrix();
	glTranslated(m_Position[0], m_Position[1], m_Position[2]);
	m_ClearMoon->Render();
	m_ClearRabbit->Render();
	m_ClearRabbitEar->Render();
	m_ClearSunglass->Render();
	m_ClearMartini->Render();
	glPopMatrix();
}

void CClearObject::Update()
{
	if (abs(rotatedegree) == 30) {
		IsClockRotate = !IsClockRotate;
	}

	if (IsClockRotate) {
		rotatedegree += 1;
		m_ClearMartini->Rotate(0.05f, 0, 0, 1);
	}
	else {
		rotatedegree -= 1;
		m_ClearMartini->Rotate(-0.05f, 0, 0, 1);
	}

}

void CClearObject::SetPos(const CVector3D<>& pos)
{
	m_Position = pos;
}

void CClearObject::SetPos(CVector3D<>&& pos)
{
	m_Position = pos;
}
