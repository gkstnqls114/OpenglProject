#pragma once

class CObjModel;
class CMatrix;

class CEarth
{
	static CObjModel* m_Earth;

	CMatrix* m_Matrix{ nullptr };

private:
	static void InitModel();
	static void DeleteModel();

public:
	CEarth();
	~CEarth();

	void Update();
	void Render();
};

