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

// �սǵս� �������� �������� ������Ʈ�մϴ�.
void Float::Update(Item & item)
{
	item.Float();
}
