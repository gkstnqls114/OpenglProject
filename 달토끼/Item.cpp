#include "pch.h"
#include "Item.h"


Item::Item()
{
}

Item::~Item()
{
}

void Item::Render()
{
	glPushMatrix();
	glTranslatef(m_Pos.x, m_Pos.y, m_Pos.z);
	glMultMatrixf(m_Rotate_Matrix);

	ModelRender();

	glPopMatrix();
}

void Item::Set_Pos(const CVector3D<>& rhs)
{
	if (rhs.x < 0) {
		m_Side = k_left;
	}
	else if (rhs.x > 0) {
		m_Side = k_right;
	}
	else {
		m_Side = k_front;
	}

	m_Pos = rhs;
}
