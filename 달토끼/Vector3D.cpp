#include "pch.h"
#include "Vector3D.h"



CVector3D::CVector3D()
{
	x = NULL;
	y = NULL;
	z = NULL;
}



CVector3D::~CVector3D()
{

}


CVector3D::CVector3D(const CVector3D & other)
{
	//복사생성자
	x = other.x;
	y = other.y;
	z = other.z;
}


CVector3D::CVector3D(CVector3D && rhs)
{
	//이동생성자
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
}


float CVector3D::Get_Length() const noexcept
{
	return sqrt(x * x + y * y + z * z);
}


void CVector3D::Normalize()
{
	float length = Get_Length();
	if (length == 0) {
		x = 0;
		y = 0;
		z = 0;
		return;
	}

	x /= length;
	y /= length;
	z /= length;
}

CVector3D CVector3D::operator*(const double & val)
{
	//int에 대한 곱하기
	return CVector3D(x * val, y * val, z * val);
}



CVector3D CVector3D::operator+(const CVector3D & other)
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return CVector3D(x + other.x, y + other.y, z + other.z);
}


CVector3D CVector3D::operator-(const CVector3D & other)
{
	return CVector3D(x - other.x, y - other.y, z - other.z);
}


CVector3D & CVector3D::operator=(const CVector3D & other)
{
	x = other.x;
	y = other.y;
	z = other.z;

	return *this;
}


CVector3D & CVector3D::operator=(CVector3D && rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	rhs.x = NULL;
	rhs.y = NULL;
	rhs.z = NULL;

	return *this;
}

