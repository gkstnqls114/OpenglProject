#pragma once

class RotateMatrix
{
	GLfloat m_Rotate_Matrix[16] =
	{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};

public:
	RotateMatrix();
	~RotateMatrix();
	void Rotate();
	
	void Calu_Rotate(const int& Nowdegree, const int& x, const int& y, const int& z);
	void Calu_Rotate(const float& Nowdegree, const int& x, const int& y, const int& z);
	void Set_Rotate(const int& Nowdegree, const int& x, const int& y, const int& z);
	void Set_Rotate(const float& Nowdegree, const int& x, const int& y, const int& z);
	
	void ResetRotate();
};