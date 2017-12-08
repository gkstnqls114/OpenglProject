#include "pch.h"
#include "Star.h"
#include "Skybox.h"


CSkybox::CSkybox()
{
	m_Stars = new CStar[m_StarNum];
}


CSkybox::~CSkybox()
{
	delete[] m_Stars;
}

void CSkybox::Render()
{
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);

	for (int index = 0; index < m_StarNum; ++index) {
		m_Stars[index].Render();
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
}

void CSkybox::Update()
{
	for (int index = 0; index < m_StarNum; ++index) {
		m_Stars[index].Update();
	}
}
