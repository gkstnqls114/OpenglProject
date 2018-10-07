#pragma once

class CObjModel;
class RotateMatrix;
class CMediator;

class CMoon
{
	float m_Scale{ 0.7f };
	CVector3D<> m_InitPosition;
	CVector3D<> m_Position;

	static CObjModel* m_Moon;

	CMediator*		m_pMediator{ nullptr };

	RotateMatrix* m_Matrix{ nullptr };
	GLdouble m_BeginY{ 0 };
	GLdouble m_EndY{ 1.f };
	float m_Time{ 0.f };

	bool IsGameStart{ false };
	bool IsFloat{ false };
private:
	static void InitModel();
	static void DeleteModel();

public:
	CMoon(CMediator*& mediator);
	~CMoon();
	void Initialize();
	void SetPos(const CVector3D<>& rhs);
	void SetPos(CVector3D<>&& rhs);

	void Update();
	void Render();

	void Float();

	virtual void Init_MainScene();
	void Init_GameScene();
	virtual void GameStart();
};

