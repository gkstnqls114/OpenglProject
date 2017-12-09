#include "pch.h"
#include "SceneManager.h"
#include "Mediator.h"
#include "GameClear.h"


CGameClear::CGameClear(CSceneManager* const changer)
{
	m_pSceneManager = changer;
	m_pMediator = new CMediator(m_pSceneManager);
}

CGameClear::~CGameClear()
{

}

void CGameClear::Initialize()
{
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
}

void CGameClear::Render()
{
}

void CGameClear::Reshape(const int & w, const int & h)
{
}

void CGameClear::Timer(const int & value)
{
}

void CGameClear::Update()
{
}

void CGameClear::Keyboard(const unsigned char & key, const int & x, const int & y)
{
	m_pSceneManager->ChangeToMain();
}

void CGameClear::SpecialKeys(const int & key, const int & x, const int & y)
{

}
