#pragma once
#include "PlayerSubject.h"
#include "RoadSubject.h"
#include "ItemEffectManager.h"

#include "Scene.h"

class CSceneManager;
class CPlayer;
class CMoon;
class CEarth;
class Road;
class CMediator;
class CSkybox;
class CCamera;

class CTextureStorage;

class CGameScene :
	public Scene
{
	ItemEffectManager   m_ItemEffectManager;
	PlayerSubject		m_PlayerObserver;
	RoadSubject			m_RoadObserver;

	CSceneManager*		m_pSceneManager	{ nullptr };

	CMediator *			m_pMediator		{ nullptr };

	CPlayer *			m_Player		{ nullptr };
	CMoon *				m_Moon			{ nullptr };
	CEarth *			m_Earth			{ nullptr };
	CCamera*			m_Camera		{ nullptr };
	CCamera*			m_MapCamera		{ nullptr };
	Road *				m_Road			{ nullptr };

	CSkybox*			m_Skybox		{ nullptr };

	GLuint				m_ExplainTextureID;
	GLuint				m_BackgroundTextureID;
	CTextureStorage*	m_textureStroage{ nullptr };

	bool				Explain			{ false };
	bool				Start			{ false };
	bool				Perspective		{ false };

private:
	void RenderBack();
	void RenderExplain();

public:
	CGameScene(CSceneManager* const changer);
	virtual ~CGameScene();

	virtual void Initialize		();
	virtual void SoundStop		();
	virtual void Render			();
	virtual void Update			();
	virtual void Reshape		(const int& w, const int& h);
	virtual void Timer			(const int& value);
	virtual void Keyboard		(const unsigned char& key, const int& x, const int& y);
	virtual void SpecialKeys	(const int& key, const int& x, const int& y);
};

