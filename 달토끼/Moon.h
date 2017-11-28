#pragma once

class CObjModel;
class CMatrix;

class CMoon
{
	static CObjModel* m_Moon;

	CMatrix* m_Matrix{ nullptr };
	GLdouble m_BeginY{ 0 };
	GLdouble m_EndY{ 1.f };
	float m_Time{ 0.f };

private:
	static void InitModel();
	static void DeleteModel();

public:
	CMoon(const CVector3D& Pos);
	~CMoon();

	void Update();
	void Render();

	void Float();
};

