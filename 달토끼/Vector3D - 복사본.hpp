#include "Vector3D - 복사본.h"

template <typename T>
CVector3D<T> CVector3D<T>::operator+(const CVector3D<T> & rhs)
{
	CVector3D<T> Temp(
		x + rhs.x,
		y + rhs.y,
		z + rhs.z
	);
	return Temp;
}

template<typename T>
CVector3D<T> CVector3D<T>::operator+(CVector3D<T>&& rhs)
{
	CVector3D<T> Temp(
		x + rhs.x,
		y + rhs.y,
		z + rhs.z
	);
	return Temp;
}

template <typename T>
CVector3D<T> CVector3D<T>::operator-(const CVector3D<T> & rhs)
{
	CVector3D<T> Temp(
		x - rhs.x,
		y - rhs.y,
		z - rhs.z
	);
	return Temp;
}

template<typename T>
CVector3D<T> CVector3D<T>::operator-(CVector3D<T>&& rhs)
{
	CVector3D<T> Temp(
		vector.x - rhs.vector.x,
		vector.y - rhs.vector.y,
		vector.z - rhs.vector.z
	);
	return Temp;
}

template <typename T>
CVector3D<T> & CVector3D<T>::operator=(const CVector3D<T> & rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;

	return *this;
}

template <typename T>
CVector3D<T> & CVector3D<T>::operator=(CVector3D<T> && rhs)
{
	//std::cout << "복사 대입 연산자" << std::endl;
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;

	return *this;
}


#include "pch.h"