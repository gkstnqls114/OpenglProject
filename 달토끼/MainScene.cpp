#include "pch.h"

#include "Mediator.h"
#include "Camera.h"
#include "Moon.h"
#include "Earth.h"
#include "PLAY_word.h"
#include "EXIT_word.h"
#include "SceneManager.h"

#include "TestScene.h"
#include "MainScene.h"


void CMainScene::ConfirmCursor()
{
	if (m_Cursor == k_EXIT) {
		//나중에 수정
		// 일단 임시사용
		exit(0);
	}
	else if (m_Cursor == k_PLAY) {
		//장면 넘어간다.
		m_pSceneChager->ChangeToGame();
	}
}

void CMainScene::SelectCursor()
{
	if (m_Cursor == k_EXIT) {
		m_CursorPos = m_EXIT->GetPos();
		m_CursorPos[1] += 100;
		m_PLAY->NotSelected();
		m_EXIT->Selected();
	}
	else if (m_Cursor == k_PLAY) {
		m_CursorPos = m_PLAY->GetPos();
		m_CursorPos[1] += 100;
		m_PLAY->Selected();
		m_EXIT->NotSelected();
	}
}

void CMainScene::WordRender()
{
	//앞에 있는 play, exit
	glClear(GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_WIDTH) / 2,
		- static_cast<float>(glutGet(GLUT_WINDOW_HEIGHT)) / 2, static_cast<float>(glutGet(GLUT_WINDOW_HEIGHT)) / 2,
		-1.f, 600);
	glMatrixMode(GL_MODELVIEW);

	//커서
	glColor3f(1.f, 1.f, 1.f);
	glPushMatrix();
	glTranslated(m_CursorPos[0], m_CursorPos[1], m_CursorPos[2]);
	glRotated(90, 1, 0, 0);
	glutSolidCone(10, 15, 10, 10);
	glPopMatrix();

	//모델
	m_PLAY->Render();
	m_EXIT->Render();
}

CMainScene::CMainScene(CSceneManager* const changer)
{
	std::cout << "받은 주소: " << changer;
	m_pSceneChager = changer;

	m_Mediator = new CMediator;

	m_Camera = new CCamera(m_Mediator);
	m_Camera->Initialize(CVector3D<>(0.f, 0.f, 0.f), 350, 0.1f, 600.f, 60);
	m_Camera->Rotate(0, 0);

	//m_Moon = new CMoon(CVector3D<>(80, 50, -100));
	m_Earth = new CEarth((CVector3D<>(-20, -50, 100)));
	m_PLAY = new CPLAY_word(CVector3D<>(- 150, -250, 0));
	m_EXIT = new CEXIT_word(CVector3D<>(150, -250, 0));

	SelectCursor();
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

	//m_Moon->Render();
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
	//m_Moon->Update();
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

	const int kENTER = 13;
	const int kSPACE = 32;
	if (key == kENTER || key == kSPACE) {
		ConfirmCursor();
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

	SelectCursor();
}
