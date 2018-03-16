#include "pch.h"
#include "SceneManager.h"
#include "Camera.h"
#include "Player.h"
#include "Texture.h"
#include "Road.h"
#include "PlayerObserver.h"
#include "RoadObserver.h"
#include "TestScene.h"


CTestScene::CTestScene()
{
	m_Camera = new CCamera();
	m_Player = new CPlayer();
	m_Road = new Road(100);

	m_Camera->Initialize(CVector3D<>(0.f, 0.f, 0.f), 100, 0.1f, 600.f, 60);
	m_Camera->Rotate(25, 20);

	m_Player->Set_PlayerSubjer(&m_PlayerObserver);
	m_Road->Set_RoadObserver(&m_RoadObserver);
	m_PlayerObserver.Add_Observer(m_Camera);
	m_PlayerObserver.Add_Observer(m_Road);
	m_RoadObserver.Add_Observer(m_Player);

}


CTestScene::~CTestScene()
{

}

void CTestScene::Initialize()
{
	m_Player->Init_GameScene();
}

void CTestScene::SoundStop()
{
}

void CTestScene::Render()
{
	RenderAxis();

	//¹Ù´Ú
	//glColor3f(0.7f, 0.7f, 0.7f);
	//glBegin(GL_QUADS);
	//glVertex3d(50, 0, 50);
	//glVertex3d(-50, 0, 50);
	//glVertex3d(-50, 0, -50);
	//glVertex3d(50, 0, -50);
	//glEnd();

	m_Player->Render();
	m_Road->TestRender();
}

void CTestScene::Reshape(const int & w, const int & h)
{
	glViewport(0, 0, w, h);

	m_Camera->LookAt();

	glMatrixMode(GL_MODELVIEW);
}

void CTestScene::Timer(const int & value)
{
	Update();

	glutPostRedisplay();
}

void CTestScene::Update()
{
	m_Player->Update();
	m_Road->Update();
}

void CTestScene::Keyboard(const unsigned char & key, const int & x, const int & y)
{
	if (key == '=' || key == '+') {
		m_Camera->zoom(0.8f);
	}
	if (key == '-' || key == '_') {
		m_Camera->zoom(1.2f);
	}

	if (key == 'd' || key == 'D') {
		m_Camera->Rotate(10, 0);
	}
	if (key == 'a' || key == 'A') {
		m_Camera->Rotate(-10, 0);
	}
	if (key == 's' || key == 'S') {
		m_Camera->Rotate(0, -10);
	}
	if (key == 'w' || key == 'W') {
		m_Camera->Rotate(0, 10);
	}

	m_Camera->LookAt();
}

void CTestScene::SpecialKeys(const int & key, const int & x, const int & y)
{
	m_Road->StateChange_Disappear();
	m_Player->SpecialKeys(key, x, y);
}
