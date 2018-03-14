#pragma once
#include "RoadState.h"

class Disappear :
	public RoadState
{
public:
	Disappear();
	virtual ~Disappear();

	virtual void Initialize();
	virtual void Update(Road& road);
};

