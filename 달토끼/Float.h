#pragma once
#include "ItemState.h"
class Float :
	public ItemState
{
public:
	Float();
	virtual ~Float();

	virtual void Initialize();
	virtual void Render(Item& item);
	virtual void Update(Item& item);
};

