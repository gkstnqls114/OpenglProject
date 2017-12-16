#include "pch.h"
//#include "SoundManager.h"
#include "GLFramework.h"

using namespace std;

#define Window_Width 800
#define Window_Height 800


namespace
{
	CGLFramework framework;

}//익명 네임스페이스 


void main(int argc, char** argv)
{
	//초기화 함수들
	framework.Initialize(argc, argv, 600, 800, 0, 0);

	framework.RegisterDrawFunction([]() {framework.DrawScene(); });
	framework.RegisterTimerFunction([](int val) {framework.Timer(val); });
	framework.RegisterReshapeFunction([](int w, int h) { framework.Reshape(w, h); });
	framework.RegisterKeyboardFunction([](unsigned char key, int x, int y) { framework.Keyboard(key, x, y); });
	framework.RegisterSpecialKeysFunction([](int key, int x, int y) { framework.SpecialKeys(key, x, y); });

	framework.Bind();
	framework.Run();
}
