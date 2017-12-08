#pragma once

class CScene;

class CSceneManager
{
	CScene* m_pCurrScene{ nullptr };

	CScene* m_GameScene	{ nullptr };
	CScene* m_MainScene	{ nullptr };
	CScene* m_TestScene	{ nullptr };

public:
	CSceneManager();
	~CSceneManager();

	void ChangeToMain();
	void ChangeToGame();
	void ChangeToTest();

	void SceneRender		();
	void SceneReshape		(const int& w, const int& h);
	void SceneKeyboard		(const unsigned char& key, const int& x, const int& y);
	void SceneSpecialKeys	(const int& key, const int& x, const int& y);
	void SceneTimer			(const int& value);

};

