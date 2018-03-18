#pragma once
#include "Item.h"

class CObjModel;

class Carrat :
	public Item
{
	static CObjModel* m_ObjModel	;

private:
	virtual void Render_Model();

public:
	Carrat();
	virtual ~Carrat();

	static void InitModel();
	virtual void Update();
};
