#include "pch.h"
#include "Mediator.h"
#include "Camera.h"
#include "Moon.h"
#include "Earth.h"
#include "PLAY_word.h"
#include "EXIT_word.h"
#include "MainScene.h"


void CMainScene::WordRender()
{
	//앞에 있는 play, exit
	glClear(GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_WIDTH) / 2,
		- static_cast<float>(glutGet(GLUT_WINDOW_HEIGHT)) / 2, static_cast<float>(glutGet(GLUT_WINDOW_HEIGHT)) / 2,
		0.1, 600);
	glMatrixMode(GL_MODELVIEW);
	glColor3f(1.f, 1.f, 1.f);
	m_PLAY->Render();
	//m_EXIT->Render();
}

CMainScene::CMainScene()
{
	m_Mediator = new CMediator;

	m_Camera = new CCamera(m_Mediator);
	m_Camera->Initialize(CVector3D<>(0.f, 0.f, 0.f), 350, 0.1f, 600.f, 60);
	m_Camera->Rotate(0, 0);

	m_Moon = new CMoon(CVector3D<>(80, 50, -100));
	m_Earth = new CEarth((CVector3D<>(-20, -50, 100)));
	m_PLAY = new CPLAY_word(CVector3D<>(- 150, -250, 0));

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
}


CMainScene::~CMainScene()
{
	delete m_Camera;
	delete m_Mediator;
	delete m_Moon;
	delete m_Earth;
	delete m_PLAY;
}

void CMainScene::Initialize()
{

}

void CMainScene::Render()
{
	RenderAxis();

	glPushMatrix();
	//glRotated(degree, 0, 1, 0);

	m_Moon->Render();
	m_Earth->Render();
	
	glPopMatrix();

	WordRender();
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

	degree += 1;

	glutPostRedisplay();
}

void CMainScene::Update()
{
	m_Moon->Update();
	m_Earth->Update();
	m_Camera->LookAt();
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
			m_PLAY->Selected();
		}
	}
	else if (key == GLUT_KEY_LEFT) {
		m_Cursor -= 1;
		
		if (m_Cursor > k_PLAY) {
			m_Cursor = k_EXIT;
			m_PLAY->NotSelected();
		}
	}
	else if (key == GLUT_ENTERED) {
		//확인

	}
}
