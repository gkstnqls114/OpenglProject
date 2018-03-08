#pragma once
#include "Item.h"

class CObjModel;

class Carrat :
	public Item
{
	static CObjModel* m_Carrat	;

public:
	Carrat(const int& boardnum);
	virtual ~Carrat();

	static void InitModel();

	virtual void Update();
	virtual void Render();
};
