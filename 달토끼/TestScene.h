#pragma once
#include "Scene.h"

class CPlayer;
class CObjModel;
class CCamera;

class CTestScene :
	public CScene
{
	CPlayer * m_player	{ nullptr };

	CCamera * m_camera	{ nullptr };

public:
	CTestScene();
	virtual ~CTestScene();

	virtual void Initialize();
	virtual void Render();
	virtual void Update();
	virtual void Reshape(const int& w, const int& h);
	virtual void Timer(const int& value);
	virtual void Keyboard(const unsigned char& key, const int& x, const int& y);
	virtual void SpecialKeys(const int& key, const int& x, const int& y);

};

