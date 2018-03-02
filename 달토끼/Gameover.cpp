#include "pch.h"
#include "Player.h"
#include "Camera.h"
#include "GAMEOVER_word.h"
#include "SceneManager.h"
#include "Gameover.h"



CGameOver::CGameOver(CSceneManager* const changer)
{
	SoundManager.AddSound(
		"GameOverBGM"
		, "./Sound/GameOverBGM/Isaku98.mp3"
		, SoundType::Stream
	);

	m_pSceneManager = changer;

	m_Player = new CPlayer();
	m_Camera = new CCamera();
	m_GAMEOVER = new CGAMEOVER_word(CVector3D<>(0, -200, 0));

	Initialize();
}


CGameOver::~CGameOver()
{
	delete[] m_Camera;
	delete[] m_Player;
	delete[] m_GAMEOVER;
}

void CGameOver::Initialize()
{
	SoundManager.Play("GameOverBGM");

	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glDisable(GL_LIGHT3);

}

void CGameOver::SoundStop()
{
	SoundManager.Stop("GameOverBGM");
}

void CGameOver::Render()
{
	glPushMatrix();
		glRotated(150, 0, 1, 0);
		m_Player->Render();
	glPopMatrix();

	glPushMatrix();
	glScaled(0.04f, 0.04f, 0.04f);
	m_GAMEOVER->Render();
	glPopMatrix();
}

void CGameOver::Reshape(const int & w, const int & h)
{
	glViewport(0, 0, w, h);
	
	m_Camera->LookAt();

	glMatrixMode(GL_MODELVIEW);
}

void CGameOver::Timer(const int & value)
{
	Update();

	glutPostRedisplay();
}

void CGameOver::Update()
{

	m_Camera->LookAt();
}

void CGameOver::Keyboard(const unsigned char & key, const int & x, const int & y)
{

}

void CGameOver::SpecialKeys(const int & key, const int & x, const int & y)
{

}
