#pragma once

class CPlayer;
class Road;
class Item;

//Ŭ������ ������ �ʽ��ϴ�.
//�Լ��� ȣ���ϴ� Ŭ�����Դϴ�.
class Collision
{
public:
	Collision();
	~Collision();

	static void Collide(CPlayer& player, Item& item);
	
};

