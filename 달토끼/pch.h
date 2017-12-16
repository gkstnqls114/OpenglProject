#pragma once

//opengl
#include <gl/glut.h>

//c++
#include <wtypes.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>

//make
#include "Vector3D.h"

#include "SoundManager.h"

static CSoundManager SoundManager;

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

const int Road_Distance_X = 20;
const CVector3D<float, 3> LIGHTRGB{ 1.f, 0.7f, 0.7f };
