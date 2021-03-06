#include "pch.h"
#include "ObjModel.h"
#include "RotateMatrix.h"
#include "GAMEOVER_word.h"


CGAMEOVER_word::CGAMEOVER_word(const CVector3D<>& Pos)
{
	if (m_model != nullptr) return;

	m_model = new CObjModel;
	m_model->LoadObj(".\\OBJModel\\GAMEOVERWORD.obj");
	m_model->LoadTexture(".\\Texture\\GAMEOVERWORD.bmp");

	m_Position = Pos;
	m_matrix = new RotateMatrix;
	//m_matrix->Set_Translate(m_Position);
}

CGAMEOVER_word::~CGAMEOVER_word()
{
}

void CGAMEOVER_word::Render()
{
	glPushMatrix();
	glTranslatef(m_Position.x, m_Position.y, m_Position.z);
	m_matrix->Rotate();
	m_model->Render();
	glPopMatrix();
}

void CGAMEOVER_word::Update()
{
}
