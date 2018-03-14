#pragma once

class Road;
class Observer;

class RoadObserver
{
public:
	RoadObserver();
	~RoadObserver();

	virtual void Receive_DisappearFootBoard(Road* road) = 0;
};

