#pragma once

//x, y, z�� ������ ���� Ŭ�����Դϴ�.

class CVector3D
{
public:
	GLdouble x;
	GLdouble y;
	GLdouble z;

private:

public:
	CVector3D();
	CVector3D(GLdouble x, GLdouble y, GLdouble z) : x{ x }, y{ y }, z{ z } {};
	CVector3D(const CVector3D& other);
	CVector3D(CVector3D&& rhs);

	~CVector3D();
	

	float Get_Length() const noexcept;
	void Normalize();

	CVector3D operator*(const double& val);

	CVector3D operator+(const CVector3D& other);
	CVector3D operator-(const CVector3D& other);
	CVector3D& operator=(const CVector3D& other);
	CVector3D& operator=(CVector3D&& rhs);
};

