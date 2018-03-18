#include "pch.h"
#include "Item.h"
#include "Float.h"


Float::Float()
{
}


Float::~Float()
{
}

void Float::Initialize()
{
}

void Float::Render(Item & item)
{
	item.Render_All();
}

// 둥실둥실 떠오르는 아이템을 업데이트합니다.
void Float::Update(Item & item)
{
	item.Float();
}
