#pragma once

class CPlayer;
class CRoad;

class Observer
{

public:
	Observer();
	~Observer();

	virtual void Render() {};
	virtual void Update() {};

	virtual void Notify(const CPlayer* player) {};
	virtual void Notify(const CRoad* road) {};
};
