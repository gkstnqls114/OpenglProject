#pragma once
#include "Item.h"

class CObjModel;

class Star :
	public Item
{
	static CObjModel* m_ObjModel;

private:
	virtual void Render_Model();

public:
	Star();
	virtual ~Star();

	static void InitModel();

};

