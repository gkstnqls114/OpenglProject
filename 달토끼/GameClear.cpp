#include "pch.h"
#include "SceneManager.h"
#include "TextureStorage.h"
#include "ClearObject.h"
#include "Earth.h"
#include "Camera.h"
#include "GAMECLEAR_word.h"
#include "GameClear.h"


CGameClear::CGameClear(CSceneManager* const changer)
{
	SoundManager.AddSound(
		"GameClearBGM"
		, "./Sound/GameClearBGM/Baauer-01-Harlem Shake.mp3"
		, SoundType::Stream
	);

	m_textureStroage = new CTextureStorage;
	m_textureStroage->StoreBitmap("Background.bmp", m_BackgroundTextureID);

	m_pSceneManager = changer;

	m_Camera = new CCamera();
	m_GAMECLEAR = new CGAMECLEAR_word(CVector3D<>(0, 200, -100));

	m_earth = new CEarth(m_pMediator);
	m_ClearObj = new CClearObject;
}

CGameClear::~CGameClear()
{
	delete[] m_Camera;
	delete[] m_pMediator;
	delete[] m_ClearObj;
	delete[] m_GAMECLEAR;
	delete[] m_textureStroage;
}

void CGameClear::Initialize()
{
	SoundManager.Play("GameClearBGM");

	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHT2);
	glEnable(GL_LIGHT3);


}

void CGameClear::SoundStop()
{
	SoundManager.Stop("GameClearBGM");
}

void CGameClear::Render()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double Left = -glutGet(GLUT_WINDOW_WIDTH) / 2;
	double Right = glutGet(GLUT_WINDOW_WIDTH) / 2;
	double Top = static_cast<float>(glutGet(GLUT_WINDOW_HEIGHT)) / 2;
	double Bottom = -static_cast<float>(glutGet(GLUT_WINDOW_HEIGHT)) / 2;

	glOrtho(Left, Right, Bottom, Top, -600.f, 300);
	glMatrixMode(GL_MODELVIEW);

	glColor3f(LIGHTRGB.x, LIGHTRGB.y, LIGHTRGB.z);
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

	glEnable(GL_BLEND);
	//ÀðÀò

	glDisable(GL_BLEND);

	glClear(GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glTranslated(-150, 100, -100);
	glScaled(0.5f, 0.5f, 0.5f);
	m_earth->Render();
	glPopMatrix();
	
	glPushMatrix();
	glTranslated(0, 180, 0);
	glRotated(10, 1, 0, 0);
	glScaled(0.28f, 0.28f, 0.28f);
	m_GAMECLEAR->Render();
	glPopMatrix();

	glPushMatrix();
	glTranslated(250, -350, 0);
	glScaled(1.7f, 1.7f, 1.7f);
	m_ClearObj->Render();
	glPopMatrix();
}

void CGameClear::Reshape(const int & w, const int & h)
{
	glViewport(0, 0, w, h);

	m_Camera->LookAt();

	glMatrixMode(GL_MODELVIEW);
}

void CGameClear::Timer(const int & value)
{

	Update();

	glutPostRedisplay();

}

void CGameClear::Update()
{
	m_ClearObj->Update();
	m_earth->Update();
}

void CGameClear::Keyboard(const unsigned char & key, const int & x, const int & y)
{

}

void CGameClear::SpecialKeys(const int & key, const int & x, const int & y)
{

}
