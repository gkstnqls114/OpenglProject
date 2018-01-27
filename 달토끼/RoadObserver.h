#pragma once

class CRoad;
class Observer;

class RoadObserver
{
	std::list<Observer*> m_List;

public:
	RoadObserver();
	~RoadObserver();

	void Add_Observer(Observer* push);
	void Sub_Observer(Observer* pop);
	
	void Notify_DisappearFootBoard(CRoad* road);
};

