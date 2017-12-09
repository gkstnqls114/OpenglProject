#include "pch.h"

#include "Mediator.h"
#include "Camera.h"
#include "Moon.h"
#include "Earth.h"
#include "PLAY_word.h"
#include "EXIT_word.h"
#include "SceneManager.h"
#include "TextureStorage.h"

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
		IsGameStart = true;
		m_pMediator->GameStart();
	}
}

void CMainScene::SelectCursor()
{
	if (m_Cursor == k_PLAY) {
		m_CursorPos = m_PLAY->GetPos();
		m_CursorPos[1] += 100;
		m_pMediator->Cursor_PLAY();

		if (Nowdegree < 360 && Nowdegree >= 180) {
			IsClockWise = false;
		}
		else {
			IsClockWise = true;
		}
	}
	else if (m_Cursor == k_EXIT) {
		m_CursorPos = m_EXIT->GetPos();
		m_CursorPos[1] += 100;
		m_pMediator->Cursor_EXIT();

		if (Nowdegree < 180 && Nowdegree >= 0) {
			IsClockWise = false;
		}
		else {
			IsClockWise = true;
		}
	}

	IsRotate = true;
}

void CMainScene::RotateUpdate()
{
	if (!IsRotate) return;

	if (IsClockWise) {
		//시계방향회전
		Nowdegree -= 2;
	}
	else {
		//반시계 회전
		Nowdegree += 2;
	}
	
	if (m_Cursor == k_EXIT && abs(Nowdegree) == 180) {
		Nowdegree = 180;
	}
	else if (m_Cursor == k_PLAY && abs(Nowdegree) == 360) {
		Nowdegree = 0;
	}
	

	const bool IsRotateFinish_PLAY =
		m_Cursor == k_PLAY && Nowdegree == k_PLAYdegree;
	if (IsRotateFinish_PLAY) {
		IsRotate = false;
	}
	const bool IsRotateFinish_EXIT = 
		m_Cursor == k_EXIT && Nowdegree == k_EXITdegree;
	if (IsRotateFinish_EXIT) {
		IsRotate = false;
	}
}

void CMainScene::WordRender()
{
	//앞에 있는 play, exit
	glClear(GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double Left = -glutGet(GLUT_WINDOW_WIDTH) / 2;
	double Right = glutGet(GLUT_WINDOW_WIDTH) / 2;
	double Top = static_cast<float>(glutGet(GLUT_WINDOW_HEIGHT)) / 2;
	double Bottom = -static_cast<float>(glutGet(GLUT_WINDOW_HEIGHT)) / 2;

	glOrtho(Left, Right, Bottom, Top, -100.f, 100);
	glMatrixMode(GL_MODELVIEW);

	glBindTexture(GL_TEXTURE_2D, m_BackgroundTextureID);
		glBegin(GL_QUADS);
		glTexCoord2f(0.f, 1.f);
		glVertex3d(Left, Top, 0);
		glTexCoord2f(1.f, 1.f);
		glVertex3d(Right, Top, 0);
		glTexCoord2f(1.f, 0.f);
		glVertex3d(Right, Bottom, 0);
		glTexCoord2f(0.f, 0.f);
		glVertex3d(Left, Bottom, 0);
		glEnd();
	glClear(GL_DEPTH_BUFFER_BIT);

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
	m_pSceneManager = changer;
	m_pMediator = new CMediator(m_pSceneManager);

	m_Camera = new CCamera(m_pMediator);
	//m_Moon = new CMoon(CVector3D<>(80, 50, -100));
	m_Earth = new CEarth(m_pMediator);
	m_PLAY = new CPLAY_word(CVector3D<>(- 150, -300, 0));
	m_EXIT = new CEXIT_word(CVector3D<>(150, -300, 0));

	m_pMediator->SetMoon(m_Moon);
	m_pMediator->SetEarth(m_Earth);
	m_pMediator->SetPLAYWORD(m_PLAY);
	m_pMediator->SetEXITWORD(m_EXIT);
	m_pMediator->SetCamera(m_Camera);

	Initialize();

	m_textureStroage = new CTextureStorage;
	m_textureStroage->StoreBitmap("MainBack.bmp", m_BackgroundTextureID);

}

CMainScene::~CMainScene()
{
	delete m_Camera;
	delete m_pMediator;
	delete m_Moon;
	delete m_Earth;
	delete m_PLAY;
}

void CMainScene::Initialize()
{
	m_pMediator->Init_MainScene();
	m_Cursor = k_PLAY;
	SelectCursor();
	IsRotate = false;
	IsGameStart = false;
	IsClockWise = false;
	Nowdegree = 0;
}

void CMainScene::Render()
{
	//배경
	WordRender();

	m_Camera->LookAt();
	
	RenderAxis();

	glPushMatrix();
	glRotated(Nowdegree, 0, 1, 0);
	{
		//m_Moon->Render();
		m_Earth->Render();
	}
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
	//m_Moon->Update();
	m_Earth->Update();

	m_PLAY->Update();
	m_EXIT->Update();

	RotateUpdate();

	m_Camera->LookAt();
}

void CMainScene::Keyboard(const unsigned char & key, const int & x, const int & y)
{
	if (IsGameStart) return;

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
		
		if (m_Cursor < k_PLAY) {
			m_Cursor = k_EXIT;
		}
	}

	SelectCursor();
}
