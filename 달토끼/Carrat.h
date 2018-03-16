#pragma once
#include "Item.h"

class CObjModel;

class Carrat :
	public Item
{
	static CObjModel* m_ObjModel	;

private:
	virtual void ModelRender();

public:
	Carrat();
	virtual ~Carrat();

	static void InitModel();
	virtual void Update();
};
