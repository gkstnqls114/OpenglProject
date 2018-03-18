#pragma once

class CPlayer;
class Road;

class Collision
{
public:
	Collision();
	~Collision();

	void Collide(CPlayer& player, Road& road);

};

