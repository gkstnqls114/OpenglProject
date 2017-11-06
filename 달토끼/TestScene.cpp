#include "pch.h"
#include "Player.h"
#include "ObjModel.h"
#include "TestScene.h"


CTestScene::CTestScene()
{
	
}

CTestScene::~CTestScene()
{
	delete m_player;
	m_player = nullptr;

	delete m_obj;
	m_obj = nullptr;
}

void CTestScene::Initialize()
{
	if (m_player == nullptr) {
		m_player = new CPlayer();
	}

}


void CTestScene::Render()
{
	glColor3f(0.f, 0.f, 0.f);
	if (nullptr != m_player){
		m_player->Render();
	}
	if (nullptr != m_obj) {
		//m_obj->Render();
	}
}

void CTestScene::Update()
{
	if (nullptr != m_player) {
		m_player->Update();
	}

}

void CTestScene::Reshape(int w, int h)
{

}

void CTestScene::Timer(int value)
{
	glutPostRedisplay();
}

void CTestScene::Keyboard(unsigned char key, int x, int y)
{
	if (nullptr != m_player) {
		m_player->Keyboard(key, x, y);
	}
}
