#include "pch.h"

#include "Camera.h"
#include "Moon.h"
#include "Earth.h"
#include "PLAY_word.h"
#include "EXIT_word.h"
#include "SceneManager.h"
#include "TextureStorage.h"
//#include "SoundManager.h"

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
		//m_pMediator->GameStart();
	}
}

void CMainScene::SelectCursor()
{
	if (m_Cursor == k_PLAY) {
		m_CursorPos = m_PLAY->Get_Pos();
		m_CursorPos.y += 100;
		//m_pMediator->Cursor_PLAY();

		if (Nowdegree < 360 && Nowdegree >= 180) {
			IsClockWise = false;
		}
		else {
			IsClockWise = true;
		}
	}
	else if (m_Cursor == k_EXIT) {
		m_CursorPos = m_EXIT->Get_Pos();
		m_CursorPos.y += 100;
		//m_pMediator->Cursor_EXIT();

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
	LogoAlpha -= 0.05f;

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

	glColor3f(1.f, 1.f, 1.f);
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
	glTranslated(m_CursorPos.x, m_CursorPos.y, m_CursorPos.z);
	glRotated(90, 1, 0, 0);
	glutSolidCone(10, 15, 10, 10);
	glPopMatrix();

	//모델
	m_PLAY->Render();
	m_EXIT->Render();
}

CMainScene::CMainScene(CSceneManager* const changer)
{
	SoundManager.AddSound(
		"MainBGM"
		, ".\\Sound\\MainBGM\\Main.mp3"
		, SoundType::Stream
	);

	m_pSceneManager = changer;

	m_Camera = new CCamera();
	m_Moon = new CMoon(m_pMediator);
	m_Earth = new CEarth(m_pMediator);
	m_PLAY = new CPLAY_word(CVector3D<>(- 150, -300, 0));
	m_EXIT = new CEXIT_word(CVector3D<>(150, -300, 0));

	Initialize();

	m_textureStroage = new CTextureStorage;
	m_textureStroage->StoreBitmap(".\\Texture\\MainBack.bmp", m_BackgroundTextureID);
	m_textureStroage->StoreBitmap(".\\Texture\\main_mask.bmp", m_LogoMaskTextureID);
	m_textureStroage->StoreBitmap(".\\Texture\\main_image.bmp", m_LogoTextureID);

}

CMainScene::~CMainScene()
{
	delete m_Camera;
	delete m_Moon;
	delete m_Earth;
	delete m_PLAY;
}

void CMainScene::Initialize()
{
	SoundManager.Play("MainBGM");

	glEnable(GL_LIGHT0);
	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHT2);
	glDisable(GL_LIGHT3);

	m_Moon->Init_MainScene();
	m_Earth->Init_MainScene();
	m_PLAY->Init_MainScene();
	m_EXIT->Init_MainScene();

	m_Cursor = k_PLAY;
	SelectCursor();
	IsRotate = false;
	IsGameStart = false;
	IsClockWise = false;
	Nowdegree = 0;
	LogoAlpha = 1.f;
}

void CMainScene::SoundStop()
{
	SoundManager.Stop("MainBGM");
}

void CMainScene::Render()
{
	//배경
	WordRender();

	m_Camera->LookAt();
	
	glPushMatrix();
	glTranslated(0, -50, 0);
	glRotated(45, 0, 1, 0);
	glRotated(Nowdegree, 0, 1, 0);
	{
		m_Moon->Render();
		m_Earth->Render();
	}
	glPopMatrix();

	glClear(GL_DEPTH_BUFFER_BIT);
	float Left = -150;
	float Right = 150;
	float Top = 150 + 150;
	float Bottom = -150 + 150;
	glColor3f(1.f, 1.f, 1.f);
	glEnable(GL_BLEND);
	/*glBlendFunc(GL_DST_COLOR, GL_ZERO);
	glBindTexture(GL_TEXTURE_2D, m_LogoMaskTextureID);
	glBegin(GL_QUADS);
	glTexCoord2f(0.f, 1.f);
	glVertex3d(Left, Top, 0);
	glTexCoord2f(1.f, 1.f);
	glVertex3d(Right, Top, 0);
	glTexCoord2f(1.f, 0.f);
	glVertex3d(Right, Bottom, 0);
	glTexCoord2f(0.f, 0.f);
	glVertex3d(Left, Bottom, 0);
	glEnd();*/

	glColor4f(1.f, 1.f, 0.5f, LogoAlpha);
	glBlendFunc(GL_ONE, GL_ONE);
	glBindTexture(GL_TEXTURE_2D, m_LogoTextureID);
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

	glDisable(GL_BLEND);
	glClear(GL_DEPTH_BUFFER_BIT);
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
	m_Moon->Update();
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
	if (IsGameStart) return;

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
