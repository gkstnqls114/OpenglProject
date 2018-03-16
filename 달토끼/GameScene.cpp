#include "pch.h"
#include "SceneManager.h"
#include "Player.h"
#include "Moon.h"
#include "Earth.h"
#include "Camera.h"
#include "Skybox.h"
#include "Road.h"
#include "TextureStorage.h"
#include "GameScene.h"

void CGameScene::RenderBack()
{
	glClear(GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double Left = -glutGet(GLUT_WINDOW_WIDTH) / 2;
	double Right = glutGet(GLUT_WINDOW_WIDTH) / 2;
	double Top = static_cast<float>(glutGet(GLUT_WINDOW_HEIGHT)) / 2;
	double Bottom = -static_cast<float>(glutGet(GLUT_WINDOW_HEIGHT)) / 2;

	glOrtho(Left, Right, Bottom, Top, -100.f, 100);
	glMatrixMode(GL_MODELVIEW);

	glColor3f(LIGHTRGB.x, LIGHTRGB.y, LIGHTRGB.z);
	glBindTexture(GL_TEXTURE_2D, m_BackgroundTextureID);
	glBegin(GL_QUADS);
	glTexCoord2f(0.f, 1.f);
	glVertex3d(Left, Top, 0);
	glTexCoord2f(1.f, 1.f);
	glVertex3d(Right, Top, 0);
	glTexCoord2f(1.f, 0.f);
	glVertex3d(Right, Bottom, 0);
	glTexCoord2f(0.f, 0.f);
	glVertex3d(Left, Bottom, 0);
	glEnd();

	glClear(GL_DEPTH_BUFFER_BIT);
}

void CGameScene::RenderExplain()
{
	if (Explain) return;

	glClear(GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double Left = -glutGet(GLUT_WINDOW_WIDTH) / 2;
	double Right = glutGet(GLUT_WINDOW_WIDTH) / 2;
	double Top = static_cast<float>(glutGet(GLUT_WINDOW_HEIGHT)) / 2;
	double Bottom = -static_cast<float>(glutGet(GLUT_WINDOW_HEIGHT)) / 2;

	glOrtho(Left, Right, Bottom, Top, -100.f, 100);
	glMatrixMode(GL_MODELVIEW);

	glDisable(GL_LIGHTING);

	glColor3f(1.f, 1.f, 1.f);
	glBindTexture(GL_TEXTURE_2D, m_ExplainTextureID);
	glBegin(GL_QUADS);
	glTexCoord2f(0.f, 1.f);
	glVertex3d(Left, Top, 0);
	glTexCoord2f(1.f, 1.f);
	glVertex3d(Right, Top, 0);
	glTexCoord2f(1.f, 0.f);
	glVertex3d(Right, Bottom, 0);
	glTexCoord2f(0.f, 0.f);
	glVertex3d(Left, Bottom, 0);
	glEnd();

	glEnable(GL_LIGHTING);
	glClear(GL_DEPTH_BUFFER_BIT);
}

CGameScene::CGameScene(CSceneManager* const changer)
{
	SoundManager.AddSound(
		"GameBGM"
		, "./Sound/GamePlayBGM/Chew_Chew_Island_Main_Theme.mp3"
		, SoundType::Stream
	);
	SoundManager.AddSound(
		"JumpEffect"
		, "./Sound/Effect/Jump.wav"
		, SoundType::Effect2D
	);
	SoundManager.AddSound(
		"FallEffect"
		, "./Sound/Effect/Fall.wav"
		, SoundType::Effect2D
	);


	m_pSceneManager = changer;

	m_textureStroage = new CTextureStorage;
	m_textureStroage->StoreBitmap("Background.bmp", m_BackgroundTextureID);

	m_textureStroage = new CTextureStorage;
	m_textureStroage->StoreBitmap("Explain.bmp", m_ExplainTextureID);

	m_MapCamera = new CCamera();
	m_Camera = new CCamera();
	m_Player = new CPlayer();

	m_Road = new Road(100);
	int LastZ = m_Road->Get_LastPos().z;
	m_Skybox = new CSkybox(LastZ);

	m_Moon = new CMoon(m_pMediator);
	m_Earth = new CEarth(m_pMediator);


	Initialize();
}

CGameScene::~CGameScene()
{
	delete m_Player;
	m_Player = nullptr;

	delete m_Moon;
	m_Moon = nullptr;
	
	delete m_Earth;
	m_Earth = nullptr;

	delete m_Camera;
	m_Camera = nullptr;

	delete m_Road;
	m_Road = nullptr;

	delete m_Skybox;
	m_Skybox = nullptr;
}

void CGameScene::Initialize()
{
	SoundManager.Play("GameBGM");

	glDisable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glDisable(GL_LIGHT2);
	glDisable(GL_LIGHT3);

	glEnable(GL_COLOR_MATERIAL);

	//m_pMediator->Init_GameScene();

	m_MapCamera->Initialize(CVector3D<>(0.f, 0.f, m_Road->Get_FirstPos().z * 5), 500, 0.1f, 600.f, 60);
	m_MapCamera->Rotate(0.f, 1.4f);
	m_MapCamera->Rotate(90, 0);

	GLdouble DownY = 100;
	CVector3D<> MoonPos = m_Road->Get_LastPos();
	CVector3D<> EarthPos = m_Road->Get_FirstPos();
	m_Earth->SetPos(CVector3D<>(EarthPos.x, EarthPos.y - DownY, EarthPos.z));
	m_Moon->SetPos(CVector3D<>(MoonPos.x, MoonPos.y - DownY + 30, MoonPos.z));

	Start = false;
	Explain = false;
	Perspective = false;
}

void CGameScene::SoundStop()
{
	SoundManager.Stop("GameBGM");
	SoundManager.Stop("JumpEffect");
	SoundManager.Stop("FallEffect");
}

void CGameScene::Render()
{
	double Width = glutGet(GLUT_WINDOW_WIDTH);
	double Height = static_cast<float>(glutGet(GLUT_WINDOW_HEIGHT));

	RenderBack();

	m_Camera->LookAt();

	m_Skybox->Render();

	m_Player->Render();
	m_Road->Render();
	m_Earth->Render();
	m_Moon->Render();
	
	//ui viewport
	glViewport(0, -Height/2 + 100, Width, Height);
	glClear(GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	m_MapCamera->LookAt();
	{
		m_Road->TestRender();
		m_Player->Render();
	}
	glPopMatrix();

	glViewport(0, 0, Width, Height);

	RenderExplain();
}

void CGameScene::Update()
{
	if (PlayQueueSize() > 0) {
		auto info = PopPlayQueue();
		SoundManager.Play(info.first, info.second);
	}

	m_Camera->Update();
	//m_Skybox->Update();
	m_Earth->Update();
	m_Moon->Update();

	if (!Start) return;
	
	m_Player->Update();
	m_Road->Update();
}

void CGameScene::Reshape(const int& w, const int& h)
{
	glViewport(0, 0, w, h);

	m_Camera->LookAt();
	
	glMatrixMode(GL_MODELVIEW);
}

void CGameScene::Timer(const int& value)
{
	Update();
	
	glutPostRedisplay();
}

void CGameScene::Keyboard(const unsigned char& key, const int& x, const int& y)
{
	if (!Explain) {
		Explain = true;
		return;
	}


	if (key == '=' || key == '+') {
		m_Camera->zoom(0.8f);
	}
	if (key == '-' || key == '_') {
		m_Camera->zoom(1.2f);
	}

	if (key == 'd' || key =='D') {
		m_Camera->Rotate(10, 0);
	}
	if (key == 'a' || key == 'A') {
		m_Camera->Rotate(-10, 0);
	}
	if (key == 's' || key =='S') {
		m_Camera->Rotate(0, -10);
	}
	if (key == 'w' || key =='W') {
		m_Camera->Rotate(0, 10);
	}

	m_Camera->LookAt();
}

void CGameScene::SpecialKeys(const int& key, const int& x, const int& y)
{
	if (!Explain) {
		Explain = true;
		return;
	}

	if (key == GLUT_KEY_F1) {
		if (Start) return;
		if (Perspective) {
			m_Camera->Initialize(CVector3D<>(0.f, 0.f, 0.f), 130, 0.1f, 600.f, 60);
			m_Camera->Rotate(25, 20);
			m_Camera->LookAt();
		}
		else {
			m_Camera->Initialize(CVector3D<>(0.f, 0.f, 0.f), 100, 0.1f, 600.f, 60);
			m_Camera->Rotate(0, 20);
			m_Camera->LookAt();
		}
		Perspective = !Perspective;
	}

	if (key == GLUT_KEY_UP || key == GLUT_KEY_LEFT || key == GLUT_KEY_RIGHT) {
		Start = true;
	}
	
	m_Player->SpecialKeys(key, x, y);
}
