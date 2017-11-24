#pragma once
#include "Scene.h"

class CPlayer;
class CObjModel;
class CRoad;
class CMediator;
class CCamera;

class CGameScene :
	public CScene
{
	CPlayer * m_Player{ nullptr };
	CCamera* m_Camera{ nullptr };
	CRoad * m_Road{ nullptr };

	CMediator * m_Mediator{ nullptr };

	bool Start{ false };
private:
	void RenderAxis();

public:
	CGameScene();
	virtual ~CGameScene();

	virtual void Initialize();
	virtual void Render();
	virtual void Update();
	virtual void Reshape(const int& w, const int& h);
	virtual void Timer(const int& value);
	virtual void Keyboard(const unsigned char& key, const int& x, const int& y);
	virtual void SpecialKeys(const int& key, const int& x, const int& y);
};

