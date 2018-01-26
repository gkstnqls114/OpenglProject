#pragma once
#include "RoadState.h"
class Stop :
	public RoadState
{
public:
	Stop();
	virtual ~Stop();

	virtual void Initialize() = 0;
	virtual void Update(CRoad* road);
};

