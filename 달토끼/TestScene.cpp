#include "pch.h"
#include "SceneManager.h"
#include "Mediator.h"
#include "Camera.h"
#include "Player.h"
#include "Texture.h"
#include "TestScene.h"


CTestScene::CTestScene(CSceneManager* const changer)
{
	m_pSceneManager = changer;

	m_pMediator = new CMediator(m_pSceneManager);

	m_Camera = new CCamera(m_pMediator);
	m_Camera->Initialize(CVector3D<>(0.f, 0.f, 0.f), 100, 0.1f, 600.f, 60);
	m_Camera->Rotate(25, 20);

	m_Player = new CPlayer(m_pMediator);

	GLfloat gray[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	GLfloat ambient[] = { 1.f, 0.7f, 1.f, 1.0f };
	GLfloat diffuse[] = { 1.f, 1.f, 1.f, 1.f };
	GLfloat  specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	GLfloat lightPos[] = {0, 100, 10, 0};
	
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray); 
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glMateriali(GL_FRONT, GL_SHININESS, 64);

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_TEXTURE_2D);
}


CTestScene::~CTestScene()
{

}

void CTestScene::Initialize()
{

}

void CTestScene::Render()
{
	RenderAxis();

	//¹Ù´Ú
	glColor3f(0.7f, 0.7f, 0.7f);
	glBegin(GL_QUADS);
	glVertex3d(50, 0, 50);
	glVertex3d(-50, 0, 50);
	glVertex3d(-50, 0, -50);
	glVertex3d(50, 0, -50);
	glEnd();

	m_Player->Render();
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

}
