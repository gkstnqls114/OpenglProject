#pragma once
#include "Scene.h"

class CSceneManager;
class CTextureStorage;

class CTestScene :
	public CScene
{
	CSceneManager*		m_pSceneManager		{ nullptr };

	CMediator*			m_Mediator			{ nullptr };
	CPlayer *			m_Player			{ nullptr };
	CCamera*			m_Camera			{ nullptr };
	
	GLint				texture_object;
	CTextureStorage*	m_texture			{ nullptr };


public:
	CTestScene(CSceneManager* const changer);
	virtual ~CTestScene();

	virtual void Initialize();
	virtual void Render();
	virtual void Reshape(const int& w, const int& h);
	virtual void Timer(const int& value);
	virtual void Update();
	virtual void Keyboard(const unsigned char& key, const int& x, const int& y);
	virtual void SpecialKeys(const int& key, const int& x, const int& y);
};
