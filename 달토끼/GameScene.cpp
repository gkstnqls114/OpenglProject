#include "pch.h"
#include "SceneManager.h"
#include "Mediator.h"
#include "Player.h"
#include "Moon.h"
#include "Earth.h"
#include "Camera.h"
#include "Vector3D.h"
#include "Road.h"
#include "GameScene.h"

CGameScene::CGameScene(CSceneManager* const changer)
{
	m_pSceneManager = changer;

	m_Mediator = new CMediator;

	m_Camera = new CCamera(m_Mediator);
	m_Camera->Initialize(CVector3D<>(0.f, 0.f, 0.f), 130, 0.1f, 600.f, 60);
	m_Camera->Rotate(25, 20);
	//m_Camera->Rotate(90, 0);

	m_Player = new CPlayer(m_Mediator);

	double distance = m_Player->Get_JumpReach();
	std::cout << distance << "이다" << std::endl;
	m_Road = new CRoad(distance, m_Mediator);

	GLdouble DownY = 60;
	CVector3D<> MoonPos = m_Road->GetLastPos();
	m_Moon = new CMoon(CVector3D<>(MoonPos[0] , MoonPos[1]- DownY, MoonPos[2]));

	CVector3D<> EarthPos = m_Road->GetFirstPos();
	m_Earth = new CEarth(CVector3D<>(EarthPos[0], EarthPos[1] - DownY + 10, EarthPos[2]));

	m_Mediator->Set_Colleague(m_Player, m_Road, m_Camera);

	//임시로 쓰이는 라이트값
	GLfloat gray[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	GLfloat ambient[] = { 1.f, 0.7f, 1.f, 1.0f };
	GLfloat diffuse[] = { 1.f, 1.f, 1.f, 1.f };
	GLfloat  specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	GLfloat lightPos[] = { 0, 100, 10, 0 };

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glMateriali(GL_FRONT, GL_SHININESS, 64);

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//임시로 쓰이는 라이트값
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
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

	delete m_Mediator;
	m_Mediator = nullptr;
}

void CGameScene::Initialize()
{
	//뭔가 해야하나?
}


void CGameScene::Render()
{
	RenderAxis();

	m_Player->Render();
	m_Road->Render();
	//m_Earth->Render();
	//m_Moon->Render();
}

void CGameScene::Update()
{
	if (!Start) return;
	
	m_Player->Update();
	//m_Road->Update();
	m_Camera->Update();
	m_Earth->Update();
	m_Moon->Update();
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
	if (nullptr != m_Player) {
		//m_Player->Keyboard(key, x, y);
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
	if (!Start) {
		Start = true;
	}

	m_Player->SpecialKeys(key, x, y);
}
