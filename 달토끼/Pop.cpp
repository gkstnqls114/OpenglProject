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

// ����� ������ �ִϸ��̼��� ������Ʈ �մϴ�.
void Pop::Update(Item & item)
{
	item.Pop();
}
