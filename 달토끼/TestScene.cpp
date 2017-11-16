#include "pch.h"
#include "ObjModel.h"
#include "Player.h"
#include "Camera.h"
#include "Vector.h"
#include "Road.h"
#include "TestScene.h"


void CTestScene::RenderAxis()
{
	//좌표축 중심선을 그린다.

	//중심선
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

	//50pixel마다 점찍는다
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
	float distance = m_player->Get_JumpReach();

	std::cout << distance << "이다" << std::endl;
	
	m_road = new CRoad(distance);

	CVector temp_at(0.f, 0.f, 0.f);
	m_camera->Initialize(temp_at, 100, 0.1f, 600.f, 60);
	m_camera->Rotate(90 * 3.14 / 180, 0.f);

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
	//뭔가 해야하나?
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
			//m_camera->SetPosition(CVector(player_move_x, 0, player_move_z));
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
		//m_player->Keyboard(key, x, y);
	}

	if (key == '=' || key == '+') {
		m_camera->zoom(1.2f);
	}
	if (key == '-' || key == '_') {
		m_camera->zoom(0.8f);
	}

	if (key == 'd' || key =='D') {
		m_camera->Rotate(0.1f, 0.f);
	}
	if (key == 'a' || key == 'A') {
		m_camera->Rotate(-0.1f, 0.f);
	}
	if (key == 's' || key =='S') {
		m_camera->Rotate(0.f, -0.1f);
	}
	if (key == 'w' || key =='W') {
		m_camera->Rotate(0.f, 0.1f);
	}


	m_camera->LookAt();
}

void CTestScene::SpecialKeys(const int& key, const int& x, const int& y)
{
	if (nullptr != m_player) {
		m_player->SpecialKeys(key, x, y);
	}

	if (nullptr == m_camera) return;

}
