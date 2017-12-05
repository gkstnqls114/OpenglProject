#pragma once
#include "Scene.h"

class CTexture;

class CTestScene :
	public CScene
{

	CMediator*		m_Mediator{ nullptr };
	CCamera*		m_Camera{ nullptr };
	
	GLint	texture_object;
	CTexture*		m_texture{ nullptr };

	CPlayer * m_Player{ nullptr };

public:
	CTestScene();
	virtual ~CTestScene();

	virtual void Initialize();
	virtual void Render();
	virtual void Reshape(const int& w, const int& h);
	virtual void Timer(const int& value);
	virtual void Update();
	virtual void Keyboard(const unsigned char& key, const int& x, const int& y);
	virtual void SpecialKeys(const int& key, const int& x, const int& y);
};
