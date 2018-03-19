#pragma once
#include "Item.h"

class CObjModel;

class Carrot :
	public Item
{
	static CObjModel* m_ObjModel	;

private:
	virtual void ItemEffect();
	virtual void Render_Model();

public:
	Carrot();
	virtual ~Carrot();

	static void InitModel();
};
