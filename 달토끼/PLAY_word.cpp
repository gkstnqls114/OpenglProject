#include "pch.h"
#include "ObjModel.h"
#include "Matrix.h"
#include "PLAY_word.h"


CPLAY_word::CPLAY_word(const CVector3D<>& pos)
{
	if (m_model != nullptr) return;

	m_model = new CObjModel;
	m_model->LoadObj("PLAYWORD.obj");
	m_model->LoadTexture("PLAYWORD.bmp");

	m_Position = pos;
	m_matrix = new CMatrix;
	m_matrix->Calu_Tranlate(m_Position);
}


CPLAY_word::~CPLAY_word()
{
	delete m_model;
	delete m_matrix;
}

void CPLAY_word::Render()
{
	glPushMatrix();
	m_matrix->MultiMatrix();
	m_model->Render();
	glPopMatrix();
}

void CPLAY_word::Update()
{
	if (!IsSelected) return;

	m_matrix->Set_Scale(1.2f);
}

void CPLAY_word::Scale(const float & size)
{
	m_matrix->Calu_Scale(size);
}

void CPLAY_word::NotSelected()
{
	IsSelected = false;
	m_matrix->ResetScale();
}
