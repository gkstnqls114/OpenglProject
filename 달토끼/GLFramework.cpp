#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameScene.h"
#include "MainScene.h"
#include "TestScene.h"
#include "GLFramework.h"


CGLFramework::CGLFramework()
{

}

CGLFramework::~CGLFramework()
{
}

void CGLFramework::Initialize(int argc, char ** argv, int width, int height, int x, int y, int DisplayMode)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(DisplayMode);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(x, y);
	glutCreateWindow("MOON RABBIT");

	m_SceneChager = new CSceneManager;


	//임시로 쓰이는 라이트값
	//게임 라이트
	GLfloat gray0[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	GLfloat ambient0[] = { 1.f, 0.7f, 1.f, 1.0f };
	GLfloat diffuse0[] = { 1.f, 1.f, 1.f, 1.f };
	GLfloat  specref0[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	GLfloat lightPos0[] = { 0, 30, -30, 0 };

	//glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	//glMateriali(GL_FRONT, GL_SHININESS, 64);

	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient0);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse0);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos0);

	//임시로 쓰이는 라이트값
	//메인 라이트
	GLfloat gray1[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	GLfloat ambient1[] = { 1.f, 0.7f, 1.f, 1.0f };
	GLfloat diffuse1[] = { 1.f, 1.f, 1.f, 1.f };
	GLfloat  specref1[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	GLfloat lightPos1[] = { 0, 30, 0, 0 };

	//glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	//glMateriali(GL_FRONT, GL_SHININESS, 64);

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient1);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse1);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos1);

	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);
}

void CGLFramework::DrawScene()
{
	glClearColor(0.5f, 0.5f, 0.5f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	Render();

	glutSwapBuffers();
}

void CGLFramework::Render()
{
	m_SceneChager->SceneRender();

	//if (m_CurrScene) m_CurrScene->Render();
}

void CGLFramework::Reshape(int w, int h)
{
	m_SceneChager->SceneReshape(w, h);

	//if (m_CurrScene) m_CurrScene->Reshape(w, h);

	glutPostRedisplay();
}

void CGLFramework::Keyboard(unsigned char key, int x, int y)
{
	m_SceneChager->SceneKeyboard(key, x, y);
	
	//if (m_CurrScene) m_CurrScene->Keyboard(key, x, y);
}

void CGLFramework::SpecialKeys(int key, int x, int y)
{
	m_SceneChager->SceneSpecialKeys(key, x, y);

	//if(m_CurrScene) m_CurrScene->SpecialKeys(key, x, y);
}

void CGLFramework::Timer(int value)
{
	m_SceneChager->SceneTimer(value);

	//if (m_CurrScene) m_CurrScene->Timer(value);

	glutTimerFunc(m_fps, fnTimer, 1);
}

void CGLFramework::RegisterDrawFunction(DrawFunc && draw)
{
	fnDraw = draw;
}

void CGLFramework::RegisterTimerFunction(TimerFunc && timer)
{
	fnTimer = timer;
}

void CGLFramework::RegisterReshapeFunction(ReshapeFunc && reshape)
{
	fnReshape = reshape;
}

void CGLFramework::RegisterKeyboardFunction(KeyboardFunc && keyboard)
{
	fnKeyboard = keyboard;
}

void CGLFramework::RegisterSpecialKeysFunction(SpecialKeysFunc && specialkeys)
{
	fnSpecialKeys = specialkeys;
}

void CGLFramework::Bind()
{
	glutDisplayFunc(fnDraw);
	glutReshapeFunc(fnReshape);
	glutKeyboardFunc(fnKeyboard);
	glutSpecialFunc(fnSpecialKeys);

	glutTimerFunc(m_fps, fnTimer, 1);
}

void CGLFramework::ChangeScene(CScene * newScene)
{
	//auto old = m_CurrScene;
	//m_CurrScene = newScene;
	//delete old;
}
