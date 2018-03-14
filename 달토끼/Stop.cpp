#include "pch.h"
#include "Road.h"
#include "Stop.h"


Stop::Stop()
{
}


Stop::~Stop()
{
}

void Stop::Initialize()
{
}

void Stop::Update(Road & road)
{
	road.Stop();
}

