#pragma once

class CObjModel;
class CMatrix;

class CEarth
{
	static CObjModel* m_Earth;

	CMatrix* m_Matrix{ nullptr };
	GLdouble m_BeginY{ 0.f };
	GLdouble m_EndY{ 1.f };
	float m_Time{ 0.f };
	
private:
	static void InitModel();
	static void DeleteModel();

public:
	CEarth(const CVector3D<>& Pos);
	~CEarth();

	void Update();
	void Render();
	void Float();
};

