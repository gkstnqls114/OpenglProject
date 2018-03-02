#pragma once
class Item
{

public:
	Item();
	virtual ~Item();
	
	virtual void Update() = 0;
	virtual void Render() = 0;

	void StateChange_Pop() {};
	void StateChange_Float() {};
	void StateChange_Disappear() {};
};

