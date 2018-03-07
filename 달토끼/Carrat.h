#pragma once
#include "Item.h"

class CObjModel;

class Carrat :
	public Item
{
	static CObjModel* m_Carrat	;

	static void InitModel();
public:
	Carrat();
	virtual ~Carrat();

	virtual void Update();
	virtual void Render();
};
