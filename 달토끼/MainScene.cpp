#include "pch.h"
#include "Mediator.h"
#include "Camera.h"
#include "Moon.h"
#include "Earth.h"
#include "MainScene.h"


CMainScene::CMainScene()
{
	m_Mediator = new CMediator;

	m_Camera = new CCamera(m_Mediator);
	m_Camera->Initialize(CVector3D(-30.f, 0.f, 0.f), 300, 0.1f, 600.f, 60);
	m_Camera->Rotate(0, 0);

	m_Moon = new CMoon(CVector3D(50, 50, -100));
	m_Earth = new CEarth((CVector3D(-50, -50, 100)));

}


CMainScene::~CMainScene()
{
	delete m_Camera;
	delete m_Mediator;
	delete m_Moon;
	delete m_Earth;
}

void CMainScene::Initialize()
{

}

void CMainScene::Render()
{
	RenderAxis();

	glPushMatrix();
	m_Moon->Render();
	glPopMatrix();

	glPushMatrix();
	m_Earth->Render();
	glPopMatrix();
}

void CMainScene::Reshape(const int & w, const int & h)
{
	glViewport(0, 0, w, h);

	m_Camera->LookAt();

	glMatrixMode(GL_MODELVIEW);
}

void CMainScene::Timer(const int & value)
{
	Update();

	glutPostRedisplay();
}

void CMainScene::Update()
{
	m_Moon->Float();
	m_Earth->Float();

	m_Moon->Update();
	m_Earth->Update();
}

void CMainScene::Keyboard(const unsigned char & key, const int & x, const int & y)
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

void CMainScene::SpecialKeys(const int & key, const int & x, const int & y)
{
	if (key == GLUT_KEY_RIGHT) {
		m_Cursor += 1;

		if (m_Cursor > k_EXIT) {
			m_Cursor = k_PLAY;
		}
	}
	else if (key == GLUT_KEY_LEFT) {
		m_Cursor -= 1;
		
		if (m_Cursor > k_PLAY) {
			m_Cursor = k_EXIT;
		}
	}
	else if (key == GLUT_ENTERED) {
		//»Æ¿Œ

	}
}
