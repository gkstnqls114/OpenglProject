#include "pch.h"
#include "Player.h"
#include "Camera.h"
#include "Mediator.h"
#include "SceneManager.h"
#include "Gameover.h"


void CGameOver::Ortho()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double Left = -glutGet(GLUT_WINDOW_WIDTH) / 2;
	double Right = glutGet(GLUT_WINDOW_WIDTH) / 2;
	double Top = static_cast<float>(glutGet(GLUT_WINDOW_HEIGHT)) / 2;
	double Bottom = -static_cast<float>(glutGet(GLUT_WINDOW_HEIGHT)) / 2;

	glOrtho(Left, Right, Bottom, Top, -100.f, 100);

	glMatrixMode(GL_MODELVIEW);
}

CGameOver::CGameOver(CSceneManager* const changer)
{
	m_pSceneManager = changer;
	m_pMediator = new CMediator(m_pSceneManager);

	m_Player = new CPlayer(m_pMediator);
	m_Camera = new CCamera(m_pMediator);
	
	m_pMediator->SetPlayer(m_Player);
	m_pMediator->SetCamera(m_Camera);

	Initialize();
}


CGameOver::~CGameOver()
{
	delete[] m_Camera;
	delete[] m_Player;
}

void CGameOver::Initialize()
{
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glDisable(GL_LIGHT3);

	m_pMediator->Init_GameOver();

	Ortho();
}

void CGameOver::Render()
{
	glPushMatrix();
		//glTranslated(0, -100, 0);
		glRotated(150, 0, 1, 0);
		//glScaled(8.f, 8.f, 8.f);
		m_Player->Render();
	glPopMatrix();
}

void CGameOver::Reshape(const int & w, const int & h)
{
	glViewport(0, 0, w, h);
	
	m_Camera->LookAt();

	glMatrixMode(GL_MODELVIEW);
}

void CGameOver::Timer(const int & value)
{
	Update();

	glutPostRedisplay();
}

void CGameOver::Update()
{

	m_Camera->LookAt();
}

void CGameOver::Keyboard(const unsigned char & key, const int & x, const int & y)
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

}

void CGameOver::SpecialKeys(const int & key, const int & x, const int & y)
{
	m_pMediator->GameScene();
}
