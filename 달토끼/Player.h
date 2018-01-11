#pragma once
#include "Waiting.h"
#include "FrontJump.h"
#include "JumpProperty.h"


class CObjModel;
class CMatrix;
class CMediator;
class CRoad;
class CCamera;

class CPlayerState;


class CPlayer
{
	static CObjModel* m_Rabit_Body		;
	static CObjModel* m_Rabit_Ear		;
	static CObjModel* m_Rabit_LeftFoot	;
	static CObjModel* m_Rabit_RightFoot	;

	CMediator* m_pMediator{ nullptr };

	//플레이어 위치
	CVector3D<> m_Pos;
	CMatrix* m_Matrix{ nullptr };
	
	//플레이어 상태
	CJumpProperty m_JumpProperty;
	CPlayerState* m_PlayerState{ nullptr };
	
	CWaiting WaitingState;
	CFrontJump FrontJumpState;

	//현재 발판 넘버
	int m_BoardNum{ 0 };
	int m_prevSide{ 0 };
	int m_MySide{ 0 };

private:
	void ProcessSide(int& lhs);
	void Jump_BodyRotate();
	//void Jump();
	void Calculate_JumpVector();
	void Finish_Jump();

	static void InitBody();
	static void InitEar();
	static void InitLeftFoot();
	static void InitRightFoot();
	static void DeleteBody();
	static void DeleteEar();
	static void DeleteLeftFoot();
	static void DeleteRightFoot();


public:
	CPlayer(CMediator*& mediator);
	~CPlayer();
	static void InitModel();
	static void DeleteModel();
	void Initialize();

	void Keyboard(const unsigned char& key, const int& x, const int& y);
	void SpecialKeys(const int& key, const int& x, const int& y);
	void Update();
	void Render();

	void FrontJump();
	void RightJump();
	void LeftJump();

	/////////////////////////////////State Change
	void StateChange_FrontJump();
	void StateChange_RightJump();
	void StateChange_LeftJump();
	void StateChange_Wait();
	void StateChange_Fall();
	/////////////////////////////////State Change

	/////////////////////////////////Mediator
	virtual void Init_GameScene();
	virtual void Init_GameOver();
	/////////////////////////////////Mediator

	/////////////////////////////////GET
	const GLdouble Get_JumpReach() const noexcept { return m_JumpProperty.Get_JumpReach(); }
	const int Get_BoardNum() const noexcept { return m_BoardNum; }
	const int Get_Side() const noexcept { return m_MySide; }
	CVector3D<> GetPos() const noexcept { return m_Pos; }
	/////////////////////////////////GET

	/////////////////////////////////SET
	void RotateX(const int degree);
	void RotateY(const int degree);
	void RotateZ(const int degree);
	/////////////////////////////////SET

};

