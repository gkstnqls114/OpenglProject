#include "pch.h"
#include "ObjModel.h"
#include "RotateMatrix.h"
#include "PLAY_word.h"


CPLAY_word::CPLAY_word(const CVector3D<>& pos)
{
	if (m_model != nullptr) return;

	m_model = new CObjModel;
	m_model->LoadObj(".\\OBJModel\\PLAYWORD.obj");
	m_model->LoadTexture(".\\Texture\\PLAYWORD.bmp");

	m_InitPosition = pos;
	m_Position = pos;
	m_matrix = new RotateMatrix;
//	m_matrix->Set_Translate(m_Position);
}


CPLAY_word::~CPLAY_word()
{
	delete m_model;
	delete m_matrix;
}

void CPLAY_word::Render()
{
	glPushMatrix();
	glTranslatef(m_Position.x, m_Position.y, m_Position.z);
	m_matrix->Rotate();
	glScalef(NowSize, NowSize, NowSize);
	m_model->Render();
	glPopMatrix();
}

void CPLAY_word::Update()
{
	if (IsGameStart) {
		//내려간다
		m_matrix->Calu_Rotate(5, 0, 1, 0);
	}
	if (!IsSelected) return;

	if (SizeTime >= 1.f) {
		SizeTime = 0.f;
		float temp = BeginSize;
		BeginSize = EndSize;
		EndSize = temp;
	}

	SizeTime += 0.03f;
	NowSize = Interpolation(BeginSize, EndSize, SizeTime);
}

void CPLAY_word::Init_MainScene()
{
	m_Position = m_InitPosition;
	m_matrix->ResetRotate();
	IsGameStart = false;
}

void CPLAY_word::GameStart()
{
	//회전 한바퀴
	IsGameStart = true;
}

void CPLAY_word::Scale(const float & size)
{
	NowSize = size;
	//m_matrix->Calu_Scale(NowSize);
}

void CPLAY_word::NotSelected()
{
	IsSelected = false;
	NowSize = 1.f;
	SizeTime = 0.f;
	BeginSize = 1.1f;
	EndSize = 1.3f;
	// m_matrix->ResetScale();
}
