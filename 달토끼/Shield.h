#pragma once
#include "Item.h"

class CObjModel;

class Shield :
	public Item
{
	static CObjModel* m_ObjModel;

private:
	virtual void Render_Model();

public:
	Shield();
	virtual ~Shield();

	static void InitModel();
	virtual void Update();

};

