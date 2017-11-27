#include "pch.h"
#include "Scene.h"
#include "GameScene.h"
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
	glutCreateWindow("Example1");

	m_CurrScene =
		new CGameScene{};
	m_CurrScene->Initialize();
}

void CGLFramework::DrawScene()
{
	glClearColor(0.5f, 0.5f, 0.5f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	Render();

	glutSwapBuffers();
}

void CGLFramework::Render()
{
	if (m_CurrScene) m_CurrScene->Render();
}

void CGLFramework::Reshape(int w, int h)
{
	if (m_CurrScene) m_CurrScene->Reshape(w, h);

	glutPostRedisplay();
}

void CGLFramework::Keyboard(unsigned char key, int x, int y)
{
	if (m_CurrScene) m_CurrScene->Keyboard(key, x, y);
}

void CGLFramework::SpecialKeys(int key, int x, int y)
{
	if(m_CurrScene) m_CurrScene->SpecialKeys(key, x, y);
}

void CGLFramework::Timer(int value)
{
	if (m_CurrScene) m_CurrScene->Timer(value);

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
	auto old = m_CurrScene;
	m_CurrScene = newScene;
	delete old;
}
