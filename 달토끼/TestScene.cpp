#include "pch.h"
#include "ObjModel.h"
#include "TestScene.h"


CTestScene::CTestScene()
{

}

CTestScene::~CTestScene()
{
	delete m_obj;
	m_obj = nullptr;
}

void CTestScene::Initialize()
{
	m_obj = new CObjModel;
	m_obj->Initialize();
}


void CTestScene::Render()
{
	glColor3f(1.0f, 0.5f, 0.5f);
	//glRectf(100, 100, 200, 200);
	
	glPushMatrix();
		glTranslated(300, 300, 0);
		glRotated(rotateXdegree, 0, 0, 1);
		glRotated(rotateYdegree, 0, 1, 0);
		glScaled(3, 3, 3);

	if (m_obj != nullptr){
		m_obj->Render();
	}
	glPopMatrix();
}

void CTestScene::Update()
{
}

void CTestScene::Reshape(int w, int h)
{

}

void CTestScene::Timer(int value)
{

	glutPostRedisplay();
}

void CTestScene::Keyboard(unsigned char key, int x, int y)
{
	if (key == 'a') {
		rotateXdegree -= 5;
	}

	if (key == 'd') {
		rotateXdegree += 5;
	}

	if (key == 'w') {
		rotateYdegree += 5;
	}

	if (key == 's') {
		rotateYdegree -= 5;

	}
}
