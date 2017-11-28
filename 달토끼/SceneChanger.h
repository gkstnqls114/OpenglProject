#pragma once

class CScene;

class CSceneChanger
{
	CScene* m_current{ nullptr };

public:
	CSceneChanger();
	~CSceneChanger();

	void SceneChange();
	const CScene* Get_CurrentScene();
};

