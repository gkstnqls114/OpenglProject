#include "pch.h"
#include "Matrix.h"
#include "ObjModel.h"
#include "EXIT_word.h"


CEXIT_word::CEXIT_word(const CVector3D<>& Pos)
{
	if (m_model != nullptr) return;

	m_model = new CObjModel;
	m_model->LoadObj("EXITWORD.obj");
	m_model->LoadTexture("EXITWORD.bmp");

	m_Position = Pos;
	m_matrix = new CMatrix;
	m_matrix->Calu_Tranlate(m_Position);
}

CEXIT_word::~CEXIT_word()
{
	delete m_model;
	delete m_matrix;
}

void CEXIT_word::Render()
{
	glPushMatrix();
	m_matrix->MultiMatrix();
	m_model->Render();
	glPopMatrix();
}

void CEXIT_word::Update()
{
	if (!IsSelected) return;

	m_matrix->Calu_Rotate(5, 0, 1, 0);
}

void CEXIT_word::Scale(const float & size)
{
	m_matrix->Calu_Scale(size);
}
