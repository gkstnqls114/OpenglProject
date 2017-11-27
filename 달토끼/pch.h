#pragma once

//opengl
#include <gl/glut.h>

//c++
#include <iostream>
#include <algorithm>
#include <list>
#include <math.h>

//make
#include "Vector3D.h"


template <typename T>
T Interpolation(T begin, T end, float time) {
	return begin * (1 - time) + end * time;
}

enum side_num
{
	k_left = -1,
	k_front,
	k_right
};
