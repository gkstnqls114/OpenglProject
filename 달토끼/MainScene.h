#pragma once
#include "Scene.h"

class CCamera;
class CMediator;
class CMoon;
class CObjModel;

class CMainScene :
	public CScene
{
	CMediator* m_Mediator{ nullptr };
	CCamera* m_Camera{ nullptr };
	
	enum {
		k_PLAY,
		k_EXIT
	};
	int m_Cursor = k_PLAY;
	
	CVector3D m_CursorPos;

	CMoon* m_Moon	{ nullptr };
	CEarth* m_Earth	{ nullptr };
	
	float YTime{ 0.f };

	
	CObjModel* m_PLAY	{ nullptr };
	CObjModel* m_EXIT	{ nullptr };


public:
	CMainScene();
	virtual ~CMainScene();

	virtual void Initialize();
	virtual void Render();
	virtual void Reshape(const int& w, const int& h);
	virtual void Timer(const int& value);
	virtual void Update();
	virtual void Keyboard(const unsigned char& key, const int& x, const int& y);
	virtual void SpecialKeys(const int& key, const int& x, const int& y);
};

