#include "pch.h"
#include "Collision.h"
#include "Item.h"
ItemEffectManager* Item::m_pItemEffectManager{ nullptr };
const int Item::MaxRadius{ 40 };

void Item::Render_All()
{
	glPushMatrix();
	glTranslatef(m_Pos.x, m_Pos.y, m_Pos.z);
	glMultMatrixf(m_Rotate_Matrix);

	Render_Model();
	
	glPopMatrix();
}

void Item::Render_Sphere()
{
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glColor4f(0.8f, 0.8f, 1.f, 0.3f);
	glutSolidSphere(m_sphereRadius, 10, 10);

	glDisable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
}

Item::Item()
{
	StateChange_Float();
}

Item::~Item()
{
}

void Item::Update()
{
	m_ItemState->Update(*this);
}

void Item::Render()
{
	m_ItemState->Render(*this);
}

void Item::Set_Pos(const CVector3D<>& rhs)
{
	m_Pos = rhs;
}

//터짐 변수를 true로 만들고 아이템 효과를 쓴다.
void Item::IsCollided()
{ 
	m_IsCollide = true;
	ItemEffect();
}

//터지는 애니메이션 업데이트를 수행합니다.
void Item::Pop()
{
	m_sphereRadius += 1;
	
	bool IsBig = m_sphereRadius > MaxRadius;
	if (IsBig) {
		StateChange_BeUsed();
	}
}

//둥실둥실 떠다니는 애니메이션 업데이트를 수행합니다.
void Item::Float()
{
	m_Time += 0.02f;
	if (m_Time >= 1.f) {
		m_Time = 0.f;
		m_BeginY = m_EndY;
		m_EndY = -m_EndY;
	}

	GLdouble MoveY = Interpolation(m_BeginY, m_EndY, m_Time);
	m_Pos.y += MoveY;
}
