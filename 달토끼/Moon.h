#pragma once

class CObjModel;
class CMatrix;

class CMoon
{
	static CObjModel* m_Moon;

	CMatrix* m_Matrix{ nullptr };

private:
	static void InitModel();
	static void DeleteModel();

public:
	CMoon(const CVector3D& Pos);
	~CMoon();

	void Update();
	void Render();
};

