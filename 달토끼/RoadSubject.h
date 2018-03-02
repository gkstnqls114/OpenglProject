#pragma once

class RoadObserver;
class CRoad;

class RoadSubject
{
public:
	RoadSubject();
	~RoadSubject();

	void Add_Observer(RoadObserver* push);
	void Sub_Observer(RoadObserver* pop);

	void Notify_DisappearFootBoard(CRoad* road);

private:
	std::list<RoadObserver*> m_RoadObserverList;

};

