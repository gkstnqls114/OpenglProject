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
