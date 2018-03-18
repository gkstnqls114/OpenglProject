#pragma once
#include "ItemState.h"
class Pop :
	public ItemState
{
public:
	Pop();
	virtual ~Pop();

	virtual void Initialize();
	virtual void Render(Item& item);
	virtual void Update(Item& item);
};

