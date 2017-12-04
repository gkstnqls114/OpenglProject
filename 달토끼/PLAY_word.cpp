#include "pch.h"
#include "ObjModel.h"
#include "Matrix.h"
#include "PLAY_word.h"


CPLAY_word::CPLAY_word(const CVector3D& pos)
{
	m_model = new CObjModel;
	m_model->LoadObj("sample_play.obj");

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

	m_matrix->Calu_Rotate(5, 0, 1, 0);
}

void CPLAY_word::Scale(const float & size)
{
	m_matrix->Calu_Scale(size);
}
