#pragma once
#include "Scene.h"

class CObjModel;

class CTestScene :
	public CScene
{
	CObjModel * m_obj{ nullptr };
	int rotateXdegree = 0;
	int rotateYdegree = 0;


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

