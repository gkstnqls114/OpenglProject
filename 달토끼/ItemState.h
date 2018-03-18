#pragma once

class Item;

class ItemState
{

public:
	ItemState();
	virtual ~ItemState();

	virtual void Initialize() = 0;
	virtual void Update(Item& player) = 0;
};