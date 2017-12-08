#include "pch.h"
#include "MainScene.h"
#include "GameScene.h"
#include "TestScene.h"
#include "SceneManager.h"

CSceneManager::CSceneManager()
{
	std::cout << "장면 체인지 주소: " << this << std::endl;
	m_GameScene = new CGameScene(this);
	m_MainScene = new CMainScene(this);
	m_TestScene = new CTestScene(this);
	m_pCurrScene = m_MainScene;
}


CSceneManager::~CSceneManager()
{
	delete[] m_GameScene;
	delete[] m_MainScene;
	delete[] m_TestScene;
}

void CSceneManager::ChangeToMain()
{
	m_pCurrScene = m_MainScene;
	//나중에 리셋 추가
}

void CSceneManager::ChangeToGame()
{
	m_pCurrScene = m_GameScene;
}

void CSceneManager::ChangeToTest()
{
	m_pCurrScene = m_TestScene;
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
