#include "pch.h"
#include "Player.h"
#include "Camera.h"
#include "Vector.h"
#include "TestScene.h"


CTestScene::CTestScene()
{
	
}

CTestScene::~CTestScene()
{
	delete m_player;
	m_player = nullptr;


	delete m_camera;
	m_camera = nullptr;
}

void CTestScene::Initialize()
{
	if (m_player == nullptr) {
		m_player = new CPlayer();
	}
	if (m_camera == nullptr) {
		m_camera = new CCamera;
	}

	CVector temp_pos(0.f, 0.f, 0.f);
	m_camera->Initialize(temp_pos, 100, 0, 100, 60);
}


void CTestScene::Render()
{
	//Áß½É¼±
	glLineWidth(5);

	//glPushMatrix();
		glColor3f(1.f, 0.f, 0.f);
		glBegin(GL_LINES);
			glVertex3f(0, 0, 0);
			glVertex3f(1, 0, 0);
		glEnd();
	
		//y
		glColor3f(0.f, 1.f, 0.f);
		glBegin(GL_LINES);
			glVertex3d(0, 0, 0);
			glVertex3d(0, 1, 0);
		glEnd();

		//z
		glColor3f(0.f, 0.f, 1.f);
		glBegin(GL_LINES);
			glVertex3d(0, 0, 0);
			glVertex3d(0, 0, 1);
		glEnd();
	//glPopMatrix();

	glLineWidth(1);
	glColor3f(0.7f, 0.1f, 0.1f);
	if (nullptr != m_player){
		m_player->Render();
	}

}

void CTestScene::Update()
{
	if (nullptr != m_player) {
		m_player->Update();
	}

}

void CTestScene::Reshape(const int& w, const int& h)
{
	glViewport(0, 0, w, h);

	m_camera->LookAt();
	
	glMatrixMode(GL_MODELVIEW);
}

void CTestScene::Timer(const int& value)
{
	Update();
	
	glutPostRedisplay();
}

void CTestScene::Keyboard(const unsigned char& key, const int& x, const int& y)
{
	if (nullptr != m_player) {
		m_player->Keyboard(key, x, y);
	}
}

void CTestScene::SpecialKeys(const int& key, const int& x, const int& y)
{
	if (nullptr != m_player) {
		m_player->SpecialKeys(key, x, y);
	}
}
