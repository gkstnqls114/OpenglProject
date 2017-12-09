#pragma once

//x, y, z�� ������ ���� Ŭ�����Դϴ�.
//Ȥ�� �� w�� ���� �ϴ� �Ҵ��� 4���� �ص���.

#ifndef VECTOR3D
#define VECTOR3D

template <typename T = GLdouble, int NUM = 4>
class CVector3D
{
private:
	T* vector{ nullptr };

private:


public:
	CVector3D();
	CVector3D(GLdouble x, GLdouble y, GLdouble z);
	CVector3D(const CVector3D<T, NUM>& other);
	CVector3D(CVector3D<T, NUM>&& rhs);

	~CVector3D();
	
	double Get_Length() const noexcept;
	void Normalize();
	void Reset();
	const T* GetVector() const noexcept { return vector; }

	template <typename COUNT>
	CVector3D<T, NUM> operator*(const COUNT& val)
	{
		return CVector3D(
			vector[0] * val,
			vector[1] * val,
			vector[2] * val
			);
	}

	CVector3D<T, NUM> operator+(const CVector3D<T, NUM>& rhs);
	CVector3D<T, NUM> operator+(CVector3D<T, NUM>&& rhs);

	CVector3D<T, NUM> operator-(const CVector3D<T, NUM>& rhs);
	CVector3D<T, NUM> operator-(CVector3D<T, NUM>&& rhs);

	CVector3D<T, NUM>& operator=(const CVector3D<T, NUM>& rhs);
	CVector3D<T, NUM>& operator=(CVector3D<T, NUM>&& rhs);
	
	T& operator[](const int& num) const;

	void ShowData();
	void ShowData(const CVector3D<T, NUM>& rhs);
	void ShowData(CVector3D<T, NUM>&& rhs);

	friend const bool operator==(const CVector3D<T, NUM>& rhs1, const CVector3D<T, NUM>& rhs2);

};

#include "Vector3D.hpp"

#endif
