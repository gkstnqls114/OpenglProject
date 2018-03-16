#pragma once
#include "Item.h"

class CObjModel;

class Shield :
	public Item
{
	static CObjModel* m_ObjModel;

private:
	virtual void ModelRender();

public:
	Shield();
	virtual ~Shield();

	static void InitModel();
	virtual void Update();

};

