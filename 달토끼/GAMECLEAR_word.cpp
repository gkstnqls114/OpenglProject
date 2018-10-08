#include "pch.h"
#include "ObjModel.h"
#include "RotateMatrix.h"
#include "GAMECLEAR_word.h"


CGAMECLEAR_word::CGAMECLEAR_word(const CVector3D<>& Pos)
{

	if (m_model != nullptr) return;

	m_model = new CObjModel;
	m_model->LoadObj(".\\OBJModel\\GAMECLEARWORD.obj");
	m_model->LoadTexture(".\\Texture\\GAMECLEARWORD.bmp");
	
	m_Position = Pos;
	m_matrix = new RotateMatrix;
	//m_matrix->Set_Translate(m_Position);
}

CGAMECLEAR_word::~CGAMECLEAR_word()
{
}

void CGAMECLEAR_word::Render()
{
	glColor3f(LIGHTRGB.x, LIGHTRGB.y, LIGHTRGB.z);
	glPushMatrix();
	glTranslatef(m_Position.x, m_Position.y, m_Position.z);
	m_matrix->Rotate();
	m_model->Render();
	glPopMatrix();
}

void CGAMECLEAR_word::Update()
{
}
