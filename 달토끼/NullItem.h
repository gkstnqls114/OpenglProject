#pragma once
#include "Item.h"
class NullItem :
	public Item
{

private:
	virtual void Render_Model() override{ /*do nothing*/};
	virtual void ItemEffect() override { /*do nothing*/ };

public:
	NullItem();
	virtual ~NullItem();

};

