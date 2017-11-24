#pragma once

class CVector3D;

class CMatrix
{
	GLfloat m_Translate_Matrix[16] =
	{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};

	GLfloat m_Scale_Matrix[16] =
	{
		1.f, 0, 0, 0,
		0, 1.f, 0, 0,
		0, 0, 1.f, 0,
		0, 0, 0, 1.f
	};

	GLfloat m_Rotate_Matrix[16] =
	{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
public:
	CMatrix();
	~CMatrix();
	void MultiMatrix();
	void Calu_Tranlate(const CVector3D& rhs);
	void Calu_Tranlate(CVector3D&& rhs);
	void Calu_Rotate(const int& degree, const int& x, const int& y, const int& z);
	void Calu_Rotate(const float& degree, const int& x, const int& y, const int& z);

	void Calu_Scale(const float &size);

	//잠시 임시로 사용
	const GLdouble Get_Tranlate_13 ()
		const {
		return m_Translate_Matrix[13];
	}
	//마찬가지로 임시사용
	void Set_Translate_13(const GLdouble val)
	{
		m_Translate_Matrix[13] = val;
	}

};