#pragma once
#include "Scene.h"

class CSceneManager;
class CClearObject;
class CMediator;
class CEarth;

class CGAMECLEAR_word;
class CTextureStorage;

class CGameClear :
	public Scene
{
	CTextureStorage*	m_textureStroage{ nullptr };


	CCamera*			m_Camera{ nullptr };
	CClearObject*		m_ClearObj{ nullptr };
	CEarth*				m_earth{ nullptr };

	CGAMECLEAR_word*	m_GAMECLEAR{ nullptr };
	GLuint				m_BackgroundTextureID;

public:
	CGameClear(CSceneManager* const changer);
	virtual ~CGameClear();

	virtual void Initialize();
	virtual void SoundStop();
	virtual void Render();
	virtual void Reshape(const int& w, const int& h);
	virtual void Timer(const int& value);
	virtual void Update();
	virtual void Keyboard(const unsigned char& key, const int& x, const int& y);
	virtual void SpecialKeys(const int& key, const int& x, const int& y);

};

