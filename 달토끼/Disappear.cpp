#include "pch.h"
#include "Disappear.h"
#include "Road.h"


Disappear::Disappear()
{
	
}


Disappear::~Disappear()
{

}

void Disappear::Initialize()
{
}

void Disappear::Update(Road&road)
{
	road.Disappear();
}
