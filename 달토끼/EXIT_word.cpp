#include "pch.h"
#include "ObjModel.h"
#include "EXIT_word.h"


CEXIT_word::CEXIT_word()
{
	m_model = new CObjModel;
	m_model->LoadObj("sample_exit.obj");


}


CEXIT_word::~CEXIT_word()
{

}

void CEXIT_word::Render()
{
	m_model->Render();
}

void CEXIT_word::Update()
{
}
