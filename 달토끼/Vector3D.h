#pragma once

//x, y, z를 가지는 벡터 클래스입니다.
//혹시 모를 w를 위해 일단 할당은 4개로 해뒀음.

class CVector3D
{
private:
	GLdouble* vector{ nullptr };

private:


public:
	CVector3D();
	CVector3D(GLdouble x, GLdouble y, GLdouble z);
	CVector3D(const CVector3D& other);
	CVector3D(CVector3D&& rhs);

	~CVector3D();
	
	double Get_Length() const noexcept;
	void Normalize();
	void Reset();

	template <typename T>
	CVector3D operator*(const T& val)
	{
		return CVector3D(
			vector[0] * val,
			vector[1] * val,
			vector[2] * val
			);
	}

	CVector3D operator+(const CVector3D& rhs);

	CVector3D operator-(const CVector3D& rhs);

	CVector3D& operator=(const CVector3D& rhs);
	CVector3D& operator=(CVector3D&& rhs);
	GLdouble& operator[](const int& num) const;

	void ShowData();
	void ShowData(const CVector3D& rhs);
	void ShowData(CVector3D&& rhs);

	friend const bool operator==(const CVector3D& rhs1, const CVector3D& rhs2);

};

