#pragma once
#include "RoadState.h"

class Disappear :
	public RoadState
{
public:
	Disappear();
	virtual ~Disappear();

	virtual void Initialize() = 0;
	virtual void Update(CRoad* road);
};

