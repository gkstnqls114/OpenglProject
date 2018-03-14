#pragma once

class Road;

class RoadState
{
public:
	RoadState();
	virtual ~RoadState();

	virtual void Initialize();
	virtual void Update(Road& road) = 0;
};
