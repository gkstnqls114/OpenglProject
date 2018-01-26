#pragma once

class CPlayer;
class CRoad;
class CCamera;
class CMoon;
class CEarth;
class CPLAY_word;
class CEXIT_word;
class Observer;

class CSceneManager;
class CSoundManager;

// 하아아.. ...(깊은 한숨)
class CMediator
{
	CSceneManager* m_pSceneManager{ nullptr };
	CSoundManager* m_pSoundManager = &SoundManager;

	CPlayer*	m_pPlayer	{ nullptr };
	CRoad*		m_pRoad		{ nullptr };
	CCamera*	m_pCamera	{ nullptr };
	CCamera*	m_pMapCamera{ nullptr };

	CMoon*		m_pMoon		{ nullptr };
	CEarth*		m_pEarth	{ nullptr };
	CPLAY_word* m_pPLAY		{ nullptr };
	CEXIT_word* m_pEXIT		{ nullptr };

public:
	CMediator(CSceneManager*& manager);
	~CMediator();
	void SetSceneManger(CSceneManager*& manager) { m_pSceneManager = manager; }
	void SetPlayer(CPlayer*& player) { m_pPlayer = player; };
	void SetRoad(CRoad*& road) { m_pRoad = road; };
	void SetCamera(CCamera*& camera) { m_pCamera = camera; };
	void SetMapCamera(CCamera*& camera) { m_pMapCamera = camera; }
	void SetMoon(CMoon*& moon) { m_pMoon = moon; };
	void SetEarth(CEarth*& earth) { m_pEarth = earth; };
	void SetPLAYWORD(CPLAY_word*& play) { m_pPLAY = play; };
	void SetEXITWORD(CEXIT_word*& exit) { m_pEXIT = exit; };

	//화면전환
	void GameOver();
	void GameClear();
	void MainScene();
	void GameScene();
	void TestScene();

	//메인화면
	void Init_MainScene();
	void Cursor_PLAY();
	void Cursor_EXIT();
	void GameStart();

	//게임화면
	void Init_GameScene();
	void Player_JumpStart();
	void Player_Jumping();
	void Player_JumpFinish();
	void Player_Dead();
	void Player_Fall();
	void Player_Clear();

	//게임종료
	void Init_GameOver();

	//게임 클리어
	void Init_GameClear();
};