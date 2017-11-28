#include "pch.h"
#include "Scene.h"


void CScene::RenderAxis()
{
	//좌표축 중심선을 그린다.

	//중심선
	//glPushMatrix();
	glColor3f(1.f, 0.f, 0.f);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(1000, 0, 0);
	glEnd();

	//y
	glColor3f(0.f, 1.f, 0.f);
	glBegin(GL_LINES);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 1000, 0);
	glEnd();

	//z
	glColor3f(0.f, 0.f, 1.f);
	glBegin(GL_LINES);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 0, 1000);
	glEnd();

	//50pixel마다 점찍는다
	glPointSize(10);
	glBegin(GL_POINTS);
	for (int x = 0; x < 100; ++x) {
		glColor3f(1, 0, 0);
		glVertex3d(10 * x, 0, 0);

		glColor3f(0, 1, 0);
		glVertex3d(0, 10 * x, 0);

		glColor3f(0, 0, 1);
		glVertex3d(0, 0, -10 * x);
	}
	glEnd();
	glPointSize(1);
}

CScene::CScene()
{
}


CScene::~CScene()
{
}
