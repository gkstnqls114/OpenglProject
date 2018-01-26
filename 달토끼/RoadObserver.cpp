#include "pch.h"
#include "Observer.h"
#include "RoadObserver.h"


RoadObserver::RoadObserver()
{
}


RoadObserver::~RoadObserver()
{
}

void RoadObserver::Add_Observer(Observer * push)
{
	m_List.push_back(push);
}

void RoadObserver::Sub_Observer(Observer * pop)
{
}

void RoadObserver::Notify(CRoad * road)
{
	for (auto d : m_List) {
		d->Notify(road);
	}
}
