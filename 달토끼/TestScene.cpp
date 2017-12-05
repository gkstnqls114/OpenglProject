#include "pch.h"
#include "Mediator.h"
#include "Camera.h"
#include "Player.h"
#include "Texture.h"
#include "TestScene.h"


CTestScene::CTestScene()
{
	m_Mediator = new CMediator;

	m_Camera = new CCamera(m_Mediator);
	m_Camera->Initialize(CVector3D(0.f, 0.f, 0.f), 100, 0.1f, 600.f, 60);
	m_Camera->Rotate(25, 20);

	m_Player = new CPlayer(m_Mediator);

	m_texture = new CTexture();
	//텍스처와 갤체 결합
	glBindTexture(GL_TEXTURE_2D, texture_object);
	//이미지 로드
	m_texture->LoadDIBitmap("Rabit_Body(24bmp).bmp");
	//텍스쳐 설정 정의
	glTexImage2D(
		GL_TEXTURE_2D,	0, 3,
		m_texture->GetWidth(), m_texture->GetHegiht(),
		0, GL_BGR_EXT, GL_UNSIGNED_BYTE, m_texture->GetTextureBit()
	);


	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHT0);
}


CTestScene::~CTestScene()
{

}

void CTestScene::Initialize()
{

}

void CTestScene::Render()
{
	RenderAxis();

	//glEnable(GL_TEXTURE_2D);
	//바닥
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	
	glBindTexture(GL_TEXTURE_2D, texture_object);
	glColor3f(0.7f, 0.7f, 0.7f);
	glBegin(GL_QUADS);
	glTexCoord2f(1.f, 1.f);
	glVertex3d(50, 0, 50);

	glTexCoord2f(0.f, 1.f);
	glVertex3d(-50, 0, 50);

	glTexCoord2f(0.f, 0.f);
	glVertex3d(-50, 0, -50);

	glTexCoord2f(1.f, 0.f);
	glVertex3d(50, 0, -50);
	glEnd();

	//glDisable(GL_TEXTURE_2D);
	glColor3f(1.f, 0.5f, 0.5f);
	m_Player->Render();
}

void CTestScene::Reshape(const int & w, const int & h)
{
	glViewport(0, 0, w, h);

	m_Camera->LookAt();

	glMatrixMode(GL_MODELVIEW);
}

void CTestScene::Timer(const int & value)
{
	Update();

	glutPostRedisplay();
}

void CTestScene::Update()
{
}

void CTestScene::Keyboard(const unsigned char & key, const int & x, const int & y)
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

	m_Camera->LookAt();
}

void CTestScene::SpecialKeys(const int & key, const int & x, const int & y)
{
}
