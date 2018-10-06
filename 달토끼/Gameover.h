#pragma once
#include "Scene.h"

class CSceneManager;
class CPlayer;
class CCamera;
class CGAMEOVER_word;

class CGameOver:
	public Scene
{
	CSceneManager*		m_pSceneManager{ nullptr };

	CCamera*			m_Camera{ nullptr };
	CPlayer *			m_Player{ nullptr };
	CGAMEOVER_word*		m_GAMEOVER{ nullptr };
private:

public:
	CGameOver(CSceneManager* const changer);
	virtual ~CGameOver();

	virtual void Initialize();
	virtual void SoundStop();
	virtual void Render();
	virtual void Reshape(const int& w, const int& h);
	virtual void Timer(const int& value);
	virtual void Update();
	virtual void Keyboard(const unsigned char& key, const int& x, const int& y);
	virtual void SpecialKeys(const int& key, const int& x, const int& y);
};

