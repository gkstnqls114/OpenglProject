#pragma once
#include "Item.h"

class CObjModel;

class Carrat :
	public Item
{
	static CObjModel* m_ObjModel	;

public:
	Carrat(const int& boardnum);
	virtual ~Carrat();

	static void InitModel();

	virtual void Update();
	virtual void Render();
	virtual void Set_Pos(const CVector3D<>& pos) override { m_Pos = pos; };
};
