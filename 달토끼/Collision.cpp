#include "pch.h"
#include "Player.h"
#include "Item.h"
#include "Collision.h"


Collision::Collision()
{
}


Collision::~Collision()
{
}

void Collision::Collide(CPlayer & player, Item & item)
{
	if (item.Get_Collide()) return;

	GLdouble collideLength = player.Get_Radius() + item.Get_sphereRadius();

	CVector3D<> vector (player.Get_CollidPos().x - item.Get_Pos().x,
		player.Get_CollidPos().y - item.Get_Pos().y,
		player.Get_CollidPos().z - item.Get_Pos().z);
	float length = vector.GetLength();
	
	if (length <= collideLength) {
		item.IsCollided();
		item.StateChange_Pop();
	}
}
