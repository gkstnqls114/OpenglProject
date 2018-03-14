#pragma once
#include "RoadState.h"
class Stop :
	public RoadState
{
public:
	Stop();
	virtual ~Stop();

	virtual void Initialize();
	virtual void Update(Road& road);
};

