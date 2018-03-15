#pragma once
#include "Item.h"

class CObjModel;

class Shield :
	public Item
{
	static CObjModel* m_ObjModel;

public:
	Shield();
	virtual ~Shield();

	static void InitModel();

	virtual void Update();
	virtual void Render();
	virtual void Set_Pos(const CVector3D<>& pos) override { m_Pos = pos; };
};

