#pragma once
#include "Item.h"
class Shield :
	public Item
{
public:
	Shield();
	virtual ~Shield();

	static void InitModel();

	virtual void Update();
	virtual void Render();
};

