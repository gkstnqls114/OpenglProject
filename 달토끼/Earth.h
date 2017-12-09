#pragma once

class CObjModel;
class CMediator;
class CMatrix;

class CEarth
{
	static CObjModel* m_Earth;

	CMediator* m_pMediator{ nullptr };

	CMatrix* m_Matrix{ nullptr };
	GLdouble m_BeginY{ 0.f };
	GLdouble m_EndY{ 1.f };
	float m_Time{ 0.f };
	
	bool IsGameStart{ false };
private:
	static void InitModel();
	static void DeleteModel();


public:
	CEarth(CMediator*& mediator);
	~CEarth();
	void SetPos(const CVector3D<>& rhs);
	void SetPos(CVector3D<>&& rhs);

	void Update();
	void Render();
	void Float();

	virtual void Init_MainScene();
	virtual void GameStart();
};

