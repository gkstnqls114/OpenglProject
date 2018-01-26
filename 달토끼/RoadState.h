#pragma once

class CRoad;

class RoadState
{
public:
	RoadState();
	virtual ~RoadState();

	virtual void Initialize() = 0;
	virtual void Update(CRoad* road) = 0;
};
