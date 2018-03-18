#pragma once

class CPlayer;
class Road;
class Item;

//클래스를 만들지 않습니다.
//함수만 호출하는 클래스입니다.
class Collision
{
public:
	Collision();
	~Collision();

	static void Collide(CPlayer& player, Item& item);
	
};

