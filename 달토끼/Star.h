#pragma once
#include "Item.h"
class Star :
	public Item
{
public:
	Star();
	virtual ~Star();

	static void InitModel();

	virtual void Update();
	virtual void Render();
};

