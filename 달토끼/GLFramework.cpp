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
	//메인 라이트
	GLfloat Main_ambient[] = { 1.f, 0.7f, 1.f, 1.0f };
	GLfloat Main_diffuse[] = { 1.f, 1.f, 1.f, 1.f };
	GLfloat Main_lightPos[] = { 0, 30, 0, 0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, Main_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Main_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, Main_lightPos);

	//임시로 쓰이는 라이트값
	//게임 라이트
	GLfloat Game_ambient[] = { 1.f, 0.7f, 1.f, 1.0f };
	GLfloat Game_diffuse[] = { 1.f, 1.f, 1.f, 1.f };
	GLfloat Game_lightPos[] = { 0, 30, -30, 0 };

	glLightfv(GL_LIGHT1, GL_AMBIENT, Game_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Game_diffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, Game_lightPos);

	//종료 라이트
	GLfloat Over_ambient[] = { 0.2f, 0.7f, 1.f, 1.0f };
	GLfloat Over_diffuse[] = { 1.f, 1.f, 1.f, 1.f };
	GLfloat Over_lightPos[] = { 0, 30, 0, 0 };

	glLightfv(GL_LIGHT2, GL_AMBIENT, Over_ambient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, Over_diffuse);
	glLightfv(GL_LIGHT2, GL_POSITION, Over_lightPos);

	//클리어 라이트
	GLfloat Clear_ambient[] = { 1.f, 1.f, 1.f, 1.0f };
	GLfloat Clear_diffuse[] = { 1.f, 1.f, 1.f, 1.f };
	GLfloat Clear_lightPos[] = { 0, 0, 30, 0 };

	glLightfv(GL_LIGHT3, GL_AMBIENT, Clear_ambient);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, Clear_diffuse);
	glLightfv(GL_LIGHT3, GL_POSITION, Clear_lightPos);

	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);
}

void CGLFramework::DrawScene()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	Render();

	glutSwapBuffers();
}

void CGLFramework::Render()
{
	m_SceneChager->SceneRender();
}

void CGLFramework::Reshape(int w, int h)
{
	m_SceneChager->SceneReshape(w, h);

	glutPostRedisplay();
}

void CGLFramework::Keyboard(unsigned char key, int x, int y)
{
	m_SceneChager->SceneKeyboard(key, x, y);
}

void CGLFramework::SpecialKeys(int key, int x, int y)
{
	m_SceneChager->SceneSpecialKeys(key, x, y);
}

void CGLFramework::Timer(int value)
{
	m_SceneChager->SceneTimer(value);

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
