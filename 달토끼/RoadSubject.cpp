#include "pch.h"
#include "RoadObserver.h"
#include "RoadSubject.h"


RoadSubject::RoadSubject()
{
}

RoadSubject::~RoadSubject()
{
}

void RoadSubject::Add_Observer(RoadObserver * push)
{
	m_RoadObserverList.push_back(push);
}

void RoadSubject::Sub_Observer(RoadObserver * pop)
{
}

void RoadSubject::Notify_DisappearFootBoard(CRoad * road)
{
	for (auto d : m_RoadObserverList) {
		d->Receive_DisappearFootBoard(road);
	}
}
