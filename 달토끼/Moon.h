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

	bool IsGameStart{ false };

private:
	static void InitModel();
	static void DeleteModel();

public:
	CMoon(const CVector3D<>& Pos);
	~CMoon();
	void Initialize();

	void Update();
	void Render();

	void Float();

	virtual void Init_MainScene();
	virtual void GameStart();
};

