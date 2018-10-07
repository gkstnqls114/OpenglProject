#pragma once

class CObjModel;
class CMediator;
class RotateMatrix;

class CEarth
{
	CVector3D<> m_Position;
	float m_Scale{ 1.f };
	static CObjModel* m_Earth;

	RotateMatrix* m_Matrix{ nullptr };
	GLdouble m_BeginY{ 0.f };
	GLdouble m_EndY{ 1.f };
	float m_Time{ 0.f };
	
	bool IsGameStart{ false };
	bool IsFloat{ false };
private:
	static void InitModel();
	static void DeleteModel();


public:
	CEarth();
	~CEarth();
	void SetPos(const CVector3D<>& rhs);
	void SetPos(CVector3D<>&& rhs);

	void Update();
	void Render();
	void Float();

	virtual void Init_MainScene();
	virtual void Init_GameScene();
	virtual void GameStart();
};

