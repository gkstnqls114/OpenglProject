#pragma once

class CScene;
class CGameScene;

class CGLFramework
{
public:
	CGLFramework();
	~CGLFramework();

	void Initialize(int argc
		, char** argv
		, int width, int height
		, int x, int y
		, int DisplayMode = GLUT_DOUBLE | GLUT_RGBA);

	void Run() { glutMainLoop(); }

	void DrawScene();

	void Render();

	void Reshape(int w, int h);

	void Keyboard(unsigned char key, int x, int y);

	void SpecialKeys(int key, int x, int y);

	using DrawFunc = void(*)();
	using ReshapeFunc = void(*)(int, int);
	using TimerFunc = void(*)(int);
	using KeyboardFunc = void(*)(unsigned char, int, int);
	using SpecialKeysFunc = void(*)(int, int, int);

	void Timer(int value);

	void RegisterDrawFunction(DrawFunc&& draw);
	void RegisterTimerFunction(TimerFunc&& timer);
	void RegisterReshapeFunction(ReshapeFunc&& reshape);
	void RegisterKeyboardFunction(KeyboardFunc&& keyboard);
	void RegisterSpecialKeysFunction(SpecialKeysFunc&& specialkeys);

	void Bind();

	void ChangeScene(CScene* newScene);
private:

	TimerFunc	fnTimer{ nullptr };
	DrawFunc	fnDraw{ nullptr };
	ReshapeFunc	fnReshape{ nullptr };
	KeyboardFunc fnKeyboard{ nullptr };
	SpecialKeysFunc fnSpecialKeys{ nullptr };
	
	int m_fps = 16;

	CScene *		m_CurrScene{ nullptr };
};

