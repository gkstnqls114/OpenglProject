#include "pch.h"
#include "SceneManager.h"
#include "Mediator.h"
#include "Camera.h"
#include "GAMECLEAR_word.h"
#include "GameClear.h"


CGameClear::CGameClear(CSceneManager* const changer)
{
	SoundManager.AddSound(
		"GameClearBGM"
		, "./Sound/GameClearBGM/ViviC Heart Session!.mp3"
		, SoundType::Stream
	);

	m_pSceneManager = changer;
	m_pMediator = new CMediator(m_pSceneManager);

	m_Camera = new CCamera(m_pMediator);
	m_GAMECLEAR = new CGAMECLEAR_word(CVector3D<>(0, -200, 0));

	m_pMediator->SetPlayer(m_Player);
	m_pMediator->SetCamera(m_Camera);

}

CGameClear::~CGameClear()
{
	delete[] m_Camera;
	//delete[] m_Player;
	delete[] m_GAMECLEAR;
}

void CGameClear::Initialize()
{
	SoundManager.Play("GameClearBGM");

	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHT2);
	glEnable(GL_LIGHT3);

	m_pMediator->Init_GameOver();

}

void CGameClear::SoundStop()
{
	SoundManager.Stop("GameClearBGM");
}

void CGameClear::Render()
{
	glPushMatrix();
	glScaled(0.04f, 0.04f, 0.04f);
	m_GAMECLEAR->Render();
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
}

void CGameClear::Keyboard(const unsigned char & key, const int & x, const int & y)
{
}

void CGameClear::SpecialKeys(const int & key, const int & x, const int & y)
{
	m_pMediator->MainScene();
}
