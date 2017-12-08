#pragma once
#include "Scene.h"

class CSceneManager;
class CPlayer;
class CMoon;
class CEarth;
class CRoad;
class CMediator;
class CSkybox;
class CCamera;

class CGameScene :
	public CScene
{
	CSceneManager*		m_pSceneManager	{ nullptr };

	CMediator *			m_pMediator		{ nullptr };

	CPlayer *			m_Player		{ nullptr };
	CMoon *				m_Moon			{ nullptr };
	CEarth *			m_Earth			{ nullptr };
	CCamera*			m_Camera		{ nullptr };
	CRoad *				m_Road			{ nullptr };

	CSkybox*			m_Skybox		{ nullptr };

	bool				Start			{ false };

public:
	CGameScene(CSceneManager* const changer);
	virtual ~CGameScene();

	virtual void Initialize		();
	virtual void Render			();
	virtual void Update			();
	virtual void Reshape		(const int& w, const int& h);
	virtual void Timer			(const int& value);
	virtual void Keyboard		(const unsigned char& key, const int& x, const int& y);
	virtual void SpecialKeys	(const int& key, const int& x, const int& y);
};

