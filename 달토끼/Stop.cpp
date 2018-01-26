#include "pch.h"
#include "Road.h"
#include "Stop.h"


Stop::Stop()
{
}


Stop::~Stop()
{
}

void Stop::Update(CRoad * road)
{
	road->Stop();
}
