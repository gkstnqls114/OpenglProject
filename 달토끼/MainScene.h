#pragma once
#include "Scene.h"

class CCamera;
class CMediator;
class CMoon;
class CEarth;
class CEXIT_word;
class CPLAY_word;

class CSceneManager;

class CMainScene :
	public CScene
{
	CSceneManager*	m_pSceneManager	{ nullptr };

	CMediator*		m_pMediator		{ nullptr };
	CCamera*		m_Camera		{ nullptr };
	CMoon*			m_Moon			{ nullptr };
	CEarth*			m_Earth			{ nullptr };
	CPLAY_word*		m_PLAY			{ nullptr };
	CEXIT_word*		m_EXIT			{ nullptr };

	enum {
		k_PLAY,
		k_EXIT
	};
	CVector3D<>		m_CursorPos;
	int				m_Cursor		{ k_PLAY };

	int				Nowdegree		{ 0 };
	const int		k_PLAYdegree	{ 0 };
	const int		k_EXITdegree	{ 180 };
	bool			IsClockWise		{ false };
	bool			IsRotate		{ false };

	bool			IsGameStart		{ false };
private:
	void ConfirmCursor();
	void SelectCursor();
	void RotateUpdate();
	void WordRender(); //ortho ¶§¹®¿¡...

public:
	CMainScene(CSceneManager* const changer);
	virtual ~CMainScene();

	virtual void Initialize		();
	virtual void Render			();
	virtual void Reshape		(const int& w, const int& h);
	virtual void Timer			(const int& value);
	virtual void Update			();
	virtual void Keyboard		(const unsigned char& key, const int& x, const int& y);
	virtual void SpecialKeys	(const int& key, const int& x, const int& y);
};

