#pragma once

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

	static CObjModel* m_Rabits_Helmet	;

	CPlayerState* m_PlayerState{ nullptr };

	CMediator* m_pMediator{nullptr};

	CMatrix* m_Matrix{nullptr};

	CVector3D<> m_Pos;

	bool IsTumbling{ false };
	float Tumblingdegree{ 0 };

	float Rotatedegree{ 0 };
	float Sidedegree{ 0 };
	
	//현재 발판 넘버
	int m_BoardNum{ 0 };
	int m_MySide{ 0 };

	
private:

	void ProcessSide(int& lhs);
	void Jump_BodyRotate();
	void Find_JumpProperty();
	void Jump();
	void Calculate_JumpVector();
	void Reset_JumpProperty();
	void Finish_Jump();

	static void InitBody();
	static void InitEar();
	static void InitLeftFoot();
	static void InitRightFoot();
	static void InitHelmet();
	static void DeleteBody();
	static void DeleteEar();
	static void DeleteLeftFoot();
	static void DeleteRightFoot();
	static void DeleteHelmet();

public:
	CPlayer(CMediator*& mediator);
	~CPlayer();
	static void InitModel();
	static void DeleteModel();
	void Initialize();

	CVector3D<> GetPos() const noexcept { return m_Pos; }

	void Keyboard(const unsigned char& key, const int& x, const int& y);
	void SpecialKeys(const int& key, const int& x, const int& y);
	void Update();
	void Render();

	const int Get_BoardNum() const noexcept { return m_BoardNum; }
	const int Get_Side() const noexcept { return m_MySide; }
	const float Get_Sidedegree() const noexcept{ return Sidedegree; };

	void ChangeState(CPlayerState* state);

	//Mediator
	//virtual void Init_GameScene();
	//virtual void Player_Jumping();
	//virtual void Player_JumpFinish();
	//virtual void Player_Dead();
	//virtual void Player_Fall();

	//virtual void Player_Clear();

	//virtual void Init_GameOver();
};

