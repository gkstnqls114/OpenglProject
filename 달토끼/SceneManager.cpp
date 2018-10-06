#include "pch.h"
#include "MainScene.h"
#include "GameScene.h"
#include "TestScene.h"
#include "Gameover.h"
#include "GameClear.h"
#include "SceneManager.h"


CSceneManager* CSceneManager::m_pCSceneManager{ nullptr };

CSceneManager::CSceneManager()
{
	m_GameScene = new CGameScene(this);
	m_GameScene->SoundStop();
	m_MainScene = new CMainScene(this);
	m_MainScene->SoundStop();
	m_TestScene = new CTestScene();
	m_TestScene->SoundStop();
	m_GameOverScene = new CGameOver(this);
	m_GameOverScene->SoundStop();
	m_GameClearScene = new CGameClear(this);
	m_GameClearScene->SoundStop();

	ChangeToGame();
}


CSceneManager::~CSceneManager()
{
	delete m_GameScene;
	delete m_MainScene;
	delete m_TestScene;
	delete m_GameOverScene;
	delete m_GameClearScene;
}

void CSceneManager::ChangeToMain()
{
	if(m_pCurrScene) m_pCurrScene->SoundStop();
	m_pCurrScene = m_MainScene;
	m_pCurrScene->Initialize();
}

void CSceneManager::ChangeToGame()
{
	if (m_pCurrScene) m_pCurrScene->SoundStop();
	m_pCurrScene = m_GameScene;
	m_pCurrScene->Initialize();
}

void CSceneManager::ChangeToTest()
{
	if (m_pCurrScene) m_pCurrScene->SoundStop();
	m_pCurrScene = m_TestScene;
	m_pCurrScene->Initialize();
}

void CSceneManager::ChangeToGameOver()
{
	if (m_pCurrScene) m_pCurrScene->SoundStop();
	m_pCurrScene = m_GameOverScene;
	m_pCurrScene->Initialize();
}

void CSceneManager::ChangeToGameClear()
{
	if (m_pCurrScene) m_pCurrScene->SoundStop();
	m_pCurrScene = m_GameClearScene;
	m_pCurrScene->Initialize();
}

void CSceneManager::SceneRender()
{
	if (m_pCurrScene) m_pCurrScene->Render();
}

void CSceneManager::SceneReshape(const int & w, const int & h)
{
	if (m_pCurrScene) m_pCurrScene->Reshape(w, h);
}

void CSceneManager::SceneKeyboard(const unsigned char & key, const int & x, const int & y)
{
	if (m_pCurrScene) m_pCurrScene->Keyboard(key, x, y);
}

void CSceneManager::SceneSpecialKeys(const int & key, const int & x, const int & y)
{
	if (m_pCurrScene) m_pCurrScene->SpecialKeys(key, x, y);
}

void CSceneManager::SceneTimer(const int & value)
{
	if (m_pCurrScene) m_pCurrScene->Timer(value);
}
