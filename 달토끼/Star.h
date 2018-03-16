#pragma once
#include "Item.h"

class CObjModel;

class Star :
	public Item
{
	int m_Side{ k_front };
	CVector3D<GLdouble>	m_Pos;
	static CObjModel* m_ObjModel;

public:
	Star();
	virtual ~Star();

	static void InitModel();

	virtual void Update();
	virtual void Render();
	virtual void Set_Pos(const CVector3D<>& pos) override;// { m_Pos = pos; };
	virtual const CVector3D<> Get_Pos() const { return m_Pos; };
   //virtual void Set_Pos(CVector3D<>&& pos) override { m_Pos = pos; };
};

