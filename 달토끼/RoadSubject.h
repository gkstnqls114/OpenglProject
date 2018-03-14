#pragma once

class RoadObserver;
class Road;

class RoadSubject
{
public:
	RoadSubject();
	~RoadSubject();

	void Add_Observer(RoadObserver* push);
	void Sub_Observer(RoadObserver* pop);

	void Notify_DisappearFootBoard(Road* road);

private:
	std::list<RoadObserver*> m_RoadObserverList;

};

