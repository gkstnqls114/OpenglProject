#pragma once

//opengl
#include <gl/glut.h>

//c++
#include <wtypes.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>

//makeDAKF
#include "Vector3D - บนป็บป.h"
#include "SoundManager.h"
#include "Side.h"

static CSoundManager SoundManager;

template <typename T>
T Interpolation(T begin, T end, float time) {
	return begin * (1 - time) + end * time;
}

const CVector3D<float> LIGHTRGB{ 1.f, 0.7f, 0.7f };

#define _MASTER