#include "pch.h"
#include "Player.h"
#include "Camera.h"
#include "Vector.h"
#include "Road.h"
#include "TestScene.h"


void CTestScene::RenderAxis()
{
	//��ǥ�� �߽ɼ��� �׸���.

	//�߽ɼ�
	//glPushMatrix();
	glColor3f(1.f, 0.f, 0.f);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(1000, 0, 0);
	glEnd();



	//y
	glColor3f(0.f, 1.f, 0.f);
	glBegin(GL_LINES);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 1000, 0);
	glEnd();

	//z
	glColor3f(0.f, 0.f, 1.f);
	glBegin(GL_LINES);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 0, 1000);
	glEnd();

	//50pixel���� ����´�
	glPointSize(10);
	glBegin(GL_POINTS);
	for (int x = 0; x < 100; ++x) {
		glColor3f(1, 0, 0);
		glVertex3d(10 * x, 0, 0);

		glColor3f(0, 1, 0);
		glVertex3d(0, 10 * x, 0);

		glColor3f(0, 0, 1);
		glVertex3d(0, 0, -10 * x);
	}
	glEnd();
	glPointSize(1);

}

CTestScene::CTestScene()
{
	m_player = new CPlayer();
	m_camera = new CCamera();
	m_road = new CRoad();

	CVector temp_at(0.f, 0.f, 0.f);
	m_camera->Initialize(temp_at, 100, 0.1f, 600.f, 60);
	m_camera->Rotate(0.3f, 0.5f);
}

CTestScene::~CTestScene()
{
	delete m_player;
	m_player = nullptr;

	delete m_camera;
	m_camera = nullptr;

	delete m_road;
	m_road = nullptr;
}

void CTestScene::Initialize()
{
	//���� �ؾ��ϳ�?
}


void CTestScene::Render()
{
	RenderAxis();

	if (nullptr != m_player){
		m_player->Render();
	}

	if (nullptr != m_road) {
		m_road->Render();
	}

}

void CTestScene::Update()
{
	if (nullptr == m_player) return;

	m_player->Update();
	

	if (nullptr != m_camera) {
	
		float player_move_x = m_player->Get_VectorX();
		float player_move_z = m_player->Get_VectorZ();
		if (player_move_x != 0 || player_move_z != 0)
		{
			m_camera->Move(CVector(player_move_x, 0, player_move_z));
		}
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
