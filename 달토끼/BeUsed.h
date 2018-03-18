#pragma once
#include "ItemState.h"
class BeUsed :
	public ItemState
{
public:
	BeUsed();
	virtual ~BeUsed();

	virtual void Initialize();
	virtual void Render(Item& item);
	virtual void Update(Item& item);
};

