#pragma once
#include "Item.h"

class CObjModel;

class Shield :
	public Item
{
	int m_Side { k_front };
	CVector3D<GLdouble>	m_Pos; 
	static CObjModel* m_ObjModel;

public:
	Shield();
	virtual ~Shield();

	static void InitModel();

	virtual void Update();
	virtual void Render();
	virtual void Set_Pos(const CVector3D<>& pos) override;
	virtual const CVector3D<> Get_Pos() const { return m_Pos; };

};

