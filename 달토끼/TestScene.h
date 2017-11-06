#pragma once
#include "Scene.h"

class CPlayer;
class CObjModel;

class CTestScene :
	public CScene
{
	CPlayer * m_player{ nullptr };
	CObjModel * m_obj{ nullptr };

public:
	CTestScene();
	virtual ~CTestScene();

	virtual void Initialize();
	virtual void Render();
	virtual void Update();
	virtual void Reshape(int w, int h);
	virtual void Timer(int value);
	virtual void Keyboard(unsigned char key, int x, int y);
};

