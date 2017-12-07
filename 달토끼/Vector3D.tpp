#include "Vector3D.h"


template <typename T, int NUM>
  CVector3D<T, NUM>::CVector3D()
{
	vector = new T[NUM];
	Reset();
}

template <typename T, int NUM>
  CVector3D<T, NUM>::CVector3D(GLdouble x, GLdouble y, GLdouble z)
{
	vector = new T[NUM];
	vector[0] = x;
	vector[1] = y;
	vector[2] = z;
	if (NUM >= 3) {
		vector[3] = 0;
	}
}

template <typename T, int NUM>
  CVector3D<T, NUM>::~CVector3D()
{
	delete[] vector;
}


template <typename T, int NUM>
  CVector3D<T, NUM>::CVector3D(const CVector3D<T, NUM> & rhs)
{
	//복사생성자
	//std::cout << "복사생성자" << std::endl;
	vector = new T[NUM];

	for (int index = 0; index < NUM; ++index) {
		vector[index] = rhs.vector[index];
	}
}

template <typename T, int NUM>
  CVector3D<T, NUM>::CVector3D(CVector3D<T, NUM> && rhs)
{
	//std::cout << "이동생성자" << std::endl;
	vector = new T[NUM];
	
	vector[0] = rhs.vector[0];
	vector[1] = rhs.vector[1];
	vector[2] = rhs.vector[2];
	vector[3] = rhs.vector[3];

	rhs.vector = nullptr;
}

template <typename T, int NUM>
  double CVector3D<T, NUM>::Get_Length() const noexcept
{
	return sqrt(
		vector[0] * vector[0] +
		vector[1] * vector[1] +
		vector[2] * vector[2]
		);
}

template <typename T, int NUM>
  void CVector3D<T, NUM>::Normalize()
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

template <typename T, int NUM>
  void CVector3D<T, NUM>::Reset()
{
	for (int index = 0; index < 4; ++index) {
		vector[index] = 0;
	}
}

template <typename T, int NUM>
  CVector3D<T, NUM> CVector3D<T, NUM>::operator+(const CVector3D<T, NUM> & rhs)
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return CVector3D<T, NUM>(
		vector[0] + rhs.vector[0],
		vector[1] + rhs.vector[1],
		vector[2] + rhs.vector[2]
	);
}

template <typename T, int NUM>
  CVector3D<T, NUM> CVector3D<T, NUM>::operator-(const CVector3D<T, NUM> & rhs)
{
	return CVector3D<T, NUM>(
		vector[0] - rhs.vector[0],
		vector[1] - rhs.vector[1],
		vector[2] - rhs.vector[2]
		);
}

template <typename T, int NUM>
  CVector3D<T, NUM> & CVector3D<T, NUM>::operator=(const CVector3D<T, NUM> & rhs)
{
	//std::cout << "복사 대입 연산자" << std::endl;
	if (vector != nullptr) {
		delete[] vector;
	}

	vector = new T[NUM];
	for (int index = 0; index < NUM; ++index) {
		vector[index] = rhs.vector[index];
	}

	return *this;
}

template <typename T, int NUM>
  CVector3D<T, NUM> & CVector3D<T, NUM>::operator=(CVector3D<T, NUM> && rhs)
{
	//std::cout << "이동 대입 연산자" << std::endl;
	if (vector == nullptr) {
		vector = new T[NUM];
	}

	vector[0] = rhs.vector[0];
	vector[1] = rhs.vector[1];
	vector[2] = rhs.vector[2];
	vector[3] = rhs.vector[3];

	rhs.vector = nullptr;

	return *this;
}

template <typename T, int NUM>
  T& CVector3D<T, NUM>::operator[](const int& num) const
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	if (num >= NUM || num < 0) {
		std::cout << "Out Range" << std::endl;
		return vector[0]; //일단 임의로라도 제공..
	}

	return vector[num];
}


template <typename T, int NUM>
void CVector3D<T, NUM>::ShowData()
{
	for (int index = 0; index < 4; ++index) {
		std::cout << vector[index] << std::endl;
	}
	std::cout << std::endl;
}

template <typename T, int NUM>
void CVector3D<T, NUM>::ShowData(const CVector3D & rhs)
{

	for (int index = 0; index < 4; ++index) {
		std::cout << rhs.vector[index] << std::endl;
	}
	std::cout << std::endl;
}

template <typename T, int NUM>
  void CVector3D<T, NUM>::ShowData(CVector3D && rhs)
{

	for (int index = 0; index < NUM; ++index) {
		std::cout << rhs.vector[index] << std::endl;
	}
	std::cout << std::endl;
}

template <typename T1 , typename T2>
  const bool operator==(const CVector3D<T1> & rhs1, const CVector3D<T2> & rhs2)
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


#include "pch.h"