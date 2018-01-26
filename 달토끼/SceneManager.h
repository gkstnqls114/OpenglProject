#pragma once

class Scene;

class CSceneManager
{
	Scene* m_pCurrScene{ nullptr };

	Scene* m_GameScene	{ nullptr };
	Scene* m_MainScene	{ nullptr };
	Scene* m_GameOverScene{ nullptr };
	Scene* m_GameClearScene{ nullptr };
	Scene* m_TestScene	{ nullptr };

public:
	CSceneManager();
	~CSceneManager();

	void ChangeToMain();
	void ChangeToGame();
	void ChangeToTest();
	void ChangeToGameOver();
	void ChangeToGameClear();

	void SceneRender		();
	void SceneReshape		(const int& w, const int& h);
	void SceneKeyboard		(const unsigned char& key, const int& x, const int& y);
	void SceneSpecialKeys	(const int& key, const int& x, const int& y);
	void SceneTimer			(const int& value);

};

