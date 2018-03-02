#pragma once

class CRoad;
class Observer;

class RoadObserver
{
public:
	RoadObserver();
	~RoadObserver();

	virtual void Receive_DisappearFootBoard(CRoad* road) = 0;
};

