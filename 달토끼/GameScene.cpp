#include "pch.h"
#include "Item.h"
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
		, ".\\Sound\\GamePlayBGM\\Chew_Chew_Island_Main_Theme.mp3"
		, SoundType::Stream
	);
	

	m_pSceneManager = changer;

	m_textureStroage = new CTextureStorage;
	m_textureStroage->StoreBitmap(".\\Texture\\Background.bmp", m_BackgroundTextureID);

	m_textureStroage = new CTextureStorage;
	m_textureStroage->StoreBitmap(".\\Texture\\Explain.bmp", m_ExplainTextureID);

	m_MapCamera = new CCamera();
	m_MapCamera->IsMapCamera();
	m_Camera = new CCamera();
	m_Player = new CPlayer();

	m_Road = new Road(75);
	int LastZ = m_Road->Get_LastPos().z;
	m_Skybox = new CSkybox(LastZ);

	m_Moon = new CMoon(m_pMediator);
	m_Earth = new CEarth();

	m_ItemEffectManager.Set_pPlayer(m_Player);
	m_ItemEffectManager.Set_pRoad(&m_Road->Get_FootBoardManager());
	Item::Set_pItemEffectManager(m_ItemEffectManager);

	m_Player->Set_PlayerSubjer(&m_PlayerObserver);
	m_Road->Set_RoadObserver(&m_RoadObserver);

	m_PlayerObserver.Add_Observer(m_MapCamera);
	m_PlayerObserver.Add_Observer(m_Camera);
	m_PlayerObserver.Add_Observer(m_Road);
	m_RoadObserver.Add_Observer(m_Player);

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

	glEnable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glDisable(GL_LIGHT2);
	glDisable(GL_LIGHT3);

	glEnable(GL_COLOR_MATERIAL);

	//////////////////////////////////// 오브젝트 초기화
	m_Road->Init_GameScene();
	m_Camera->Init_GameScene();
	m_Player->Init_GameScene();
	m_Moon->Init_GameScene();
	m_Earth->Init_GameScene();
	//////////////////////////////////// 오브젝트 초기화

	m_MapCamera->Initialize(CVector3D<>(0.f, 0.f, m_Road->Get_FirstPos().z * 5), 1100, 0.1f, 1500.f, 90);
	m_MapCamera->Rotate(0.f, 1.4f);
	m_MapCamera->Rotate(90, 0);

	GLdouble DownY = 300;
	CVector3D<> MoonPos = m_Road->Get_LastPos();
	CVector3D<> EarthPos = m_Road->Get_FirstPos();
	m_Earth->SetPos(CVector3D<>(EarthPos.x, EarthPos.y - DownY, EarthPos.z));
	m_Moon->SetPos(CVector3D<>(MoonPos.x, MoonPos.y - DownY + 150, MoonPos.z));

	Start = false;
	Explain = false;
	Perspective = false;
}

void CGameScene::SoundStop()
{
	SoundManager.Stop("GameBGM");
	m_Player->SoundStop();
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
		m_Road->Render();
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
	m_Skybox->Update();
	m_Earth->Update();
	m_Moon->Update();
	m_Road->Update();

	if (!Start) return;
	
	m_Player->Update();
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
			m_Camera->Init_ThirdPerspective();
		}
		else {
			m_Camera->Init_FistPerspective();
		}
		Perspective = !Perspective;
		return;
	}

	if (key == GLUT_KEY_UP || key == GLUT_KEY_LEFT || key == GLUT_KEY_RIGHT) {
		Start = true;
	}

	if (Start && Explain) {
		m_Road->StateChange_Disappear();
		m_Player->SpecialKeys(key, x, y);
	}
}
