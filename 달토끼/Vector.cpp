#include "pch.h"
#include "Vector.h"


CVector::CVector()
{

}

float CVector::Get_Length() const noexcept
{
	return sqrt(x * x + y * y + z * z);
}

void CVector::Normalize()
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

CVector::~CVector()
{
}

CVector CVector::operator*(const int & val)
{
	// TODO: ���⿡ ��ȯ ������ �����մϴ�.
	return CVector (x * val, y * val, z * val);

}

CVector CVector::operator+(const CVector & val)
{
	// TODO: ���⿡ ��ȯ ������ �����մϴ�.
	return CVector(x + val.x, y + val.y, z + val.z);
}

