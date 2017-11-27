#include "pch.h"
#include "Vector3D.h"



CVector3D::CVector3D()
{
	vector = new GLdouble[4];
	Reset();
}

CVector3D::CVector3D(GLdouble x, GLdouble y, GLdouble z)
{
	vector = new GLdouble[4];
	vector[0] = x;
	vector[1] = y;
	vector[2] = z;
	vector[3] = 0;
}

CVector3D::~CVector3D()
{
	delete[] vector;
}


CVector3D::CVector3D(const CVector3D & rhs)
{
	//복사생성자
	std::cout << "복사생성자" << std::endl;
	vector = new GLdouble[4];

	vector[0] = rhs.vector[0];
	vector[1] = rhs.vector[1];
	vector[2] = rhs.vector[2];
	vector[3] = rhs.vector[3];

}

CVector3D::CVector3D(CVector3D && rhs)
{
	vector = new GLdouble[4];
	
	vector[0] = rhs.vector[0];
	vector[1] = rhs.vector[1];
	vector[2] = rhs.vector[2];
	vector[3] = rhs.vector[3];

	rhs.vector = nullptr;
}

double CVector3D::Get_Length() const noexcept
{
	return sqrt(
		vector[0] * vector[0] +
		vector[1] * vector[1] +
		vector[2] * vector[2]
		);
}

void CVector3D::Normalize()
{
	float length = Get_Length();
	if (length == 0) {
		Reset();
		return;
	}

	vector[0] /= length;
	vector[1] /= length;
	vector[2] /= length;
}

void CVector3D::Reset()
{
	for (int index = 0; index < 4; ++index) {
		vector[index] = 0;
	}
}

CVector3D CVector3D::operator+(const CVector3D & rhs)
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return CVector3D(
		vector[0] + rhs.vector[0],
		vector[1] + rhs.vector[1],
		vector[2] + rhs.vector[2]
	);
}

CVector3D CVector3D::operator-(const CVector3D & rhs)
{
	return CVector3D(
		vector[0] - rhs.vector[0],
		vector[1] - rhs.vector[1],
		vector[2] - rhs.vector[2]
		);
}

CVector3D & CVector3D::operator=(const CVector3D & rhs)
{
	if (vector != nullptr) {
		delete[] vector;
	}

	vector = new GLdouble[4];
	vector[0] = rhs.vector[0];
	vector[1] = rhs.vector[1];
	vector[2] = rhs.vector[2];
	vector[3] = rhs.vector[3];

	return *this;
}

CVector3D & CVector3D::operator=(CVector3D && rhs)
{
	if (vector == nullptr) {
		vector = new GLdouble[4];
	}

	vector[0] = rhs.vector[0];
	vector[1] = rhs.vector[1];
	vector[2] = rhs.vector[2];
	vector[3] = rhs.vector[3];

	rhs.vector = nullptr;

	return *this;
}

GLdouble& CVector3D::operator[](const int& num) const
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	if (num > 3 || num < 0) {
		std::cout << "Out Range" << std::endl;
		return vector[3]; //일단 임의로라도 제공..
	}

	return vector[num];
}


void CVector3D::ShowData()
{
	for (int index = 0; index < 4; ++index) {
		std::cout << vector[index] << std::endl;
	}
	std::cout << std::endl;
}

void CVector3D::ShowData(const CVector3D & rhs)
{

	for (int index = 0; index < 4; ++index) {
		std::cout << rhs.vector[index] << std::endl;
	}
	std::cout << std::endl;
}

void CVector3D::ShowData(CVector3D && rhs)
{

	for (int index = 0; index < 4; ++index) {
		std::cout << rhs.vector[index] << std::endl;
	}
	std::cout << std::endl;
}

const bool operator==(const CVector3D & rhs1, const CVector3D & rhs2)
{
	bool IsSameX = abs(rhs1.vector[0] - rhs2.vector[0]) < 0.0001f;
	bool IsSameY = abs(rhs1.vector[1] - rhs2.vector[1]) < 0.0001f;
	bool IsSameZ = abs(rhs1.vector[2] - rhs2.vector[2]) < 0.0001f;
	bool IsSameW = abs(rhs1.vector[3] - rhs2.vector[3]) < 0.0001f;

	if (IsSameX && IsSameY &&IsSameZ && IsSameW) {
		return true;
	}

	return false;
}

