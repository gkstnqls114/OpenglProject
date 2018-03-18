#include "pch.h"
#include "Item.h"


void Item::Render_Sphere()
{
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glColor4f(1.f, 1.f, 1.f, 0.5f);
	glutSolidSphere(30, 10, 10);

	glDisable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
}

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

	Render_Model();
	Render_Sphere();

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
