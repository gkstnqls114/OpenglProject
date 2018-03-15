#pragma once
#include "Item.h"
class NullItem :
	public Item
{
public:
	NullItem();
	virtual ~NullItem();

	virtual void Update() override { /*do nothing*/ };
	virtual void Render() override { /*do nothing*/ };
	virtual void Set_Pos(const CVector3D<>& pos) override { m_Pos = pos; };

};

