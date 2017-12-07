#pragma once

class CScene;

class CSceneChanger
{
private:
	static CScene* m_CurrScene;

public:
	CSceneChanger();
	~CSceneChanger();

	void SceneChange();
	const CScene* Get_CurrentScene();
};

