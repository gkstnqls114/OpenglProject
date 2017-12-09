#include "pch.h"
#include "ObjModel.h"
#include "Matrix.h"
#include "GAMEOVER_word.h"


CGAMEOVER_word::CGAMEOVER_word(const CVector3D<>& Pos)
{
	if (m_model != nullptr) return;

	m_model = new CObjModel;
	m_model->LoadObj("GAMEOVERWORD.obj");
	m_model->LoadTexture("GAMEOVERWORD.bmp");

	m_Position = Pos;
	m_matrix = new CMatrix;
	m_matrix->Set_Translate(m_Position);
}

CGAMEOVER_word::~CGAMEOVER_word()
{
}

void CGAMEOVER_word::Render()
{
	glPushMatrix();
	m_matrix->MultiMatrix();
	m_model->Render();
	glPopMatrix();
}

void CGAMEOVER_word::Update()
{
}
