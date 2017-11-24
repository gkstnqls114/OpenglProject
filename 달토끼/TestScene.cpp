#include "pch.h"
#include "Mediator.h"
#include "Player.h"
#include "Camera.h"
#include "Vector3D.h"
#include "Road.h"
#include "TestScene.h"

void CGameScene::RenderAxis()
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

CGameScene::CGameScene()
{
	m_Mediator = new CMediator;

	m_Camera = new CCamera(m_Mediator);
	m_Camera->Initialize(CVector3D(0.f, 0.f, 0.f), 130, 0.1f, 600.f, 60);
	m_Camera->Rotate(25, 20);
	//m_Camera->Rotate(90, 0);

	m_Player = new CPlayer(m_Mediator);

	double distance = m_Player->Get_JumpReach();
	std::cout << distance << "�̴�" << std::endl;
	m_Road = new CRoad(distance, m_Mediator);

	m_Mediator->Set_Colleague(m_Player, m_Road, m_Camera);
}

CGameScene::~CGameScene()
{
	delete m_Player;
	m_Player = nullptr;

	delete m_Camera;
	m_Camera = nullptr;

	delete m_Road;
	m_Road = nullptr;

	delete m_Mediator;
	m_Mediator = nullptr;
}

void CGameScene::Initialize()
{
	//���� �ؾ��ϳ�?
}


void CGameScene::Render()
{
	RenderAxis();

	if (nullptr != m_Player){
		m_Player->Render();
	}

	if (nullptr != m_Road) {
		m_Road->Render();
	}
}

void CGameScene::Update()
{
	if (!Start) return;
	if (nullptr == m_Player) return;

	m_Player->Update();
	m_Road->Update();
	
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
