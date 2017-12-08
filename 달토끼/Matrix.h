#pragma once

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

private:

public:
	CMatrix();
	~CMatrix();
	void MultiMatrix();
	
	void Calu_Tranlate(const CVector3D<GLdouble>& rhs);
	void Calu_Tranlate(CVector3D<GLdouble>&& rhs);

	void Calu_Rotate(const int& Nowdegree, const int& x, const int& y, const int& z);
	void Calu_Rotate(const float& Nowdegree, const int& x, const int& y, const int& z);
	void Set_Rotate(const int& Nowdegree, const int& x, const int& y, const int& z);
	void Set_Rotate(const float& Nowdegree, const int& x, const int& y, const int& z);


	void Calu_Scale(const float &NowSize);
	void Calu_Scale(const float &x, const float &y, const float &z);
	void Set_Scale(const float& NowSize);
	void Set_Scale(const float &x, const float &y, const float &z);

	void ResetTranslate();
	void ResetRotate();
	void ResetScale();

	//��� �ӽ÷� ���
	const GLdouble Get_Tranlate_Y ()
		const {
		return m_Translate_Matrix[13];
	}
	//���������� �ӽû��
	void Set_Translate_13(const GLdouble val)
	{
		m_Translate_Matrix[13] = val;
	}

};