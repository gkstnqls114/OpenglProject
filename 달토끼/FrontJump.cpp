#include "pch.h"
#include "Player.h"
#include "FrontJump.h"


CFrontJump::CFrontJump()
{
}


CFrontJump::~CFrontJump()
{
}

void CFrontJump::Initialize()
{
}

void CFrontJump::Update(CPlayer & player)
{
	player.FrontJump();


	//if (!IsJump) return;

	//Calculate_JumpVector();
	//CVector3D<> move(m_vector_x, m_vector_y, m_vector_z);
	//m_Matrix->Calu_Tranlate(move);
	//
	//m_pMediator->Player_Jumping();

	//Finish_Jump();

}

void CFrontJump::SpecialKeys(CPlayer & player, const int & key)
{
}

