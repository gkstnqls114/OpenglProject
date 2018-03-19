#pragma once
/////////////////////// Item State
#include "Pop.h"
#include "BeUsed.h"
#include "Float.h"
/////////////////////// Item State

#include "PlayerObserver.h"

class ItemState;
class ItemEffectManager;

class Item
{
protected:
	static ItemEffectManager* m_pItemEffectManager;
	static const int MaxRadius;
	int m_sphereRadius{ 30 };

	/////////////////////// Item State
	ItemState* m_ItemState{ nullptr };
	Pop		   PopState;
	BeUsed	   BeUsedState;
	Float	   FloatState;
	/////////////////////// Item State

	GLdouble m_BeginY{ 0 };
	GLdouble m_EndY{ 1.f };
	
	bool m_IsCollide{ false };

	int m_Side{ k_FrontIndex };
	CVector3D<GLdouble>	m_Pos;
	float m_Time{ 0 };

	GLfloat m_Scale_Matrix[16] =
	{
		1.f, 0, 0, 0,
		0, 1.f, 0, 0,
		0, 0, 1.f, 0,
		0, 0, 0, 1.f
	};

	GLfloat m_Rotate_Matrix[16] =
	{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};

private:
	void Render_Sphere();
	virtual void Render_Model() = 0;
	virtual void ItemEffect() = 0;

public:
	Item();
	virtual ~Item();
	static void Set_pItemEffectManager(ItemEffectManager& manager) {
		m_pItemEffectManager = &manager;
	}

	void Update();
	void Render();
	void Render_All();

	void Set_Pos(const CVector3D<>& pos);
	void IsCollided();

	/////////////////////////////////// Get
	const CVector3D<> Get_Pos() const { return m_Pos; };
	const int Get_sphereRadius() const { return m_sphereRadius; };
	const bool Get_Collide() const { return m_IsCollide; }
	/////////////////////////////////// Get

	/////////////////////////////////// State
	void StateChange_Pop() { m_ItemState = &PopState; };
	void StateChange_Float() { m_ItemState = &FloatState; };
	void StateChange_BeUsed() { m_ItemState = &BeUsedState; };

	void Pop();
	void Float();
	/////////////////////////////////// State

};

