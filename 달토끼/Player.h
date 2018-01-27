#pragma once
#include "Observer.h"

#include "WaitCamera.h"
#include "Waiting.h"
#include "FrontJump.h"
#include "RightJump.h"
#include "LeftJump.h"
#include "Fall.h"
#include "Dead.h"

#include "JumpProperty.h"


class CObjModel;
class CMatrix;
class CMediator;
class CRoad;
class CCamera;

class CPlayerState;
class PlayerObserver;


class CPlayer
	: public Observer
{
	static CObjModel* m_Rabit_Body		;
	static CObjModel* m_Rabit_Ear		;
	static CObjModel* m_Rabit_LeftFoot	;
	static CObjModel* m_Rabit_RightFoot	;

	PlayerObserver* m_pPlayerObserver{ nullptr };

	//플레이어 위치
	CVector3D<> m_Pos;
	CMatrix* m_Matrix{ nullptr };
	
	//플레이어 상태
	CJumpProperty m_JumpProperty;
	CPlayerState* m_PlayerState{ nullptr };
	
	CDead		DeadState;
	WaitCamera  WaitCameraState;
	CWaiting	WaitingState;
	CFalling	FallingState;
	CFrontJump	FrontJumpState;
	CRightJump	RightJumpState;
	CLeftJump	LeftJumpState;
	

	//현재 넘어간 발판 개수
	int m_MyBoardIndex{ 0 };
	//좌, 우, 앞 발판 중 어디에 있는가?
	int m_MyBoardSide{ 0 };
	// 방향키를 이전에 어떤 것을 눌렀는가?
	int m_prevKeySide{ 0 };
	int m_MyKeySide{ 0 };

private:
	

	float BodyRotateDegree(); //함수이름 나중에 수정
	void JumpRotate(); //함수이름 나중에 수정
	void Calculate_JumpVector();
	const bool IsGetOutRoad() const noexcept;
	const int RotateDegree() const { return abs(m_prevKeySide - m_MyKeySide); };

	void PrintSide() const
	{
		std::cout << "m_prevSide: " << m_prevKeySide << std::endl;
		std::cout << "m_MySide: " << m_MyKeySide << std::endl;
		std::cout << "RotateDegree: " << RotateDegree() << std::endl << std::endl;
	};

	static void InitBody();
	static void InitEar();
	static void InitLeftFoot();
	static void InitRightFoot();
	static void DeleteBody();
	static void DeleteEar();
	static void DeleteLeftFoot();
	static void DeleteRightFoot();


public:
	CPlayer();
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
	void Fall();
	void WaitCamera();
	
	/////////////////////////////////State Change
	void StateChange_FrontJump();
	void StateChange_RightJump();
	void StateChange_LeftJump();
	void StateChange_Wait();
	void StateChange_WaitCamera();
	void StateChange_Fall();
	void StateChange_Dead();
	/////////////////////////////////State Change

	/////////////////////////////////Mediator
	virtual void Init_GameScene();
	virtual void Init_GameOver();
	virtual void Notify_DisappearFootBoard(CRoad* road);
	/////////////////////////////////Mediator

	/////////////////////////////////GET
	const GLdouble Get_JumpReach() const noexcept { return m_JumpProperty.Get_JumpReach(); }
	const int Get_BoardNum() const noexcept { return m_MyBoardIndex; }
	const int Get_Side() const noexcept { return m_MyKeySide; }
	const CVector3D<> Get_Pos() const noexcept { return m_Pos; }
	/////////////////////////////////GET

	/////////////////////////////////SET
	void RotateX(const int degree);
	void RotateY(const int degree);
	void RotateZ(const int degree);
	void SetPlayerObserver(PlayerObserver* notification) noexcept { m_pPlayerObserver = notification; };
	/////////////////////////////////SET

};
