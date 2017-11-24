#include "pch.h"
#include "MyRGB.h"


CMyRGB::CMyRGB()
{
}


CMyRGB::~CMyRGB()
{
}

void CMyRGB::ColorSelect()
{
	glColor4f(m_r, m_g, m_b, m_a);
}

void CMyRGB::Disappear()
{
	m_a -= 0.001f;
}
