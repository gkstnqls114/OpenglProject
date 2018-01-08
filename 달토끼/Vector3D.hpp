#include "Vector3D.h"


template <typename T, int NUM>
  CVector3D<T, NUM>::CVector3D()
{
	V3 = new T[NUM];
	Reset();
}

template <typename T, int NUM>
  CVector3D<T, NUM>::CVector3D(GLdouble x, GLdouble y, GLdouble z)
{
	V3 = new T[NUM];
	V3[0] = x;
	V3[1] = y;
	V3[2] = z;
	if (NUM > 3) {
		for(int index = 4; index < NUM; ++index){
			V3[index] = 0;
		}
	}
}

template <typename T, int NUM>
  CVector3D<T, NUM>::~CVector3D()
{
	delete[] V3;
}


template <typename T, int NUM>
  CVector3D<T, NUM>::CVector3D(const CVector3D<T, NUM> & rhs)
{
	//복사생성자
	//std::cout << "복사생성자" << std::endl;
	V3 = new T[NUM];

	for (int index = 0; index < NUM; ++index) {
		V3[index] = rhs.V3[index];
	}
}

template <typename T, int NUM>
  CVector3D<T, NUM>::CVector3D(CVector3D<T, NUM> && rhs)
{
	//std::cout << "이동생성자" << std::endl;
	V3 = rhs.V3;

	rhs.V3 = nullptr;
}

template <typename T, int NUM>
  double CVector3D<T, NUM>::Get_Length() const noexcept
{
	return sqrt(
		V3[0] * V3[0] +
		V3[1] * V3[1] +
		V3[2] * V3[2]
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

	V3[0] /= length;
	V3[1] /= length;
	V3[2] /= length;
}

template <typename T, int NUM>
  void CVector3D<T, NUM>::Reset()
{
	for (int index = 0; index < 4; ++index) {
		V3[index] = 0;
	}
}

template <typename T, int NUM>
CVector3D<T, NUM> CVector3D<T, NUM>::operator+(const CVector3D<T, NUM> & rhs)
{
	CVector3D<T, NUM> Temp(
		V3[0] + rhs.V3[0],
		V3[1] + rhs.V3[1],
		V3[2] + rhs.V3[2]
	);
	return Temp;
}

template<typename T, int NUM>
CVector3D<T, NUM> CVector3D<T, NUM>::operator+(CVector3D<T, NUM>&& rhs)
{
	CVector3D<T, NUM> Temp(
		V3[0] + rhs.V3[0],
		V3[1] + rhs.V3[1],
		V3[2] + rhs.V3[2]
	);
	return Temp;
}

template <typename T, int NUM>
  CVector3D<T, NUM> CVector3D<T, NUM>::operator-(const CVector3D<T, NUM> & rhs)
{
	CVector3D<T, NUM> Temp(
		V3[0] - rhs.V3[0],
		V3[1] - rhs.V3[1],
		V3[2] - rhs.V3[2]
	);
	return Temp;
}

template<typename T, int NUM>
CVector3D<T, NUM> CVector3D<T, NUM>::operator-(CVector3D<T, NUM>&& rhs)
{
	CVector3D<T, NUM> Temp(
		V3[0] - rhs.V3[0],
		V3[1] - rhs.V3[1],
		V3[2] - rhs.V3[2]
	);
	return Temp;
}

template <typename T, int NUM>
  CVector3D<T, NUM> & CVector3D<T, NUM>::operator=(const CVector3D<T, NUM> & rhs)
{
	//std::cout << "복사 대입 연산자" << std::endl;
	
	V3 = new T[NUM];
	for (int index = 0; index < NUM; ++index) {
		V3[index] = rhs.V3[index];
	}

	return *this;
}

template <typename T, int NUM>
  CVector3D<T, NUM> & CVector3D<T, NUM>::operator=(CVector3D<T, NUM> && rhs)
{
	//std::cout << "이동 대입 연산자" << std::endl;
	vector = rhs.vector;

	rhs.vector = nullptr;

	return *this;
}

template <typename T, int NUM>
  T& CVector3D<T, NUM>::operator[](const int& num) const
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	if (num >= NUM || num < 0) {
		//std::cout << "Out Range" << std::endl;
		return V3[0]; //일단 임의로라도 제공..
	}

	return V3[num];
}


template <typename T, int NUM>
void CVector3D<T, NUM>::ShowData()
{
	for (int index = 0; index < 4; ++index) {
		std::cout << V3[index] << std::endl;
	}
	std::cout << std::endl;
}

template <typename T, int NUM>
void CVector3D<T, NUM>::ShowData(const CVector3D & rhs)
{

	for (int index = 0; index < 4; ++index) {
		std::cout << rhs.V3[index] << std::endl;
	}
	std::cout << std::endl;
}

template <typename T, int NUM>
  void CVector3D<T, NUM>::ShowData(CVector3D && rhs)
{

	for (int index = 0; index < NUM; ++index) {
		std::cout << rhs.V3[index] << std::endl;
	}
	std::cout << std::endl;
}

template <typename T1 , typename T2>
  const bool operator==(const CVector3D<T1> & rhs1, const CVector3D<T2> & rhs2)
{
	bool IsSameX = abs(rhs1.V3[0] - rhs2.V3[0]) < 0.0001f;
	bool IsSameY = abs(rhs1.V3[1] - rhs2.V3[1]) < 0.0001f;
	bool IsSameZ = abs(rhs1.V3[2] - rhs2.V3[2]) < 0.0001f;
	bool IsSameW = abs(rhs1.V3[3] - rhs2.V3[3]) < 0.0001f;

	if (IsSameX && IsSameY &&IsSameZ && IsSameW) {
		return true;
	}

	return false;
}


#include "pch.h"