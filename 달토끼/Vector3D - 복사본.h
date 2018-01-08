#pragma once

//x, y, z를 가지는 벡터 클래스입니다.
//혹시 모를 w를 위해 일단 할당은 4개로 해뒀음.

#ifndef VECTOR3D
#define VECTOR3D

template <typename T = GLdouble>
class CVector3D
{
public:
	T x;
	T y;
	T z;

public:
	CVector3D() {
		x = 0;
		y = 0;
		z = 0;
	}
	CVector3D(const CVector3D& rhs) {
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
	}
	CVector3D(const T& a, const T& b, const T&c) {
		x = a;
		y = b;
		z = c;
	}
	float Get_Length() {
		return sqrt(
			x * x +
			y * y +
			z * z
		);
	}

	void Normalize() {
		float length = Get_Length();
		if (length == 0) {
			x = 0; y = 0; z = 0;
			return;
		}

		x /= length;
		y /= length;
		z /= length;
	}

	T* GetVector() {
		T temp[3]{ x, y, z };
		return temp;
	}

	CVector3D<T> operator*(const float& val)
	{
		return CVector3D(
			x * val,
			y * val,
			z * val
		);
	}
	CVector3D<T> operator*(const double& val)
	{
		return CVector3D(
			x * val,
			y * val,
			z * val
		);
	}

	CVector3D<T> operator+(const CVector3D<T>& rhs);
	CVector3D<T> operator+(CVector3D<T>&& rhs);

	CVector3D<T> operator-(const CVector3D<T>& rhs);
	CVector3D<T> operator-(CVector3D<T>&& rhs);

	CVector3D<T>& operator=(const CVector3D<T>& rhs);
	CVector3D<T>& operator=(CVector3D<T>&& rhs);

};

#include "Vector3D - 복사본.hpp"

#endif
