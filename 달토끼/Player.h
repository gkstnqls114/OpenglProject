#pragma once
#include "RoadObserver.h"

#include "WaitCamera.h"
#include "Waiting.h"
#include "FrontJump.h"
#include "RightJump.h"
#include "LeftJump.h"
#include "Fall.h"
#include "Dead.h"

#include "JumpProperty.h"


class CObjModel;
class RotateMatrix;
class CMediator;
class Road;
class CCamera;

class CPlayerState;
class PlayerSubject;


class CPlayer
	: public RoadObserver
{
	static CObjModel* m_Rabit_Body		;
	static CObjModel* m_Rabit_Ear		;
	static CObjModel* m_Rabit_LeftFoot	;
	static CObjModel* m_Rabit_RightFoot	;

	PlayerSubject* m_pPlayerSubject{ nullptr };

	//플레이어 위치
	CVector3D<> m_Pos;
	RotateMatrix* m_Matrix{ nullptr };
	GLdouble m_CollideY{ 30 }; /* 플레이어 Y 위치에 이 값을 더해 충돌을 계산해야 합니다*/
	int m_playerRadius{ 30 };
	
	//플레이어 상태
	JumpProperty m_JumpProperty;
	CPlayerState* m_PlayerState{ nullptr };
	
	CDead		DeadState;
	WaitCamera  WaitCameraState;
	CWaiting	WaitingState;
	CFalling	FallingState;
	CFrontJump	FrontJumpState;
	CRightJump	RightJumpState;
	CLeftJump	LeftJumpState;
	
	//현재 넘어간 발판 개수
	int m_MyBoardLength{ 0 };
	//좌, 우, 앞 발판 중 어디에 있는가?
	Side m_MyBoardSide;
	// 방향키를 이전에 어떤 것을 눌렀는가?
	Side m_prevKeySide;
	Side m_MyKeySide;

private:
	float BodyRotateDegree(); //함수이름 나중에 수정
	void JumpRotate(); //함수이름 나중에 수정
	void Calculate_JumpVector();
	const bool IsGetOutRoad() const noexcept;
	void Render_TestRadius();

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

	void Reset_ModelRotate();

	/////////////////////////////////Init
	void Init_GameScene();
	void Init_GameOver();
	/////////////////////////////////Init
	
	/////////////////////////////////State
	void FrontJump();
	void RightJump();
	void LeftJump();
	void WaitCamera();
	void Fall();
	void Dead();

	void StateChange_FrontJump();
	void StateChange_RightJump();
	void StateChange_LeftJump();
	void StateChange_Wait();
	void StateChange_WaitCamera();
	void StateChange_Fall();
	void StateChange_Dead();
	/////////////////////////////////State

	/////////////////////////////////Road Observer
	virtual void Receive_DisappearFootBoard(Road* road) override;
	/////////////////////////////////Road Observer

	/////////////////////////////////GET
	const GLdouble Get_JumpReach() const noexcept { return m_JumpProperty.Get_JumpReach(); }
	const int Get_BoardLength() const noexcept { return m_MyBoardLength; }
	const Side Get_KeySide() const noexcept { return m_MyKeySide; }
	const Side Get_BoardSide() const noexcept { return m_MyBoardSide; }
	const CVector3D<> Get_Pos() const noexcept { return m_Pos; }
	const CVector3D<GLdouble> Get_CollidPos() const noexcept { return CVector3D<>(m_Pos.x, m_Pos.y + m_CollideY, m_Pos.z); }
	const int Get_Radius() const noexcept { return m_playerRadius; }
	/////////////////////////////////GET

	/////////////////////////////////SET
	void RotateX(const int degree);
	void RotateY(const int degree);
	void RotateZ(const int degree);
	void Set_PlayerSubjer(PlayerSubject* subject) noexcept { m_pPlayerSubject = subject; };
	/////////////////////////////////SET

};
