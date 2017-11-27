#pragma once

//opengl
#include <gl/glut.h>

//c++
#include <iostream>
#include <algorithm>
#include <list>
#include <math.h>

//c
#include <stdio.h>

enum side_num
{
	k_left = -1,
	k_front,
	k_right
};
//
//enum player_state
//{
//	JUMP,
//	DEAD
//};
//

template <typename T>
T Interpolation(T begin, T end, float time) {
	return begin * (1 - time) + end * time;
}
