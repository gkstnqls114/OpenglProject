#include "pch.h"
#include "BeUsed.h"


BeUsed::BeUsed()
{
}


BeUsed::~BeUsed()
{
}

void BeUsed::Initialize()
{
}

// 사용되었으므로 그리지 않습니다.
void BeUsed::Render(Item & item)
{
	//do nothing
}

// 사용되었으므로 업데이트하지 않습니다.
void BeUsed::Update(Item & item)
{
	//do nothing
}
