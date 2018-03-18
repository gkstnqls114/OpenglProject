#pragma once
#include "Item.h"
class NullItem :
	public Item
{

private:
	virtual void Render_Model() { /*do nothing*/};

public:
	NullItem();
	virtual ~NullItem();

};

