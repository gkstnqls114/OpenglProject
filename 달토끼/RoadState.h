#pragma once

class CRoad;

class RoadState
{
public:
	RoadState();
	virtual ~RoadState();

	virtual void Initialize();
	virtual void Update(CRoad* road) = 0;
};
