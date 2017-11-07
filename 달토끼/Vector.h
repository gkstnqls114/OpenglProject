#pragma once

class CVector
{
public:
	float x{ 0.f };
	float y{ 0.f };
	float z{ 0.f };

public:
	CVector();
	CVector(float x, float y, float z) : x{ x }, y{ y }, z{ z } {};
	
	~CVector();
	
	float Get_Length() const noexcept;
	void Normalize();

	CVector& operator*(const int& val);
	CVector& operator+(const CVector& val);
	
};

