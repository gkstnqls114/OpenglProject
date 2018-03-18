#include "pch.h"
#include "Item.h"
#include "Pop.h"


Pop::Pop()
{
}


Pop::~Pop()
{
}

void Pop::Initialize()
{
}

void Pop::Render(Item & item)
{
	item.Render_All();
}

// 방울이 터지는 애니메이션을 업데이트 합니다.
void Pop::Update(Item & item)
{
	item.Pop();
}
