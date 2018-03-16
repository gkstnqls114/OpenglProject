#pragma once
#include "Item.h"
class NullItem :
	public Item
{

private:
	virtual void ModelRender() { /*do nothing*/};

public:
	NullItem();
	virtual ~NullItem();

	virtual void Update() override { /*do nothing*/ };

};

