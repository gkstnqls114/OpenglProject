#pragma once
#include "Item.h"

class CObjModel;

class Star :
	public Item
{
	static CObjModel* m_ObjModel;

private:
	virtual void ModelRender();

public:
	Star();
	virtual ~Star();

	static void InitModel();
	virtual void Update();

};

